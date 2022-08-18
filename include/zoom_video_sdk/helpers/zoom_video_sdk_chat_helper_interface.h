/*!
* \file zoom_video_sdk_chat_helper_interface.h
* \brief chat helper
*
*/

#ifndef _ZOOM_VIDEO_SDK_CHAT_HELPER_INTERFACE_H_
#define _ZOOM_VIDEO_SDK_CHAT_HELPER_INTERFACE_H_
#include "zoom_video_sdk_def.h"

BEGIN_ZOOM_VIDEO_SDK_NAMESPACE
class IZoomVideoSDKUser;
/// \brief Chat helper interface.
///
class IZoomVideoSDKChatHelper
{
public:
	/// \brief Determine if chat is disable.
    /// \return True if chat is disable. Otherwise returns false.
    virtual bool isChatDisabled() = 0;
    
	/// \brief Determine if private chat is disable.
    /// \return True if private chat is disable. Otherwise returns false.
    virtual bool isPrivateChatDisabled() = 0;
    
	/// \brief Send message to someone.
    /// \param pUser, it's the user which you want to send to.
    /// \param msgContent, the message content.
    /// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
    ///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
    virtual ZoomVideoSDKErrors sendChatToUser(IZoomVideoSDKUser* pUser, const zchar_t* msgContent) = 0;
    
	/// \brief Send message to all.
    /// \param msgContent, the message content.
    /// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
    ///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
    virtual ZoomVideoSDKErrors sendChatToAll(const zchar_t* msgContent) = 0;
};
END_ZOOM_VIDEO_SDK_NAMESPACE
#endif