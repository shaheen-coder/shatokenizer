// shatokenizer_pybind.cpp
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "tokenizer.hpp"
 
namespace py = pybind11;

PYBIND11_MODULE(shatokenizer, m) {
    m.doc() = "Pybind11 wrapper for ShaTokenizer";

    py::class_<ShaTokenizer>(m, "ShaTokenizerAPI")
        .def(py::init<>())
        .def("train", &ShaTokenizer::train,
              py::arg("fname"),py::arg("vocabSize"),
             "Train the tokenizer on the provided file")
        .def("encode_word", &ShaTokenizer::encode_word,
             py::arg("word"),
             "Encode a single word into BPE tokens")
        .def("encode", &ShaTokenizer::encode,
             py::arg("text"),
             "Encode a full string into a list of token IDs")
        .def("decode", &ShaTokenizer::decode,
             py::arg("ids"),
             "Decode a list of token IDs back into a string")
        // Special token accessors
        .def("get_pad_id", &ShaTokenizer::get_pad_id)
        .def("get_unk_id", &ShaTokenizer::get_unk_id)
        .def("get_start_id", &ShaTokenizer::get_start_id)
        .def("get_end_id", &ShaTokenizer::get_end_id)
        // Expose vocab size and vocab mapping
        .def_readwrite("vocab_size",    &ShaTokenizer::vocab_size)
        .def_readwrite("vocab",         &ShaTokenizer::vocab)
        .def_readwrite("bpe_rank",      &ShaTokenizer::bpe_rank)
        .def_readwrite("token_to_id",   &ShaTokenizer::token_to_id)
        .def_readwrite("id_to_token",   &ShaTokenizer::id_to_token)
        // if you want to modify the special‑token IDs from Python
        .def_readwrite("pad_token_id",   &ShaTokenizer::pad_token_id)
        .def_readwrite("unk_token_id",   &ShaTokenizer::unk_token_id)
        .def_readwrite("start_token_id", &ShaTokenizer::start_token_id)
        .def_readwrite("end_token_id",   &ShaTokenizer::end_token_id)
        ;
}
