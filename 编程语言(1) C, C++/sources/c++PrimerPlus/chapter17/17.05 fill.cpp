// fill.cpp -- changing fill character for fields
#include <iostream>

int main()
{
	using std::cout;
	cout.fill('*');		// 一直有效
	const char *staff[2] = {"Waldo Whipsnade", "Wilmarie Wooper"};
	long bonus[2] = {900, 1350};

	for (int i = 0; i < 2; i++)
	{
		cout << staff[i] << ": $";
		cout.width(7);
		cout << bonus[i] << "\n";
	}

	system("pause");
	return 0;
}
