/*
   1.输入中缀表达式
   2.中缀转后缀表达式
   3.计算
   4.输出 
*/
#include "clc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR printf
#define ISRUN 1

stackNode *g_operand = NULL;	//【改】书写风格 
stackNode *g_operator = NULL;
char g_suffixExp[1024];

int main(int argc, char *argv[])
{
	printf("Please enter the calculation expression...\n\n");
	
	while (ISRUN)	 //【改】有意义变量代替常量 
	{ 	
		printf("Expression: ");
			
		char *expression = (char*)malloc(sizeof(char));
	    if (NULL == expression)	//【改】Exp内存分配检查 
	    {
	    	ERROR("Unable ot allocate memory!");
			break;	
		}
		
	    memset(g_suffixExp, '#', sizeof(g_suffixExp));	//【改】g_suffixExp[]内存初始化 
	    
		g_operand = (stackNode*)malloc(sizeof(stackNode));
		if (NULL == g_operand)
		{
			ERROR("Unable to allocate memoty!");
			break;
		}
		g_operand->next = NULL;
		MakeStackEmpty(g_operand);
	
		g_operator = (stackNode*)malloc(sizeof(stackNode));
		if (NULL == g_operator)
		{
			ERROR("Unable to allocate memory!");
			break;
		}
		g_operator->next = NULL;
		MakeStackEmpty(g_operator);	
	
		scanf("%s", expression);
	
		InfixToSuffix(expression);
		Calculation(g_suffixExp);
		
		printf("    Answer: %.2f\n\n", g_operand->next->value);
		free(expression);
		free(g_operand);
		free(g_operator);
	}
	
	return 0;
}
//判断栈空 
char IsStackEmpty(stackNode *stack)    //【改】变量名修改 
{
	return !(stack->next);
}
//清空栈 
void MakeStackEmpty(stackNode *stack)
{
	if (NULL == stack)
	{
		ERROR("Must be created first!");
		return ;
	}
	while (!IsStackEmpty(stack))
	{
		PopStack(stack);
	}
}
//入栈操作 
void PushStack(stackNode *stack, float data)
{
	stackNode *stackTemp = (stackNode*)malloc(sizeof(stackNode));
	if (NULL == stackTemp)
	{
		ERROR("Out of space!");
		return ;
	}
	stackTemp->value = data;
	stackTemp->next = stack->next;
	stack->next = stackTemp;
}
//出栈操作 
void PopStack(stackNode *stack)
{
	stackNode *top = NULL;
	if (IsStackEmpty(stack))	
	{
		ERROR("The stackNode is empty!");
		return ;
	}
	top = stack->next;
	stack->next = stack->next->next;
	free(top);
}
//中缀表达式转后缀表达式
void InfixToSuffix(char *expression)
{
	int i = 0;
    while (*expression)
    {
    	if ((*expression>='0') && (*expression<='9'))
    	{
  			while ((*expression>='0') && (*expression<='9'))
  	    	{
  				g_suffixExp[i] = *expression;
  		 		expression++;
  				i++;
	  		}
			g_suffixExp[i++] = '#';
  		}	
 	 	 /* 
 	 	    符号优先级 
 	  	    ( ------- 0
      	    + ------- 1
     	    - ------- 2
      	    * ------- 3
      	    / ------- 4
            ) ------- 
  	 	*/
  		if (*expression == '(')
  		{
  			PushStack(g_operator, 0);
  			expression++;
	 	 }
	  
		if (*expression == ')')
		{  
			while (g_operator->next->value)
			{
				switch ((int)(g_operator->next->value))     
				{
					case 1: g_suffixExp[i++] = '+'; g_suffixExp[i++] = '#'; break;
					case 2: g_suffixExp[i++] = '-'; g_suffixExp[i++] = '#'; break;
			  	 	case 3: g_suffixExp[i++] = '*'; g_suffixExp[i++] = '#'; break;
			   	 	case 4: g_suffixExp[i++] = '/'; g_suffixExp[i++] = '#'; break;
			   	 	default: break;    //【改】添加缺少的default 
				}	
				PopStack(g_operator);
			}
			PopStack(g_operator);
	    	expression++;
		}
	
  		if (*expression == '+')
  		{   
  			if ( (IsStackEmpty(g_operator)) )
	    	{
	    		PushStack(g_operator, 1);
			}
			else if (g_operator->next->value > 2)
			{
				while ((!IsStackEmpty(g_operator)) && (g_operator->next->value))
				{
 					switch ((int)(g_operator->next->value))
					{
						case 1: g_suffixExp[i++] = '+'; g_suffixExp[i++] = '#'; break;
						case 2: g_suffixExp[i++] = '-'; g_suffixExp[i++] = '#'; break;
			  	 		case 3: g_suffixExp[i++] = '*'; g_suffixExp[i++] = '#'; break;
			   	 		case 4: g_suffixExp[i++] = '/'; g_suffixExp[i++] = '#'; break;
			    		default: break;
					}
					PopStack(g_operator);
				}
				PushStack(g_operator, 1);
			}
			else
			{
				PushStack(g_operator, 1);
			}
			expression++;
  		}
  	
  		if (*expression == '-')
   		{ 
  			if ((IsStackEmpty(g_operator)))
	    	{
	    		PushStack(g_operator, 2);
			}
			else if (g_operator->next->value > 2)
			{
				while ((!IsStackEmpty(g_operator)) && (g_operator->next->value))
				{
					switch ((int)(g_operator->next->value))
					{
						case 1: g_suffixExp[i++] = '+'; g_suffixExp[i++] = '#'; break;
						case 2: g_suffixExp[i++] = '-'; g_suffixExp[i++] = '#'; break;
			  	 		case 3: g_suffixExp[i++] = '*'; g_suffixExp[i++] = '#'; break;
			   	 		case 4: g_suffixExp[i++] = '/'; g_suffixExp[i++] = '#'; break;
			    		default: break;
					}
					PopStack(g_operator);
				}
				PushStack(g_operator, 2);
			}
			else
			{
				PushStack(g_operator, 2);
			}
			expression++;
  	 	}
  		if (*expression == '*')
  		{
  	   		PushStack(g_operator, 3);
  	   		expression++;
  		}
 		if (*expression == '/')
  		{
  			PushStack(g_operator, 4);
  			expression++;
 		}
 	}  
 	while (!IsStackEmpty(g_operator))
 	{
 		switch ((int)(g_operator->next->value))
		{
			case 1: g_suffixExp[i++] = '+'; g_suffixExp[i++] = '#'; break;
			case 2: g_suffixExp[i++] = '-'; g_suffixExp[i++] = '#'; break;
			case 3: g_suffixExp[i++] = '*'; g_suffixExp[i++] = '#'; break;
			case 4: g_suffixExp[i++] = '/'; g_suffixExp[i++] = '#'; break;
			default: break;
		}
		PopStack(g_operator);
	 }
}
//计算后缀表达式 
void Calculation(char *postExp)
{
	int i = 0;
	float operandValue_a, operandValue_b, operandMidResult;
	char clcTemp[100];
    
    MakeStackEmpty(g_operand);
    MakeStackEmpty(g_operator); 
    
    while (*postExp)
    {
    	if ((*postExp >= '0') && (*postExp <= '9'))
    	{
    		while ((*postExp >= '0') && (*postExp <= '9'))
    		{
    			clcTemp[i] = *postExp;
    			i++;
    			postExp++;
			}
			PushStack(g_operand, atoi(clcTemp));
			memset(clcTemp, 0, sizeof(clcTemp));
			i = 0;
		}
		if (*postExp == '+')
 		{
 			operandValue_a = g_operand->next->value;
 			PopStack(g_operand);
 			operandValue_b = g_operand->next->value;
 			PopStack(g_operand);
 			operandMidResult = operandValue_b + operandValue_a;
 			PushStack(g_operand, operandMidResult);
	 	}
	 	if (*postExp == '-')
 		{
 			operandValue_a = g_operand->next->value;
 			PopStack(g_operand);
 			operandValue_b = g_operand->next->value;
 			PopStack(g_operand);
 			operandMidResult = operandValue_b - operandValue_a;
 			PushStack(g_operand, operandMidResult);
	 	}
	 	if (*postExp == '*')
 		{
 			operandValue_a = g_operand->next->value;
 			PopStack(g_operand);
 			operandValue_b = g_operand->next->value;
 			PopStack(g_operand);
 			operandMidResult = operandValue_b * operandValue_a;
 			PushStack(g_operand, operandMidResult);
	 	}
	 	if (*postExp == '/')
 		{
 			operandValue_a = g_operand->next->value;
 			PopStack(g_operand);
 			operandValue_b = g_operand->next->value;
 			PopStack(g_operand);
 			operandMidResult = operandValue_b / operandValue_a;
 			PushStack(g_operand, operandMidResult);
	 	}
	 	postExp++;
	}
 
 } 
