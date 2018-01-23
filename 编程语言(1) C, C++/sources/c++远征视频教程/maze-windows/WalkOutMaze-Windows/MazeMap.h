#ifndef MazeMap_H
#define MazeMap_H

#include <windows.h>

class MazeMap
{
public:
    MazeMap(char wall, char road);						// 构造函数
    ~MazeMap();

    void	setWallChar(char wall);						// 设置代表墙的字符
	char	getWallChar();								// 获取代表墙的字符
    void	setRoadChar(char road);						// 设置代表路的字符
	char	getRoadChar();								// 获取代表路的字符
	void	setMapArray(int *map, int row, int col);	// 设置指向二维数组的指针
    int		**getMapArray();							// 获取指向二维数组的指针
    void	setExitPosition(COORD coo);					// 设置出口位置
    COORD	getExitPosition();							// 获取出口位置
	void	drawMap();									// 绘制迷宫地图
private:
    char	m_cWall;			// 墙壁字符
    char	m_cRoad;			// 通路字符
    int		**m_pMapArr;		// 指向二维数组的指针
    int		m_iMapRow;			// 二维数组的行数
    int		m_iMapCol;			// 二维数组的列数
	COORD	m_ExitPosition;		// 迷宫出口的坐标
};

#endif
