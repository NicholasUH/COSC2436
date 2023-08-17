#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "ArgumentManager.h"
#include "LinkedList.h"
using namespace std;

int main(int argc, char *argv[])
{

  ArgumentManager am(argc, argv);
  ifstream inputFile(am.get("input"));
  ifstream commandFile(am.get("command"));
  ofstream outputFile(am.get("output"));

  /*
  ifstream inputFile("input1.txt");
  ofstream outputFile("answer.txt");
  ifstream commandFile("command1.txt");
  */

  string inputStr;
  int idIndex, userIndex, scoreIndex, gradeIndex = 0;
  linkedList userCredentials;

  while (getline(inputFile, inputStr))
  {
    inputStr.erase(remove(inputStr.begin(), inputStr.end(), '\n'), inputStr.end());
    inputStr.erase(remove(inputStr.begin(), inputStr.end(), '\r'), inputStr.end());

    idIndex = inputStr.find("id:");
    userIndex = inputStr.find("username:");
    scoreIndex = inputStr.find("score:");
    gradeIndex = inputStr.find("grade:");

    if (idIndex == -1 || userIndex == -1 || scoreIndex == -1 || gradeIndex == -1)
    {
      continue;
    }

    if (idIndex > userIndex || userIndex > scoreIndex || scoreIndex > gradeIndex)
    {
      continue;
    }

    string id = inputStr.substr(idIndex + 3, userIndex - idIndex - 4);
    string username = inputStr.substr(userIndex + 9, scoreIndex - userIndex - 10);
    string score = inputStr.substr(scoreIndex + 6, gradeIndex - scoreIndex - 7);
    string grade = inputStr.substr(gradeIndex + 6, 1);

    if (userCredentials.checkDupes(username, stoi(id), grade[0], stoi(score)))
    {
    }
    else
    {
      userCredentials.addAtTail(username, stoi(id), grade[0], stoi(score));
    }
  }

  while (getline(commandFile, inputStr))
  {
    inputStr.erase(remove(inputStr.begin(), inputStr.end(), '\n'), inputStr.end());
    inputStr.erase(remove(inputStr.begin(), inputStr.end(), '\r'), inputStr.end());
    if (inputStr.find("Add") != -1)
    {
      int indexLeft = inputStr.find("(");
      int indexRight = inputStr.find(")");
      string addIndex = inputStr.substr(indexLeft + 1, indexRight - indexLeft - 1);

      idIndex = inputStr.find("id:");
      userIndex = inputStr.find("username:");
      scoreIndex = inputStr.find("score:");
      gradeIndex = inputStr.find("grade:");

      if (idIndex == -1 || userIndex == -1 || scoreIndex == -1 || gradeIndex == -1)
      {
        continue;
      }

      if (idIndex > userIndex || userIndex > scoreIndex || scoreIndex > gradeIndex)
      {
        continue;
      }

      string id = inputStr.substr(idIndex + 3, 4);
      string username = inputStr.substr(userIndex + 9, scoreIndex - userIndex - 10);
      string score = inputStr.substr(scoreIndex + 6, gradeIndex - scoreIndex - 7);
      string grade = inputStr.substr(gradeIndex + 6, 1);

      if (stoi(addIndex) < 0 || stoi(addIndex) > userCredentials.getSize())
      {
        continue;
      }
      else if (userCredentials.checkDupes(username, stoi(id), grade[0], stoi(score)))
      {
      }
      else if (stoi(addIndex) == 0)
      {
        userCredentials.addAtHead(username, stoi(id), grade[0], stoi(score));
      }
      else if (stoi(addIndex) == userCredentials.getSize())
      {
        userCredentials.addAtTail(username, stoi(id), grade[0], stoi(score));
      }
      else if (stoi(addIndex) > 0 && stoi(addIndex) < userCredentials.getSize())
      {
        userCredentials.addByPosition(username, stoi(id), grade[0], stoi(score), stoi(addIndex));
      }
    }
    else if (inputStr.find("Remove") != -1)
    {
      string value;

      if (inputStr.find("username:") != -1)
      {
        value = inputStr.substr(inputStr.find(":") + 1, inputStr.find(")") - inputStr.find(":") - 1);
        userCredentials.removeByUserName(value);
      }
      else if (inputStr.find("id:") != -1)
      {
        value = inputStr.substr(inputStr.find(":") + 1, inputStr.find(")") - inputStr.find(":") - 1);
        userCredentials.removeByID(stoi(value));
      }
      else if (inputStr.find("grade:") != -1)
      {
        value = inputStr.substr(inputStr.find(":") + 1, 1);
        userCredentials.removeByGrade(value[0]);
      }
      else if (inputStr.find("score:") != -1)
      {
        value = inputStr.substr(inputStr.find(":") + 1, inputStr.find(")") - inputStr.find(":") - 1);
        userCredentials.removeByScore(stoi(value));
      }
    }
    else if (inputStr.find("Sort") != -1)
    {
      if (inputStr.find("username") != -1)
      {
        userCredentials.sortByUserName();
      }
      else if (inputStr.find("id") != -1)
      {
        userCredentials.sortByID();
      }
      else if (inputStr.find("grade") != -1)
      {
        userCredentials.sortByGrade();
      }
      else if (inputStr.find("score") != -1)
      {
        userCredentials.sortByScore();
      }
    }
  }
  userCredentials.print(outputFile);

  inputFile.close();
  commandFile.close();
  outputFile.close();
  return 0;
}


