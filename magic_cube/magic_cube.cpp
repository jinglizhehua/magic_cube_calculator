#include <iostream>
#include <string>
#include "block.h"
using namespace std;

const char gs1[] = "RRURUR'U'R'U'R'UR'";//逆三棱换
const char gs2[] = "RU'RURURU'R'U'RR";

//当前程序，计算"RrUuFf"20步所需时间为 52742.616 小时
int main()
{
    Cube cube;
    cube.runByString("RUFBLDR'U'F'B'L'D'");
    cube.calc(12);
    return 0;
} 