#include "MagicCube.h"

bool valid(const Formula& f)
{
	if (f.size() <= 1) return true;
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

MagicCube::MagicCube()
{
	for (int i = 0; i < 9; i++)
	{
		ff[i] = Red;
		fb[i] = Orange;
		fl[i] = Blue;
		fr[i] = Green;
		fu[i] = Yellow;
		fd[i] = White;
	}
}

MagicCube::MagicCube(const MagicCube& mc)
{
	memcpy(this->ff, mc.ff, sizeof(this->ff));
	memcpy(this->fb, mc.fb, sizeof(this->fb));
	memcpy(this->fl, mc.fl, sizeof(this->fl));
	memcpy(this->fr, mc.fr, sizeof(this->fr));
	memcpy(this->fu, mc.fu, sizeof(this->fu));
	memcpy(this->fd, mc.fd, sizeof(this->fd));
}

void MagicCube::operate(Operation op)
{
	switch (op)
	{
	case R:
		change(fu[8], fb[0], fd[8], ff[8]);
		change(fu[5], fb[3], fd[5], ff[5]);
		change(fu[2], fb[6], fd[2], ff[2]);
		change(fr[0], fr[2], fr[8], fr[6]);
		change(fr[1], fr[5], fr[7], fr[3]);
		break;
	case R_:
		change_reverse(fu[8], fb[0], fd[8], ff[8]);
		change_reverse(fu[5], fb[3], fd[5], ff[5]);
		change_reverse(fu[2], fb[6], fd[2], ff[2]);
		change_reverse(fr[0], fr[2], fr[8], fr[6]);
		change_reverse(fr[1], fr[5], fr[7], fr[3]);
		break;
	case L:
		change(fu[0], ff[0], fd[0], fb[8]);
		change(fu[3], ff[3], fd[3], fb[5]);
		change(fu[6], ff[6], fd[6], fb[2]);
		change(fl[1], fl[5], fl[7], fl[3]);
		change(fl[0], fl[2], fl[8], fl[6]);
		break;
	case L_:
		change_reverse(fu[0], ff[0], fd[0], fb[8]);
		change_reverse(fu[3], ff[3], fd[3], fb[5]);
		change_reverse(fu[6], ff[6], fd[6], fb[2]);
		change_reverse(fl[1], fl[5], fl[7], fl[3]);
		change_reverse(fl[0], fl[2], fl[8], fl[6]);
		break;
	case U:
		change(ff[0], fl[0], fb[0], fr[0]);
		change(ff[1], fl[1], fb[1], fr[1]);
		change(ff[2], fl[2], fb[2], fr[2]);
		change(fu[1], fu[5], fu[7], fu[3]);
		change(fu[0], fu[2], fu[8], fu[6]);
		break;
	case U_:
		change_reverse(ff[0], fl[0], fb[0], fr[0]);
		change_reverse(ff[1], fl[1], fb[1], fr[1]);
		change_reverse(ff[2], fl[2], fb[2], fr[2]);
		change_reverse(fu[1], fu[5], fu[7], fu[3]);
		change_reverse(fu[0], fu[2], fu[8], fu[6]);
		break;
	case D:
		change(ff[6], fr[6], fb[6], fl[6]);
		change(ff[7], fr[7], fb[7], fl[7]);
		change(ff[8], fr[8], fb[8], fl[8]);
		change(fd[1], fd[5], fd[7], fd[3]);
		change(fd[0], fd[2], fd[8], fd[6]);
		break;
	case D_:
		change_reverse(ff[6], fr[6], fb[6], fl[6]);
		change_reverse(ff[7], fr[7], fb[7], fl[7]);
		change_reverse(ff[8], fr[8], fb[8], fl[8]);
		change_reverse(fd[1], fd[5], fd[7], fd[3]);
		change_reverse(fd[0], fd[2], fd[8], fd[6]);
		break;
	case F:
		change(fu[6], fr[0], fd[2], fl[8]);
		change(fu[7], fr[3], fd[1], fl[5]);
		change(fu[8], fr[6], fd[0], fl[2]);
		change(ff[1], ff[5], ff[7], ff[3]);
		change(ff[0], ff[2], ff[8], ff[6]);
		break;
	case F_:
		change_reverse(fu[6], fr[0], fd[2], fl[8]);
		change_reverse(fu[7], fr[3], fd[1], fl[5]);
		change_reverse(fu[8], fr[6], fd[0], fl[2]);
		change_reverse(ff[1], ff[5], ff[7], ff[3]);
		change_reverse(ff[0], ff[2], ff[8], ff[6]);
		break;
	case B:
		change(fu[0], fl[6], fd[8], fr[2]);
		change(fu[1], fl[3], fd[7], fr[5]);
		change(fu[2], fl[0], fd[6], fr[8]);
		change(fb[1], fb[5], fb[7], fb[3]);
		change(fb[0], fb[2], fb[8], fb[6]);
		break;
	case B_:
		change_reverse(fu[0], fl[6], fd[8], fr[2]);
		change_reverse(fu[1], fl[3], fd[7], fr[5]);
		change_reverse(fu[2], fl[0], fd[6], fr[8]);
		change_reverse(fb[1], fb[5], fb[7], fb[3]);
		change_reverse(fb[0], fb[2], fb[8], fb[6]);
		break;
	}
}

void MagicCube::operate(const Formula& f)
{
	for (Operation op : f)
		operate(op);
}

bool MagicCube::check()
{
	for (int i = 1; i < 9; i++)
		if (ff[i] != ff[0] || fb[i] != fb[0] ||
			fu[i] != fu[0] || fd[i] != fd[0] ||
			fl[i] != fl[0] || fr[i] != fr[0])
			return false;
	return true;
}

ostream& operator<<(ostream& o, Color c)
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

ostream& operator<<(ostream& os, const MagicCube& mc)
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
		os << endl;
	}
	return os;
}

void MagicCube::runByString(string str)
{
	int length = (int)str.length();
	for (int i = 0; i < length; i++)
	{
		if ((i == length - 1) || (str[(long long)i + 1] != '\''))
		{
			switch (str[i])
			{
			case 'R': operate(R); break;
			case 'L': operate(L); break;
			case 'U': operate(U); break;
			case 'D': operate(D); break;
			case 'F': operate(F); break;
			case 'B': operate(B); break;
			default:
				cout << "input error!" << endl;
				break;
			}
		}
		else if (str[(long long)i + 1] == '\'')
		{
			switch (str[(long long)i])
			{
			case 'R': operate(R_); break;
			case 'L': operate(L_); break;
			case 'U': operate(U_); break;
			case 'D': operate(D_); break;
			case 'F': operate(F_); break;
			case 'B': operate(B_); break;
			default:
				cout << "input error!" << endl;
				break;
			}
			i++;
		}
	}
}

bool MagicCube::equal(MagicCube& magicCube)
{
	//for (int i = 1; i < 9; i++)
	//	if (ff[i] != magicCube.ff[i] || fb[i] != magicCube.fb[i] ||
	//		fu[i] != magicCube.fu[i] || fd[i] != magicCube.fd[i] ||
	//		fl[i] != magicCube.fl[i] || fr[i] != magicCube.fr[i])
	//		return false;
	if (memcmp(ff, magicCube.ff, sizeof(ff)) != 0 ||
		memcmp(fb, magicCube.fb, sizeof(fb)) != 0 ||
		memcmp(fu, magicCube.fu, sizeof(fu)) != 0 ||
		memcmp(fd, magicCube.fd, sizeof(fd)) != 0 ||
		memcmp(fl, magicCube.fl, sizeof(fl)) != 0 ||
		memcmp(fr, magicCube.fr, sizeof(fr)) != 0)
		return false;
	return true;
}

Operation steps[] = {R, R_, U, U_, F, F_};

MagicCube runStep(const MagicCube& cube, int step)
{
	MagicCube newCube = cube;
	newCube.operate(steps[step]);
	return newCube;
}

string stackToString(Mystack<node> a)
{
	Mystack<node> temp(30);
	while (!a.empty())
	{
		temp.push(a.pop());
	}
	string str = "";
	while (!temp.empty())
	{
		switch (steps[temp.pop().step])
		{
		case R: str.append("R"); break;
		case R_: str.append("R'"); break;
		case L: str.append("L"); break;
		case L_: str.append("L'"); break;
		case U: str.append("U"); break;
		case U_: str.append("U'"); break;
		case D: str.append("D"); break;
		case D_: str.append("D'"); break;
		case F: str.append("F"); break;
		case F_: str.append("F'"); break;
		case B: str.append("B"); break;
		case B_: str.append("B'"); break;
		default:
			break;
		}
	}
	return str;
}


bool thread_run_flag = false;
long long cnt;
long long allcnt;
const char back_str[] = "\b\b\b\b\b\b\b\b\b\b";
void thread_progress()//显示进度
{
	long long allcnt_cut = allcnt / 100;
	long long now_allcnt = allcnt_cut;
	//cout << "进度显示线程已启动：" << this_thread::get_id() << endl;
	printf("进度显示线程已启动：%d\n", this_thread::get_id());
	while (thread_run_flag)
	{
		//cout.setf(ios::fixed);
		//cout.setf(ios::showpoint);
		//cout.precision(6);
		//cout << back_str << (100.0 * cnt / allcnt) << "%";
		printf("%s%f%%", back_str, 100.0 * cnt / allcnt);
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
	printf("\n[thread][end]进度显示线程 %d 已退出.\n	", this_thread::get_id());
}

bool main_loop_run;
void thread_check_termination()
{
	printf("\n[thread][start]监测按键线程已启动：%d\n按q键终止计算...\n", this_thread::get_id());
	while (_getch() != 'q');
	printf("\n计算已终止.\n");
	main_loop_run = false;
}


void MagicCube::calc(int maxStep, int maxResultNum)
{
	Mystack<node> s(30);
	Mystack<Mystack<node>> result(maxResultNum);
	int stepLen = sizeof(steps)/sizeof(Operation) - 1;
	MagicCube now;
	node temp;
	cnt = 0;	//总cnt = (stepLen+1)^(maxStep+1)/stepLen
	allcnt = (long long)pow(stepLen + 1, maxStep + 1) / stepLen;  //(stepLen + 1) ^ (maxStep + 1) / stepLen;
	cout << "总可能数为: " << allcnt << endl;

	thread_run_flag = true;
	main_loop_run = true;
	thread t1(thread_check_termination);
	t1.detach();
	Sleep(100);
	thread t2(thread_progress);
	t2.detach();

	int count = 0;

	while (main_loop_run)
	{
		cnt++;
		if (count < maxStep)
		{
			s.push({ 0, now });	//存储上次执行情况
			//now = runStep(now, 0);
			now.operate(steps[0]);
			if (this->equal(now))
				result.push(s);
			++count;
		}
		else
		{
			while (true)
			{
				temp = s.pop();
				if (temp.step == stepLen)
				{
					--count;
					if (count == 0)
					{
						cout << endl << "finished." << endl;
						goto finished;
					}
				}
				else
					break;
			}
			s.push({ temp.step + 1, temp.state });
			//now = runStep(temp.state, temp.step + 1);
			now = temp.state;
			now.operate(steps[temp.step + 1]);
			if (this->equal(now))
				//cout << back_str << stackToString(s) << endl;
				result.push(s);
		}
	}

finished:
	thread_run_flag = false;
	Sleep(1000);
	cout << endl;
	while (!result.empty())
	{
		cout << stackToString(result.pop()) << endl;
	}
}

