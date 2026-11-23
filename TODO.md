## Current Roadmap
- [ ] Add README.md
- [ ] Create naive implementation of a fixed-size mathematical vector
- [ ] Refactor constructors and mathematical operations to use standard algorithms
- [ ] Implement a second constructor using std::span 
- [ ] Benchmark and test the naive implementation using Google Benchmark and Catch2
- [ ] Create a Python interface using pybind11

## Current Tasks
- [ ] Setup Github Actions
- [ ] Implement iterators such as begin(), end() to allow integration with standard algorithms and range loops
- [ ] Implement scalar arithmetic... ex.
    vec += 5;
    vec *= 2;
    vec /= 3;
- [ ] Refactor constructor to use a variadic template constructor to allow compile time assertions


- save this header to add into tests/vector_tests.cpp:
//#include <catch2/matchers/catch_matchers_floating_point.hpp>