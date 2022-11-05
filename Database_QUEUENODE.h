#include <fstream>
#include "Database_BST_Node.h"
using namespace std;

class Database_QUEUENODE{
private:
    int Idx;
    string Name;
    Database_QUEUENODE *Next;

public:
    Database_QUEUENODE();
    void SetItem(Database_BST_Node *data);
    void SetNext(Database_QUEUENODE *data);
    int GetIndex();
    string GetName();
    Database_QUEUENODE *GetNext();
};