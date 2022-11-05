#include "Database_IMAGENODE.h"

class Database_IMAGE{
private:
    int datanumbers;
    Database_IMAGENODE *First;

public:
    Database_IMAGE();
    ~Database_IMAGE();
    bool IsEmpty();
    void PUSH(Database_IMAGENODE *data);
    Database_IMAGENODE *StackPOP();
    Database_IMAGENODE *QueuePOP();
};