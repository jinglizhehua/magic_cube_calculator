/*
��c++ʵ�ֵ�ħ���࣬ʵ�������ħ�����ж��Ƿ�ԭ�����и���ת�������ȡ�
Ϊ����Ч�ʣ������п����ɫ������һһ���룬����������ֱ�ۣ�������������ٶȵõ��ܴ�������
һ���Ӵ���ܹ��������ڴ�ת��������
*/

#ifndef MAGIC_CUBE_H
#define MAGIC_CUBE_H
#include <vector>
#include <iomanip>
#include <iostream>

using namespace std;
//��ɫ
enum Color { Red, Blue, Green, Yellow, White, Orange };
//����������Cube��MagicCube����Ӧ������ż�Դ����Ƿ�reversed
enum Operation { R, R_, R2, L, L_, L2, U, U_, U2, D, D_, D2, F, F_, F2, B, B_, B2 };
//�Զ��幫ʽ����
typedef vector<Operation> Formula;
//ר�����ڽ����ĸ�Ԫ�ص�change������Ч���ǷǷ�ת��b��Ϊaֵ��c��Ϊbֵ���Դ����ơ�
template <class T>
void inline change(T&a, T&b, T&c, T&d, bool reversed = false)
{
	T tmp;
	if (reversed)
	{
		tmp = a;
		a = b;
		b = c;
		c = d;
		d = tmp;
	}
	else
	{
		tmp = d;
		d = c;
		c = b;
		b = a;
		a = tmp;
	}
}

bool valid(const Formula &f)
{
	if (f.size()<=1) return true;
	auto p = f.rbegin();
	Operation a = *p;
	++p;
	Operation b = *p;
	if (a / 3 * 3 == b / 3 * 3)
		return false;
	if (f.size() >= 3)
	{
		++p;
		Operation c = *p;
		if (c / 3 / 2 == b / 3 / 2 && c / 3 != b / 2 && a / 3 * 3 == c / 3 * 3)
			return false;
	}
	return true;
}

class MagicCube
{
	friend ostream&operator<<(ostream&os, const MagicCube&mc);
private:
	Color ff[9], fu[9], fb[9], fd[9], fl[9], fr[9];
public:
	MagicCube()
	{
		for (int i = 0; i < 9; i++)
		{
			ff[i] = Orange;
			fb[i] = Red;
			fl[i] = Green;
			fr[i] = Blue;
			fu[i] = Yellow;
			fd[i] = White;
		}
	}
	void operate(Operation op)
	{
	  Color *a = NULL, *b = NULL, *c = NULL, *d = NULL,
			*e = NULL, *f = NULL, *g = NULL, *h = NULL,
			*i = NULL, *j = NULL, *k = NULL, *l = NULL,
			*m = NULL, *n = NULL, *o = NULL, *p = NULL,
			*q = NULL, *r = NULL, *s = NULL, *t = NULL;
		switch (op)
		{
		case R:case R_:
			a = &fu[8], b = &fb[0], c = &fd[8], d = &ff[8];
			e = &fu[5], f = &fb[3], g = &fd[5], h = &ff[5];
			i = &fu[2], j = &fb[6], k = &fd[2], l = &ff[2];
			m = &fr[1], n = &fr[5], o = &fr[7], p = &fr[3];
			q = &fr[0], r = &fr[2], s = &fr[8], t = &fr[6];
			break;
		case L:case L_:
			a = &fu[0], b = &ff[0], c = &fd[0], d = &fb[8];
			e = &fu[3], f = &ff[3], g = &fd[3], h = &fb[5];
			i = &fu[6], j = &ff[6], k = &fd[6], l = &fb[2];
			m = &fl[1], n = &fl[5], o = &fl[7], p = &fl[3];
			q = &fl[0], r = &fl[2], s = &fl[8], t = &fl[6];
			break;
		case U:case U_:
			a = &ff[0], b = &fl[0], c = &fb[0], d = &fr[0];
			e = &ff[1], f = &fl[1], g = &fb[1], h = &fr[1];
			i = &ff[2], j = &fl[2], k = &fb[2], l = &fr[2];
			m = &fu[1], n = &fu[5], o = &fu[7], p = &fu[3];
			q = &fu[0], r = &fu[2], s = &fu[8], t = &fu[6];
			break;
		case D:case D_:
			a = &ff[6], b = &fr[6], c = &fb[6], d = &fl[6];
			e = &ff[7], f = &fr[7], g = &fb[7], h = &fl[7];
			i = &ff[8], j = &fr[8], k = &fb[8], l = &fl[8];
			m = &fd[1], n = &fd[5], o = &fd[7], p = &fd[3];
			q = &fd[0], r = &fd[2], s = &fd[8], t = &fd[6];
			break;
		case F:case F_:
			a = &fu[6], b = &fr[0], c = &fd[2], d = &fl[8];
			e = &fu[7], f = &fr[3], g = &fd[1], h = &fl[5];
			i = &fu[8], j = &fr[6], k = &fd[0], l = &fl[2];
			m = &ff[1], n = &ff[5], o = &ff[7], p = &ff[3];
			q = &ff[0], r = &ff[2], s = &ff[8], t = &ff[6];
			break;
		case B:case B_:
			a = &fu[0], b = &fl[6], c = &fd[8], d = &fr[2];
			e = &fu[1], f = &fl[3], g = &fd[7], h = &fr[5];
			i = &fu[2], j = &fl[0], k = &fd[6], l = &fr[8];
			m = &fb[1], n = &fb[5], o = &fb[7], p = &fb[3];
			q = &fb[0], r = &fb[2], s = &fb[8], t = &fb[6];
			break;
		case U2:
			operate(U);
		    operate(U);
			return;
		case D2:
			operate(D);
			operate(D);
			return;
		case L2:
			operate(L);
			operate(L);
			return;
		case R2:
			operate(R);
			operate(R);
			return;
		case B2:
			operate(B);
			operate(B);
			return;
		case F2:
			operate(F);
			operate(F);
			return;
		}
		change(*a, *b, *c, *d, op % 3);
		change(*e, *f, *g, *h, op % 3);
		change(*i, *j, *k, *l, op % 3);
		change(*m, *n, *o, *p, op % 3);
		change(*q, *r, *s, *t, op % 3);
	}
	void operate(const Formula&f)
	{
		for (Operation op : f)
			operate(op);
	}
	bool check()
	{
		for (int i = 1; i < 9; i++)
			if (ff[i] != ff[0] || fb[i] != fb[0] ||
				fu[i] != fu[0] || fd[i] != fd[0] ||
				fl[i] != fl[0] || fr[i] != fr[0])
				return false;
		return true;
	}
};

ostream &operator<<(ostream &o, Color c)
{
	switch (c)
	{
	case Red:
		o << "R";
		break;
	case Orange:
		o << "O";
		break;
	case Blue:
		o << "B";
		break;
	case Green:
		o << "G";
		break;
	case White:
		o << "W";
		break;
	case Yellow:
		o << "Y";
		break;
	}
	return o;
}

ostream& operator<<(ostream&os, const MagicCube& mc)
{
	for (int i = 0; i < 3; i++)
	{
		os << setw(6) << ' ';
		for (int j = 0; j < 3; j++)
			os << mc.fu[3 * i + j] << ' ';
		os << endl;
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			os << mc.fl[3 * i + j] << ' ';
		for (int j = 0; j < 3; j++)
			os << mc.ff[3 * i + j] << ' ';
		for (int j = 0; j < 3; j++)
			os << mc.fr[3 * i + j] << ' ';
		for (int j = 0; j < 3; j++)
			os << mc.fb[3 * i + j] << ' ';
		os << endl;
	}
	for (int i = 0; i < 3; i++)
	{
		os << setw(6) << ' ';
		for (int j = 0; j < 3; j++)
			os << mc.fd[3 * i + j] << ' ';
		os<< endl;
	}
	return os;
}

#endif // MAGIC_CUBE_H
