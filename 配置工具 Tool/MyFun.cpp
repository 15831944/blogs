#include "StdAfx.h"

CString Str(int integer)
{
	CString tempStr;
	tempStr.Format("%d",integer);
	return tempStr;
}

CString Str(float mfloat)
{
	CString tempStr;
	tempStr.Format("%0.2f",mfloat);
	return tempStr;
}

CString Str(double mfloat)
{
	CString tempStr;
	tempStr.Format("%0.2lf",mfloat);
	return tempStr;
}

CString Str(char *mchr)
{
	CString tempStr;
	tempStr.Format("%s", mchr);
	return tempStr;
}

int myatoi(const char *string)
{
	CString str;
	str = string;
	if (!str.IsEmpty())
		return atoi(str);
//	else
//		AfxMessageBox("Err:此项没有键值");

	return 0;
}
float myatof(const char *string)
{
	CString str;
	str = string;
	if (!str.IsEmpty())
		return atof(str);
//	else
//		AfxMessageBox("Err:此项没有键值");

	return 0;
}

void msg(CString str)
{
	AfxMessageBox(str);
}

void msg(int mini)
{
	AfxMessageBox(Str(mini));
}

void msgdebug(int mini)
{
	msg("reach here"+Str(mini));
}

bool bForDel = false;

void *memmem(const void *haystack, size_t haystacklen,
			 const void *needle, size_t needlelen)
{
	char *dst = (char*)haystack;
	char *src = (char*)needle;
	unsigned int obj_posi = 0;
	unsigned int i = 0;

	if(haystacklen < needlelen)
		return NULL;

	while(obj_posi < haystacklen)
	{
		if(*(dst + obj_posi + i) == *(src + i))
		{
			i++;
			if(i >= needlelen)
				return (dst + obj_posi);
		}
		else
		{
			i = 0;
			obj_posi++;
		}
	}

	return NULL;
}
