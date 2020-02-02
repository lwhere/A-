#pragma once

#include"global.h"
bool success(const int& e, const int& s);         //检查是否到达目标路径
bool checkvalid(const int& cur, const int& tar); //检查是否有解
int H1(int curState, int tarState);              //启发函数1
int H2(int curState, int tarState);              //启发函数2
int H3(int curState);                            //启发函数3
int H4(int curState, int tarState);              //启发函数4
int F(const Snode& e);                           //返回状态的F值
int arc_toState(const board& se);                //二维数组转换为一维数字
void state_toArc(int e, board se);               //一维数字转换为二维数组
void inPut(board s);                             //输入初始序列和目标序列
void outPut(const int& e);                       //输出状态的state值的矩阵形式
void findPath(int pre, int size, int step);      //找到最优解的路径
int run(const int& st, const int& ed);            //运行A*函数算法主体
void isOk(int step);                             //当算法运行完毕，检查
