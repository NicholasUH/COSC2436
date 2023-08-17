#include "ArgumentManager.h"
#include "Queue.h"
#include "Stack.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void createMatrix(vector<vector<char>> &matrix, size_t row, size_t col, ifstream &inputFile)
{
    for (int x = 0; x < row; x++)
    {
        vector<char> tempRow;
        for (int y = 0; y < col; y++)
        {
            char element;
            inputFile >> element;
            tempRow.push_back(element);
        }
        matrix.push_back(tempRow);
    }
}

bool moveMatrixUp(vector<vector<char>> &matrix, size_t row, size_t col)
{
    Stack elementStack;
    int O_Counter = 0;
    vector<vector<char>> oldMatrix = matrix;

    for (int y = 0; y < col; y++)
    {
        for (int x = 0; x < row; x++)
        {
            if (matrix[x][y] == 'X')
            {
                while (elementStack.getSize() < O_Counter)
                {
                    elementStack.push('O');
                }
                elementStack.push('X');
            }
            else if (matrix[x][y] == 'B')
            {
                if (!elementStack.isEmpty() && elementStack.peek() == 'B')
                {
                    elementStack.pop();
                    elementStack.push('X');
                }
                else
                {
                    elementStack.push(matrix[x][y]);
                }
            }
            O_Counter++;
        }

        while (elementStack.getSize() < O_Counter)
        {
            elementStack.push('O');
        }

        for (int x = row - 1; x >= 0; x--)
        {
            matrix[x][y] = elementStack.pop();
        }

        O_Counter = 0;
    }

    return matrix != oldMatrix;
}

bool moveMatrixRight(vector<vector<char>> &matrix, size_t row, size_t col)
{
    Stack elementStack;
    int O_Counter = 0;
    vector<vector<char>> oldMatrix = matrix;

    for (int y = 0; y < row; y++)
    {
        for (int x = col - 1; x >= 0; x--)
        {
            if (matrix[y][x] == 'X')
            {
                while (elementStack.getSize() < O_Counter)
                {
                    elementStack.push('O');
                }
                elementStack.push('X');
            }
            else if (matrix[y][x] == 'B')
            {
                if (!elementStack.isEmpty() && elementStack.peek() == 'B')
                {
                    elementStack.pop();
                    elementStack.push('X');
                }
                else
                {
                    elementStack.push(matrix[y][x]);
                }
            }

            O_Counter++;
        }

        while (elementStack.getSize() < O_Counter)
        {
            elementStack.push('O');
        }

        for (int x = 0; x < col; x++)
        {
            matrix[y][x] = elementStack.pop();
        }

        O_Counter = 0;
    }

    return matrix != oldMatrix;
}

bool moveMatrixDown(vector<vector<char>> &matrix, size_t row, size_t col)
{
    Stack elementStack;
    int O_Counter = 0;
    vector<vector<char>> oldMatrix = matrix;

    for (int y = 0; y < col; y++)
    {
        for (int x = row - 1; x >= 0; x--)
        {
            if (matrix[x][y] == 'X')
            {
                while (elementStack.getSize() < O_Counter)
                {
                    elementStack.push('O');
                }
                elementStack.push('X');
            }
            else if (matrix[x][y] == 'B')
            {
                if (!elementStack.isEmpty() && elementStack.peek() == 'B')
                {
                    elementStack.pop();
                    elementStack.push('X');
                }
                else
                {
                    elementStack.push(matrix[x][y]);
                }
            }

            O_Counter++;
        }

        while (elementStack.getSize() < O_Counter)
        {
            elementStack.push('O');
        }

        for (int x = 0; x < row; x++)
        {
            matrix[x][y] = elementStack.pop();
        }

        O_Counter = 0;
    }
    return matrix != oldMatrix;
}

bool moveMatrixLeft(vector<vector<char>> &matrix, size_t row, size_t col)
{
    Stack elementStack;
    int O_Counter = 0;
    vector<vector<char>> oldMatrix = matrix;

    for (int y = 0; y < row; y++)
    {
        for (int x = 0; x < col; x++)
        {

            if (matrix[y][x] == 'X')
            {
                while (elementStack.getSize() < O_Counter)
                {
                    elementStack.push('O');
                }
                elementStack.push('X');
            }
            else if (matrix[y][x] == 'B')
            {
                if (!elementStack.isEmpty() && elementStack.peek() == 'B')
                {
                    elementStack.pop();
                    elementStack.push('X');
                }
                else
                {
                    elementStack.push(matrix[y][x]);
                }
            }
            O_Counter++;
        }

        while (elementStack.getSize() < O_Counter)
        {
            elementStack.push('O');
        }

        for (int x = col - 1; x >= 0; x--)
        {
            matrix[y][x] = elementStack.pop();
        }

        O_Counter = 0;
    }
    return matrix != oldMatrix;
}

bool isMatrixSolved(vector<vector<char>> matrix, size_t row, size_t col)
{
    for (int x = 0; x < row; x++)
    {
        for (int y = 0; y < col; y++)
        {
            if (matrix[x][y] == 'B')
            {
                return false;
            }
        }
    }
    return true;
}

void addPath(Queue &q, Pair p, string move, size_t row, size_t col)
{
    Pair newPair = p;

    if (move == "UP" && moveMatrixUp(newPair.matrix, row, col))
    {
        newPair.moves += "1";
        q.enqueue(newPair);
    }
    else if (move == "RIGHT" && moveMatrixRight(newPair.matrix, row, col))
    {
        newPair.moves += "2";
        q.enqueue(newPair);
    }
    else if (move == "DOWN" && moveMatrixDown(newPair.matrix, row, col))
    {
        newPair.moves += "3";
        q.enqueue(newPair);
    }
    else if (move == "LEFT" && moveMatrixLeft(newPair.matrix, row, col))
    {
        newPair.moves += "4";
        q.enqueue(newPair);
    }
}

void findSmallestSequence(vector<vector<char>> &matrix, Queue &comboQueue, size_t row, size_t col, ofstream &outputFile)
{
    while (!comboQueue.isEmpty())
    {
        Pair temp = comboQueue.dequeue();
        if (isMatrixSolved(temp.matrix, row, col))
        {
            if (temp.moves == "")
            {
                outputFile << 0;
            }
            else
            {
                outputFile << temp.moves;
            }
            while (!comboQueue.isEmpty())
            {
                comboQueue.dequeue();
            }
        }
        else
        {
            addPath(comboQueue, temp, "UP", row, col);
            addPath(comboQueue, temp, "RIGHT", row, col);
            addPath(comboQueue, temp, "DOWN", row, col);
            addPath(comboQueue, temp, "LEFT", row, col);
        }
    }
}

void printMatrix(vector<vector<char>> matrix, size_t row, size_t col)
{
    for (int x = 0; x < row; x++)
    {
        for (int y = 0; y < col; y++)
        {
            cout << matrix[x][y] << " ";
        }
        cout << endl;
    }
    return;
}

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    ifstream inputFile(am.get("input"));
    ofstream outputFile(am.get("output"));

    // ifstream inputFile("input1.txt");
    // ofstream outputFile("output1.txt");

    size_t matrixRow;
    size_t matrixCol;
    inputFile >> matrixRow;
    inputFile >> matrixCol;
    vector<vector<char>> inputMatrix;
    createMatrix(inputMatrix, matrixRow, matrixCol, inputFile);

    // printMatrix(inputMatrix, matrixRow, matrixCol);
    // moveMatrixDown(inputMatrix, matrixRow, matrixCol);
    // cout << endl;
    // printMatrix(inputMatrix, matrixRow, matrixCol);

    Pair temp;
    temp.matrix = inputMatrix;
    temp.moves = "";
    Queue comboQueue;
    comboQueue.enqueue(temp);
    findSmallestSequence(inputMatrix, comboQueue, matrixRow, matrixCol, outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}