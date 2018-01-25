// strfile.cpp -- read strings from a file
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main()
{
	using namespace std;

	ifstream fin;
	fin.open("D:\\tobuy.txt");
	if (fin.is_open() == false)
	{
		cerr << "Can't open file. Bye." << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}

	string item;
	int count = 0;
	getline(fin, item, ':');	// 从文件读取字符串到 stirng 对象, 以 ":" 为分界符
	while (fin)
	{
		++count;
		cout << count << ": " << item << endl;
		getline(fin, item, ':');
	}

	cout << "Done" << endl;
	fin.close();

	system("pause");
	return 0;
}
