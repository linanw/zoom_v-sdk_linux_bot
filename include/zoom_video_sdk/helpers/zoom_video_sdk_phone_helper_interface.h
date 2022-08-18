/*!
* \file zoom_video_sdk_phone_helper_interface.h
* \brief phone helper interface.
*
*/

#ifndef _ZOOM_VIDEO_SDK_PHONE_INTERFACE_H_
#define _ZOOM_VIDEO_SDK_PHONE_INTERFACE_H_
#include "zoom_video_sdk_def.h"
#include "zoom_video_sdk_vector_interface.h"

BEGIN_ZOOM_VIDEO_SDK_NAMESPACE
/// \brief Phone session support country information interface.
class IZoomVideoSDKPhoneSupportCountryInfo
{
public:
	virtual ~IZoomVideoSDKPhoneSupportCountryInfo() {}
	/// \brief Get the country ID of the current information. 
	/// \return The country ID.
	virtual const zchar_t* getCountryID() = 0;
	/// \brief Get the country name of the current information.
	/// \return The country name.
	virtual const zchar_t* getCountryName() = 0;
	/// \brief Get the country code of the current information.
	/// \return The country code.
	virtual const zchar_t* getCountryCode() = 0;
};

/*! \enum PhoneStatus
	\brief Status of telephone.
	Here are more detailed structural descriptions.
*/
enum PhoneStatus
{
	PhoneStatus_None,///<No status.
	PhoneStatus_Calling,///<In process of calling out.
	PhoneStatus_Ringing,///<In process of ringing.
	PhoneStatus_Accepted,///<Accept the call.
	PhoneStatus_Success,///<Call successful.
	PhoneStatus_Failed,///<Call failed.
	PhoneStatus_Canceling,///<In process of canceling the response to the previous state.
	PhoneStatus_Canceled, ///<Cancel successfully.
	PhoneStatus_Cancel_Failed,///<Cancel fails.
	PhoneStatus_Timeout,///<Timeout.
};


/*! \enum PhoneFailedReason
	\brief The reason for the failure of the telephone call.
	Here are more detailed structural descriptions.
*/
enum PhoneFailedReason
{
	PhoneFailedReason_None,///<For initialization.
	PhoneFailedReason_Busy,///<The telephone service is busy.
	PhoneFailedReason_Not_Available,///<The telephone is out of the service.
	PhoneFailedReason_User_Hangup,///<The user hangs up.
	PhoneFailedReason_Other_Fail,///<Other reasons.
	PhoneFailedReason_No_Answer,///<The telephone does not reply.
	PhoneFailedReason_Block_No_Host,///<Disable the function of international call-out before the host joins the session.
	PhoneFailedReason_Block_High_Rate,///<The call-out is blocked by the system due to the high cost.
	PhoneFailedReason_Block_Too_Frequent,///<All the invitees invited by the call should press the button one(1) to join the session. In case that many invitees do not press the button that leads to time out, the call invitation for this session shall be banned.
};


/// \brief zoom video sdk phone helper interface.
///
class IZoomVideoSDKPhoneHelper
{
public:
	/// \brief Determine whether the session supports to join by the phone or not.
	/// \return TRUE indicates to support to join by phone. FALSE not.
	virtual bool isSupportPhoneFeature() = 0;

	/// \brief Get the list of the country information where the session supports to join by telephone.
	/// \return List of the country information returns if the session supports to join by telephone. Otherwise NULL.
	virtual IVideoSDKVector<IZoomVideoSDKPhoneSupportCountryInfo* >* getSupportCountryInfo() = 0;

	/// \brief Invite the specified user to join the session by call out.
	/// \param countryCode The country code of the specified user must be in the support list. 
	/// \param phoneNumber The phone number of specified user.
	/// \param name The screen name of the specified user in the session.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual ZoomVideoSDKErrors inviteByPhone(const zchar_t* countryCode, const zchar_t* phoneNumber, const zchar_t* name) = 0;

	/// \brief Cancel the invitation that is being invited by phone.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual ZoomVideoSDKErrors cancelInviteByPhone() = 0;

	/// \brief Get the process of the invitation by phone.
	/// \return If the function succeeds, the return value is the current invite by phone process. To get extended error information, see \link PhoneStatus \endlink enum
	virtual PhoneStatus getInviteByPhoneStatus() = 0;
};

END_ZOOM_VIDEO_SDK_NAMESPACE
#endif