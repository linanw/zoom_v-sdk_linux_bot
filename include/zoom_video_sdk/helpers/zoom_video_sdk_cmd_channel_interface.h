/*!
* \file zoom_video_sdk_cmd_channel_interface.h
* \brief cmd channel
*
*/

#ifndef _ZOOM_VIDEO_SDK_CMD_CHANNEL_INTERFACE_H_
#define _ZOOM_VIDEO_SDK_CMD_CHANNEL_INTERFACE_H_
#include "zoom_video_sdk_def.h"

BEGIN_ZOOM_VIDEO_SDK_NAMESPACE

/// \brief The command channel is a service tied to the current session, 
///        which allows users to send data or commands to other users in the same session.
class IZoomVideoSDKUser;
class IZoomVideoSDKCmdChannel
{
public:
    virtual ~IZoomVideoSDKCmdChannel() {}

	/// \brief Send custom commands to other users in the current session.
    /// \param receiver: the user who will receive the command, if receiver is NULL, send to all. see \link IZoomVideoSDKUser \endlink.
    /// \param strCmd: the customized command.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
    virtual ZoomVideoSDKErrors sendCommand(IZoomVideoSDKUser* receiver, const zchar_t* strCmd) = 0;
};
END_ZOOM_VIDEO_SDK_NAMESPACE
#endif