#include <iostream>

#include "matrix_t.h"
#include "minefield.h"

int main () {
  minefield gato;
  std::cin >> gato;
  gato.print();
  gato.show_spaces(0, 3);

  gato.print();
}