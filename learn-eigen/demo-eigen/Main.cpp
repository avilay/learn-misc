// clang++ -std=c++20 -I. Main.cpp

#include <Eigen/Dense>
#include <format>
#include <iostream>
#include <random>

namespace eg = Eigen;

void demo1() {
  eg::MatrixXf m(3, 2);

  m(0, 0) = 0.0;
  m(0, 1) = 0.1;

  m(1, 0) = 1.0;
  m(1, 1) = 1.1;

  m(2, 0) = 2.0;
  m(2, 1) = 2.1;

  std::cout << m << std::endl;

  float* data = m.data();
  int len{3 * 2};
  for (int i = 0; i < len; i++) {
    std::cout << std::format("data[{}] = {}", i, data[i]) << std::endl;
  }

  eg::Matrix<float, 3, 2, eg::RowMajor> n;
  n << 0.0, 0.1, 1.0, 1.1, 2.0, 2.1;
  std::cout << n << std::endl;
  data = n.data();
  for (int i = 0; i < len; i++) {
    std::cout << std::format("data[{}] = {}", i, data[i]) << std::endl;
  }

  eg::Matrix<float, 3, 2, eg::RowMajor> p{eg::MatrixXf::Random(3, 2)};
  std::cout << p << std::endl;

  std::cout << "Creating 2 random 1000x1000 matrices..." << std::endl;
  eg::MatrixXf a{eg::MatrixXf::Random(1000, 1000)};
  eg::MatrixXf b{eg::MatrixXf::Random(1000, 1000)};
  std::cout << "Multiplying the two matrices..." << std::endl;
  auto c = a * b;
  std::cout << c(0, 0) << " " << c(100, 100) << " " << c(999, 999) << std::endl;
  std::cout << "Done." << std::endl;

  int width{3};
  eg::MatrixXf x{eg::MatrixXf::Random(width, width)};
  std::cout << x << std::endl;

  eg::Matrix<float, eg::Dynamic, eg::Dynamic, eg::RowMajor> y{
      eg::MatrixXf::Random(width, width)};
  std::cout << y << std::endl;

  float* zdata = new float[3 * 2];
  for (int i = 0; i < 3 * 2; i++) {
    zdata[i] = i + 1;
  }
  // Need to know the size at compile time
  eg::Matrix<float, 3, 2> z{zdata};
  delete[] zdata; // zdata has been copied over to z
  std::cout << z << std::endl;
}

void demo2() {
  std::random_device device{};
  auto seed{device()};
  std::default_random_engine engine{seed};
  std::uniform_int_distribution<int> dist{1, 5};
  int width{dist(engine)};
  int len = width * width;
  float* data = new float[len];
  for (int i = 0; i < len; i++) {
    data[i] = i + 1;
  }

  eg::Map<eg::MatrixXf> mat(data, width, width);
  // delete[] data; --> data is shared with mat, deleting it will make mat
  // invalid
  std::cout << mat << std::endl;

  eg::MatrixXf x(width, width);
  x.setRandom();
  std::cout << x << std::endl;

  eg::MatrixXf y = mat * x;
  std::cout << y << std::endl;

  delete[] data; // responsibility of the client to free up the space
}

int main() { demo2(); }