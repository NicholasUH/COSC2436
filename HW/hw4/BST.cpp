#include "BST.h"
using namespace std;

BST::BST()
{
    root = nullptr;
}

void BST::postOrderTraversal(bNode *curr, ofstream &outputFile)
{
    if (curr == nullptr)
    {
        return;
    }
    if (curr != nullptr)
    {
        postOrderTraversal(curr->left, outputFile);
        postOrderTraversal(curr->right, outputFile);
        outputFile << curr->message << endl;
    }
}
void BST::preOrderTraversal(bNode *curr, ofstream &outputFile)
{
    if (curr == nullptr)
    {
        return;
    }
    if (curr != nullptr)
    {
        outputFile << curr->message << endl;
        preOrderTraversal(curr->left, outputFile);
        preOrderTraversal(curr->right, outputFile);
    }
}
void BST::inOrderTraversal(bNode *curr, ofstream &outputFile)
{
    if (curr == nullptr)
    {
        return;
    }
    if (curr != nullptr)
    {
        inOrderTraversal(curr->left, outputFile);
        outputFile << curr->message << std::endl;
        inOrderTraversal(curr->right, outputFile);
    }
}

void BST::insert(string message)
{
    bNode *temp = new bNode;
    temp->message = message;
    temp->left = temp->right = nullptr;
    if (root == nullptr)
    {
        root = temp;
    }
    else
    {
        bNode *curr = root;
        bNode *previous = new bNode;

        while (true)
        {
            previous = curr;

            if (message.length() < curr->message.length())
            {
                curr = curr->left;
                if (curr == nullptr)
                {
                    previous->left = temp;
                    return;
                }
            }
            else if (message.length() > curr->message.length())
            {
                curr = curr->right;
                if (curr == nullptr)
                {
                    previous->right = temp;
                    return;
                }
            }
            else if (message.length() == curr->message.length())
            {
                curr->message = message;
                return;
            }
        }
    }
}

bNode *BST::insertR(bNode *curr, string message)
{
    if (curr == nullptr)
    {
        bNode *temp = new bNode(message);
        if (root == nullptr)
        {
            root = temp;
            return root;
        }
        curr = temp;
    }
    else if (curr->message.length() == message.length())
    {
        curr->message = message;
    }
    else if (message.length() > curr->message.length())
    {
        curr->right = insertR(curr->right, message);
    }
    else if (message.length() < curr->message.length())
    {
        curr->left = insertR(curr->left, message);
    }
    return curr;
}

