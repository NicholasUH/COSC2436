#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
#include <map>
#include "ArgumentManager.h"
using namespace std;

string formatInput(string s)
{
    string new_String;

    for (int x = 0; x < s.length(); x++)
    {
        if (isalpha(s[x]))
        {
            new_String += tolower(s[x]);
        }
        else if (isalpha(s[x - 1]) && ispunct(s[x]) && isalpha(s[x + 1]))
        {
            new_String += s[x];
        } 
    }
    return new_String;
}

void printMap(map<string, int> &frequencyMap, ofstream &outputFile)
{
    for (map<string, int>::iterator it = frequencyMap.begin(); it != frequencyMap.end(); it++)
    {
        outputFile << it->first << ": " << it->second << endl;
    }
}

void makeMap(ifstream &inputFile, ofstream &outputFile)
{
    string keyName;
    map<string, int> frequencyMap;

    while (inputFile >> keyName)
    {
        keyName.erase(remove(keyName.begin(), keyName.end(), '\n'), keyName.end());
        keyName.erase(remove(keyName.begin(), keyName.end(), '\r'), keyName.end());

        if (keyName != "")
        {
            keyName = formatInput(keyName);
            frequencyMap[keyName]++;
        }
    }
    printMap(frequencyMap, outputFile);
}

void solveLab(ifstream &inputFile, ofstream &outputFile)
{
    makeMap(inputFile, outputFile);
}

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    ifstream inputFile(am.get("input"));
    ofstream outputFile(am.get("output"));

    solveLab(inputFile, outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}