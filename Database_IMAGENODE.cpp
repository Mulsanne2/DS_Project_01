#include "Database_IMAGENODE.h"

Database_IMAGENODE::Database_IMAGENODE(){ //constructor for database_imagenode
    Next = NULL;
}

void Database_IMAGENODE::SetPixel(int num){ //set pixel information
    Pixel = num;
}

void Database_IMAGENODE::SetNext(Database_IMAGENODE *data){ //set next node
    Next = data;
}

unsigned char Database_IMAGENODE::GetPixel(){ //get pixel information from node
    return this->Pixel;
}

Database_IMAGENODE *Database_IMAGENODE::GetNext(){
    return this->Next;
}