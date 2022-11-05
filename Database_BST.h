#pragma once
#include <cstring>
#include <fstream>
#include "Database_BST_Node.h"
#include "Loaded_LIST_Node.h"
#include "Database_STACK.h"
#include "Database_QUEUE.h"
using namespace std;

class Database_BST{
private:
    int Datanumbers;
    Database_BST_Node *Root;
    Database_STACK *STKptr;

public:
    Database_BST();
    ~Database_BST();
    Database_BST_Node *GetRoot();
    int GetNumber();

    bool Insert(Database_BST_Node *data);
    void PrintInorder(Database_BST_Node *now);
    void CheckDuplicate(Database_BST_Node *now, string name, int idx,int *duplicate);
    void Erase(Database_BST_Node *ToStart); //Erase Node

    bool BST_Postorder(Database_BST_Node *ToStart, Database_QUEUE *ptr);
    Database_BST_Node* BST_Preorder(int Findex, Database_BST_Node *store, Database_BST_Node *cur);
};