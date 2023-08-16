#include <iostream>
#include <fstream>
using namespace std;

struct node
{
    double val;
    node *left;
    node *right;
    node(double _val)
    {
        val = _val;
        left = right = nullptr;
    }
};

class BST
{
private:
    node *root;
    node *insert(node *, double);
    void preOrderTraversal(node *, ofstream &, string);

public:
    BST();
    void insert(double val)
    {
        insert(root, val);
    }
    void print(ofstream &outputFile)
    {
        preOrderTraversal(root, outputFile, "x");
    }
};

BST::BST()
{
    root = nullptr;
}

node *BST::insert(node *curr, double val)
{

    if (curr == nullptr)
    {
        node *temp = new node(val);
        if (root == nullptr)
        {
            root = temp;
            return root;
        }
        curr = temp;
    }
    else if (val < curr->val)
    {
        curr->left = insert(curr->left, val);
    }
    else if (val > curr->val)
    {
        curr->right = insert(curr->right, val);
    }
    return curr;
}

void BST::preOrderTraversal(node *curr, ofstream &outputFile, string location)
{
    if (curr == nullptr)
    {
        return;
    }
    else
    {
        outputFile << "[" << location << "] " << curr->val << endl;
        preOrderTraversal(curr->left, outputFile, location += "l");
        location = location.substr(0, location.length() - 1);
        preOrderTraversal(curr->right, outputFile, location += "r");
    }
}