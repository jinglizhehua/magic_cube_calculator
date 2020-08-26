#pragma once
#include <iostream>
#include <string>
#include <stack>

enum BlockColor
{
	white = 0,
	yellow = 1,
	red = 2,
	green = 3,
	orange = 4,
	blue = 5
};

/*
		2
	1		3
		0

	9		10

	8		11

		6
	5		7
		4
*/
class BlockLeng
{
public:
	int id;	//棱块编号
	int state;	//状态0,1
	BlockColor color[2];	//上或下或前或后在前

	BlockLeng() {};
	BlockLeng(int id, int state, BlockColor color[2]);
	void output();
	bool equal(BlockLeng& blockleng);
};

/*
	1	2
	0	3

	5	6
	4	7
*/
class BlockJiao
{
public:
	int id;	//角块编号
	int state;		//状态0, 1, 2 //规定状态表示角块逆时针旋转次数
	BlockColor color[3];	//从上或下开始，按顺时针方向

	BlockJiao() {};
	BlockJiao(int id, int state, BlockColor color[3]);
	void output();
	bool equal(BlockJiao& blockjiao);
};

class Cube
{
public:
	BlockJiao jiao[8];
	BlockLeng leng[12];

	Cube();
	void output();
	void R();
	void _R();
	void L();
	void _L();
	void U();
	void _U();
	void D();
	void _D();
	void F();
	void _F();
	void B();
	void _B();

	void runByString(std::string str);
	bool equal(Cube& cube);
	void calc(int maxStep);//已知状态计算公式
};

struct node
{
	int step;	//当前执行步骤
	Cube state;
};
