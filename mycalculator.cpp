#include <iostream>
#include <string.h>
#include <stack>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>

using namespace std;
//judge the precedence of the operator
int judge(char oper)
{
    switch(oper)
    {
        case'(' :
            return -1;
            break;
        case '+' : case '-' :
            return 1;
            break;
        case '*' : case '/' : case '%':
        	return 2;
        default :
            return 0;
    }
}
//change from infix expression to postfix expression
string infixtopostfix(string infix)
{
    istringstream isstream(infix);
    ostringstream postfix;
    string a;
    char aStack[1000];
    int top = -1;
    //check whether there exists an error by securing the number we input minus the operator we input will equal to one
    int flag = 0;
    while(isstream >> a)
    {
		//check whether it is an operand                     
        if(isdigit(a[0]))
        {
        	//check whether it is overflowed
        	if(a.length()>10)
        		return "overflow";
        	else if (a.length()==10){
        		if(a[0]>2)
        			if (a[1]>1)
        				return "overflow";
        	}
        	else{
            	postfix << a << " ";//數字直接輸出 
            	flag++;
            }
        }
        //check whether it is negative
        else if(isdigit(a[1]))
        {
        	if(a.length()>11)
        		return "underflow";
        	else if (a.length()==10){
        		if(a[1]>2)
        			return "underflow";
        		}
        	else{
        		flag++;
				postfix << a << " ";
        }
    }
        else
        {
        	
            switch(a[0])
            {
            	//we put '(' into stack directly
                case '(' : 
                    aStack[top++] = a[0];
                    break;
                case ')' : 
                    while(aStack[top-1]!='(') 
                    {
                        postfix << aStack[--top] << " ";
                        //we cannot find a '('
                        if(top<0)
                        	return "error";
                        flag--;
                    } 
                    top--;
                    break;
                    
                case '+' : case'-' : case '*' : case '/' : case '%': 
                	
                    if(top>=0)
                        while(judge(aStack[top-1]) >= judge(a[0])&&top>=0)
                        {
                            postfix << aStack[--top] << " ";
                            flag--;
                               
                        }
                        
                    aStack[top++] = a[0];
                    
                    break;
                    
                    default : 
                        break;
            }
        }
   
    }
    //put the rest of the stack into postfix    
    while(top>=0) 
    {
    	flag--;
        postfix << aStack[--top] << " ";
                  
    }
    //check the error
    if(flag!=1)
    	return "error";
    return postfix.str();    
}

int compute(string postfix)
{
    int bstack[1000];
    int top = 0;
    istringstream post(postfix);
    string b;
    while(post >> b)
    {
    	//change from type string to type int
        if(isdigit(b[0]))
        {	
        	bstack[top++] = atoi(b.c_str());
            
        }
        else if (isdigit(b[1])){
        	bstack[top++] = atoi(b.c_str());
        }
        //calculate
        else
        {
            switch(b[0])
            {
                case '+' : 
                    bstack[top-2] = bstack[top-2] + bstack[top-1];
                   	top -= 1;
                   	break;
    				
                case '-' :
                	bstack[top-2] = bstack[top-2] - bstack[top-1];
                   	top -= 1; 
               		break;
						
    			case '*' :
                
                   	bstack[top-2] = bstack[top-2] * bstack[top-1];
                   	top -= 1;
                   	break;
                case '/' : 
                	if(bstack[top-1]==0){
                		cout<<"error"<<endl;
                		return 0;
                	}
                	else{
                    	bstack[top-2] = bstack[top-2] / bstack[top-1];
                    	top -= 1;
                   		break;
                   	}
                case '%' : 
                    if(bstack[top-1]==0){
                		cout<<"error"<<endl;
                		return 0;
                	}
                	else{
                    	bstack[top-2] = bstack[top-2] % bstack[top-1];
                    	top -= 1;
                   		break;
                   	}
            }
        }
    }
    return bstack[0];
}

int main()
{
    string input;
  
    while(getline(cin, input))
    {
        string postfix = infixtopostfix(input);
    	if (postfix=="error"||postfix=="overflow"||postfix=="underflow")
        	cout << postfix<<endl;
        else{
        	int i=compute(postfix);
        	if (i!=0)
        		cout << compute(postfix) << endl;
    	}
	}
}


