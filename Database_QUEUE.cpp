#include "Database_QUEUE.h"

Database_QUEUE::Database_QUEUE(){ //constructor of database_Queue
    Datanumbers = 0;
    First = NULL;
}

Database_QUEUE::~Database_QUEUE(){ //destructor of Database_Queue
    Database_QUEUENODE *Cur = First;
    Database_QUEUENODE *temp;
    while (Cur){ //delete node until end
        temp = Cur;
        Cur = Cur->GetNext();
        temp->SetNext(NULL);
        delete temp;
    }
}

void Database_QUEUE::PUSH(Database_BST_Node *data) //push bst node into Queue
{
    if(!data)
        return;

    Database_QUEUENODE *new_data = new Database_QUEUENODE;
    new_data->SetItem(data); //change bst node into queuenode and then push

    if (!First) //when first is null put in first node
    {
        First = new_data;
        Datanumbers++;
        return;
    }
    Database_QUEUENODE *temp = First;
    while(temp->GetNext()){ //move to the end of Queue
        temp = temp->GetNext();
    }
    temp->SetNext(new_data);
    Datanumbers++;
}

bool Database_QUEUE::BoyMoo(string inputdata){ //boyer-moore algorithm
    if(!First)
        return false;

    ofstream flog;
    flog.open("log.txt", ios::app); //open flog to write log in log.txt

    bool printstartbar = false;
    int findnum = 0;

    Database_QUEUENODE *temp = First;
    while(temp){ //find until the stack ends
        string namedata = temp->GetName();
        int len1 = inputdata.length();
        int len2 = namedata.length();
        char *Word1 = new char[len1+1]; // use dynamical allocater to compare char one by one
        char *Word2 = new char[len2+1];

        strcpy(Word1, inputdata.c_str());
        strcpy(Word2, namedata.c_str());

        Word1[len1] = '\0'; //put null on the end which is end of string
        Word2[len2] = '\0';

        int same = 0;
        for (int i = 0; i < len2 - len1 + 1; i++) //compare char by char from first
        {
            same = 0;
            for (int j = 0; j < len1; j++) //compare until length of input
            {
                if(Word1[j] != Word2[i + j]){
                    break;
                }
                same++;

            }
            if (same == len1) // if we find the word
            { 
                break;
            }
            else{
                i += same;
            }
        }

        delete[] Word1; //delete char pointer which uses dynamically allocate
        delete[] Word2;

        if(printstartbar==false && same==len1){ //if we find the word then write log that we found
            printstartbar = true;
            flog << "=========SEARCH=========" << endl;
        }
        if(same==len1){
            flog << "\"" << temp->GetName() << "\" / " << temp->GetIndex() << endl; // print the result that include word
            findnum++;
        }

        temp = POP(); // Pop the stack
    }

    if(findnum!=0){
        flog << "=====================" << endl
             << endl;
        flog.close();
        return true;
    }
    else{
        flog.close(); //close the flog
        return false;
    }
}

Database_QUEUENODE *Database_QUEUE::POP(){ //Pop the first and then return the next node
    if(Datanumbers==0) //check if Queue is empty
        return NULL;

    Database_QUEUENODE *toDelete = First;
    Database_QUEUENODE *temp = toDelete->GetNext();
    First = temp;
    toDelete->SetNext(NULL);
    delete toDelete;
    Datanumbers--;
    return temp;
}