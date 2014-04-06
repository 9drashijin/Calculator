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

void test_evaluateOperator_given_multiply_should_multiply_2_values(){
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
void test_evaluateOperator_given_divide_should_divide_2_values(){
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
void test_evaluateOperator_given_modulo_should_modulo_2_values(){
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
void test_evaluateOperator_given_minus_should_minus_2_values(){
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
void test_evaluateOperator_given_xor_should_xor_2_values(){
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
void test_evaluateOperator_given_and_should_and_2_values(){
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
void test_evaluateOperator_given_or_should_or_2_values(){
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
	Stack dataStack;
	Stack Stackoperator;
	OperatorToken plus = {.type=OPERATOR_TOKEN ,.name = "+"	,.precedence = 70};
	OperatorToken minus = {.type=OPERATOR_TOKEN ,.name = "-",.precedence = 70};
	NumberToken value1 = {.type=NUMBER_TOKEN ,.value = 1};
	NumberToken value2 = {.type=NUMBER_TOKEN ,.value = 2};
	NumberToken value3 = {.type=NUMBER_TOKEN ,.value = 3};
	NumberToken value4 = {.type=NUMBER_TOKEN ,.value = 2};
	NumberToken value5 = {.type=NUMBER_TOKEN ,.value = 1};
	
	pop_ExpectAndReturn(&Stackoperator,&plus);
	pop_ExpectAndReturn(&dataStack, &value1);
	pop_ExpectAndReturn(&dataStack, &value2);
	createNumberToken_ExpectAndReturn(3 , &value3);
	push_Expect(&dataStack, &value3);
	
	pop_ExpectAndReturn(&Stackoperator,&minus);
	pop_ExpectAndReturn(&dataStack, &value3);
	pop_ExpectAndReturn(&dataStack, &value4);
	createNumberToken_ExpectAndReturn(1 , &value5);
	push_Expect(&dataStack, &value5);
	
	pop_ExpectAndReturn(&Stackoperator,NULL);
	evaluateAllOperatorsOnStack(&dataStack, &Stackoperator);
}
void test_evaluateAllOperatorsOnStack_with_more_operator(){
	Stack dataStack;
	Stack Stackoperator;
	OperatorToken multiply = {.type=OPERATOR_TOKEN ,.name = "*"	,.precedence = 100};
	OperatorToken divide = {.type=OPERATOR_TOKEN ,.name = "/"	,.precedence = 100};
	OperatorToken plus = {.type=OPERATOR_TOKEN ,.name = "+",.precedence = 70};
	OperatorToken minus = {.type=OPERATOR_TOKEN ,.name = "-",.precedence = 70};
	NumberToken value1 = {.type=NUMBER_TOKEN ,.value = 10};
	NumberToken value2 = {.type=NUMBER_TOKEN ,.value = 10};
	NumberToken value3 = {.type=NUMBER_TOKEN ,.value = 100};
	NumberToken value4 = {.type=NUMBER_TOKEN ,.value = 2};
	NumberToken value5 = {.type=NUMBER_TOKEN ,.value = 50};
	NumberToken value6 = {.type=NUMBER_TOKEN ,.value = 10};
	NumberToken value7 = {.type=NUMBER_TOKEN ,.value = 60};
	NumberToken value8 = {.type=NUMBER_TOKEN ,.value = 100};
	NumberToken value9 = {.type=NUMBER_TOKEN ,.value = -40};
	
	pop_ExpectAndReturn(&Stackoperator,&multiply);
	pop_ExpectAndReturn(&dataStack, &value1);
	pop_ExpectAndReturn(&dataStack, &value2);
	createNumberToken_ExpectAndReturn(100 , &value3);
	push_Expect(&dataStack, &value3);
	
	pop_ExpectAndReturn(&Stackoperator,&divide);
	pop_ExpectAndReturn(&dataStack, &value3);
	pop_ExpectAndReturn(&dataStack, &value4);
	createNumberToken_ExpectAndReturn(50 , &value5);
	push_Expect(&dataStack, &value5);
	
	pop_ExpectAndReturn(&Stackoperator,&plus);
	pop_ExpectAndReturn(&dataStack, &value5);
	pop_ExpectAndReturn(&dataStack, &value6);
	createNumberToken_ExpectAndReturn(60 , &value7);
	push_Expect(&dataStack, &value7);
	
	pop_ExpectAndReturn(&Stackoperator,&minus);
	pop_ExpectAndReturn(&dataStack, &value7);
	pop_ExpectAndReturn(&dataStack, &value8);
	createNumberToken_ExpectAndReturn(-40 , &value9);
	push_Expect(&dataStack, &value9);
	
	pop_ExpectAndReturn(&Stackoperator,NULL);
	evaluateAllOperatorsOnStack(&dataStack, &Stackoperator);
}

void test_tryEvaluateOperatorOnStackThenPush(){
	Stack dataStack;
	Stack Stackoperator;
	
	OperatorToken plus = {.type=OPERATOR_TOKEN ,.name = "+"	,.precedence = 70};
	OperatorToken multiply = {.type=OPERATOR_TOKEN ,.name = "*",.precedence = 100};
	NumberToken value1 = {.type=NUMBER_TOKEN ,.value = 10};
	NumberToken value2 = {.type=NUMBER_TOKEN ,.value = 10};
	NumberToken value3 = {.type=NUMBER_TOKEN ,.value = 100};
	NumberToken value4 = {.type=NUMBER_TOKEN ,.value = 20};
	NumberToken value5 = {.type=NUMBER_TOKEN ,.value = 120};
	
	pop_ExpectAndReturn(&Stackoperator,&multiply);
	pop_ExpectAndReturn(&dataStack, &value1);
	pop_ExpectAndReturn(&dataStack, &value2);
	createNumberToken_ExpectAndReturn(100 , &value3);
	push_Expect(&dataStack, &value3);
	
	pop_ExpectAndReturn(&Stackoperator,NULL);
	//push_Expect(&dataStack, &plus);
	
	tryEvaluateOperatorOnStackThenPush(&dataStack,&Stackoperator,&plus);
}
void test_tryEvaluateOperatorOnStackThenPush_2ndTest(){
	Stack dataStack;
	Stack Stackoperator;
	
	OperatorToken and = {.type=OPERATOR_TOKEN ,.name = "&"	,.precedence = 20};
	OperatorToken or = {.type=OPERATOR_TOKEN ,.name = "|",.precedence = 10};
	NumberToken value1 = {.type=NUMBER_TOKEN ,.value = 0b1010};
	NumberToken value2 = {.type=NUMBER_TOKEN ,.value = 0b1111};
	NumberToken value3 = {.type=NUMBER_TOKEN ,.value = 0b1010};
	
	pop_ExpectAndReturn(&Stackoperator,&and);
	pop_ExpectAndReturn(&dataStack, &value1);
	pop_ExpectAndReturn(&dataStack, &value2);
	createNumberToken_ExpectAndReturn(0b1010 , &value3);
	push_Expect(&dataStack, &value3);
	
	pop_ExpectAndReturn(&Stackoperator,NULL);
	
	tryEvaluateOperatorOnStackThenPush(&dataStack,&Stackoperator,&or);
}
//fail
void test_evaluate_plus(){
	Stack dataStack;
	Stack Stackoperator;
	ErrorCode e;
	
	Tokenizer tokenizer = {.expression = "+" , .startIndex = 0};
	OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+" , .precedence = 70};
	
	tokenizerNew_ExpectAndReturn("+",&tokenizer);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&plus);
	Try{
		evaluate(&dataStack,&Stackoperator,"+");
	}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_NOT_DATA,e);
	}
}
void test_evaluate_38_39(){
	Stack dataStack;
	Stack Stackoperator;
	ErrorCode e;
	
	Tokenizer tokenizer = {.expression = "38 39" , .startIndex = 0};
	NumberToken value1 = {.type = NUMBER_TOKEN, .value = 38};
	NumberToken value2 = {.type = NUMBER_TOKEN, .value = 39};
	
	tokenizerNew_ExpectAndReturn("38 39",&tokenizer);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&value1);
	push_Expect(&dataStack, &value1);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&value2);
	Try{
		evaluate(&dataStack,&Stackoperator,"38 39");
	}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_NOT_OPERATOR,e);
	}
}
void test_evaluate_40(){
	Stack dataStack;
	Stack Stackoperator;
	ErrorCode e;
	
	Tokenizer tokenizer = {.expression = "40 + *", .startIndex = 0};
	NumberToken value1 = {.type = NUMBER_TOKEN, .value = 40};
	OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};	
	OperatorToken multiply = {.type = OPERATOR_TOKEN, .name = "*", .precedence = 100};
	
	tokenizerNew_ExpectAndReturn("40 + *", &tokenizer);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&value1);
	push_Expect(&dataStack, &value1);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&plus);
	push_Expect(&Stackoperator, &plus);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&multiply);
	
	Try{
		evaluate(&dataStack,&Stackoperator,"40 + *");
	}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_NOT_DATA,e);
	}
}
void test_evaluate_42(){
	Stack dataStack;
	Stack Stackoperator;
	ErrorCode e;
	
	Tokenizer tokenizer = {.expression = "42 ^ 2 -", .startIndex = 0};
	NumberToken value1 = {.type = NUMBER_TOKEN, .value = 42};
	NumberToken value2 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken answer = {.type = NUMBER_TOKEN, .value = 40};
	OperatorToken xor = {.type = OPERATOR_TOKEN, .name = "^", .precedence = 50};	
	OperatorToken minus = {.type = OPERATOR_TOKEN, .name = "-", .precedence = 70};
	
	tokenizerNew_ExpectAndReturn("42 ^ 2 -",&tokenizer);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&value1);
	push_Expect(&dataStack, &value1);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&xor);
	push_Expect(&Stackoperator, &xor);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&value2);
	push_Expect(&dataStack, &value2);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&minus);
	
	pop_ExpectAndReturn(&Stackoperator, &xor);
	push_Expect(&Stackoperator, &xor);
	push_Expect(&Stackoperator, &minus);
	nextToken_ExpectAndReturn(&tokenizer, NULL);
	Try{
		evaluate(&dataStack,&Stackoperator,"42 ^ 2 -");
	}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_INVALID_EXPRESSION,e);
	}
}
void test_evaluate_43(){
	Stack dataStack;
	Stack Stackoperator;
	ErrorCode e;
	
	Tokenizer tokenizer = {.expression = "43 #", .startIndex = 0};
	NumberToken value1 = {.type = NUMBER_TOKEN, .value = 43};

	tokenizerNew_ExpectAndReturn("43 #", &tokenizer);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&value1);
	push_Expect(&dataStack, &value1);
	nextToken_ExpectAndThrow(&tokenizer, ERR_INVALID_EXPRESSION);

	Try{
		evaluate(&dataStack,&Stackoperator,"43 #");
	}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_INVALID_EXPRESSION,e);
	}
}

//pass
void test_evaluate_given_1_plus_2_return3(){
	Stack dataStack;
	Stack Stackoperator;
	int answer;
	Tokenizer tokenizer = {.expression = "1 + 2" , .startIndex = 0};
	OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+" , .precedence = 70};
	NumberToken value1 = {.type = NUMBER_TOKEN, .value = 1};
	NumberToken value2 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken value3 = {.type = NUMBER_TOKEN, .value = 3};
	
	tokenizerNew_ExpectAndReturn("1 + 2", &tokenizer);
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&value1);
	push_Expect(&dataStack,&value1);
	
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&plus);
	push_Expect(&Stackoperator,&plus);
	
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&value2);
	push_Expect(&dataStack,&value2);
	nextToken_ExpectAndReturn(&tokenizer, NULL);
	
	pop_ExpectAndReturn(&Stackoperator,&plus);
	pop_ExpectAndReturn(&dataStack,&value2);
	pop_ExpectAndReturn(&dataStack,&value1);
	createNumberToken_ExpectAndReturn(3,&value3);
	push_Expect(&dataStack,&value3);
	pop_ExpectAndReturn(&Stackoperator, NULL);
	
	pop_ExpectAndReturn(&dataStack,&value3);
	answer = evaluate(&dataStack,&Stackoperator,"1 + 2");
	TEST_ASSERT_EQUAL(3,answer);
}
void test_evaluate_given_4_times_3_should_return_3(){
	Stack dataStack;
	Stack Stackoperator;
	int answer;
	Tokenizer tokenizer = {.expression = "4 * 3" , .startIndex = 0};
	OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "*" , .precedence = 100};
	NumberToken value1 = {.type = NUMBER_TOKEN, .value = 4};
	NumberToken value2 = {.type = NUMBER_TOKEN, .value = 3};
	NumberToken value3 = {.type = NUMBER_TOKEN, .value = 12};
	
	tokenizerNew_ExpectAndReturn("4 * 3", &tokenizer);
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&value1);
	push_Expect(&dataStack,&value1);
	
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&plus);
	push_Expect(&Stackoperator,&plus);
	
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&value2);
	push_Expect(&dataStack,&value2);
	nextToken_ExpectAndReturn(&tokenizer, NULL);
	
	pop_ExpectAndReturn(&Stackoperator,&plus);
	pop_ExpectAndReturn(&dataStack,&value2);
	pop_ExpectAndReturn(&dataStack,&value1);
	createNumberToken_ExpectAndReturn(12,&value3);
	push_Expect(&dataStack,&value3);
	pop_ExpectAndReturn(&Stackoperator, NULL);
	
	pop_ExpectAndReturn(&dataStack,&value3);
	answer = evaluate(&dataStack,&Stackoperator,"4 * 3");
	TEST_ASSERT_EQUAL(12,answer);
}
void test_evaluate_given_3_plus_4_plus_5_minus_6_should_return_6(){
	Stack dataStack;
	Stack Stackoperator;
	int answer;
	Tokenizer tokenizer = {.expression = "3 + 4 + 5 - 6" , .startIndex = 0};
	OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+" , .precedence = 70};
	OperatorToken minus = {.type = OPERATOR_TOKEN, .name = "-" , .precedence = 70};
	NumberToken value1 = {.type = NUMBER_TOKEN, .value = 3};
	NumberToken value2 = {.type = NUMBER_TOKEN, .value = 4};
	NumberToken value3 = {.type = NUMBER_TOKEN, .value = 7};
	NumberToken value4 = {.type = NUMBER_TOKEN, .value = 5};
	NumberToken value5 = {.type = NUMBER_TOKEN, .value = 12};
	NumberToken value6 = {.type = NUMBER_TOKEN, .value = 6};
	NumberToken value7 = {.type = NUMBER_TOKEN, .value = 6};
	
	tokenizerNew_ExpectAndReturn("3 + 4 + 5 - 6", &tokenizer);
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&value1);
	push_Expect(&dataStack,&value1);
	
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&plus);
	push_Expect(&Stackoperator,&plus);
	
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&value2);
	push_Expect(&dataStack,&value2);
	
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&plus);
	
	pop_ExpectAndReturn(&Stackoperator,&plus);
	pop_ExpectAndReturn(&dataStack,&value2);
	pop_ExpectAndReturn(&dataStack,&value1);
	createNumberToken_ExpectAndReturn(7,&value3);
	push_Expect(&dataStack,&value3);
	pop_ExpectAndReturn(&Stackoperator, NULL);
	
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&value4);
	push_Expect(&dataStack,&value4);
	
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&minus);
	
	pop_ExpectAndReturn(&Stackoperator,&plus);
	pop_ExpectAndReturn(&dataStack,&value3);
	pop_ExpectAndReturn(&dataStack,&value4);
	createNumberToken_ExpectAndReturn(12,&value5);
	push_Expect(&dataStack,&value5);
	pop_ExpectAndReturn(&Stackoperator, NULL);
	
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&value6);
	push_Expect(&dataStack,&value6);
	
	nextToken_ExpectAndReturn(&tokenizer, NULL);
	
	pop_ExpectAndReturn(&Stackoperator,&minus);
	pop_ExpectAndReturn(&dataStack,&value5);
	pop_ExpectAndReturn(&dataStack,&value6);
	createNumberToken_ExpectAndReturn(6,&value7);
	push_Expect(&dataStack,&value7);
	pop_ExpectAndReturn(&Stackoperator, NULL);

	pop_ExpectAndReturn(&dataStack, &value7);

	answer=evaluate(&dataStack,&Stackoperator,"3 + 4 + 5 - 6");
	TEST_ASSERT_EQUAL(6,answer);
}
void xtest_evaluate_given_266_or_27_xor_28_plus_29_and_30_should_return_17(){
	Stack dataStack;
	Stack Stackoperator;
	int answer;
	ErrorCode e;
	Tokenizer tokenizer = {.expression = "266 | 27 ^ 28 + 29 & 30" , .startIndex = 0};
	OperatorToken or = {.type = OPERATOR_TOKEN, .name = "|", .precedence = 10};
	OperatorToken xor = {.type = OPERATOR_TOKEN, .name = "^", .precedence = 50};	
	OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};
	OperatorToken and = {.type = OPERATOR_TOKEN, .name = "&", .precedence = 20};
	NumberToken value266 = {.type = NUMBER_TOKEN, .value = 266};
	NumberToken value27 = {.type = NUMBER_TOKEN, .value = 27};
	NumberToken value28 = {.type = NUMBER_TOKEN, .value = 28};
	NumberToken value29 = {.type = NUMBER_TOKEN, .value = 29};
	NumberToken value30 = {.type = NUMBER_TOKEN, .value = 30};
	NumberToken value57 = {.type = NUMBER_TOKEN, .value = 57};
	NumberToken value34 = {.type = NUMBER_TOKEN, .value = 34};
	NumberToken value2 = {.type = NUMBER_TOKEN, .value = 2};
	
	tokenizerNew_ExpectAndReturn("266 | 27 ^ 28 + 29 & 30", &tokenizer);
	
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&value266);
	push_Expect(&dataStack,&value266);
	
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&or);
	push_Expect(&Stackoperator,&or);
	
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&value27);
	push_Expect(&dataStack,&value27);
	
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&xor);
	pop_ExpectAndReturn(&Stackoperator, &or);
	push_Expect(&Stackoperator, &or);
	push_Expect(&Stackoperator, &xor);
	
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&value28);
	push_Expect(&dataStack,&value28);
	
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&plus);
	pop_ExpectAndReturn(&Stackoperator, &xor);
	push_Expect(&Stackoperator, &xor);
	push_Expect(&Stackoperator, &plus);
	
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&value29);
	push_Expect(&dataStack,&value29);
	
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&and);
	
	pop_ExpectAndReturn(&Stackoperator,&plus);
	pop_ExpectAndReturn(&dataStack,&value28);
	pop_ExpectAndReturn(&dataStack,&value27);
	createNumberToken_ExpectAndReturn(57,&value57);
	push_Expect(&dataStack,&value57);
	
	pop_ExpectAndReturn(&Stackoperator,&xor);
	pop_ExpectAndReturn(&dataStack,&value57);
	pop_ExpectAndReturn(&dataStack,&value27);
	createNumberToken_ExpectAndReturn(34,&value34);
	push_Expect(&dataStack,&value34);
	
	pop_ExpectAndReturn(&Stackoperator, &or);
	push_Expect(&Stackoperator, &or);
	push_Expect(&Stackoperator, &and);
	
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&value30);
	push_Expect(&dataStack,&value30);
	nextToken_ExpectAndReturn(&tokenizer, NULL);
	
	pop_ExpectAndReturn(&Stackoperator,&and);
	pop_ExpectAndReturn(&dataStack,&value30);
	pop_ExpectAndReturn(&dataStack,&value34);
	createNumberToken_ExpectAndReturn(2,&value2);
	push_Expect(&dataStack,&value2);
	
	pop_ExpectAndReturn(&Stackoperator,&or);
	pop_ExpectAndReturn(&dataStack,&value2);
	pop_ExpectAndReturn(&dataStack,&value266);
	createNumberToken_ExpectAndReturn(266,&value266);
	push_Expect(&dataStack,&value266);
	pop_ExpectAndReturn(&Stackoperator, NULL);
	pop_ExpectAndReturn(&dataStack, &value266);
	
	Try{
	answer=evaluate(&dataStack,&Stackoperator,"266 | 27 ^ 28 + 29 & 30");
	TEST_ASSERT_EQUAL(266,answer);
	}Catch(e){
	TEST_ASSERT_EQUAL(ERR_NOT_DATA,e);
	}
}
