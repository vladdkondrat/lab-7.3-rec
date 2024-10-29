#include <iostream>
#include <iomanip>
using namespace std;

// Функція для введення елементів матриці з клавіатури (рекурсивно)
void InputMatrix(int** matrix, int rows, int cols, int row = 0, int col = 0) {
    if (row == rows) return;
    if (col == cols) {
        cout << endl;
        InputMatrix(matrix, rows, cols, row + 1, 0);
    }
    else {
        cout << "matrix[" << row << "][" << col << "] = ";
        cin >> matrix[row][col];
        InputMatrix(matrix, rows, cols, row, col + 1);
    }
}

// Функція для виведення матриці (рекурсивно)
void PrintMatrix(int** matrix, int rows, int cols, int row = 0, int col = 0) {
    if (row == rows) return;
    if (col == cols) {
        cout << endl;
        PrintMatrix(matrix, rows, cols, row + 1, 0);
    }
    else {
        cout << setw(4) << matrix[row][col];
        PrintMatrix(matrix, rows, cols, row, col + 1);
    }
}

// Рекурсивна функція для циклічного зміщення рядка вправо
void ShiftRowRightRecursive(int* row, int* tempRow, int cols, int shiftCount, int col = 0) {
    if (col == cols) return;
    tempRow[(col + shiftCount) % cols] = row[col];
    ShiftRowRightRecursive(row, tempRow, cols, shiftCount, col + 1);
}

// Основна функція для рекурсивного зміщення рядка
void ShiftRowRight(int* row, int cols, int shiftCount) {
    int* tempRow = new int[cols];
    ShiftRowRightRecursive(row, tempRow, cols, shiftCount);

    // Копіюємо значення з тимчасового масиву назад у початковий рядок
    ShiftRowRightRecursive(tempRow, row, cols, 0);
    delete[] tempRow;
}

// Рекурсивна функція для циклічного зміщення стовпця вниз
void ShiftColumnDownRecursive(int** matrix, int* tempCol, int rows, int col, int shiftCount, int row = 0) {
    if (row == rows) return;
    tempCol[(row + shiftCount) % rows] = matrix[row][col];
    ShiftColumnDownRecursive(matrix, tempCol, rows, col, shiftCount, row + 1);
}

// Основна функція для рекурсивного зміщення стовпця
void ShiftColumnDown(int** matrix, int rows, int col, int shiftCount) {
    int* tempCol = new int[rows];
    ShiftColumnDownRecursive(matrix, tempCol, rows, col, shiftCount);

    // Копіюємо значення з тимчасового масиву назад у початковий стовпець
    for (int i = 0; i < rows; i++) {
        matrix[i][col] = tempCol[i];
    }
    delete[] tempCol;
}

// Основна функція для рекурсивного циклічного зміщення матриці
void ShiftMatrix(int** matrix, int rows, int cols, int shiftCount, bool shiftRight, int index = 0) {
    if (shiftRight) { // Зміщення рядків вправо
        if (index == rows) return;
        ShiftRowRight(matrix[index], cols, shiftCount);
        ShiftMatrix(matrix, rows, cols, shiftCount, shiftRight, index + 1);
    }
    else { // Зміщення стовпців вниз
        if (index == cols) return;
        ShiftColumnDown(matrix, rows, index, shiftCount);
        ShiftMatrix(matrix, rows, cols, shiftCount, shiftRight, index + 1);
    }
}

// Рекурсивна функція для підрахунку нулів у рядку
int CountZeroesInRow(int* row, int cols, int col = 0) {
    if (col == cols) return 0;
    return (row[col] == 0 ? 1 : 0) + CountZeroesInRow(row, cols, col + 1);
}

// Рекурсивна функція для знаходження першого рядка з найбільшою кількістю нулів
int FindRowWithMostZeroes(int** matrix, int rows, int cols, int row = 0, int maxZeroCount = 0, int rowIndexWithMostZeroes = -1) {
    if (row == rows) return rowIndexWithMostZeroes;
    int zeroCount = CountZeroesInRow(matrix[row], cols);
    if (zeroCount > maxZeroCount) {
        maxZeroCount = zeroCount;
        rowIndexWithMostZeroes = row;
    }
    return FindRowWithMostZeroes(matrix, rows, cols, row + 1, maxZeroCount, rowIndexWithMostZeroes);
}

// Основна функція
int main() {
    int rows, cols, shiftCount;
    bool shiftRight;

    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;

    // Динамічне створення матриці
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

    // Введення матриці
    InputMatrix(matrix, rows, cols);

    // Зміщення матриці
    cout << "Enter shift count: ";
    cin >> shiftCount;
    cout << "Enter shift direction (1 for right, 0 for down): ";
    cin >> shiftRight;
    ShiftMatrix(matrix, rows, cols, shiftCount, shiftRight);

    // Виведення зміщеної матриці
    PrintMatrix(matrix, rows, cols);

    // Знаходження рядка з найбільшою кількістю нулів
    int rowIndex = FindRowWithMostZeroes(matrix, rows, cols);
    if (rowIndex != -1) {
        cout << "First row with the most zeroes is row " << rowIndex << endl;
    }
    else {
        cout << "No zeroes found in the matrix." << endl;
    }

    // Звільнення пам'яті
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
