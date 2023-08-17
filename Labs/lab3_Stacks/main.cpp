#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
#include <stack>
#include "ArgumentManager.h"
using namespace std;

int precedenceCheck(char op)
{
    if (op == '/' || op == '*')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return -1;
}

string toPostFix(string exp)
{

    stack<char> operatorStack;
    string newExp = "";

    for (int x = 0; x < exp.length(); x++)
    {
        if (isalpha(exp[x])) // IF NUMBER
        {
            newExp += exp[x];
        }
        else if (isdigit(exp[x]))
        {
            newExp += exp[x];
        }
        else if (exp[x] == '(') // IF OPEN PARENTHESIS
        {
            operatorStack.push(exp[x]);
        }
        else if (exp[x] == ')') // IF CLOSED PARENTHESIS
        {
            while (operatorStack.top() != '(')
            {
                newExp += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.pop();
        }
        else if (exp[x] == '+' || exp[x] == '-' || exp[x] == '*' || exp[x] == '/')
        {
            while (!operatorStack.empty() && precedenceCheck(exp[x]) <= precedenceCheck(operatorStack.top()))
            {
                newExp += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(exp[x]);
        }
    }

    newExp += operatorStack.top();

    return newExp;
}

double evaluateExpression(string exp)
{
    stack<double> valueStack;
    string newExp = "";
    double num1, num2, num3;
    for (int x = 0; x < exp.length() - 1; x++)
    {
        if (isdigit(exp[x]))
        {
            valueStack.push(exp[x] - '0');
        }
        else if (exp[x] == '+')
        {
            num1 = valueStack.top();
            valueStack.pop();
            num2 = valueStack.top();
            valueStack.pop();
            num3 = num2 + num1;
            valueStack.push(num3);
        }
        else if (exp[x] == '*')
        {
            num1 = valueStack.top();
            valueStack.pop();
            num2 = valueStack.top();
            valueStack.pop();
            num3 = num2 * num1;
            valueStack.push(num3);
        }
        else if (exp[x] == '-')
        {
            num1 = valueStack.top();
            valueStack.pop();
            num2 = valueStack.top();
            valueStack.pop();
            num3 = num2 - num1;
            valueStack.push(num3);
        }
        else if (exp[x] == '/')
        {
            num1 = valueStack.top();
            valueStack.pop();
            num2 = valueStack.top();
            valueStack.pop();
            num3 = num2 / num1;
            valueStack.push(num3);
        }
    }
    while (!valueStack.empty())
    {
        newExp += to_string(valueStack.top());
        valueStack.pop();
    }
    return stod(newExp);
}

double solveForX(int xPos, char finalOp, double left, double right)
{

    if (finalOp == '+')
    {
        return right - left;
    }
    else if (finalOp == '-')
    {
        if (xPos == 0)
        {
            return right + left;
        }
        else if (xPos != 0)
        {
            return (right - left) * -1;
        }
    }
    else if (finalOp == '*')
    {
        return right / left;
    }
    else if (finalOp == '/')
    {
        if (xPos == 0)
        {
            return right * left;
        }
        else if (xPos != 0)
        {
            return left / right;
        }
    }

    return -1;
}

int main(int argc, char *argv[])
{

    ArgumentManager am(argc, argv);
    ifstream inputFile(am.get("input"));
    ofstream outputFile(am.get("output"));

    /*
    ifstream inputFile("input4.txt");
    ofstream outputFile("output1.txt");
    */

    if (!inputFile.is_open()) // CHECK IF INPUTFILE IS OPEN
    {
        cout << "Error - Unable to Open Input File." << endl;
        outputFile.close();
        return 0;
    }

    if (inputFile.peek() == EOF) // CHECK IF INPUTFILE IS EMPTY
    {
        cout << "Error - Input File is Empty" << endl;
        inputFile.close();
        outputFile.close();
        return 0;
    }

    string inputExp = "";
    string leftSide = "";
    char finalOperation;
    int xPosition = 0;
    double leftSolved = 0.0;
    double rightSide = 0.0;
    double finalAnswer = 0.0;

    getline(inputFile, inputExp);
    inputExp.erase(remove(inputExp.begin(), inputExp.end(), '\n'), inputExp.end());
    inputExp.erase(remove(inputExp.begin(), inputExp.end(), '\r'), inputExp.end());
    inputExp.erase(remove(inputExp.begin(), inputExp.end(), ' '), inputExp.end());

    leftSide = toPostFix(inputExp.substr(0, inputExp.find('=')));
    leftSolved = evaluateExpression(leftSide);
    xPosition = inputExp.find('x');
    rightSide = stod(inputExp.substr(inputExp.find('=') + 1, inputExp.length() - inputExp.find('=') - 1));

    if (xPosition == 0)
    {
        finalOperation = inputExp[1];
    }
    else
    {
        finalOperation = inputExp[xPosition - 1];
    }

    finalAnswer = solveForX(xPosition, finalOperation, leftSolved, rightSide);

    outputFile << fixed;
    outputFile << setprecision(2);
    outputFile << finalAnswer;

    inputFile.close();
    outputFile.close();
    return 0;
}
