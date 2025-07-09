#include <cstddef>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <unordered_map>
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

std::unordered_map<std::pair<std::string, std::string>, int, PairHash> ShaTokenizer::get_stats(const std::unordered_map<std::string,int>& vocab){
    std::unordered_map<std::pair<std::string, std::string>, int, PairHash> paris;

    for(const auto& [word,freq] : vocab){
        auto tokens = split_words(word);
        for(size_t i=0; i+1 < tokens.size(); ++i){
            paris[{tokens[i],tokens[i+1]}] += freq;
        }
    }

    return paris;
}

std::unordered_map<std::string,int> ShaTokenizer::merege_vocab(const std::pair<std::string,std::string>& pair, const std::unordered_map<std::string,int>& vocab) {
    std::unordered_map<std::string,int> new_vocab;
    for (const auto& [key, freq] : vocab) {
        // Split key into subwords
        std::vector<std::string> subwords;
        std::istringstream iss(key);
        std::string token;
        while (iss >> token) {
            subwords.push_back(token);
        }
        // Merge consecutive subwords matching the pair
        std::vector<std::string> new_subwords;
        size_t i = 0;
        while (i < subwords.size()) {
            if (i + 1 < subwords.size() && subwords[i] == pair.first && subwords[i + 1] == pair.second) {
                new_subwords.push_back(pair.first + pair.second);
                i += 2;
            } else {
                new_subwords.push_back(subwords[i]);
                i++;
            }
        }
        // Join subwords back into a string
        std::ostringstream oss;
        for (size_t j = 0; j < new_subwords.size(); ++j) {
            if (j > 0) oss << " ";
            oss << new_subwords[j];
        }
        std::string new_key = oss.str();
        new_vocab[new_key] = freq;
    }
    return new_vocab;
}



std::vector<std::string> ShaTokenizer::encode_word(const std::string& input) {
    std::vector<std::string> symbols;
    symbols.reserve(input.size() + 1);
    for (char c : input) {
        symbols.emplace_back(1, c);
    }
    symbols.emplace_back("<w>");

    std::unordered_map<std::string,int> current_vocab;
    current_vocab.reserve(1);
    current_vocab[join_tokens(symbols)] = 1;

    std::unordered_map<std::pair<std::string,std::string>,int,PairHash> pairs;
    pairs.reserve(symbols.size());

    while (true) {
        pairs = get_stats(current_vocab);

        auto best = pairs.end();
        int best_rank = std::numeric_limits<int>::max();

        for (auto it = pairs.begin(); it != pairs.end(); ++it) {
            auto rank_it = bpe_rank.find(it->first);
            if (rank_it != bpe_rank.end() && rank_it->second < best_rank) {
                best = it;
                best_rank = rank_it->second;
            }
        }

        if (best == pairs.end()) {
            break;
        }

        current_vocab = merege_vocab(best->first, current_vocab);

        const std::string& merged = current_vocab.begin()->first;
        symbols.clear();
        {
            std::istringstream iss(merged);
            std::string tok;
            while (iss >> tok) {
                symbols.emplace_back(std::move(tok));
            }
        }
    }

    return symbols;
}
std::vector<int> ShaTokenizer::encode(const std::string& str){
    std::vector<int> tokens;
    tokens.push_back(start_token_id);
    for(const auto& word : split_words(str)){
        auto word_encoded = encode_word(word);
        for(const auto& token : word_encoded){
            std::string temp = token;
            remove_w_tag(temp);
            auto it = token_to_id.find(temp);
            if (it == token_to_id.end()) {
                tokens.push_back(unk_token_id);
                std::cerr << "Unknown token “" << temp << "” in encode(); assigning <unk>=0\n";
                tokens.push_back(0);
            } else {
                tokens.push_back(it->second);
            }
        }
    }
    tokens.push_back(end_token_id); 
    return tokens;
}

std::string ShaTokenizer::decode(const std::vector<int>& ids){
    std::ostringstream oss;
    for (int id : ids) {
        if (id == pad_token_id || id == start_token_id || id == end_token_id) continue;
        auto it = id_to_token.find(id);
        if (it != id_to_token.end()) {
            oss << it->second;
            oss << " ";
        } else {
            oss << unk_token;
            oss << " ";  // fallback
        }
    }
    return oss.str();
}



void ShaTokenizer::train(std::string fname,int vocabSize){
    filename = fname;
    vocab_size = vocabSize;
    load_text();
    
    std::unordered_map<std::string,int> word_freq;
    
    // creating inital vocab
    for(const auto& line : sentence_list){
        for(const auto& words : split_words(line)){
            std::string temp;
            for(char chr : words){
                temp.append(1, chr);
                temp.append(" ");

            }
            temp += "<w>";
            word_freq[temp]++;
        }
    }
    for(std::size_t i = 0; i <= vocab_size; i++){
        auto paris = get_stats(word_freq);
        auto best = get_max_pair(paris);
        word_freq = merege_vocab(best,word_freq);
        bpe_rank[best] = static_cast<int>(i);

    }
    // Step 1: Clean vocab and collect tokens
    std::vector<std::string> tokens;
    tokens.reserve(word_freq.size() + 4); // room for 4 special tokens
    for (const auto& [word, freq] : word_freq) {
        std::string temp = word;
        remove_w_tag(temp);
        tokens.push_back(temp);
    }

    // Step 2: Add special tokens FIRST
    std::vector<std::string> special_tokens = {
        pad_token, unk_token, start_token, end_token
    };
    int idx = 0;
    for (const auto& tok : special_tokens) {
        token_to_id[tok] = idx;
        id_to_token[idx] = tok;
        if (tok == pad_token) pad_token_id = idx;
        else if (tok == unk_token) unk_token_id = idx;
        else if (tok == start_token) start_token_id = idx;
        else if (tok == end_token) end_token_id = idx;
        ++idx;
    }

    // Step 3: Add learned tokens
    for (std::size_t i = 0; i < tokens.size(); ++i) {
        token_to_id[tokens[i]] = static_cast<int>(i + idx);
        id_to_token[static_cast<int>(i + idx)] = tokens[i];
    }    
    vocab = word_freq;

}


