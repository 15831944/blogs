// 配置文件结构

const unsigned short BitMask[] = {
		0x0001,0x0002,0x0004,0x0008,
		0x0010,0x0020,0x0040,0x0080,
		0x0100,0x0200,0x0400,0x0800,
		0x1000,0x2000,0x4000,0x8000
};

#define NONE_TREE 0
#define RTU_TREE  3
#define PROC_TREE 4
#define OBJ_TREE  5

const DWORD   START_ROOTITEM   =  0;
const DWORD   END_ROOTITEM     =  1000;
const DWORD   START_CHILDITEM  =  1001;
const DWORD   END_CHILDITEM    =  10000;

const CString BeginBorder     = "[";
const CString EndBorder       = "]";
const CString Remark          = "#";
const CString Demo            = "%";

//const CString Info_Sign	 = "INFO";
//const CString PZK300CFG_SIGN = "SETINPUT_";
//const CString PZK300PRO_SING = "PROTECT_";
#define PROTECT_FILE	2
#define SXPLC_FILE		3
#define ZJPLC_FILE		4
#define JZSLG_FILE      5
#define MLPLC_FILE      6
#define FAULT_FILE      7
#define SXJZS_FILE		8 //绍兴集中式 2015.7.15 lizhen
#define KMG_FILE		9 //看门狗 2015.7.15 lizhen

#define SXYJ_FILE		10//绍兴液晶 2016.3.14
#define FDG_FILE		11 //分段狗 2017
//保护用配置
const CString FileName	= "FILENAME";
const CString InfoSign	= "INFO";
const CString LineSign	= "prot_Line";
const CString ControlW  = "ControlW";
const CString prot_general = "prot_general";
//PLC用配置
const CString Plcenable = "PLC_ENABLE";
const CString Limitvalue= "LIMIT_VALUE";
const CString Modetype  = "MODE_TYPE";
const CString Plctime   = "PLC_TIME";
const CString Jxchz     = "JXCHZ_ENABLE";
const CString Cxchz     = "CXCHZ_ENABLE";

const CString ConfigSign	= "CONFIG";
const CString DelayTimeSign	= "DELAYTIME";
const CString LV_ProtSign	= "IN_LOSTV_PROTECT";
const CString AutoBzkSign	= "AUTO_BZT_PROTECT";
const CString RecloseSign	= "PROTECT";
const CString UnitSign		= "UNIT_";
const CString CtrlTimeSign	= "CONTROL_TIME";
const CString BZTCONFIG		= "BZT_CFG";

const int Sec_None		= 0;
//const int Sec_Info		= 18;
//const int Sec_300_Cfg	= 19;
//const int Set_300_Pro	= 20;
const int Sec_Info		= 1;
const int Sec_Line		= 2;
const int Sec_Config	= 3;
const int Sec_DelayTime	= 4;
const int Sec_LV_Prot	= 5;
const int Sec_Bzt		= 6;
const int Sec_Unit		= 7;
const int Sec_Auto_Bzt	= 8;
const int Sec_Ctrl_time	= 9;

const int Zj_Sec_Config = 10;
const int Zj_Sec_DelayTime = 11;
const int Zj_Sec_Unit	= 12;
const int Zj_Sec_Bzt	= 13;
const int Jz_Info       = 14;

const int Sec_enable    = 15;
const int Sec_value     = 16;
const int Sec_type      = 17;
const int Sec_time      = 18;
const int Sec_jxchz     = 19;
const int Sec_cxchz     = 20;
const int Sec_ControlW  = 21;
const int Sec_prot_general = 22;


//故障配置 by lz 2014/12/24
const int Sec_Byd_Current = 30;
const int Sec_Byd_Voltage = 31;
const int Sec_Byd_ZeroI = 32;
const int Sec_Byd_ZeroU = 33;
const int Sec_Flt_Current = 34;
const int Sec_Flt_3I0 = 35;


const int Sec_FileName	= 100;

#define NO_TYPE		0
//#define BYTE_TYPE	1
//#define WORD_TYPE	2
#define INT_TYPE	1
//#define LONG_TYPE	4
#define FLOAT_TYPE	2
#define STR_TYPE	3

typedef union {
	char SetByte;
	short SetWord;
	int SetInt;
	long SetLong;
	float SetFloat;
	char SetStr[32];
} Pzk300UnionStru;

typedef struct Pzk300CfgStruct_
{
	CString ChinaName;					//名称
	CString SetInputName;				//程序内用的常量名
	int SetInputDataStyle;				//数据类型
	Pzk300UnionStru SetInputValue;		//数据
	CString SetInputDataUnit;			//单位
	Pzk300UnionStru SetInputDataHLimit;	//最大量程值
	Pzk300UnionStru SetInputDataLLimit;	//最小量程值
	CString Remark;						//备注
} Pzk300CfgStruct;

#define MAX_300_NORMAL_CFG 64
typedef struct {
	Pzk300CfgStruct NormalCfg[MAX_300_NORMAL_CFG];
	int num;
} Pzk300NormalCfgStru;

typedef struct{
	CString ProtectName;
	int ProtectEnable;
	int ProtectValue;			//
	CString ProtectValueUnit;	//伏#数据单位
	int ProtectValueHLimit;		//数据上限
	int ProtectValueLLimit;		//=200; //数据下限
	int	ProtectTime;			//=60;         //单位是秒
	CString ProtectTimeUnit;	//数据单位
	int ProtectTimeHLimit;		//数据上限
	int ProtectTimeLLimit;		//=0;
} Pzk300ProItemCfgStru;

#define MAX_300_PRO_CFG 32
typedef struct{
	int num;
	Pzk300ProItemCfgStru ProcCfg[32];
} Pzk300ProCfgStru;

typedef struct{
	int onetime;
	int twotime;
	int outtime;
	}AllTime;
typedef struct {
	CString Version;	//版本号
	CString CreateTime;	//创建时间
	int LineNum;		//线路数
	int OutNum1;
	int OutNum2;

	int Byd_SOEEnble;
	int Flt_YXEnble;
	int Flt_RepEnble;

	int Prot_YXEnable;//保护虚遥信使能
	int Prot_MsgEnable;//保护信息上报使能


	int PNPL;			//每条线路的保护项数
	float VOGE;           //无压门槛值
	float CURRENT;        //无流门槛值
	int modetype;       //0表示进线是断路器，出线是负荷开关
	int isuseful;
	int ControlW_Len;
	int ControlWByte[128];
	int FixActTime;   //保护固有动作时间(ms,设置范围0~50ms)
	int Switch_Remote;  //远方遥信
	int Switch_Local;   //就地遥信
	int V_ConnectMode;
	AllTime atme;
} ProtNormalStru;

typedef struct {
	int Line_Sbo;		//#保护跳闸/合闸对应的sbo号
	int Line_Switch;	//#保护跳闸/合闸对应的开关号
	int Line_Switch_Remote;//#Remote operation enable
	int Line_Switch_Local;	//#Local operation enable
	int V_ConnectMode;

	int LineNum;
} LineCfgStru;

typedef struct {
	CString Name;
	int Type;
	int Enable;
	float Value1;
	float Value2;
	float Value;
	float Time;
	int Line_Switch_Local;
	CString	Unit;
} ProtItemStru;
typedef struct{
	bool istrue;
	CString name;
	int yesorno;
} pzk36bplc;
typedef struct{
	bool istrue;
	int  time;
	int yesorno;
} pzk36bmlplc;
typedef struct {
	LineCfgStru LineCfg;
	ProtItemStru ProtItem[32];
} LineStr;

#define _Max_Prot_Line 32
typedef struct {
	ProtNormalStru Cfg;
	LineStr Line[_Max_Prot_Line];
} ProtCfgStru;

typedef struct {
	bool PlcEnable;		//PLC逻辑控制开关
	int UnitTotal;		//=10;	#总控制单元数
	int InNum;			//=2;	#进线个数
	int OutNum1;		//=3;	#对应进线1的出线个数
	int OutNum2;		//=3;	#对应进线2的出线个数
	bool RecloseCheckVol; //决定出线开关重合前是否判电压
	bool BztCheckVol;	//备投重合前是否判断另一侧有压
	int LogicVol;
} PlcCfgStru;

typedef struct {
	int InRecloseTime;	//=4000;	#进线重合闸延时时间(t1)
	int OutRecloseTime;	//=5000;	#出线重合闸延时时间(t2)
	int InReclose2Time;	//=13000;	#进线重构延时时间(t3)
	int ConnectTime;	//=14000;	#母联备自投延时时间(t4)
	int t5;				//=10000;
	int t6;				//=16000;
} PlcDelayStru;

typedef struct {
	bool Enable1;	//=yes;
	int Delay1;		//=3000;
	int Value1;		//=5000;
	bool Enable2;	//=yes;
	int Delay2;		//=6000;
	int Value2;		//=5000;
} PlcLVProtStru;

typedef struct {
	bool Enable;
	int Delay;
	int Value;
} PlcAutoBztStru;

typedef struct {
	int TripTime;
	int CloseTime;
} CtrlTimeStru;

typedef struct {
	bool ConnectEnable;
} PlcBztStru;

typedef struct {
	bool Valid[32];
	bool ReClose[32];
	bool CheckVol[32];
	unsigned short RecloseDelay[32];
} PlcRecStru;

typedef struct {
	PlcCfgStru		Cfg;
	PlcDelayStru	Delay;
	PlcLVProtStru	LVProt;
	PlcAutoBztStru	AutoBzt;
	PlcBztStru		Bzt;
	PlcRecStru		Reclose;
	CtrlTimeStru	CtrlTime;
} PlcStru;

typedef struct {
	bool PlcEnable;		//PLC逻辑控制开关
	int UnitTotal;		//=10;	#总控制单元数
	int	LogicVol;
} ZjPlcCfgStru;

typedef struct {
	int InRecloseTime;	//=4000;	#进线重合闸延时时间(t1)
	int PlcTime;
} ZjPlcDelayStru;

typedef struct {
	bool Enable;
	int Delay;
} ZjPlcBztStru;

typedef struct {
	bool ReClose[32];
	bool Valid;
} ZjPlcRecStru;

typedef struct {
	ZjPlcCfgStru	Cfg;
	ZjPlcDelayStru	Delay;
	ZjPlcBztStru	Bzt[2];
	ZjPlcRecStru	Reclose;
} ZjPlcStru;
typedef struct{
	int NoVoltageValue;
	int NoCurrentValue;
}BHJZS;





/****绍兴集中式 2015.7.8****** lizhen****/

#define SWITCH_KIND 20 //开关类型最大配置数 例如有20个不同的开关
#define SELECT		20 //每个开关里面有20项配置
//绍兴集中式 读取prot_select里面的数据到数组


typedef struct {
	CString Version;	//版本号
	CString CreateTime;	//创建时间
	int ProtLineNum;		//线路数

	int Prot_YXEnable; // #保护虚遥信使能
	int Prot_MsgEnable;// #保护信息上报使能
//	int Byd_SOEEnable;// #越限告警SOE使能
//	int Flt_YXEnable; //#故障检测分相上报使能
//	int Flt_RepEnable; //#故障报文上报使能
	int PLC_Enable;//PLC投入
	int FixActTime;   //保护固有动作时间(ms,设置范围30~45ms)

	int MxType;//母线类型
	int LeftDTUNum;//左侧终端数量

	int ProtNumPerLine;			//每条线路的保护项数

} SXJZSNormalStru;


typedef struct {

	int Switch_Type;       //开关类型(0-断路器, 1-负荷开关)
	int SBO_Num;		//线路SBO号
	int Switch_Num;	// #线路开关号
	int Line_Type;//线路类型:0-主线;1-分支线
	int CxLogicFlag;//出线逻辑:0-不判;255-判出线逻辑
	int CHZ_Enable;//#重合使能:0-不使能;255-重合闸使能
	int PHaveV_Flag;//#重合闸判有压标志:0-不判是否有压;255-判有压
	int PSwitchStatus; //#判开关位置:0-不判开关位置;255-判开关位置,实际就是判是否在分位
	CString Line_Name;//线路名称

	int ZXCHZTime;//主线重合闸时间
	int FZXCHZTime;//分支线重合闸时间

} SXJZSLineCfgStru;

typedef struct {
	int Type;
	CString Name;
	int Enable;
	float Value;
	float Time;
//	int Line_Switch_Local;
	CString	Unit;
} SXJZSItemStru;


typedef struct {
	SXJZSLineCfgStru LineCfg;
	SXJZSItemStru SXJZSItem[32];
} SXJZSLineStr;




#define _Max_SXJZS_Line 32
typedef struct {
	SXJZSNormalStru Cfg;
	SXJZSLineStr Line[_Max_SXJZS_Line];
	CString SXJZSSelct[SWITCH_KIND];//有多少种开关，就有多少个Prot_Select
} SXJZSCfgStru;



/*****看门狗 2015.7.15 lizhen *************/

#define KMG_SWITCH_KIND 20 //开关类型最大配置数 例如有20个不同的开关
#define KMG_SELECT		20 //每个开关里面有20项配置
//绍兴集中式 读取prot_select里面的数据到数组


typedef struct {
	CString Version;	//版本号
	CString CreateTime;	//创建时间
//	int ProtLineNum;		//线路数

	int Prot_YXEnable; // #保护虚遥信使能
	int Prot_MsgEnable;// #保护信息上报使能
	int Byd_SOEEnable;// #越限告警SOE使能
	int Flt_YXEnable; //#故障检测分相上报使能
	int Flt_RepEnable; //#故障报文上报使能
//	int PLC_Enable;//PLC投入

	int Flt_RcwEnable;//故障录波使能
	int V_ConnectMode;//电压接线方式
	int FixActTime;//保护固有动作时间

	int ProtNumPerLine;			//每条线路的保护项数

} KMGNormalStru;


typedef struct {

	int Switch_Type;       //开关类型(0-断路器, 1-负荷开关)
	int SBO_Num;		//线路SBO号
	int Switch_Num;	// #线路开关号

} KMGLineCfgStru;

typedef struct {

	int Line;
	int Type;
	CString Name;
	int Enable;
	float Value1;
	float Value2;
	float Time;
//	int Line_Switch_Local;
	CString	Unit;
} KMGItemStru;


typedef struct {
	KMGLineCfgStru LineCfg;
	KMGItemStru KMGItem[32];
} KMGLineStr;




#define _Max_KMG_Line 32
typedef struct {
	KMGNormalStru Cfg;
	KMGLineStr Line[_Max_KMG_Line];
	CString KMGSelct[SWITCH_KIND];//有多少种开关，就有多少个Prot_Select
} KMGCfgStru;




/*****绍兴液晶 2016.3.14 lizhen *************/


typedef struct {
	int ProtLineNum;
	CString DeviceName;
} SXYJNormalStru;


typedef struct {

	CString LineName; //线路名
	int YxNum;		//遥测数
	int YcNum;	// 遥信数

} SXYJLineCfgStru;

typedef struct {
	CString dot;
	CString Name;
	CString	Unit;
	CString Scale;
	CString Divied;//chushu
} SXYJYCItemStru;

typedef struct {
	CString dot;
	CString Name;
} SXYJYXItemStru;



typedef struct {
	SXYJLineCfgStru LineCfg;
	SXYJYCItemStru SXYJYCItem[32];
	SXYJYXItemStru SXYJYXItem[32];
} SXYJLineStr;




#define _Max_SXYJ_Line 32
typedef struct {
	SXYJNormalStru Cfg;
	SXYJLineStr Line[_Max_SXYJ_Line];
} SXYJCfgStru;

/*****分段狗 2017.4.26  *************/

#define FDG_MODE_KIND 20 //开关类型最大配置数 例如有20个不同的开关
#define FDG_SELECT		20 //每个开关里面有20项配置
//绍兴集中式 读取prot_select里面的数据到数组


typedef struct {
	CString Version;	//版本号
	CString CreateTime;	//创建时间
//	int ProtLineNum;		//线路数

	int Prot_YXEnable; // #保护虚遥信使能
	int Prot_MsgEnable;// #保护信息上报使能
	int Byd_SOEEnable;// #越限告警SOE使能
	int Flt_YXEnable; //#故障检测分相上报使能
	int Flt_RepEnable; //#故障报文上报使能
//	int PLC_Enable;//PLC投入

	int Flt_RcwEnable;//故障录波使能
	int V_ConnectMode;//电压接线方式
	int FixActTime;//保护固有动作时间

	int ProtNumPerLine;			//线路的保护项数
	int VTimePerLine;			//电压时间型功能数量
	int VITimePerLine;			//电压电流时间型功能数量
	int SelfAdaptionPerLine;	//自适应综合型功能数量
	int LLSwitchPerLine;		//联络合闸功能数量

	int DeviceMode;				//
	int SelectType;
	int AdpSmlType;
	int SwitchType;
} FDGNormalStru;

typedef struct {

	int Switch_Type;       //开关类型(0-断路器, 1-负荷开关)
//	int SBO_Num;		//线路SBO号
//	int Switch_Num;	// #线路开关号

} FDGLineCfgStru;

typedef struct {

	int Line;
	int Type;
	CString Name;
	int Enable;
	float Value;
	float Time1;
	float Time2;
//	int Line_Switch_Local;
	CString	Unit;
} FDGItemStru;


typedef struct {
	FDGLineCfgStru LineCfg;
	FDGItemStru FDGItem[32];
} FDGLineStr;




#define _Max_FDG_Line 32
typedef struct {
	FDGNormalStru Cfg;
	FDGLineStr Line[_Max_FDG_Line];
	CString FDGSelct[FDG_MODE_KIND];//
} FDGCfgStru;
