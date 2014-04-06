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

int evaluate(Stack *dataStack, Stack *operatorStack,  char *expression){
	int i =0;
	Tokenizer *tokenizer;
	Token *token;
	NumberToken *number;
	OperatorToken *operator;
	tokenizer = tokenizerNew(expression);
	
	for(i = 0; i < 3; i++){
	token = nextToken(tokenizer);
		if(i%2==0){
			if(token->type == NUMBER_TOKEN)push(dataStack, (NumberToken *)token);
			else Throw(ERR_NOT_DATA);
		}
		else{
			if(token->type == OPERATOR_TOKEN)push(operatorStack, (OperatorToken *)token);
			else Throw(ERR_NOT_OPERATOR);
		}
	}
	token = nextToken(tokenizer);
	while(token !=NULL){
		if(token->type != OPERATOR_TOKEN)Throw(ERR_NOT_OPERATOR);
		tryEvaluateOperatorOnStackThenPush(dataStack, operatorStack,(OperatorToken *)token);
	token = nextToken(tokenizer);
	if(token != NULL) {
		if(token->type == NUMBER_TOKEN) {push(dataStack, (NumberToken *)token);}
		else {Throw(ERR_NOT_DATA);}
	}
	else{Throw(ERR_INVALID_EXPRESSION);}
	token = nextToken(tokenizer);
	}
	evaluateAllOperatorsOnStack(dataStack,operatorStack);
	number =pop(dataStack);
	return number->value;
}

void tryEvaluateOperatorOnStackThenPush(Stack *dataStack,Stack *operatorStack, OperatorToken *operator){
	OperatorToken *OperatorTOS;
	do{
	OperatorTOS = pop(operatorStack);
	if((operator->precedence) > OperatorTOS->precedence){
	push(operatorStack,OperatorTOS);
	push(operatorStack,operator);
	break;}
	else{evaluateOperator(dataStack, OperatorTOS);}
	}
	while((OperatorTOS = pop(operatorStack)) !=NULL);
	//push(operatorStack,operator);
}
void evaluateAllOperatorsOnStack(Stack *dataStack,Stack *operatorStack){
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