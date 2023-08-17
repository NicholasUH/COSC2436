#ifndef _PQ_H
#define _PQ_H
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

struct pqNode
{
    string command;
    double priority;
    pqNode *next;
};

class priorityQueue
{
private:
    pqNode *front;
    pqNode *rear;

public:
    priorityQueue();
    string getFront();
    bool isEmpty();
    void enqueue(string, double);
    void dequeue();
    void print();
};

#endif