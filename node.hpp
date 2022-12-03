#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;
class node
{
public:
	node* father;// 父节点
	int x, y;	 // 位置坐标 x,y,
	int gval, hval, fval; // cur 到起点的实际代价，cur 到终点的预估代价，总代价

	node(pair<int, int> point, pair<int, int> target, node* father = NULL);

	void show();
	~node();
};

