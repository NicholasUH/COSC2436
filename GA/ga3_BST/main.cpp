#include "ArgumentManager.h"
#include "BST.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    ifstream inputFile(am.get("input"));
    ofstream outputFile(am.get("output"));

    double number;
    BST tree;

    while(inputFile >> number){
        tree.insert(number);
    }

    tree.print(outputFile);

    inputFile.close();
    outputFile.close();
    return 0;

}