#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string.h>
using namespace std;

class Loaded_LIST_Node{
private:
    string Name;
    string Directory;
    int Idx;
    Loaded_LIST_Node * p_Next;

public:

    Loaded_LIST_Node();
    void SetItems(string name, string dir, int Idx);
    void SetNext(Loaded_LIST_Node *P_Next);
    string GetName();
    string GetDirectory();
    int GetIdx();
    Loaded_LIST_Node *GetNextNode();
};

class MainNodes
{
private:
    string Filedir;
    Loaded_LIST_Node *FirstNode;
    MainNodes *nextList;

public:
    MainNodes();
    void SetFiledir(string dirname);
    void SetFirstNode(Loaded_LIST_Node *data);
    string getFiledir();
    Loaded_LIST_Node *getFirstNode();
    MainNodes *getNextMainNode();
    void SetNextMainNode(MainNodes *data);
};
