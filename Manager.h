#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include "Loaded_LIST.h"
#include "Database_BST.h"
#include "Database_QUEUE.h"
#include "Database_IMAGE.h"
using namespace std;

class Manager{
private:
    Loaded_LIST *LISTptr;
    Database_BST *BSTptr;
    Database_QUEUE *QUEptr;
    Database_IMAGE *IMGptr;
    ifstream fin;
    ofstream flog;
    FILE *GetImage;
    string ImageName;
    unsigned char IMG[256][256];

public:
    Manager();
    ~Manager();

    void Run(const char *filepath);
    bool LOAD();
    bool ADD(char * str);
    bool MODIFY(char *str);
    bool MOVE();
    bool PRINT();
    bool SEARCH(char *str);
    bool SELECT(char *str);
    bool EDIT(char *str);
    void EXIT();

    void PrintError(int num);
    void PrintSuccess(string str);
};