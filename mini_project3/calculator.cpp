#include<iostream>
#include<string>
using namespace std;
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
bool isOperators(char digit)
{
    int i=0;
    char operators[6]={'+','-','*','/','^'};
     while(operators[i]!='\0')
     {
         if(operators[i]==digit)
            return true;
        i++;
     }
     return false;
}
bool IsError(char str[])
{
     stack parenthesis;
     int i=0 , temp;
     bool flag=false;
     while(str[i]!=NULL)
     {

        if(str[i]==')' && parenthesis.isEmpty())
            return true;

        else if(str[i]=='(')
            parenthesis.push("(");

        else if(str[i]==')')
            parenthesis.pop();

        else if(str[i]=='0' && str[i-1]=='/')
        {

            if(str[i+1]!='.')
               return true;
            else
            {
                temp=i+2;

                while(!isOperators(str[temp])){

                    if(str[temp]=='0')
                    {
                        flag=true;
                    }
                    else if(str[temp]>'0' && str[temp]<='9')
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
            bool prob = ( (str[i]=='-' || str[i]=='+') && (str[i+1]>'0' && str[i+1]<='9') );

            if(  ! ((str[i-1]==')'||str[i+1]=='(') || ( ( (str[i-1]>'0' && str[i-1]<='9') || str[i-1]=='.' )
                    && ( (str[i+1]>'0' && str[i+1]<='9') || str[i+1]=='.')) || prob ) )
               return true;

        }

        i++;
     }
       if(parenthesis.isEmpty())
         return false;

    return true;
}
bool control_error(char str[])
{
     if(IsError(str))
        return true;
    return false;

}
void convert_charTostring(char str[])
{
    int i=0 , counter=0 ;
    string arr[1000];
      while(str[i]!=NULL){

         if(str[i]=='-' && ( i==0 || str[i+1]=='('))
         {
             arr[counter]="-1";
             arr[++counter]="*";

         }

         else if(str[i]!='+' || i!=0){

            arr[counter]=str[i];

            if( (str[i]>='0'&&str[i]<='9') || str[i]=='.'){
              i++;
              while ( (str[i]>='0'&&str[i]<='9') || str[i]=='.' ){
                 arr[counter] += str[i];
                 i++;
               }
               i--;
            }

         }
         i++;
         counter++;
      }
      for(int i=0; i<counter; i++)
      {
          cout<<arr[i]<<endl;
      }

}
int main()
{
    char str[1000];
    int counter=0 , c=0 , j=0 ;
    cin.get(str , 1000);

       while(str[c]!='\0'){
          if(str[c]!=' '){
            str[j++]=str[c];
          }
        c++;
        }
     str[j]='\0';

    if(control_error(str))
    {
        cout<<"error\n";
    }
    else
    {
        convert_charTostring(str);
    }

}
