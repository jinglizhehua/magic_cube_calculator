#pragma once
#include <vector>
#include <iomanip>
#include <iostream>
#include <string>
#include "my_stack.h"
#include <thread>
#include <conio.h>
#include <Windows.h>
using namespace std;
//颜色
enum Color { Red, Blue, Green, Yellow, White, Orange };
//操作，用于Cube和MagicCube，对应序数奇偶性代表是否reversed
enum Operation { R, R_, L, L_, U, U_, D, D_, F, F_, B, B_ };
//自定义公式类型
typedef vector<Operation> Formula;
//专门用于交换四个元素的change函数，效果是非反转下b变为a值，c变为b值，以此类推。
void inline change(Color& a, Color& b, Color& c, Color& d)
{
	/*Color tmp = d;
	d = c;
	c = b;
	b = a;
	a = tmp;*/
	d = Color(d ^ c);
	c = Color(d ^ c);
	d = Color(d ^ c);
	
	c = Color(b ^ c);
	b = Color(b ^ c);
	c = Color(b ^ c);
	
	a = Color(b ^ a);
	b = Color(b ^ a);
	a = Color(b ^ a);
}
void inline change_reverse(Color& a, Color& b, Color& c, Color& d)
{
	/*Color tmp = a;
	a = b;
	b = c;
	c = d;
	d = tmp;*/
	a = Color(b ^ a);
	b = Color(b ^ a);
	a = Color(b ^ a);

	c = Color(b ^ c);
	b = Color(b ^ c);
	c = Color(b ^ c);

	d = Color(d ^ c);
	c = Color(d ^ c);
	d = Color(d ^ c);
}

bool valid(const Formula& f);

class MagicCube
{
	friend ostream& operator<<(ostream& os, const MagicCube& mc);
private:
	Color ff[9], fu[9], fb[9], fd[9], fl[9], fr[9];
public:
	MagicCube();
	MagicCube(const MagicCube& mc);
	void operate(Operation op);
	void operate(const Formula& f);
	bool check();

	void runByString(std::string str);
	bool equal(MagicCube& magicCube);
	void calc(int maxStep, int maxResultNum);//已知状态计算公式
};

struct node
{
	int step;	//当前执行步骤
	MagicCube state;
};
