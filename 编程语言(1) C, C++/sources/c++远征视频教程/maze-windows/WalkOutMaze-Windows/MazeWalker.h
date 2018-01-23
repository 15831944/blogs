#ifndef MazeWalker_H
#define MazeWalker_H

#include <windows.h>
#include "MazeMap.h"

class MazeWalker
{
public:
    MazeWalker();							// 构造函数
	void	moveForward(char direction);	// 根据传入的方向使游戏角色移动一步
    bool	walkUp();						// 向上走动一步，若成功，则返回true，若失败（上面是墙），则返回false
    bool	walkDown();						// 向下走动一步，若成功，则返回true，若失败（下面是墙），则返回false
    bool	walkLeft();						// 向左走动一步，若成功，则返回true，若失败（左面是墙），则返回false
    bool	walkRight();					// 向右走动一步，若成功，则返回true，若失败（右面是墙），则返回false
    
    void	setWalkerPosition(COORD pos);		// 设置游戏角色的位置
    void	setWalkerSpeed(int speed);			// 设置游戏角色的速度
    void	setWalkerChar(char walker);			// 设置代表游戏角色的字符
    void	setWalkerDirection(char direction);	// 设置游戏角色的朝向
    void	setMazeMap(MazeMap *map);			// 设置地图对象
    int		getSteps();							// 获取步数
	void	start();							// 游戏开始函数
private:
    char	m_cWalker;					// 代表游戏角色的字符
    char	m_cDirection;				// 游戏角色的朝向
    COORD	m_lastPos;					// 游戏角色的上个位置
    COORD	m_currentPos;				// 游戏角色的当前位置
    MazeMap	*m_pMazeMap;				// 地图对象
    int		m_iSteps;					// 记录游戏角色走了多少步
    int		m_iSpeed;					// 速度
};

#endif