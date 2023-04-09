#ifndef _S21MATRIX_H_
#define _S21MATRIX_H_
#define EPS 1e-6

#include <string.h>

#include <cmath>
#include <iostream>
#include <stdexcept>

class S21Matrix {
 private:
  // attributes
  int rows_;
  int cols_;
  double **matrix_;

  // second functions
  void CleanBadAlloc(S21Matrix *matrix, int i);
  void CleanMatrix(S21Matrix *other);
  void CheckErrMatrix(const S21Matrix *other);
  double **CreateMatrix(int rows, int cols);
  void Print();
  void FillMatrix();
  void FillMatrix(int n);

 public:
  S21Matrix();                            // default constructor
  S21Matrix(int rows, int cols);          // parameterized constructor
  S21Matrix(const S21Matrix &other);      // copy constructor
  S21Matrix(S21Matrix &&other) noexcept;  // move constructor
  ~S21Matrix();                           // destructor

  // some public methods
  bool EqMatrix(
      const S21Matrix &other);  // Checks matrices for equality with each other
  void SumMatrix(
      const S21Matrix &other);  // Adds the second matrix to the current one
  void SubMatrix(
      const S21Matrix &other);  // Subtracts another matrix from the current one
  void MulNumber(
      const double num);  // Multiplies the current matrix by a number
  void MulMatrix(const S21Matrix &other);  // Multiplies the current matrix by
                                           // the second matrix
  S21Matrix Transpose();  // Creates a new transposed matrix from the current
                          // one and returns it
  int S21GetRows() noexcept;  // accessor
  int S21GetCols() noexcept;  // accessor
  void S21SetRows(int rows);  // mutator
  void S21SetCols(int cols);  // mutator
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();

  // some operators overloads
  S21Matrix &operator=(const S21Matrix &other);   // Assignment of values from
                                                  // one matrix to another one
  S21Matrix operator+(const S21Matrix &other);    // Addition of two matrices
  S21Matrix &operator+=(const S21Matrix &other);  // Addition assignment
  S21Matrix operator-(
      const S21Matrix &other);  // Subtraction of one matrix from another
  S21Matrix &operator-=(const S21Matrix &other);  // Difference assignment
  S21Matrix operator*(const double num);    // Matrix multiplication by a number
  S21Matrix &operator*=(const double num);  // Multiplication assignment
  S21Matrix operator*(const S21Matrix &other);    // Matrix multiplication
  S21Matrix &operator*=(const S21Matrix &other);  // Multiplication assignment
  double &operator()(int rows, int cols);   // Indexation by matrix elements
  bool operator==(const S21Matrix &other);  // Checks for matrices equality
};
// namespace S21Matrix

#endif
