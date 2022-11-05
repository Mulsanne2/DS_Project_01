#pragma once
#include <cstring>
#include <string>
using namespace std;

class Database_BST_Node
{
private:
    int Idx;
    string FileDir;
    string FileName;

    Database_BST_Node *Left;
    Database_BST_Node *Right;

public:
    Database_BST_Node();

    void SetItems(int index, string directory, string name);
    int GetIdx();
    string GetDir();
    string GetName();
    Database_BST_Node *GetLeft();
    Database_BST_Node *GetRight();

    void SetLeft(Database_BST_Node *new_bst);
    void SetRight(Database_BST_Node *new_bst);
};