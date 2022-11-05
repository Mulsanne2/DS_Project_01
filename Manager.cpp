#include "Manager.h"


Manager::Manager(){
    LISTptr = new Loaded_LIST;
    BSTptr = new Database_BST;
    QUEptr = new Database_QUEUE;
    IMGptr = new Database_IMAGE;
}

Manager::~Manager(){
}


void Manager::Run(const char *filepath)
{
    
    ifstream fcommand("command.txt"); //command is on same directory
    flog.open("log.txt", ios::app);

    if (!fcommand) // if can't find the command txt exit the function
    {
        flog << "File Open Error" << endl;
        EXIT();
        return;
    }

    string com_input;
    while(!fcommand.eof()){ //read until command.txt file ends
        getline(fcommand, com_input);

        char *command = new char[com_input.length()];
        strcpy(command, com_input.c_str());

        if(command[0]==0)
            continue;
        char *temp = strtok(command, " "); //cut string by space and compare with instructions

        if (strcmp(temp,"LOAD")==0) //check if instruction is LOAD
        {
            if (LOAD())
            {
                flog << "=======LOAD=======" << endl;
                LISTptr->PRINT(LISTptr->getMainNode());
                flog << "=====================" << endl
                     << endl;
            }
            else{
                PrintError(100);
            }
        }
        else if(strcmp(temp,"ADD")==0){ //check if instruction is ADD
            temp = strtok(NULL, " ");
            if(ADD(temp)){ //execute ADD
                PrintSuccess("ADD");
            }
            else{
                PrintError(200);
            }
        }
        else if (strcmp(temp, "MODIFY") == 0) // check if instruction is MODIFY
        {
            temp = strtok(NULL , " ");
            if(MODIFY(temp)){ //execute MODIFY
                PrintSuccess("MODIFY");
            }
            else{
                PrintError(300);
            }
        }
        else if (strcmp(temp, "MOVE") == 0) // check if instruction is MOVE
        {
            if(MOVE()){ //execute MOVE
                PrintSuccess("MOVE");
            }
            else{
                PrintError(400);
            }
        }
        else if (strcmp(temp, "PRINT") == 0) // check if instruction is MOVE
        {
            if(BSTptr->GetRoot()) //execute PRINT
                PRINT();
            else{
                PrintError(500);
            }
        }
        else if (strcmp(temp, "SEARCH") == 0) // check if instruction is SEARCH
        {
            temp = strtok(NULL, "");
            if (!SEARCH(temp)) //execute SEARCH
                PrintError(600);
        }
        else if(strcmp(temp,"SELECT")==0){ //check if instruction is SELECT
            temp = strtok(NULL, " ");
            if(SELECT(temp)){
                PrintSuccess("SELECT");
            }
            else{
                PrintError(700);
            }
        }
        else if(strcmp(temp,"EDIT")==0){ //check if instruction is EDIT
            temp = strtok(NULL, " ");
            if(EDIT(temp)){ //execute EDIT
                PrintSuccess("EDIT");
            }
            else{
                PrintError(800);
            }
        }
        else if(strcmp(temp,"EXIT")==0){ //check if instruction is EXIT
            EXIT(); //execute EXIT
        }
        else{ //else print error 777
            PrintError(777);
        }

        delete[] command;
    }

    fcommand.close();
    flog.close();
}

bool Manager::LOAD(){
    fstream fread;

    fread.open("img_files/filesnumbers.csv", ios::in); //open filesnumbers.csv in img_files/filesnumbers.csv

    if (!fread) //validation when csv file does not open
    {
        return false;
    }

    if (LISTptr->getMainNode()->getFirstNode()) // check if LOAD already done
    {
        return false;
    }

    while (!fread.eof()) //read csv files until end
    {
        int idxnumber = 0;
        int startidx = 0, endidx = 0;
        string read_Index;
        string temp_strname, read_name;
        string SetFiledir = "img_files"; //set load default file directory img_files

        getline(fread, read_Index, ','); //read until number
        int num_length = read_Index.length();
        char *temp_number = new char[read_Index.length()];
        strcpy(temp_number, read_Index.c_str());

        if (temp_number[0] == 0) // continue when line is null
            continue;

        for (int i = 0; i < num_length;i++){ //delete strange word before number
            if(48<=temp_number[i]&&temp_number[i]<=57){ //check number
            startidx = i;
            break;
            }
        }

        delete[] temp_number;

        read_Index = read_Index.substr(startidx, read_Index.length()); //cut the string from number to end
        idxnumber = stoi(read_Index); //change char index into int index number

        //read file name
        getline(fread, temp_strname);
        int deletenumber = temp_strname.find(".RAW");
        if (deletenumber == -1) // if name doesn't have .RAW name return false
            return false;

        temp_strname = temp_strname.substr(0, deletenumber); //cut the string
        read_name = temp_strname;

        LISTptr->getMainNode()->SetFiledir(SetFiledir);

        // store name and index number using linked list
        Loaded_LIST_Node *new_node = new Loaded_LIST_Node;
        new_node->SetItems(read_name, SetFiledir, idxnumber);
        LISTptr->PUSH(LISTptr->getMainNode(), new_node); //Push new loaded list node into first node
    }

    fread.close();
    return true;
    
}

bool Manager::ADD(char * str) //ADD instruction
{
    char *FileDir = str; //get file directory
    str = strtok(NULL, " ");
    char *FileName = str; //get file name 

    if(LISTptr->GetDatanumbers()==0){ //Check if LOAD already done
        return false;
    }

    if(FileDir ==NULL || FileName==NULL) //check if name or directory information is null
        return false;

    string checkName = FileName;
    if (checkName.find(".csv") == string::npos) //if there is .csv inthe FileName
        return false;

    string tempDir = FileDir;
    string TOOPENFILE = tempDir.append("/")+FileName; //open file Filedir/Filename

    fstream fread;
    fread.open(TOOPENFILE, ios::in); //open which is in the command

    if (!fread) // validation when csv file does not open
    {
        return false;
    }

    MainNodes * new_main = LISTptr->ADDMAIN(); // add main node
    LISTptr->CONNECTMAINNODE(new_main); //connect main node

    new_main->SetFiledir(FileDir);

    
    
    while (!fread.eof()) // read csv files until end
    {
        int idxnumber = 0;
        int startidx = 0, endidx = 0;
        string read_Index;
        string temp_strname, read_name;

        getline(fread, read_Index, ',');      // read until number
        int num_length = read_Index.length(); 
        char *temp_number = new char[num_length];
        strcpy(temp_number, read_Index.c_str());

        if (temp_number[0] == 0) // continue when line is null
            continue;

        for (int i = 0; i < num_length; i++) // delete strange word before number
        { 
            if (48 <= temp_number[i] && temp_number[i] <= 57) //check number
            {
                startidx = i;
                break;
            }
            if(i==num_length-1){ //if it doesn't contain number validation
                delete new_main;
                delete[] temp_number;
                return false;
            }
        }
        delete[] temp_number;

        read_Index = read_Index.substr(startidx, read_Index.length()); // cut the string from number to end
        idxnumber = stoi(read_Index);                                  // change char index into int index number

        // read file name
        getline(fread, temp_strname);
        int deletenumber = temp_strname.find(".RAW");
        if(deletenumber==-1) //if name doesn't have .RAW name return false
        {
            delete new_main;
            return false;
        }

        temp_strname = temp_strname.substr(0, deletenumber); //cut string before .RAW
        read_name = temp_strname;

        // store name and index number using linked list
        Loaded_LIST_Node *new_node = new Loaded_LIST_Node;
        new_node->SetItems(read_name, FileDir, idxnumber);
        LISTptr->PUSH(new_main, new_node); //push new node into new main node
    }
    // LISTptr->PRINT(new_main);
    fread.close();
    return true;
}

bool Manager::MODIFY(char *str){
    char *FileDir = str;
    str = strtok(NULL, "");
    string temp_str = str;
    int IndexF = temp_str.find('"'); //find the first index of "
    int IndexL = temp_str.rfind('"'); //find the last index of 

    // check name is ok with two " which points name
    if(IndexF==-1||IndexF==IndexL){ 
        return false;
    }

    string FileName = temp_str.substr(IndexF + 1, IndexL-1); //cut file name by "
    string temp_Index = temp_str.substr(IndexL + 1);

    char *charIdx = new char[temp_Index.length()]; //get the name of user's command
    int startnum, endnum;
    strcpy(charIdx, temp_Index.c_str());
    for (int i = 0; i < temp_Index.length();i++){ //check the start index number of the string
        if(48<=charIdx[i]&&charIdx[i]<=58){
            startnum = i;
            break;
        }
    }
    for (int i = startnum; i < temp_Index.length()+2; i++) //check the end index number of the string
    {
        if(charIdx[i]<48||58<charIdx[i])
            break;
        endnum = i;
    }

    delete[] charIdx; //delete char pointer which findes numbers index
    temp_Index.substr(startnum, endnum);
    int idxnumber = stoi(temp_Index);

    MainNodes *FindedMain;

    FindedMain = LISTptr->FINDDIR(FileDir);
    if(FindedMain==NULL) //when we didn't find FileDir
        return false;

    if(LISTptr->FINDIDX(idxnumber)) //check if there is an same index number
    {
        return false;
    }

    Loaded_LIST_Node *new_node = new Loaded_LIST_Node;
    new_node->SetItems(FileName, FileDir, idxnumber);

    if(!LISTptr->MODIFYNODE(new_node,FindedMain, FileName)) //modify node
        return false;

    return true;
}

bool Manager::MOVE(){

    string Namedata;
    string Dirdata;
    int Indexdata;
    if(LISTptr->EMPTYLIST()) //check if List is empty
        return false;

    while (!LISTptr->EMPTYLIST())  //check if List is empty
    {
        Loaded_LIST_Node *ToMove = LISTptr->DELETE(); //select the last Loded_List_Node

        if(ToMove==NULL)
            return false;

        Indexdata = ToMove->GetIdx(); //get index from node
        Namedata = ToMove->GetName(); //get name from node
        Dirdata = ToMove->GetDirectory(); //get directory from node

        //check if node is already duplicate
        int *i = new int[1];
        *i = 0;
        BSTptr->CheckDuplicate(BSTptr->GetRoot(), Namedata, Indexdata, i); // if there is node which has same name or index

        if(*i>=1){ 
            delete[] i;
            continue; //read node again
        }
        delete[] i;

        // delete nodes when it is over 300
        if(BSTptr->GetNumber()>=300){
            BSTptr->Erase(BSTptr->GetRoot());
        }

        Database_BST_Node *new_bst = new Database_BST_Node; //make the new bst node
        new_bst->SetItems(Indexdata, Dirdata, Namedata);

        BSTptr->Insert(new_bst); // put node in the tree

        delete ToMove; //delete node
    }
    return true;
}

bool Manager::PRINT(){ //print all the name and index of all nodes in the bst

    if(!BSTptr->GetRoot()){
        return false;
    }

    flog << "=======PRINT=======" << endl;
    BSTptr->PrintInorder(BSTptr->GetRoot());
    flog << "=====================" << endl
         << endl;

    return true;
}

bool Manager::SEARCH(char *str){

    if(str ==NULL)
        return false;
    string tempstr = str;
    int startidx = 0, endidx = 0;
    startidx = tempstr.find("\""); //find the index of first "
    endidx = tempstr.rfind("\""); //find the index of last "
    if(startidx==endidx)//check if string has "
        return false;

    string Word = tempstr.substr(startidx + 1, endidx - 1);

    BSTptr->BST_Postorder(BSTptr->GetRoot(), QUEptr); //attach to BST in iterative postorder and store nodes in node Queue
    if(!QUEptr->BoyMoo(Word))
        return false;

    return true;
}

bool Manager::SELECT(char *str){

    if(str ==NULL) //check input number
        return false;
    string InputNumber = str;
    int FileNumber = stoi(InputNumber); //extract number

    Database_BST_Node *FindingNode;
    Database_BST_Node *TempNode = NULL;
    FindingNode = BSTptr->BST_Preorder(FileNumber, TempNode, BSTptr->GetRoot()); //find BST NODE using preorder

    if(!FindingNode)
        return false;

    string FileName = FindingNode->GetName();
    ImageName = FileName;
    string FileDir = FindingNode->GetDir();
    string TOOPEN = FileDir.append("/") + FileName.append(".RAW"); //open file directory 

    GetImage = fopen(TOOPEN.c_str(), "rb");

    if(GetImage==NULL) //if can't find the image raw file 
        return false;

    fread(IMG, sizeof(char), 256 * 256, GetImage);
    return true;
}

bool Manager::EDIT(char *str){

    char *read1 = str;
    char *read2 = strtok(NULL, " ");

    if (!read1) // when we can't find any words after EDIT
        return false;

    if (GetImage == NULL) // if didn't select the raw image file
        return false;

    if (strcmp(read1,"-l")==0 && read2==NULL) //when EDIT has only -l with no number
        return false;


    FILE *ResultImage;

    if (strcmp(read1, "-f") == 0) //check if flip the image
    {
        unsigned char RESULTIMG[256][256];
        for (int i = 0; i < 256; i++) // push pixel data in Stack one by one
        { 
            for (int j = 0; j < 256; j++)
            {
                Database_IMAGENODE *new_data = new Database_IMAGENODE;
                new_data->SetPixel(IMG[i][j]);
                IMGptr->PUSH(new_data);
            }
        }

        for (int i = 0; i < 256; i++)
        { // get pixel information from stack one by one
            for (int j = 0; j < 256; j++)
            {
                Database_IMAGENODE *Cur = IMGptr->StackPOP(); //get pixel information by pop stack
                RESULTIMG[i][j] = Cur->GetPixel();
                delete Cur;
            }
        }

        string toPutDir = "Result/" + ImageName + "_flipped.RAW"; //put in result directory
        ResultImage = fopen(toPutDir.c_str(), "wb");
        if (ResultImage == NULL)
            return false;

        fwrite(RESULTIMG, sizeof(char), 256 * 256, ResultImage); //write raw file
        fclose(ResultImage);

        return true;
    }
    else if(strcmp(read1,"-l")==0){ //check if we have to adjust image file
        unsigned char RESULTIMG[256][256];
        string templight = read2;
        int lightindex = stoi(templight);

        for (int i = 0; i < 256;i++){ //push pixel data in Queue
            for (int j = 0; j < 256;j++){
                Database_IMAGENODE *new_data = new Database_IMAGENODE;
                new_data->SetPixel(IMG[i][j]);
                IMGptr->PUSH(new_data);
            }
        }

        for (int i = 0; i < 256;i++){ //get pixel information from Queue one by one
            for (int j = 0; j < 256;j++){
                Database_IMAGENODE *Cur = IMGptr->QueuePOP();
                IMG[i][j] = Cur->GetPixel();
                if (IMG[i][j] + lightindex > 255) //the max pixel value is 255, so when it is over 255 then assign pixel 255
                {
                    RESULTIMG[i][j] = 255;
                }
                else if(IMG[i][j] + lightindex < 0)
                {
                    RESULTIMG[i][j] = 0;
                }
                else{
                    RESULTIMG[i][j] = IMG[i][j] + lightindex; //else add the light number
                }
                delete Cur;
            }
        }
        
        string toPutDir = "Result/"+ImageName+"_adjusted.RAW"; //write in result directory 
        ResultImage = fopen(toPutDir.c_str(), "wb");
        if(ResultImage==NULL)
            return false;

        fwrite(RESULTIMG, sizeof(char), 256 * 256, ResultImage);
        fclose(ResultImage);

        return true;
    }
    else if(strcmp(read1,"-r")==0){ //check if we have to resize image file

        unsigned char RESULTIMG[128][128];
        for (int i = 0; i < 128; i++) //calculate average pixel of 4 arrays
        { 
            for (int j = 0; j < 128; j++)
            {
                RESULTIMG[i][j] = (IMG[2 * i][2 * j] + IMG[2 * i][(2 * j) + 1] + IMG[(2 * i) + 1][2 * j] + IMG[(2 * i) + 1][(2 * j) + 1]) / 4;
            }
        }

        string toPutDir = "Result/" + ImageName + "_resized.RAW"; //write in result directory
        ResultImage = fopen(toPutDir.c_str(), "wb");
        if (ResultImage == NULL)
            return false;

        fwrite(RESULTIMG, sizeof(char), 128 * 128, ResultImage);
        fclose(ResultImage);

        return true;
    }
    else{
        return false;
    }
}

void Manager::EXIT(){ //delete all the dynamical allocator
    if(LISTptr)
        delete LISTptr; // delete LIST ptr
    if(BSTptr)
        delete BSTptr; // delete Binary Search ptr
    if(QUEptr)
        delete QUEptr; // delete Queue ptr
    if(IMGptr)
        delete IMGptr; // delete Image ptr
    fclose(GetImage);

    PrintSuccess("EXIT");
}

void Manager::PrintError(int num) // print the error code
{
    flog << "========ERROR========" << endl;
    flog << num << endl;
    flog << "=====================" << endl
         << endl;
}

void Manager::PrintSuccess(string str) // print the success code
{
    flog << "=========" << str << "=========" << endl;
    flog << "SUCCESS" << endl;
    flog << "=====================" << endl
         << endl;
}