#include "Loaded_LIST_Node.h"

Loaded_LIST_Node::Loaded_LIST_Node(){ //constructor of Loaded List Node
    Idx = 0;
    p_Next = NULL;
}

void Loaded_LIST_Node::SetItems(string name,string dir, int Idx) //set name and directory and index information into node
{
    Name = name;
    Directory = dir;
    this->Idx = Idx;
}

void Loaded_LIST_Node::SetNext(Loaded_LIST_Node *P_Next){ //set next node
    this->p_Next = P_Next;
}

string Loaded_LIST_Node::GetName(){ //get name information of node
    return this->Name;
}

string Loaded_LIST_Node::GetDirectory(){ //get directory information of node
    return this->Directory;
}

int Loaded_LIST_Node::GetIdx(){ //get index information of node
    return this->Idx;
}

Loaded_LIST_Node* Loaded_LIST_Node::GetNextNode(){ //get next node information of node
    return this->p_Next;
}


MainNodes::MainNodes(){ //constructor of Mainnodes
    FirstNode = NULL;
    nextList = NULL;
}

void MainNodes::SetFiledir(string dirname){ //set directory information into Mainnode
    this->Filedir = dirname;
}

void MainNodes::SetFirstNode(Loaded_LIST_Node *data){ //set first main node
    this->FirstNode = data;
}

string MainNodes::getFiledir(){ //get directory of files of main node
    return this->Filedir;
}

Loaded_LIST_Node * MainNodes::getFirstNode(){ //get first node of it's main node
    return this->FirstNode;
}

MainNodes *MainNodes::getNextMainNode(){ //get next main node
    return this->nextList;
}

void MainNodes::SetNextMainNode(MainNodes *data){ //set next main node
    this->nextList = data;
}