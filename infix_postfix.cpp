#include<bits/stdc++.h>

using namespace std;

string convertInfixToPostfix();
int operatorPrecedence(char ch);
int evaluatePostfixExpression(string postfix);
int calculate(int a, int b, char operatorSign);
char infixExpression[2000];
int main()
{
    string  postfixExpression;

    int result;
    gets(infixExpression) ;
    cout<<infixExpression;
    postfixExpression = convertInfixToPostfix();
    cout<<"Infix Expression: "<<infixExpression<<endl;
    cout<<"Postfix Expression: "<<postfixExpression<<endl;
    result = evaluatePostfixExpression(postfixExpression);
    cout<<"\nResult is: "<<result<<endl;
    return 0;
}

string convertInfixToPostfix()
{
    string postfix = "";
    stack <char> myStack;
    char ch;
    for(int i=0; infixExpression[i]; i++)
    {
        if(infixExpression[i]!=' ')
        {
            ch = infixExpression[i];
            if(ch=='(')
                myStack.push(ch);
            else if(ch==')') //if found closing bracket
            {
                while(!myStack.empty() && myStack.top()!='(')
                {
                    postfix = postfix + myStack.top()+" ";
                    myStack.pop();
                }
                if(!myStack.empty() && myStack.top()=='(')
                    myStack.pop();
            }
            else
            {
                int priority = operatorPrecedence(ch);
                if(priority==0)
                {
                    string num="";
                     while(operatorPrecedence(ch)==0&&infixExpression[i]!='\0'&& infixExpression[i]!='('&& infixExpression[i]!=')')
                     {
                               num=num+ch;
                               i++;
                               ch=infixExpression[i];

                     }
                     postfix=postfix+num+" ";
                     i--;
                }
                else //found operator
                {
                    if(myStack.empty())
                        myStack.push(ch);
                    else
                    {
                        while(!myStack.empty()
                                && myStack.top()!='('
                                && priority<=operatorPrecedence(myStack.top()))
                        {
                            postfix = postfix + myStack.top()+" ";
                            myStack.pop();
                        }
                        myStack.push(ch);
                    }
                }
            }
        }
    }
    while(!myStack.empty())
    {
        postfix =postfix+myStack.top()+" ";
        myStack.pop();
    }
    return postfix;
}

evaluatePostfixExpression(string postfix)
{
    stack <int> myStack;
    char ch;
    for(int i=0; postfix[i]; i++)
    {
        ch = postfix[i];
        if(ch!=' ')
        {
            if(ch>='0' && ch<='9')
            {
                      string num="";
                      while(ch!=' '&&postfix[i]!='\0')
                      {
                                num=num+ch;
                                i++;
                                ch=postfix[i];
                      }
                      reverse(num.begin(),num.end());
                      int k=1,j=0,wholeNumber=0;
                      while(num[j]!='\0')
                      {
                                int digit=(num[j]-48);
                                int  c=digit*k;
                                k*=10;
                                j++;
                                wholeNumber+=c;
                      }
                      myStack.push(wholeNumber);
            }
            else //found operator
            {
                int a,b;
                b = myStack.top();
                myStack.pop();
                a = myStack.top();
                myStack.pop();
                myStack.push(calculate(a, b, ch));
            }
        }
    }
    return myStack.top();
}

int calculate(int a, int b, char operatorSign)
{
    if(operatorSign=='+')
        return a+b;
    else if(operatorSign=='-')
        return a-b;
    else if(operatorSign=='*')
        return a*b;
    else if(operatorSign=='/')
        return a/b;
    else if(operatorSign=='^')
        return pow(a,b);
}


int operatorPrecedence(char ch)
{
    if(ch=='^')
        return 3; //highest priority for exponential operator
    else if(ch=='/' || ch=='*')
        return 2; //high priority than + or - operator
    else if(ch=='+' || ch=='-')
        return 1; //lowest priority among operators
    else
        return 0;
}

