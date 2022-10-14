// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_matrix.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (20.04.2015)
//
// Тестирование верхнетреугольной матрицы

#include <iostream>
#include "utmatrix.h"
//---------------------------------------------------------------------------

void showExample();
void generateMatrix();

void main()
{
  unsigned int value;
  int size,value_1,value_2;

  setlocale(LC_ALL, "Russian");
  std::cout << "-> Enter 1 to print standart matrix example\n-> Enter 2 to work with ur own matrix\n= Ur choice:\t";
  std::cin >> value;
  switch (value) {
  case 1:
      showExample();
      break;
  case 2:
      generateMatrix();
      break;
  default:
      std::cout << "-> Incorrect value...\n";
      break;
  }
  system("pause");
}

void showExample() {
    TMatrix<int> a(5), b(5), c(5);
    cout << "Тестирование программ поддержки представления треугольных матриц"
        << endl;
    for (int i = 0; i < 5; i++)
        for (int j = i; j < 5; j++)
        {
            a[i][j] = i * 10 + j;
            b[i][j] = (i * 10 + j) * 100;
        }
   // c = a + b;
    cout << "Matrix a = " << endl << a << endl;
    cout << "Matrix b = " << endl << b << endl;
    cout << "Matrix c = a + b" << endl << a + b << endl;
    cout << "Matrix c = a - b" << endl << a - b << endl;
    cout << "Matrix c = b - a" << endl << b - a << endl;
}

void generateMatrix() {
    unsigned int value, operation;
    int size, value_1, value_2;
    std::cout << "-> Enter matrix size:\t";
    std::cin >> size;
    TMatrix<int> matrix_1(size), matrix_2(size), matrix_result(size);
    std::cout << "-> Enter first matrix values\n";
    for (int i = 0; i < size; i++)
        for (int j = i; j < size; j++) {
            std::cout << "a[ " << i + 1 << " ][ " << j + 1 << " ] = ";
            std::cin >> value_1;
            matrix_1[i][j] = value_1;
        }
    std::cout << "-> Ur matrix:\n";
    std::cout << matrix_1;
    std::cout << "\n\n";

    std::cout << "-> Enter second matrix values\n";
    for (int i = 0; i < size; i++)
        for (int j = i; j < size; j++) {
            std::cout << "a[ " << i + 1 << " ][ " << j + 1 << " ] = ";
            std::cin >> value_2;
            matrix_2[i][j] = value_2;
        }
    std::cout << "-> Ur matrix:\n";
    std::cout << matrix_2;
    std::cout << "\n\n";

    std::cout << "-> Please enter 1-3 to continue working with matrix\n";
    std::cout << "   1 - sum\n";
    std::cout << "   2 - substract\n";
    std::cout << "   3 - assign first matrix to second\n";
    std::cout << "   4 - assign second matrix to first\n";
    std::cout << "-> Ur choice:\t";
    std::cin >> operation;
    switch (operation) {
    case 1:
        std::cout << "\n" << "Matrix_1 + Matrix_2 = " << matrix_1 + matrix_2;
        break;
    case 2:
        std::cout << "\n" << "Matrix_1 - Matrix_2 = " << matrix_1 - matrix_2;
        break;
    case 3:
        matrix_1 = matrix_2;
        std::cout << "\n" << matrix_1;
        break;
    case 4:
        matrix_2 = matrix_1;
        std::cout << "\n" << matrix_2;
        break;
    default:
        std::cout << "-> Incorrect value...\n";
        break;
    }

}
//---------------------------------------------------------------------------
