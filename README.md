# ShaTokenizer 0.1.1

[![PyPI version](https://badge.fury.io/py/shatokenizer.svg)](https://badge.fury.io/py/shatokenizer)
[![Python versions](https://img.shields.io/pypi/pyversions/shatokenizer.svg)](https://pypi.org/project/shatokenizer/)
[![License](https://img.shields.io/github/license/shaheen-coder/shatokenizer.svg)](LICENSE)
[![PyPI downloads](https://img.shields.io/pypi/dm/shatokenizer.svg)](https://pypi.org/project/shatokenizer/)
[![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)
[![pybind11](https://img.shields.io/badge/pybind11-2.11%2B-blue.svg)](https://pybind11.readthedocs.io/)

A high-performance BPE (Byte Pair Encoding) tokenizer with Python bindings and a header-only C++ implementation.

## Features

- 🚀 **Fast C++ Core**: Header-only C++ implementation for maximum performance
- 🐍 **Python Bindings**: Easy-to-use Python API with pybind11
- 💾 **Serialization**: Save and load trained tokenizer models
- 🔧 **Header-Only**: Simple integration into C++ projects
- 📊 **BPE Algorithm**: Efficient subword tokenization
- 🎯 **Cross-Platform**: Works on Windows, macOS, and Linux

## ⏱️ Tokenization Time Benchmark

### 🔄 Version Comparison: `v0.1.1` vs `v0.1.0`

Significant improvements in tokenization speed have been made in version **0.1.1** compared to the initial release **0.1.0**.

| Tokens Processed | Time (v0.1.0) | Time (v0.1.1) | Speedup |
| ---------------- | ------------- | ------------- | ------- |
| 0                | 84,157 µs     | 5,502 µs      | \~15×   |
| 100              | 6,977,301 µs  | 642,335 µs    | \~10.9× |
| 200              | 14,437,683 µs | 1,370,924 µs  | \~10.5× |
| 300              | 20,902,067 µs | 2,154,547 µs  | \~9.7×  |
| 400              | 26,554,987 µs | 2,967,434 µs  | \~8.9×  |
| 500              | 32,350,267 µs | 3,798,688 µs  | \~8.5×  |
| 600              | 38,075,928 µs | 4,630,268 µs  | \~8.2×  |
| 700              | 43,831,217 µs | 5,471,428 µs  | \~8.0×  |
| 800              | 49,559,857 µs | 6,316,320 µs  | \~7.8×  |
| 900              | 56,149,850 µs | 7,166,352 µs  | \~7.8×  |
| 1000             | 62,877,499 µs | *(Pending)*   | *(N/A)* |

⚡ **Overall**, version `0.1.1` is **7–15× faster** across the board due to internal optimizations and improved data structures.

> 💡 *Benchmark run with vocab size of 1000 tokens. Measurements are approximate and may vary slightly based on system specs.*

---

### 📈 Visual Benchmark

You can visualize the performance improvements in the chart below:

#### Time Comparison (Lower is Better)

!\[Tokenization Time Comparison]\([https://quickchart.io/chart?c={](https://quickchart.io/chart?c={)
"type":"line",
"data":{
"labels":\["0","100","200","300","400","500","600","700","800","900"],
"datasets":\[
{
"label":"v0.1.0",
"data":\[84157,6977301,14437683,20902067,26554987,32350267,38075928,43831217,49559857,56149850],
"borderColor":"#e74c3c",
"fill"\:false
},
{
"label":"v0.1.1",
"data":\[5502,642335,1370924,2154547,2967434,3798688,4630268,5471428,6316320,7166352],
"borderColor":"#2ecc71",
"fill"\:false
}
]
},
"options":{
"title":{
"display"\:true,
"text":"ShaTokenizer Tokenization Time Benchmark (µs)"
},
"scales":{
"yAxes":\[{"scaleLabel":{"display"\:true,"labelString":"Time (µs)"}}],
"xAxes":\[{"scaleLabel":{"display"\:true,"labelString":"Tokens Processed"}}]
}
}
})

> 📊 Powered by [QuickChart.io](https://quickchart.io) for inline GitHub chart rendering.

---
## Installation

### From PyPI

```bash
pip install shatokenizer
```

### From Source

```bash
git https://github.com/shaheen-coder/shatokenizer.git
cd shatokenizer
pip install .
```

## Quick Start

### Python Usage

```python
from shatokenizer import ShaTokenizer

# Create tokenizer instance
tokenizer = ShaTokenizer()

# Train on your dataset
tokenizer.train('dataset.txt', 1000)

# Encode text to token IDs
tokens = tokenizer.encode('hello this tokenizer')
print(tokens)  # [123, 43, 1211]

# Decode token IDs back to text
text = tokenizer.decode(tokens)
print(text)  # "hello this tokenizer"

# Save trained model
tokenizer.save("shatokenizer.pkl")

# Load trained model
tokenizer2 = ShaTokenizer.load("shatokenizer.pkl")
```

### C++ Usage

```cpp
#include <iostream>
#include <shatokenizer/tokenizer.hpp>

int main() {
    auto tokenizer = new ShaTokenizer();
    tokenizer->train("data.txt", 1000);
    
    auto ids = tokenizer->encode("hello");
    std::cout << "decode: " << tokenizer->decode(ids) << std::endl;
    
    delete tokenizer;
    return 0;
}
```

## API Reference

### Python API

#### `ShaTokenizer()`
Creates a new tokenizer instance.

#### `train(dataset_path: str, vocab_size: int) -> None`
Trains the tokenizer on the provided dataset.

- `dataset_path`: Path to the training text file
- `vocab_size`: Target vocabulary size

#### `encode(text: str) -> List[int]`
Encodes text into token IDs.

- `text`: Input text to encode
- Returns: List of token IDs

#### `decode(tokens: List[int]) -> str`
Decodes token IDs back to text.

- `tokens`: List of token IDs
- Returns: Decoded text string

#### `save(path: str) -> None`
Saves the trained tokenizer model.

- `path`: Output file path

#### `load(path: str) -> ShaTokenizer` (static method)
Loads a trained tokenizer model.

- `path`: Path to saved model file
- Returns: Loaded tokenizer instance

## Building from Source

### Requirements

- Python 3.7+
- C++17 compatible compiler
- pybind11
- CMake (for C++ development)

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/yourusername/shatokenizer.git
cd shatokenizer

# Install in development mode
pip install -e .
```

## Contributing

We welcome contributions! Please see our [Contributing Guide](CONTRIBUTING.md) for details.

### Development Setup

1. Fork the repository
2. Create a virtual environment:
   ```bash
   python -m venv venv
   source venv/bin/activate  # On Windows: venv\Scripts\activate
   ```
3. Install development dependencies:
   ```bash
   pip install -e ".[dev]"
   ```
4. Run tests:
   ```bash
   pytest
   ```

### Code Style

- Python code should follow PEP 8
- C++ code should follow Google C++ Style Guide
- Use `black` for Python formatting
- Use `clang-format` for C++ formatting

### Submitting Changes

1. Create a feature branch: `git checkout -b feature-name`
2. Make your changes and add tests
3. Ensure all tests pass: `pytest`
4. Format your code: `black .` and `clang-format -i src/*.cpp src/*.hpp`
5. Commit your changes: `git commit -m "Add feature"`
6. Push to your fork: `git push origin feature-name`
7. Open a Pull Request

## Performance

ShaTokenizer is designed for high performance:

- C++ core implementation for speed-critical operations
- Minimal Python overhead with pybind11
- Efficient memory usage with header-only design
- Optimized BPE algorithm implementation

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Built with [pybind11](https://pybind11.readthedocs.io/)
- Inspired by modern tokenization libraries
- Thanks to all contributors

## Support

- 📝 [Documentation](https://github.com/shaheen-coder/shatokenizer/wiki)
- 🐛 [Issue Tracker](https://github.com/shaheen-coder/shatokenizer/issues)
- 💬 [Discussions](https://github.com/shaheen-coder/shatokenizer/discussions)

---

**Made with ❤️ by Shaheen**