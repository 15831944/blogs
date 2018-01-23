//tv.h -- Tv and Remote classes
#ifndef TV_H_
#define TV_H_

// 定义原始类(被友元类)
class Tv
{
public:
	// 声明友元类(让整个类成为友元)
	friend class Remote;		// Remote can access Tv private parts

	// 无名称的枚举常量, 作用域在类内
	enum {Off, On};				// 开/关状态;
	enum {MinVal, MaxVal = 20};	// 音量大小限制
	enum {Antenna, Cable};		// 有线电视或无线调节模式
	enum {TV, DVD};				// TV调谐或A/V输入

	// 自定义默认构造函数, 参数全部带有默认值, 使用成员初始化列表初始化数据成员
	Tv(int s = Off, int mc = 125) : state(s), volume(5), maxchannel(mc), channel(2), mode(Cable), input(TV) {}
	void	onoff() {state = (state == On) ? Off : On;}		// 切换开关状态
	bool	ison() const {return state == On;}
	bool	volup();
	bool	voldown();
	void	chanup();
	void	chandown();
	void	set_mode() {mode = (mode == Antenna) ? Cable : Antenna;}
	void	set_input() {input = (input == TV) ? DVD : TV;}
	void	settings() const;		// display all settings
private:
	// 数据成员
	int		state;				// on or Off
	int		volume;				// assumed to be digitized
	int		maxchannel;			// maximum number of channels
	int		channel;			// current channel setting
	int		mode;				// broadcast or cable
	int		input;				// TV or DVD
};

// 定义友元类
class Remote
{
private:
	int		mode;				// controls TV or DVD
public:
	Remote(int m = Tv::TV) : mode(m) {}		// 自定义默认构造函数, 默认参数值初始化为TV调谐模式
	// 友元类的成员函数的参数可以是原始类的引用, 表明遥控器必须针对特定的电视机, 且全都使用内联函数实现
	bool	volup(Tv & t) {return t.volup();}
	bool	voldown(Tv & t) {return t.voldown();}
	void 	onoff(Tv & t) {return t.onoff();}
	void	chanup(Tv & t) {return t.chanup();}
	void	chandown(Tv & t) {return t.chandown();}
	void	set_chan(Tv & t, int c) {t.channel = c;}		// 访问了Tv的私有数据成员, 只有这里用到了友元
	void	set_mode(Tv & t) {t.set_mode();}
	void	set_input(Tv & t) {t.set_input();}
};

#endif
