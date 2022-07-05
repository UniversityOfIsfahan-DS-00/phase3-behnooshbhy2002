#include<iostream>
#include<string>
#include<sstream>
#include<cstring>
#include<math.h>
#include<iomanip>
#include<windows.h>
using namespace std;
#define count 5
bool History = false;
bool tree = false;
int step=0;
void SetColor(int ForgC);
class stack
{
  private :
      int top;
      string arr[50];
  public :
      stack()
      {
          top=-1;
      }
      void push(string str )
      {
          top++;
          arr[top]=str;
      }
      string peek()
      {
          return arr[top];
      }
      string pop()
      {
          if(top!=-1){
            int t=top;
            top--;
            return arr[t];
          }

      }
      bool isEmpty()
      {
          if(top==-1)
            return true;
          return false;
      }

};
class node {
  public:
     string element;
     node* left;
     node* right;
     node* next = NULL;
     node(string c)
     {
        this->element = c;
        left = NULL;
        right = NULL;
     }
     node()
     {
        left = NULL;
        right = NULL;
     }
    friend class Stack2;
    friend class expression_tree;
};
class Stack2{

  public:
    node* head;
    void push(node *str)
    {
        if (head == NULL) {
          head = str;
        }
        else {
          str->next = head;
          head = str;
        }
    }
    node* pop()
    {
         node* p = head;
         head = head->next;
         return p;
    }
    friend class node;
    friend class expression_tree;
};

class expression_tree {
  public:

    void printBT( string prefix, const node* root, bool isLeft)
    {
       if( root != nullptr )
        {
          SetColor(7);
          cout << prefix;
          SetColor(7);
          cout << (isLeft ? "|--" : "!--" );
          SetColor(14);
          cout << root->element << endl;

          printBT( prefix + (isLeft ? "|   " : "    "), root->left, true);
          printBT( prefix + (isLeft ? "|   " : "    "), root->right, false);
        }
    }

    void printBT(const node* root)
    {
        printBT("", root, false);
    }

};

bool isOperators(string digit)
{
    int i=0;
    string operators[6]={"+","-","*","/","^"};
     while(operators[i]!="\0")
     {
         if(operators[i]==digit)
            return true;
        i++;
     }
     return false;
}
bool IsNumber(string digit)
{
    if(digit>="0" && digit<="9")
        return true;
    return false;
}
bool IsError(string str[])
{
    stack parenthesis;
    int i=0 , temp;
    bool flag=false;
    while(str[i]!="\0")
    {

        if(!( isOperators(str[i]) || str[i]=="(" || str[i]==")" || str[i]=="." || IsNumber(str[i])))
            return true;

        if(str[i]==")" && parenthesis.isEmpty())
            return true;

        else if(str[i]=="(")
        {
            if(str[i+1]==")")
                return true;

            parenthesis.push("(");
        }

        else if(str[i]==")")
            parenthesis.pop();

        else if(isOperators(str[i]) && isOperators(str[i+1]))
            return true;

        else if( (str[i]=="." && str[i+1]==".") || ( str[i]=="." && !IsNumber(str[i-1]) && !IsNumber(str[i+1])))
            return true;

        else if(str[i]=="0" && str[i-1]=="/")
        {

            if(str[i+1]!=".")
               return true;
            else
            {
                temp=i+2;

                while(!isOperators(str[temp])){

                    if(str[temp]=="0")
                    {
                        flag=true;
                    }
                    else if(IsNumber(str[temp]) && str[temp]!="0")
                    {
                        return false;
                    }
                    temp++;

                }
                if(flag)
                    return true;
            }
        }
        else if(isOperators(str[i]))
        {

            bool prob = ( (str[i]=="-" || str[i]=="+") && (IsNumber(str[i+1])) );

            if(  !((str[i-1]==")"||str[i+1]=="(")
              || ( ( (IsNumber(str[i-1])) || str[i-1]=="." )
               && ( (IsNumber(str[i+1]) ) || str[i+1]==".")) || prob ) )
               return true;

        }


        i++;
    }

    if(parenthesis.isEmpty())
        return false;

    return true;
}
bool control_error(string str[])
{
    if(IsError(str))
        return true;
    return false;
}

void Postfix_To_Infix(string arr[])
{
    stack stk;
    string num1 , num2;
    int i=0;
    while(arr[i]!="\0")
    {

        if(isOperators(arr[i]))
        {
            num1 = stk.pop();
            num2 = stk.pop();
            stk.push("(" + num2 + arr[i] + num1 + ")");
        }
        else
        {
             stk.push(arr[i]);
        }
        i++;
    }

    cout<<"Step "<<step<<" : "<<stk.pop()<<endl;
    step++;
}
void insert_tree(string arr[])
{
    int i=0;
    node *num1 , *num2 , *op;
    expression_tree t;
    Stack2 stk;
     while(arr[i]!="\0")
     {
         op = new node(arr[i]);
         if(isOperators( arr[i] ))
         {

            num1 = stk.pop();
            num2 = stk.pop();
            op->right = num2;
            op->left = num1;

         }
           stk.push(op);
           i++;
     }

     t.printBT(op);

}
void solve(string arr[])
{
    int i=0;
    double number1 , number2 , result;
    string num1 , num2 , res;
    stack stk;

    while(arr[i]!="\0")
    {
        if(isOperators(arr[i]))
        {
            num1 = stk.pop();
            num2 = stk.pop();
            number1= strtod(num1.c_str(), NULL);
            number2= strtod(num2.c_str(), NULL);

                if(arr[i]=="+")
                {
                    result = number2 + number1;
                }
                else if(arr[i]=="-")
                {
                    result = number2 - number1;
                }
                else if(arr[i]=="*")
                {
                    result = number2 * number1;
                }
                else if(arr[i]=="/")
                {
                    result = number2 / number1;
                }
                else
                {
                    result = pow(number2 , number1);
                }

                res = to_string(result);
                int length= res.length();
                for(int h = length-1; h>=0; h--)
                {
                    if(res.at(h)=='0' || res.at(h)=='.')
                        res.pop_back();
                    else
                        break;
                }

                if(History)
                {
                    arr[i]=res;
                    int temp=i;
                    while(arr[temp]!="\0")
                    {
                       arr[temp-2]="\0";
                       arr[temp-1]="\0";
                       arr[temp-2]=arr[temp];
                       arr[temp]="\0";
                       temp++;
                    }
                    Postfix_To_Infix(arr);
                    i=i-2;
                }

                stk.push(res);

        }
        else
        {
          stk.push(arr[i]);
        }

        i++;
    }

      cout<<"result : "<<stk.pop();

}
int precedence(string operate)
{
    if(operate=="^")
        return 3;
    else if(operate=="*" || operate=="/")
        return 2;
    else if(operate=="+" || operate=="-")
        return 1;
}
void Infix_To_Postfix(string arr[])
{
    stack s;
    int i=0 , n=-1;

      while(arr[i]!="\0")
      {

        if(!isOperators(arr[i]) && arr[i]!="(" && arr[i]!=")")
        {
            arr[++n]=arr[i];
        }
        else if(arr[i]=="(")
        {
            s.push(arr[i]);
        }
        else if(arr[i]==")")
        {
            while(!s.isEmpty() && s.peek()!="(")
            {
                arr[++n]=s.pop();
            }

            if(!s.isEmpty() && s.peek()!="(")
                return;
            else
                s.pop();
        }
        else if(arr[i]!="^")
        {

            while(!s.isEmpty() && precedence(arr[i]) <= precedence(s.peek()))
                arr[++n]=s.pop();

            s.push(arr[i]);

        }
        else
        {

            while(!s.isEmpty() && precedence(arr[i]) < precedence(s.peek()))
                arr[++n]=s.pop();

            s.push(arr[i]);

        }

        i++;

      }

      while(!s.isEmpty())
      {
          arr[++n]=s.pop();
      }
      arr[++n]="\0";
      if(tree)
      {
          insert_tree(arr);
      }
      else
      {
          if(History)
            Postfix_To_Infix(arr);
          solve(arr);

      }


}

void convert_charTostring(string str[])
{
    int i=0 , counter=0 ;
    string arr[1000];
    while(str[i]!="\0")
    {

        if(str[i]=="-" && ( i==0 || str[i-1]=="(" ))
        {
            arr[counter]="-1";
            arr[++counter]="*";

        }
        else if(str[i]!="+" || i!=0)
        {
            arr[counter]=str[i];
               if( IsNumber(str[i]) || str[i]==".")
               {
                   i++;
                    while ( IsNumber(str[i]) || str[i]=="." ){
                       arr[counter] += str[i];
                       i++;
                    }
                   i--;

                }

        }

        i++;
        counter++;

    }

    Infix_To_Postfix(arr);

}
int main()
{
    char str[1000];
    int counter=0 , c=0 , j=0 , i=0 , type;
    string arr[1000];
    cin.get(str , 1000);

     while(str[c]!='\0'){
       if(str[c]!=' '){
         str[j++]=str[c];
        }
         c++;
     }

     str[j]='\0';
     while(str[i]!=NULL)
     {
         arr[i]=str[i];
         i++;
     }


    if(control_error(arr))
    {
        cout<<"error\n";
    }
    else
    {
        while(1){
          cout<<"\n1.Result \n2.Step By Step Solution \n3.Tree view\n4.Exit\n";
          cin>>type;
           if(type==2)
           {
             History = true;
           }
           if(type==1 || type==2)
             convert_charTostring(arr);
           if(type==3)
           {
             tree = true;
             convert_charTostring(arr);
           }
           if(type==4)
             break;
           tree = false;
           History = false;
           step=0;
        }

    }

}
void SetColor(int ForgC)
{
     WORD wColor;

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

