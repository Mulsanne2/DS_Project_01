#include "Database_IMAGE.h"

Database_IMAGE::Database_IMAGE(){ //constructor of database image
    First = NULL;
}

Database_IMAGE::~Database_IMAGE(){ //destructor of database image
    Database_IMAGENODE *Cur = First;
    Database_IMAGENODE *Temp;
    while (Cur){ //delete nodes until end
        Temp = Cur;
        Cur = Cur->GetNext();
        Temp->SetNext(NULL);
        delete Temp;
    }
}

bool Database_IMAGE::IsEmpty(){ //function that check if database_IMAGE has no node
    if(datanumbers==0)
        return true;
    else
        return false;
}

void Database_IMAGE::PUSH(Database_IMAGENODE *data){ //push image node into image linked list
    if (datanumbers == 0) //when it doesn't have any nodes put in first node
    {
        First = data; 
        datanumbers++;
        return;
    }

    Database_IMAGENODE *temp = First;
    while (temp->GetNext()) //put in last node
    {
        temp = temp->GetNext();
    }

    temp->SetNext(data);
    datanumbers++;
}

Database_IMAGENODE* Database_IMAGE::StackPOP(){ //pop the last node which is method of stack
    Database_IMAGENODE *Cur = First;
    Database_IMAGENODE *Prev = NULL;

    if(!Cur)
        return NULL;

    while(Cur->GetNext()){
        Prev = Cur;
        Cur = Cur->GetNext();
    }
    if(!Prev){ //if stack has only one node assign first node null
        First = NULL;
        datanumbers--;
        return Cur;
    }
    Prev->SetNext(NULL);
    datanumbers--;
    return Cur;
}


Database_IMAGENODE *Database_IMAGE::QueuePOP(){ //pop the first node
    if(First==NULL){
        return NULL;
    }

    Database_IMAGENODE *toDelete = First;
    First = toDelete->GetNext(); //move first node into next node
    datanumbers--;
    return toDelete;
}