#ifndef PAIRHASH_H
#define PAIRHASH_H

#include <string>
#include <unordered_map>

struct PairHash {
    std::size_t operator()(const std::pair<std::string, std::string>& p) const {
        return std::hash<std::string>()(p.first) ^ (std::hash<std::string>()(p.second) << 1);
    }
};

#endif // PAIRHASH_H