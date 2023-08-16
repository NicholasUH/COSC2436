#include "ArgumentManager.h"
#include "btree.h"
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void makeBTree(BTree &BTree, ifstream &inputFile)
{
    int valueToInsert = 0;
    while (inputFile >> valueToInsert)
    {
        if (BTree.hasDupe(valueToInsert) == false)
        {
            BTree.insert(valueToInsert);
        }
    }
}

void printLevels(BTree &BTree, ifstream &commandFile, ofstream &outputFile)
{
    string levelToPrint = "";

    outputFile << "Height=" << BTree.getHeight() << endl;

    while (commandFile >> levelToPrint)
    {
        if (isdigit(levelToPrint[0]) == true)
        {
            BTree.printLevel(outputFile, stoi(levelToPrint));
            outputFile << endl;
        }
    }
}

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    ifstream inputFile(am.get("input"));
    ifstream commandFile(am.get("command"));
    ofstream outputFile(am.get("output"));

    if (commandFile.peek() == EOF)
    {
        inputFile.close();
        commandFile.close();
        outputFile.close();
        return 0;
    }

    string degreeOfTree;
    getline(commandFile, degreeOfTree, '=');
    commandFile >> degreeOfTree;

    BTree BTree(stoi(degreeOfTree));

    makeBTree(BTree, inputFile);
    printLevels(BTree, commandFile, outputFile);

    inputFile.close();
    commandFile.close();
    outputFile.close();
    return 0;
}