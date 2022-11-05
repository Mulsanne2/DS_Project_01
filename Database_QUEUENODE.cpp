#include "Database_QUEUENODE.h"

Database_QUEUENODE::Database_QUEUENODE(){ //constructor of Database_QUEUENODE
    Next = NULL;
}

void Database_QUEUENODE::SetItem(Database_BST_Node *data) //set name and index information from bst node
{
    Name = data->GetName();
    Idx = data->GetIdx();
}

void Database_QUEUENODE::SetNext(Database_QUEUENODE *data){ //set next Queuenode
    Next = data;
}

int Database_QUEUENODE::GetIndex() //return node's index
{
    return this->Idx;
}

string Database_QUEUENODE::GetName(){ //return node's Name
    return this->Name;
}

Database_QUEUENODE *Database_QUEUENODE::GetNext(){ //return node's nex pointing node
    return this->Next;
}