#pragma once
#include "Database_STACKNODE.h"
using namespace std;

class Database_STACK
{
private:
    int Datanumbers;
    Database_STACKNODE *FIRST;
    Database_STACKNODE *LAST;

public:
    Database_STACK();
    bool IsEmpty();

    Database_STACKNODE *GetLast();

    void Push(Database_BST_Node *data);
    Database_STACKNODE *Pop();
};