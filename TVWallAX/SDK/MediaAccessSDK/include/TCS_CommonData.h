#ifndef TCS_COMMONDATA_H
#define TCS_COMMONDATA_H

#pragma pack(push,1) 

#define MAX_STRINGLEN 64	//最大相机ID长度
#define MAX_PLATFOMRCNT 64	//最大支持平台个数

//底层连接类型
typedef enum _SocketType
{
	TCS_UDP = 0,
	TCS_TCP
}SocketType;

//平台类型
typedef int PlatformId;

//平台信息结构
typedef struct _PlatformInfo
{
	PlatformId id;
	char description[128];
}PlatformInfo;

//平台信息集合
typedef struct _PlatformInfoSet
{
	unsigned cnt;							//平台个数
	PlatformInfo infos[MAX_PLATFOMRCNT];	//平台信息数组
}PlatformInfoSet;

//播放顺序
typedef enum _PlaySequence
{
	SequencePlay = 0,	//顺序播放
	RewindPlay,			//倒序播放
}PlaySequence;

//码流类型
typedef enum _StreamType
{
	MainStream = 0, 
	SubStream
}StreamType;

//PTZ移动控制类型
typedef enum _TCS_PTZ_
{
	PTZCTL_UP =0,				/** 上 */
	PTZCTL_DOWN ,				/** 下 */
	PTZCTL_RIGHT ,				/** 右 */
	PTZCTL_LEFT ,				/** 左*/
	PTZCTL_IRIS_OPEN ,			/** 光圈开 */
	PTZCTL_IRIS_CLOSE ,			/** 光圈关*/
	PTZCTL_ZOOM_WIDE ,			/** 拉远*/
	PTZCTL_ZOOM_TELE ,			/** 拉近*/
	PTZCTL_FOCUS_NEAR ,			/** 近焦*/
	PTZCTL_FOCUS_FAR ,			/** 远焦*/
	PTZCTL_STOP ,				/** 停止*/
}TCS_PTZMoveOp;

//播放速度定义
typedef enum _PLAY_SPEED_
{
	SPEED_1X = 0,
	FAST_2X, 
	FAST_4X, 
	FAST_8X, 
	FAST_16X, 
	SLOW_2X, 
	SLOW_4X, 
	SLOW_8X, 
	SLOW_16X,
}PLAY_SPEED;

//连接回调函数数据类型定义
typedef enum _ConnectionNotifyType
{
	STATE_DISCONNECT = 0,
} ConnectionNotifyType;

//连接回调函数数据
typedef struct _ConnectionNotify
{
	ConnectionNotifyType type;
} ConnectionNotify;

//连接回调函数定义
typedef void(*CONNECTION_CALLBACK)(int connectionId, ConnectionNotify data, void* pUserData);

//连接回调结构
typedef struct _ConnectionCallback
{
	CONNECTION_CALLBACK m_func;
	void* pUserData;
} ConnectionCallback;

//登陆信息
typedef struct _LoginInfo
{
	const char* ip;
	unsigned short port;
	const char* username;
	const char* password; 
	SocketType st;
	ConnectionCallback callback;
}LOGININFO, *PLOGININFO;

//查询录像的结果结构(按分钟数)
#define MAX_QUERY_MINITES 1440
typedef struct _QUERY_RECORD_RESULT
{
	unsigned int nNum;					/*分钟数，(the length of records)*/
	char records[MAX_QUERY_MINITES];	/*每个字节表示一分钟，0表示没有视频，1表示有视频*/
}QUERY_RECORD_RESULT;

//媒体流数据包
typedef struct _MediaData
{
	int errorcode;		//0 正常，1 异常断流
	int imageWidth;		//图像宽
	int imageHeight;	//图像高
	int yStride;		//跨度(同linesize)
	void* yData;		//Y分量数据
	void* uData;		//U分量数据
	void* vData;		//V分量数据
	__int64 timestamp;	//时间戳(毫秒)
}MediaData;

//相机信息
typedef struct _CameraInfo
{
	char cameraId[MAX_STRINGLEN];	//相机标识
	char name[MAX_STRINGLEN];		//相机名称
	char ip[MAX_STRINGLEN];			//IP地址
	char firm[MAX_STRINGLEN];		//厂商
	char model[MAX_STRINGLEN];		//型号
	unsigned char enabled;			//是否可用 0否 1是 其它未知
	unsigned char bPTZ;				//能否进行PTZ控制 0否 1是 其它未知
}CameraInfo;


//媒体流回调函数定义
typedef void(*MEDIADATA_CALLBACK)(int sessionId, MediaData* data, void* pUserData);

//错误码
typedef enum _TCSErrorCode
{
	OK = 0,						//成功
	SystemError,				//系统返回的错误
	InvalidConnection,			//无效连接
	ConfigFileError,			//配置文件错误
	InvalidSession,				//无效session
	StatusError,				//状态错误
	ParamError,					//参数错误
	PlatformNotSupport = 101,	//平台不支持
	InvalidCamera,				//无效Camera
	ExecFaild,					//执行失败
	FilePathError,				//路径错误
	PlatformError				//平台反馈的错误
}TCSErrorCode;

enum TCSResult
{
	Success = 0,
	Failed = -1
};

//错误信息
typedef struct _TrError_
{
	TCSErrorCode error_code;	//错误码
	const char* error_msg;		//错误描述
}TrError;


#pragma pack(pop)

#endif