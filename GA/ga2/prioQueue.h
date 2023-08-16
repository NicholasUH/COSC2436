#include <iostream>
#include <fstream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

struct node
{
    string expression;
    double value;
    node *next;
};

class prioQueue
{
private:
    node *front;

public:
    prioQueue() { front = nullptr; }

    bool isEmpty() { return front == nullptr; }

    ~prioQueue()
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

    void enqueue(string _exp, int _val)
    {
        node *current = front;
        node *temp = new node;
        temp->expression = _exp;
        temp->value = _val;

        if (isEmpty() || _val < front->value)
        {
            temp->next = front;
            front = temp;
        }
        else
        {
            while (current->next != nullptr && current->next->value <= _val)
            {
                current = current->next;
            }
            temp->next = current->next;
            current->next = temp;
        }
    }

    void print(ofstream &outputFile)
    {
        if (isEmpty())
        {
            outputFile << "No Valid Expression";
            return;
        }
        else
        {
            node *current = front;
            while (current != nullptr)
            {
                if (current->next != nullptr)
                {
                    outputFile << current->expression << endl;
                }
                else
                {
                    outputFile << current->expression;
                }
                current = current->next;
            }
        }
    }
};