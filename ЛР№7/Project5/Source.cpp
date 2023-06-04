#include <iostream>

void analyzeMatrix();
void transformMatrix();

int main()
{
    int choice;
    std::cout << "Enter 1 to analyze matrix or 2 to transform matrix: ";
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        analyzeMatrix();
        break;
    case 2:
        transformMatrix();
        break;
    default:
        std::cout << "Invalid choice." << std::endl;
        break;
    }

    return 0;
}

void analyzeMatrix()
{
    // Ввод исходных данных
    int rows, cols;
    std::cout << "Enter the number of rows: ";
    std::cin >> rows;
    std::cout << "Enter the number of columns: ";
    std::cin >> cols;

    // Создание и заполнение матрицы
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; ++i)
    {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; ++j)
        {
            std::cout << "Enter the element at position (" << i + 1 << ", " << j + 1 << "): ";
            std::cin >> matrix[i][j];
        }
    }

    // Анализ и вывод результата
    int maxSortedCol = 0;
    bool isSorted = true;

    for (int j = 0; j < cols; ++j)
    {
        bool ascending = true;
        bool descending = true;

        for (int i = 1; i < rows; ++i)
        {
            if (matrix[i][j] > matrix[i - 1][j])
            {
                descending = false;
            }

            if (matrix[i][j] < matrix[i - 1][j])
            {
                ascending = false;
            }
        }

        if (ascending || descending)
        {
            if (maxSortedCol == 0 || j < maxSortedCol)
            {
                maxSortedCol = j;
            }
        }
        else
        {
            isSorted = false;
        }
    }

    if (isSorted)
    {
        std::cout << "The maximum sorted column is: " << maxSortedCol + 1 << std::endl;
    }
    else
    {
        std::cout << "There are no sorted columns." << std::endl;
    }

    // Освобождение памяти
    for (int i = 0; i < rows; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void transformMatrix()
{
    // Ввод исходных данных
    int rows, cols;
    std::cout << "Enter the number of rows: ";
    std::cin >> rows;
    std::cout << "Enter the number of columns: ";
    std::cin >> cols;

    // Создание и заполнение матрицы
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; ++i)
    {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; ++j)
        {
            std::cout << "Enter the element at position (" << i + 1 << ", " << j + 1 << "): ";
            std::cin >> matrix[i][j];
        }
    }

    // Преобразование и вывод результата
    for (int j = 0; j < cols; ++j)
    {
        int minIndex = 0;
        int maxIndex = 0;

        for (int i = 1; i < rows; ++i)
        {
            if (matrix[i][j] < matrix[minIndex][j])
            {
                minIndex = i;
            }

            if (matrix[i][j] > matrix[maxIndex][j])
            {
                maxIndex = i;
            }
        }

        std::swap(matrix[minIndex][j], matrix[maxIndex][j]);
    }

    std::cout << "Transformed matrix:" << std::endl;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Освобождение памяти
    for (int i = 0; i < rows; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}