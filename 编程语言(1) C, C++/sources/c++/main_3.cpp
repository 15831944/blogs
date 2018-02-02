//
//  main.cpp
//  cpp_primer_plus
//
//  Created by wanghuiyong on 8/29/16.
//  Copyright © 2016 wanghuiyong. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[])
{
    using namespace std;
    
    // 通用字符名
    cout << "g\u00E2teau" << endl << "k\u00F6rper" << endl;
    
    // 宽字符类型 扩展字符集
    wchar_t     bob = L'P';
    char16_t    ch1 = u'q';
    char32_t    ch2 = U'\U0000222B';
    wcout << bob << endl << L"tall" << endl << ch1 << endl << ch2 << endl ;
    
    // 转义序列
    cout << "\aOperation \"HyperHype\" is now activated!\n";
    cout << "Enter your agent code: ********\b\b\b\b\b\b\b\b";
    long code;
    cin  >> code;
    cout << "\aYou entered " << code << "...\n";
    cout << "\aCode verified! Proceed with Plan Z3!\n";
    
    return 0;
}
