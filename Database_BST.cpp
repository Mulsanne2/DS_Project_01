#include "Database_BST.h"

Database_BST::Database_BST(){ //constructor of database_BST
    Datanumbers = 0;
    Root = NULL;
    STKptr = new Database_STACK;
}

Database_BST::~Database_BST(){ //destructor of database Bst
    Database_BST_Node *Cur = Root;
    while(Datanumbers!=0){ //erase all the bst nodes until total nodes become zero
        Erase(Root);
    }
    delete STKptr;
}

Database_BST_Node *Database_BST::GetRoot(){ //get the root of binary search tree
    return this->Root;
}

int Database_BST::GetNumber(){ //get total nodes number of binary search tree
    return this->Datanumbers;
}

bool Database_BST::Insert(Database_BST_Node *data){ //insert node into binary search tree
    
    if(data == NULL) //check data has data
        return false;

    else if(Root ==NULL) //when BST is empty then put in Root node
    {
        Root = data;
        Datanumbers++;
        return true;
    }

    Database_BST_Node *temp = Root;
    Database_BST_Node *prev = Root;
    int direction = 0;

    while(temp){ //comparing the index and repeat until go to the leaf node
        if(data->GetIdx() < temp->GetIdx()){
            prev = temp;
            temp = temp->GetLeft();
            direction = 1;
        }
        else if(temp->GetIdx() < data->GetIdx()){
            prev = temp;
            temp = temp->GetRight();
            direction = 2;
        }
    }

    if (direction == 0) // if we can't find direction return false
        return false;
    if (direction == 1) //put data into left side
        prev->SetLeft(data);
    else if (direction == 2) //put data into right side
        prev->SetRight(data);

    Datanumbers++; //increase data numbers
    return true;
}

void Database_BST::PrintInorder(Database_BST_Node *now ){ //print all the data in the bst, by inorder
    ofstream flog;
    flog.open("log.txt", ios::app); //open flog to write log
    if (now == NULL)
        return;
    else{
        PrintInorder(now->GetLeft());
        flog << now->GetDir() << " / \"" << now->GetName() << "\" / " << now->GetIdx() << endl; //write all the prints of bst
        PrintInorder(now->GetRight());
    }

    flog.close();
}

// check it all the bst nodes if it has same name or index using recursive function
// check in in-order
void Database_BST::CheckDuplicate(Database_BST_Node *now, string name, int idx, int *duplicate) 
{
    if (!now)
        return;
    else
    {
        CheckDuplicate(now->GetLeft(), name, idx, duplicate); //use reculsive function
        if (now->GetIdx() == idx || now->GetName() == name)
            (*duplicate)++;
        CheckDuplicate(now->GetRight(), name, idx, duplicate); //use reculsive function
    }
}

void Database_BST::Erase(Database_BST_Node *FindStart) //when number of bst node is over 300 erase the smallest node of binary search tree
{
    if(Root==NULL)
        return;
    
    //Find Minimum Node
    Database_BST_Node *toErase = FindStart;
    Database_BST_Node *prev = NULL;
    while(toErase->GetLeft()){
        prev = toErase;
        toErase = toErase->GetLeft();
    }

    if(toErase==Root){ //when it has only one node which is root
        Root = toErase->GetRight();
        Datanumbers--;
        delete toErase;
    }
    else if(toErase->GetLeft()==NULL&& toErase->GetRight()==NULL){ //when erase node is leaf
        prev->SetLeft(NULL);
        Datanumbers--;
        delete toErase;
    }
    else if(toErase->GetLeft()==NULL){ //when erase node has only right node
        prev->SetLeft(toErase->GetRight());
        Datanumbers--;
        delete toErase;
    }
}

// visit tree in post-order using stack and store into Queue
bool Database_BST::BST_Postorder(Database_BST_Node *ToStart, Database_QUEUE *ptr)
{

    Database_BST_Node *Current = ToStart;
    if (!Current)
        return false;

    while (Current != NULL || !STKptr->IsEmpty())
    {
        if (Current != NULL) //Move to smallest node 
        {
            STKptr->Push(Current);
            Current = Current->GetLeft();
        }

        else
        {
            Database_STACKNODE *toDelNode;
            Database_BST_Node *temp = STKptr->GetLast()->GetData()->GetRight(); //check previous node has right node //이전꺼의 오른쪽 확인
            if (temp == NULL) //it doesn't have previous node has right side
            {
                // temp = STKptr->Pop()->GetData(); //하나씩 튀어나오는 부분
                toDelNode = STKptr->Pop(); //then we can erase it's node
                temp = toDelNode->GetData();
                ptr->PUSH(temp); //push information into Queue
                toDelNode->SetItem(NULL); //prepare to delete it's node
                delete toDelNode;

                while (!STKptr->IsEmpty() && temp == STKptr->GetLast()->GetData()->GetRight()) //if deleted node was the right side delete one more time // right가 자신인 경우 그냥 지운다.
                {
                    // temp = STKptr->Pop()->GetData();
                    toDelNode = STKptr->Pop();
                    temp = toDelNode->GetData();
                    ptr->PUSH(temp); //push data in the Queue 원래있었음
                    toDelNode->SetItem(NULL); //prepare to delete it's node
                    delete toDelNode;
                }
            }
            else //visit the right side//오른쪽께 있으면 오른쪽 꺼부터 방문
            {
                Current = temp;
            }
        }
    }

    return true;
}

Database_BST_Node* Database_BST::BST_Preorder(int Findex, Database_BST_Node *store, Database_BST_Node *cur) //find bstnode which has same index using recursive funtion in pre-order
{
    if(cur){
        if(cur->GetIdx() ==Findex){
            store=cur;
            return store;
        }
        store = BST_Preorder(Findex, store, cur->GetLeft());
        store = BST_Preorder(Findex, store, cur->GetRight());
    }
    return store;
}