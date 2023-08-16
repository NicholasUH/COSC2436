#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <algorithm>
#include "ArgumentManager.h"

bool BFS(int **graph, int start, int end, int numOfNodes)
{
  queue<int> q;
  bool *visited = new bool[numOfNodes];

  for (int i = 0; i < numOfNodes; i++)
  {
    visited[i] = false;
  }

  q.push(start);
  int currentNode = 0;

  while (!q.empty())
  {
    currentNode = q.front();
    q.pop();

    if (currentNode == end)
    {
      delete[] visited;
      return true;
    }

    else if (!visited[currentNode])
    {
      visited[currentNode] = true;
    }

    for (int i = 0; i < numOfNodes; i++)
    {
      if (graph[currentNode][i] != 0 && !visited[i])
      {
        q.push(i);
      }
    }
  }

  delete[] visited;
  return false;
}

bool DFS(int **graph, int start, int end, int numOfNodes)
{
  stack<int> q;
  bool *visited = new bool[numOfNodes];

  for (int i = 0; i < numOfNodes; i++)
  {
    visited[i] = false;
  }

  q.push(start);
  int currentNode = 0;

  while (!q.empty())
  {
    currentNode = q.top();
    q.pop();

    if (currentNode == end)
    {
      delete[] visited;
      return true;
    }

    else if (!visited[currentNode])
    {
      visited[currentNode] = true;
    }

    for (int i = 0; i < numOfNodes; i++)
    {
      if (graph[currentNode][i] != 0 && !visited[i])
      {
        q.push(i);
      }
    }
  }

  delete[] visited;
  return false;
}

int main(int argc, char *argv[])
{
  ArgumentManager am(argc, argv);
  ifstream inputFile(am.get("input"));
  ofstream outputFile(am.get("output"));

  int numOfNodes, start, end, node1, node2 = 0;
  string inStr = "";

  inputFile >> numOfNodes;
  int **graph = new int *[numOfNodes];

  for (int i = 0; i < numOfNodes; i++)
  {
    graph[i] = new int[numOfNodes];
  }

  for (int i = 0; i < numOfNodes; i++)
  {
    for (int j = 0; j < numOfNodes; j++)
    {
      graph[i][j] = 0;
    }
  }

  inputFile >> start;
  inputFile >> end;

  while (getline(inputFile, inStr))
  {
    inStr.erase(remove(inStr.begin(), inStr.end(), '\n'), inStr.end());
    inStr.erase(remove(inStr.begin(), inStr.end(), '\r'), inStr.end());

    if (inStr == " " || inStr.length() == 0)
    {
      continue;
    }
    else
    {
      node1 = stoi(inStr.substr(0, inStr.find(' ')));
      node2 = stoi(inStr.substr(inStr.find(' ') + 1, inStr.length() - inStr.find(' ') - 1));
    }
    graph[node1][node2] = 1;
    graph[node2][node1] = 1;
  }

  if (BFS(graph, start, end, numOfNodes) || DFS(graph, start, end, numOfNodes))
  {
    outputFile << "true" << endl;
  }

  else
    outputFile << "false" << endl;

  return 0;
}