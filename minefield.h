/**
 * @author AnormalDog
 * @date 1/5/2024
 * @brief main class, all the program goes around it
*/

#pragma once

#include <iostream>

#include "matrix_t.h"


class minefield {
  private:
    matrix_t<bool> mines_; // where are the mines and where not
    matrix_t<bool> visited_; // used by show_spaces, where have been landed
    matrix_t<bool> touching_; // where are the marks

    unsigned bomb_number_{0}; // number of bombs in the map

    void build (const unsigned row, const unsigned column);
  public:
    minefield () {}
    ~minefield () {};

    void queue_to_build (std::queue<int>& cola); // build from queue<int> 

    bool legal_move (const unsigned n, const unsigned m) const; // return if a cord is legal
    unsigned around_a_mine (const unsigned n, const unsigned m) const;

    unsigned get_number_of_marks () const;
    unsigned get_number_of_bombs () const {return bomb_number_;}

    void touch (const unsigned n, const unsigned m, bool& game, const unsigned mode);

    void show_spaces (unsigned n, unsigned m); // recursive method

    void print () const; // main print
    void print_sol () const; // print the solution

    bool is_a_win (); // check if win
};

/**
 * @brief return the number of marks in the map
 * @return unsigned
 * @file minefield.h
*/
unsigned minefield::get_number_of_marks () const {
  unsigned counter {0};
  for (unsigned i = 0; i < touching_.get_row(); ++i) {
    for (unsigned j = 0; j < touching_.get_column(); ++j) {
      if (touching_(i, j) == 1) {
        ++counter;
      }
    }
  }
  return counter;
}

/**
 * @brief build and put every member of a queue in the mines_
 * @return
 * @file minefield.h
*/
void minefield::queue_to_build (std::queue<int>& cola) {
  int row = cola.front(); // extract the number of rows
  cola.pop();
  int column = cola.front(); // extract the number of columns
  cola.pop();
  build (row, column);
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < column; ++j) {
      int aux = cola.front();
      cola.pop();
      if (aux == 0) { // int 0 = false
        mines_(i, j) = false;
      } 
      else if (aux == 1) { // int 1 = true
        mines_(i, j) = true;
        ++bomb_number_;
      } 
      else { // if no 1 or 0, put 0 and continue
        std::cerr << "unusual int found in queue, using 0 instead" << std::endl;
        mines_(i, j) = false;
      }
    }
  }
}

/**
 * @brief build the basics, sizes and fills
 * @return
 * @file minefield.h
*/
void minefield::build(const unsigned row, const unsigned column) {
  // resize all matrix so same size
  mines_.resize(row, column); 
  visited_.resize(row, column); 
  touching_.resize(row, column);
  // fill visited and touching with 0
  visited_.fill(false); 
  touching_.fill(false);
}

/**
 * @brief print the mines_ matrix
 * @return 
 * @file minefield.h
*/
void minefield::print_sol () const {
  for (unsigned i = 0; i < mines_.get_row(); ++i) {
    for (unsigned j = 0; j < mines_.get_column(); ++j) {
      std::cout << mines_(i, j) << " ";
    }
    std::cout << std::endl;
  }
}

/**
 * @brief Check if a cordinate is inside the matrix
 * @return bool
 * @file minefield.h
*/
bool minefield::legal_move (const unsigned n, const unsigned m) const {
  if ((n < 0 || n >= mines_.get_row()) || (m < 0 || m >= mines_.get_column())) {
    return false;
  }
  return true;
}

/**
 * @brief recursive method, if found a empty square, then clear around
 * @return
 * @file minefield.h
*/
void minefield::show_spaces (unsigned n, unsigned m) {
  visited_(n, m) = true; // mark square as visited
  if (mines_(n, m) == true) { // Case if show_spaces is used over a bomb
    return;
  }
  // north
  if (legal_move(n-1, m)) {
    if (!(visited_(n-1, m)) && !(mines_(n-1, m))) {
      show_spaces (n-1, m);
    }
  }
  // south
  if (legal_move(n+1, m)) {
    if (!(visited_(n+1, m)) && !(mines_(n+1, m))) {
      show_spaces (n+1, m);
    }
  }
  // west
  if (legal_move(n, m-1)) {
    if (!(visited_(n, m-1)) && !(mines_(n, m-1))) {
      show_spaces (n, m-1);
    }
  }
  // east
  if (legal_move(n, m+1)) {
    if (!(visited_(n, m+1)) && !(mines_(n, m+1))) {
      show_spaces (n, m+1);
    }
  }
  // base
  else {
    return;
  }
}

/**
 * @brief check around a square how many bombs there are
 * @return unsigned
 * @file minefield.h
*/
unsigned minefield::around_a_mine (const unsigned n, const unsigned m) const {
  unsigned counter {0};
  // north
  if (legal_move(n-1, m) && mines_(n-1, m)) {
    ++counter;
  }
  // northeast
  if (legal_move(n-1, m-1) && mines_(n-1, m-1)) {
    ++counter;
  }
  // south
  if (legal_move(n+1, m) && mines_(n+1, m)) {
    ++counter;
  }
  // southeast
  if (legal_move(n+1, m+1) && mines_(n+1, m+1)) {
    ++counter;
  }
  // east
  if (legal_move(n, m+1) && mines_(n, m+1)) {
    ++counter;
  }
  // west
  if (legal_move(n, m-1) && mines_(n, m-1)) {
    ++counter;
  }
  // southwest
  if (legal_move(n+1, m-1) && mines_(n+1, m-1)) {
    ++counter;
  }
  // northeast
  if (legal_move(n-1, m+1) && mines_(n-1, m+1)) {
    ++counter;
  }
  return counter;
}

/**
 * @brief depending the mode, do different things. main method called by main
 * mode = 0: try touch
 * mode = 1: put a mark
 * mode = 2: remove a mark, if exist
 * game is passed as argument if touch a bomb put game on false\
 * @return
 * @file minefield.h
*/
void minefield::touch (const unsigned n, const unsigned m, bool& game, const unsigned mode) {
  if (!legal_move(n, m)) {
    std::cout << "invalid move!" << std::endl;
    return;
  }
  if (mode == 0) {
    if (mines_(n, m)) {
      std::cout << "you touched a mine!" << std::endl;
      game = false;
    }
    else {
      show_spaces (m, m);
    }
  }
  else if (mode == 1) {
    touching_(n, m) = true;
  }
  else {
    touching_(n, m) = false;
  }

  
}

/**
 * @brief main print
 * @return none
 * @file minefield.h
*/
void minefield::print () const {
  for (unsigned i = 0; i < mines_.get_row(); ++i) {
    std::cout << i << " | ";
    for (unsigned j = 0; j < mines_.get_column(); ++j) {
      if (!visited_(i, j) && !touching_(i, j)) {
        std::cout << 'X' << " ";
      }
      else if (touching_(i, j)) {
        std::cout << 'B' << " ";
      }
      else {
        std::cout << around_a_mine(i, j) << " ";
      }
    }
    std::cout << std::endl;
  }
  std::cout << "    ";
  for (unsigned i = 0; i < mines_.get_column(); ++i) {
    std::cout << "─ ";
  }
  std::cout << std::endl << "    ";
  for (unsigned i = 0; i < mines_.get_column(); ++i) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

/**
 * @brief count the number of marks in correct places, the if coincide with the number of bombs
 * return true
 * @return bool
 * @file minefield.h
*/
bool minefield::is_a_win () {
  unsigned good_marks {0};
  for (unsigned i = 0; i < mines_.get_row(); ++i) {
    for (unsigned j = 0; j < mines_.get_column(); ++j) {
      if (mines_(i, j) && touching_(i, j)) {
        ++good_marks;
      }
    }
  }
  if (good_marks == bomb_number_) {
    return true;
  }
  else {
    return false;
  }
}