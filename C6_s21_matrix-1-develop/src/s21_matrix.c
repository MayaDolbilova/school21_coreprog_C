#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = INCORRECT_MATRIX;
  if (rows > 0 && columns > 0 && result) {
    result->rows = rows;
    result->columns = columns;
    if ((result->matrix = (double **)calloc(
             rows * columns * sizeof(double) + rows * sizeof(double *), 1)) !=
        NULL) {
      double *ptr = (double *)(result->matrix + rows);
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = ptr + columns * i;
      }
      error = OK;
    }
  }
  return error;
}

void s21_remove_matrix(matrix_t *A) {
  if (A) {
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (A->columns == B->columns && A->rows == B->rows && correct_matrix(A) &&
      correct_matrix(B)) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= 1e-7) {
          res = FAILURE;
          break;
        }
      }
    }
  } else {
    res = FAILURE;
  }
  return res;
}

int correct_matrix(matrix_t *A) {
  int res = FAILURE;
  if (A != NULL && A->matrix != NULL && A->rows >= 1 && A->columns >= 1) {
    res = SUCCESS;
  } else {
    res = FAILURE;
  }
  return res;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (correct_matrix(A) && correct_matrix(B) && result) {
    if (A->rows == B->rows && A->columns == B->columns) {
      int res = s21_create_matrix(A->rows, A->columns, result);
      if (res == 0) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }
      }
    } else {
      error = CALCULATION_ERROR;
    }
  } else {
    error = INCORRECT_MATRIX;
  }
  return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (correct_matrix(A) && correct_matrix(B) && result) {
    if (A->rows == B->rows && A->columns == B->columns) {
      int error = s21_create_matrix(A->rows, A->columns, result);
      if (error == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }
      }
    } else {
      error = CALCULATION_ERROR;
    }
  } else {
    error = INCORRECT_MATRIX;
  }
  return error;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = OK;
  if (correct_matrix(A)) {
    int error = s21_create_matrix(A->rows, A->columns, result);
    if (error == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  } else {
    error = INCORRECT_MATRIX;
  }
  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (correct_matrix(A) && correct_matrix(B)) {
    if (A->columns == B->rows) {
      error = s21_create_matrix(A->rows, B->columns, result);
      if (error == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < B->columns; j++) {
            for (int k = 0; k < B->rows; k++) {
              result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
          }
        }
      }
    } else {
      error = CALCULATION_ERROR;
    }
  } else {
    error = INCORRECT_MATRIX;
  }
  return error;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = OK;
  if (correct_matrix(A)) {
    int error = s21_create_matrix(A->columns, A->rows, result);
    if (error == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  } else {
    error = INCORRECT_MATRIX;
  }
  return error;
}

int s21_determinant(matrix_t *A, double *result) {
  int error = OK;
  int sign = 1;
  if (correct_matrix(A)) {
    if (A->columns == A->rows && A->columns == 1) {
      *result = A->matrix[0][0];
    } else if (A->columns == A->rows && A->columns == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else if (A->columns == A->rows && A->columns >= 3) {
      double lasting_result = 0;
      for (int i = 0; i < A->columns; i++) {
        matrix_t crop_matrix;
        minor_find(0, i, A, &crop_matrix);
        s21_determinant(&crop_matrix, result);
        lasting_result += *result * A->matrix[0][i] * sign;
        sign *= -1;
        s21_remove_matrix(&crop_matrix);
      }
      *result = lasting_result;
    } else {
      error = CALCULATION_ERROR;
    }
  } else {
    error = INCORRECT_MATRIX;
  }
  return error;
}

void minor_find(int col, int row, matrix_t *A, matrix_t *result) {
  int new_row = 0;
  int new_col = 0;

  s21_create_matrix(A->rows - 1, A->columns - 1, result);
  for (int i = 0; i < A->rows; i++) {
    new_col = 0;
    if (i == col) {
      continue;
    }
    for (int j = 0; j < A->columns; j++) {
      if (j == row) {
        continue;
      }
      result->matrix[new_row][new_col++] = A->matrix[i][j];
    }
    new_row++;
  }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = OK;
  if (correct_matrix(A)) {
    if (A->rows == A->columns) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          matrix_t minor_matrix;
          minor_find(i, j, A, &minor_matrix);
          double determinant;
          error = s21_determinant(&minor_matrix, &determinant);
          if ((i + j) % 2 == 1) {
            determinant *= -1;
          }
          result->matrix[i][j] = determinant;
          s21_remove_matrix(&minor_matrix);
        }
      }
    } else {
      error = CALCULATION_ERROR;
    }
  } else {
    error = INCORRECT_MATRIX;
  }
  return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = OK;
  double det = 0.0;
  if (!correct_matrix(A)) error = INCORRECT_MATRIX;

  if (A->rows != A->columns && error == OK) error = CALCULATION_ERROR;

  if (error == OK && A->rows > 1 && A->columns > 1) {
    error = s21_determinant(A, &det);
    if (det == 0) {
      error = CALCULATION_ERROR;
    } else {
      det = 1 / det;
      matrix_t comatrix;
      matrix_t transposed_comatrix;
      error = s21_calc_complements(A, &comatrix);
      error = s21_transpose(&comatrix, &transposed_comatrix);
      if (error == OK) {
        s21_mult_number(&transposed_comatrix, det, result);
      }
      s21_remove_matrix(&comatrix);
      s21_remove_matrix(&transposed_comatrix);
    }
  }
  if (A->rows == 1 && A->columns == 1 && error == OK) {
    error = s21_create_matrix(1, 1, result);
    if (error == OK) {
      result->matrix[0][0] = 1 / (A->matrix[0][0]);
    }
  }
  return error;
}
