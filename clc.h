#ifndef _CLC_H_
#define _CLC_H_

struct _stackNode;
typedef struct _stackNode stackNode;

char IsStackEmpty(stackNode *stack);
void MakeStackEmpty(stackNode *stack); 
void PushStack(stackNode *stack, float data);
void PopStack (stackNode *stack) ;

void InfixToSuffix(char *expression);
void Calculation(char *postExp);

#endif 

struct _stackNode 
{
	float value;
	struct _stackNode *next;
};
