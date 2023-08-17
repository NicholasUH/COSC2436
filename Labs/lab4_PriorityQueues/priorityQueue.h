#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

struct node
{
    string task;
    double time;
    node *next;
};

class priorityQueue
{
private:
    node *front;
    node *rear;

public:
    priorityQueue();
    ~priorityQueue();
    string getFrontTask();
    double getFrontTime();
    bool isEmpty();
    void enqueue(string, double);
    void dequeue();
};

priorityQueue::priorityQueue()
{
    front = nullptr;
    rear = nullptr;
}

priorityQueue::~priorityQueue()
{
    node *current = front;
    node *temp = new node;

    while (current != nullptr)
    {
        temp = current;
        current = current->next;
        delete temp;
    }
}

string priorityQueue::getFrontTask()
{
    return front->task;
}
double priorityQueue::getFrontTime()
{
    return front->time;
}

bool priorityQueue::isEmpty()
{
    return front == nullptr;
}

void priorityQueue::enqueue(string _task, double _time)
{
    node *current = front;
    node *temp = new node;
    temp->task = _task;
    temp->time = _time;
    temp->next = nullptr;

    if (front == nullptr || rear == nullptr)
    {
        front = temp;
        rear = temp;
    }
    else if (_time < front->time)
    {
        temp->next = front;
        front = temp;
    }
    else
    {
        while (current->next != nullptr && current->next->time <= _time)
        {
            current = current->next;
        }
        if (current->next != nullptr)
        {
            temp->next = current->next;
            current->next = temp;
        }
        else
        {
            rear->next = temp;
            rear = temp;
        }
    }
}

void priorityQueue::dequeue()
{
    if (!isEmpty())
    {
        node *temp = front;
        front = front->next;
        delete temp;
    }
}