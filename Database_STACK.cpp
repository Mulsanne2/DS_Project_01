#include "Database_STACK.h"

Database_STACK::Database_STACK() //constructor of databse stack
{
    Datanumbers = 0;
    FIRST = NULL;
    LAST = NULL;
}

bool Database_STACK::IsEmpty(){ //function which return stack is empty
    if(Datanumbers==0)
        return true;
    else
        return false;
}

Database_STACKNODE *Database_STACK::GetLast(){ //function that returns last stack node
    return LAST;
}

void Database_STACK::Push(Database_BST_Node *data){ //push data into stack
    if(data ==NULL)
        return;

    Database_STACKNODE *new_node = new Database_STACKNODE; 
    new_node->SetItem(data); //store bst node data into stack node

    if(FIRST==NULL){ //if first node is null then assign new node into first node
        FIRST = new_node;
        LAST = new_node;
        Datanumbers++;
        return;
    }

    Database_STACKNODE *temp = FIRST;


    while(temp->GetNext()){ //move node until end
            temp = temp->GetNext();
    }
    temp->SetNext(new_node); //set new node in the end
    LAST = new_node;
    Datanumbers++;
}

Database_STACKNODE *Database_STACK::Pop(){ //function that pop the node from stack
    if(IsEmpty())
        return NULL;

    Database_STACKNODE *toPop = FIRST;
    Database_STACKNODE *prev = NULL;
    if (Datanumbers == 1) //if stack has only one data then pop the first node
    {
        FIRST = NULL;
        Datanumbers--;
        return toPop;
    }

    prev = FIRST;
    while(toPop->GetNext()){ //go to least node to pop
        prev = toPop;
        toPop = toPop->GetNext();
    }
    prev->SetNext(NULL);
    LAST = prev; //last will be previous node of end node
    Datanumbers--;
    return toPop;
}