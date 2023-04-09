#include "s21_matrix_oop.h"

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  CheckErrMatrix(&other);
  CleanMatrix(this);
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = CreateMatrix(this->rows_, this->cols_);

  for (int i = 0; i < rows_; i++) {
    memcpy(this->matrix_[i], other.matrix_[i], other.cols_ * sizeof(double));
  }
  return *this;
};

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  CheckErrMatrix(&other);
  try {
    if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
      throw std::invalid_argument("Error in matrix sizes");
  } catch (std::invalid_argument()) {
  };

  S21Matrix res(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[i][j] = this->matrix_[i][j] + other.matrix_[i][j];
    }
  }
  return res;
};

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  CheckErrMatrix(&other);
  try {
    if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
      throw std::invalid_argument("Error in matrix sizes");
  } catch (std::invalid_argument()) {
  };

  S21Matrix res(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[i][j] = this->matrix_[i][j] - other.matrix_[i][j];
    }
  }
  return res;
};
bool S21Matrix::operator==(const S21Matrix& other) {
  CheckErrMatrix(&other);
  bool res = true;
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    res = false;
  else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        if (fabs(this->matrix_[i][j] - other.matrix_[i][j]) > EPS) {
          res = false;
          break;
        }
      }
    }
  }
  return res;
};

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  CheckErrMatrix(&other);
  try {
    if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
      throw std::invalid_argument("Error in matrix sizes");
  } catch (std::invalid_argument()) {
  };

  *this = *this + other;
  return *this;
};

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  CheckErrMatrix(&other);
  try {
    if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
      throw std::invalid_argument("Error in matrix sizes");
  } catch (std::invalid_argument()) {
  };

  *this = *this - other;
  return *this;
};

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[i][j] = matrix_[i][j] * num;
    }
  }
  return res;
};

S21Matrix& S21Matrix::operator*=(const double num) {
  *this = *this * num;
  return *this;
};

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  CheckErrMatrix(&other);
  try {
    if (this->cols_ != other.rows_)
      throw std::invalid_argument("Error in matrix sizes");
  } catch (std::invalid_argument()) {
  };

  S21Matrix tmp(this->rows_, other.cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < this->cols_; k++)
        tmp.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
    }
  }
  *this = S21Matrix(std::move(tmp));
  return *this;
};

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  CheckErrMatrix(&other);
  *this = *this * other;
  return *this;
};

double& S21Matrix::operator()(int rows, int cols) {
  try {
    if (rows >= rows_ || cols >= cols_ || rows < 0 || cols < 0)
      throw std::invalid_argument("Incorrect indexes!");
  } catch (std::invalid_argument()) {
  };
  return matrix_[rows][cols];
};