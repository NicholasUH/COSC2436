#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

struct node
{
	double data;
	node *left;
	node *right;
	int height;
	node(double d)
	{
		data = d;
		left = nullptr;
		right = nullptr;
		height = 0;
	}
};

class AVL
{
private:
	node *root;

public:
	AVL() { root = nullptr; }

	void add(double data) { root = insert(root, data); }

	node *getRoot() { return root; }

	node *insert(node *curr, double x)
	{
		if (curr == nullptr)
			curr = new node(x);
		else if (x < curr->data)
		{
			curr->left = insert(curr->left, x);
			if (bFactor(curr) >= 2)
			{
				if (x < curr->left->data)
					curr = singleRight(curr);
				else
					curr = leftRight(curr);
			}
		}
		else if (x > curr->data)
		{
			curr->right = insert(curr->right, x);
			if (bFactor(curr) <= -2)
			{
				if (x > curr->right->data)
					curr = singleLeft(curr);
				else
					curr = rightLeft(curr);
			}
		}
		curr->height = max(height(curr->left), height(curr->right)) + 1;
		return curr;
	}

	node *singleRight(node *curr)
	{
		node *u = curr->left;
		curr->left = u->right;
		u->right = curr;
		curr->height = max(height(curr->left), height(curr->right)) + 1;
		u->height = max(height(u->left), height(u->right)) + 1;
		return u;
	}

	node *singleLeft(node *curr)
	{
		node *u = curr->right;
		curr->right = u->left;
		u->left = curr;
		curr->height = max(height(curr->left), height(curr->right)) + 1;
		u->height = max(height(u->left), height(u->right)) + 1;
		return u;
	}

	node *leftRight(node *curr)
	{
		curr->left = singleLeft(curr->left);
		return singleRight(curr);
	}

	node *rightLeft(node *curr)
	{
		curr->right = singleRight(curr->right);
		return singleLeft(curr);
	}

	int height(node *curr)
	{
		if (curr == nullptr)
			return -1;
		else
			return curr->height;
	}

	int bFactor(node *curr)
	{
		return (height(curr->left) - height(curr->right));
	}

	void printLevelOrder(node *curr, ofstream &outputFile, int numOfNodes)
	{
		if (curr == nullptr)
		{
			return;
		}

		queue<node *> q;
		q.push(curr);
		while (!q.empty())
		{
			int levelSize = q.size();
			for (int x = 0; x < levelSize; x++)
			{
				node *temp = q.front();
				q.pop();
				numOfNodes--;
				if(numOfNodes != 0){
					outputFile << temp->data << " ";
				}
				else{
					outputFile << temp->data;
				}
				if (temp->left != nullptr)
				{
					q.push(temp->left);
				}
				if (temp->right != nullptr)
				{
					q.push(temp->right);
				}
			}
		}
	}
	
	void print(ofstream &outputFile,int numOfNodes){
		printLevelOrder(root, outputFile,numOfNodes);
	}
};
