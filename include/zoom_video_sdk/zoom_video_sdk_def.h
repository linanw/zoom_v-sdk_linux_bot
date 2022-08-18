/*!
* \file zoom_video_sdk_def.h
* \brief Zoom Video SDK Common Definition File.
*
*/

#ifndef _ZOOM_VIDEO_SDK_DEF_H_
#define _ZOOM_VIDEO_SDK_DEF_H_
#include <iostream>
#include "zoom_video_sdk_platform.h"
#include "zoom_sdk_raw_data_def.h"

#define ZOOM_VIDEO_SDK_NAMESPACE ZOOMVIDEOSDK
#define BEGIN_ZOOM_VIDEO_SDK_NAMESPACE namespace ZOOM_VIDEO_SDK_NAMESPACE {
#define END_ZOOM_VIDEO_SDK_NAMESPACE };
#define USING_ZOOM_VIDEO_SDK_NAMESPACE using namespace ZOOM_VIDEO_SDK_NAMESPACE;

BEGIN_ZOOM_VIDEO_SDK_NAMESPACE
typedef enum
{ 
	ZoomVideoSDKErrors_Success = 0,///<Success.
	ZoomVideoSDKErrors_Wrong_Usage,
	ZoomVideoSDKErrors_Internal_Error,
	ZoomVideoSDKErrors_Uninitialize,
	ZoomVideoSDKErrors_Memory_Error,
	ZoomVideoSDKErrors_Load_Module_Error,
	ZoomVideoSDKErrors_UnLoad_Module_Error,
	ZoomVideoSDKErrors_Invalid_Parameter,
	ZoomVideoSDKErrors_Call_Too_Frequently,
	ZoomVideoSDKErrors_No_Impl,
	ZoomVideoSDKErrors_Dont_Support_Feature,
	ZoomVideoSDKErrors_Unknown,
	ZoomVideoSDKErrors_Auth_Error = 1001,
	ZoomVideoSDKErrors_Auth_Empty_Key_or_Secret,
	ZoomVideoSDKErrors_Auth_Wrong_Key_or_Secret,
	ZoomVideoSDKErrors_Auth_DoesNot_Support_SDK,
	ZoomVideoSDKErrors_Auth_Disable_SDK,
	ZoomVideoSDKErrors_JoinSession_NoSessionName = 1500,
	ZoomVideoSDKErrors_JoinSession_NoSessionToken,
	ZoomVideoSDKErrors_JoinSession_NoUserName,
	ZoomVideoSDKErrors_JoinSession_Invalid_SessionName,
	ZoomVideoSDKErrors_JoinSession_Invalid_Password,
	ZoomVideoSDKErrors_JoinSession_Invalid_SessionToken,
	ZoomVideoSDKErrors_JoinSession_SessionName_TooLong,
	ZoomVideoSDKErrors_JoinSession_Token_MismatchedSessionName,
	ZoomVideoSDKErrors_JoinSession_Token_NoSessionName,
	ZoomVideoSDKErrors_JoinSession_Token_RoleType_EmptyOrWrong,
	ZoomVideoSDKErrors_JoinSession_Token_UserIdentity_TooLong,
	ZoomVideoSDKErrors_SessionModule_Not_Found = 2001,
	ZoomVideoSDKErrors_SessionService_Invaild,
	ZoomVideoSDKErrors_Session_Join_Failed,
	ZoomVideoSDKErrors_Session_No_Rights,
	ZoomVideoSDKErrors_Session_Already_In_Progress,
	ZoomVideoSDKErrors_Session_Dont_Support_SessionType,
	ZoomVideoSDKErrors_Session_Reconnecting,
	ZoomVideoSDKErrors_Session_Disconnecting,
	ZoomVideoSDKErrors_Session_Not_Started,
	ZoomVideoSDKErrors_Session_Need_Password,
	ZoomVideoSDKErrors_Session_Password_Wrong,
	ZoomVideoSDKErrors_Session_Remote_DB_Error,
	ZoomVideoSDKErrors_Session_Invalid_Param,
	ZoomVideoSDKErrors_Session_Audio_Error = 3000,
	ZoomVideoSDKErrors_Session_Audio_No_Microphone,
	ZoomVideoSDKErrors_Session_Audio_No_Speaker,
	ZoomVideoSDKErrors_Session_Video_Error = 4000,
	ZoomVideoSDKErrors_Session_Video_Device_Error,
	ZoomVideoSDKErrors_Session_Live_Stream_Error = 5000,
	ZoomVideoSDKErrors_Session_Phone_Error = 5500,

	ZoomVideoSDKErrors_RAWDATA_MALLOC_FAILED = 6001,
	ZoomVideoSDKErrors_RAWDATA_NOT_IN_Session,
	ZoomVideoSDKErrors_RAWDATA_NO_LICENSE,
	ZoomVideoSDKErrors_RAWDATA_VIDEO_MODULE_NOT_READY,
	ZoomVideoSDKErrors_RAWDATA_VIDEO_MODULE_ERROR,
	ZoomVideoSDKErrors_RAWDATA_VIDEO_DEVICE_ERROR,
	ZoomVideoSDKErrors_RAWDATA_NO_VIDEO_DATA,
	ZoomVideoSDKErrors_RAWDATA_SHARE_MODULE_NOT_READY,
	ZoomVideoSDKErrors_RAWDATA_SHARE_MODULE_ERROR,
	ZoomVideoSDKErrors_RAWDATA_NO_SHARE_DATA,
	ZoomVideoSDKErrors_RAWDATA_AUDIO_MODULE_NOT_READY,
	ZoomVideoSDKErrors_RAWDATA_AUDIO_MODULE_ERROR,
	ZoomVideoSDKErrors_RAWDATA_NO_AUDIO_DATA,
	ZoomVideoSDKErrors_RAWDATA_PREPROCESS_RAWDATA_ERROR,
	ZoomVideoSDKErrors_RAWDATA_NO_DEVICE_RUNNING,
	ZoomVideoSDKErrors_RAWDATA_INIT_DEVICE,
	ZoomVideoSDKErrors_RAWDATA_VIRTUAL_DEVICE,
	ZoomVideoSDKErrors_RAWDATA_CANNOT_CHANGE_VIRTUAL_DEVICE_IN_PREVIEW,
	ZoomVideoSDKErrors_RAWDATA_INTERNAL_ERROR,
	ZoomVideoSDKErrors_RAWDATA_SEND_TOO_MUCH_DATA_IN_SINGLE_TIME,
	ZoomVideoSDKErrors_RAWDATA_SEND_TOO_FREQUENTLY,
	ZoomVideoSDKErrors_RAWDATA_VIRTUAL_MIC_IS_TERMINATE,

	ZoomVideoSDKErrors_Session_Share_Error = 7001,
	ZoomVideoSDKErrors_Session_Share_Module_Not_Ready,
	ZoomVideoSDKErrors_Session_Share_You_Are_Not_Sharing,
	ZoomVideoSDKErrors_Session_Share_Type_Is_Not_Support,
	ZoomVideoSDKErrors_Session_Share_Internal_Error,
	ZoomVideoSDKErrors_Dont_Support_Multi_Stream_Video_User,
	ZoomVideoSDKErrors_Fail_Assign_User_Privilege,
	ZoomVideoSDKErrors_No_Recording_In_Process,

}ZoomVideoSDKErrors;

typedef enum 
{
	ZoomVideoSDKShareStatus_None,
	ZoomVideoSDKShareStatus_Start,
	ZoomVideoSDKShareStatus_Pause,
	ZoomVideoSDKShareStatus_Resume,
	ZoomVideoSDKShareStatus_Stop,
}ZoomVideoSDKShareStatus;

typedef enum
{
	ZoomVideoSDKShareType_None,
	ZoomVideoSDKShareType_Normal,//application or desktop share
	ZoomVideoSDKShareType_PureAudio, //pure computer audio share
}ZoomVideoSDKShareType;

typedef enum
{
	ZoomVideoSDKLiveStreamStatus_None,
	ZoomVideoSDKLiveStreamStatus_InProgress,
	ZoomVideoSDKLiveStreamStatus_Connecting,
	ZoomVideoSDKLiveStreamStatus_FailedTimeout,
	ZoomVideoSDKLiveStreamStatus_StartFailed,
	ZoomVideoSDKLiveStreamStatus_Ended,
}ZoomVideoSDKLiveStreamStatus;

typedef enum
{
	ZoomVideoSDKRawDataMemoryModeStack = 0,
	ZoomVideoSDKRawDataMemoryModeHeap,
}ZoomVideoSDKRawDataMemoryMode;

typedef enum
{
	RAW_DATA_TYPE_VIDEO = 0,
	RAW_DATA_TYPE_SHARE,
}ZoomVideoSDKRawDataType;


typedef enum
{
	ZoomVideoSDKCameraControlRequestType_RequestControl = 0,
	ZoomVideoSDKCameraControlRequestType_GiveUpControl
	
}ZoomVideoSDKCameraControlRequestType;

/*! \enum RecordingStatus
	\brief  An enum representing the status of the recording status.
*/
enum RecordingStatus
{
	/// \brief The recording has started or resumed.
	Recording_Start,
	/// \brief The recording has stopped.
	Recording_Stop,
	/// \brief Recording is unsuccessful due to not having enough storage space.
	///	Please try to:
	///		Free up space
	///		Purchase more space
	Recording_DiskFull,
	/// \brief The recording has paused.
	Recording_Pause,
};

typedef	enum
{
	ZoomVideoSDKMic_CanTest = 0,///<Test the mic via TestMicStartRecording. It is useless to call TestMicStopTesting/TestMicPlayRecording in this status.
	ZoomVideoSDKMic_Recording,///<Test the mic via TestMicStopTesting/TestMicPlayRecording. It is useless to call TestMicStartRecording in this status.
	ZoomVideoSDKMic_CanPlay,///<Test the mic via TestMicStopTesting/TestMicPlayRecording. It is useless call TestMicStartRecording in this status.
}ZoomVideoSDK_TESTMIC_STATUS;

/*! \struct ZoomVideoSDKInitParams
	\brief Initialization parameters.
*/
struct ZoomVideoSDKExtendParams
{
	const zchar_t* speakerTestFilePath;  //Only support mp3 format,The size cannot exceed 1M

	ZoomVideoSDKExtendParams()
	{
		speakerTestFilePath = NULL;
	}
};

struct ZoomVideoSDKInitParams
{
	const zchar_t* domain; /// \brief Web domain, required.
	const zchar_t* logFilePrefix; /// \brief Prefix for log file name, optional.
	bool  enableLog; /// \brief Enable log or not, optional.
	bool  enableIndirectRawdata; /// \brief Enable indirect rawdata or not, optional.
	ZoomVideoSDKRawDataMemoryMode audioRawDataMemoryMode; /// \brief Store audio raw data buffer in heap or stack, optional.
	ZoomVideoSDKRawDataMemoryMode videoRawDataMemoryMode; /// \brief Store video raw data buffer in heap or stack, optional.
	ZoomVideoSDKRawDataMemoryMode shareRawDataMemoryMode; /// \brief Store share raw data buffer in heap or stack, optional.

	ZoomVideoSDKExtendParams extendParam;
	ZoomVideoSDKInitParams()
	{
		domain = NULL;
		logFilePrefix = NULL;
		enableLog = false;
#if (defined __IOS__) || (defined CMM_MAC)
		enableIndirectRawdata = true;
#else
		enableIndirectRawdata = false;
#endif
		audioRawDataMemoryMode = ZoomVideoSDKRawDataMemoryModeStack;
		videoRawDataMemoryMode = ZoomVideoSDKRawDataMemoryModeStack;
		shareRawDataMemoryMode = ZoomVideoSDKRawDataMemoryModeStack;
	}
};

/*! \struct ZoomVideoSDKVideoOption
	\brief Video option used by ZoomVideoSDKSessionContext.
*/
struct ZoomVideoSDKVideoOption 
{
    bool localVideoOn; /// \brief Turn local video on or off.
	ZoomVideoSDKVideoOption()
	{
		localVideoOn = true;
	}
};
/*! \struct ZoomVideoSDKAudioOption
	\brief Audio options used by ZoomVideoSDKSessionContext.
*/
struct ZoomVideoSDKAudioOption 
{
    bool connect; /// \brief Connect local audio or not.
    bool mute;    /// \brief Mute audio or not.

	ZoomVideoSDKAudioOption()
	{
		connect = true;
		mute = false;
	}
};

class IZoomVideoSDKVideoSourcePreProcessor;
class IZoomVideoSDKVideoSource;
class IZoomVideoSDKVirtualAudioMic;
class IZoomVideoSDKVirtualAudioSpeaker;

/*! \struct ZoomVideoSDKSessionContext
	\brief Session context information.
*/
struct ZoomVideoSDKSessionContext
{
    const zchar_t* sessionName;		///<Session name, required.
    const zchar_t* sessionPassword; ///<Session password, optional.
    const zchar_t* userName;        ///<Display name in session, required.
    const zchar_t* token;			///<JWT token to join session, required.
    ZoomVideoSDKVideoOption videoOption; ///<Video option, optional.
    ZoomVideoSDKAudioOption audioOption; ///<Audio option, optional.
	IZoomVideoSDKVideoSourcePreProcessor* preProcessor; ///<Camera data preprocessor object pointer, optional.
	IZoomVideoSDKVideoSource* externalVideoSource; ///<Virtual camera object pointer, optional.
	IZoomVideoSDKVirtualAudioMic* virtualAudioMic; ///<Virtual mic object pointer, optional.
	IZoomVideoSDKVirtualAudioSpeaker* virtualAudioSpeaker; ///<Virtual speaker object pointer, optional.
	unsigned int sessionIdleTimeoutMins; ///<The amount of time in minutes after which an idle session will end. If the value is 0, the session will stay alive indefinitely.

	ZoomVideoSDKSessionContext()
	{
		sessionName = NULL;
		sessionPassword = NULL;
		userName = NULL;
		token = NULL;
		preProcessor = NULL;
		externalVideoSource = NULL;
		virtualAudioMic = NULL;
		virtualAudioSpeaker = NULL;
		sessionIdleTimeoutMins = 40;
	}
};
END_ZOOM_VIDEO_SDK_NAMESPACE
#endif