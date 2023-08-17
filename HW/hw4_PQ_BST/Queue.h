#ifndef Q_H
#define Q_H
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

struct qNode
{
    string message;
    qNode *next;
};

class Queue
{
private:
    qNode *front;
    qNode *rear;

public:
    Queue();
    bool isEmpty();
    void enqueue(string s);
    string getFront(){return front->message;}
    string dequeue();
    void print();
};

#endif