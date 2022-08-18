/*!
* \file zoom_video_sdk_session_info_interface.h
* \brief Zoom video sdk session info interface.
*
*/

#ifndef _ZOOM_VIDEO_SDK_SESSION_INFO_INTERFACE_H_
#define _ZOOM_VIDEO_SDK_SESSION_INFO_INTERFACE_H_
#include "zoom_video_sdk_def.h"
#include "zoom_video_sdk_vector_interface.h"
#include <string.h>
BEGIN_ZOOM_VIDEO_SDK_NAMESPACE
class IZoomVideoSDKUser;

/*! \struct _SessionAudioStatisticInfo
	\brief Session audio statistic information.
*/
typedef struct _SessionAudioStatisticInfo
{
	int   frequency; ///<Unit KHz
	int   latency;   ///<Unit ms
	int   Jitter;    ///<Unit ms
	float packetLossAvg; ///%
	float packetLossMax; ///%

	_SessionAudioStatisticInfo()
	{
		reset();
	}

	void reset() 
	{
		memset(this, 0, sizeof(_SessionAudioStatisticInfo));  //checked safe
	}
}ZoomVideoSDKSessionAudioStatisticInfo;

/*! \struct _SessionASVStatisticInfo
	\brief Session video/share statistic information.
*/
typedef struct _SessionASVStatisticInfo
{
	int	  frame_width;
	int   frame_height;
	int   fps;     ///Unit frames/second
	int   latency; ///Unit ms
	int   Jitter;  ///Unit ms
	float packetLossAvg; ///%
	float packetLossMax; ///%

	_SessionASVStatisticInfo()
	{
		reset();
	}

	void reset() 
	{
		frame_width = 0;
		frame_height = 0;
		fps = 0;
		latency = 0;
		Jitter = 0;
		packetLossAvg = 0.0;
		packetLossMax = 0.0;
	}
}ZoomVideoSDKSessionASVStatisticInfo;
/// \brief Session information interface.
///
class IZoomVideoSDKSession
{
public:
	/// \brief Get the session name.
	/// \return If the function succeeds, the return value is session name. Otherwise returns NULL.
	virtual const zchar_t* getSessionName() = 0;

	/// \brief Get the session password.
	/// \return If the function succeeds, the return value is session password. Otherwise returns NULL.
	virtual const zchar_t* getSessionPassword() = 0;

	/// \brief Get the session ID.
	/// \return If the function succeeds, the return value is session ID. Otherwise returns NULL.
	/// \remarks This interface is only valid for the host.
	virtual const zchar_t* getSessionID() = 0;

	/// \brief Get the session host name.
	/// \return If the function succeeds, the return value is session host name. Otherwise returns NULL.
	virtual const zchar_t* getSessionHostName() = 0;

	/// \brief Get the session host user object.
	/// \return If the function succeeds, the return value is session host user object. Otherwise returns NULL.
	virtual IZoomVideoSDKUser* getSessionHost() = 0;

	/// \brief Get all users list in the session except myself.
	/// \return If the function succeeds, the return value is session all user list object. Otherwise returns NULL.
	virtual IVideoSDKVector<IZoomVideoSDKUser*>* getRemoteUsers() = 0;
	
	/// \brief Get myself object.
	/// \return If the function succeeds, the return value is myself object. Otherwise returns NULL.
	virtual IZoomVideoSDKUser* getMyself() = 0;
	
	/// \brief Determine if a user object is valid.
	/// \param pUser is user object pointer.
	/// \return True if user object is valid. Otherwise returns false.
	virtual bool IsValidUser(IZoomVideoSDKUser* pUser) = 0;
	
	/// \brief Get session audio statistic information.
	/// \param send_info[out] is audio send information refer.
	/// \param recv_info[out] is audio receive information refer.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors getSessionAudioStatisticInfo(ZoomVideoSDKSessionAudioStatisticInfo& send_info, ZoomVideoSDKSessionAudioStatisticInfo& recv_info) = 0;

	/// \brief Get session video statistic information.
	/// \param send_info[out] is video send information refer.
	/// \param recv_info[out] is video receive information refer.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors getSessionVideoStatisticInfo(ZoomVideoSDKSessionASVStatisticInfo& send_info, ZoomVideoSDKSessionASVStatisticInfo& recv_info) = 0;
	
	/// \brief Get session share statistic information.
	/// \param send_info[out] is share send information refer.
	/// \param recv_info[out] is share receive information refer.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors getSessionShareStatisticInfo(ZoomVideoSDKSessionASVStatisticInfo& send_info, ZoomVideoSDKSessionASVStatisticInfo& recv_info) = 0;
};
END_ZOOM_VIDEO_SDK_NAMESPACE
#endif