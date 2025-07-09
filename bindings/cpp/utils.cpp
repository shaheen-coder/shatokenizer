#include "utils.hpp"

#include <sstream>

std::vector<std::string> split_words(const std::string& str){
    std::vector<std::string> words;
    std::stringstream ss(str);
    std::string temp;
    while(ss >> temp){
        words.push_back(temp);
    }
    return words;
}

std::vector<std::string> split_char(const std::string& word){
    std::vector<std::string> chrs;
    for(const auto& chr : word){
        chrs.push_back(std::to_string(chr));
    }
    return chrs;
}
std::pair<std::string, std::string> get_max_pair(
    const std::unordered_map<std::pair<std::string, std::string>, int, PairHash>& pairs
) {
    int max_freq = -1;
    std::pair<std::string, std::string> best_pair;

    for (const auto& [pair, freq] : pairs) {
        if (freq > max_freq) {
            max_freq = freq;
            best_pair = pair;
        }
    }

    return best_pair;
}

std::pair<std::string, std::string> get_min_pair(
    const std::unordered_map<std::pair<std::string, std::string>, int, PairHash>& pairs
) {
    int min_freq = std::numeric_limits<int>::max();
    std::pair<std::string, std::string> best_pair;

    for (const auto& [pair, freq] : pairs) {
        if (freq < min_freq) {
            min_freq = freq;
            best_pair = pair;
        }
    }

    return best_pair;
}


// Helper to join a vector of tokens into a single space‑delimited string
std::string join_tokens(const std::vector<std::string>& tokens) {
    std::ostringstream oss;
    if (!tokens.empty()) {
        oss << tokens[0];
        for (size_t i = 1; i < tokens.size(); ++i) {
            oss << ' ' << tokens[i];
        }
    }
    return oss.str();
}


void remove_w_tag(std::string& str) {
    const std::string from = "<w>";
    size_t pos = 0;
    while ((pos = str.find(from, pos)) != std::string::npos) {
        str.erase(pos, from.length()); 
    }
}

