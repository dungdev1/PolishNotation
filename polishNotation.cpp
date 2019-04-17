#include <stdio.h>
#include <iostream>
#include<string.h>
using namespace std;

#define MAX 100

bool isEmpty(char Stack[], int nStack)
{
	return (nStack == 0);
}

bool isFull(char Stack[], int nStack)
{
	return (nStack == MAX);
}

int size(char Stack[], int nStack)
{
	return nStack;
}

char top(char Stack[], int nStack)
{
	return Stack[nStack - 1];
}

//Đẩy vào stack
bool push(char Stack[], int &nStack, char value)
{
	if (isFull(Stack, nStack)) return false;

	Stack[nStack] = value;
	nStack++;
	return true;
}

//Lấy ra khỏi stack
bool pop(char Stack[], int &nStack, char &value)
{
	if (isEmpty(Stack, nStack)) return false;

	value = Stack[nStack - 1];
	nStack--;
	return true;
}

bool isEmpty2(double Stack[], int nStack)
{
	return (nStack == 0);
}

bool isFull2(double Stack[], int nStack)
{
	return (nStack == MAX);
}

int size2(double Stack[], int nStack)
{
	return nStack;
}

double top(double Stack[], int nStack)
{
	return Stack[nStack - 1];
}

//Đẩy vào stack
bool push2(double Stack[], int &nStack, double value)
{
	if (isFull2(Stack, nStack)) return false;

	Stack[nStack] = value;
	nStack++;
	return true;
}

//Lấy ra khỏi stack
bool pop2(double Stack[], int &nStack, double &value)
{
	if (isEmpty2(Stack, nStack)) return false;

	value = Stack[nStack - 1];
	nStack--;
	return true;
}

int sizeQueue(char Queue[], int front, int rear)
{
	return (front == -1) ? 0 : (rear - front + 1);
}
bool isEmptyQueue(char Queue[], int front, int rear)
{
	return sizeQueue(Queue, front, rear) == 0;
}
bool isFullQueue(char Queue[], int front, int rear)
{
	return (sizeQueue(Queue, front, rear) == MAX);
}
bool getFront(char Queue[], int &front, int rear, char &value)
{
	if (isEmptyQueue(Queue, front, rear)) 
		return false;

	value = Queue[front];
	return true;
}

bool enQueue(char Queue[], int &front, int &rear, int value)
{
	if (isFullQueue(Queue, front, rear))
		return false;
	
	Queue[rear + 1] = value;
	if (front == -1) front = 0;
	rear++;
	return true;
}

bool deQueue(char Queue[], int &front, int rear, char &value)
{
	if (isEmptyQueue(Queue, front, rear))
		return false;

	value = Queue[front];
	front++;
	return true;
}

bool isLargerOrEqual(char x, char y)
{
	switch (x)
	{
		case '+':
		case '-':
			if (y == '+' || y == '-') return true;
			else return false;
		case '*':
		case '/':
			return true;
	}
	return false;
}

void printQueue(char Queue[], int front, int rear)
{
	for (int i = front; i <= rear; i++)
	{
		printf("%c ", Queue[i]);
	}
	printf("\n");
}
void printStack(char Stack[], int nStack)
{
	for (int i = 0; i < nStack; i++)
	{
		printf("%c ", Stack[i]);
	}
	printf("\n");
}

void convert(char *eq, int nEq, 
	char Queue[], int &front, int &rear)
{
	char Stack[MAX];
	int nStack = 0;
	for (int i = 0; i < nEq; i++)
	{
		if (eq[i] >= '0' && eq[i] <= '9') 
		{
			//number : enqueue to Queue
			enQueue(Queue, front, rear, eq[i]);
		}
		else if (eq[i] == '(')
		{
			// 🙂 push to stack
			push(Stack, nStack, eq[i]);
		}
		else if (eq[i] == ')')
		{
			// ): pop all until stack empty or (
			char x;
			while (!isEmpty(Stack, nStack) && top(Stack, nStack) != '(')
			{
				pop(Stack, nStack, x);
				enQueue(Queue, front, rear, x);
			}
			if (top(Stack, nStack) == '(')
				pop(Stack, nStack, x);
		}
		else {
			//+ - * /: check precedence if stack top is operator
			while (!isEmpty(Stack, nStack) && top(Stack, nStack) != '(')
			{
				char x = top(Stack, nStack);
				if (isLargerOrEqual(x, eq[i]))
				{
					pop(Stack, nStack, x);
					enQueue(Queue, front, rear, x);					
				}
				else break;
			}
			push(Stack, nStack, eq[i]);
		}
		
	}	
}
double calculate(double num1, double num2, char dau)
{
	switch (dau)
	{
		case '+':
			return num1 + num2;
		case '-':
			return num1 - num2;
		case '*':
			return num1 * num2;
		case '/':
			return num1 / num2;
	}
	return 0;
}

double evaluate(char Queue[], int front, int rear)
{
	double Stack2[MAX];
	int nStack2 = 0;

	for (int i = front; i <= rear; i++)
	{
		if (Queue[i] >= '0' && Queue[i] <= '9')
		{
			push2(Stack2, nStack2, Queue[i] - '0');
		}
		else {
			double num1, num2;
			pop2(Stack2, nStack2, num2);
			pop2(Stack2, nStack2, num1);
			double result = calculate(num1, num2, Queue[i]);
			push2(Stack2, nStack2, result);

		}
	}

	double finalResult;
	pop2(Stack2, nStack2, finalResult);

	return finalResult;
}

int main()
{
	//expression
	char eq[] = "((3+5)*5/2-7*(8-3-1*2)/3)";
	int nEq = strlen(eq);

	//init stack and queue
	char Queue[MAX];
	int front, rear;
	front = -1;
	rear = -1;

	//convert infix to postfix
	convert(eq, nEq, Queue, front, rear);
	
	//evaluate equation
	double result = evaluate(Queue, front, rear);

	printf("Result is %lf", result);

	system("pause");
	return 0;
}