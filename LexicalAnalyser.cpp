#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>

using namespace std;

string Reserved[]={"auto","double","int","struct","break","else","long","switch",
                   "case","enum","register","typedef","char","extern","return","union",
                   "const","float","short","unsigned","continue","for","signed","void",
                   "default","goto","sizeof","volatile","do","if","static","while"};


int isOperator(char ch)
{
    switch(ch)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '=':
        case '<':
        case '>':
        case '!':
        case '&':
        case '|':
            return 1;
    }
    return 0;
}

int isSpecialChar(char ch)
{
    switch(ch)
    {
        case '(':
        case ')':
        case '{':
        case '}':
        case '#':
        case '"':
        case '\'':
        case '[':
        case ']':
        case ' ':
        case ';':
        case '\n':
            return 1;
    }
    return 0;
}

int isKeyword(string lexeme)
{
    for(int i=0;i<32;i++)
        if(lexeme==Reserved[i])
            return 1;
    return 0;
}

int getOperators(string Buffer,int Forward)
{
    char current=Buffer[Forward];

    switch(current)
    {
        case '<':

            current=Buffer[++Forward];
            if(current=='=')
            {
                Forward++;
                cout<<"\t <= \t"<<"Operator \t"<<"LE"<<endl;
                break;
            }
            else
            {
                cout<<"\t < \t"<<"Operator \t"<<"LT"<<endl;
                    break;
            }

        case '!':
            current=Buffer[++Forward];
            if(current=='=')
            {
                Forward++;
                cout<<"\t != \t"<<"Operator \t"<<"\t NE"<<endl;
                break;
            }
            else
            {
                cout<<"\t ! \t"<<"Operator \t"<<"\t NT"<<endl;
                break;
            }

        case '=':
            Forward++;
            cout<<"\t = \t"<<"Operator \t"<<"\t EQ"<<endl;
            break;

        case '>':

            current=Buffer[++Forward];
            if(current=='=')
            {
                Forward++;
                cout<<"\t >= \t"<<"Operator \t"<<"\t GE"<<endl;
                break;
            }
            else
            {
                cout<<"\t > \t"<<"Operator \t"<<"\t GT"<<endl;
                break;
            }

        case '+':

            current=Buffer[++Forward];
            if(current=='=')
            {
                Forward++;
                cout<<"\t += \t"<<"Operator \t"<<"\t ADDE"<<endl;
                break;
            }
            else
            {
                cout<<"\t + \t"<<"Operator \t"<<"\t ADD"<<endl;
                    break;
            }

        case '-':

            current=Buffer[++Forward];
            if(current=='=')
            {
                Forward++;
                cout<<"\t -= \t"<<"Operator \t"<<"\t SUBE"<<endl;
                break;
            }
            else
            {
                cout<<"\t - \t"<<"Operator \t"<<"\t SUB"<<endl;
                    break;
            }

        case '*':

            current=Buffer[++Forward];
            if(current=='=')
            {
                Forward++;
                cout<<"\t *= \t"<<"Operator \t"<<"\t MULE"<<endl;
                break;
            }
            else
            {
                cout<<"\t * \t"<<"Operator \t"<<"\t MUL"<<endl;
                    break;
            }

        case '/':

            current=Buffer[++Forward];
            if(current=='=')
            {
                Forward++;
                cout<<"\t /= \t"<<"Operator \t"<<"\t DIVE"<<endl;
                break;
            }
            else
            {
                cout<<"\t / \t"<<"Operator \t"<<"\t DIV"<<endl;
                    break;
            }

        case '&':

            current=Buffer[++Forward];
            if(current=='&')
            {
                Forward++;
                cout<<"\t && \t"<<"Operator \t"<<"\t LAND"<<endl;
                break;
            }
            else
            {
                cout<<"\t & \t"<<"Operator \t"<<"\t BITAND"<<endl;
                    break;
            }
        case '|':

            current=Buffer[++Forward];
            if(current=='=')
            {
                Forward++;
                cout<<"\t || \t"<<"Operator \t"<<"\t LOR"<<endl;
                break;
            }
            else
            {
                cout<<"\t | \t"<<"Operator \t"<<"\t BITOR"<<endl;
                    break;
            }
    }
    return Forward;

}

int getNumbers(string Buffer,int Forward)
{
    int StartPointer=Forward;

    state_1:
        Forward++;
        if(Buffer[Forward]>='0'&&Buffer[Forward]<='9')
            goto state_1;
        else if(Buffer[Forward]=='.')
            goto state_2;
        else
            goto state_final;

    state_2:
        Forward++;
        if(Buffer[Forward]>='0'&&Buffer[Forward]<='9')
            goto state_3;
         else
            return Forward;

    state_3:
        Forward++;
        if(Buffer[Forward]>='0'&&Buffer[Forward]<='9')
            goto state_3;
        else
            goto state_final;

    state_final:
            cout<<"\t "<<Buffer.substr(StartPointer,(Forward-StartPointer))<<" \tNumber \t"<<" \t\t - "<<endl;
            return Forward;

}

int getIdentifiers(string Buffer,int Forward)
{
    int StartPointer=Forward;
    string Lexeme;

    state_1:
        Forward++;
        if( isalpha(Buffer[Forward]) || isdigit(Buffer[Forward]) || Buffer[Forward]=='_')
            goto state_1;
        else
            goto state_final;

    state_final:
         Lexeme=Buffer.substr(StartPointer,(Forward-StartPointer));
         if(!isKeyword(Lexeme))
            cout<<"\t "<<Lexeme<<" \tIdentifier \t"<<"\t Pointer to Symbol Table"<<endl;
         else
            cout<<"\t "<<Lexeme<<" \tKeyword \t"<<"\t - "<<endl;
        return Forward;
}
int main(int argc,char **argv)
{
    FILE *f;
    char current;
    int LexemeBegin,Forward;
    LexemeBegin=0,Forward=0;

    if(argc!=2)
    {
        cout<<"Invalid number of arguments.\n";
        return 0;
    }

    f = fopen(argv[1], "r");

   // Determine file size
    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);

    char* Buffer = new char[size];

    rewind(f);
    fread(Buffer, sizeof(char), size, f);
    fclose(f);

    cout<<"\n\tTOKENS\tTOKEN_NAME\t\tATTRIBUTE"<<endl;
    while(Buffer[Forward]!=EOF)
    {
            current=Buffer[Forward];

            if(isOperator(current))
                LexemeBegin=getOperators(Buffer,Forward);
            else if(isdigit(current))
                LexemeBegin=getNumbers(Buffer,Forward);
            else if(isSpecialChar(current))
                LexemeBegin++;
            else if(current=='_' || isalpha(current))
                LexemeBegin=getIdentifiers(Buffer,Forward);

            Forward=LexemeBegin;

    }
    return 0;
}
