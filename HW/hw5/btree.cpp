#include "btree.h"

void bubbleSort(vector<int> &keys, int length)
{
    bool isSorted = true;
    string sorted = "";
    for (int x = 0; x < length - 1; ++x)
    {
        for (int y = 0; y < length - x - 1; ++y)
        {
            if (keys.at(y) > keys.at(y + 1))
            {
                int temp = keys.at(y);
                keys.at(y) = keys.at(y + 1);
                keys.at(y + 1) = temp;
                isSorted = false;
            }
        }
        if (isSorted == true)
        {
            break;
        }
    }
}

BTree::BTree(int degree)
{
    this->degree = degree;
    node *temp = new node(true, nullptr);
    root = temp;
}

void BTree::insertAtLeaf(node *curr, int key)
{
    if (curr->isLeaf == true)
    {
        insertKey(curr, key);
    }
    else
    {
        int insertIndex = 0;
        while (insertIndex < curr->keys.size() && key > curr->keys.at(insertIndex))
        {
            ++insertIndex;
        }
        insertAtLeaf(curr->children.at(insertIndex), key);
    }
}

void BTree::insertKey(node *curr, int key)
{
    curr->keys.push_back(key);
    bubbleSort(curr->keys, curr->keys.size());
    if (curr == root)
    {
        splitRoot(curr);
    }
    else
    {
        splitNode(curr);
    }
}

void BTree::splitNode(node *curr)
{
    if (curr->keys.size() < degree)
    {
        return;
    }
    else
    {
        node *left = new node(curr->isLeaf, curr->parentNode);

        int middle = (degree - 1) / 2;
        int rootKey = curr->keys.at(middle);

        for (int x = 0; x < middle; ++x)
        {
            insertKey(left, curr->keys.at(x));
        }
        for (int x = 0; x <= middle; ++x)
        {
            curr->keys.erase(curr->keys.begin());
        }

        if (curr->isLeaf == false)
        {
            for (int x = 0; x <= middle; ++x)
            {
                curr->children.at(x)->parentNode = left;
                left->children.push_back(curr->children.at(x));
            }
            for (int x = 0; x <= middle; ++x)
            {
                curr->children.erase(curr->children.begin());
            }
        }
        curr->parentNode->children.insert(find(curr->parentNode->children.begin(), curr->parentNode->children.end(), curr), left);
        insertKey(curr->parentNode, rootKey);
    }
}

void BTree::splitRoot(node *curr)
{
    if (curr->keys.size() < degree)
    {
        return;
    }
    else
    {
        node *newRoot = new node(false, nullptr);
        node *left = new node(curr->isLeaf, curr->parentNode);

        int middle = (degree - 1) / 2;
        int rootKey = curr->keys.at(middle);

        for (int x = 0; x < middle; ++x)
        {
            insertKey(left, curr->keys.at(x));
        }
        for (int x = 0; x <= middle; ++x)
        {
            curr->keys.erase(curr->keys.begin());
        }

        if (curr->isLeaf == false)
        {
            for (int x = 0; x <= middle; ++x)
            {
                curr->children.at(x)->parentNode = left;
                left->children.push_back(curr->children.at(x));
            }
            for (int x = 0; x <= middle; ++x)
            {
                curr->children.erase(curr->children.begin());
            }
        }

        left->parentNode = newRoot;
        curr->parentNode = newRoot;

        newRoot->children.push_back(left);
        newRoot->children.push_back(curr);

        insertKey(newRoot, rootKey);

        root = newRoot;
    }
}

bool BTree::duplicateCheck(node *curr, int val)
{
    if (curr == nullptr)
    {
        return false;
    }
    else
    {
        for (int x = 0; x < curr->keys.size(); ++x)
        {
            if (curr->keys.at(x) == val)
            {
                return true;
            }
        }
        for (int x = 0; x < curr->children.size(); ++x)
        {
            if (duplicateCheck(curr->children.at(x), val) == true)
            {
                return true;
            }
        }
        return false;
    }
}

void BTree::printLevel(node *curr, ofstream &outputFile, int targetLevel)
{
    if (curr == nullptr)
    {
        return;
    }
    else if (this->getHeight(this->root) < targetLevel || root->keys.empty())
    {
        outputFile << "Empty";
    }
    else if (targetLevel == 1)
    {
        for (int x = 0; x < curr->keys.size(); ++x)
        {
            outputFile << curr->keys.at(x) << " ";
        }
    }
    else if (curr->isLeaf == false && targetLevel > 1)
    {
        for (int x = 0; x < curr->children.size(); ++x)
        {
            printLevel(curr->children.at(x), outputFile, targetLevel - 1);
        }
    }
}

int BTree::getHeight(node *curr)
{
    if(root->keys.empty()){
        return 0;
    }
    else if (curr == nullptr)
    {
        return 0;
    }
    else if (curr->isLeaf == false)
    {
        return 1 + getHeight(curr->children.at(0));
    }
    else if (curr->isLeaf == true)
    {
        return 1;
    }
    else{
        return 0;
    }
}