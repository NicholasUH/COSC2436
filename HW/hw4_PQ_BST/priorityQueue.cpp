#include "priorityQueue.h"
using namespace std;

priorityQueue::priorityQueue()
{
    front = nullptr;
    rear = nullptr;
}

string priorityQueue::getFront()
{
    return front->command;
}

bool priorityQueue::isEmpty()
{
    return front == nullptr;
}

void priorityQueue::enqueue(string _command, double _priority)
{
    pqNode *current = front;
    pqNode *temp = new pqNode;
    temp->command = _command;
    temp->priority = _priority;
    temp->next = nullptr;

    if (isEmpty())
    {
        front = temp;
        rear = temp;
    }
    else if (_priority < front->priority)
    {
        temp->next = front;
        front = temp;
    }
    else
    {
        while (current->next != nullptr && current->next->priority <= _priority)
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
        pqNode *temp = front;
        front = front->next;
        delete temp;
    }
}

void priorityQueue::print()
{
    if (isEmpty())
    {
        return;
    }

    pqNode *curr = front;
    while (curr != nullptr)
    {
        cout << curr->command << "(" << curr->priority << ")" << endl;
        curr = curr->next;
    }
}