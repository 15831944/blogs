#include "MazeWalker.h"
#include "literals.h"
#include <windows.h>
#include <iostream>

using namespace std;

/******************************
	构造函数
	初始化角色已走的步数
******************************/
MazeWalker::MazeWalker()
{
    m_iSteps = 0;
}

/********************************************
	根据传入的方向使游戏角色移动一步
	角色移动的过程:
	首先让游戏角色在当前位置消失
	然后让游戏角色在下一个位置出现
********************************************/
void MazeWalker::moveForward(char direction)
{
    unsigned long numWritten;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);							// 获取命令行窗口的窗口句柄
    FillConsoleOutputCharacter(handle, ' ', 1, m_currentPos, &numWritten);		// 在游戏角色当前位置填充空格，使游戏角色消失
    switch (direction)															// 根据传入的方向来设置下一个位置的坐标
    {
	case _UPWARD:
		m_currentPos.Y--;
		break;
	case _DOWN:
		m_currentPos.Y++;
		break;
	case _LEFT:
		m_currentPos.X--;
		break;
	case _RIGHT:
		m_currentPos.X++;
		break;
	default:
		break;
    }
    FillConsoleOutputCharacter(handle, m_cWalker, 1, m_currentPos, &numWritten);	// 在游戏角色新坐标位置上填出代表游戏角色的字符
    m_cDirection = direction;			// 移动完成后更新游戏角色的朝向
}

/**********************************************
	向上走一步
	首先判断游戏角色上方的位置是墙还是路
	若是路，则调用moveForward进行移动
	若是墙，则直接返回false，表示移动失败
**********************************************/
bool MazeWalker::walkUp()
{
    if (m_pMazeMap->getMapArray()[m_currentPos.Y - 1][m_currentPos.X])
	{
        return false;
    }
    else
	{
        moveForward(_UPWARD);	// 成功移动才会更新放方向
        return true;
    }
}

/*******************
	向下走一步
*******************/
bool MazeWalker::walkDown()
{
    if (m_pMazeMap->getMapArray()[m_currentPos.Y + 1][m_currentPos.X])
	{
        return false;
    }
    else
	{
        moveForward(_DOWN);
        return true;
    }
}

/*******************
	向左走一步
*******************/
bool MazeWalker::walkLeft()
{
    if (m_pMazeMap->getMapArray()[m_currentPos.Y][m_currentPos.X - 1])
	{
        return false;
    }
    else
	{
        moveForward(_LEFT);
        return true;
    }
}

/*******************
	向右走一步
*******************/
bool MazeWalker::walkRight()
{
    if (m_pMazeMap->getMapArray()[m_currentPos.Y][m_currentPos.X + 1])
	{
        return false;
    }
    else
	{
        moveForward(_RIGHT);
        return true;
    }
}

/*************************
	设置游戏角色的位置
*************************/
void MazeWalker::setWalkerPosition(COORD pos)
{
    unsigned long numWritten;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    m_currentPos.X = pos.X;
    m_currentPos.Y = pos.Y;
    FillConsoleOutputCharacter(handle, m_cWalker, 1, m_currentPos, &numWritten);
	Sleep(2000);
	cout << "\nwalking!" << endl;
}

void MazeWalker::setWalkerSpeed(int speed)
{
	m_iSpeed = speed;
}
/*****************************
	设置代表游戏角色的字符
*****************************/
void MazeWalker::setWalkerChar(char hero)
{
    m_cWalker = hero;
}

/*****************************
	设置游戏角色的初始朝向
*****************************/
void MazeWalker::setWalkerDirection(char direction)
{
    m_cDirection = direction;
}

/*******************
	设置地图对象
*******************/
void MazeWalker::setMazeMap(MazeMap *map)
{
    m_pMazeMap = map;
}

/****************
	获取步数
****************/
int MazeWalker::getSteps()
{
	cout << "totally " << m_iSteps << " steps" << endl;
    return m_iSteps;
}

//游戏开始函数
void MazeWalker::start()
{
    while (true)
    {
        switch (m_cDirection)		// 右手原则, 起始朝向, 途中朝向
        {
		case _UPWARD:
			walkRight() || walkUp() || walkLeft() || walkDown();	//移动成功则更新方向
			break;
        case _DOWN:
            walkLeft() || walkDown() || walkRight() || walkUp();
            break;
		case _LEFT:
            walkUp() || walkLeft() || walkDown() || walkRight();
            break;
        case _RIGHT:
            walkDown() || walkRight() || walkUp() || walkLeft();
            break;
        default:
			cout << "direction error!" << endl;
            break;
        }
        m_iSteps++;

        //判断游戏角色的当前位置是否是迷宫出口位置，如果到达出口，游戏结束
        if (   m_currentPos.X == m_pMazeMap->getExitPosition().X
			&& m_currentPos.Y == m_pMazeMap->getExitPosition().Y )
        {
			cout << "arrived!" << endl;
            break;
        }
        //每步时间间隔ms
        Sleep(m_iSpeed);
    }
}
