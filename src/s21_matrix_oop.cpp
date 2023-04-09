#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(2), cols_(3) {
  matrix_ = CreateMatrix(rows_, cols_);
};

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  matrix_ = CreateMatrix(rows_, cols_);
};

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = CreateMatrix(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    memcpy(this->matrix_[i], other.matrix_[i], other.cols_ * sizeof(double));
  }
};

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

int S21Matrix::S21GetRows() noexcept { return rows_; };

int S21Matrix::S21GetCols() noexcept { return cols_; };

S21Matrix::~S21Matrix() {
  rows_ = cols_ = 0;
  for (int i = 0; i < rows_; i++) {
    if (matrix_[i]) {
      delete[] matrix_[i];
      matrix_[i] = nullptr;
    }
  }
  if (matrix_) {
    delete[] matrix_;
    matrix_ = nullptr;
  }
};

void S21Matrix::S21SetRows(int rows) {
  if (rows == this->rows_) {
  } else {
    S21Matrix res(rows, this->cols_);
    int tmp = rows < this->rows_ ? rows : this->rows_;

    for (int i = 0; i < tmp; i++) {
      memcpy(res.matrix_[i], this->matrix_[i], this->cols_ * sizeof(double));
    }
    *this = res;
  }
}

void S21Matrix::S21SetCols(int cols) {
  if (cols == this->cols_) {
  } else {
    S21Matrix res(this->rows_, cols);
    int tmp = cols < this->cols_ ? cols : this->cols_;

    for (int i = 0; i < this->rows_; i++) {
      memcpy(res.matrix_[i], this->matrix_[i], tmp * sizeof(double));
    }
    *this = res;
  }
}

// int main() {
//   S21Matrix a(2, 2);
//   a.FillMatrix();
//   a.Print();
//   int res = a.Determinant();
//   std::cout << res << std::endl;
//   S21Matrix b = a.CalcComplements();
//   b.Print();
//
//   S21Matrix c = a.InverseMatrix();
//   c.Print();
//   return 0;
// }