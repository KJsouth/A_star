#include "node.h"

//node::node(pair<int, int> point, pair<int, int> target, node* parent)
//{
//	x = point.first; y = point.second;
//	father = parent;
//	if (parent == NULL) {//û�и��ڵ�ʱ
//		gval = -1;
//		fval = -1;
//		hval = -1;
//	}
//	else {//����gval\hval\fval
//		//������ʹ�õ�hval���㷽��Ϊ|deltaX|+|deltaY|�������е��ƶ���ʽ�����˶Խ��ߵ��ƶ�
//		if (abs(father->x - x) + abs(father->y - y) == 1) { gval = 10; }
//		else { gval = 14; }
//		hval = abs(target.first - x) * 10 + abs(target.second - y) * 10;
//		fval = gval + hval;
//	}
//}

node::node(pair<int, int> point, pair<int, int> target, node* parent)
{
	x = point.first; y = point.second;
	father = parent;

	if (parent == NULL) {//û�и��ڵ�ʱ
		gval = 0;
	}
	else {//����gval\hval\fval
		if (abs(father->x - x) + abs(father->y - y) == 1) { gval = 10; }
		else { gval = 14; }
		//gval += father->gval;
	}
	//������ʹ�õ�hval���㷽��Ϊ|deltaX|+|deltaY|�������е��ƶ���ʽ�����˶Խ��ߵ��ƶ�
	hval = abs(target.first - x) * 10 + abs(target.second - y) * 10;
	fval = gval + hval;
}


void node::show()
{
	// printf("Location: (%d,%d); Gval: %d ; Hval: %d ; Fval: %d .\n", x, y, gval, hval, fval);
}

node::~node()
{
}

