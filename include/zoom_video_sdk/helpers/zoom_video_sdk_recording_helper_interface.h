#ifndef _ZOOM_VIDEO_SDK_RECORDING_HELPER_INTERFACE_H_
#define _ZOOM_VIDEO_SDK_RECORDING_HELPER_INTERFACE_H_

#include "zoom_video_sdk_def.h"

BEGIN_ZOOM_VIDEO_SDK_NAMESPACE

class IZoomVideoSDKRecordingHelper
{
public:
	/// \brief Checks whether the current user has permission to start cloud recording.
	/// The following are the prerequisites to use the helper class:
	///		A cloud recording add-on plan
	///		Cloud recording feature enabled on the Web portal
	/// \return ZoomVideoSDKErrors_Success if the current user can start recording.
	///Otherwise, the user cannot start recording, see error codes defined in \link ZoomVideoSDKErrors \endlink.
	virtual ZoomVideoSDKErrors canStartRecording() = 0;
	
	/// \brief Start cloud recording.
	/// \return ZoomVideoSDKErrors_Success if the start cloud recording request was successful.
	///Otherwise, the start cloud recording request failed.
	/// Since cloud recording involves asynchronous operations, 
	/// a return value of ZoomVideoSDKErrors_Success does not guarantee that the recording will start. 
	/// See \link ZoomVideoSDKDelegate  \endlink, see \link onCloudRecordingStatus \endlink,
	/// for information on how to confirm that recording has commenced.
	/// See error codes defined in  \link  ZoomVideoSDKErrors \endlink.
	virtual ZoomVideoSDKErrors startCloudRecording() = 0;

	/// \brief Pause the ongoing cloud recording.
	/// \return ZoomVideoSDKErrors_Success if the pause cloud recording request was successful.
	///Otherwise, the pause cloud recording request failed.
	/// Since cloud recording involves asynchronous operations, 
	/// a return value of ZoomVideoSDKErrors_Success does not guarantee that the recording will pause. 
	/// See \link ZoomVideoSDKDelegate  \endlink, see \link onCloudRecordingStatus \endlink,
	/// for information on how to confirm that recording has paused.
	/// See error codes defined in  \link  ZoomVideoSDKErrors \endlink.
	virtual ZoomVideoSDKErrors stopCloudRecording() = 0;

	/// \brief Resume the previously paused cloud recording.
	/// \return ZoomVideoSDKErrors_Success if the pause cloud recording request was successful.
	///Otherwise, the pause cloud recording request failed.
	/// Since cloud recording involves asynchronous operations, 
	/// a return value of ZoomVideoSDKErrors_Success does not guarantee that the recording will pause. 
	/// See \link ZoomVideoSDKDelegate  \endlink, see \link onCloudRecordingStatus \endlink,
	/// for information on how to confirm that recording has paused.
	/// See error codes defined in  \link  ZoomVideoSDKErrors \endlink.
	virtual ZoomVideoSDKErrors pauseCloudRecording() = 0;

	/// \brief Resume the previously paused cloud recording.
	/// \return ZoomVideoSDKErrors_Success if the resume cloud recording request was successful.
	///Otherwise, the resume cloud recording request failed.
	/// Since cloud recording involves asynchronous operations, 
	/// a return value of ZoomVideoSDKErrors_Success does not guarantee that the recording will resume. 
	/// See \link ZoomVideoSDKDelegate  \endlink, see \link onCloudRecordingStatus \endlink,
	/// for information on how to confirm that recording has resumed.
	/// See error codes defined in  \link  ZoomVideoSDKErrors \endlink.
	virtual ZoomVideoSDKErrors resumeCloudRecording() = 0;

	/// \brief Get the current status of cloud recording.
	/// \param status cloud recording status defined in \link RecordingStatus \endlink.
	/// \return ZoomVideoSDKErrors_Success if the get cloud recording status request was successful.
	///Otherwise failed. the get cloud recording status request failed.
	/// See error codes defined in  \link  ZoomVideoSDKErrors \endlink.
	virtual ZoomVideoSDKErrors getCloudRecordingStatus(RecordingStatus& record_status) = 0;
};

END_ZOOM_VIDEO_SDK_NAMESPACE
#endif // _ZOOM_VIDEO_SDK_RECORDING_HELPER_INTERFACE_H_