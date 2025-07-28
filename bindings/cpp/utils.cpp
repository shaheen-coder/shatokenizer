#include "utils.hpp"

#include <sstream>
#include <string>

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

// remove w tag in decode function [1.1.2]
std::string remove_w_tag_r(std::string str) {
    const std::string from = "<w>";
    size_t pos = 0;
    while ((pos = str.find(from, pos)) != std::string::npos) {
        str.erase(pos, from.length()); 
    }
    return str;
}

