#include "MazeMap.h"
#include "MazeWalker.h"
#include "literals.h"
#include <windows.h>
#include <iostream>

using namespace std;

int main(void)
{
	// 定义并初始化存储地图数据的二维数组
	int map[_ROW][_COL] = {
		{WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
		{WALL, ROAD, ROAD, ROAD, WALL, ROAD, ROAD, ROAD, ROAD, ROAD, ROAD, ROAD},
		{WALL, ROAD, WALL, WALL, WALL, ROAD, WALL, WALL, WALL, ROAD, ROAD, WALL},
		{WALL, ROAD, ROAD, ROAD, WALL, ROAD, ROAD, ROAD, WALL, ROAD, ROAD, WALL},
		{WALL, ROAD, WALL, ROAD, WALL, ROAD, WALL, ROAD, WALL, WALL, ROAD, WALL},
		{WALL, ROAD, WALL, ROAD, ROAD, ROAD, WALL, ROAD, ROAD, ROAD, ROAD, WALL},
		{WALL, ROAD, WALL, WALL, WALL, WALL, WALL, WALL, WALL, ROAD, ROAD, WALL},
		{WALL, ROAD, WALL, ROAD, ROAD, ROAD, ROAD, ROAD, WALL, WALL, ROAD, WALL},
		{WALL, WALL, WALL, ROAD, WALL, WALL, WALL, ROAD, WALL, ROAD, ROAD, WALL},
		{ROAD, ROAD, ROAD, ROAD, WALL, ROAD, ROAD, ROAD, ROAD, ROAD, ROAD, WALL},
		{WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL}
	};

	COORD entry, exit;
	entry.X = _COL - 1;
	entry.Y = 1;
	exit.X  = 0;
	exit.Y  = _ROW - 2;

	MazeMap *myMaze = new MazeMap('E', ' ');	// 创建地图对象
	myMaze->setMapArray(&map[0][0], _ROW, _COL);// 初始化地图
	myMaze->setExitPosition(exit);				// 设置地图出口
	myMaze->drawMap();							// 绘制地图

	MazeWalker *myHero = new MazeWalker();		// 创建角色对象
	myHero->setWalkerChar('i');					// 设置代表游戏角色的字符
	myHero->setWalkerPosition(entry);			// 将游戏角色带到迷宫入口
	myHero->setWalkerDirection(_DOWN);			// 设置游戏角色的朝向
	myHero->setWalkerSpeed(FAST);				// 设置角色速度
	myHero->setMazeMap(myMaze);					// 设置游戏角色要走的地图
	myHero->start();							// 开始游戏
	myHero->getSteps();							// 获取步数

	delete myMaze;		// 销毁对象
	myMaze = NULL;

	delete myHero;
	myHero = NULL;

	system("pause");
}
