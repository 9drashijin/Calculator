#include "evaluate.h"
// #include "Token.h"
// #include "Stack.h"
#include "Error.h"
#include <stdio.h>
#include <CException.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

OperatorTable Operator[] = {
            {.operator = "*",.callback = multiply},
            {.operator = "/",.callback = devide},
			{.operator = "%",.callback = modulo},
			{.operator = "+",.callback = plus},
			{.operator = "-",.callback = minus},
			{.operator = "^",.callback = xor},
			{.operator = "&",.callback = and},
			{.operator = "|",.callback = or},
            };	

int evaluate(char *expression){
	return 1;
}

void tryEvaluateOperatorOnStackThenPush(Stack *operatorStack, Stack *dataStack, OperatorToken *operator){
	
}
void evaluateAllOperatorsOnStack(Stack *operatorStack, Stack *dataStack){
	OperatorToken *operator;
	while((operator = pop(operatorStack)) != NULL){
		evaluateOperator(dataStack, operator);
	}
}
void evaluateOperator(Stack *dataStack, OperatorToken *operator){
	NumberToken *resultToken;
	NumberToken *value1 = pop(dataStack);
	NumberToken *value2 = pop(dataStack);
	int i = 0 ,result;
	
	for(i = 0; i<8 ;i ++){
		if(strcmp(Operator[i].operator,operator->name) == 0){
		result = Operator[i].callback(value1->value,value2->value);
		break;
		}
	}
	resultToken = createNumberToken(result);
	push(dataStack, resultToken);
}

int multiply(int value1, int value2){return value1*value2;}
int devide(int value1, int value2){return value1/value2;}
int modulo(int value1, int value2){return value1%value2;}
int plus(int value1, int value2){return value1+value2;}
int minus(int value1, int value2){return value1-value2;}
int xor(int value1, int value2){return value1^value2;}
int and(int value1, int value2){return value1&value2;}
int or(int value1, int value2){return value1|value2;}