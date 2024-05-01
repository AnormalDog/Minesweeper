#pragma once

#include <iostream>
#include <cassert>
#include <string>

template <class T>
class matrix_t {
  private:
    void build (const unsigned n, const unsigned m);
    void remove ();

    unsigned row_;
    unsigned columns_;
    T** matrix_;
  public:
    matrix_t ();
    matrix_t (const unsigned n, const unsigned m);
    ~matrix_t ();

    void simple_print ();
    void read (std::istream& cin);

    unsigned get_row () {return row_;}
    unsigned get_column () {return columns_;}

    // Getter - Setter
    T& at (const unsigned n, const unsigned m);
    T& at (const unsigned n, const unsigned m) const;

    T& operator() (const unsigned n, const unsigned m);
    T& operator() (const unsigned n, const unsigned m) const;

    template<class U>
    friend std::istream& operator>> (std::istream& is, matrix_t<U>& t);
};

template<class U>
std::istream& operator>> (std::istream& is, matrix_t<U>& t) {
  t.read(is);
  return is;
}

template <class T>
void matrix_t<T>::build(const unsigned n, const unsigned m) {
  assert ((row_ > 0) && (columns_ > 0));
  T** aux = new T*[n];
  for (unsigned i = 0; i < n; ++i) {
    aux[i] = new T[m];
  }
  matrix_ = aux;
}

template <class T>
void matrix_t<T>::remove () {
  for (unsigned i = 0; i < row_; ++i) {
    delete matrix_[i];
  }
  delete matrix_;
}

template <class T>
matrix_t<T>::matrix_t () {
  row_ = 0;
  columns_= 0;
  matrix_ = nullptr;
}

template <class T>
matrix_t<T>::matrix_t (const unsigned n, const unsigned m) {
  row_ = n;
  columns_ = m;
  build (m, m);
}

template <class T>
matrix_t<T>::~matrix_t () {
  remove ();
}


template <class T>
void matrix_t<T>::simple_print () {
  for (unsigned i = 0; i < row_; ++i) {
    for (unsigned j = 0; j < columns_; ++j) {
      std::cout << matrix_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

template <class T>
void matrix_t<T>::read (std::istream& cin) {
  cin >> row_ >> columns_;
  T n;
  assert ((row_ > 0) && (columns_ > 0));
  build (row_, columns_);
  for (unsigned i = 0; i < row_; ++i) {
    for (unsigned j = 0; j < columns_; ++j) {
      cin >> n;
      at(i, j) = n;
    }
  }
}

template <class T>
T& matrix_t<T>::at (const unsigned n, const unsigned m) {
  assert ((n >= 0 && n < row_) && (m >= 0 && m < columns_));
  return (matrix_[n][m]);
}

template <class T>
T&  matrix_t<T>::at (const unsigned n, const unsigned m) const {
  assert ((n >= 0 && n < row_) && (m >= 0 && m < columns_));
  return (matrix_[n][m]);
}

template <class T>
T& matrix_t<T>::operator() (const unsigned n, const unsigned m) {
  return (at(n, m));
}

template <class T>
T& matrix_t<T>::operator() (const unsigned n, const unsigned m) const {
  return (at(n, m));
}