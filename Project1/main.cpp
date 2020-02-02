#include"windows.h"
#include"global.h"
#include"function.h"



//将一维数字转换为二维数组


int main() {
	double time = 0;
	double counts = 0;
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时

	board st, ed;
	freopen("1.txt", "r+", stdin);
	inPut(st);
	inPut(ed);

	int step = run(arc_toState(st), arc_toState(ed));
	if (step != -1)
	{
		cout << "有解，最短路径是" << step << endl;
		isOk(step);
	}
	else {
		cout << "不可达" << endl;
	}

	QueryPerformanceCounter(&nEndTime);//停止计时
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s
	cout << "程序执行时间：" << time * 1000 << "ms" << endl;

	return 0;
}