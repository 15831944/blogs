// hangman.cpp -- some string methods
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>

using std::string;

const int NUM = 26;
// 全局对象数组, 使用C风格字符串初始化
const string wordlist[NUM] = {
	"apiary", "beetle", "cereal", "danger", "ensign", "florid", "garage", "health", "insult", "jackal", "keeper", "loaner", "manage",
	"nonce", "onset", "plaid", "quilt", "remote", "stolid", "train", "useful", "valid", "whence", "xenon", "yearn", "zippy"
};

int main()
{
	using namespace std;
	std::srand(std::time(0));		// 随机数种子
	char play;
	cout << "Will you play a word game? <y/n>";
	cin >> play;
	play = tolower(play);
	while (play == 'y')
	{
		string target = wordlist[std::rand() % NUM];	// 目标单词
		int length = target.length();
		string attempt(length, '-');					// 猜对字符
		string badchars;								// 猜错字符

		int guesses = 6;								// 每局重置剩余次数
		cout << "Guess my secret word. It has " << length << " letters, and you guess" << endl
			<< "one letter at a time. You get " << guesses << " wrong guesses" << endl;
		cout << "Your word: " << attempt << endl;

		// 本局次数未到且还未猜对
		while (guesses > 0 && attempt != target)	// string 对象重载比较运算符
		{
			// 输入一个字符
			char letter;
			cout << "Guess a letter: ";
			cin >> letter;

			// 检查输入的字符是否位于已经猜过的猜对或猜错字符串中
			if (  badchars.find(letter, 0) != string::npos
				|| attempt.find(letter, 0) != string::npos)	// 从0位置开始找, 找到则返回字符首次出现的位置, 否则返回 npos, 第2个参数可以省略
			{
				cout << "You already guessed that. Try again." << endl;
				continue;
			}

			// 猜错情况和猜对情况
			int loc = target.find(letter, 0);
			if (loc == string::npos)	// npos 是 string 对象的静态成员, 表示能存储的最大字符数
			{
				cout << "Oh, bad guess!" << endl;
				--guesses;
				badchars +=letter;	// append a char to a string object
			}
			else
			{
				cout << "Good guess!" << endl;
				attempt[loc] = letter;			// 将猜对的字母放在字符串的相应位置
				// check if letter appears again
				loc = target.find(letter, loc + 1);	// 从找到的字符的下一个位置开始搜索
				while (loc != string::npos)
				{
					attempt[loc] = letter;
					loc = target.find(letter, loc + 1);
				}
			}
			cout << "Your word: " << attempt << endl;
			// 还没猜对情况的提示信息
			if (attempt != target)
			{
				if (badchars.length() > 0)
				{
					cout << "Bad choices: " << badchars << endl;
				}
				cout << guesses << " bad guesses left" << endl;
			}
		}
		if (guesses > 0)
		{
			cout << "That's right!" << endl;
		}
		else
		{
			cout << "Sorry, the word is " << target << "." << endl;
		}
		// 重新设置循环条件
		cout << "Will you play another?<y/n>";
		cin >> play;
		play = tolower(play);
	}
	cout << "Bye" << endl;

	system("pause");
	return 0;
}
