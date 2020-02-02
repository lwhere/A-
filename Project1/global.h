#pragma once
#include <iostream> // C++��IO�������
#include <vector> // �洢open������ݽṹ
#include <map> // �洢closed������ݽṹ

using namespace std;

//���ڿ��ܱ����.h,.cppִ�е������������⴦��
typedef int board[4][4];//����ά����Ķ����ض���ΪArc
struct Snode {
	int state;//һά���ֱ�ʾ״̬����
	int g;    //·�����
	int h;    //��������������ֵ
	int cur;  //״̬����ű��
	int pre;  //״̬�ĸ��ڵ���

	Snode(int state, int g, int h, int cur, int pre) :state(state), g(g), h(h), cur(cur), pre(pre) {}

	bool operator <(const Snode& e)const {
		return(state < e.state);
	}
	bool operator ==(const Snode& e)const {
		return (state == e.state);  //��stateֵ��ͬ
	}
};

//���ڿ��ܱ����.h .cppִ�еı�����Ҫ���⴦����Ȼ����������
static int move_x[] = { -1,0,1,0 };  //���ƶ���-1,���ƶ���+1
static int move_y[] = { 0,1,0,-1 };  //���ƶ���1,���ƶ���-1
static multimap<int, Snode> open_key;//open��
static map<Snode, int> open_value;   //open���value-key�������ڲ���Ԫ��
static map <int, bool> closed;       //closed��
static vector <Snode> path;          //����closed��ľ���ṹ·��
