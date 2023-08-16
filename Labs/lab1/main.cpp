// Nicholas Tran
// Lab 1
// Recursion

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

bool findTarget(int **matrix, int row, int col, int target, int count, int maxRows, int maxCols, bool **seen)
{
    if (row < 0 || row >= maxRows || col < 0 || col >= maxCols || seen[row][col])
    {
        return false;
    }

    count += matrix[row][col];

    if (count == target)
    {
        return true;
    }

    seen[row][col] = true;

    if (findTarget(matrix, row + 1, col, target, count, maxRows, maxCols, seen) 
    || findTarget(matrix, row - 1, col, target, count, maxRows, maxCols, seen) 
    || findTarget(matrix, row, col + 1, target, count, maxRows, maxCols, seen) 
    || findTarget(matrix, row, col - 1, target, count, maxRows, maxCols, seen))
    {
        return true;
    }
    seen[row][col] = false;

    return false;
}

bool searchZero(int rows, int cols, int **matrix, int target) // SEARCHS FOR A ZERO IF IT FINDS ZERO, CALLS THE FINDTARGET FUNCTION, IF NOT RETURNS FALSE
{
    bool **seen = new bool *[rows];
    for (int i = 0; i < rows; i++)
    {
        seen[i] = new bool[cols];
        for (int j = 0; j < cols; j++)
        {
            seen[i][j] = false;
        }
    }

    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            if (matrix[x][y] == 0 && findTarget(matrix, x, y, target, 0, rows, cols, seen))
            {
                for (int i = 0; i < rows; i++)
                {
                    delete[] seen[i];
                }
                delete[] seen;
                return true;
            }
        }
    }

    for (int i = 0; i < rows; i++)
    {
        delete[] seen[i];
    }
    delete[] seen;
    return false;
}

int main(int argc, char *argv[])
{

    ArgumentManager am(argc, argv);
    ifstream inputFile(am.get("input"));
    ofstream outputFile(am.get("output"));


    // CHECK IF FILE IS OPEN
    if (!inputFile.is_open())
    {
        cout << "Error - Unable to Open Input File." << endl;
        outputFile << "Not Possible" << endl;
        outputFile.close();
        return 0;
    }
    // CHECK IF FILE IS EMPTY
    if (inputFile.peek() == EOF)
    {
        cout << "Error - Input File is Empty" << endl;
        outputFile << "Not Possible" << endl;
        inputFile.close();
        outputFile.close();
        return 0;
    }

    // EXTRACT # OF COLUMNS AND ROWS FROM FIRST LINE
    int rows, cols;

    inputFile >> rows;
    inputFile >> cols;

    // creates dynamic 2D array
    int **matrix = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new int[cols];
    }

    // EXTRACT MATRIX FROM FILE
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            inputFile >> matrix[r][c];
        }
    }

    // EXTRACT TARGET VALUE
    int target;
    inputFile >> target;

    // ALGORITHM
    if (searchZero(rows, cols, (int **)matrix, target) == false)
    {
        outputFile << "Not Possible" << endl;
    }
    else
    {
        outputFile << "Possible" << endl;
    }

    for (int i = 0; i < rows; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    inputFile.close();
    outputFile.close();

    return 0;
}

