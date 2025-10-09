# Polynomial Operator

The **Polynomial Operator** is an automation tool that collectivizes common polynomial manipulations and functions for a user-inputted integer coefficient polynomial of any degree or size. It outputs the results of common counting, divison, and factoring operations and algorithms in aid of any user looking to solve or operate on a polynomial.

---

## Quick Download (Recommended)

For casual users, this only downloads an executable app for easy access, suited to your OS. This format removes the tedium of extra installations, configurations, or compilations.

***Important Note:*** For some systems with auto-protection or malware scanners, the executable may be flagged as unknown. For users to continue, simply bypass (ex. clicking "Run Anyway"). The source code is all in this repository and I assure all that this project has no harmful intentions.

[![Windows](https://img.shields.io/badge/Download-Windows-blue?style=for-the-badge&logo=windows)](https://github.com/hgd-dev/Polynomial-Operator/actions/runs/18363655326/artifacts/4221895537)
[![macOS](https://img.shields.io/badge/Download-macOS-red?style=for-the-badge&logo=apple)](https://github.com/hgd-dev/Polynomial-Operator/actions/runs/18363655326/artifacts/4221890942)
[![Linux](https://img.shields.io/badge/Download-Linux-green?style=for-the-badge&logo=linux)](https://github.com/hgd-dev/Polynomial-Operator/actions/runs/18363655326/artifacts/4221890648)

***Caveat for all runs:*** This project has automatic input fail-safe detectors to ensure smooth running and correct input of data. While it is built-in to catch typos or mistaken keystrokes, please refrain from deliberately attempting to break the program or use corrupted data. Undefined behavior can have unintended consequences.

---

## Project Structure

```
Polynomial-Operator/
├── .github/ # GitHub Actions workflows
│ └── workflows/
│ └── build.yml
├── CMakeLists.txt # Build configuration for CMake
├── helper_functions_division_factoring.cpp # Division and Factoring functions source file
├── helper_functions_setup_input.cpp # Input and Setup functions source file
├── polynomial_long_division.cpp # Long division stand-alone source file
├── newton_polygonizer.cpp # Newton Polygonizer source file
└── polynomial_operator.cpp # Single-file version of the project
```

---

## Features

- From user-inputted integer coefficient polynomials of any magnitude, it can display the current polynomial; input or manipulate its various coefficients and terms; factor constants, perform polynomial long division, generate possible primes and roots, etc; construct a prime-based Newton Polygon using algorithms; and compute and factor linear terms.
- Outputs every result clearly, with algorithmic calculations or manipulations if applicable, in the terminal.  
- Cross-platform support: Windows, macOS, Linux.  
- Includes both multi-file CMake project and a single-file `polynomial_operator.cpp` version.  

---

## Build and Run Instructions (From project source code)

### **Requirements**

| Component                       | Version / Notes                          |
|---------------------------------|-----------------------------------------|
| C++ Compiler                     | C++17 compatible                         |
| CMake                            | 3.10+                                    |
| Operating System                 | Windows, macOS, Linux                    |

---

### **1. Multi-file Project (CMake)**

**Build:**

```bash
git clone https://github.com/hgd-dev/Polynomial-Operator.git
cd Polynomial-Operator

mkdir build && cd build
cmake ..
make
```

**Run:**

```
./PolynomialOperator
```

### **2. Single-file Version (graph_operator.cpp)**

**Compile:**

```bash
# Linux/macOS
g++ -std=c++17 polynomial_operator.cpp -o PolynomialOperator

# Windows (MinGW example)
g++ -std=c++17 polynomial_operator.cpp -o PolynomialOperator.exe
```

**Run:**

```bash
./PolynomialOperator   # or NewtonPolygonizer.exe on Windows

```


