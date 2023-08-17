#ifndef _BST_H
#define _BST_H
#include <iostream>
#include <fstream>
using namespace std;

struct bNode
{

    string message;
    bNode *left;
    bNode *right;
    bNode() {}
    bNode(string _message)
    {
        message = _message;
        left = right = nullptr;
    }
};

class BST
{
private:
    bNode *root;

public:
    BST();
    void insert(string);
    bNode *insertR(bNode *, string);
    bNode *getRoot() { return root; }
    void inOrderTraversal(bNode *, ofstream &);
    void preOrderTraversal(bNode *, ofstream &);
    void postOrderTraversal(bNode *, ofstream &);
};
#endif