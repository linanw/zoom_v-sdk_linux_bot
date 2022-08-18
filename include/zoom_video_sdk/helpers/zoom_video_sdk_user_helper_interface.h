/*!
* \file zoom_video_sdk_user_helper_interface.h
* \brief user helper
*
*/

#ifndef _ZOOM_VIDEO_SDK_USER_HELPER_INTERFACE_H_
#define _ZOOM_VIDEO_SDK_USER_HELPER_INTERFACE_H_
#include "zoom_video_sdk_def.h"
#include "zoom_video_sdk_vector_interface.h"

BEGIN_ZOOM_VIDEO_SDK_NAMESPACE
/*! \struct ZoomVideoSDKVideoStatus
	\brief Video status information.
*/
typedef struct
{
	bool isHasVideoDevice;
	bool isOn;
}ZoomVideoSDKVideoStatus;

/*! \struct ZoomVideoSDKAudioType
	\brief Audio type information.
*/
typedef enum {
	ZoomVideoSDKAudioType_VOIP,
	ZoomVideoSDKAudioType_TELEPHONY,
	ZoomVideoSDKAudioType_None,
}ZoomVideoSDKAudioType;

/*! \struct ZoomVideoSDKAudioStatus
	\brief Audio status information.
*/
typedef struct
{
	ZoomVideoSDKAudioType audioType;
	bool isMuted;
	bool isTalking;
}ZoomVideoSDKAudioStatus;

/*! \struct ZoomVideoSDKVideoStatisticInfo
	\brief Video statistic information.
*/
typedef struct
{
	int width;
	int height;
	int fps;
	int bpf;
}ZoomVideoSDKVideoStatisticInfo;

/*! \struct ZoomVideoSDKShareStatisticInfo
	\brief Share statistic information.
*/
typedef struct
{
	int width;
	int height;
	int fps;
	int bpf;
}ZoomVideoSDKShareStatisticInfo;

typedef enum
{
	ZoomVideoSDKResolution_90P = 0,
	ZoomVideoSDKResolution_180P,
	ZoomVideoSDKResolution_360P,
	ZoomVideoSDKResolution_720P,
#if (defined _WIN32) || (defined __MACOS__) || (defined __LINUX__)
	ZoomVideoSDKResolution_1080P,
#endif
	ZoomVideoSDKResolution_NoUse = 100,
}ZoomVideoSDKResolution;

typedef enum 
{
	RawData_On,
	RawData_Off,
}RawDataStatus;

/// \brief Video/share raw data sink interface.
///
class IZoomVideoSDKRawDataPipeDelegate
{
public:
	/// \brief Call when subscribed data received.
	/// \param data_, data object.
	virtual void onRawDataFrameReceived(YUVRawDataI420* data_) = 0;

	/// \brief Call when subscribed data status changed.
	/// \param status, current data status.
	virtual void onRawDataStatusChanged(RawDataStatus status) = 0;

	virtual ~IZoomVideoSDKRawDataPipeDelegate() {};
};

/// \brief Video/share raw data pipe interface.
///
class IZoomVideoSDKRawDataPipe
{
public:
	/// \brief Subscribe video/share.
	/// \param resolution, subscribe size.
	/// \param listener, callback sink object.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors subscribe(ZoomVideoSDKResolution resolution, IZoomVideoSDKRawDataPipeDelegate* listener) = 0;
	
	/// \brief Unsubscribe video/share.
	/// \param listener, the callback sink object.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors unSubscribe(IZoomVideoSDKRawDataPipeDelegate* listener) = 0;

	/// \brief Subscribe to the computer audio shared by other user.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	/// \remark Please call this interface after the callback onUserShareStatusChanged is received and the share type is ZoomVideoSDKShareType_PureAudio.
	virtual ZoomVideoSDKErrors subscribeToSharedComputerAudio() = 0;

	/// \brief Unsubscribe to the computer audio shared by other user.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors unsubscribeToSharedComputerAudio() = 0;

	/// \brief Get raw data data type.
	/// \return raw data type.
	virtual ZoomVideoSDKRawDataType getRawdataType() = 0;

	/// \brief Get video status.
	/// \return Video status of the user object.
	virtual ZoomVideoSDKVideoStatus getVideoStatus() = 0;

	/// \brief Get share status.
	/// \return Share status of the user object.
	virtual ZoomVideoSDKShareStatus getShareStatus() = 0;

	/// \brief Get share type.
	/// \return Share type of the user object.
	virtual ZoomVideoSDKShareType getShareType() = 0;
};


/// \brief Camera control interface.
///
class IZoomVideoSDKCameraControlRequestHandler
{
public:
	virtual ~IZoomVideoSDKCameraControlRequestHandler() {}

	/// \brief Approve the remote camera control request.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	virtual ZoomVideoSDKErrors approve() = 0;

	/// \brief Decline the remote camera control request.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	virtual ZoomVideoSDKErrors decline() = 0;
};

class IZoomVideoSDKRemoteCameraControlHelper
{
public:
	virtual ~IZoomVideoSDKRemoteCameraControlHelper() {}

	/// \brief Request to control remote camera.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	virtual ZoomVideoSDKErrors requestControlRemoteCamera() = 0;

	/// \brief Give up control of the remote camera.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	virtual ZoomVideoSDKErrors giveUpControlRemoteCamera() = 0;

	/// \brief Turn the camera to the left.
	/// \param range: Rotation range,  10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	virtual ZoomVideoSDKErrors turnLeft(unsigned int range = 50) = 0;

	/// \brief Turn the camera to the right.
	/// \param range: Rotation range,  10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	virtual ZoomVideoSDKErrors turnRight(unsigned int range = 50) = 0;

	/// \brief Turn the camera up.
	/// \param range: Rotation range,  10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	virtual ZoomVideoSDKErrors turnUp(unsigned int range = 50) = 0;

	/// \brief Turn the camera down.
	/// \param range: Rotation range,  10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	virtual ZoomVideoSDKErrors turnDown(unsigned int range = 50) = 0;

	/// \brief Zoom the camera in.
	/// \param range: Zoom range,  10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	virtual ZoomVideoSDKErrors zoomIn(unsigned int range = 50) = 0;

	/// \brief Zoom the camera out.
	/// \param range: Zoom range,  10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	virtual ZoomVideoSDKErrors zoomOut(unsigned int range = 50) = 0;
};

/**
 * @brief Enumerations of the type for live transcription status.
 */
typedef enum
{
	ZoomVideoSDKLiveTranscription_Status_Stop = 0,//not start
	ZoomVideoSDKLiveTranscription_Status_Start = 1,  //start	
}ZoomVideoSDKLiveTranscriptionStatus;

/**
 * @brief Enumerations of the type for live transcription operation type.
 */
typedef enum
{
	ZoomVideoSDKLiveTranscription_OperationType_None = 0,
	ZoomVideoSDKLiveTranscription_OperationType_Add,
	ZoomVideoSDKLiveTranscription_OperationType_Update,
	ZoomVideoSDKLiveTranscription_OperationType_Delete,
	ZoomVideoSDKLiveTranscription_OperationType_Complete,
	ZoomVideoSDKLiveTranscription_OperationType_NotSupported,
}ZoomVideoSDKLiveTranscriptionOperationType;

/// \brief live transcription language interface.
///
class ILiveTranscriptionLanguage
{
public:
	/// \brief Get id of the language.
	/// \return The id of the language.
	virtual int getLTTLanguageID() = 0;

	/// \brief Get name of the language.
	/// \return The name of the language.
	virtual const zchar_t* getLTTLanguageName() = 0;

	virtual ~ILiveTranscriptionLanguage() {};
};

/// \brief live transcription helper interface.
class IZoomVideoSDKLiveTranscriptionHelper
{
public:
	/// Query if the user can start live transcription.
	virtual bool canStartLiveTranscription() = 0;

	/// \brief Get the current live transcription status.
	//  \return type: the current live transcription status. For more details, see \link ZoomVideoSDKLiveTranscriptionStatus \endlink.
	virtual ZoomVideoSDKErrors getLiveTranscriptionStatus(ZoomVideoSDKLiveTranscriptionStatus& status) = 0;

	/// \brief Start live transcription.
	/// \If the session allows multi-language transcription,all users can start live transcription.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	/// Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors startLiveTranscription() = 0;

	/// \brief Stop live transcription.
	/// \If the session allows multi-language transcription,all users can stop live transcription.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	/// Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors stopLiveTranscription() = 0;

	/// \brief Get the list of all available spoken languages in session.
	/// \return If the function succeeds, the return value is the list of the available spoken languages in a session.
	///Otherwise failed, the return value is NULL.	
	virtual IVideoSDKVector<ILiveTranscriptionLanguage*>* getAvailableSpokenLanguages() = 0;

	/// \brief Set the spoken language of the current user.
	/// \param languageID: The spoken language ID.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors setSpokenLanguage(int languageID) = 0;

	/// Get the spoken language of the current user.
	virtual ILiveTranscriptionLanguage* getSpokenLanguage() = 0;

	/// \brief Get the list of all available translation languages in a session.
	/// \return If the function succeeds, the return value is the list of all available translation languages in a session.
	///Otherwise failed, the return value is NULL.
	virtual IVideoSDKVector<ILiveTranscriptionLanguage*>* getAvailableTranslationLanguages() = 0;

	/// \brief Set the translation language of the current user.	
	/// \param languageID: The translation language ID.
	/// If the language id is set to -1, live translation will be disabled.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors setTranslationLanguage(int languageID) = 0;

	/// Get the translation language of the current user.
	virtual ILiveTranscriptionLanguage* getTranslationLanguage() = 0;
};

/// \brief User object interface.
///
class IZoomVideoSDKUser
{
public:
	virtual ~IZoomVideoSDKUser(){}
	
	/// \brief Get custom id.
	/// \return The Custom id of the user object.
	virtual const zchar_t* getCustomIdentity() = 0;

	/// \brief Get user name.
	/// \return The name of the user object.
	virtual const zchar_t* getUserName() = 0;

	/// \brief Get user id of the user.
	/// \return The user id of the user object.
	virtual const zchar_t* getUserID() = 0;

	/// \brief Get video status.
	/// \return Video status of the user object.
	/// this interface be marked as deprecated, then it will be instead by IZoomVideoSDKRawDataPipe.getVideoStatus()
	virtual ZoomVideoSDKVideoStatus getVideoStatus() = 0;

	/// \brief Get audio status.
	/// \return Audio status of the user object.
	virtual ZoomVideoSDKAudioStatus getAudioStatus() = 0;
	
	/// \brief Get share status.
	/// \return Share status of the user object.
	/// this interface be marked as deprecated, then it will be instead by IZoomVideoSDKRawDataPipe.getShareStatus()
	virtual ZoomVideoSDKShareStatus getShareStatus() = 0;
	
	/// \brief Determine if the user is session host.
	/// \return True if current user is host. Otherwise returns false.
	virtual bool isHost() = 0;

	/// \brief Determine if the user is session manager(coHost).
	/// \return True if current user is session manager(coHost). Otherwise returns false.
	virtual bool isManager() = 0;
	
	/// \brief Get video statistic information of the user.
	/// \return Statistic information.
	virtual ZoomVideoSDKVideoStatisticInfo getVideoStatisticInfo() = 0;

	/// \brief Get share statistic information of the user.
	/// \return Statistic information.
	virtual ZoomVideoSDKShareStatisticInfo getShareStatisticInfo() = 0;
	
	/// \brief Get video raw data pipe.
	/// \return Pipe object.
	virtual IZoomVideoSDKRawDataPipe* GetVideoPipe() = 0;

	/// \brief Get share raw data pipe.
	/// \return Pipe object.
	virtual IZoomVideoSDKRawDataPipe* GetSharePipe() = 0;

	/// \brief Get the helper class instance to access the remote camera control.
	/// \return If the function succeeds, the return value is the remote camera control helper object.
	///Otherwise returns NULL. For more details, see \link IZoomVideoSDKRemoteCameraControlHelper \endlink.
	virtual IZoomVideoSDKRemoteCameraControlHelper* getRemoteCameraControlHelper() = 0;

	/// \brief Get multi-camera data pipe list.
	/// \return the return value is the pipe list.
	virtual IVideoSDKVector<IZoomVideoSDKRawDataPipe*>* getMultiCameraStreamList() = 0;

	/// \brief Get live transcription helper object.
	/// \return If the function succeeds, the return value is the live transcription helper object. Otherwise returns NULL. For more details, see \link IZoomVideoSDKLiveTranscriptionHelper \endlink.
	virtual IZoomVideoSDKLiveTranscriptionHelper* getLiveTranscriptionHelper() = 0;
};

/// \brief User helper interface.
///
class IZoomVideoSDKUserHelper
{
public:
	/// \brief Change name of user object.
	/// \param name, the new name of the user object.
	/// \return True if success. Otherwise returns false.
	virtual bool changeName(const zchar_t* name, IZoomVideoSDKUser* pUser) = 0;

	/// \brief Make some user as session host.
	/// \param pUser, the user object.
	/// \return True if success. Otherwise returns false.
	virtual bool makeHost(IZoomVideoSDKUser* pUser) = 0;

	/// \brief Make some user as session manager(coHost).
	/// \param pUser, the user object.
	/// \return True if success. Otherwise returns false.
	virtual bool makeManager(IZoomVideoSDKUser* pUser) = 0;

	/// \brief Revoke some user's manager right.
	/// \param pUser, the user object.
	/// \return True if success. Otherwise returns false.
	virtual bool revokeManager(IZoomVideoSDKUser* pUser) = 0;

	/// \brief Remove some user from current session.
	/// \param pUser, the user object.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors removeUser(IZoomVideoSDKUser* pUser) = 0;
};
END_ZOOM_VIDEO_SDK_NAMESPACE
#endif