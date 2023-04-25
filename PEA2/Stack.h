#pragma once
#include <iostream>
using namespace std;
class Stack
{
	struct number
	{
		int value;
		number* next;
	};

	number* top = NULL;
	number* bottom = NULL;

public:

	int n;
	Stack();
	void push(int newValue);
	int pop();


};



