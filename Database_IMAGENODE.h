#pragma once
#include<fstream>
using namespace std;

class Database_IMAGENODE{
private:
    unsigned char Pixel;
    Database_IMAGENODE *Next;

public:
    Database_IMAGENODE();
    void SetPixel(int num);
    void SetNext(Database_IMAGENODE *data);
    unsigned char GetPixel();
    Database_IMAGENODE *GetNext();
};