#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
#include "ArgumentManager.h"
#include "priorityQueue.h"
using namespace std;

void printContents(priorityQueue &q, ofstream &outputFile)
{
    while (!q.isEmpty())
    {
        outputFile << q.getFrontTask() << endl;
        q.dequeue();
    }
}

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    ifstream inputFile(am.get("input"));
    ofstream outputFile(am.get("output"));

    // ifstream inputFile("input1.txt");
    // ofstream outputFile("output1.txt");

    priorityQueue taskQueue;
    string inputLine = "";
    string inputTask = "";
    int seperatorIndex = 0;
    double inputTime = 0.0;

    while (getline(inputFile, inputLine))
    {
        inputLine.erase(remove(inputLine.begin(), inputLine.end(), '\n'), inputLine.end());
        inputLine.erase(remove(inputLine.begin(), inputLine.end(), '\r'), inputLine.end());

        if (inputLine != "")
        {
            seperatorIndex = inputLine.rfind(' ');
            inputTask = inputLine.substr(0, seperatorIndex);
            inputTime = stod(inputLine.substr(seperatorIndex + 1));
            taskQueue.enqueue(inputTask, inputTime);
        }
    }
    printContents(taskQueue,outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}