#pragma once
#include "Database_QUEUENODE.h"
using namespace std;

class Database_QUEUE
{
private:
    Database_QUEUENODE *First;
    int Datanumbers;

public:
    Database_QUEUE();
    ~Database_QUEUE();
    void PUSH(Database_BST_Node *data);
    bool BoyMoo(string Word);
    Database_QUEUENODE *POP();
};