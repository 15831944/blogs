
#define MsgBox AfxMessageBox
#define msgbox MsgBox

CString Str(int integer);
CString Str(float mfloat);
CString Str(double mfloat);
CString Str(char *mchr);

int myatoi(const char *string);
float myatof(const char *string);
void msg(CString str);
void msg(int mini);
void msgdebug(int mini);

extern bool bForDel;