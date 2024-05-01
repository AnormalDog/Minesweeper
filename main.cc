#include <iostream>
#include <string>
#include <fstream>
#include <queue>

#include "matrix_t.h"
#include "minefield.h"

std::queue<int> file_to_queue (std::string& file, bool& a) {
  std::queue<int> cola;
  std::ifstream my_file (file);
  if (!my_file.is_open()) {
    std::cerr << "error opening file" << std::endl;
    a = false;
    return cola;
  }
  std::string aux_1, aux_2;
  while (getline(my_file, aux_1)) {
    aux_2 += aux_1 + ' ';
  }
  my_file.close();
  for (size_t i = 0; i < aux_2.size(); ++i) {
    char aux = aux_2[i];
    if (aux != 32) {
     int char_to_number = aux;
     char_to_number -= 48; 
     cola.push(char_to_number);
    }
  }
  return cola;
}

void wait_to_press () {
  char a;
  std::cout << "enter any key..." << std::endl;
  std::cin >> a;
  return;
}

void clean_screen () {
  system ("clear");
}

int main (int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "invalid argument number" << std::endl;
    return 1;
  }
  bool game = true;
  std::string file_name {argv[1]};
  std::queue cola {file_to_queue(file_name, game)};
  if (game == false) {
    return 2;
  }

  minefield mines;
  mines.queue_to_build(cola);
  
  unsigned a, b;
  while (game) {
    clean_screen ();
    mines.super_print();
    std::cout << "Introduce the cordinates" << std::endl;
    std::cin >> a >> b;
    mines.touch (a, b, game);
  }
}