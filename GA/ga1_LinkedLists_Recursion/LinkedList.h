#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

struct node
{
  string data;
  node *next;
};

class linkedList
{
private:
  node *head;

public:
  linkedList()
  {
    head = nullptr;
  }

  ~linkedList()
  {
    node *curr = head;
    node *temp = nullptr;
    while (curr != head)
    {
      temp = curr;
      curr = curr->next;
      delete temp;
    }
  }

  node *getHead()
  {
    return head;
  }

  bool isEmpty(node *curr)
  {
    if (curr == nullptr)
    {
      return true;
    }

    return false;
  }

  // recursively add to linked list
  node *insert(node *curr, string _data)
  {

    if (head == nullptr)
    {
      node *temp = new node;
      temp->data = _data;
      head = temp;
    }

    else if (curr->next == nullptr)
    {
      node *temp = new node;
      temp->data = _data;
      curr->next = temp;
    }

    else
    {
      return insert(curr->next, _data);
    }

    return head;
  }

  // recursive print function
  void print(node *curr)
  {

    if (curr == nullptr)
    {
      return;
    }

    else
    {
      cout << curr->data << endl;
      print(curr->next);
    }
  }

  void sort(node *curr)
  {

    if (curr == nullptr || curr->next == nullptr)
    {
      return;
    }

    else
    {
      node *min = curr;
      node *ptr;
      for (ptr = curr; ptr->next != nullptr; ptr = ptr->next)
      {
        if (stod(ptr->next->data) < stod(min->data))
        {
          min = ptr->next;
        }
      }
      if (min != curr)
      {
        string temp = min->data;
        min->data = curr->data;
        curr->data = temp;
      }
      sort(curr->next);
    }
  }

  // checks for duplicate IDs
  void isGuilty(node *curr, ofstream &outputFile)
  {

    if (curr == nullptr || curr->next == nullptr)
    {
      return;
    }

    else if (curr->data == curr->next->data)
    {
      outputFile << curr->data << endl;
      isGuilty(curr->next->next, outputFile);
    }

    else
    {
      isGuilty(curr->next, outputFile);
    }
  }

  // checks for unique IDs
  void isInnocent(node *curr, ofstream &outputFile)
  {

    if (curr == nullptr)
    {
      return;
    }

    else if (curr->next == nullptr || curr->data != curr->next->data)
    {
      outputFile << curr->data << endl;
      isInnocent(curr->next, outputFile);
    }

    else
    {
      isInnocent(curr->next->next, outputFile);
    }
  }

  bool guiltyPresent(node *curr)
  {
    if (curr == nullptr || curr->next == nullptr)
    {
      return false;
    }

    else if (curr->data == curr->next->data)
    {
      return true;
    }

    else
    {
      return guiltyPresent(curr->next);
    }
  }

  bool isInnocentBool(node *curr)
  {
    if (curr == nullptr)
    {
      return false;
    }

    else if (curr->next != nullptr && curr->data != curr->next->data)
    {
      return true;
    }

    else
    {
      return isInnocentBool(curr->next->next);
    }
  }
};