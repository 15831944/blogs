#include "MazeMap.h"
#include <iostream>

using namespace std;

/****************
    构造函数
****************/
MazeMap::MazeMap(char wall, char road) : m_cWall(wall), m_cRoad(road)
{
    m_pMapArr = NULL;
}

/****************
    析构函数
****************/
MazeMap::~MazeMap()
{
	// 释放动态分配的二维数组
    if (m_pMapArr)
	{
        for (int i = 0; i < m_iMapRow; i++)
        {
            delete m_pMapArr[i];	// 先释放整型数组
            m_pMapArr[i] = NULL;
        }
        delete m_pMapArr;			// 再释放指针数组
    }
}

/***********************
	设置代表墙的字符
***********************/
void MazeMap::setWallChar(char wall)
{
    m_cWall = wall;
}

/***********************
	获取代表墙的字符
***********************/
char MazeMap::getWallChar()
{
    return m_cWall;
}

/***********************
    设置代表路的字符
***********************/
void MazeMap::setRoadChar(char road)
{
    m_cRoad = road;
}

/***********************
    获取代表路的字符
***********************/
char MazeMap::getRoadChar()
{
    return m_cRoad;
}

/*******************************
    动态分配并初始化二维数组
*******************************/
void MazeMap::setMapArray(int *map, int row, int col)
{
    m_iMapRow = row;
    m_iMapCol = col;

	// 动态分配二维数组
    m_pMapArr = new int *[m_iMapRow];		// 动态分配指针数组, 用于指向数组的每一行

    for (int i = 0; i < m_iMapRow; i++)
    {
        m_pMapArr[i] = new int[m_iMapCol];	// 动态分配整型数组, 用于表示数组的每一行
    }

    // 初始化二维数组
    int *p = map;
    for (int i = 0; i < m_iMapRow; i++)
    {
        for (int j = 0; j < m_iMapCol; j++)
        {
            m_pMapArr[i][j] = *p;
            p++;					// 遍历传入的二维数组
        }
    }
}

/***************************
	获取指向二维数组指针
***************************/
int **MazeMap::getMapArray()
{
    return m_pMapArr;
}

/*******************
	设置出口位置
*******************/
void MazeMap::setExitPosition(COORD coo)
{
    m_ExitPosition = coo;
}

/*******************
	获取出口位置
*******************/
COORD MazeMap::getExitPosition()
{
    return m_ExitPosition;
}

/*****************
    绘制地图
*****************/
void MazeMap::drawMap()
{
    for (int i = 0; i < m_iMapRow; i++)
    {
        for (int j = 0; j < m_iMapCol; j++)
        {
            if (m_pMapArr[i][j])	// 数组元素若为1，则打印代表墙的字符
            {
                cout << m_cWall;
            }
			else					// 数组元素若为0，则打印代表路的字符
            {
                cout << m_cRoad;
            }
        }
        cout << endl;
    }
}