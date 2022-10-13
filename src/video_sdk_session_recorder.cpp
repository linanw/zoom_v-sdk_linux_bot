#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <curl/curl.h>


#include "glib.h"
#include "json.hpp"
#include "helpers/zoom_video_sdk_user_helper_interface.h"
#include "zoom_video_sdk_api.h"
#include "zoom_video_sdk_def.h"
#include "zoom_video_sdk_delegate_interface.h"
#include "zoom_video_sdk_interface.h"
#include "raw_data_ffmpeg_encoder.h"
#include "zoom_video_sdk_chat_message_interface.h"

using Json = nlohmann::json;
USING_ZOOM_VIDEO_SDK_NAMESPACE
IZoomVideoSDK *video_sdk_obj;
GMainLoop *loop;
std::string FINALJWTToken;
std::string FINALLocalURL;

std::string getSelfDirPath()
{
    char dest[PATH_MAX];
    memset(dest, 0, sizeof(dest)); // readlink does not null terminate!
    if (readlink("/proc/self/exe", dest, PATH_MAX) == -1)
    {
    }

    char *tmp = strrchr(dest, '/');
    if (tmp)
        *tmp = 0;
    printf("getpath\n");
    return std::string(dest);
}

class ZoomVideoSDKDelegate : public IZoomVideoSDKDelegate
{
public:
    /// \brief Triggered when user enter the session.
    virtual void onSessionJoin()
    {
        printf("Joined session successfully\n");
    };

    /// \brief Triggered when session leaveSession
    virtual void onSessionLeave()
    {
        g_main_loop_unref(loop);
        printf("Already left session.\n");
        exit(1);
    };

    /// \brief Triggered when session error.
    /// \param errorCode for more details, see \link ZoomVideoSDKErrors \endlink.
    /// \param detailErrorCode Detailed errorCode.
    virtual void onError(ZoomVideoSDKErrors errorCode, int detailErrorCode)
    {
        printf("join session errorCode : %d  detailErrorCode: %d\n", errorCode, detailErrorCode);
    };

    /// \brief Triggered when myself or other user join session.
    /// \param pUserHelper is the pointer to user helper object, see \link IZoomVideoSDKUserHelper \endlink.
    /// \param userList is the pointer to user object list.
    virtual void onUserJoin(IZoomVideoSDKUserHelper *pUserHelper, IVideoSDKVector<IZoomVideoSDKUser *> *userList)
    {
        if (userList)
        {
            int count = userList->GetCount();
            for (int index = 0; index < count; index++)
            {
                IZoomVideoSDKUser *user = userList->GetItem(index);
                if (user)
                {
                    // class ZoomVideoSDKRawDataPipeDelegate : public IZoomVideoSDKRawDataPipeDelegate
                    // {
                    // public:
                    //     /// \brief Call when subscribed data received.
                    //     /// \param data_, data object.
                    //     virtual void onRawDataFrameReceived(YUVRawDataI420 *data_)
                    //     {
                    //         // printf("onRawDataFrameReceived %d*%d\n", data_->GetStreamWidth(), data_->GetStreamHeight());
                    //         printf(".");
                    //         std::cout.flush();
                    //     }

                    //     /// \brief Call when subscribed data status changed.
                    //     /// \param status, current data status.
                    //     virtual void onRawDataStatusChanged(RawDataStatus status)
                    //     {
                    //     }
                    // };
                    // static ZoomVideoSDKRawDataPipeDelegate s_video_data_cb_obj;
                    // user->GetVideoPipe()->subscribe(ZoomVideoSDKResolution_720P, &s_video_data_cb_obj);
                    RawDataFFMPEGEncoder *encoder = new RawDataFFMPEGEncoder(user);
                }
            }
        }
    };

    /// \brief Triggered when other users leave session.
    /// \param pUserHelper is the pointer to user helper object, see \link IZoomVideoSDKUserHelper \endlink.
    /// \param userList is the pointer to user object list.
    virtual void onUserLeave(IZoomVideoSDKUserHelper *pUserHelper, IVideoSDKVector<IZoomVideoSDKUser *> *userList)
    {
        if (userList)
        {
            int count = userList->GetCount();
            for (int index = 0; index < count; index++)
            {
                IZoomVideoSDKUser *user = userList->GetItem(index);
                if (user)
                {
                    RawDataFFMPEGEncoder::stop_encoding_for(user);
                }
            }
        }
    };

    /// \brief Triggered when user video status changed.
    /// \param pVideoHelper is the pointer to video helper object, see \link IZoomVideoSDKVideoHelper \endlink.
    /// \param userList is the pointer to user object list.
    virtual void onUserVideoStatusChanged(IZoomVideoSDKVideoHelper *pVideoHelper,
                                          IVideoSDKVector<IZoomVideoSDKUser *> *userList){};

    /// \brief Triggered when user audio status changed.
    /// \param pAudioHelper is the pointer to audio helper object, see \link IZoomVideoSDKAudioHelper \endlink.
    /// \param userList is the pointer to user object list.
    virtual void onUserAudioStatusChanged(IZoomVideoSDKAudioHelper *pAudioHelper,
                                          IVideoSDKVector<IZoomVideoSDKUser *> *userList){};

    /// \brief Triggered when user Share status changed.
    /// \param pShareHelper is the pointer to share helper object, see \link IZoomVideoSDKShareHelper \endlink.
    /// \param pUser is the pointer to user object.
    /// \param status is the share status of the user.
    virtual void onUserShareStatusChanged(IZoomVideoSDKShareHelper *pShareHelper,
                                          IZoomVideoSDKUser *pUser,
                                          ZoomVideoSDKShareStatus status){};

    /// \brief Triggered when user live stream status changed
    /// \param pLiveStreamHelper is the pointer to live stream helper object, see \link IZoomVideoSDKLiveStreamHelper
    /// \endlink. \param status is the current status of live stream.
    virtual void onLiveStreamStatusChanged(IZoomVideoSDKLiveStreamHelper *pLiveStreamHelper,
                                           ZoomVideoSDKLiveStreamStatus status){


                                           };

    /// \brief Triggered when chat message received.
    /// \param pChatHelper is the pointer to chat helper object, see \link IZoomVideoSDKChatHelper \endlink.
    /// \param messageItem is the pointer to message object
    virtual void onChatNewMessageNotify(IZoomVideoSDKChatHelper *pChatHelper, IZoomVideoSDKChatMessage *messageItem){
    //printf("chat message received\n");
    if (!messageItem)
        return;

    //get raw zchar_t* 
    //for non win32, this is mapped to a char datatype
    const zchar_t* szMessageContent = messageItem->getContent();

  
    //IZoomVideoSDKUser* pRecievingUser = messageItem->getReceiveUser();
    //IZoomVideoSDKUser* pSendingUser = messageItem->getSendUser();


    //convert to string
    std::string s = szMessageContent;


    if (s.compare("u")==0){

    printf("chat message received : up\n");
    std::string url_to_call = FINALLocalURL+"up";
    callNodeJSToSerialHelper(url_to_call);
    }
    else  if (s.compare("d")==0){

    printf("chat message received : down\n");
  std::string url_to_call = FINALLocalURL+"down";
    callNodeJSToSerialHelper(url_to_call);
    }
       else  if (s.compare("l")==0){

    printf("chat message received : left\n");
    std::string url_to_call = FINALLocalURL+"left";
    callNodeJSToSerialHelper(url_to_call);
    }
       else  if (s.compare("r")==0){

    printf("chat message received : right\n");
   std::string url_to_call = FINALLocalURL+"right";
    callNodeJSToSerialHelper(url_to_call);
    }
       else  if (s.compare("s")==0){

    printf("chat message received : start\n");
    std::string url_to_call = FINALLocalURL+"start";
    callNodeJSToSerialHelper(url_to_call);
    }
       else  if (s.compare("c")==0){

    printf("chat message received : catch\n");
   std::string url_to_call = FINALLocalURL+"catch";
    callNodeJSToSerialHelper(url_to_call);



    }

       else  if (s.compare("stream")==0){

    printf("chat message received : stream\n");

    // Get the IZoomVideoSDKLiveStreamHelper to perform livestream actions.
    IZoomVideoSDKLiveStreamHelper* pLiveStreamHelper = video_sdk_obj->getLiveStreamHelper();

       // Check if live stream can start.
   // if (pLiveStreamHelper->canStartLiveStream() == ZoomVideoSDKErrors_Success) {

    const zchar_t* strStreamUrl ="rtmp://a.rtmp.youtube.com/live2";
    const zchar_t* strKey ="6kft-yswg-uf68-0sj1-49gm";
    const zchar_t* strBroadcastUrl ="https://www.youtube.com/watch?v=oCJdsKSrTHo";
    // Call startLiveStream to begin live stream.
    int err = pLiveStreamHelper->startLiveStream(strStreamUrl, strKey, strBroadcastUrl);

        if (err == ZoomVideoSDKErrors_Success)
        {
            // Live stream successfully began.
              printf(" Live stream successfully began.\n");

        }
        else
        {
            // Live stream could not start.

              printf(" Live stream could not start.\n");

        }
//}


    }

 
    };

    /// \brief Triggered when host changed.
    /// \param pUserHelper is the pointer to user helper object, see \link IZoomVideoSDKUserHelper \endlink.
    /// \param pUser is the pointer to user object.
    virtual void onUserHostChanged(IZoomVideoSDKUserHelper *pUserHelper, IZoomVideoSDKUser *pUser){};

    /// \brief Triggered when active audio user changed.
    /// \param pAudioHelper is the pointer to audio helper object, see \link IZoomVideoSDKAudioHelper \endlink.
    /// \param list is the pointer to user object list.
    virtual void onUserActiveAudioChanged(IZoomVideoSDKAudioHelper *pAudioHelper,
                                          IVideoSDKVector<IZoomVideoSDKUser *> *list){};

    /// \brief Triggered when session needs password.
    /// \param handler is the pointer to password handler object, see \link IZoomVideoSDKPasswordHandler \endlink.
    virtual void onSessionNeedPassword(IZoomVideoSDKPasswordHandler *handler){};

    /// \brief Triggered when password is wrong.
    /// \param handler is the pointer to password handler object, see \link IZoomVideoSDKPasswordHandler \endlink.
    virtual void onSessionPasswordWrong(IZoomVideoSDKPasswordHandler *handler){};

    /// \brief Triggered when mixed audio raw data received.
    /// \param data_ is the pointer to audio raw data, see \link AudioRawData \endlink.
    virtual void onMixedAudioRawDataReceived(AudioRawData *data_){};

    /// \brief Triggered when one way audio raw data received.
    /// \param data_ is the pointer to audio raw data, see \link AudioRawData \endlink.
    /// \param pUser is the pointer to user object, see \link IZoomVideoSDKUser \endlink.
    virtual void onOneWayAudioRawDataReceived(AudioRawData *data_, IZoomVideoSDKUser *pUser){};

    /// \brief Triggered when share audio data received.
    /// \param data_ is the pointer to audio raw data, see \link AudioRawData \endlink.
    virtual void onSharedAudioRawDataReceived(AudioRawData *data_){};

    /// \brief Triggered when user get session manager role.
    /// \param pUser is the pointer to user object, see \link IZoomVideoSDKUser \endlink.
    virtual void onUserManagerChanged(IZoomVideoSDKUser *pUser){};

    /// \brief Triggered when user name changed.
    /// \param pUser is the pointer to user object, see \link IZoomVideoSDKUser \endlink.
    virtual void onUserNameChanged(IZoomVideoSDKUser *pUser){};

    /// \brief Callback for when the current user is granted camera control access.
    /// Once the current user sends the camera control request, this callback will be triggered with the result of the
    /// request. \param pUser the pointer to the user who received the request, see \link IZoomVideoSDKUser \endlink.
    /// \param isApproved the result of the camera control request
    virtual void onCameraControlRequestResult(IZoomVideoSDKUser *pUser, bool isApproved){};

    /// \brief Callback interface for when the current user has received a camera control request.
    /// This will be triggered when another user requests control of the current user��s camera.
    /// \param pUser is the pointer to the user who sent the request, see \link IZoomVideoSDKUser \endlink.
    /// \param requestType the request type, see \link ZoomVideoSDKCameraControlRequestType \endlink.
    /// \param pCameraControlRequestHandler the pointer to the helper instance of the camera controller, see \link
    /// IZoomVideoSDKCameraControlRequestHandler \endlink.
    virtual void onCameraControlRequestReceived(
        IZoomVideoSDKUser *pUser,
        ZoomVideoSDKCameraControlRequestType requestType,
        IZoomVideoSDKCameraControlRequestHandler *pCameraControlRequestHandler){};

    /// \brief Callback for when a message has been received from the command channel.
    ///        Once the command channel is active, this callback is triggered each time a message has been received.
    /// \param pSender The user who sent the command, see \link IZoomVideoSDKUser \endlink.
    /// \param strCmd Received command.
    virtual void onCommandReceived(IZoomVideoSDKUser *sender, const zchar_t *strCmd){
        //strCmd;
    printf("command message received\n");

    };

    /// \brief Callback for when the command channel is ready to be used.
    ///        After the SDK attempts to establish a connection for the command channel upon joining a session,
    ///        this callback will be triggered once the connection attempt has completed.
    /// \param isSuccess true: success, command channel is ready to be used.
    ///        false: Failure, command channel was unable to connect.
    virtual void onCommandChannelConnectResult(bool isSuccess){
            if (isSuccess){
            printf("command channel connected : success\n");
            }
    };

    /// \brief Triggered when call Out status changed.
    virtual void onInviteByPhoneStatus(PhoneStatus status, PhoneFailedReason reason){};

    /// \brief Callback for when the cloud recording status has changed (e.g. paused, stopped, resumed).
    /// \param status cloud recording status defined in \link RecordingStatus \endlink.
    virtual void onCloudRecordingStatus(RecordingStatus status){};

    /// \brief Triggered when host ask you to unmute.
    virtual void onHostAskUnmute(){};

    virtual void onUserShareStatusChanged(IZoomVideoSDKShareHelper *pShareHelper, IZoomVideoSDKUser *pUser, ZoomVideoSDKShareStatus status, ZoomVideoSDKShareType type) {}

    virtual void onMultiCameraStreamStatusChanged(ZoomVideoSDKMultiCameraStreamStatus status, IZoomVideoSDKUser *pUser, IZoomVideoSDKRawDataPipe *pVideoPipe) {}

    virtual void onMicSpeakerVolumeChanged(unsigned int micVolume, unsigned int speakerVolume) {}

    virtual void onAudioDeviceStatusChanged(ZoomVideoSDKAudioDeviceType type, ZoomVideoSDKAudioDeviceStatus status) {}

    virtual void onTestMicStatusChanged(ZoomVideoSDK_TESTMIC_STATUS status) {}

    virtual void onSelectedAudioDeviceChanged() {}

    virtual void onLiveTranscriptionStatus(ZoomVideoSDKLiveTranscriptionStatus status) {}

    /// \brief live transcription message received callback.
    /// \param ltMsg: an object pointer to the live transcription message content.
    /// \param pUser the pointer to the user who speak the message, see \link IZoomVideoSDKUser \endlink.
    /// \param type: the live transcription operation type. For more details, see \link ZoomVideoSDKLiveTranscriptionOperationType \endlink.
    virtual void onLiveTranscriptionMsgReceived(const zchar_t *ltMsg, IZoomVideoSDKUser *pUser, ZoomVideoSDKLiveTranscriptionOperationType type) {}

    /// \brief The translation message error callback.
    /// \param speakingLanguage: an object of the spoken message language.
    /// \param transcriptLanguageId: an object of the message language you want to translate.
    virtual void onLiveTranscriptionMsgError(ILiveTranscriptionLanguage *spokenLanguage, ILiveTranscriptionLanguage *transcriptLanguage) {}




    static int callNodeJSToSerialHelper(std::string local_url)
{
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, local_url.c_str());

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}
};

void joinVideoSDKSession(std::string &session_name, std::string &session_psw, std::string &session_token)
{
    video_sdk_obj = CreateZoomVideoSDKObj();
    ZoomVideoSDKInitParams init_params;
    init_params.domain = "https://go.zoom.us";
    init_params.enableLog = true;
    init_params.logFilePrefix = "zoom_videosdk_demo";
    init_params.videoRawDataMemoryMode = ZoomVideoSDKRawDataMemoryModeHeap;
    init_params.shareRawDataMemoryMode = ZoomVideoSDKRawDataMemoryModeHeap;
    init_params.audioRawDataMemoryMode = ZoomVideoSDKRawDataMemoryModeHeap;
    init_params.enableIndirectRawdata = false;

    ZoomVideoSDKErrors err = video_sdk_obj->initialize(init_params);
    if (err != ZoomVideoSDKErrors_Success)
    {
        return;
    }
    IZoomVideoSDKDelegate *listener = new ZoomVideoSDKDelegate();
    video_sdk_obj->addListener(dynamic_cast<IZoomVideoSDKDelegate *>(listener));
    ZoomVideoSDKSessionContext session_context;
    session_context.sessionName = session_name.c_str();
    session_context.sessionPassword = session_psw.c_str();
    session_context.userName = "Linux Bot";
    session_context.token = session_token.c_str();
    session_context.videoOption.localVideoOn = true;
    session_context.audioOption.connect = true;
    session_context.audioOption.mute = true;
    IZoomVideoSDKSession *session = NULL;
    if (video_sdk_obj)
        session = video_sdk_obj->joinSession(session_context);

       
}

void startLiveStreaming(){
    // Get the IZoomVideoSDKLiveStreamHelper to perform livestream actions.
    IZoomVideoSDKLiveStreamHelper* pLiveStreamHelper = video_sdk_obj->getLiveStreamHelper();

       // Check if live stream can start.
 if (pLiveStreamHelper->canStartLiveStream() == ZoomVideoSDKErrors_Success) {

    const zchar_t* strStreamUrl ="rtmp://a.rtmp.youtube.com/live2";
    const zchar_t* strKey ="6kft-yswg-uf68-0sj1-49gm";
    const zchar_t* strBroadcastUrl ="https://www.youtube.com/watch?v=oCJdsKSrTHo";
    // Call startLiveStream to begin live stream.
    int err = pLiveStreamHelper->startLiveStream(strStreamUrl, strKey, strBroadcastUrl);

        if (err == ZoomVideoSDKErrors_Success)
        {
            // Live stream successfully began.
              printf(" Live stream successfully began.\n");

        }
        else
        {
            // Live stream could not start.

              printf(" Live stream could not start.\n");

        }
}
}
void startCommandChannel(){

    IZoomVideoSDKCmdChannel* commandChannel = video_sdk_obj->getCmdChannel();
  commandChannel->sendCommand(NULL,"init");

}
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{

    //TODO dreamtcs improve if we have time
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    std::string response=(char*)contents;
    std::string response2= response.substr(14,response.length());
    FINALJWTToken =response2.substr(0,response2.length()-2);
    return size * nmemb;
}



int getJWTToken(std::string remote_url, std::string session_name){
  CURL *curl;
  CURLcode res;
  std::string readBuffer;
  
  char *json = NULL;
  struct curl_slist *headers = NULL;

  curl = curl_easy_init();
  if(curl) {
    //curl_easy_setopt(curl, CURLOPT_URL, "https://asdc.cc/video/");
    curl_easy_setopt(curl, CURLOPT_URL, remote_url.c_str());

    //buffer size
      curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, 120000L);
    //region for callback
    // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    // curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    // res = curl_easy_perform(curl);
    // curl_easy_cleanup(curl);
    //std::cout << readBuffer << std::endl;
    //region for call back

   //headers
   headers = curl_slist_append(headers, "Expect:");
   headers = curl_slist_append(headers, "Content-Type: application/json");
   curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  
   //std::string json = "{\"sessionName\":\"herochun6871\",\"role\":1,\"user_identity\":\"user_identity6871\",\"session_key\":\"session_key6871\"}";
   std::string json = "{\"sessionName\":\""+session_name+"\",\"role\":1,\"user_identity\":\"user_identity6871\",\"session_key\":\"session_key6871\"}";
   curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
   //callback
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    //perform
    res = curl_easy_perform(curl);
    std::cout << readBuffer << std::endl;
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* always cleanup */
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    
  }
  return 0;

}

gboolean timeout_callback(gpointer data)
{
    return TRUE;
}

void my_handler(int s)
{
    printf("\nCaught signal %d\n", s);
    video_sdk_obj->leaveSession(false);
    printf("Leaving session.\n");
}

int main(int argc, char *argv[])
{
    std::string self_dir = getSelfDirPath();
    printf("self path: %s\n", self_dir.c_str());
    self_dir.append("/config.json");

    std::ifstream t(self_dir.c_str());
    t.seekg(0, std::ios::end);
    size_t size = t.tellg();
    std::string buffer(size, ' ');
    t.seekg(0);
    t.read(&buffer[0], size);

    std::string session_name, session_psw, session_token, local_url, remote_url;
    do
    {
        Json config_json;
        try
        {
            config_json = Json::parse(buffer);
            printf("config all_content: %s\n", buffer.c_str());
        }
        catch (Json::parse_error &ex)
        {
            break;
        }

        if (config_json.is_null())
        {
            break;
        }


        Json json_name = config_json["session_name"];
        Json json_psw = config_json["session_psw"];
        Json json_token = config_json["token"];
        Json json_local_url = config_json["local_url_for_serial_control"];
        Json json_remote_url = config_json["remote_url_for_jwt_token"];
        if (!json_name.is_null())
        {
            session_name = json_name.get<std::string>();
            printf("config session_name: %s\n", session_name.c_str());
        }
        if (!json_psw.is_null())
        {
            session_psw = json_psw.get<std::string>();
            printf("config session_psw: %s\n", session_psw.c_str());
        }
        if (!json_token.is_null())
        {
            session_token = json_token.get<std::string>();
            printf("config session_token: %s\n", session_token.c_str());
        }

         if (!json_local_url.is_null())
        {
            local_url = json_local_url.get<std::string>();
            FINALLocalURL=local_url;
            printf("config local_url: %s\n", local_url.c_str());
        }

         if (!json_remote_url.is_null())
        {
            remote_url = json_remote_url.get<std::string>();
            printf("config remote_url: %s\n", remote_url.c_str());
        }
    } while (false);

    if (session_name.size() == 0 || session_token.size() == 0)
    {
        return 0;
    }
    getJWTToken(remote_url,session_name);
    printf("begin to join: %s\n", self_dir.c_str());
    //joinVideoSDKSession(session_name, session_psw, session_token);
    
    joinVideoSDKSession(session_name, session_psw, FINALJWTToken);
       startCommandChannel();
       
     startLiveStreaming();
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

    loop = g_main_loop_new(NULL, FALSE);

    // add source to default context
    g_timeout_add(100, timeout_callback, loop);
    g_main_loop_run(loop);
    return 0;
}
