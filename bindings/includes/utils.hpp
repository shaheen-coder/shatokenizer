// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <unordered_map>
#include "../includes/pairhash.hpp"

std::vector<std::string> split_words(const std::string& str);

std::vector<std::string> split_char(const std::string& word);


std::string join_tokens(const std::vector<std::string>& tokens);

std::string remove_w_tag_r(std::string str); // [1.1.2]

#endif // UTILS_H