#include "node.hpp"

node::node(pair<int, int> point, pair<int, int> target, node* parent)
{
	x = point.first; y = point.second;
	father = parent;

	if (parent == NULL) {// start节点
		gval = 0;
	}else {// 相邻节点
		if (abs(father->x - x) + abs(father->y - y) == 1) {
			 gval = 10 + father->gval; 
		}else{
			 gval = 14 + father->gval; 
		}
	}
	hval = abs(target.first - x) * 10 + abs(target.second - y) * 10;
	// hval = 0;
	fval = gval + hval;
}


void node::show()
{
	printf("Location: (%d,%d); Gval: %d ; Hval: %d ; Fval: %d .\n", x, y, gval, hval, fval);
}

node::~node()
{
}

