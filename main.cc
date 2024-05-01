#include <iostream>


#include "matrix_t.h"

int main () {
  matrix_t<int> perro;
  std::cin >> perro;
  perro.simple_print();
}