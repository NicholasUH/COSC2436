#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <stack>
#include "ArgumentManager.h"
#include "LinkedList.h"
using namespace std;



string decodeString(string encodedString)
{
  stack<string> myStack;
  string result = "";

  for (int i = 0; i < encodedString.length(); i++)
  {
    if (encodedString[i] == '(')
    {
      myStack.push(result);
      result = "";
    }

    else if (encodedString[i] == ')')
    {
      // reverse using stacks
      stack<char> reverseStack;

      for (int i = 0; i < result.length(); i++)
      {
        reverseStack.push(result[i]);
      }

      for (int i = 0; i < result.length(); i++)
      {
        result[i] = reverseStack.top();
        reverseStack.pop();
      }

      string temp = myStack.top();
      myStack.pop();
      result = temp + result;
    }

    else
    {
      result += encodedString[i];
    }
  }

  return result;
}

int main(int argc, char *argv[])
{
  
  ArgumentManager am(argc, argv);
  ifstream inputFile(am.get("input"));
  ofstream outputFile(am.get("output"));

  //ofstream outputFile("output13.txt");
  //ifstream inputFile("input13.txt");

  string inStr = "";

  // where we'll store all decoded IDs
  linkedList IDContainer;

  while (getline(inputFile, inStr))
  {
    inStr.erase(remove(inStr.begin(), inStr.end(), '\n'), inStr.end());
    inStr.erase(remove(inStr.begin(), inStr.end(), '\r'), inStr.end());
    inStr.erase(remove(inStr.begin(), inStr.end(), ' '), inStr.end());

    if (inStr.find("Bar") != -1)
    {
      continue;
    }

    // skip empty lines
    if (inStr == "")
    {
      continue;
    }

    string decoded = decodeString(inStr);

    IDContainer.insert(IDContainer.getHead(), decoded);
  }

  IDContainer.sort(IDContainer.getHead());

  if (IDContainer.guiltyPresent(IDContainer.getHead()))
  {
    outputFile << "Guilty:" << endl;
    IDContainer.isGuilty(IDContainer.getHead(), outputFile);
  }

  if (IDContainer.isInnocentBool(IDContainer.getHead()))
  {
    outputFile << "Innocent:" << endl;
    IDContainer.isInnocent(IDContainer.getHead(), outputFile);
  }

  inputFile.close();
  outputFile.close();

  return 0;
}
