from setuptools import setup, Extension, find_packages
import sys
import os

# Helper to locate pybind11 include
try:
    import pybind11
    pybind11_include = pybind11.get_include()
except ImportError:
    sys.stderr.write("Error: pybind11 is required to build the C++ extension. Install it via 'pip install pybind11'.\n")
    sys.exit(1)
here = os.path.abspath(os.path.dirname(__file__))

# Define extension module
module = Extension(
    name="shatokenizer.shatokenizer",
    sources=[
        os.path.join("bindings", "cpp", "main.cpp"),
        os.path.join("bindings", "cpp", "utils.cpp"),
        os.path.join("bindings", "cpp", "wapper.cpp"),
    ],
    include_dirs=[
        pybind11_include,
        os.path.join(here, "bindings", "includes"),
    ],
    language="c++",
    extra_compile_args=["-O3", "-std=c++20"],
)

# Read long description
here = os.path.abspath(os.path.dirname(__file__))
with open(os.path.join(here, "README.md"), encoding="utf-8") as f:
    long_description = f.read()

setup(
    name="shatokenizer",
    version="0.1.0",
    author="Shaheen Ahmed",
    author_email="shaheenvsa@gmail.com",
    description="High-performance bpe tokenizer with C++ backend and Python bindings",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/shaheen-coder/shatokenizer",
    packages=find_packages(where="src"),
    package_dir={"": "src"},
    ext_modules=[module],
    install_requires=[
        "pybind11>=2.6.0"
    ],
    classifiers=[
        "Programming Language :: Python :: 3",
        "Programming Language :: C++",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    python_requires='>=3.7',
    include_package_data=True,
    zip_safe=False,
    )

