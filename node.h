#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;
class node
{
public:
	node* father;//���ڵ�����
	int x, y, gval, hval, fval;//�ڵ�λ��x��y
	
	//raw define
    //gval�����˴Ӹýڵ㵽���ڵ���ƶ�����
	//hval�����˴Ӹýڵ㵽�յ�ľ��루�þ���ļ��㷽���ж��ֿ���ϸ���ң�
	//fval=gval+hval����ȻfvalԽС�����ƶ�������õ�����յ�ĺ�ԽС��Ҳ��������Խϣ�����ֵ����

	//gval�����˴Ӹýڵ㵽��ʼ�ڵ���ƶ�����
	//hval�����˴Ӹýڵ㵽�յ�ľ��루�þ���ļ��㷽���ж��ֿ���ϸ���ң�
	//fval=gval+hval����ȻfvalԽС�����ƶ�������õ�����յ�ĺ�ԽС��Ҳ��������Խϣ�����ֵ����
	node(pair<int, int> point, pair<int, int> target, node* father = NULL);

	void show();
	~node();
};

