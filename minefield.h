#pragma once

#include <iostream>

#include "matrix_t.h"


class minefield {
  private:
    matrix_t<bool> mines_;
    matrix_t<bool> visited_;

    void build (const unsigned row, const unsigned column);
  public:
    minefield (const unsigned row, const unsigned column);
    minefield () {}
    ~minefield () {};

    void queue_to_build (std::queue<int>& cola);

    bool legal_move (const unsigned n, const unsigned m) const;
    unsigned around_a_mine (const unsigned n, const unsigned m) const;


    void touch (const unsigned n, const unsigned m, bool& game);

    void show_spaces (unsigned n, unsigned m);

    void super_print () const;
    void simple_print () const;
    void print () const;
};

void minefield::queue_to_build (std::queue<int>& cola) {
  int row = cola.front();
  cola.pop();
  int column = cola.front();
  cola.pop();
  build (row, column);
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < column; ++j) {
      int aux = cola.front();
      cola.pop();
      if (aux == 0) {
        mines_(i, j) = false;
      }
      else if (aux == 1) {
        mines_(i, j) = true;
      } 
      else {
        std::cout << "unusual int found in queue, using 0 instead" << std::endl;
        mines_(i, j) = false;
      }
    }
  }
}



void minefield::build(const unsigned row, const unsigned column) {
  mines_.resize(row, column);
  visited_.resize(row, column);
  visited_.fill(false);
}

void minefield::print () const {
  for (int i = 0; i < mines_.get_row(); ++i) {
    for (int j = 0; j < mines_.get_column(); ++j) {

      if (visited_.at(i, j) == false) {
        std::cout << "X" << " ";
      }
      else {
        std::cout << mines_.at(i, j) << " ";
      }
    }
    std::cout << std::endl;
  }
}

minefield::minefield (const unsigned row, const unsigned column) {
  build (row, column);
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
  visited_(n, m) = true;
  if (mines_(n, m) == true) {
    return;
  }
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

unsigned minefield::around_a_mine (const unsigned n, const unsigned m) const {
  unsigned counter = 0;
  // norte
  if (legal_move(n-1, m) && mines_(n-1, m)) {
    //std::cout << "entro norte" << std::endl;
    ++counter;
  }
  // noroeste
  if (legal_move(n-1, m-1) && mines_(n-1, m-1)) {
    //std::cout << "entro noroeste" << std::endl;
    ++counter;
  }
  // sur
  if (legal_move(n+1, m) && mines_(n+1, m)) {
    //std::cout << "entro sur" << std::endl;
    ++counter;
  }
  // sureste
  if (legal_move(n+1, m+1) && mines_(n+1, m+1)) {
    //std::cout << "entro sureste" << std::endl;
    ++counter;
  }
  // este
  if (legal_move(n, m+1) && mines_(n, m+1)) {
    //std::cout << "entro este" << std::endl;
    ++counter;
  }
  // oeste
  if (legal_move(n, m-1) && mines_(n, m-1)) {
    //std::cout << "entro oeste" << std::endl;
    ++counter;
  }
  //suroeste
  if (legal_move(n+1, m-1) && mines_(n+1, m-1)) {
    //std::cout << "entro suroeste" << std::endl;
    ++counter;
  }
  //noreste
  if (legal_move(n-1, m+1) && mines_(n-1, m+1)) {
    //std::cout << "entro noreste" << std::endl;
    ++counter;
  }
  return counter;
}

void minefield::touch (const unsigned n, const unsigned m, bool& game) {
  if (!legal_move(n, m)) {
    std::cout << "invalid move!" << std::endl;
    return;
  }
  if (mines_(n, m)) {
    std::cout << "you touched a mine!" << std::endl;
    game = false;
  }
  else {
    show_spaces (m, m);
  }
  
}

void minefield::super_print () const {
  for (unsigned i = 0; i < mines_.get_row(); ++i) {
    std::cout << i << " | ";
    for (unsigned j = 0; j < mines_.get_column(); ++j) {
      if (!visited_(i, j)) {
        std::cout << 'X' << " ";
      }
      else {
        std::cout << around_a_mine(i, j) << " ";
      }
    }
    std::cout << std::endl;
  }
  std::cout << "     ";
  for (unsigned i = 0; i < mines_.get_column(); ++i) {
    std::cout << "─ ";
  }
  std::cout << std::endl << "    ";
  for (unsigned i = 0; i < mines_.get_column(); ++i) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}