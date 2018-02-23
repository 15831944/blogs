#include "stdafx.h"

//
//定义特殊字符的替换字符
//
//特别注意定义规则：
//		字符多的必须要放在前面，否则程序处理可能会有误
//
char *SpecialWord[] = {	"&quot;",	//"""
						"&apos;",	//"'
						"&amp;",	//"&"
						"&lt;",		//"<"
						"&gt;"		//">""
						};

//定义特殊字符
char SpecialChar[] = {	'\"',
						'\'',
						'&',
						'<',	
						'>'
						};


char REQ[] = "Req";
char ACK[] = "Ack";
