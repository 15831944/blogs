// �����ļ��ṹ

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
#define SXJZS_FILE		8 //���˼���ʽ 2015.7.15 lizhen
#define KMG_FILE		9 //���Ź� 2015.7.15 lizhen

#define SXYJ_FILE		10//����Һ�� 2016.3.14
#define FDG_FILE		11 //�ֶι� 2017
//����������
const CString FileName	= "FILENAME";
const CString InfoSign	= "INFO";
const CString LineSign	= "prot_Line";
const CString ControlW  = "ControlW";
const CString prot_general = "prot_general";
//PLC������
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


//�������� by lz 2014/12/24
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
	CString ChinaName;					//����
	CString SetInputName;				//�������õĳ�����
	int SetInputDataStyle;				//��������
	Pzk300UnionStru SetInputValue;		//����
	CString SetInputDataUnit;			//��λ
	Pzk300UnionStru SetInputDataHLimit;	//�������ֵ
	Pzk300UnionStru SetInputDataLLimit;	//��С����ֵ
	CString Remark;						//��ע
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
	CString ProtectValueUnit;	//��#���ݵ�λ
	int ProtectValueHLimit;		//��������
	int ProtectValueLLimit;		//=200; //��������
	int	ProtectTime;			//=60;         //��λ����
	CString ProtectTimeUnit;	//���ݵ�λ
	int ProtectTimeHLimit;		//��������
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
	CString Version;	//�汾��
	CString CreateTime;	//����ʱ��
	int LineNum;		//��·��
	int OutNum1;
	int OutNum2;

	int Byd_SOEEnble;
	int Flt_YXEnble;
	int Flt_RepEnble;

	int Prot_YXEnable;//������ң��ʹ��
	int Prot_MsgEnable;//������Ϣ�ϱ�ʹ��


	int PNPL;			//ÿ����·�ı�������
	float VOGE;           //��ѹ�ż�ֵ
	float CURRENT;        //�����ż�ֵ
	int modetype;       //0��ʾ�����Ƕ�·���������Ǹ��ɿ���
	int isuseful;
	int ControlW_Len;
	int ControlWByte[128];
	int FixActTime;   //�������ж���ʱ��(ms,���÷�Χ0~50ms)
	int Switch_Remote;  //Զ��ң��
	int Switch_Local;   //�͵�ң��
	int V_ConnectMode;
	AllTime atme;
} ProtNormalStru;

typedef struct {
	int Line_Sbo;		//#������բ/��բ��Ӧ��sbo��
	int Line_Switch;	//#������բ/��բ��Ӧ�Ŀ��غ�
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
	bool PlcEnable;		//PLC�߼����ƿ���
	int UnitTotal;		//=10;	#�ܿ��Ƶ�Ԫ��
	int InNum;			//=2;	#���߸���
	int OutNum1;		//=3;	#��Ӧ����1�ĳ��߸���
	int OutNum2;		//=3;	#��Ӧ����2�ĳ��߸���
	bool RecloseCheckVol; //�������߿����غ�ǰ�Ƿ��е�ѹ
	bool BztCheckVol;	//��Ͷ�غ�ǰ�Ƿ��ж���һ����ѹ
	int LogicVol;
} PlcCfgStru;

typedef struct {
	int InRecloseTime;	//=4000;	#�����غ�բ��ʱʱ��(t1)
	int OutRecloseTime;	//=5000;	#�����غ�բ��ʱʱ��(t2)
	int InReclose2Time;	//=13000;	#�����ع���ʱʱ��(t3)
	int ConnectTime;	//=14000;	#ĸ������Ͷ��ʱʱ��(t4)
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
	bool PlcEnable;		//PLC�߼����ƿ���
	int UnitTotal;		//=10;	#�ܿ��Ƶ�Ԫ��
	int	LogicVol;
} ZjPlcCfgStru;

typedef struct {
	int InRecloseTime;	//=4000;	#�����غ�բ��ʱʱ��(t1)
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





/****���˼���ʽ 2015.7.8****** lizhen****/

#define SWITCH_KIND 20 //����������������� ������20����ͬ�Ŀ���
#define SELECT		20 //ÿ������������20������
//���˼���ʽ ��ȡprot_select��������ݵ�����


typedef struct {
	CString Version;	//�汾��
	CString CreateTime;	//����ʱ��
	int ProtLineNum;		//��·��

	int Prot_YXEnable; // #������ң��ʹ��
	int Prot_MsgEnable;// #������Ϣ�ϱ�ʹ��
//	int Byd_SOEEnable;// #Խ�޸澯SOEʹ��
//	int Flt_YXEnable; //#���ϼ������ϱ�ʹ��
//	int Flt_RepEnable; //#���ϱ����ϱ�ʹ��
	int PLC_Enable;//PLCͶ��
	int FixActTime;   //�������ж���ʱ��(ms,���÷�Χ30~45ms)

	int MxType;//ĸ������
	int LeftDTUNum;//����ն�����

	int ProtNumPerLine;			//ÿ����·�ı�������

} SXJZSNormalStru;


typedef struct {

	int Switch_Type;       //��������(0-��·��, 1-���ɿ���)
	int SBO_Num;		//��·SBO��
	int Switch_Num;	// #��·���غ�
	int Line_Type;//��·����:0-����;1-��֧��
	int CxLogicFlag;//�����߼�:0-����;255-�г����߼�
	int CHZ_Enable;//#�غ�ʹ��:0-��ʹ��;255-�غ�բʹ��
	int PHaveV_Flag;//#�غ�բ����ѹ��־:0-�����Ƿ���ѹ;255-����ѹ
	int PSwitchStatus; //#�п���λ��:0-���п���λ��;255-�п���λ��,ʵ�ʾ������Ƿ��ڷ�λ
	CString Line_Name;//��·����

	int ZXCHZTime;//�����غ�բʱ��
	int FZXCHZTime;//��֧���غ�բʱ��

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
	CString SXJZSSelct[SWITCH_KIND];//�ж����ֿ��أ����ж��ٸ�Prot_Select
} SXJZSCfgStru;



/*****���Ź� 2015.7.15 lizhen *************/

#define KMG_SWITCH_KIND 20 //����������������� ������20����ͬ�Ŀ���
#define KMG_SELECT		20 //ÿ������������20������
//���˼���ʽ ��ȡprot_select��������ݵ�����


typedef struct {
	CString Version;	//�汾��
	CString CreateTime;	//����ʱ��
//	int ProtLineNum;		//��·��

	int Prot_YXEnable; // #������ң��ʹ��
	int Prot_MsgEnable;// #������Ϣ�ϱ�ʹ��
	int Byd_SOEEnable;// #Խ�޸澯SOEʹ��
	int Flt_YXEnable; //#���ϼ������ϱ�ʹ��
	int Flt_RepEnable; //#���ϱ����ϱ�ʹ��
//	int PLC_Enable;//PLCͶ��

	int Flt_RcwEnable;//����¼��ʹ��
	int V_ConnectMode;//��ѹ���߷�ʽ
	int FixActTime;//�������ж���ʱ��

	int ProtNumPerLine;			//ÿ����·�ı�������

} KMGNormalStru;


typedef struct {

	int Switch_Type;       //��������(0-��·��, 1-���ɿ���)
	int SBO_Num;		//��·SBO��
	int Switch_Num;	// #��·���غ�

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
	CString KMGSelct[SWITCH_KIND];//�ж����ֿ��أ����ж��ٸ�Prot_Select
} KMGCfgStru;




/*****����Һ�� 2016.3.14 lizhen *************/


typedef struct {
	int ProtLineNum;
	CString DeviceName;
} SXYJNormalStru;


typedef struct {

	CString LineName; //��·��
	int YxNum;		//ң����
	int YcNum;	// ң����

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

/*****�ֶι� 2017.4.26  *************/

#define FDG_MODE_KIND 20 //����������������� ������20����ͬ�Ŀ���
#define FDG_SELECT		20 //ÿ������������20������
//���˼���ʽ ��ȡprot_select��������ݵ�����


typedef struct {
	CString Version;	//�汾��
	CString CreateTime;	//����ʱ��
//	int ProtLineNum;		//��·��

	int Prot_YXEnable; // #������ң��ʹ��
	int Prot_MsgEnable;// #������Ϣ�ϱ�ʹ��
	int Byd_SOEEnable;// #Խ�޸澯SOEʹ��
	int Flt_YXEnable; //#���ϼ������ϱ�ʹ��
	int Flt_RepEnable; //#���ϱ����ϱ�ʹ��
//	int PLC_Enable;//PLCͶ��

	int Flt_RcwEnable;//����¼��ʹ��
	int V_ConnectMode;//��ѹ���߷�ʽ
	int FixActTime;//�������ж���ʱ��

	int ProtNumPerLine;			//��·�ı�������
	int VTimePerLine;			//��ѹʱ���͹�������
	int VITimePerLine;			//��ѹ����ʱ���͹�������
	int SelfAdaptionPerLine;	//����Ӧ�ۺ��͹�������
	int LLSwitchPerLine;		//�����բ��������

	int DeviceMode;				//
	int SelectType;
	int AdpSmlType;
	int SwitchType;
} FDGNormalStru;

typedef struct {

	int Switch_Type;       //��������(0-��·��, 1-���ɿ���)
//	int SBO_Num;		//��·SBO��
//	int Switch_Num;	// #��·���غ�

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
