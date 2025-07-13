#include <cstddef>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <limits>
#include <sstream>
#include <algorithm>

#include "utils.hpp"
#include "tokenizer.hpp"


// load text from file
void ShaTokenizer::load_text(){
    std::ifstream File(filename);

    if(!File.is_open()){
        std::cerr<<"Error : could not open file ("<<filename<<")"<<std::endl;
        return;
    }

    std::string line;
    while(std::getline(File,line)){
        sentence_list.push_back(line);
    }

    File.close();
}


std::vector<int> ShaTokenizer::encode_word(const std::string& word) {
    std::vector<int> tokens;
    tokens.reserve(word.size() + 1);
    for (char c : word) {
        std::string s(1, c);
        tokens.push_back(token_to_id.contains(s) ? token_to_id[s] : unk_token_id);
    }
    tokens.push_back(token_to_id["<w>"]);

    while (true) {
        std::vector<std::pair<int, int>> pairs;
        pairs.reserve(tokens.size() - 1);
        for (size_t j = 0; j + 1 < tokens.size(); ++j) {
            pairs.emplace_back(tokens[j], tokens[j + 1]);
        }
        if (pairs.empty()) break;

        std::pair<int, int> best_pair;
        int best_rank = std::numeric_limits<int>::max();
        for (const auto& p : pairs) {
            if (auto it = bpe_rank.find(p); it != bpe_rank.end() && it->second < best_rank) {
                best_pair = p;
                best_rank = it->second;
            }
        }
        if (best_rank == std::numeric_limits<int>::max()) break;

        int new_id = merge_map[best_pair];
        std::vector<int> new_tokens;
        new_tokens.reserve(tokens.size());
        size_t k = 0;
        while (k < tokens.size()) {
            if (k + 1 < tokens.size() && tokens[k] == best_pair.first && tokens[k + 1] == best_pair.second) {
                new_tokens.push_back(new_id);
                k += 2;
            } else {
                new_tokens.push_back(tokens[k]);
                k++;
            }
        }
        tokens = std::move(new_tokens);
    }

    if (!tokens.empty() && tokens.back() == token_to_id["<w>"]) {
        tokens.pop_back();
    }
    return tokens;
}

std::vector<int> ShaTokenizer::encode(const std::string& str) {
    std::vector<int> tokens;
    tokens.reserve(str.size()); // Rough estimate
    tokens.push_back(start_token_id);
    for (const auto& word : split_words(str)) {
        auto word_tokens = encode_word(word);
        tokens.insert(tokens.end(), word_tokens.begin(), word_tokens.end());
    }
    tokens.push_back(end_token_id);
    return tokens;
}

std::string ShaTokenizer::decode(const std::vector<int>& ids) {
    std::ostringstream oss;
    for (int id : ids) {
        if (id == pad_token_id || id == start_token_id || id == end_token_id) continue;
        if (id >= 0 && static_cast<size_t>(id) < id_to_token.size()) {
            oss << id_to_token[id] << " ";
        } else {
            oss << unk_token << " "; // fallback
        }
    }
    return oss.str();
}

void ShaTokenizer::train(std::string fname, int vocabSize) {
    filename = fname;
    vocab_size = vocabSize;
    load_text();

    // Initialize initial tokens
    std::unordered_set<std::string> initial_tokens{"<w>"};
    for (const auto& line : sentence_list) {
        for (const auto& word : split_words(line)) {
            for (char c : word) {
                initial_tokens.insert(std::string(1, c));
            }
        }
    }

    // Add special tokens first
    int next_id = 0;
    for (const auto& tok : {pad_token, unk_token, start_token, end_token}) {
        token_to_id[tok] = next_id;
        id_to_token.push_back(tok);
        if (tok == pad_token) pad_token_id = next_id;
        else if (tok == unk_token) unk_token_id = next_id;
        else if (tok == start_token) start_token_id = next_id;
        else if (tok == end_token) end_token_id = next_id;
        ++next_id;
    }

    // Add initial character tokens
    for (const auto& token : initial_tokens) {
        if (!token_to_id.contains(token)) { // C++20 contains
            token_to_id[token] = next_id;
            id_to_token.push_back(token);
            ++next_id;
        }
    }

    // Build word frequencies and initial token lists
    std::unordered_map<std::string, int> word_freq;
    for (const auto& line : sentence_list) {
        for (const auto& word : split_words(line)) {
            word_freq[word]++;
        }
    }

    struct Word {
        std::vector<int> tokens;
        int freq;
    };
    std::vector<Word> words;
    words.reserve(word_freq.size()); // Pre-allocate for efficiency
    for (const auto& [word, freq] : word_freq) {
        std::vector<int> tokens;
        tokens.reserve(word.size() + 1);
        for (char c : word) {
            std::string s(1, c);
            tokens.push_back(token_to_id.contains(s) ? token_to_id[s] : unk_token_id);
        }
        tokens.push_back(token_to_id["<w>"]);
        words.push_back({std::move(tokens), freq});
    }

    // Training loop
    for (std::size_t i = 0; i < vocab_size; ++i) {
        std::unordered_map<std::pair<int, int>, int, IntPairHash> pair_freq;
        for (const auto& word : words) {
            const auto& tokens = word.tokens;
            for (size_t j = 0; j + 1 < tokens.size(); ++j) {
                pair_freq[{tokens[j], tokens[j + 1]}] += word.freq;
            }
        }

        if (pair_freq.empty()) break;
        auto best_pair = std::max_element(pair_freq.begin(), pair_freq.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; })->first;

        // Create new token
        std::string new_token = id_to_token[best_pair.first] + id_to_token[best_pair.second];
        int new_id = token_to_id.contains(new_token) ? token_to_id[new_token] : next_id++;
        if (new_id == next_id - 1) {
            token_to_id[new_token] = new_id;
            id_to_token.push_back(new_token);
        }

        // Record merge
        merge_map[best_pair] = new_id;
        bpe_rank[best_pair] = i;

        // Update words
        for (auto& word : words) {
            auto& tokens = word.tokens;
            std::vector<int> new_tokens;
            new_tokens.reserve(tokens.size());
            size_t k = 0;
            while (k < tokens.size()) {
                if (k + 1 < tokens.size() && tokens[k] == best_pair.first && tokens[k + 1] == best_pair.second) {
                    new_tokens.push_back(new_id);
                    k += 2;
                } else {
                    new_tokens.push_back(tokens[k]);
                    k++;
                }
            }
            tokens = std::move(new_tokens);
        }
    }

    // Populate vocab for compatibility (if needed by Python extension)
    for (const auto& word : words) {
        std::ostringstream oss;
        for (size_t i = 0; i < word.tokens.size(); ++i) {
            if (i > 0) oss << " ";
            oss << id_to_token[word.tokens[i]];
        }
        vocab[oss.str()] = word.freq;
    }
}
