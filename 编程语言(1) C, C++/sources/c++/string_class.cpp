#include <string>
#include <iostream>
using namespace std;

int string_class(void)
{
	string str1("This is ");			// ×Ö·û´®¶ÔÏó
	string str2("just ");
	string str3("That is ");
	string str4("hello world ");
	string str5("application");

	cout << "pos of 'i': " << str1.find("i") << endl;
	cout << "len of str1: " << str1.length() << endl;
	cout << "str1 = " << str1 << endl;
	
	str1.append("my first ");
	cout << "len of str1: " << str1.length() << endl;
	cout << "str1 = " << str1 << endl;

	str1.insert(8, str2);
	cout << str1 << endl;

	cout << str1.compare("ABC") << endl;
	cout << str1.compare(str1) << endl;
	cout << str1.empty() << endl;

	str1.swap(str3);
	cout << "str1 = " << str1 << endl;
	cout << "str3 = " << str3 << endl;
	
	cout << "pos of 'world': " << str4.find("world") << endl;
	cout << "len of str4: "  << str4.length() << endl;
	cout << "str4 = " << str4 << endl;


	cout << "pos of 'app': " << str5.find("app") << endl;
	cout << "len of str5: "  << str5.length() << endl;
	cout << "str5 = " << str5 << endl;

	return (0);
}