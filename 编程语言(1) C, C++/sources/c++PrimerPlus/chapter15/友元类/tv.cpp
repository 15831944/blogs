// tv.cpp -- methods for the Tv class (Remote class are inline)
#include <iostream>
#include "tv.h"

// 音量调大
bool Tv::volup()
{
	if (volume < MaxVal)
	{
		volume++;
		return true;
	}
	else
		return false;
}

// 音量调小
bool Tv::voldown()
{
	if (volume > MinVal)
	{
		volume++;
		return true;
	}
	else
		return false;
}

// 频道循环向上切换
void Tv:: chanup()
{
	if (channel < maxchannel)
		channel++;
	else
		channel = 1;
}

// 频道循环向下切换
void Tv:: chandown()
{
	if (channel > 1)
		channel--;
	else
		channel = maxchannel;
}

// 显示电视机设置
void Tv::settings() const
{
	using std::cout;
	using std::endl;
	cout << "TV is " << (state == Off ? "Off" : "On") << endl;
	if (state == On)
	{
		cout << "Volume setting = " << volume << endl;
		cout << "Channel setting = " << channel << endl;
		cout << "Mode = " << (mode == Antenna ? "antenna" : "cable") << endl;
		cout << "Input = " << (input == TV ? "TV" : "DVD") << endl;
	}
}
