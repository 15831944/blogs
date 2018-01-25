21互联远程教育网_计算机二级考试_金文VB教程

退出：Alt+Q
控制菜单：Alt+Space
激活菜单栏：Alt或F10
激活属性窗口：Ctrl+PgUp或Ctrl+PgDn
设计模式
运行模式
中断模式

窗体文件frm
标准模块文件bas(纯代码文件)
类模块文件cls(预定义的类)
工程文件vbp
工程组文件vbg
资源文件res(纯文本文件)

一个应用程序最多255个窗体
内部控件或标准控件和ActiveX控件
ESC关闭打开的不需要的菜单或对话框
工具栏有浮动格式和固定格式

第二章
第一节 对象及操作
面向对象：用鼠标对窗口操作
属性
事件 事件过程
方法 对象名.方法名(对象名是窗口时可省略)
用?代替print

第二节 窗体
窗体的结构和属性：
AutoRedraw(自动重画,刷新)
BackColor(背景色)
BorderStyle(边框类型) 只读，默认为2，大小可变，双边界线；值为0，无边框
Caption(标题) 窗体标题栏上显示的标题
ControlBox(控制框)
Enabled(允许) 激活或禁止(不活动)状态
Font(字形属性)
ForeColor(前景颜色) Print方法
Height(高) 单位:twip 单精度数
Wideth(宽)
MaxButton(最大化按钮) 运行期间有效，设计阶段不起作用，即总显示
MinButton(最小化按钮)
Name(对象的名称) 只读，运行时不能更改，写代码时的对象名，更改为了编写简便
Picture(图形) 在对象(图片框,图像框)中选择显示图片
Top(顶端)
Left(左端)
Visible(可见性) 计时器不可设,运行时有效,设计时总可见
WindowState(窗体状态) 0正常(标准)状态，1最小化状态，2最大化状态

窗体事件
Click(单击)事件
DblClick(双击)事件 单击事件也执行，窗体有双击事件，命令按钮没有
Load(装入)事件 属性和变量初始化
Unload(卸载)事件 从内存中清除窗体
Activate(活动) 当前窗口活动时
Deactivate(非活动) 其他窗口活动时
Paint(绘画)事件 窗体移动和覆盖时

第三节 控件
标准(内部)控件 由.exe文件提供
ActiveX控件 扩展名为.ocx的独立文件
可插入对象 可添加到工具箱

Pointer(指针) 改变控件位置和大小
PictureBox(图片框) 容器控件，显示图像和文本
Label(标签) 输出文本
text(文本框) 输入和输出
Frame(框架) 组合相关对象
CommandButton(命令按钮)
CheckBox(复选框)
OptionButton(单选按钮)
ComboBox(组合框) 文本框和列表框的组合，既可选择又可编辑
ListBox(列表框)
HScrollBar(水平滚动条)
VScrollBar(垂直滚动条)
Timer(计时器) 运行时不可见
DriveListBox(驱动器列表框)
DirListBox(目录列表框) 
FileListBox(文件列表框)
Shape(图形，形状)
Line(直线)
Image(图像框) 有凹陷
Data()
OLE() 

控件值(默认属性,属性可省略)
控件.属性
text1.text
label1.caption

第4节 控件的画法和基本操作

拖拽
双击
按住ctrl键拖拽

删除控件标题:break键
控件数组

题：
激活属性窗口:F4键
属性窗口:对象框,属性显示方式,属性列表,属性解释.

第3章 简单程序设计
第1节 VB中的语句
语句,命令,函数不区分大小写
复合语句行,用冒号隔开
续行符:下划线(前面加空格)
常用语句:
赋值语句:[Let]目标操作符=源操作符(先计算,后赋值)
注释语句:Rem或单引号+注释内容(不能放在续行符后面)
结束语句:
end sub
end function
end if
end type
end select

第2节 编写简单的VB应用程序
步骤：
建立可视用户界面
设置可视界面特性
编写事件驱动代码

代码编辑器
工具―>选项―>编辑器

第3节 程序的保存,装入和运行
窗体文件.frm
标准模块.bas
类模块.cls
工程文件.vbp

保存:由小到大
保存窗体和模块―>保存工程

解释运行
生成可执行文件

第4章 VB程序设计基础
第1节 数据类型
基本数据类型
字符串(string)
空串
变长字符串
定长字符串
数值
单精度浮点数(single) E
双精度浮点数(double) D
货币(currency) 定点数 小数点后4位
日期(date) #

用户定义的数据类型
Type语句 写在窗体或标准模块的通用声明部分 默认public

枚举类型
Enum语句
常数表达式  long型 默认值为0,1,2...	

第2节 变量和常量
文字常量
字符串常量 ASCII字符
数值常量 整型,长整型,货币型,浮点型
类型说明符 % & 
符号常量
Const 类型说明符放在常量名或变量名后

变量的类型和定义
用类型说明符标识 放在变量名后
在定义变量时指定类型 
Declare 变量名 As 类型(每个变量都要有As类型说明)
Dim 自动变量
Static 静态变量
Public 全局变量(标准模块中)

DefType 字母范围(声明部分)
DefInt a-f

记录类型变量
标准模块
窗体模块 需要加private Type

第3节 变量的作用域
局部变量
模块变量(窗体层变量,标准模块变量)
全局变量 public语句
默认声明:变体类型数据
要求变量声明:Option Explicit(通用声明部分)

第4节 常用内部函数
转换类
Int(x) integer
Fix(x)
Hex(x) hexadecimal
Oct(x) octonary
Asc(x) ascii
Chr(x) character
Str(x) string
Cint(x) int
Clng(x) long
Ccur(x) currency
Cdbl(x) double
Csng(x) single
单精度数前7位有效,第8位四舍五入

数学类
Sin(x) sine
Cos(x) cosine
Tan(x) tangent
Atn(x) arc tangent
Abs(x) absolute
Sgn(x) sign 1 0 -1
Sqr(x) square root
Exp(x) exponent

日期型
Day(Now)
WeekDay(Now)
Month(Now)
Year(Now)

时间型
Hour(Now)
Minute(Now)
Second(Now)

随机数
Rnd(x) random

第5节 字符串处理与字符串函数
字符处理机制
ANSI
UniCode
StrConv函数
vbFromUniCode
vbUniCode
len函数
lenb函数

字符串函数
删除空白字符函数
LTrim$(str)
RTrim$(str)
Trim$(str)
字符串截取函数
Left$(str,n)
Mid$(str,p,n)
Right$(str,n)
字符串长度测试函数
Len(字符串) 长度
Len(变量名) 存储空间
String$函数
String$(n,ASCII码)
String$(n,字符串)
空格函数
Space(n)
字符串匹配函数
InStr() 0区分大小写(默认) 1不区分大小写
字母大小写转换函数
Ucase$(字符串) upper
Lcase$(字符串) lower
插入字符串语句
Mid$(字符串,p,n)=子字符串

第6节 运算符和表达式
算数运算符
Mod运算:结果符号与被除数符号相同
关系运算符 True False
逻辑运算符 1 and 0, true and false
Not,And,Or,Xor,Eqv,Imp(equal value,imply)

第5章 数据的输入输出
第1节 数据输出 Print方法
逗号分隔:
空格或分号分隔:紧凑格式
逗号结尾:不自动换行,下一区段
分号结尾:同一行紧凑输出

与Print方法有关的函数
Tab(n)
Spc(n)

格式输出
格式输出函数
Format$(数值表达式,格式字符串)
默认时,format输出整数字符串不带符号位,而str函数留有符号位

其他方法和属性
Cls方法
Move方法
TextHeight方法
TextWidth方法
FontSize方法

第2节 数据输入 InputBox函数
InputBox(prompt,title,default,xpos,ypos,helpfile,context)
默认返回值类型:字符串
取消则返回空字符串
一次调用只能输入一个值

第3节 MsgBox函数和MsgBox语句
函数:MsgBox(msg,type,title,helpfile,context)
语句:MsgBox Msg$ 格式相同，但无返回值

第4节 字形
字体类型和大小
FontName
FontSize
FontBold
FontItalic
FontUnderline
FontStrikethru

第6章 常用控件标准
第1节 文本控件
标签
Alignment
AutoSize
BoderStyle 0 1
Caption
BackStyle 0 1
WordWrap 整字换行
注意先设置wordwrap再设置autosize

文本框
MaxLength 默认0,32K
MultiLine 默认false
按Ctrl+Enter可以插入空行
PasswordChar
ScrollBars 0 1 2 3 
前提：multiline有效
SelLength
SelStart
SelText
Locked

文本框事件和方法
change事件
gotfocus事件
lostfocus事件
setfocus方法

第2节 图形控件
图片框picturebox 
容器控件,按钮是图片框的一部分
可用print方法接收文本
图像框imagebox
非容器控件
不支持print方法
CurrentX
CurrentY
Picture 默认图片框适应图像 bitmap,icon,metafile,jpeg,gif
Stretch 默认图像适应图像框,设置为true则适应图像

运行期间装入图形文件
对象.Picture=LoadPicture("完整路径文件名")

直线line和形状shape
BorderColor
BorderStyle
0-transparent 透明
1-solid 实线(默认)
2-dash 虚线
3-dot 点线
4-dash-dot 点划线
5-dash-dot-dot 双点划线
6-inside-solid 内实线
BorderWidth 单位:像素
BackStyle 0 1 opaque
FillColor 前提:fillstyle不为1透明
fillstyle 0-7
shape 0-5

第3节 按钮控件
Cancel属性 Esc键
Default属性 Enter键
Style属性 0 1
Picture属性 前提:style为1
DownPicture属性 前提:style为1
DisablePicture属性

第4节 选择控件 复选框Check和单选按钮Option
Value
Alignment
Style 只读
灰显grayed和禁用disabled不同

第5节 选择控件 列表框List和组合框ComboBox
列表框和文本框组合

列表框属性
Columns
List
ListCount
ListIndex 多选时返回最后选中的一项的下标
MultiSelect
Selected
SelCount 前提:multiselect 1 2
Sorted
Style 只读
Text

列表框方法
AddItem
Clear
RemoveItem

组合框属性
Style 0 1 2
Text

组合框事件
DbClick 前提:style=1
Click
DropDown
Change 前提:style=0 1

组合框方法
AddItem
Clear
RemoveItem

第6节 滚动条
属性
Max 100
Min 0
LargeChange 10
SmallChange 1
Value 位置
事件
Scroll
Change

第7节 计时器
属性
Name
Enabled
Interval 次/毫秒
最大时间间隔65s
单位:毫秒
事件
Timer

第8节 框架
容器控件
事件
Click
DbClick

第9节 焦点与Tab顺序
SetFocus方法 
前提:Enabled,Visible
有效:Load事件之后
TabStop属性
TabIndex属性
快捷键设置:& 显示为下划线
Tab站只有一个

题
Icon属性 最小化时显示的图标
ControlBox属性
Scorllbar 前提:multiline
0-none
1-horizontal
2-vertical
3-both
获得焦点方法:setfocus
Alignment属性
0-left
1-right
2-center
columns属性 0 1
文本框默认单行显示
multiline属性
interval=0,计时器暂时失效
组合框的style属性
0-dropdown combo 下拉式组合框
1-simple combo 简单组合框
2-dropdown list 下拉式列表框 text不能更改

第7章 VB控制结构
if语句
单行结构 then后面语句在同一行
块结构 有end if
数值表达式: 非0真，0假
逻辑表达式: -1真，0假
多个条件为真时，也只能执行第一个满足的语句。
块结构条件语句可以嵌套

IIf函数
result=IIf(条件，true部分，false部分)
false部分执行不到也需合法

第2节 多分支控制结构
Select Case
,
to
Is
case else
End Select
测试表达式
表达式表列

第3节 For循环控制结构
计数循环
操作变量
形式变量
For-next
Exit For
实例：斐波那数列

第4节 当循环控制结构
While-Wend 

第5节 Do循环控制结构
Do
Exit do
Loop while
Loop until

Do while
Do until
Exit Do
Loop

第6节 多重循环

第7节 题
Setfocus方法不能出现在Load事件中
For循环初值，终值，步长可以为实数

第8章 数组
定义
Dim 窗体模块，标准模块
ReDim 过程 动态数组
Static 过程 静态数组
Public 标准模块 全局数组

下标下界：option base 1 窗体层，模块层

LBound
UBound

第2节 静态数组和动态数组
ReDim Preserve 
Erase
Private Function
End function

第3节 数组的基本操作
数组元素的引用
数组元素的输入
数组元素的输出
数组元素的复制
冒泡排序
大数沉底
n个数比较n-1轮，每轮从1比到i-1

for each in
next

sub过程
引用（传地址） byref（默认）
传值（传数值） byval
sub过程无法返回数值

第4节 数组的初始化
数组变量
Array函数 一维变体类型数组的初始化

第5节 控件数组
index属性

第9章 过程
第1节 sub过程
sub过程 子程序过程 无返回值 不能嵌套
function过程 函数过程

sub
exit sub
end sub

static局部静态变量（默认）
private 私有过程
public 公有过程

建立sub过程
标准模块和窗体模块中
工程->添加模块；工具->添加过程

调用sub过程
call语句 过程名 （实际参数）
过程名 实际参数，实际参数

事件过程 放在窗体模块中（也可以被调用）
控件事件过程
窗体事件过程

通用过程 放在窗体模块中和标准模块中

第2节 function过程（不能嵌套）
function
过程名=表达式
exit function
end function
返回值
数值函数默认返回0
字符串函数默认反水空串

调用function函数

第3节 参数传送
按位置传送
指名参数传送
实参:=实参值

引用byref（传地址默认）
传值byval

数组参数的传送
LBound
UBound

第4节 可选参数和可变参数
optional
ismissing

paramarray

第5节 对象参数
窗体参数
控件参数

第6节 局部内存分配
static

第7节 shell函数
必须有返回值
异步执行

第8节 题
过程的定义不能嵌套
过程的调用可以嵌套
默认为传地址
