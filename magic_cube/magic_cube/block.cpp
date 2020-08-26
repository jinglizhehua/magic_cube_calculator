#include <iostream>
#include <stack>
#include <math.h>
#include <thread>
#include "block.h"
using namespace std;

void outputColor(BlockColor color)
{
	switch (color)
	{
	case white:		cout << "白"; break;
	case yellow:	cout << "黄"; break;
	case red:		cout << "红"; break;
	case green:		cout << "绿"; break;
	case orange:	cout << "橙"; break;
	case blue:		cout << "蓝"; break;
	default:	break;
	}
}

//BlockLeng::BlockLeng() {}
BlockLeng::BlockLeng(int id, int state, BlockColor color[2])
{
	this->id = id;
	this->state = state;
	this->color[0] = color[0];
	this->color[1] = color[1];
}
void BlockLeng::output()
{
	for (int i = 0; i < 2; i++) 
	{
		outputColor(color[(state + i) % 2]);
	}
}

//BlockJiao::BlockJiao() {}
BlockJiao::BlockJiao(int id, int state, BlockColor color[3])
{
	this->id = id;
	this->state = state;
	this->color[0] = color[0];
	this->color[1] = color[1];
	this->color[2] = color[2];
}
void BlockJiao::output()
{
	for (int i = 0; i < 3; i++)
	{
		outputColor(color[(state + i) % 3]);
	}
}

Cube::Cube()
{
	this->jiao[0] = BlockJiao(0, 0, new BlockColor[3]{ yellow, red, blue });
	this->jiao[1] = BlockJiao(1, 0, new BlockColor[3]{ yellow, blue, orange });
	this->jiao[2] = BlockJiao(2, 0, new BlockColor[3]{ yellow, orange, green });
	this->jiao[3] = BlockJiao(3, 0, new BlockColor[3]{ yellow, green, red });
	this->jiao[4] = BlockJiao(4, 0, new BlockColor[3]{ white, blue, red });
	this->jiao[5] = BlockJiao(5, 0, new BlockColor[3]{ white, orange, blue });
	this->jiao[6] = BlockJiao(6, 0, new BlockColor[3]{ white, green, orange });
	this->jiao[7] = BlockJiao(7, 0, new BlockColor[3]{ white, red, green });

	this->leng[0] = BlockLeng(0, 0, new BlockColor[2]{ yellow, red });
	this->leng[1] = BlockLeng(1, 0, new BlockColor[2]{ yellow, blue });
	this->leng[2] = BlockLeng(2, 0, new BlockColor[2]{ yellow, orange });
	this->leng[3] = BlockLeng(3, 0, new BlockColor[2]{ yellow, green });
	this->leng[4] = BlockLeng(4, 0, new BlockColor[2]{ white, red });
	this->leng[5] = BlockLeng(5, 0, new BlockColor[2]{ white, blue });
	this->leng[6] = BlockLeng(6, 0, new BlockColor[2]{ white, orange });
	this->leng[7] = BlockLeng(7, 0, new BlockColor[2]{ white, green });
	this->leng[8] = BlockLeng(8, 0, new BlockColor[2]{ red, blue });
	this->leng[9] = BlockLeng(9, 0, new BlockColor[2]{ orange, blue });
	this->leng[10] = BlockLeng(10, 0, new BlockColor[2]{ orange, green });
	this->leng[11] = BlockLeng(11, 0, new BlockColor[2]{ red, green });
}

void Cube::output()
{
	int list[] = {0, 1, 1, 2, 0, 2, -1,
	1, 1, -2, 1, 3, -1,
	0, 0, 1, 0, 0, 3, -1, -1,

	1, 9, -2, 1, 10, -1,
	1, 8, -2, 1, 11, -1, -1,

	0, 5, 1, 6, 0, 6, -1,
	1, 5, -2, 1, 7, -1,
	0, 4, 1, 4, 0, 7, -1};
	
	for (int i = 0; i < (sizeof(list)/sizeof(list[0])); i++)
	{
		cout << "\t";
		switch (list[i])
		{
		case -1:	//输出换行
			cout << endl;
			break;
		case -2:	//输出制表符
			//cout << "\t";
			break;
		case 0:	//输出角块
			i++;
			jiao[list[i]].output();
			break;
		case 1:	//输出棱块
			i++;
			leng[list[i]].output();
			break;
		default:
			break;
		}
	}
}

//a -> b -> c -> d -> a
inline void swapFour(BlockJiao& a, BlockJiao& b, BlockJiao& c, BlockJiao& d)
{
	BlockJiao temp = d;
	d = c;
	c = b;
	b = a;
	a = temp;
}
inline void swapFour(BlockLeng& a, BlockLeng& b, BlockLeng& c, BlockLeng& d)
{
	BlockLeng temp = d;
	d = c;
	c = b;
	b = a;
	a = temp;
}

inline void rotate_shun(int& state)        // state = (state + 1) % 3
{
	state = ((state & 1) << 1) | (((state >> 1) | state) ^ 1);
}
inline void rotate_ni(int& state)          // state = (state + 2) % 3
{
	state = (state >> 1) | (((state << 1) | state) ^ 2);
}

void Cube::R()
{
	//jiao[3].state = (jiao[3].state + 2) % 3;
	rotate_ni(jiao[3].state);
	//jiao[2].state = (jiao[2].state + 1) % 3;
	rotate_shun(jiao[2].state);
	//jiao[6].state = (jiao[6].state + 2) % 3;
	rotate_ni(jiao[6].state);
	//jiao[7].state = (jiao[7].state + 1) % 3;
	rotate_shun(jiao[7].state);

	swapFour(leng[3], leng[10], leng[7], leng[11]);
	swapFour(jiao[3], jiao[2], jiao[6], jiao[7]);
}

void Cube::_R()
{
	//jiao[3].state = (jiao[3].state + 2) % 3;
	rotate_ni(jiao[3].state);
	//jiao[2].state = (jiao[2].state + 1) % 3;
	rotate_shun(jiao[2].state);
	//jiao[6].state = (jiao[6].state + 2) % 3;
	rotate_ni(jiao[6].state);
	//jiao[7].state = (jiao[7].state + 1) % 3;
	rotate_shun(jiao[7].state);

	swapFour(leng[3], leng[11], leng[7], leng[10]);
	swapFour(jiao[3], jiao[7], jiao[6], jiao[2]);
}

void Cube::L()
{
	//jiao[1].state = (jiao[1].state + 2) % 3;
	rotate_ni(jiao[1].state);
	//jiao[0].state = (jiao[0].state + 1) % 3;
	rotate_shun(jiao[0].state);
	//jiao[4].state = (jiao[4].state + 2) % 3;
	rotate_ni(jiao[4].state);
	//jiao[5].state = (jiao[5].state + 1) % 3;
	rotate_shun(jiao[5].state);

	swapFour(leng[1], leng[8], leng[5], leng[9]);
	swapFour(jiao[1], jiao[0], jiao[4], jiao[5]);
}

void Cube::_L()
{
	//jiao[1].state = (jiao[1].state + 2) % 3;
	rotate_ni(jiao[1].state);
	//jiao[0].state = (jiao[0].state + 1) % 3;
	rotate_shun(jiao[0].state);
	//jiao[4].state = (jiao[4].state + 2) % 3;
	rotate_ni(jiao[4].state);
	//jiao[5].state = (jiao[5].state + 1) % 3;
	rotate_shun(jiao[5].state);

	swapFour(leng[1], leng[9], leng[5], leng[8]);
	swapFour(jiao[1], jiao[5], jiao[4], jiao[0]);
}

void Cube::F()
{
	//jiao[0].state = (jiao[0].state + 2) % 3;
	rotate_ni(jiao[0].state);
	//jiao[3].state = (jiao[3].state + 1) % 3;
	rotate_shun(jiao[3].state);
	//jiao[7].state = (jiao[7].state + 2) % 3;
	rotate_ni(jiao[7].state);
	//jiao[4].state = (jiao[4].state + 1) % 3;
	rotate_shun(jiao[4].state);

	leng[0].state = !leng[0].state;
	leng[11].state = !leng[11].state;
	leng[4].state = !leng[4].state;
	leng[8].state = !leng[8].state;

	swapFour(leng[0], leng[11], leng[4], leng[8]);
	swapFour(jiao[0], jiao[3], jiao[7], jiao[4]);
}

void Cube::_F()
{
	//jiao[0].state = (jiao[0].state + 2) % 3;
	rotate_ni(jiao[0].state);
	//jiao[3].state = (jiao[3].state + 1) % 3;
	rotate_shun(jiao[3].state);
	//jiao[7].state = (jiao[7].state + 2) % 3;
	rotate_ni(jiao[7].state);
	//jiao[4].state = (jiao[4].state + 1) % 3;
	rotate_shun(jiao[4].state);

	leng[0].state = !leng[0].state;
	leng[11].state = !leng[11].state;
	leng[4].state = !leng[4].state;
	leng[8].state = !leng[8].state;

	swapFour(leng[0], leng[8], leng[4], leng[11]);
	swapFour(jiao[0], jiao[4], jiao[7], jiao[3]);
}

void Cube::B()
{
	//jiao[5].state = (jiao[5].state + 2) % 3;
	rotate_ni(jiao[5].state);
	//jiao[1].state = (jiao[1].state + 1) % 3;
	rotate_shun(jiao[1].state);
	//jiao[2].state = (jiao[2].state + 2) % 3;
	rotate_ni(jiao[2].state);
	//jiao[6].state = (jiao[6].state + 1) % 3;
	rotate_shun(jiao[6].state);

	leng[2].state = !leng[2].state;
	leng[9].state = !leng[9].state;
	leng[6].state = !leng[6].state;
	leng[10].state = !leng[10].state;

	swapFour(leng[2], leng[9], leng[6], leng[10]);
	swapFour(jiao[1], jiao[5], jiao[6], jiao[2]);
}

void Cube::_B()
{
	//jiao[5].state = (jiao[5].state + 2) % 3;
	rotate_ni(jiao[5].state);
	//jiao[1].state = (jiao[1].state + 1) % 3;
	rotate_shun(jiao[1].state);
	//jiao[2].state = (jiao[2].state + 2) % 3;
	rotate_ni(jiao[2].state);
	//jiao[6].state = (jiao[6].state + 1) % 3;
	rotate_shun(jiao[6].state);

	leng[2].state = !leng[2].state;
	leng[9].state = !leng[9].state;
	leng[6].state = !leng[6].state;
	leng[10].state = !leng[10].state;

	swapFour(leng[2], leng[10], leng[6], leng[9]);
	swapFour(jiao[1], jiao[2], jiao[6], jiao[5]);
}

void Cube::U()
{
	swapFour(leng[0], leng[1], leng[2], leng[3]);
	swapFour(jiao[0], jiao[1], jiao[2], jiao[3]);
}

void Cube::_U()
{
	swapFour(leng[0], leng[3], leng[2], leng[1]);
	swapFour(jiao[0], jiao[3], jiao[2], jiao[1]);
}

void Cube::D()
{
	swapFour(leng[4], leng[7], leng[6], leng[5]);
	swapFour(jiao[4], jiao[7], jiao[6], jiao[5]);
}

void Cube::_D()
{
	swapFour(leng[4], leng[5], leng[6], leng[7]);
	swapFour(jiao[4], jiao[5], jiao[6], jiao[7]);
}

void Cube::runByString(string str)
{
	int length = (int)str.length();
	for(int i = 0; i < length; i ++)
	{
		if ((i == length - 1) || (str[(long long)i + 1] != '\''))
		{
			switch (str[i])
			{
			case 'R': R(); break;
			case 'L': L(); break;
			case 'U': U(); break;
			case 'D': D(); break;
			case 'F': F(); break;
			case 'B': B(); break;
			default:
				cout << "input error!" << endl;
				break;
			}
		}
		else if (str[(long long)i + 1] == '\'')
		{
			switch (str[(long long)i])
			{
			case 'R': _R(); break;
			case 'L': _L(); break;
			case 'U': _U(); break;
			case 'D': _D(); break;
			case 'F': _F(); break;
			case 'B': _B(); break;
			default:
				cout << "input error!" << endl;
				break;
			}
			i++;
		}
	}
}

bool BlockLeng::equal(BlockLeng& blockleng)
{
	if (this->id != blockleng.id)
		return false;
	else if (this->state != blockleng.state)
		return false;
	else
		return true;
}

bool BlockJiao::equal(BlockJiao& blockjiao)
{
	if (this->id != blockjiao.id)
		return false;
	else if (this->state != blockjiao.state)
		return false;
	else
		return true;
}

bool Cube::equal(Cube& cube)
{
	for (int i = 0; i < 12; i++)
	{
		if (!(this->leng[i].equal(cube.leng[i])))
			return false;
	}
	for (int i = 0; i < 8; i++)
	{
		if (!(this->jiao[i].equal(cube.jiao[i])))
			return false;
	}
	return true;
}

string steps = "RrUuFf";//小写代表逆操作

Cube runStep(Cube& cube, int step)
{
	Cube newCube = cube;
	switch (steps[step])
	{
	case 'R': newCube.R(); break;
	case 'r': newCube._R(); break;
	case 'U': newCube.U(); break;
	case 'u': newCube._U(); break;
	case 'F': newCube.F(); break;
	case 'f': newCube._F(); break;
	case 'L': newCube.L(); break;
	case 'l': newCube._L(); break;
	case 'B': newCube.B(); break;
	case 'b': newCube._B(); break;
	case 'D': newCube.D(); break;
	case 'd': newCube._D(); break;
	default:
		break;
	}
	return newCube;
}

string stackToString(stack<node> a)
{
	stack<node> temp;
	while (!a.empty())
	{
		temp.push(a.top());
		a.pop();
	}
	string str = "";
	while (!temp.empty())
	{
		switch (steps[temp.top().step])
		{
		case 'R': str.append("R"); break;
		case 'r': str.append("R'"); break;
		case 'L': str.append("L"); break;
		case 'l': str.append("L'"); break;
		case 'U': str.append("U"); break;
		case 'u': str.append("U'"); break;
		case 'D': str.append("D"); break;
		case 'd': str.append("D'"); break;
		case 'F': str.append("F"); break;
		case 'f': str.append("F'"); break;
		case 'B': str.append("B"); break;
		case 'b': str.append("B'"); break;
		default:
			break;
		}
		temp.pop();
	}
	return str;
}

long long cnt;
long long allcnt;
bool thread_run_flag = false;
const char back_str[] = "\b\b\b\b\b\b\b\b\b\b";
void thread_progress()//显示进度
{
	long long allcnt_cut = allcnt / 100;
	long long now_allcnt = allcnt_cut;
	cout << "hello" << endl;
	while (thread_run_flag)
	{
		cout.setf(ios::fixed);
		cout.setf(ios::showpoint);
		cout.precision(6);
		cout << back_str << (100.0 * cnt / allcnt) << "%";
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
}

void Cube::calc(int maxStep)
{
	stack<node> s;
	int stepLen = (int)steps.length()-1;
	Cube now;
	node temp;
	int count = 0;
	cnt = 0;	//总cnt = (stepLen+1)^(maxStep+1)/stepLen
	allcnt = (long long)pow(stepLen + 1, maxStep + 1) / stepLen;  //(stepLen + 1) ^ (maxStep + 1) / stepLen;
	cout << "总可能数为: " << allcnt << endl;

	thread_run_flag = true;
	thread t1(thread_progress);
	t1.detach();

	while (true)
	{
		cnt++;
		if (count < maxStep)
		{
			s.push({ 0, now });	//存储上次执行情况
			now = runStep(now, 0);
			if (this->equal(now))
				cout << stackToString(s) << endl;
			++count;
		}
		else
		{
			while(true)
			{
				temp = s.top();
				if (temp.step == stepLen)
				{
					s.pop();
					--count;
					if (count == 0)
					{
						cout << back_str << "finished." << endl;
						thread_run_flag = false;
						return;
					}
				}
				else
					break;
			}
			s.pop();
			s.push({ temp.step + 1, temp.state });
			now = runStep(temp.state, temp.step + 1);
			if (this->equal(now))
				cout << back_str << stackToString(s) << endl;
		}
	}
}