#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Loaded_LIST_Node.h"
#include <fstream>
using namespace std;

class Loaded_LIST{
private:
    MainNodes *FirstMain_Node;
    Loaded_LIST_Node *FirstLoadedNode;
    int Datanumbers;

public:

    Loaded_LIST();
    ~Loaded_LIST();

    bool PUSH(MainNodes *main_node, Loaded_LIST_Node *data);
    bool POP();
    bool PRINT(MainNodes *main_node);
    bool EMPTY(MainNodes *main_node);
    int GetDatanumbers();
    MainNodes *getMainNode();
    MainNodes *ADDMAIN();
    void CONNECTMAINNODE(MainNodes *main_node);
    

    MainNodes *FINDDIR(string Directory);
    bool FINDIDX(int FindingIdx);
    bool MODIFYNODE(Loaded_LIST_Node *new_node, MainNodes *main_node, string Name);

    Loaded_LIST_Node *DELETE();
    bool EMPTYLIST();
};