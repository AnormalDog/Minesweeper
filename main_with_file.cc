/**
 * @brief My own interpretation of minesweper, for c++
 * @author AnormalDog
 * @date 1/6/2024
 * @file main_with_file.cc
 * 
*/

#include <iostream>
#include <string>
#include <fstream>
#include <queue>

#include "minefield.h"

/**
 * @brief Open a file, convert to string and convert to queue of int, using std::queue
 * @return queue<int>
 * @file main_with_file.cc 
 * 
*/
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
      if (aux_2[i+1] != 32) {
        int char_to_number_1 = aux_2[i] - 48;
        int char_to_number_2 = aux_2[i+1] - 48;
        ++i;
        int char_to_number = (10 * char_to_number_1) + char_to_number_2;
        cola.push(char_to_number);
      }
      else {
        int char_to_number = aux;
        char_to_number -= 48; 
        cola.push(char_to_number);
      }
    }
  }
  return cola;
}

/**
 * @brief clear the screen, using a syscall to linux
 * @return
 * @file main_with_file.cc
 * 
*/
void clean_screen () {
  system ("clear");
}

int main (int argc, char** argv) {
  bool game = true;
  bool debug = false;
  if (argc == 3) {
    std::string command = {argv[2]};
    if (command == "--debug") {
      debug = true;
    }
    else {
      std::cerr << "command not found" << std::endl;
      return 1;
    }
  }

  std::string file_name {argv[1]};

  std::queue cola {file_to_queue(file_name, game)};
  if (game == false) {
    return 2;
  }
  
  minefield mines;
  mines.queue_to_build(cola); // build the mines with the queue
  unsigned x, y, mode;
  while (game) {
    clean_screen ();
    std::cout << "MODES: 0 = touch / 1 = mark / 2 = remove mark /10 = exit" << std::endl;
    if (debug == true) {
      std::cout << "5 for debug info" << std::endl;
    }
    mines.print();
    std::cout << std::endl << "number of bombs: " << mines.get_number_of_bombs() << " number of marks: " 
      << mines.get_number_of_marks() << std::endl;
    std::cout << "Introduce the cordinates and mode (x, y, m):" << std::endl;
    std::cin >> x >> y >> mode;
    if (mode == 10) {
      return 0;
    }
    if (mode == 5) {
      clean_screen();
      mines.print_sol();
      char a;
      std::cin >> a;
    }
    if (mode >= 0 && mode < 3) {
      mines.touch (x, y, game, mode);
    }
    if (mines.is_a_win()) {
      std::cout << "YOU WON!" << std::endl;
      break;
    }
  }
  return 0;
}