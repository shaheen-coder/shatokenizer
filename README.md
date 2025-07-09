# ShaTokenizer

[![PyPI version](https://badge.fury.io/py/shatokenizer.svg)](https://badge.fury.io/py/shatokenizer)
[![Python versions](https://img.shields.io/pypi/pyversions/shatokenizer.svg)](https://pypi.org/project/shatokenizer/)
[![License](https://img.shields.io/github/license/yourusername/shatokenizer.svg)](LICENSE)
[![Build Status](https://github.com/yourusername/shatokenizer/workflows/CI/badge.svg)](https://github.com/yourusername/shatokenizer/actions)
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