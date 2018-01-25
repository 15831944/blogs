// exc_mean.h -- execption classes for hmean(), gmean()
#include <iostream>

// 定义异常类
class bad_hmean
{
private:
	double v1;
	double v2;
public:
	bad_hmean(double a = 0, double b = 0) : v1(a), v2(b) {}
	void mesg();
};

inline void bad_hmean::mesg()
{
	std::cout << "hmean(" << v1 << ", " << v2 << "): " << "invalid arguments: a = -b" << std::endl;
}

// 定义另一个异常类
class bad_gmean
{
private:
	double v1;
	double v2;
public:
	bad_gmean(double a = 0, double b = 0) : v1(a), v2(b) {}
	const char * mesg();
};

inline const char * bad_gmean::mesg()
{
	return "gmean() arguments should be >= 0\n";
}
