#include "tri_diagonal.h"

#include <iostream>
#include <complex>

int main() {
  std::vector<double> a(6, 2.0);
  std::vector<double> b(6, 4.0);
  std::vector<double> c(6, 1.0);

  tri_diagonal<double> A(a, b, c);
  A.compute_lu();

  std::vector<double> r{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  std::vector<double> x = A.solve(r);

  double eps = 1e-5;
  if (std::abs(x[0] - 0.174686) < eps &&
      std::abs(x[1] - 0.301255) < eps &&
      std::abs(x[2] - 0.445607) < eps &&
      std::abs(x[3] - 0.615063) < eps &&
      std::abs(x[4] - 0.648536) < eps &&
      std::abs(x[5] - 1.17573) < eps) {
    std::cout << "Solve PASS!" << std::endl;
  } else {
    std::cout << "Solve FAIL!" << std::endl;
    std::cout << "x[0] = " << x[0] << ", expected to be: 0.174686" << std::endl;
    std::cout << "x[1] = " << x[1] << ", expected to be: 0.301255" << std::endl;
    std::cout << "x[2] = " << x[2] << ", expected to be: 0.445607" << std::endl;
    std::cout << "x[3] = " << x[3] << ", expected to be: 0.615063" << std::endl;
    std::cout << "x[4] = " << x[4] << ", expected to be: 0.648536" << std::endl;
    std::cout << "x[5] = " << x[5] << ", expected to be: 1.17573" << std::endl;
  }

  std::vector<double> y = A.multiply(r);
  if (std::abs(y[0] - 6.0) < eps &&
      std::abs(y[1] - 13.0) < eps &&
      std::abs(y[2] - 20.0) < eps &&
      std::abs(y[3] - 27.0) < eps &&
      std::abs(y[4] - 34.0) < eps &&
      std::abs(y[5] - 34.0) < eps) {
    std::cout << "Multiply PASS!" << std::endl;
  } else {
    std::cout << "Multiply FAIL!" << std::endl;
    std::cout << "y[0] = " << y[0] << ", expected to be: 6.0" << std::endl;
    std::cout << "y[1] = " << y[1] << ", expected to be: 13.0" << std::endl;
    std::cout << "y[2] = " << y[2] << ", expected to be: 20.0" << std::endl;
    std::cout << "y[3] = " << y[3] << ", expected to be: 27.0" << std::endl;
    std::cout << "y[4] = " << y[4] << ", expected to be: 34.0" << std::endl;
    std::cout << "y[5] = " << y[5] << ", expected to be: 34.0" << std::endl;
  }


  return 0;
}
