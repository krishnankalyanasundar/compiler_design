//	symboltable.cpp
//	Krishnan Kalyanasundar
//	N17957143
//	kk3059@nyu.edu

#include <iostream>
#include <fstream>
#include <locale> 
#include <string>

using namespace std;


/* 
*
* Scanner Code - Start 
*
*/

const char eof = '\0';
const int lexemeLength = 100;

string alltokenlist[100];
int alltokenlisttype[100];
int alltokenlistsize = -1;


class scanner {
    
    ifstream fin;
    string fileName;
    char ch;
    
    string *tokenList;
    string *binaryOprList;
    
    int linenum;
    bool eofNotReached;
    
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
            alltokenlist[++alltokenlistsize] = lexeme;
            alltokenlisttype[alltokenlistsize] = 1;
            
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
        alltokenlist[++alltokenlistsize] = lexeme;
        alltokenlisttype[alltokenlistsize] = 1;
            
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
           	alltokenlist[++alltokenlistsize] = lexeme;
            alltokenlisttype[alltokenlistsize] = 2;
            
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
        alltokenlist[++alltokenlistsize] = lexeme;
       	alltokenlisttype[alltokenlistsize] = 2;    
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
                   	alltokenlist[++alltokenlistsize] = lexeme[k];
           			alltokenlisttype[alltokenlistsize] = 3;
                }
            }
            
            else
            {
                alltokenlist[++alltokenlistsize] = lexeme;
            	alltokenlisttype[alltokenlistsize] = 3;
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
        alltokenlist[++alltokenlistsize] = lexeme;
        alltokenlisttype[alltokenlistsize] = 3;
            
    }
}



void startscanning()
{
    scanner obj;
}


/* 
* 
* Scanner Code - End
*
*/




/* 
* 
* Symbol Table Code - Start
*
*/


int keywordnum = 35;

//initial keywords of Pascal language
string keywords[] = 
{
	"begin", "call", "declare", "do", "else", "const",
	"end", "endif", "enduntil", "endwhile", "if", 
	"integer", "parameters", "procedure", "program",
    "read", "real", "set", "then", "until", "while",
    "write", "*", "+", "-", "/", "=", ";",
    ",", ".", ">", "<", "!", "(", ")"
};

//initial tokentypes for predefined keywords
string tokentype[] = 
{
	"tokbegin", "tokcall", "tokdeclare", "tokdo", "tokelse", "tokword",
	"tokend", "tokendif", "tokenduntil", " tokendwhile", "tokif",
	"tokinteger", "tokparameters", "tokprocedure", "tokprogram",
	"tokread", "tokreal", "tokset", "tokthen", "tokuntil", "tokwhile",
	"tokwrite", "tokstar", "tokplus", "tokminus", "tokslash", "tokequals", "toksemicolon",
	"tokcomma", "tokperiod", "tokgreater", "tokless", "toknotequal", "tokopenparen", "tokcloseparen"
};


//function to get the index of a keyword
int keywordindex(string word)
{
	for(int i=0;i<keywordnum;i++)
	{
		if(keywords[i] == word)
			return i;
	}

	return -1;
}

//hash table declaration
int hastable[100];

//string table declaration
string stringtable[10000];
int stringtablesize = -1;

//structure of name table
struct nametablestruct
{
	int startpos;
	int strlength;
	int attrindexptr;
	int tokenptr;
}nametable[100];

int nametablesize = -1;

//structure of symbol table
struct symboltablestruct
{
	string lexeme;
	string tokenclass;
}symboltable[100];

int symboltablesize = -1;


//structure of attribute table
struct attributetablestruct
{
	string lexeme;
	string tokenclass;
	string symboltype;
	string datatype;
	string value;
	string scope;
}attributetable[100];

int attributetablesize = -1;

//function to avoid case sentive errors
void changetoupper()
{
	for(int i=0; i<=alltokenlistsize; i++)
	{
		locale loc;
		string str = alltokenlist[i];

		for (string::size_type j=0; j<str.length(); j++)
    		str[j] = toupper(str[j],loc);

    	alltokenlist[i] = str;
	}

	for(int i=0; i<keywordnum; i++)
	{
		locale loc;
		string str = keywords[i];

		for (string::size_type j=0; j<str.length(); j++)
    		str[j] = toupper(str[j],loc);

    	keywords[i] = str;
	}

}


//function to insert into hastable
void searchinhastable(string lex)
{
	int value = 0;
	for(int i=0;i<lex.length();i++)
	{
		value = value + (int)lex[i];
	}
	int hashvalue = value%100;

	int valueatindex = hastable[hashvalue];

}

//function to insert into string and nametable
void createstringandnametable(string lex)
{
	int start = stringtablesize+1;
	int slength = lex.length();

	for(int j=0;j<slength;j++)
	{
		stringtable[++stringtablesize] = lex[j];
	}

	++nametablesize;
	nametable[nametablesize].startpos = start;
	nametable[nametablesize].strlength = slength;
	nametable[nametablesize].attrindexptr = nametablesize;
	nametable[nametablesize].tokenptr = -1;

}


//function to insert lexemes and tokenclasses into symbol table
void insertsymboltable(string lexeme, string tokenclass)
{
	++symboltablesize;
	symboltable[symboltablesize].lexeme = lexeme;
	symboltable[symboltablesize].tokenclass = tokenclass;
}

//function to print the final result from symbol table
void printsymboltable()
{
	if(symboltablesize<0)
	{
		cout<<"Symbol table is empty!"<<"\n";
	}
	else
	{
		for(int i=0;i<=symboltablesize;i++)
		{
			cout<<symboltable[i].lexeme<<"\t";
			cout<<symboltable[i].tokenclass<<"\n";

		}
	}
}


//funtion to print the contents of attribute table
void printattrtable()
{
	if(attributetablesize<1)
	{
		cout<<"Attribute table is empty!"<<"\n";
	}
	else
	{
		for(int i=0;i<=attributetablesize;i++)
		{	
		cout<<attributetable[i].lexeme<<"\t";
		cout<<attributetable[i].tokenclass<<"\t";
		cout<<attributetable[i].symboltype<<"\t";
		cout<<attributetable[i].datatype<<"\t";
		cout<<attributetable[i].value<<"\t";
		cout<<attributetable[i].scope<<"\n";

		}
	}
}

//function to intialize the attribute table
void initializeattrtable()
{
	for(int i=0;i<keywordnum;i++)
	{

		string lex = keywords[i];

		++attributetablesize;
		attributetable[attributetablesize].lexeme = lex;
		attributetable[attributetablesize].tokenclass = tokentype[keywordindex(lex)];

		if(lex.length()>1)
			attributetable[attributetablesize].symboltype = "Keyword";
		else
			attributetable[attributetablesize].symboltype = "Operator";

		attributetable[attributetablesize].datatype = "None";
		attributetable[attributetablesize].value = "0";
		attributetable[attributetablesize].scope = "Global";
	}

}

//function to search and insert into the attribute table
void searchandinsertattrtable(string lex, int toktype)
{
	bool islexavail = false;

	for(int i=0;i<=attributetablesize;i++)
	{	
		if(attributetable[i].lexeme == lex)
		{
			islexavail = true;
			//insert the already existing entry into symbol table
			insertsymboltable(lex,attributetable[i].tokenclass);
			break;
		}

	}

	if(!islexavail)
	{
		++attributetablesize;
		attributetable[attributetablesize].lexeme = lex;
	
		if(toktype==1) //tokword
		{
			attributetable[attributetablesize].tokenclass = "tokidentifier";
			attributetable[attributetablesize].symboltype = "Variable";

		}
		else if(toktype==2) //toknumber
		{
			attributetable[attributetablesize].tokenclass = "tokconstant";
			attributetable[attributetablesize].symboltype = "Literal";
		}
		else if(toktype==3) //tokop
		{
			attributetable[attributetablesize].tokenclass = "tokperator";
			attributetable[attributetablesize].symboltype = "Operator";
		}

		attributetable[attributetablesize].datatype = "None";
		attributetable[attributetablesize].value = "0";
		attributetable[attributetablesize].scope = "Global";

		//insert the newly created entry into symbol table
		insertsymboltable(attributetable[attributetablesize].lexeme,attributetable[attributetablesize].tokenclass);

	}
}



int main()
{
	//initialize and invoke the scanner
	startscanning();
	changetoupper();

	//intitialize the attribute table
	initializeattrtable();

	//search/insert into final symbol table
    for(int i=0;i<=alltokenlistsize;i++)
	{
		searchinhastable(alltokenlist[i]);
		searchandinsertattrtable(alltokenlist[i],alltokenlisttype[i]);
	}

	//print final result from symbol table
	printsymboltable();

	cout<<"\n\n";
	return 0;
}