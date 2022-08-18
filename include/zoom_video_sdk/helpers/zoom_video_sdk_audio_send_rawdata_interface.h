/*!
* \file zoom_video_sdk_audio_send_rawdata_interface.h
* \brief send audio raw data
*
*/
#ifndef _ZOOM_VIDEO_SDK_AUDIO_SEND_RAWDATA_INTERFACE_H_
#define _ZOOM_VIDEO_SDK_AUDIO_SEND_RAWDATA_INTERFACE_H_
#include "zoom_video_sdk_def.h"

BEGIN_ZOOM_VIDEO_SDK_NAMESPACE

/// \brief Audio raw data sender interface.
///
class IZoomVideoSDKAudioSender 
{
public:
	virtual ~IZoomVideoSDKAudioSender() {}

	/// \brief send audio raw data, channel number must be mono, and sampling bits must be 16.
	/// \param data, the address of audio data.
	/// \param data_length, the length of audio data, it must be even numbers.
	/// \param sample_rate, the sampling rate of audio data.
	/// Supported audio data properties:
	/// Sample Rate: 8000/11025/32000/44100/48000/50000/50400/96000/192000/2822400
	/// Channels: mono
	/// resolution: little-endian, 16bit
	virtual ZoomVideoSDKErrors Send(char* data, unsigned int data_length, int sample_rate) = 0;
};

/// \brief Virtual audio mic interface.
///
class IZoomVideoSDKVirtualAudioMic
{
public:
	virtual ~IZoomVideoSDKVirtualAudioMic() {}

	/// \brief Callback for virtual audio mic to do some initialization.
	/// \param rawdata_sender, you can send audio data based on this object, see \link IZoomVideoSDKAudioRawDataSender \endlink.
	virtual void onMicInitialize(IZoomVideoSDKAudioSender* rawdata_sender) = 0;

	/// \brief Callback for virtual audio mic can send raw data with 'rawdata_sender'.
	virtual void onMicStartSend() = 0;
	
	/// \brief Callback for virtual audio mic should stop send raw data.
	virtual void onMicStopSend() = 0;
	
	/// \brief Callback for virtual audio mic is uninitialized.
	virtual void onMicUninitialized() = 0;
};


class IZoomVideoSDKUser;
/// \brief Virtual audio speaker interface.
///
class IZoomVideoSDKVirtualAudioSpeaker
{
public:
	virtual ~IZoomVideoSDKVirtualAudioSpeaker() {}

	/// \brief The callback event for receiving the mixed audio raw data.
	/// \param data_, The mixed audio raw data. A pointer to AudioRawData. For more details, see \link AudioRawData \endlink.
	virtual void onVirtualSpeakerMixedAudioReceived(AudioRawData* data_) = 0;

	/// \brief The callback event for receiving the one way audio raw data.
	/// \param data_, The one way audio raw data. A pointer to AudioRawData. For more details, see \link AudioRawData \endlink.
	/// \param pUser, The corresponding participant of the audio raw data.
	virtual void onVirtualSpeakerOneWayAudioReceived(AudioRawData* data_, IZoomVideoSDKUser* pUser) = 0;

	/// \brief The callback event for receiving the share audio raw data.
	/// \param data_, The shared audio raw data in session. A pointer to AudioRawData. For more details, see \link AudioRawData \endlink.
	virtual void onVirtualSpeakerSharedAudioReceived(AudioRawData* data_) = 0;
};
END_ZOOM_VIDEO_SDK_NAMESPACE
#endif