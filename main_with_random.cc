/**
 * @brief My own interpretation of minesweper, for c++.
 * Now with random matrix
 * @author AnormalDog
 * @date 2/6/2024
 * @file main_with_random.cc
 * 
*/

#include <iostream>
#include <string>
#include <fstream>
#include <queue>

#include "minefield.h"


/**
 * @brief clear the screen, using a syscall to linux
 * @return
 * @file main_with_random.cc
 * 
*/
void clear_screen () {
  system ("clear");
} 

int main (int argc, char** argv) {
  unsigned number_of_inters {0};
  bool game {true};

  minefield mines;
  unsigned x, y, mode, n, m;
  std::cout << "Introduce the size of the game: " << std::endl;
  std::cin >> n >> m;
  mines.build(n, m);
  
  while (game) {
    clear_screen ();
    std::cout << "MODES: 0 = touch / 1 = mark / 2 = remove mark /10 = exit" << std::endl;
    mines.print();
    std::cout << std::endl << "number of bombs: " << mines.get_number_of_bombs() << " number of marks: " 
      << mines.get_number_of_marks() << std::endl;
    std::cout << "Introduce the cordinates and mode (x, y, m):" << std::endl;
    std::cin >> x >> y >> mode;    
    if (mode == 10) { // EXIT
      return 0;
    }
    if (mode >= 0 && mode < 3) { // NORMAL
      if (number_of_inters == 0) { // If first iteration, create the matrix
        mines.get_a_random_matrix(n, m, x, y);
        mines.touch(x, y, game, mode);
      }
      else { // normal
        mines.touch(x, y, game, mode);
      }
    }
    if (mines.is_a_win()) {
      std::cout << "YOU WON!" << std::endl;
      break;
    }
    ++number_of_inters;
  }
  return 0;
}