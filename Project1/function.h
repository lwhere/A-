#pragma once

#include"global.h"
bool success(const int& e, const int& s);         //����Ƿ񵽴�Ŀ��·��
bool checkvalid(const int& cur, const int& tar); //����Ƿ��н�
int H1(int curState, int tarState);              //��������1
int H2(int curState, int tarState);              //��������2
int H3(int curState);                            //��������3
int H4(int curState, int tarState);              //��������4
int F(const Snode& e);                           //����״̬��Fֵ
int arc_toState(const board& se);                //��ά����ת��Ϊһά����
void state_toArc(int e, board se);               //һά����ת��Ϊ��ά����
void inPut(board s);                             //�����ʼ���к�Ŀ������
void outPut(const int& e);                       //���״̬��stateֵ�ľ�����ʽ
void findPath(int pre, int size, int step);      //�ҵ����Ž��·��
int run(const int& st, const int& ed);            //����A*�����㷨����
void isOk(int step);                             //���㷨������ϣ����
