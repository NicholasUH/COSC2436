#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

struct node
{
  string username;
  int id;
  char grade;
  int score;
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
    cout << "Destructor Called" << endl;
    node *current = head;
    while (current != nullptr)
    {
      node *temp = current;
      current = current->next;
      delete temp;
    }
  }

  int getSize()
  {
    int count = 0;
    node *current = head;
    while (current != NULL)
    {
      count++;
      current = current->next;
    }
    return count;
  }

  node *createNode(string _username, int _id, char _grade, int _score, node *_next)
  {
    node *temp = new node;
    temp->username = _username;
    temp->id = _id;
    temp->grade = _grade;
    temp->score = _score;
    temp->next = _next;
    return temp;
  }

  node *createNode(string _username, int _id, char _grade, int _score)
  {
    node *temp = new node;
    temp->username = _username;
    temp->id = _id;
    temp->grade = _grade;
    temp->score = _score;
    temp->next = nullptr;
    return temp;
  }

  void addAtHead(string _username, int _id, char _grade, int _score)
  {
    if (head == nullptr)
    {
      head = createNode(_username, _id, _grade, _score);
    }
    else
    {
      head = createNode(_username, _id, _grade, _score, head);
    }
  }

  void addAtTail(string _username, int _id, char _grade, int _score)
  {
    if (head == nullptr)
    {
      head = createNode(_username, _id, _grade, _score);
    }
    else
    {
      node *temp = new node;
      temp = createNode(_username, _id, _grade, _score);

      node *current = head;
      while (current->next != nullptr)
      {
        current = current->next;
      }
      current->next = temp;
    }
  }

  void addByPosition(string _username, int _id, char _grade, int _score, int position)
  {
    node *temp = new node;
    temp = createNode(_username, _id, _grade, _score);

    node *current = head;
    for (int x = 0; x < position - 1; x++)
    {
      current = current->next;
    }
    temp->next = current->next;
    current->next = temp;
  }

  bool checkDupes(string _username, int _id, char _grade, int _score)
  {
    node *current = head;
    while (current != nullptr)
    {
      if (current->username == _username && current->id != _id)
      {
        return true;
      }
      else if (current->username == _username && current->id == _id)
      {
        current->score = _score;
        current->grade = _grade;
        return true;
      }
      else if (current->id == _id)
      {
        current->username = _username;
        current->grade = _grade;
        current->score = _score;
        return true;
      }
      current = current->next;
    }
    return false;
  }

  void removeByUserName(string _username)
  {

    if (head == nullptr)
    {
      return;
    }

    while (head != nullptr && head->username == _username)
    {
      head = head->next;
    }
    node *current = head;
    node *previous = nullptr;
    while (current != nullptr)
    {
      if (current->username == _username)
      {
        previous->next = current->next;
      }
      else
      {
        previous = current;
      }
      current = current->next;
    }
  }
  void removeByID(int _id)
  {

    if (head == nullptr)
    {
      return;
    }

    while (head != nullptr && head->id == _id)
    {
      head = head->next;
    }
    node *current = head;
    node *previous = nullptr;
    while (current != nullptr)
    {
      if (current->id == _id)
      {
        previous->next = current->next;
      }
      else
      {
        previous = current;
      }
      current = current->next;
    }
  }

  void removeByScore(int _score)
  {

    if (head == nullptr)
    {
      return;
    }

    while (head != nullptr && head->score == _score)
    {
      head = head->next;
    }

    node *current = head;
    node *previous = nullptr;

    while (current != nullptr)
    {
      if (current->score == _score)
      {
        previous->next = current->next;
      }
      else
      {
        previous = current;
      }
      current = current->next;
    }
  }
  void removeByGrade(char _grade)
  {

    if (head == nullptr)
    {
      return;
    }

    while (head != nullptr && head->grade == _grade)
    {
      head = head->next;
    }

    node *current = head;
    node *previous = nullptr;

    while (current != nullptr)
    {
      if (current->grade == _grade)
      {
        previous->next = current->next;
      }
      else
      {
        previous = current;
      }
      current = current->next;
    }
  }

  void sortByGrade()
  {
    if (head == nullptr || head->next == nullptr)
    {
      return;
    }
    else
    {
      bool isSorted = false;
      node *current;
      node *next;
      while (!isSorted)
      {
        isSorted = true;
        current = head;
        next = current->next;
        while (current->next != nullptr)
        {
          if (current->grade > next->grade)
          {
            string tempUser = current->username;
            current->username = next->username;
            next->username = tempUser;

            int tempID = current->id;
            current->id = next->id;
            next->id = tempID;

            char tempChar = current->grade;
            current->grade = next->grade;
            next->grade = tempChar;

            int tempScore = current->score;
            current->score = next->score;
            next->score = tempScore;

            isSorted = false;
          }
          current = current->next;
          next = current->next;
        }
      }
    }
  }

  void sortByScore()
  {
    if (head == nullptr || head->next == nullptr)
    {
      return;
    }
    else
    {
      bool isSorted = false;
      node *current;
      node *next;
      while (!isSorted)
      {
        isSorted = true;
        current = head;
        next = current->next;
        while (current->next != nullptr)
        {
          if (current->score < next->score)
          {
            string tempUser = current->username;
            current->username = next->username;
            next->username = tempUser;

            int tempID = current->id;
            current->id = next->id;
            next->id = tempID;

            char tempChar = current->grade;
            current->grade = next->grade;
            next->grade = tempChar;

            int tempScore = current->score;
            current->score = next->score;
            next->score = tempScore;

            isSorted = false;
          }
          current = current->next;
          next = current->next;
        }
      }
    }
  }

  void sortByID()
  {
    if (head == nullptr || head->next == nullptr)
    {
      return;
    }
    else
    {
      bool isSorted = false;
      node *current;
      node *next;
      while (!isSorted)
      {
        isSorted = true;
        current = head;
        next = current->next;
        while (current->next != nullptr)
        {
          if (current->id > next->id)
          {
            string tempUser = current->username;
            current->username = next->username;
            next->username = tempUser;

            int tempID = current->id;
            current->id = next->id;
            next->id = tempID;

            char tempChar = current->grade;
            current->grade = next->grade;
            next->grade = tempChar;

            int tempScore = current->score;
            current->score = next->score;
            next->score = tempScore;

            isSorted = false;
          }
          current = current->next;
          next = current->next;
        }
      }
    }
  }

  void sortByUserName()
  {
    if (head == nullptr || head->next == nullptr)
    {
      return;
    }
    else
    {
      bool isSorted = false;
      node *current;
      node *next;
      while (!isSorted)
      {
        isSorted = true;
        current = head;
        next = current->next;
        while (current->next != nullptr)
        {
          if (current->username > next->username)
          {
            string tempUser = current->username;
            current->username = next->username;
            next->username = tempUser;

            int tempID = current->id;
            current->id = next->id;
            next->id = tempID;

            char tempChar = current->grade;
            current->grade = next->grade;
            next->grade = tempChar;

            int tempScore = current->score;
            current->score = next->score;
            next->score = tempScore;

            isSorted = false;
          }
          current = current->next;
          next = current->next;
        }
      }
    }
  }
  void print(ofstream &outputFile)
  {
    node *current = head;
    while (current != nullptr)
    {
      if (current->next != nullptr)
      {
        outputFile << "[id:" << current->id << ";username:" << current->username << ";score:" << current->score << ";grade:" << current->grade << "]" << endl;
        current = current->next;
      }
      else
      {
        outputFile << "[id:" << current->id << ";username:" << current->username << ";score:" << current->score << ";grade:" << current->grade << "]";
        current = current->next;
      }
    }
  }
};