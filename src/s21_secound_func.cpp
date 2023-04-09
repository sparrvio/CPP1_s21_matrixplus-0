#include "s21_matrix_oop.h"

void S21Matrix::Print() {
  std::cout << this << " rows_ = " << rows_ << std::endl;
  std::cout << this << " cols_ = " << cols_ << std::endl;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::cout << this->matrix_[i][j] << " ";
    }
    std::cout << std::endl;
  }
};

void S21Matrix::FillMatrix() {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      matrix_[i][j] = i * this->cols_ + j;
    }
  }
};

void S21Matrix::FillMatrix(int n) {
  srand(n);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      matrix_[i][j] = rand() % 100;
    }
  }
};

void S21Matrix::CleanBadAlloc(S21Matrix* bad_matrix, int num) {
  try {
    for (int i = 0; i < num; i++) {
      if (bad_matrix->matrix_[i]) {
        delete[] bad_matrix->matrix_[i];
        bad_matrix->matrix_[i] = nullptr;
      }
    }
    delete[] bad_matrix->matrix_;
    bad_matrix->matrix_ = nullptr;
    bad_matrix->rows_ = bad_matrix->cols_ = 0;
    throw std::bad_alloc();
  } catch (std::bad_alloc()) {
    std::cout << "Failed to allocate memory" << std::endl;
  }
};

void S21Matrix::CleanMatrix(S21Matrix* other) {
  CheckErrMatrix(other);
  for (int i = 0; i < other->rows_; i++) {
    if (other->matrix_[i]) delete[] other->matrix_[i];
  }
  delete[] other->matrix_;
  other->rows_ = other->cols_ = 0;
};

void S21Matrix::CheckErrMatrix(const S21Matrix* other) {
  try {
    if (!other->matrix_) throw std::bad_alloc();
    if (other->rows_ < 1 || other->cols_ < 1)
      throw std::length_error("Matrix size cannot be less than 1x1");
    for (int i = 0; i < other->rows_; i++) {
      if (!other->matrix_[i]) throw std::bad_alloc();
    }
  } catch (std::bad_alloc()) {
    std::cout << "Failed to allocate memory" << std::endl;
  } catch (std::length_error()) {
  }
};

double** S21Matrix::CreateMatrix(int rows, int cols) {
  int i = 0;
  double** result_matrix = nullptr;
  try {
    if (rows < 1 || cols < 1)
      throw std::out_of_range("Matrix size cannot be less than 1x1");

    result_matrix = new double*[rows];
    for (; i < rows; i++) {
      result_matrix[i] = new double[cols];
      memset(result_matrix[i], 0, cols * sizeof(double));
    }
  } catch (std::bad_alloc& exception) {
    CleanBadAlloc(this, i);
  } catch (std::out_of_range()) {
  };
  return result_matrix;
};