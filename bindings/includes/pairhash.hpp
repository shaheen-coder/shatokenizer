#ifndef PAIRHASH_H
#define PAIRHASH_H

#include <string>
#include <unordered_map>

struct IntPairHash {
    std::size_t operator()(const std::pair<int, int>& p) const {
        auto h1 = std::hash<int>{}(p.first);
        auto h2 = std::hash<int>{}(p.second);
        return h1 ^ (h2 << 1); // Simple hash combination
    }
};


#endif // PAIRHASH_H