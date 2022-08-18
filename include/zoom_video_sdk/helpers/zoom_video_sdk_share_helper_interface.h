/*!
* \file zoom_video_sdk_share_helper_interface.h
* \brief share helper
*
*/

#ifndef _ZOOM_VIDEO_SDK_SHARE_HELPER_INTERFACE_H_
#define _ZOOM_VIDEO_SDK_SHARE_HELPER_INTERFACE_H_
#include "zoom_video_sdk_def.h"

BEGIN_ZOOM_VIDEO_SDK_NAMESPACE
struct ZoomVideoSDKShareOption
{
    bool isWithDeviceAudio;            ///<share option, true: share computer sound when share screen/window, otherwise not.
    bool isOptimizeForSharedVideo;     ///<share option, true: optimize the frame rate when share screen/window, otherwise not.

    ZoomVideoSDKShareOption()
    {
        isWithDeviceAudio = false;
        isOptimizeForSharedVideo = false;
    }

    ZoomVideoSDKShareOption(const ZoomVideoSDKShareOption& option)
    {
        isWithDeviceAudio = option.isWithDeviceAudio;
        isOptimizeForSharedVideo = option.isOptimizeForSharedVideo;
    }

    ZoomVideoSDKShareOption(bool bWithAudio, bool optimize)
    {
        isWithDeviceAudio = bWithAudio;
        isOptimizeForSharedVideo = optimize;
    }
};

/// \brief Share helper interface.
///
class IZoomVideoSDKRawDataPipeDelegate;
class IZoomVideoSDKShareHelper
{
public:

	/// \brief Share a window, if virtual speaker is enabled, don't support share audio.
    /// \param handle, the window handle that will to be share.
    /// \param option, see \link ZoomVideoSDKShareOption \endlink.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
    virtual ZoomVideoSDKErrors startShareView(void* handle, ZoomVideoSDKShareOption option = {false, false}) = 0;
	
	/// \brief Share a screen, if virtual speaker is enabled, don't support share audio.
    /// \param monitorID, the screen name that will to be share.
    /// \param option, see \link ZoomVideoSDKShareOption \endlink.
    /// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
    ///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
    virtual ZoomVideoSDKErrors startShareScreen(const zchar_t* monitorID, ZoomVideoSDKShareOption option = { false, false }) = 0;

    /// \brief Start sharing only the computer audio.
    /// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
    ///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
    virtual ZoomVideoSDKErrors startShareComputerAudio() = 0;
    
	/// \brief Stop share.
    /// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
    ///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
    virtual ZoomVideoSDKErrors stopShare() = 0;
    
	/// \brief Determine if myself is sharing.
	/// \return True if myself is sharing. Otherwise returns false.
    virtual bool isSharingOut() = 0;
    
	/// \brief Determine if myself is sharing screen.
    /// \return True if myself is sharing screen. Otherwise returns false.
    virtual bool isScreenSharingOut() = 0;

	/// \brief Determine if other user is sharing.
    /// \return True if other user is sharing screen. Otherwise returns false.
    virtual bool isOtherSharing() = 0;
    
	/// \brief Lock current share.(only host call).
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
    virtual ZoomVideoSDKErrors lockShare(bool lock) = 0;
    
	/// \brief Determine if share is locked.
    /// \return True if share is locked. Otherwise returns false.
    virtual bool isShareLocked() = 0;

	/// \brief Enable or disable the computer sound when sharing, if virtual speaker is enabled, don't support share audio.
    /// \param  enable, TRUE indicates to enable. FALSE disable.
    /// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
    ///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors enableShareDeviceAudio(bool enable) = 0;
	
	/// \brief Determine if share computer sound is enabled.
    /// \return True if enabled. Otherwise returns false.
    virtual bool isShareDeviceAudioEnabled() = 0;

	/// \brief Enable or disable the optimization of frame rate, you can enable it when there is video in shared content.
    /// \param  enable, TRUE indicates to enable. FALSE disable.
    /// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
    ///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors enableOptimizeForSharedVideo(bool enable) = 0;
	
	/// \brief Determine if optimization for shared video is enabled.
    /// \return True if enabled. Otherwise returns false.
    virtual bool isOptimizeForSharedVideoEnabled() = 0;

    /// \brief Start sharing a camera feed specified by the cameraID as the second camera.
    /// \param cameraID: The camera ID.Warning: This must be a different camera than the one sending your primary video.
    /// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
    ///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
    virtual ZoomVideoSDKErrors startShare2ndCamera(const zchar_t* cameraID) = 0;

    /// \brief Subscribe to the raw data stream of the camera that is shared as the second camera.
    /// \param data_handler: Data handler object.
    /// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
    ///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
    virtual ZoomVideoSDKErrors subscribeMyShareCamera(IZoomVideoSDKRawDataPipeDelegate* data_handler) = 0;
    
    /// \brief Unsubscribe to the raw data stream of the camera that is shared as the second camera.
    /// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
    ///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
    virtual ZoomVideoSDKErrors unSubscribeMyShareCamera() = 0;
};
END_ZOOM_VIDEO_SDK_NAMESPACE
#endif