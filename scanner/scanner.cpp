// scanner.cpp
// Krishnan Kalyanasundar

#include<iostream>
#include<fstream>
using namespace std;

const char eof = '\0';
const int lexemeLength = 100;

class scanner {
    
    ifstream fin;
    string fileName;
    char ch;
    
    string *tokenList;
    string *binaryOprList;
    
    int linenum;
    bool eofNotReached;
    
    //string lexemes[lexemeLength];
    //string tokens[lexemeLength];
    
public:
    scanner();
    ~scanner();
    
    void setTokenList();
    void printTokenList();
    string getTokenAtIndex(int i);
    
    void setBinaryOprList();
    bool checkIfBinaryOperator(char *opr);
    
    bool getNextChar();
    void pushBackPointer(char ch);
    
    void gettoken();
    void gettokword();
    void gettoknumber();
    void gettokop();
    
};


// default constructor to check if file exists and if so calls the gettoken method
scanner::scanner()
{
    fileName = "inputPascal.txt";
    fin.open(fileName);
    
    if(!fin)
    {
        cout<<"File does not exist\n";
        exit(0);
    }
    
    
    setTokenList();
    setBinaryOprList();
    linenum = 0;
    
    gettoken();
    
}

// destructor to close the file pointer
scanner::~scanner()
{
    fin.close();
}

// sets the token list
void scanner::setTokenList()
{
    tokenList = new string[3];
    tokenList[0] = "tokword";
    tokenList[1] = "toknumber";
    tokenList[2] = "tokop";
}

// gets the name of the token at an index
string scanner::getTokenAtIndex(int i)
{
    return tokenList[i];
}

void scanner::printTokenList()
{
    cout<<"TokenList : "<<tokenList[0]<<" "<<tokenList[1]<<" "<<tokenList[2]<<"\n";
}

// sets the list of binary operators in Pascal
void scanner::setBinaryOprList()
{
    binaryOprList = new string[4];
    binaryOprList[0] = "<>";
    binaryOprList[1] = "<=";
    binaryOprList[2] = ">=";
    binaryOprList[3] = ":=";
}

// checks if an encountered opertor is a binary operator or not
bool scanner::checkIfBinaryOperator(char *opr)
{
    for(int i=0;i<4;i++)
    {
        if(opr==binaryOprList[i])
            return true;
    }
    
    return false;
}

// gets next character from input file
bool scanner::getNextChar()
{
    if(fin.get(ch) && ch!=eof)
    {
        eofNotReached = true;
    }
    else
    {
        eofNotReached = false;
    }
    
    if(ch=='\n')
    {
        linenum++;
    }
    
    return eofNotReached;
}

// push the file read pointer one step backward
void scanner::pushBackPointer(char ch)
{
    if(ch=='\n')
    {
        linenum--;
    }
    
    fin.putback(ch);
}

// function to recognize the lexemes and return the tokens
void scanner::gettoken()
{
    while(getNextChar())
    {
        if(isalpha(ch)) // starting with alpha -> tokword
        {
            gettokword();
        }
        else if(isdigit(ch)) // starting with a number -> toknumber
        {
            gettoknumber();
        }
        else if(!isspace(ch))// other lexemes -> tokop
        {
            gettokop();
        }
        
    }
    
    cout<<endl<<endl;
    
}

// finds lexemes which are tokwords
void scanner::gettokword()
{
    
    char lexeme[lexemeLength];
    int i=0;
    
    lexeme[i] = ch;
    lexeme[++i] = eof;
    
    while(getNextChar())
    {
        
        if(!isspace(ch) && (isalpha(ch)||isdigit(ch)))
        {
            lexeme[i] = ch;
            lexeme[++i] = eof;
        }
        else
        {
            
            cout<<"\n"<<lexeme<<"\t\t"<<getTokenAtIndex(0);
            
            
            if(!isspace(ch))
            {
                //move file pointer one step back
                pushBackPointer(ch);
            }
            break;
        }
    }
    
    if(!eofNotReached)
    {
        cout<<"\n"<<lexeme<<"\t\t"<<getTokenAtIndex(0);
    }
    
    
}


// finds lexemes which are toknumbers
void scanner::gettoknumber()
{
    char lexeme[lexemeLength];
    int i=0;
    
    lexeme[i] = ch;
    lexeme[++i] = eof;
    
    while(getNextChar())
    {
        if(isalpha(ch))
        {
            cout<<"\nError in syntax. Check your input code. Scanner stopped at line number "<<linenum+1<<"\n\n";
            exit(0);
        }
        else if(!isspace(ch) && isdigit(ch))
        {
            lexeme[i] = ch;
            lexeme[++i] = eof;
        }
        else
        {
            cout<<"\n"<<lexeme<<"\t\t"<<getTokenAtIndex(1);
         
            if(!isspace(ch))
            {
                //move file pointer one step back
                pushBackPointer(ch);
            }
            break;
        }
    }
    
    if(!eofNotReached)
    {
        cout<<"\n"<<lexeme<<"\t\t"<<getTokenAtIndex(1);
    }

    
}

// finds lexemes which are tokops
void scanner::gettokop()
{
    char lexeme[lexemeLength];
    int i=0;
    
    lexeme[i] = ch;
    lexeme[++i] = eof;
    
    while(getNextChar())
    {

        if(!isspace(ch) && !isdigit(ch) && !isalpha(ch))
        {
            lexeme[i] = ch;
            lexeme[++i] = eof;
        }
        
        else
        {
            if(i>1 && !checkIfBinaryOperator(lexeme))
            {
                for(int k=0; k<strlen(lexeme); k++)
                {
                    cout<<"\n"<<lexeme[k]<<"\t\t"<<getTokenAtIndex(2);
                }
            }
            
            else
            {
                cout<<"\n"<<lexeme<<"\t\t"<<getTokenAtIndex(2);
            }
            
            if(!isspace(ch))
            {
                //move file pointer one step back
                pushBackPointer(ch);
            }
            break;
        }
    }
    
    if(!eofNotReached)
    {
        cout<<"\n"<<lexeme<<"\t\t"<<getTokenAtIndex(2);
    }
}

int main() {
    
    scanner obj;

    return 0;
}