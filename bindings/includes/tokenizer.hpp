#ifndef ShaTokenizer_H
#define ShaTokenizer_H


#include <unordered_map>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include "../includes/pairhash.hpp"

class ShaTokenizer{
    private:
        std::string filename;
        std::vector<std::string> sentence_list;
        // uitls functions 
        void load_text();
    public:
        std::size_t vocab_size;
        std::unordered_map<std::string,int> vocab;
        std::unordered_map<std::pair<int, int>, int, IntPairHash> bpe_rank; 
        std::unordered_map<std::pair<int, int>, int, IntPairHash> merge_map;

        std::unordered_map<std::string,int> token_to_id;
        std::vector<std::string> id_to_token;
        
        // speical tokens 
        const std::string pad_token  = "<pad>";
        const std::string unk_token  = "<unk>";
        const std::string start_token = "<start>";
        const std::string end_token   = "<end>";


        // Special token IDs
        int pad_token_id   = -1;
        int unk_token_id   = -1;
        int start_token_id = -1;
        int end_token_id   = -1;

        // Accessors
        int get_pad_id() const { return pad_token_id; }
        int get_unk_id() const { return unk_token_id; }
        int get_start_id() const { return start_token_id; }
        int get_end_id() const { return end_token_id; }


        // public func
        void train(std::string fname,int vocabSize);
        std::vector<int> encode_word(const std::string& word);      
        std::vector<int> encode(const std::string& str);
        std::string decode(const std::vector<int>& ids);

};

#endif // ShaTokenizer_H