// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <unordered_map>
#include "../includes/pairhash.hpp"

std::vector<std::string> split_words(const std::string& str);

std::vector<std::string> split_char(const std::string& word);

std::pair<std::string, std::string> get_max_pair(
    const std::unordered_map<std::pair<std::string, std::string>, int, PairHash>& pairs
);


std::pair<std::string, std::string> get_min_pair(
    const std::unordered_map<std::pair<std::string, std::string>, int, PairHash>& pairs
);

std::string join_tokens(const std::vector<std::string>& tokens);

void remove_w_tag(std::string& str);

#endif // UTILS_H