#pragma once
#include <iostream> // C++的IO输入输出
#include <vector> // 存储open表的数据结构
#include <map> // 存储closed表的数据结构

using namespace std;

//对于可能被多个.h,.cpp执行的声明不用特殊处理
typedef int board[4][4];//将二维数组的定义重定义为Arc
struct Snode {
	int state;//一维数字表示状态序列
	int g;    //路径深度
	int h;    //启发函数的评估值
	int cur;  //状态的序号标号
	int pre;  //状态的父节点标号

	Snode(int state, int g, int h, int cur, int pre) :state(state), g(g), h(h), cur(cur), pre(pre) {}

	bool operator <(const Snode& e)const {
		return(state < e.state);
	}
	bool operator ==(const Snode& e)const {
		return (state == e.state);  //即state值相同
	}
};

//对于可能被多个.h .cpp执行的变量需要特殊处理，不然连接器报错
static int move_x[] = { -1,0,1,0 };  //左移动是-1,右移动是+1
static int move_y[] = { 0,1,0,-1 };  //上移动是1,下移动是-1
static multimap<int, Snode> open_key;//open表
static map<Snode, int> open_value;   //open表的value-key反表，便于查找元素
static map <int, bool> closed;       //closed表
static vector <Snode> path;          //保存closed表的具体结构路径
