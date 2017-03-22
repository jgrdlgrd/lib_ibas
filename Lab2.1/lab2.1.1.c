//
// Created by Павел on 13.02.2017.
//

#include "lib_ibas/v1.9/base.h"
#include "lib_ibas/v1.9/matrix/i-matrix.h"

int doTask();
IMatrix_t inputMatrix();
IMatrix_t computeSaddlePoints(IMatrix_t *matrix);
void printWithSaddlePoints(IMatrix_t *matrix, IMatrix_t *saddles);

int main() {
  Console.setRusLocale();
  Scanner.stream = stdin;

  printf("Вас приветствует программа для поиска седловых точек в матрице\n"
             "(седловой точкой называется элемент, являющийся минимумом в своём столбце и максимумом в своей строке).\n"
             "Автор: Павел Андреев\n\n");
  Console.repeat(doTask, "Вы желаете найти седловые точки для другой матрицы? (Y/N): ");
  Console.newLine();

  Console.coloured(Colors.GREEN, "Goodbye :)");
  Console.pause();
  return 0;
}

int doTask() {
  static bool firstRun = true;
  if (!firstRun) Console.clearScreen();
  firstRun = false;

  IMatrix_t matrix = inputMatrix();
  Console.newLine();
  Console.newLine();

  IMatrix_t saddles = computeSaddlePoints(&matrix);
  printWithSaddlePoints(&matrix, &saddles);
  Console.newLine();

  IMatrix.destroy(&matrix);
  IMatrix.destroy(&saddles);
  return 0;
}

IMatrix_t inputMatrix() {
  String err = "Ошибка! Пожалуйста, введите натуральное число!\n";
  int rows = Console.inputIntFromInterval("Введите количество строк в матрице: ", err, 1, INT_MAX);
  int cols = Console.inputIntFromInterval("Введите количество столбцов в матрице: ", err, 1, INT_MAX);
  Console.newLine();

  IMatrix_t matrix = IMatrix.create(rows, cols);
  IMatrix.input(&matrix, "Пожалуйста, введите матрицу из %d строк и %d столбцов:");

  return matrix;
}

IMatrix_t computeSaddlePoints(IMatrix_t *matrix) {
  IMatrix_t saddles = IMatrix.create(matrix->rows, matrix->cols), *s = &saddles;
  IMatrix_t colMins = IMatrix.create(matrix->cols, 1), *cm = &colMins;
  IMatrix_t rowMaxs = IMatrix.create(matrix->rows, 1), *rm = &rowMaxs;

  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->cols; j++) {
      int current = IMatrix.get(matrix, i, j);

      //initial column minimum
      if (i == 0) {
        IMatrix.set(cm, j, 0, current);
      }

      //initial row maximum
      if (j == 0) {
        IMatrix.set(rm, i, 0, current);
      }

      //current element > row maximum
      if (current > IMatrix.get(rm, i, 0)) {
        IMatrix.set(rm, i, 0, current);
      }

      //current element < column minimum
      if (current < IMatrix.get(cm, j, 0)) {
        IMatrix.set(cm, j, 0, current);
      }
    }
  }

  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->cols; j++) {
      bool isSaddle = IMatrix.get(rm, i, 0) == IMatrix.get(cm, j, 0);
      IMatrix.set(s, i, j, isSaddle);
    }
  }

  IMatrix.destroy(rm);
  IMatrix.destroy(cm);
  return saddles;
}

void printWithSaddlePoints(IMatrix_t *matrix, IMatrix_t *saddles) {
  printf("Седловые точки в матрице выделены цветом:\n");

  for (int i = 0; i < matrix->rows; i++) {
    putchar('|');
    for (int j = 0; j < matrix->cols; j++) {
      int current = IMatrix.get(matrix, i, j);
      bool isSaddle = (bool) IMatrix.get(saddles, i, j);

      if (isSaddle) {
        Console.coloured(Colors.RED, "%8d", current);
        printf(" | ");
      } else {
        printf("%8d | ", current);
      }
    }
    Console.newLine();
  }
}
