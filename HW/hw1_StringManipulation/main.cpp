// Nicholas Tran
// HW1
// String Manipulation and Filtering

#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
#include "ArgumentManager.h"
using namespace std;

string removeWhiteSpace(string word) // USED TO REMOVE WHITESPACES
{
    string newWord;
    for (int x = 0; x < word.size(); x++)
    {
        if (isspace(word[x]))
        {
            continue;
        }
        else
        {
            newWord += word[x];
        }
    }
    return newWord;
}

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    ifstream inputFile(am.get("input"));
    ofstream outputFile(am.get("output"));
    ifstream commandFile(am.get("command"));

    // COMMAND FILE OPERATIONS
    string commands[101];
    int commandCount = 0;
    bool hasCommand = true;
    bool firstAndLast = false;
    int firstCount = 0;
    int lastCount = 0;
    string ctemp;

    if (commandFile.peek() == EOF || !commandFile.is_open()) // CHECKS IF COMMANDFILE IS EMPTY OR NOT OPEN
    {
        hasCommand = false;
    }

    while (getline(commandFile, ctemp)) // EXTRACTS COMMANDS AND COUNTS HOW MANY FIRSTS/LASTS EXIST
    {
        ctemp = removeWhiteSpace(ctemp);
        commands[commandCount] = ctemp;
        if (commands[commandCount].find("first4:") != string::npos)
        {
            firstCount++;
        }
        else if (commands[commandCount].find("last4:") != string::npos)
        {
            lastCount++;
        }
        commandCount++;
    }

    if (firstCount > 0 && lastCount > 0) // CHECKS IF FIRSTS AND LASTS EXIST IN COMMANDFILE
    {
        firstAndLast = true;
    }

    if (!inputFile.is_open()) // IF INPUTFILE IS OPEN
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

    // ADDS ENTRIES INTO ARRAY WHILE FILTERING EMPTY LINES, SPACES, AND INVALID ENTRIES
    string entries[101];
    string temp;
    int arrayLength = 0;
    while (getline(inputFile, temp))
    {
        temp = removeWhiteSpace(temp);
        if (temp != "" && temp.find(';') != string::npos && temp.find("id:") != string::npos)
        {
            entries[arrayLength] = temp;
            arrayLength++;
        }
    }

    // EXTRACTS THE IDs INTO AN ARRAY
    string ids[arrayLength];
    int IDPosition;
    for (int x = 0; x < arrayLength; x++)
    {
        IDPosition = entries[x].find("id:");
        ids[x] = entries[x].substr(IDPosition + 3, entries[x].length() - 1);
    }

    // EXTRACTS CHARACTER SETS
    string charSets[arrayLength];
    int alphaCount = 0;
    int setPosition;
    for (int x = 0; x < arrayLength; x++)
    {
        setPosition = entries[x].find("id:");
        charSets[x] = entries[x].substr(0, setPosition);
    }

    // DECODING
    for (int x = 0; x < arrayLength; x++) // ITERATES THRU IDS
    {
        string currentID = ids[x];
        string currentSet = charSets[x];
        string replacement = "";

        for (int y = 0; y < currentSet.length(); y++) // ITERATES THRU CURRENTID
        {
            replacement = "";
            if (isalpha(currentSet[y]))
            {
                for (int i = y; i < currentSet.length(); i++) // CREATES REPLACEMENT SET
                {
                    if (isdigit(currentSet[i]))
                    {
                        replacement += currentSet[i];
                    }
                    else if (currentSet[i] == ';')
                    {
                        break;
                    }
                }
                while (currentID.find(currentSet[y]) != string::npos) // LOOKS FOR CURRENT LETTER IN CURRENT ID
                {
                    currentID.replace(currentID.find(currentSet[y]), 1, replacement);
                }
                ids[x] = currentID;
            }
        }
    }

    for (int x = 0; x < arrayLength; x++) // REPLACES #s WITH CURERNT INDEX
    {
        string currentID = ids[x];
        string newID;
        for (int y = 0; y < currentID.length(); y++)
        {
            if (currentID[y] == '#')
            {
                newID += to_string(y);
            }
            else
            {
                newID += currentID[y];
            }
        }
        ids[x] = newID;
    }

    // COMMAND FILTERING
    bool first = false;
    bool last = false;
    firstCount = 0;
    lastCount = 0;

    for (int x = 0; x < arrayLength; x++) // ITERATES THRU IDS
    {
        firstCount = 0;
        lastCount = 0;
        string commandCheck = ids[x];
        string commandCon = "";
        for (int y = 0; y < commandCount; y++) // ITERATES THRU COMMANDS
        {
            commandCon = "";

            if (commands[y].find("first4:") != string::npos) // CHECK FOR FIRST4
            {
                commandCon = commands[y].substr(commands[y].find(':') + 1, 4);
                if (commandCheck.substr(0, 4) == commandCon)
                {

                    firstCount++;
                }
            }
            else if (commands[y].find("last4:") != string::npos) // CHECK FOR LAST 4
            {
                commandCon = commands[y].substr(commands[y].find(':') + 1, 4);
                if (commandCheck.substr(commandCheck.length() - 4, commandCheck.length()) == commands[y].substr(commands[y].find(":") + 1, 4))
                {
                    lastCount++;
                }
            }
        }
        if (!firstAndLast && (firstCount > 0 || lastCount > 0)) // CONDITIONS FOR FILTERING TO OUTPUT FILE
        {
            outputFile << commandCheck << endl;
        }
        if (firstAndLast && (firstCount > 0 && lastCount > 0))
        {
            outputFile << commandCheck << endl;
        }
        if (hasCommand == false)
        {
            outputFile << commandCheck << endl;
        }
    }

    inputFile.close();
    outputFile.close();
    commandFile.close();

    return 0;
}



/*
command file issues with whitespace

*/