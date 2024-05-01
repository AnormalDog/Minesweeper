#pragma once

#include <iostream>

#include "matrix_t.h"


class minefield {
  private:
    matrix_t<bool> mines_;
    matrix_t<bool> visited_;
  public:
    minefield (const unsigned row, const unsigned column);
    minefield ();
    ~minefield () {};
    
    bool legal_move (const unsigned n, const unsigned m) const;

    void show_spaces (unsigned n, unsigned m);

    void simple_print () const;
    void print () const;
    friend std::istream& operator>> (std::istream& cin, minefield& mine);
};

void clean_screen () {
  system ("clear");
}

void minefield::print () const {
  clean_screen();
  for (int i = 0; i < mines_.get_row(); ++i) {
    //std::cout << i << " ";
    for (int j = 0; j < mines_.get_column(); ++j) {

      if (visited_.at(i, j) == false) {
        std::cout << "X" << " ";
      }
      else {
        std::cout << mines_.at(i, j) << " ";
      }
    }
    //std::cout << std::endl;
    //if (i == mines_.get_row() - 1) {
    //  std::cout << "  ";
    //  for (int j = 0; j < mines_.get_column(); ++j) {
    //  std::cout << j << " ";
    //}
    std::cout << std::endl;
    //}
  }
}


std::istream& operator>> (std::istream& cin, minefield& mine) {
  mine.mines_.read(cin);
  int row = mine.mines_.get_row();
  int column = mine.mines_.get_column();
  mine.visited_.resize(row, column);
  mine.visited_.fill(false);

  return cin;
}

minefield::minefield () {}

minefield::minefield (const unsigned row, const unsigned column) {
  mines_.resize (row, column);
  visited_.resize (row, column);
  visited_.fill (false);
}

void minefield::simple_print () const {
  mines_.simple_print();
}

bool minefield::legal_move (const unsigned n, const unsigned m) const {
  if ((n < 0 || n >= mines_.get_row()) || (m < 0 || m >= mines_.get_column())) {
    return false;
  }
  return true;
}

void minefield::show_spaces (unsigned n, unsigned m) {
  // Segundo caso base si la primera vez esta en bomba
  if (mines_(n, m) == true) {
    return;
  }
  visited_(n, m) = true;
  // norte
  if (legal_move(n-1, m)) {
    if (!(visited_(n-1, m)) && !(mines_(n-1, m))) {
      show_spaces (n-1, m);
    }
  }
  // sur
  if (legal_move(n+1, m)) {
    if (!(visited_(n+1, m)) && !(mines_(n+1, m))) {
      show_spaces (n+1, m);
    }
  }
  // oeste
  if (legal_move(n, m-1)) {
    if (!(visited_(n, m-1)) && !(mines_(n, m-1))) {
      show_spaces (n, m-1);
    }
  }
  // este
  if (legal_move(n, m+1)) {
    if (!(visited_(n, m+1)) && !(mines_(n, m+1))) {
      show_spaces (n, m+1);
    }
  }
  // Caso base
  else {
    return;
  }
}