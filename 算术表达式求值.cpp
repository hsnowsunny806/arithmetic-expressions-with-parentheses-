#include "utility.h"		
#include "lk_stack.h"		
#include <stdlib.h>
#include<iostream>
using namespace std;
class Calculator{
public:
	void Run();                               //执行表达式
private:
	LinkStack<double> OPND;     //操作数栈 
	LinkStack<char> OPTR;         //操作符栈          
	int isp(char op);                        //栈内优先数
	int icp(char op);                        //栈外优先数
	double DoOperator(double x, char op, double y);     
               //形成运算指令，进行运算
	void GetChar(char &ch);         //从输入流获取一字符ch,并跳过空格及回车
	bool IsOperator(char ch);         //判断ch是否为操作符 
};
bool Calculator::IsOperator(char ch)
{
	if(ch == '+'||ch == '-'||ch == '(' ||ch == ')'||ch == '*'||ch == '/'||ch == '%'||ch == '^'||ch == '=')
	return true;
	else
	return false;
}
int Calculator::isp(char op)
{
    
    int priority;
    switch(op)
    {
	    case '(':priority = 1;break;
	    case '+':priority = 3;break;
	    case '-':priority = 3;break;
	    case '*':priority = 5;break;
	    case '/':priority = 5;break;
	    case '%':priority = 5;break;
	    case '^':priority = 7;break;
	    case ')':priority = 8;break;
	    case '=':priority = 0;break;
    }
    return priority;
}
int Calculator::icp(char c)
{
    int priority;
    switch(c)
    {
    case '(':priority = 8;break;
    case '+':priority = 2;break;
    case '-':priority = 2;break;
    case '*':priority = 4;break;
    case '/':priority = 4;break;
    case '%':priority = 4;break;
    case '^':priority = 6;break;
    case ')':priority = 1;break;
    case '=':priority = 0;break;
    }
    return priority;
}


void Calculator::GetChar(char &ch)
{
	ch = getchar();
	if(ch == ' '||ch == '\n')
	ch = getchar();
} 
double Calculator::DoOperator(double x, char op, double y)
{  
		if(op == '+')                        
		return x + y;  
		else if(op == '-')                       
		return x - y; 
		else if(op == '*')                 
		return x * y; 
		else if(op == '=')
		return x;
		else if(op == '/')
		{                        
			if (0 == y) 
			{  
				cout<<"除数为零"<<endl; 
	        	exit(1); 
			} 
			else  
				return x / y; 
		}
        else if(op == '^')  
            return pow(x, y);
       else if(op =='%')  
		   return (int)x % (int)y; 
	   else
	   {
			cout<<"计算停止！有非法字符："<<op<<endl; 
			exit(1); 
		} 
	return 0; 

}  

void Calculator::Run()
{
	OPTR.Clear();
	OPND.Clear();
	OPTR.Push('=');
	char ch;
	char prch;
	char soptr;
	double opnd;
	char op;
	prch = '=';
	GetChar(ch);
	if(OPTR.Top(soptr) == UNDER_FLOW)
	{
		cout<<"表达式有错！"<<endl;
		exit(1);
	}
	while(soptr != '='||ch != '=')
	{
		if(isdigit(ch)||ch =='.')
		{
			cin.putback(ch);
			cin>>opnd;
			OPND.Push(opnd);
			prch = '\0';
			GetChar(ch);
		}
		else if(!IsOperator(ch))
		{
			cout<<"表达式有错！"<<endl;
			exit(1); 
		}
		else
		{
			if((prch == '='||prch == '(')&&(ch == '+'|| ch == '-'))
			{
				OPND.Push(0);
				prch = '\0';
			}
			if(soptr == ')' &&ch == '('|| soptr == '(' &&ch == '='||soptr == '='&&ch ==')')
			{
				cout<<"表达式有错！"<<endl;
				exit(1);
			}
			else if(soptr =='('&&ch == ')')
			{
				if(OPTR.Top(soptr) == UNDER_FLOW)
				{
					cout<<"表达式有错!"<<endl;
					exit(1); 
				} 
				OPTR.Pop(soptr);
				GetChar(ch);
				prch = ')';
			}
			else if(isp(soptr) < icp(ch))
			{
				OPTR.Push(ch);
				prch = ch;
				GetChar(ch); 
			}
			else
			{
				if(OPTR.Pop(op) == UNDER_FLOW)
				{
					cout<<"表达式有错！"<<endl;
					exit(1);
				} 
				double left, right;
				if(OPND.Empty())
				{
					cout<<"缺少右操作数！"<<endl;
					exit(1);
				}
				OPND.Pop(right);
				if(OPND.Empty())
				{
					cout<<"缺少左操作数！"<<endl;
					exit(1);
				}
				OPND.Pop(left);
				OPND.Push(DoOperator(left, op, right));
			}
		}
		if(OPTR.Top(soptr) == UNDER_FLOW)
		{
			cout<<"表达式有错!"<<endl; 
			exit(1);
		}
	}
	if(OPND.Top(opnd) == UNDER_FLOW)
	{
		cout<<"表达式有错!"<<endl; 
		exit(1);
	}
	
	cout<<opnd<<endl; 
} 
int main()
{
	cout<<"请输入表达式："<<endl;
	Calculator c;
	c.Run();
	return 0;
} 
