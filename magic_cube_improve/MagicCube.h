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
//��ɫ
enum Color { Red, Blue, Green, Yellow, White, Orange };
//����������Cube��MagicCube����Ӧ������ż�Դ����Ƿ�reversed
enum Operation { R, R_, L, L_, U, U_, D, D_, F, F_, B, B_ };
//�Զ��幫ʽ����
typedef vector<Operation> Formula;
//ר�����ڽ����ĸ�Ԫ�ص�change������Ч���ǷǷ�ת��b��Ϊaֵ��c��Ϊbֵ���Դ����ơ�
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
	void calc(int maxStep, int maxResultNum);//��֪״̬���㹫ʽ
};

struct node
{
	int step;	//��ǰִ�в���
	MagicCube state;
};
