#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
#include "ArgumentManager.h"
#include "AVL.h"
using namespace std;

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    ifstream inputFile(am.get("input"));
    ofstream outputFile(am.get("output"));

    // ifstream inputFile("input2.txt");
    // ofstream outputFile("output2.txt");

    if (inputFile.peek() == EOF)
    {
        inputFile.close();
        outputFile.close();
        return 0;
    }

    AVL tree;
    int numOfNodes;
    double input;
    inputFile >> numOfNodes;

    for (int x = 0; x < numOfNodes; x++)
    {
        inputFile >> input;
        tree.add(input);
    }

    tree.print(outputFile, numOfNodes);

    inputFile.close();
    outputFile.close();
    return 0;
}