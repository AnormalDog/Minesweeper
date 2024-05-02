/**
 * @brief matrix<T> class, done by fun and practice
*/

#pragma once

#include <iostream>
#include <cassert>
#include <string>

template <class T>
class matrix_t {
  private:
    unsigned row_; // number of rows
    unsigned columns_; // number of columns
    
    T** matrix_ {nullptr}; // pointer to array of arrays

    void remove ();
  public:
    // constructor and destructor
    matrix_t ();
    matrix_t (const unsigned n, const unsigned m);
    ~matrix_t ();

    // print the matrix
    void print () const;

    // remove and resize the matrix
    void resize (const unsigned n, const unsigned m);
    // fill all the matrix with same element
    void fill (const T& tipe);

    // size getters
    unsigned get_row () {return row_;}
    unsigned get_column () {return columns_;}
    unsigned get_row () const {return row_;}
    unsigned get_column () const {return columns_;}

    // Getter - Setter
    T& at (const unsigned n, const unsigned m);
    T& at (const unsigned n, const unsigned m) const;

    // operator overloading
    T& operator() (const unsigned n, const unsigned m);
    T& operator() (const unsigned n, const unsigned m) const;

};

/**
 * @brief free all elements from memory
 * @return
 * @file matrix_t.h
*/
template <class T>
void matrix_t<T>::remove () {
  for (unsigned i = 0; i < row_; ++i) {
    delete matrix_[i];
  }
  delete matrix_;
  matrix_ = nullptr;
}

/**
 * @brief simple constructor
 * @file matrix_t.h
*/
template <class T>
matrix_t<T>::matrix_t () {
  row_ = 0;
  columns_= 0;
  matrix_ = nullptr;
}

/**
 * @brief parametrized constructor
 * @file matrix_t.h
*/
template <class T>
matrix_t<T>::matrix_t (const unsigned n, const unsigned m) {
  resize (m, m);
}

/**
 * @brief class destructor
 * @file matrix_t.h
*/
template <class T>
matrix_t<T>::~matrix_t () {
  remove ();
}

/**
 * @brief print the matrix
 * @return
 * @file matrix_t.h
*/
template <class T>
void matrix_t<T>::print () const {
  for (unsigned i = 0; i < row_; ++i) {
    for (unsigned j = 0; j < columns_; ++j) {
      std::cout << matrix_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

/**
 * @brief setter-getter, constants and not constants
 * @return &T
 * @file matrix_t.h
*/
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


/**
 * @brief clean and resize the matrix
 * @return
 * @file matrix_t.h
*/
template <class T>
void matrix_t<T>::resize (const unsigned n, const unsigned m) {
  assert (n > 0 && m > 0);
  T** new_data = new T*[n];
  for (unsigned i = 0; i < n; ++i) {
    new_data[i] = new T[m];
  }
  if (matrix_ != nullptr) {
    remove();
  }
  row_ = n;
  columns_ = m;
  matrix_ = new_data;
}

/**
 * @brief fill all the matrix with the same element
 * @return
 * @file matrix_t.h
*/
template <class T>
void matrix_t<T>::fill (const T& dato) {
  for (unsigned i = 0; i < row_; ++i) {
    for (unsigned j = 0; j < columns_; ++j) {
      at(i, j) = dato;
    }
  }
}