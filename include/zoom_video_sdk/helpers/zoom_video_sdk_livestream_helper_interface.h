/*!
* \file zoom_video_sdk_livestream_helper_interface.h
* \brief live stream helper
*
*/

#ifndef _ZOOM_VIDEO_SDK_LIVESTREAM_HELPER_INTERFACE_H_
#define _ZOOM_VIDEO_SDK_LIVESTREAM_HELPER_INTERFACE_H_
#include "zoom_video_sdk_def.h"

BEGIN_ZOOM_VIDEO_SDK_NAMESPACE
/// \brief Live stream helper interface.
///
class IZoomVideoSDKLiveStreamHelper
{
public:
    
	/// \brief start live stream.
    /// \param streamUrl, the live stream url.
    /// \param key, the live stream key.
    /// \param broadcastUrl, the live stream broadcast url.
    /// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
    ///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
    virtual ZoomVideoSDKErrors startLiveStream(const zchar_t* streamUrl, const zchar_t* key, const zchar_t* broadcastUrl) = 0;
    
	/// \brief stop live stream.
    /// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
    ///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
    virtual ZoomVideoSDKErrors stopLiveStream() = 0;
    
	/// \brief Determin if can start the live stream.
    /// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
    ///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
    virtual ZoomVideoSDKErrors canStartLiveStream() = 0;
};
END_ZOOM_VIDEO_SDK_NAMESPACE
#endif