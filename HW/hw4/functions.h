#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H
#include <iostream>
using namespace std;

void makeCommandQueue(ifstream &inputFile, priorityQueue &commandQueue, string &methodOfTraversal)
{
    string s = "";
    while (getline(inputFile, s))
    {
        s.erase(remove(s.begin(), s.end(), '\n'), s.end());
        s.erase(remove(s.begin(), s.end(), '\r'), s.end());

        if (s == "Inorder" || s == "Preorder" || s == "Postorder")
        {
            methodOfTraversal = s;
        }
        else if (s != "")
        {
            int indexLeft = s.find("(");
            int indexRight = s.find(")");
            string command = s.substr(0, indexLeft);
            string priority = s.substr(indexLeft + 1, indexRight - indexLeft - 1);

            commandQueue.enqueue(command, stod(priority));
        }
    }
}

void addEncodedMessage(Queue &q, string message)
{
    int leftBracket = message.find("[");
    int rightBracket = message.find("]");

    message = message.substr(leftBracket + 1, rightBracket - leftBracket - 1);

    q.enqueue(message);
    return;
}

string replaceChars(string command, string message)
{
    int commaIndex = command.find(",");
    char toBeReplaced = command[commaIndex - 1];
    char replacement = command[commaIndex + 1];

    for (int x = 0; x < message.length(); x++)
    {
        if (message[x] == toBeReplaced)
        {
            message[x] = replacement;
        }
    }
    return message;
}

string addCharAfter(string command, string message)
{
    int commaIndex = command.find(",");
    char targetChar = command[commaIndex - 1];
    char additionalChar = command[commaIndex + 1];
    string newString = "";

    for (int x = 0; x < message.length(); x++)
    {
        if (message[x] == targetChar)
        {
            newString += message[x];
            newString += additionalChar;
        }
        else
        {
            newString += message[x];
        }
    }
    return newString;
}

string removeChar(string command, string message)
{
    string newString = "";

    int leftBracket = command.find("[");
    int rightBracket = command.find("]");

    string s = command.substr(leftBracket + 1, rightBracket - leftBracket - 1);
    char charToRemove = s[0];

    for (int x = 0; x < message.length(); x++)
    {
        if (message[x] == charToRemove)
        {
            continue;
        }
        else
        {
            newString += message[x];
        }
    }

    return newString;
}

string swapChars(string command, string message)
{
    string newString = "";
    int commaIndex = command.find(",");
    char swapOne = command[commaIndex - 1];
    char swapTwo = command[commaIndex + 1];

    for (int x = 0; x < message.length(); x++)
    {
        if (message[x] == swapOne)
        {
            newString += swapTwo;
        }
        else if (message[x] == swapTwo)
        {
            newString += swapOne;
        }
        else
        {
            newString += message[x];
        }
    }

    return newString;
}

void printBST(BST &t, string orderOfTravseral, ofstream &outputFile)
{
    if (orderOfTravseral == "Inorder")
    {
        t.inOrderTraversal(t.getRoot(), outputFile);
    }
    else if (orderOfTravseral == "Preorder")
    {
        t.preOrderTraversal(t.getRoot(), outputFile);
    }
    else if (orderOfTravseral == "Postorder")
    {
        t.postOrderTraversal(t.getRoot(), outputFile);
    }
}

void executeCommands(priorityQueue &commandQueue, Queue &messageQueue, BST &messageTree)
{
    string s = "";
    while (!commandQueue.isEmpty())
    {
        if (commandQueue.getFront().find("DECODE") != -1)
        {
            addEncodedMessage(messageQueue, commandQueue.getFront());
        }
        else if (!messageQueue.isEmpty())
        {
            if (commandQueue.getFront().find("REPLACE") != std::string::npos)
            {
                s = replaceChars(commandQueue.getFront(), messageQueue.dequeue());
                messageQueue.enqueue(s);
            }
            else if (commandQueue.getFront().find("ADD") != std::string::npos)
            {
                s = addCharAfter(commandQueue.getFront(), messageQueue.dequeue());
                messageQueue.enqueue(s);
            }
            else if (commandQueue.getFront().find("REMOVE") != std::string::npos)
            {
                s = removeChar(commandQueue.getFront(), messageQueue.dequeue());
                messageQueue.enqueue(s);
            }
            else if (commandQueue.getFront().find("SWAP") != std::string::npos)
            {
                s = swapChars(commandQueue.getFront(), messageQueue.dequeue());
                messageQueue.enqueue(s);
            }
            else if (commandQueue.getFront().find("BST") != std::string::npos)
            {
                messageTree.insertR(messageTree.getRoot(), messageQueue.dequeue());
                // messageTree.insert(messageQueue.dequeue());
            }
        }
        commandQueue.dequeue();
    }
}

#endif