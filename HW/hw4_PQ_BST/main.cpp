#include "ArgumentManager.h"
#include "priorityQueue.h"
#include "BST.h"
#include "Queue.h"
#include "functions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
using namespace std;

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    ifstream inputFile(am.get("input"));
    ofstream outputFile(am.get("output"));

    // ifstream inputFile("input1.txt");
    // ofstream outputFile("output1.txt");

    priorityQueue commandQueue;
    string traversalMethod = "";
    Queue messageQueue;
    BST messageTree;

    makeCommandQueue(inputFile, commandQueue, traversalMethod);
    executeCommands(commandQueue, messageQueue, messageTree);
    printBST(messageTree, traversalMethod, outputFile);
    inputFile.close();
    outputFile.close();

    return 0;
}