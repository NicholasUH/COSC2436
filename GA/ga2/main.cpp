#include "ArgumentManager.h"
#include "prioQueue.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

void printInfo(ofstream &outputFile, string inputExp, string inputPostfixExp, double expValue)
{
    cout << inputExp << endl;
    cout << inputPostfixExp << endl;
    cout << expValue << endl;
    cout << endl;
}

string changeParenthesis(string exp)
{
    for (int x = 0; x < exp.length(); x++)
    {
        if (exp[x] == '}' || exp[x] == ']')
        {
            exp[x] = ')';
        }
        else if (exp[x] == '{' || exp[x] == '[')
        {
            exp[x] = '(';
        }
    }
    return exp;
}

int precedenceCheck(char op)
{
    if (op == '/' || op == '*')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return 0;
}

string infixToPostfix(string exp)
{

    exp = changeParenthesis(exp);
    stack<char> operatorStack;
    string postfixExp = "";

    for (int x = 0; x < exp.length(); x++)
    {
        if (isalpha(exp[x]) || isdigit(exp[x]))
        {
            postfixExp += exp[x];
        }
        else if (exp[x] == '(')
        {
            operatorStack.push(exp[x]);
        }
        else if (exp[x] == ')')
        {
            while (operatorStack.top() != '(')
            {
                postfixExp += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.pop();
        }
        else if (exp[x] == '+' || exp[x] == '-' || exp[x] == '*' || exp[x] == '/')
        {
            while (!operatorStack.empty() && precedenceCheck(exp[x]) <= precedenceCheck(operatorStack.top()))
            {
                postfixExp += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(exp[x]);
        }
    }

    while(!operatorStack.empty())
    {
        postfixExp += operatorStack.top();
        operatorStack.pop();
    }

    return postfixExp;
}

double evaluatePostfix(string exp)
{
    stack<double> valueStack;
    double num1, num2, num3;
    for (int x = 0; x < exp.length(); x++)
    {
        if (isdigit(exp[x]))
        {
            valueStack.push(exp[x] - '0');
        }
        else
        {
            if(!valueStack.empty())
            {
                num1 = valueStack.top();
                valueStack.pop();
                num2 = valueStack.top();
                valueStack.pop();
            }
            if (exp[x] == '+')
            {
                num3 = num2 + num1;
                valueStack.push(num3);
            }
            else if (exp[x] == '*')
            {
                num3 = num2 * num1;
                valueStack.push(num3);
            }
            else if (exp[x] == '-')
            {
                num3 = num2 - num1;
                valueStack.push(num3);
            }
            else if (exp[x] == '/')
            {
                num3 = num2 / num1;
                valueStack.push(num3);
            }
        }
    }
    return valueStack.top();
}

bool hasRedundantParenthesis(string exp)
{
    exp = changeParenthesis(exp);
    stack<char> stack;
    for (int x = 0; x < exp.length(); x++)
    {
        if (exp[x] == ')')
        {
            if (!stack.empty() && stack.top() == '(')
            {
                return true;
            }
            while (!stack.empty() && stack.top() != '(')
            {
                stack.pop();
            }
            if (!stack.empty())
            {
                stack.pop();
            }
        }
        else
        {
            stack.push(exp[x]);
        }
    }
    return false;
}

bool hasValidParenthesis(string exp)
{
    stack<char> stack;
    string parenthesis;

    for (int x = 0; x < exp.length(); x++)
    {
        if (exp[x] == '(' || exp[x] == '{' || exp[x] == '[' || exp[x] == ')' || exp[x] == '}' || exp[x] == ']')
        {
            parenthesis += exp[x];
        }
    }

    if (parenthesis.length() % 2 != 0)
    {
        return false;
    }

    for (int x = 0; x < parenthesis.length(); x++)
    {
        if (parenthesis[x] == '(' || parenthesis[x] == '{' || parenthesis[x] == '[')
        {
            stack.push(parenthesis[x]);
        }
        else if (!stack.empty() && parenthesis[x] == ')' && stack.top() == '(')
        {
            stack.pop();
        }
        else if (!stack.empty() && parenthesis[x] == ']' && stack.top() == '[')
        {
            stack.pop();
        }
        else if (!stack.empty() && parenthesis[x] == '}' && stack.top() == '{')
        {
            stack.pop();
        }
        else
        {
            return false;
        }
    }
    return stack.empty();
}

int main(int argc, char *argv[])
{

    ArgumentManager am(argc, argv);
    ifstream inputFile(am.get("input"));
    ofstream outputFile(am.get("output"));

    prioQueue expQueue;
    string inputExp;
    string inputPostfixExp;
    double expValue;

    while (getline(inputFile, inputExp))
    {

        inputExp.erase(remove(inputExp.begin(), inputExp.end(), '\n'), inputExp.end());
        inputExp.erase(remove(inputExp.begin(), inputExp.end(), '\r'), inputExp.end());

        if (inputExp != "" && !hasRedundantParenthesis(inputExp) && hasValidParenthesis(inputExp))
        {
            inputPostfixExp = infixToPostfix(inputExp);
            expValue = evaluatePostfix(inputPostfixExp);
            expQueue.enqueue(inputExp, expValue);
        }
    }
    expQueue.print(outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}
