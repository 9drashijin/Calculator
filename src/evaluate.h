#ifndef evaluate_H
#define evaluate_H

#include "Token.h"
#include "Stack.h"

typedef struct{
	char* operator;
	int (*callback)(int , int);
}OperatorTable;

int evaluate(char *expression);
void tryEvaluateOperatorOnStackThenPush(Stack *operatorStack, Stack *dataStack, OperatorToken *operator);
void evaluateAllOperatorsOnStack(Stack *operatorStack, Stack *dataStack);
void evaluateOperator(Stack *dataStack, OperatorToken *operator);

int multiply(int value1, int value2);
int devide(int value1, int value2);
int modulo(int value1, int value2);
int plus(int value1, int value2);
int minus(int value1, int value2);
int xor(int value1, int value2);
int and(int value1, int value2);
int or(int value1, int value2);
#endif // evaluate_H
