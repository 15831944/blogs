// use_tv.cpp -- using the Tv and Remote classes
#include <iostream>
#include "tv.h"

int main()
{
	using std::cout;

	Tv s42;						// 默认构造函数参数使用默认值
	cout << "Initial settings for 42\" TV:\n";
	s42.settings();

	s42.onoff();
	s42.chanup();
	cout << "\nAdjusted settings for 42\" TV:\n";
	s42.settings();

	Remote grey;
	grey.set_chan(s42, 10);
	grey.volup(s42);
	grey.volup(s42);
	cout << "\n42\" settings after using remote:\n";
	s42.settings();				// 友元类修改了原始类

	Tv s58(Tv::On);
	s58.set_mode();
	grey.set_chan(s58, 28);		// 一个遥控器可用于多台电视机
	cout << "\n58\" settings:\n";
	s58.settings();

	system("pause");
	return 0;
}
