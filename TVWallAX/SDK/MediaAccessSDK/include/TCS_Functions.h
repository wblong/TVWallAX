#ifndef _TCS_FUNCTIONS_H_
#define _TCS_FUNCTIONS_H_

#ifdef __cplusplus
#define CEXTERN extern "C"
#else
#define CEXTERN
#endif

#ifdef  TERRAVISIONSDK_EXPORTS
#define DLLEXPORT CEXTERN __declspec(dllexport)
#else
#define DLLEXPORT CEXTERN __declspec(dllimport)
#endif

#define STDCALL __stdcall


#include "TCS_CommonData.h"

/**
* @brief 初始化DLL
* @author xty ligd
* @date  2017/3/20
* @param
* @return 成功 TCSResult::Success
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_Init();

/**
* @brief 退出DLL
* @author xty ligd
* @date  2017/3/20
* @param
* @return 成功 TCSResult::Success
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_UnInit();

/**
* @brief 登录服务器
* @author xty ligd
* @date  2017/3/20
* @param LOGININFO:登陆信息
* @return 成功 连接ID
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_Login(PlatformId pt, LOGININFO* pInfo);

/**
* @brief 登出服务器
* @author xty ligd
* @date  2017/1/19
* @param coid : 连接ID
* @return 成功 TCSResult::Success
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_Logout(int connectId);

/**
* @brief
* @author xty ligd
* @date  2017/3/20
* @param minsNo: 分钟数
		 pMins: 结果数组[0/1...]
* @return 成功 TCSResult::Success
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention 结果数组是数字0 or 1
* @Modified
**/
DLLEXPORT int STDCALL TCS_RecordSearch(int connectId,
	const char* cameraId, __int64 beginTime, int minsNo, char* pMins);

/**
* @brief 开启一路实时视频
* @author xty ligd
* @date  2017/3/20
* @param
* @return 成功 SessionId
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_StartRealPlay(int connectId, const char* cameraId,
	StreamType streamType, MEDIADATA_CALLBACK func, void* pUserData);

/**
* @brief 关闭一路实时视频
* @author xty ligd
* @date  2017/3/20
* @param
* @return 成功 TCSResult::Success
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_StopRealPlay(int sessionId);

/**
* @brief 暂停一路实时视频
* @author ligd
* @date  2018/8/28
* @param
* @return 成功 TCSResult::Success
          失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_PauseRealPlay(int sessionId);

/**
* @brief 继承一路实时视频
* @author ligd
* @date  2018/8/28
* @param
* @return 成功 TCSResult::Success
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_ContinueRealPlay(int sessionId);

/**
* @brief 录像回放
* @author xty ligd
* @date  2017/3/20
* @param
* @return 成功 SessionId
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_StartPlayback(int connectId, const char* cameraId,
	StreamType streamType, __int64 beginTime, __int64 endTime,
	MEDIADATA_CALLBACK func, void* pUserData);

/**
* @brief 停止录像回放
* @author xty ligd
* @date  2017/3/20
* @param
* @return 成功 TCSResult::Success
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_StopPlayback(int sessionId);

/**
* @brief 暂停录像回放
* @author xty ligd
* @date  2017/3/20
* @param
* @return 成功 TCSResult::Success
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_PausePlay(int sessionId);

/**
* @brief 继续录像回放
* @author xty ligd
* @date  2017/3/20
* @param
* @return 成功 TCSResult::Success
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_ContiuePlay(int sessionId);

/**
* @brief 设置录像播放速度
* @author xty ligd
* @date  2017/3/20
* @param
* @return 成功 TCSResult::Success
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_SetPlaySpeed(int sessionId, PLAY_SPEED speed);

/**
* @brief 设置录像播放顺序
* @author xty ligd
* @date  2017/3/20
* @param
* @return 成功 TCSResult::Success
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_SetPlaySequence(int sessionId, PlaySequence playType);

/**
* @brief 录像播放时跳转
* @author xty ligd
* @date  2017/3/20
* @param
* @return 成功 TCSResult::Success
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_SkipPlay(int sessionId, __int64 timestamp);

/**
* @brief  开始录像下载
* @author xty ligd
* @date  2017/3/20
* @param pathName : 文件全路径
* @return 成功 SessionId
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_StartDownload(int connectId, const char* cameraId,
	const char* pathName, __int64 begTime, __int64 endTime,
	StreamType streamType);

/**
* @brief 停止录像下载
* @author xty ligd
* @date  2017/3/20
* @param
* @return 成功 TCSResult::Success
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_StopDownload(int sessionId);

/**
* @brief  获取录像下载进度
* @author xty ligd
* @date  2017/3/20
* @param
* @return 成功 下载进度（0-100）
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_GetDownloadProgress(int sessionId);

/**
* @brief  开始本地录像
* @author xty ligd
* @date  2017/3/20
* @param pathName : 文件全路径
* @return 成功 TCSResult::Success
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_StartLocalRecord(int sessionId, const char* pathName);

/**
* @brief  停止本地录像
* @author xty ligd
* @date  2017/3/20
* @param
* @return 成功 TCSResult::Success
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_StopLocalRecord(int sessionId);

/**
* @brief 云台移动控制
* @author xty ligd
* @date  2017/3/20
* @param
	connectId	: 连接ID，在TCS_Login的返回值
	cameraId	: 相机ID
	op			: PTZ操作, 见TCS_PTZMoveOp
	speed		: 速度值（1-10）
* @return 成功 TCSResult::Success
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_PTZControl(int connectId, const char* cameraId, TCS_PTZMoveOp op, int speed);

/**
* @brief 云台预置位设置
* @author xty ligd
* @date  2017/3/20
* @param
	connectId	: 连接ID，在TCS_Login的返回值
	cameraId	: 相机ID
	id			: 预置位ID
	name		: 预置位的名称（不要超过20字符）
* @return 成功 TCSResult::Success
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_PresetSet(int connectId, const char* cameraId, int id, const char* name);

/**
* @brief 云台预置位触发
* @author xty ligd
* @date  2017/1/18
* @param
	connectId	: 连接ID，在TCS_Login的返回值
	cameraId	: 相机ID
	id			: 预置位ID
* @return 成功 TCSResult::Success
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_PresetCall(int connectId, const char* cameraId, int id);

/**
* @brief 云台预置位删除
* @author xty ligd
* @date  2017/1/18
* @param
	connectId	: 连接ID，在TCS_Login的返回值
	cameraId	: 相机ID
	id			: 预置位ID
* @return 成功 TCSResult::Success
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_PresetDel(int connectId, const char* cameraId, int id);

/**
* @brief 获取设备列表的数量
* @author xty
* @date  2017/3/3
* @param
* @return 成功 相机数
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_GetCameraAmount(int connectId);

/**
* @brief 获取设备列表
* @author xty ligd
* @date  2017/1/19
* @param
	connectId : 连接ID
	CameraInfo : 内存区
	cameraAmount : 内存区长度
* @return 成功 TCSResult::Success
		  失败 TCSResult::Failed
		  详见TCS_GetLastError
* @attention
* @Modified
**/
DLLEXPORT int STDCALL TCS_GetCameraList(int connectId, CameraInfo* pCameras, int cameraAmount);

/**
* @brief 获取支持的平台信息
* @author xty ligd
* @date  2017/1/16
* @param
* @return 参考PlatformInfoSet定义
* @attention
* @Modified
**/
DLLEXPORT PlatformInfoSet STDCALL TCS_GetSupportedPlatform();

/**
* @brief 获取错误码
* @author xty ligd
* @date  2017/1/16
* @param
* @return 参考TCSErrorCode定义
* @attention
* @Modified
**/
DLLEXPORT TCSErrorCode STDCALL TCS_GetLastError();

#endif