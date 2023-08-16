#include "Queue.h"
using namespace std;

Queue::Queue()
{
    front = rear = nullptr;
}

bool Queue::isEmpty()
{
    return front == nullptr;
}

void Queue::enqueue(string s)
{
    qNode *temp = new qNode;
    temp->message = s;
    temp->next = nullptr;
    if (isEmpty())
    {
        front = rear = temp;
    }
    else
    {
        rear->next = temp;
        rear = temp;
    }
}
string Queue::dequeue()
{
    if (!isEmpty())
    {
        qNode *temp = front;
        string s = front->message;
        front = front->next;
        delete temp;
        return s;
    }   
    return "";
}

void Queue::print()
{
    if (isEmpty())
    {
        return;
    }

    qNode *curr = front;
    while (curr != nullptr)
    {
        cout << curr->message << endl;
        curr = curr->next;
    }
}