#pragma once
#include <iostream>
#include <string>

template <class T>
class Mystack
{
private:
	int max_length;
	T* stack;
	int p_bottom;
	int p_top;

public:
	Mystack()
	{
		this->max_length = 0;
		stack = NULL;
	}
	Mystack(int max_length)
	{
		this->max_length = max_length;
		stack = new T[max_length];
		this->p_bottom = this->p_top = 0;
	}
	Mystack(const Mystack& mystack)
	{
		this->max_length = mystack.max_length;
		//if (this->stack != NULL)
			//delete[] this->stack;
		this->stack = new T[max_length];
		memcpy(this->stack, mystack.stack, ((long)mystack.p_top + 1) * sizeof(T));
		this->p_bottom = 0;
		this->p_top = mystack.p_top;
	}
	~Mystack()
	{
		if (stack != NULL)
		{
			//delete[] stack;
		}
	}
	T& pop()
	{
		//if (p_top <= 0)
		//	return *(new T);
		return stack[p_top--];
	}
	void push(T t)
	{
		//if (p_top >= (max_length-1))
		//	return;
		stack[++p_top] = t;
	}
	bool empty()
	{
		return (p_top == 0);
	}
};

