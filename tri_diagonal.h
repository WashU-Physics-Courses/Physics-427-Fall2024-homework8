#pragma once

#include <cmath>
#include <iostream>
#include <vector>

template <typename T> class tri_diagonal {
public:
  tri_diagonal(const std::vector<T> a0, const std::vector<T> b0,
               const std::vector<T> c0) {
    a = a0;
    b = b0;
    c = c0;
    u.resize(a.size());
    l.resize(a.size());
    y.resize(a.size());
  }

  void compute_lu() {
    // TODO: Implement this
  }

  std::vector<T> solve(const std::vector<T> &r) {
    if (r.size() != a.size()) {
      std::cout << "Error: r.size() != a.size()" << std::endl;
      return std::vector<T>();
    }
    std::vector<T> x(r.size());

    // TODO: Implement the rest of the function

    return x;
  }

  std::vector<T> multiply(const std::vector<T> &x) {
    if (x.size() != a.size()) {
      std::cout << "Error: x.size() != a.size()" << std::endl;
      return std::vector<T>();
    }
    std::vector<T> r(x.size());

    // TODO: Implement the rest of the function

    return r;
  }

  std::vector<T> a, b, c;
  std::vector<T> l, u;
  std::vector<T> y;
};
