#include"windows.h"
#include"global.h"
#include"function.h"



//��һά����ת��Ϊ��ά����


int main() {
	double time = 0;
	double counts = 0;
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ

	board st, ed;
	freopen("1.txt", "r+", stdin);
	inPut(st);
	inPut(ed);

	int step = run(arc_toState(st), arc_toState(ed));
	if (step != -1)
	{
		cout << "�н⣬���·����" << step << endl;
		isOk(step);
	}
	else {
		cout << "���ɴ�" << endl;
	}

	QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
	cout << "����ִ��ʱ�䣺" << time * 1000 << "ms" << endl;

	return 0;
}