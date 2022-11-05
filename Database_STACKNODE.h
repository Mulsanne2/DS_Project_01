#pragma once
#include <string>
#include <fstream>
#include "Database_BST_Node.h"
using namespace std;

class Database_STACKNODE{
private:
    Database_BST_Node *bst_node;
    Database_STACKNODE *Next_Node;

public:
    Database_STACKNODE();
    Database_BST_Node *GetData();
    Database_STACKNODE *GetNext();

    void SetItem(Database_BST_Node *data);
    void SetNext(Database_STACKNODE *data);
};