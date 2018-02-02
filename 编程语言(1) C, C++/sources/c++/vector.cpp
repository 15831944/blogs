#include <vector>
#include <iostream>
using namespace std;

int vector_stack_operation(void)
{
	vector<char> mystack(0);
	char temp;

	cout << "input commands: " << endl;
	do
	{
		// cout << temp << endl;
		cin >> temp;
		if (temp != '#')
		{
			if (temp != '$')
				mystack.push_back(temp);
			else
				mystack.pop_back();
		}
	}while (temp != '#');

	for (int i = 0; i < mystack.size(); i++)
	{
		cout << mystack[i];
	}
	cout << endl;
	return 0;
}

/******************************
	未保存则文本丢失
	重启则无法撤消已保存内容
******************************/
int save_undo_reboot(void)
{
	vector<char> stack(0);
	char temp;

	cout << "input: " <<endl;
	do
	{
		cin >> temp;
		if (temp != '#')					// # 表示输入结束并保存
		{
			if (temp != '*')
			{
				if (temp != '$')
				{
					stack.push_back(temp);	// 未结束、未重启、未撤消则为正常输入
				}
				else						// 
				{
					if (stack.back()!='%')	// % 表示保存
					{
						stack.pop_back();	// $ 表示撤消
					}
				}
			}
			else							// * 表示重启
			{
				while(!stack.empty() && stack.back() != '%')
				{
					stack.pop_back();		// 重启则删除到上次保存位置
				}
			}
		}
	}while (temp != '#');

	if (!stack.empty())
	{
		for (int i = 0; i < stack.size(); i++)
		{
			if (stack[i]!='%')				// 不输出保存符号
			{
				cout << stack[i];
			}
		}
		cout << endl;
	}
	else
	{
		cout << "Nothing left" <<endl;
	}
	return 0;
}
