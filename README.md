# ShaTokenizer 0.1.2

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


![Tokenization Time Comparison](https://quickchart.io/chart?c=%7B%22type%22%3A%22line%22%2C%22data%22%3A%7B%22labels%22%3A%5B%220%22%2C%22100%22%2C%22200%22%2C%22300%22%2C%22400%22%2C%22500%22%2C%22600%22%2C%22700%22%2C%22800%22%2C%22900%22%5D%2C%22datasets%22%3A%5B%7B%22label%22%3A%22v0.1.0%22%2C%22data%22%3A%5B84157%2C6977301%2C14437683%2C20902067%2C26554987%2C32350267%2C38075928%2C43831217%2C49559857%2C56149850%5D%2C%22borderColor%22%3A%22%23e74c3c%22%2C%22fill%22%3Afalse%7D%2C%7B%22label%22%3A%22v0.1.1%22%2C%22data%22%3A%5B5502%2C642335%2C1370924%2C2154547%2C2967434%2C3798688%2C4630268%2C5471428%2C6316320%2C7166352%5D%2C%22borderColor%22%3A%22%232ecc71%22%2C%22fill%22%3Afalse%7D%5D%7D%2C%22options%22%3A%7B%22title%22%3A%7B%22display%22%3Atrue%2C%22text%22%3A%22ShaTokenizer%20Tokenization%20Time%20Benchmark%20(%C2%B5s)%22%7D%2C%22scales%22%3A%7B%22yAxes%22%3A%5B%7B%22scaleLabel%22%3A%7B%22display%22%3Atrue%2C%22labelString%22%3A%22Time%20(%C2%B5s)%22%7D%7D%5D%2C%22xAxes%22%3A%5B%7B%22scaleLabel%22%3A%7B%22display%22%3Atrue%2C%22labelString%22%3A%22Tokens%20Processed%22%7D%7D%5D%7D%7D%7D)

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
