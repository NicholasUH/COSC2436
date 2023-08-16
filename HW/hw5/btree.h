#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct node
{
    vector<int> keys;
    vector<node *> children;
    node *parentNode;
    bool isLeaf;
    node(bool leaf, node *parent)
    {
        this->parentNode = parent;
        this->isLeaf = leaf;
    }
};

class BTree
{
private:
    node *root;
    int degree;
    void insertAtLeaf(node *, int);
    void insertKey(node *, int);
    void splitNode(node *);
    void splitRoot(node *);
    void printLevel(node *, ofstream &, int);
    int getHeight(node *);
    bool duplicateCheck(node *, int);

public:
    BTree(int degree);

    void insert(int key)
    {
        insertAtLeaf(root, key);
    }
    void printLevel(ofstream &outputFile, int targetLevel)
    {
        printLevel(root, outputFile, targetLevel);
    }
    int getHeight()
    {
        return getHeight(root);
    }
    bool hasDupe(int val)
    {
        return duplicateCheck(root, val);
    }
};