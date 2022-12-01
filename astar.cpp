#include"node.h"
#include<queue>
using namespace std;
const int mapsize = 24;//地图的尺寸
const int barrier = 1;//阻碍物为1
const pair<int, int> start = { 0,0 };//起点
const pair<int, int> target = { 23,23 };//终点
using namespace std;
//设置地图的阻碍物
void setMap(vector<vector<int>>& map, vector<int> rows, vector<int> cols) {
	for (int i = rows[0]; i <= rows[1]; i++) {
		vector<int>& temp = map[i];
		if (cols.size() == 1)temp[cols[0]] = barrier;
		else {
			for (int j = cols[0]; j <= cols[1]; j++) { temp[j] = barrier; }
		}
	}
}
//打印地图：其中阻碍物为1，打印的时候显示为'S'，
//0为可以走的块，打印为'.'，X为最终的行走路线
void showMap(vector<vector<int>>& map) {
	for (auto i : map) {
		for (auto j : i) {
			if (j == 0) { cout << ". "; }
			else if (j == 1) { cout << "S "; }
			else { cout << "X "; }
		}
		cout << endl;
	}
}
//初始化地图，在这里可以设置阻碍物
void initMap(vector<vector<int>>& map) {
	for (int i = 0; i < mapsize; i++) {
		vector<int> t(mapsize, 0);
		map.push_back(t);
	}
	setMap(map, { 2,2 }, { 0,5 });
	setMap(map, { 0,5 }, { 8,8 });
	setMap(map, { 5,5 }, { 3,10 });
	setMap(map, { 7,7 }, { 1,20 });
	setMap(map, { 15,15 }, { 12,23 });
	setMap(map, { 10,20 }, { 11 });
}
//找到openlist中的fval最小的节点
node* findMinF(vector<node*> openlist) {
	int minF = INT_MAX;
	int minIndex = 0;
	for (int i = 0; i < openlist.size(); i++) {
		if (openlist[i]->fval == -1) { continue; }
		if (openlist[i]->fval < minF) { minIndex = i; minF = openlist[i]->fval; }
	}
	return openlist[minIndex];
}
//判断cur节点是否存在与list中
node* nodeIn(node* cur, vector<node*> list) {
	if (list.size() == 0)return NULL;
	for (auto i : list) {
		if (i->x == cur->x && i->y == cur->y) {
			return i;
		}
	}
	return NULL;
}
//处理cur节点及其周围的8个节点
void listAppend(node* cur, vector<node*>& openlist, vector<node*>& closelist, vector<vector<int>> tarmap) {
	vector<pair<int, int>> points;
	vector<pair<int, int>> temp = { { 0,1 },{ 1,0 },{ -1,0 },{ 0,-1 },{ 1,1 },{ -1,-1 },{ 1,-1 },{ -1,1 } };
	for (auto i : temp) {
		points.push_back({ cur->x + i.first,cur->y + i.second });
	}
	for (auto i : points) {//遍历这八个周围的节点
		int tx = i.first, ty = i.second;
		if (tx < mapsize && tx >= 0 && ty < mapsize && ty >= 0) {
			node* t = new node(i, target, cur);
			node* t1 = nodeIn(t, openlist);//当前节点是否在openlist中
			node* t2 = nodeIn(t, closelist);//当前节点是否在closelist中
			if (tarmap[tx][ty] == 1 || t2) { continue; }//如果当前节点是阻碍物，就直接看下一个节点
			if (t1 && t1->gval > t->gval) {//如果当前节点的gval比openlist中的该节点小，
			//这说明之前的路径走到的此节点不如当前的路径走到此节点的代价小，
			//那么就更新当前的节点（非常重要的一个步骤）
				for (int i = 0; i < openlist.size(); i++) {
					node*& temp = openlist[i];
					if (temp->x == t1->x && temp->y == t1->y) {
						temp = t1; break;
					}
				}
			}
			if (!t1)//如果当前节点不在openlist中，就直接加入到openlist中
				openlist.push_back(t);
		}
	}
}


//处理cur节点及其周围的8个节点
void listAppend_new(node* cur, vector<node*>& openlist, vector<node*>& closelist, vector<vector<int>> tarmap) {
	vector<pair<int, int>> points;
	vector<pair<int, int>> temp = { { 0,1 },{ 1,0 },{ -1,0 },{ 0,-1 },{ 1,1 },{ -1,-1 },{ 1,-1 },{ -1,1 } };
	for (auto i : temp) {
		points.push_back({ cur->x + i.first,cur->y + i.second });
	}
	for (auto i : points) {//遍历这八个周围的节点
		int tx = i.first, ty = i.second;
		if (tx < mapsize && tx >= 0 && ty < mapsize && ty >= 0) {
			node* t = new node(i, target, cur);
			node* t1 = nodeIn(t, openlist);//当前节点是否在openlist中
			node* t2 = nodeIn(t, closelist);//当前节点是否在closelist中
			if (tarmap[tx][ty] == 1) { continue; }//如果当前节点是阻碍物，就直接看下一个节点

			if(t2 && t2->gval > t->gval){//如果当前节点的gval比closelist中的该节点小，
			//这说明之前的路径走到的此节点不如当前的路径走到此节点的代价小，
			//那么就更新当前的节点（非常重要的一个步骤）
				for (int i = 0; i < closelist.size(); i++) {
					node*& temp = closelist[i];
					if (temp->x == t2->x && temp->y == t2->y) {
						temp = t; break;
					}
				}
			}

			if (!t1)//如果当前节点不在openlist中，就直接加入到openlist中
				openlist.push_back(t);
		}
	}
}
void getres(node* res, vector<vector<int>>& tarmap) {//打印路径
//从最终的节点来找到起点，通过res=res->father的方式
	vector<pair<int, int>> reslist;
	auto cur = res;
	while (!(cur->x == start.first && cur->y == start.second)) {
		reslist.push_back({ cur->x,cur->y });
		cur = cur->father;
	}
	reslist.push_back({ cur->x,cur->y });
	for (auto i : reslist) {
		tarmap[i.first][i.second] = 2;
	}
	cout << "------------------------------------------" << endl;
	showMap(tarmap);
	return;
}
void showList(vector<node*> list) {//打印openlist或者closelist用于调试
	for (auto i : list) { printf("(%d,%d):F:%d\n", i->x, i->y, i->fval); }
}
//主函数
int main()
{
	vector<vector<int>> tarmap;
	initMap(tarmap);//初始化地图
	showMap(tarmap);//打印一开始的地图

	vector<node*> openlist;
	vector<node*> closelist;
	openlist.push_back(new node(start, target));//将起点放入openlist
	clock_t startTime, endTime;//计算一下找终点的过程所花的时间
	startTime = clock();
	while (!openlist.empty())
	{
		node* temp = findMinF(openlist);
		temp->show();//把当前节点的信息打印出来看看

		if (temp->x == target.first && temp->y == target.second)
		{
			closelist.push_back(temp);
			break;
		}
		//在openlist中删除当前节点
		int tsize = openlist.size();
		for (int i = 0; i < tsize; i++) {
			node* t = openlist[i];
			if (t->x == temp->x && t->y == temp->y) {
				openlist.erase(openlist.begin() + i); break;
			}
		}
	    //如果当前节点不在closelist中就加入进去
	    if (!nodeIn(temp, closelist))
		   closelist.push_back(temp);

		listAppend(temp, openlist, closelist, tarmap);//处理当前节点周围的八个节点
	}
	



	//vector<node*> openlist;
	//vector<node*> closelist;
	//openlist.push_back(new node(start, target));//将起点放入openlist
	//clock_t startTime, endTime;//计算一下找终点的过程所花的时间
	//startTime = clock();
	//while (openlist.size() != 0 && nodeIn(new node(target, target), closelist) == NULL) {
	//	//当openlist不为空并且还没有在closelist中找到终点节点的时候一直循环
	//	node* temp = findMinF(openlist);//找到当前openlist中的fval最小的值
	//	temp->show();//把当前节点的信息打印出来看看
	//	//在openlist中删除当前节点
	//	int tsize = openlist.size();
	//	for (int i = 0; i < tsize; i++) {
	//		node* t = openlist[i];
	//		if (t->x == temp->x && t->y == temp->y) {
	//			openlist.erase(openlist.begin() + i); break;
	//		}
	//	}
	//	//如果当前节点不在closelist中就加入进去
	//	if (!nodeIn(temp, closelist))
	//		closelist.push_back(temp);
	//	listAppend(temp, openlist, closelist, tarmap);//处理当前节点周围的八个节点
	//}
	endTime = clock();
	cout << "------------------------------------------" << endl;
	cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	auto res = nodeIn(new node(target, target), closelist);
	//没找到的情况：
	if (!res) { cout << "No correct path!" << endl; }
	else { getres(res, tarmap); }
	return 0;
}
//  int main(){
// 	test();
//  }







