#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
#include "ArgumentManager.h"
using namespace std;

template <typename T>
struct Node // NODE DECLARATION/INITIALIZATION
{
  T data;
  Node<T> *next;
};

template <typename T>
class LinkedList // LINKED LIST DECLARATION/INITIALIZATION
{
private:
  Node<T> *head;

public:
  LinkedList();
  ~LinkedList();
  bool isEmpty();
  void addHead(T data);
  void addTail(T data);
  void removeHead();
  void removeTail();
  void printLinkedList(ofstream &);
};

template <typename T>
LinkedList<T>::LinkedList() { head = nullptr; } // DEFAULT CONSTRUCTOR

template <typename T>
LinkedList<T>::~LinkedList() // DESTRUCTOR
{
  cout << "Destructor Called" << endl;
  Node<T> *current = head;
  while (current != nullptr)
  {
    Node<T> *temp = current;
    current = current->next;
    delete temp;
  }
}

template <typename T>
bool LinkedList<T>::isEmpty() // CHECK IF LINKEDLIST IS EMPTY
{
  if (head == nullptr)
  {
    return true;
  }
  else
  {
    return false;
  }
}

template <typename T>
void LinkedList<T>::addHead(T data) // ADD NODE AT HEAD POSITION
{
  if (isEmpty())
  {
    head = new Node<T>;
    head->data = data;
    head->next = nullptr;
    cout << "Adding to Head - " << head << " " << head->data << endl;
  }
  else
  {
    Node<T> *temp = new Node<T>;
    temp->data = data;
    temp->next = nullptr;

    temp->next = head;
    head = temp;
    cout << "Adding to Head - " << head << " " << head->data << endl;
  }
}

template <typename T>
void LinkedList<T>::addTail(T data) // ADD NODE AT TAIL POSITION
{
  if (isEmpty())
  {
    head = new Node<T>;
    head->data = data;
    head->next = nullptr;
    cout << "Adding to Head - " << head << " " << head->data << endl;
  }
  else
  {
    Node<T> *temp = new Node<T>;
    temp->data = data;
    temp->next = nullptr;

    Node<T> *current = head;
    while (current->next != nullptr)
    {
      current = current->next;
    }
    current->next = temp;
    cout << "Adding to Tail " << temp << " " << temp->data << endl;
  }
}

template <typename T>
void LinkedList<T>::removeHead() // REMOVE HEAD
{
  if (head == nullptr)
  {
    return;
  }
  else
  {
    Node<T> *temp = head;

    cout << "Deleting Head - " << temp << " " << temp->data << endl;
    head = head->next;
    delete temp;
  }
}

template <typename T>
void LinkedList<T>::removeTail() // REMOVE TAIL
{
  if (head == nullptr)
  {
    return;
  }
  Node<T> *current = head;
  Node<T> *previous = nullptr;
  if (current == nullptr) // IF EMPTY
    return;
  else if (current->next == nullptr) // IF SIZE 1
  {
    cout << "Deleting Tail - " << head << " " << head->data << endl;
    head = nullptr;
  }
  else
  {
    while (current->next != nullptr)
    {
      previous = current;
      current = current->next;
    }
    cout << "Deleting Tail - " << current << " " << current->data << endl;
    previous->next = nullptr;
    delete current;
  }
}

template <typename T>
void LinkedList<T>::printLinkedList(ofstream &outputFile) // OUTPUT NODE INFORMATION TO FILE
{
  if (head == nullptr)
  {
    return;
  }
  Node<T> *current = head;
  while (current != nullptr)
  {
    if (current->next != nullptr)
    {
      outputFile << current->data << " ";
      current = current->next;
    }
    else
    {
      outputFile << current->data;
      current = current->next;
    }
  }

  outputFile.close();
}

int main(int argc, char *argv[])
{

  ArgumentManager am(argc, argv);
  ifstream inputFile(am.get("input"));
  ofstream outputFile(am.get("output"));

  /*
  ifstream inputFile("input1.txt");
  ofstream outputFile("answer.txt");
  */

  if (!inputFile.is_open()) // CHECK IF INPUTFILE IS OPEN
  {
    cout << "Error - Unable to Open Input File." << endl;
    outputFile.close();
    return 0;
  }

  if (inputFile.peek() == EOF) // CHECK IF INPUTFILE IS EMPTY
  {
    cout << "Error - Input File is Empty" << endl;
    inputFile.close();
    outputFile.close();
    return 0;
  }

  string inputDataType; // char,string, integer
  string addLocation;   // head or tail, place of addition

  LinkedList<string> stringLinkedList;
  LinkedList<char> charLinkedList;
  LinkedList<int> intLinkedList;

  string stringTemp;
  int intTemp;
  getline(inputFile, inputDataType);
  inputDataType.erase(remove(inputDataType.begin(), inputDataType.end(), '\n'), inputDataType.end());
  inputDataType.erase(remove(inputDataType.begin(), inputDataType.end(), '\r'), inputDataType.end());
  
  getline(inputFile, addLocation);
  addLocation.erase(remove(addLocation.begin(), addLocation.end(), '\n'), addLocation.end());
  addLocation.erase(remove(addLocation.begin(), addLocation.end(), '\r'), addLocation.end());

  if (inputDataType == "string") // STRING INSTANCE
  {
    while (getline(inputFile, stringTemp))
    {
      stringTemp.erase(remove(stringTemp.begin(), stringTemp.end(), '\n'), stringTemp.end());
      stringTemp.erase(remove(stringTemp.begin(), stringTemp.end(), '\r'), stringTemp.end());
      if (stringTemp.find("remove") == string::npos)
      {
        if (addLocation == "head")
        {
          stringLinkedList.addHead(stringTemp);
        }
        else if (addLocation == "tail")
        {
          stringLinkedList.addTail(stringTemp);
        }
      }
      else if (stringTemp.find("remove head") != string::npos)
      {
        stringLinkedList.removeHead();
      }
      else if (stringTemp.find("remove tail") != string::npos)
      {
        stringLinkedList.removeTail();
      }
    }
    stringLinkedList.printLinkedList(outputFile);
  }
  else if (inputDataType == "int") // INTEGER INSTANCE
  {
    while (getline(inputFile, stringTemp))
    {
      stringTemp.erase(remove(stringTemp.begin(), stringTemp.end(), '\n'), stringTemp.end());
      stringTemp.erase(remove(stringTemp.begin(), stringTemp.end(), '\r'), stringTemp.end());
      if (stringTemp.find("remove") == string::npos)
      {
        if (addLocation == "head")
        {
          intTemp = stoi(stringTemp);
          intLinkedList.addHead(intTemp);
        }
        else if (addLocation == "tail")
        {
          intTemp = stoi(stringTemp);
          intLinkedList.addTail(intTemp);
        }
      }
      else if (stringTemp.find("remove head") != string::npos)
      {
        intLinkedList.removeHead();
      }
      else if (stringTemp.find("remove tail") != string::npos)
      {
        intLinkedList.removeTail();
      }
    }
    intLinkedList.printLinkedList(outputFile);
  }
  else if (inputDataType == "char") // CHARACTER INSTANCE
  {
    while (getline(inputFile, stringTemp))
    {
      stringTemp.erase(remove(stringTemp.begin(), stringTemp.end(), '\n'), stringTemp.end());
      stringTemp.erase(remove(stringTemp.begin(), stringTemp.end(), '\r'), stringTemp.end());
      if (stringTemp.find("remove") == string::npos)
      {
        if (addLocation == "head")
        {
          charLinkedList.addHead(stringTemp[0]);
        }
        else if (addLocation == "tail")
        {
          charLinkedList.addTail(stringTemp[0]);
        }
      }
      else if (stringTemp.find("remove head") != string::npos)
      {
        charLinkedList.removeHead();
      }
      else if (stringTemp.find("remove tail") != string::npos)
      {
        charLinkedList.removeTail();
      }
    }
    charLinkedList.printLinkedList(outputFile);
  }

  inputFile.close();
  outputFile.close();
  return 0;
}