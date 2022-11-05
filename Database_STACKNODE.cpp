#include "Database_STACKNODE.h"

Database_STACKNODE::Database_STACKNODE()  //constructor of Stacknode
{
    bst_node = NULL;
    Next_Node = NULL;
}

void Database_STACKNODE::SetItem(Database_BST_Node *data) //set information to stacknode
{
    this->bst_node = data;
}

Database_BST_Node *Database_STACKNODE::GetData() //return data from stack node
{
    return this->bst_node;
}

Database_STACKNODE *Database_STACKNODE::GetNext() //return next node
{
    return this->Next_Node;
}

void Database_STACKNODE::SetNext(Database_STACKNODE *data) //set the next stacknode
{
    this->Next_Node = data;
}