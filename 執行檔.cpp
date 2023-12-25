/* file name: infixTopostfix.c                */
/* �N�ƾǦ��l�Ѥ��Ǫ�ܪk�ର��Ǫ�ܪk */

#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#define MAX 100
#define MAXSTACK 100 /*�w�q�̤j���|�e�q*/


/* �b���Ǫ�ܪk��C�μȦs���|���A�B��l���u�����Ǫ�A���u���Ȭ�INDEX/2 */
char infix_priority[10] = { '#', ')', '+', '-', '*', '/', '^','_', '(' };
char stack_priority[9] = { '#', '_', '(', '+', '-', '*', '/', '^' };

void infix_to_postfix(char *, int);  /* �Ѥ������Ǩ�� */
int compare(char, char);  /* �����ӹB��l��� */
int calculate(char *);
int is_operator(char);
int cal(char, int, int);
int calculate_1(char*, int);
int digits_count(int);
int is_num(char);

int main()
{
	int index = -1;
	char infix_q[MAX] = { ' ' };  /* �x�s�ϥΪ̿�J���Ǧ�����C */

	printf("---------------------------------\n");
	printf("      -- Usable operator --\n");
    printf(" *: Multiply      /: Divide\n");
	printf(" +: Add           -: Subtraction\n");
	printf(" (: Left Brace    ): Right Brace\n");
	printf(" ^: Exponentiation\n");
	printf("---------------------------------\n");

	printf("�п�J���Ǫ�ܦ�: ");
	while (infix_q[index] != '\n')
		infix_q[++index] = getchar();
	infix_q[index] = '#';  /* �����ɥ[�J # �������Ÿ� */
	printf("��������Ǫ�ܦ���:");
	infix_to_postfix(infix_q, index);
	printf("\n");
	printf("���׬� = %d", calculate_1(infix_q, index));
	printf("\n");

	return 0;
}

void infix_to_postfix(char *infix_q, int index)
{
	int top = 0, ctr, tag = 1;
	char stack_t[MAX];  /* �ΥH�x�s�٤�����X���B��l */
	stack_t[top] = '#'; /* ����|�̩��U�[�J#�������Ÿ� */
	for (ctr = 0; ctr <= index; ctr++) {
		switch (infix_q[ctr]) {
			/* ��J�� )�A�h��X���|���B��l�A������|���� ( */
		case ')':
			while (stack_t[top] != '(' && stack_t[top] != '_')//�J��A����t�A��
				printf("%c", stack_t[top--]);
			if (stack_t[top] == '_'){
			printf("%s", "-1*");
			}
			top--;
			break;
			/* ��J�� #�A�h�N���|���٥���X���B��l��X */
		case '#':
			while (stack_t[top] != '#') {
				printf("%c", stack_t[top--]);
			}
			break;
			/* ��J���B��l�A�Y�p��TOP�b���|���ҫ��B��l�A�h�N���|
				���B��l��X�A������|�����B��l�p���J���B��l�A
				�Y�j�󵥩�TOP�b���|���ҫ��B��l�A�h
				�N��J���B��l�m�J���| */

		case '(': 
			if (tag == 2) {
				stack_t[top] = '_';
				tag = 1;
			}
			else {
				while (compare(stack_t[top], infix_q[ctr]))
					printf("%c", stack_t[top--]);
				stack_t[++top] = infix_q[ctr];
				tag = 1;
			}
			break;
		case '^': case '*': case '/':
			while (compare(stack_t[top], infix_q[ctr]))
				printf("%c", stack_t[top--]);
			stack_t[++top] = infix_q[ctr];
			tag = 1;
			break;
		case '+': case '-':
			if (tag == 1) { /* �P�_ (�A^�A*�A/ �᪺ - ���O�_��ܭt�� */
				stack_t[++top] = '-';
				tag = 2;  /* �N tag �]�� 2 */
			}
			else {
				while (compare(stack_t[top], infix_q[ctr]))
					printf("%c", stack_t[top--]);
				stack_t[++top] = infix_q[ctr];
				tag = 1;
			}
			break;
			/* ��J���B�⤸�A�h������X */
		default:
			if (tag == 2) /* �N�s��b���|���t����X */
				printf("%c", stack_t[top--]);
			printf("%c", infix_q[ctr]);
			tag = 0;
			break;
		}
	}
}

int calculate_1(char *infix_q, int index)
{
	int top = 0, ctr, tag = 1, j = 0, result = 0, a = 0, b = 0, digitcount = 0, num_index = 0;
	char stack_t[MAX] = { "" };  /* �ΥH�x�s�٤�����X���B��l */
	char postfix[MAX] = { "" };
	int digit[MAX] = { 0 };
	int nump[MAX] = { 0 };
	stack_t[top] = '#'; /* ����|�̩��U�[�J#�������Ÿ� */
	for (ctr = 0; ctr <= index; ctr++) {
		switch (infix_q[ctr]) {
			/* ��J�� )�A�h��X���|���B��l�A������|���� ( */
		case ')':
			while (stack_t[top] != '(' && stack_t[top] != '_') {
				postfix[j++] = stack_t[top--];
			}
			if (stack_t[top] == '_') {
				postfix[j++] = '~';
				postfix[j++] = '1';
				postfix[j++] = 'x';
				postfix[j++] = '*';
			}
			top--;
			break;
			/* ��J�� #�A�h�N���|���٥���X���B��l��X */
		case '#':
			while (stack_t[top] != '#')
			{
				postfix[j++] = (char)(stack_t[top--]);
			}

			break;
			/* ��J���B��l�A�Y�p��TOP�b���|���ҫ��B��l�A�h�N���|
				���B��l��X�A������|�����B��l�p���J���B��l�A
				�Y�j�󵥩�TOP�b���|���ҫ��B��l�A�h
				�N��J���B��l�m�J���| */

		case '(': 
			if (tag == 2) {
				stack_t[top] = '_';
				tag = 1;
			}
			else {
				while (compare(stack_t[top], infix_q[ctr])) {
					postfix[j++] = (char)(stack_t[top--]);
				}

				stack_t[++top] = infix_q[ctr];
				tag = 1;
			}
			break;
		case '^': case '*': case '/':
			while (compare(stack_t[top], infix_q[ctr])) {
				postfix[j++] = (char)(stack_t[top--]);
			}

			stack_t[++top] = infix_q[ctr];
			tag = 1;
			break;
		case '+': case '-':
			if (tag == 1) { /* �P�_ (�A^�A*�A/ �᪺ - ���O�_��ܭt�� */
				stack_t[++top] = '~';
				tag = 2;  /* �N tag �]�� 2 */
			}
			else {
				while (compare(stack_t[top], infix_q[ctr])) {
					postfix[j++] = (char)(stack_t[top--]);
				}

				stack_t[++top] = infix_q[ctr];
				tag = 1;
			}
			break;
			/* ��J���B�⤸�A�h������X */
		default:
			if (tag == 2) /* �N�s��b���|���t����X */
				postfix[j++] = stack_t[top--];
			postfix[j++] = infix_q[ctr];
			digitcount++;
			if (floor(atoi(&infix_q[ctr]) / 10) == 0)
			{
				postfix[j++] = (char)('x');
				digit[num_index++] = digitcount;
				digitcount = 0;
			}
			tag = 0;
			break;
		}

	}
	//printf("\npostfix : %s \n", postfix);
	tag = 0;
	num_index = 0;
	
	int k = 0, stk_top = 0;
	int stk[MAX] = {0};
	int num1 = 0, num2 = 0, negative = 1;
	while (k < j) {
		switch (postfix[k]) {
		case '~':
			negative = -1;
			break;
		case '+':case '-':case '*':case '/':case '^':
			num1 = stk[--stk_top];
			stk[stk_top] = '\0';
			num2 = stk[--stk_top];
			stk[stk_top++] = cal(postfix[k], num1, num2);
			num1 = 0; num2 = 0;
			break;
		case 'x':
			stk[stk_top++] = num1 * negative;
			num1 = 0, negative = 1;
			break;
		default:
			num1 = num1 * 10 + (int)(postfix[k] - '0');
		}
		k++;
	}
	result = stk[--stk_top];
	return result;
}
/*
procedure calculate (Exp)
	top��1; x��Next_token(Exp)
	while (x�ڡ�#��) {
		if (x is an operand) then
			call push (x, STACK)
		else {  �ھ� operator ���S�ʡApop �X�A�� operand �Ӽ�
			remove the correct number of operand,
			perform the operation and
			push the result into stack
		}
		x��Next_token (Exp);
	}
	call pop (ans, STACK)
end procedure*/
int is_num(char var1) {

	if (var1 >= '0' && var1 <= '9')
		return 1;
	else
		return 0;

}

int is_operator(char operator_1) {

	switch (operator_1)
	{
	case '+': case '-': case '*': case '/': case '^':
		return 1;

	default:
		return 0;
	}

}
int cal(char op, int r1, int r2) {
	switch (op) {
	case '+': return r1 + r2;
	case '-': return r1 - r2;
	case '*': return r1 * r2;
	case '/': return r1 / r2;
	case '^': return pow(r1, r2);
	}
}



int digits_count(int n) {
	int x = 0;
	while (n != 0)
	{
		// n = n/10
		n /= 10;
		++x;
	}
	return x;
}

int compare(char stack_o, char infix_o)
{
	int index_1 = 0, index_2 = 0;
	while (stack_priority[index_1] != stack_o)
		index_1++;
	while (infix_priority[index_2] != infix_o)
		index_2++;
	return index_1 / 2 >= index_2 / 2 ? 1 : 0;
}




