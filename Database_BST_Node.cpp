#include "Database_BST_Node.h"

Database_BST_Node::Database_BST_Node(){ //constructor of BST node
    Left = NULL;
    Right = NULL;
}

void Database_BST_Node::SetItems(int index, string directory, string name){ //set items of bst node
    this->Idx = index;
    this->FileDir = directory;
    this->FileName = name;
}

int Database_BST_Node::GetIdx(){ //get index information of bst node
    return this->Idx;
}

string Database_BST_Node::GetDir(){ //get directory information of bst node
    return this->FileDir;
}

string Database_BST_Node::GetName(){ //get name information of bst node
    return this->FileName;
}

Database_BST_Node *Database_BST_Node::GetLeft(){ //get left node information of bst node
    return this->Left;
}

Database_BST_Node *Database_BST_Node::GetRight() //get right node information of bst node
{
    return this->Right;
}

void Database_BST_Node::SetLeft(Database_BST_Node *new_bst) //set the left node of bst node
{
    this->Left = new_bst;
}

void Database_BST_Node::SetRight(Database_BST_Node *new_bst) //set the right node of bst node
{
    this->Right = new_bst;
}