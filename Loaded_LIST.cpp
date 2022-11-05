#include "Loaded_LIST.h"

Loaded_LIST::Loaded_LIST(){ //constructor of Loaded_LIST
    FirstMain_Node = new MainNodes;
    FirstLoadedNode = NULL;
    Datanumbers = 0;
}

//Destructor for Loaded_LIST
Loaded_LIST::~Loaded_LIST(){

    MainNodes *CurMain = FirstMain_Node; 
    
    while(CurMain){ //delete Loaded_LIST by Main node.
        Loaded_LIST_Node *CurNode = CurMain->getFirstNode();
        Loaded_LIST_Node *Temp;
        CurMain->SetFirstNode(NULL);
        while (CurNode){ //dele all the Loaded_LIST_NODE which is in the Current Main node
            Temp = CurNode;
            CurNode = CurNode->GetNextNode();
            delete Temp;
        }
        MainNodes *DeleteMain = CurMain;
        CurMain = CurMain->getNextMainNode(); //delete this Mainnode and the go to next main node
        DeleteMain->SetNextMainNode(NULL);
        delete DeleteMain;
    }
}

bool Loaded_LIST::EMPTY(MainNodes *mainnodes){ //function that returns if Loaded list is null
    if (Datanumbers == 0)
        return true;
    else
        return false;
}

bool Loaded_LIST::PUSH(MainNodes *main_node,Loaded_LIST_Node * data){ //Push data into Main main_node

    if(main_node==NULL||data==NULL){ //if main_node or data is NULL then return false
        return false;
    }

    if (Datanumbers==0) //check if array is empty
    {
        main_node->SetFirstNode(data); //set node in the first
        FirstLoadedNode = data;
        Datanumbers++;
        return true;
    }

    if(Datanumbers >=100){ //if Data is over 100 then Pop nodes before push the node
        if(!POP())
            return false;
    };

    Loaded_LIST_Node *now = main_node->getFirstNode(); 
    Loaded_LIST_Node *prev = NULL;

    if(!now){ //if first node is null then put data into first loaded node in current main node
        main_node->SetFirstNode(data);
    }
    else{ //else move to the end of node and then put the node at the end
    while(now){
        prev = now;
        now = now->GetNextNode();
    }
    prev->SetNext(data);
    }
    Datanumbers++; //increase datanumbers

    return true;
}

bool Loaded_LIST::PRINT(MainNodes *main_node) //print all the nodes in input main node
{
    ofstream flog;
    flog.open("log.txt", ios::app); //open flog to write log in the log.txt
    if (EMPTY(main_node)) //if mainnode is empty then return false
        return false;

    else{
        Loaded_LIST_Node *Now = main_node->getFirstNode(); 
        while (Now) //show all the name and idx of node until end
        {
            flog << Now->GetName() << "/" << Now->GetIdx() << endl;
            Now = Now->GetNextNode();
        }
        flog.close();
        return true;
    }

}

int Loaded_LIST::GetDatanumbers(){ //return datanumbers
    return this->Datanumbers;
}

// return the first main node
MainNodes* Loaded_LIST::getMainNode(){ 
    return this->FirstMain_Node;
}

//pop the first node from the first main node
bool Loaded_LIST::POP()
{
    if (Datanumbers==0) //if number of data is 0 then we can't pop data.
    {
        return false;
    }
    else
    {
        FirstMain_Node->SetFirstNode(FirstLoadedNode->GetNextNode()); //erase First node and set firt node into next node
        FirstLoadedNode->SetNext(NULL);
        delete FirstLoadedNode;
        FirstLoadedNode = FirstMain_Node->getFirstNode();
        Datanumbers--;
    }

    if(!FirstMain_Node->getFirstNode()){ //check First main node is empty then erase first main node and change to second main node.
        MainNodes *ToDelete = FirstMain_Node;
        MainNodes *ToFirst = FirstMain_Node->getNextMainNode();
        FirstMain_Node->SetNextMainNode(NULL);
        delete ToDelete;

        FirstMain_Node = ToFirst;
        FirstLoadedNode = FirstMain_Node->getFirstNode(); //first Loaded node will be next row node
    }

    return true;
}

void Loaded_LIST::CONNECTMAINNODE(MainNodes *main_node){ //connec new main nodes in last of main nodes
    MainNodes *prev_main = FirstMain_Node;

    while(prev_main->getNextMainNode()) //move until the last node
        prev_main = prev_main->getNextMainNode();

    prev_main->SetNextMainNode(main_node); //connect input main node into last node.
}

MainNodes* Loaded_LIST::ADDMAIN(){ //add new main nodes
    MainNodes *newMainnode = new MainNodes;
    return newMainnode;
}

MainNodes *Loaded_LIST::FINDDIR(string Directory){ //find Directory which name is string Directory
    MainNodes *FindingMain = this->FirstMain_Node;
    if(!FirstMain_Node)
        return NULL;

    while(FindingMain){ //Find Main nodes which FIledir name is Directory
        if(FindingMain->getFiledir()==Directory)
            return FindingMain;
        FindingMain = FindingMain->getNextMainNode(); //go to next main node
    }
    return NULL;
}

bool Loaded_LIST::FINDIDX(int FindingIdx){ //Find nodes which has same index with input Finding Idx.
    MainNodes *CurrentMain = FirstMain_Node;
    Loaded_LIST_Node *CurrentNode;
    while (CurrentMain) //find by Main nodes
    {
        CurrentNode = CurrentMain->getFirstNode();
        while(CurrentNode){
            if(CurrentNode->GetIdx()==FindingIdx) //if current node index is same as finding idx then return ture
                return true;
            CurrentNode = CurrentNode->GetNextNode(); //get next node
        }
        CurrentMain = CurrentMain->getNextMainNode(); //go to next main node
    }
    return false; // if we didnt't find any node which index is FindingIdx
}

bool Loaded_LIST::MODIFYNODE(Loaded_LIST_Node *new_node, MainNodes *main_node, string Name) //modify node.
{
    Loaded_LIST_Node *FindingNode = main_node->getFirstNode();

    if (!FindingNode){ //if mainnode doesn't have any node
        delete new_node;
        return false;
    }

    if (FindingNode->GetName()==Name){ //check if node is fisrt node of main nodes
        if(FirstLoadedNode->GetName()==Name){ //if node is first of all loaded list then assign FirstLoadedNode as well.
            FirstLoadedNode = new_node;
        }
        main_node->SetFirstNode(new_node);
        new_node->SetNext(FindingNode->GetNextNode()); //change first node into new node
        FindingNode->SetNext(NULL);
        delete FindingNode; //delete finding node
        return true;
    }

    Loaded_LIST_Node *prev = FindingNode;
    FindingNode = FindingNode->GetNextNode();

    while(FindingNode){ //when finding node is not at fisrt of main nodes
        if (FindingNode->GetName() == Name){
            prev->SetNext(new_node);
            new_node->SetNext(FindingNode->GetNextNode());
            FindingNode->SetNext(NULL);
            delete FindingNode;
            return true; //delete finding node
        }
        prev = FindingNode;
        FindingNode = FindingNode->GetNextNode(); //move next node until find the smae name node
    }
    return false;
}

Loaded_LIST_Node * Loaded_LIST::DELETE(){ //get the last node to delete to move to bst
    if (!FirstLoadedNode)
        return NULL;
    MainNodes *LastMain = FirstMain_Node;
    MainNodes *PrevMain = FirstMain_Node;
    Loaded_LIST_Node *LastLoad;
    Loaded_LIST_Node *PrevLoad;
    while (LastMain->getNextMainNode()) // move to end of main node
    {
        PrevMain = LastMain;
        LastMain = LastMain->getNextMainNode();
    } //get the last main node and prev last main node

    LastLoad = LastMain->getFirstNode();
    PrevLoad = LastLoad;
    if (!LastLoad) // check there is a node
        return NULL;
    while (LastLoad->GetNextNode()){ //get the last node and prev last node 
        PrevLoad = LastLoad;
        LastLoad = LastLoad->GetNextNode();
    }

    if(FirstLoadedNode==LastLoad){ //when delete node is same as FirstLoadedNode set FisrtLodednode into null
        FirstMain_Node->SetFirstNode(NULL);
        FirstLoadedNode = NULL;
        Datanumbers--;
        return LastLoad;
    }

    else if (LastLoad == PrevLoad){ // when we delete first node of it's main node
        LastMain->SetFirstNode(NULL);
        PrevMain->SetNextMainNode(NULL);
        delete LastMain;
    }

    else{ // if nodes is in normal case
        PrevLoad->SetNext(NULL);
    }
    Datanumbers--;
    return LastLoad;
}

bool Loaded_LIST::EMPTYLIST(){ //check if list is empty
    if(Datanumbers==0)
        return true;
    else
        return false;
}