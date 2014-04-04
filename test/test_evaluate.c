#include "unity.h"
#include "evaluate.h"
#include "Error.h"
#include "mock_Token.h"
#include "mock_Stack.h"
#include <malloc.h>
#include <stdio.h>
#include <CException.h>

void setUp(void){}
void tearDown(void){}

void test_multiply(){TEST_ASSERT_EQUAL(200,multiply(10,20));}
void test_devide(){TEST_ASSERT_EQUAL(25,devide(50,2));}
void test_modulo(){TEST_ASSERT_EQUAL(1,modulo(5,2));}
void test_plus(){TEST_ASSERT_EQUAL(3,plus(1,2));}
void test_minus(){TEST_ASSERT_EQUAL(50,minus(100,50));}
void test_xor(){TEST_ASSERT_EQUAL(0b10,xor(0b11,0b01));}
void test_and(){TEST_ASSERT_EQUAL(0x5A,and(0xFF,0x5A));}
void test_or(){TEST_ASSERT_EQUAL(0b1111,xor(0b1111,0b0000));}

void test_evaluateOperator_given_plus_should_multiply_2_values(){
	Stack dataStack;
	OperatorToken multiply = {.type=OPERATOR_TOKEN ,.name = "*",.precedence = 100};
	NumberToken value10 = {.type=NUMBER_TOKEN ,.value = 10};
	NumberToken value20 = {.type=NUMBER_TOKEN ,.value = 20};
	NumberToken value30 = {.type=NUMBER_TOKEN ,.value = 200};
	
	pop_ExpectAndReturn(&dataStack, &value10);
	pop_ExpectAndReturn(&dataStack, &value20);
	createNumberToken_ExpectAndReturn(200 , &value30);
	push_Expect(&dataStack, &value30);
	
	evaluateOperator(&dataStack, &multiply);
}
void test_evaluateOperator_given_plus_should_divide_2_values(){
	Stack dataStack;
	OperatorToken divide = {.type=OPERATOR_TOKEN ,.name = "/",.precedence = 100};
	NumberToken value10 = {.type=NUMBER_TOKEN ,.value = 100};
	NumberToken value20 = {.type=NUMBER_TOKEN ,.value = 2};
	NumberToken value30 = {.type=NUMBER_TOKEN ,.value = 50};
	
	pop_ExpectAndReturn(&dataStack, &value10);
	pop_ExpectAndReturn(&dataStack, &value20);
	createNumberToken_ExpectAndReturn(50 , &value30);
	push_Expect(&dataStack, &value30);
	
	evaluateOperator(&dataStack, &divide);
}
void test_evaluateOperator_given_plus_should_modulo_2_values(){
	Stack dataStack;
	OperatorToken modulo = {.type=OPERATOR_TOKEN ,.name = "%",.precedence = 100};
	NumberToken value10 = {.type=NUMBER_TOKEN ,.value = 100};
	NumberToken value20 = {.type=NUMBER_TOKEN ,.value = 3};
	NumberToken value30 = {.type=NUMBER_TOKEN ,.value = 1};
	
	pop_ExpectAndReturn(&dataStack, &value10);
	pop_ExpectAndReturn(&dataStack, &value20);
	createNumberToken_ExpectAndReturn(1 , &value30);
	push_Expect(&dataStack, &value30);
	
	evaluateOperator(&dataStack, &modulo);
}
void test_evaluateOperator_given_plus_should_plus_2_values(){
	Stack dataStack;
	OperatorToken plus = {.type=OPERATOR_TOKEN ,.name = "+",.precedence = 70};
	NumberToken value10 = {.type=NUMBER_TOKEN ,.value = 10};
	NumberToken value20 = {.type=NUMBER_TOKEN ,.value = 20};
	NumberToken value30 = {.type=NUMBER_TOKEN ,.value = 30};
	
	pop_ExpectAndReturn(&dataStack, &value10);
	pop_ExpectAndReturn(&dataStack, &value20);
	createNumberToken_ExpectAndReturn(30 , &value30);
	push_Expect(&dataStack, &value30);
	
	evaluateOperator(&dataStack, &plus);
}
void test_evaluateOperator_given_plus_should_minus_2_values(){
	Stack dataStack;
	OperatorToken minus = {.type=OPERATOR_TOKEN ,.name = "-",.precedence = 70};
	NumberToken value10 = {.type=NUMBER_TOKEN ,.value = 50};
	NumberToken value20 = {.type=NUMBER_TOKEN ,.value = 20};
	NumberToken value30 = {.type=NUMBER_TOKEN ,.value = 30};
	
	pop_ExpectAndReturn(&dataStack, &value10);
	pop_ExpectAndReturn(&dataStack, &value20);
	createNumberToken_ExpectAndReturn(30 , &value30);
	push_Expect(&dataStack, &value30);
	
	evaluateOperator(&dataStack, &minus);
}
void test_evaluateOperator_given_plus_should_xor_2_values(){
	Stack dataStack;
	OperatorToken xor = {.type=OPERATOR_TOKEN ,.name = "^" ,.precedence = 50};
	NumberToken value10 = {.type=NUMBER_TOKEN ,.value = 0b1111};
	NumberToken value20 = {.type=NUMBER_TOKEN ,.value = 0b0011};
	NumberToken value30 = {.type=NUMBER_TOKEN ,.value = 0b1100};
	
	pop_ExpectAndReturn(&dataStack, &value10);
	pop_ExpectAndReturn(&dataStack, &value20);
	createNumberToken_ExpectAndReturn(0b1100 , &value30);
	push_Expect(&dataStack, &value30);
	
	evaluateOperator(&dataStack, &xor);
}
void test_evaluateOperator_given_plus_should_and_2_values(){
	Stack dataStack;
	OperatorToken and = {.type=OPERATOR_TOKEN ,.name = "&" ,.precedence = 20};
	NumberToken value10 = {.type=NUMBER_TOKEN ,.value = 0xFF};
	NumberToken value20 = {.type=NUMBER_TOKEN ,.value = 0x5A};
	NumberToken value30 = {.type=NUMBER_TOKEN ,.value = 0x5A};
	
	pop_ExpectAndReturn(&dataStack, &value10);
	pop_ExpectAndReturn(&dataStack, &value20);
	createNumberToken_ExpectAndReturn(0x5A , &value30);
	push_Expect(&dataStack, &value30);
	
	evaluateOperator(&dataStack, &and);
}
void test_evaluateOperator_given_plus_should_or_2_values(){
	Stack dataStack;
	OperatorToken or = {.type=OPERATOR_TOKEN ,.name = "|" ,.precedence = 10};
	NumberToken value10 = {.type=NUMBER_TOKEN ,.value = 0b1111};
	NumberToken value20 = {.type=NUMBER_TOKEN ,.value = 0b0000};
	NumberToken value30 = {.type=NUMBER_TOKEN ,.value = 0b1111};
	
	pop_ExpectAndReturn(&dataStack, &value10);
	pop_ExpectAndReturn(&dataStack, &value20);
	createNumberToken_ExpectAndReturn(0b1111 , &value30);
	push_Expect(&dataStack, &value30);
	
	evaluateOperator(&dataStack, &or);
}

void test_evaluateAllOperatorsOnStack(){
	Stack dataStack,operatorStack;
	OperatorToken plus = {.type=OPERATOR_TOKEN ,.name = "+"	,.precedence = 70};
	OperatorToken minus = {.type=OPERATOR_TOKEN ,.name = "-",.precedence = 70};
	NumberToken value1 = {.type=NUMBER_TOKEN ,.value = 1};
	NumberToken value2 = {.type=NUMBER_TOKEN ,.value = 2};
	NumberToken value3 = {.type=NUMBER_TOKEN ,.value = 3};
	NumberToken value4 = {.type=NUMBER_TOKEN ,.value = 2};
	NumberToken value5 = {.type=NUMBER_TOKEN ,.value = 1};
	
	pop_ExpectAndReturn(&operatorStack,&plus);
	pop_ExpectAndReturn(&dataStack, &value1);
	pop_ExpectAndReturn(&dataStack, &value2);
	createNumberToken_ExpectAndReturn(3 , &value3);
	push_Expect(&dataStack, &value3);
	
	pop_ExpectAndReturn(&operatorStack,&minus);
	pop_ExpectAndReturn(&dataStack, &value3);
	pop_ExpectAndReturn(&dataStack, &value4);
	createNumberToken_ExpectAndReturn(1 , &value5);
	push_Expect(&dataStack, &value5);
	
	
	evaluateOperator(&dataStack, &plus);
	evaluateAllOperatorsOnStack(&dataStack, &operatorStack);
}

