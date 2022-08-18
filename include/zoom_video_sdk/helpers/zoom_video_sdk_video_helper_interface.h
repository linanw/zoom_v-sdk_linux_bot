/*!
* \file zoom_video_sdk_video_helper_interface.h
* \brief video helper
*
*/

#ifndef _ZOOM_VIDEO_SDK_VIDEO_HELPER_INTERFACE_H_
#define _ZOOM_VIDEO_SDK_VIDEO_HELPER_INTERFACE_H_
#include "zoom_video_sdk_def.h"
#include "zoom_video_sdk_vector_interface.h"
#include "zoom_video_sdk_user_helper_interface.h"

BEGIN_ZOOM_VIDEO_SDK_NAMESPACE
typedef enum
{
	VideoRotation_0,
	VideoRotation_90,
	VideoRotation_180,
	VideoRotation_270,
}VideoRotation;

/*  \enum VideoPreferenceMode
	\brief video preference mode types
	Here are more detailed structural descriptions.
*/
typedef enum
{
	ZoomVideoSDKVideoPreferenceMode_Balance, // Balance mode
	ZoomVideoSDKVideoPreferenceMode_Sharpness, // Sharpness mode
	ZoomVideoSDKVideoPreferenceMode_Smoothness, // Smoothness mode	
	ZoomVideoSDKVideoPreferenceMode_Custom	// Custom mode.
}ZoomVideoSDKVideoPreferenceMode;

/*! \struct ZoomVideoSDKVideoPreferenceSetting
	\brief When setting custom modes, the maximum and minimum frame rates are provided by the developer.
	\If the current bandwidth cannot maintain the minimum frame rate, the video system will drop to the next lower resolution.
	\The default maximum and minimum frame rates for other modes are 0.
*/
typedef struct tagVideoPreferenceSetting
{
	ZoomVideoSDKVideoPreferenceMode mode;  ///<0: Balance mode; 1: Smoothness mode; 2: Sharpness mode; 3: Custom mode
	uint32_t minimum_frame_rate; ///<0 for the default value,minimum_frame_rate should be less than maximum_frame_rate, range: from 0 to 30 .out of range for frame-rate will use default frame-rate of Zoom	
	uint32_t maximum_frame_rate; ///<0 for the default value,maximum_frame_rate should be less and equal than 30, range: from 0 to 30.out of range for frame-rate will use default frame-rate of Zoom
	tagVideoPreferenceSetting()
	{
		mode = ZoomVideoSDKVideoPreferenceMode_Balance;
		minimum_frame_rate = 0;
		maximum_frame_rate = 0;
	}
} ZoomVideoSDKVideoPreferenceSetting;

enum ZoomVideoSDKMultiCameraStreamStatus
{
	ZoomVideoSDKMultiCameraStreamStatus_JoinStart, /// Current user only. This status is received when the current user starts the attempt to use multiple cameras in the session.
	ZoomVideoSDKMultiCameraStreamStatus_JoinFail, /// Current user only. This status is received when the current user fails the attempt to use multiple cameras in the session.
	ZoomVideoSDKMultiCameraStreamStatus_Joined, /// Broadcasted to all users. This status is received when a new camera has been successfully added to the session as the multiple cameras.
	ZoomVideoSDKMultiCameraStreamStatus_Left, /// Broadcasted to all users. This status is received when a camera that is being used as the multiple cameras has left the session.
};

/// \brief Camera device interface.
///
class IZoomVideoSDKCameraDevice
{
public:
	virtual ~IZoomVideoSDKCameraDevice(){}
	virtual const zchar_t* getDeviceId() = 0;
	virtual const zchar_t* getDeviceName() = 0;
	virtual bool isSelectedDevice() = 0;
#if !defined (__linux)
	/// \brief Determine whether the camera is selected as multiple stream video.
	/// \return True if selected. Otherwise returns false.
	virtual bool isSelectedAsMultiCamera() = 0;
	
	/// \brief Determine whether the camera is running as multiple stream video.
	/// \return True if running. Otherwise returns false.
	virtual bool isRunningAsMultiCamera() = 0;
#endif
};

/// \brief An interface to control video and manage cameras during a video session.
///
class IZoomVideoSDKVideoHelper
{
public:
	virtual ~IZoomVideoSDKVideoHelper(){}

	/// \brief Call this method to start sending local video data from the camera.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
    virtual ZoomVideoSDKErrors startVideo() = 0;

	/// \brief Call this method to stop sending local video data from the camera.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
    virtual ZoomVideoSDKErrors stopVideo() = 0;

	/// \brief Call this method to rotate the video when the device is rotated.
	/// \return Returns true if the rotation was successful, false otherwise.
    virtual bool rotateMyVideo(VideoRotation rotation) = 0;

	/// \brief Switch to the next available camera.
	/// \return Returns true if the switch to the next camera was successful, false otherwise.
    virtual bool switchCamera() = 0;

	/// \brief Switch to the camera passed in as cameraDeviceID.
	/// \return Returns true if the switch was successful, false otherwise.
	virtual bool selectCamera(const zchar_t* cameraDeviceID) = 0;

#if !defined (__linux)
	/// \brief Enable multiple stream video if you have multiple cameras 
	///        and other participants can see multiple videos of you.
	/// \param cameraDeviceID, the camera ID which you want to enable. 
	/// \return True if success. Otherwise returns false.
	virtual bool enableMultiStreamVideo(const zchar_t* cameraDeviceID) = 0;

	/// \brief Disable multiple stream video 
	/// \param cameraDeviceID, the camera id which you want to disable. 
	/// \return True if success. Otherwise returns false.
	virtual bool disableMultiStreamVideo(const zchar_t* cameraDeviceID) = 0;
#endif

	/// \brief Returns number of cameras available to share the video.
	/// \return number of cameras.
    virtual uint32_t getNumberOfCameras() = 0;

	/// \brief Returns a collection of camera devices available to share the video as an object of type \link IZoomVideoSDKCameraDevice \endlink
	/// \return Camera devices list.
    virtual IVideoSDKVector<IZoomVideoSDKCameraDevice*>* getCameraList() = 0;

	/// \brief Check whether the current user has permission to control the camera.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors canControlCamera(bool& bCan) = 0;

	/// \brief Turn the camera to the left.
	/// \param range: Rotation range, 10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors turnCameraLeft(unsigned int range = 50) = 0;

	/// \brief Turn the camera to the right.
	/// \param range: Rotation range, 10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors turnCameraRight(unsigned int range = 50) = 0;

	/// \brief Turn the camera up.
	/// \param range: Rotation range, 10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors turnCameraUp(unsigned int range = 50) = 0;

	/// \brief Turn the camera down.
	/// \param range: Rotation range, 10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors turnCameraDown(unsigned int range = 50) = 0;

	/// \brief Zoom the camera in.
	/// \param range: Zoom range, 10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors zoomCameraIn(unsigned int range = 50) = 0;

	/// \brief Zoom the camera out.
	/// \param range: Zoom range, 10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors zoomCameraOut(unsigned int range = 50) = 0;

	/// \brief Automatically adjust user's video solution and frame-rate
	/// \param preference_setting Specifies the video quality preference.	
	/// \when setting custom modes, the maximum and minimum frame rates are provided by the developer.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors setVideoQualityPreference(ZoomVideoSDKVideoPreferenceSetting& preference_setting) = 0;

	/// \brief Subscribe preview video raw data with a callback
	/// \param listener, callback sink object.
	/// \param cameraDeviceID;
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors startVideoPreview(IZoomVideoSDKRawDataPipeDelegate* listener, const zchar_t* cameraDeviceID = NULL) = 0;

	/// \brief UnSubscribe preview video raw data with the subscribed callback.
	/// \param listener, callback sink object.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors stopVideoPreview(IZoomVideoSDKRawDataPipeDelegate* listener) = 0;

};
END_ZOOM_VIDEO_SDK_NAMESPACE
#endif