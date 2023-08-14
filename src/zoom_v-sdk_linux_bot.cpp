    #include <limits.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <fstream>
    #include <iosfwd>
    #include <iostream>
    #include <signal.h>
    #include <stdlib.h>

    #include "glib.h"
    #include "json.hpp"
    #include "helpers/zoom_video_sdk_user_helper_interface.h"
    #include "zoom_video_sdk_api.h"
    #include "zoom_video_sdk_def.h"
    #include "zoom_video_sdk_delegate_interface.h"
    #include "zoom_video_sdk_interface.h"
  
    #include "zoom_video_sdk_platform.h"

    //needed for audio
    #include "ZoomVideoSDKVirtualAudioMic.h"
    #include "ZoomVideoSDKVirtualAudioSpeaker.h"
    #include "helpers/zoom_video_sdk_audio_send_rawdata_interface.h"

    //needed for share screen
    #include "ZoomVideoSDKShareSource.h"
    #include "helpers/zoom_video_sdk_share_helper_interface.h"

    //needed for get raw video
      #include "ZoomVideoSDKRawDataPipeDelegate.h"
    #include "ZoomVideoSDKVideoSource.h"
    #include "helpers/zoom_video_sdk_video_helper_interface.h"

    //needed for command channel
    #include "helpers/zoom_video_sdk_cmd_channel_interface.h"
 
    //needed for chat
    #include "helpers/zoom_video_sdk_chat_helper_interface.h"
    #include "zoom_video_sdk_chat_message_interface.h"

    //needed for LTT
    #include "zoom_video_sdk_session_info_interface.h"

    using Json = nlohmann::json;
    USING_ZOOM_VIDEO_SDK_NAMESPACE
    IZoomVideoSDK *video_sdk_obj;
    GMainLoop *loop;

    //these are controls to demonstrate the flow
    bool getRawAudio = false;
    bool getRawVideo = false;
    bool getRawShare = false;
    bool sendRawVideo = false;
    bool sendRawAudio = false;
    bool sendRawShare = false;
    bool enableCommandChannel = false;
    bool enableLiveStreaming = false;
    bool enableChat = true;
    bool enableCloudRecording = false;
    bool enableCallOut = false;
    bool enableLTT = true; //bug
    bool enableStatistics = true; //bug

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
        
      

        if (sendRawAudio){
             //needed for audio
            IZoomVideoSDKAudioHelper* m_pAudiohelper=  video_sdk_obj->getAudioHelper();
            if (m_pAudiohelper) {
                            // Connect User's audio.
                            printf("Starting Audio\n");
                            m_pAudiohelper->startAudio();
                            
                            
                            
                        }
        }
      
     
        

        if (sendRawShare){
            
            //needed for share source
            //this needs to be done after joing session
            ZoomVideoSDKShareSource* virtual_share_source = new ZoomVideoSDKShareSource();
            ZoomVideoSDKErrors err2= video_sdk_obj->getShareHelper()->startSharingExternalSource(virtual_share_source);    
            
                if (err2==ZoomVideoSDKErrors_Success){
                }
                else{
                   printf("Error setting external source %s\n", err2);
                }            
        };

        if (enableCommandChannel){

              IZoomVideoSDKCmdChannel* commandChannel = video_sdk_obj->getCmdChannel();
            commandChannel->sendCommand (NULL, "hello world");
        }
         if (enableLiveStreaming){

              IZoomVideoSDKLiveStreamHelper* pLiveStreamHelper = video_sdk_obj->getLiveStreamHelper();
                        // Check if live stream can start.
                if (pLiveStreamHelper->canStartLiveStream() == ZoomVideoSDKErrors_Success) {
                    zchar_t* streamUrl = "rtmp://a.rtmp.youtube.com/live2";
                    zchar_t* key = "xxxx-yswg-xxxx-0sj1-xxxx";
                    zchar_t* broadcastUrl = "https://studio.youtube.com/video/xxxx/livestreaming";

                    // Call startLiveStream to begin live stream.
                    int err = pLiveStreamHelper->startLiveStream(streamUrl, key, broadcastUrl);

                    if (err == ZoomVideoSDKErrors_Success)
                    {
                            // Live stream successfully began.
                    }
                    else
                    {
                            // Live stream could not start.
                    }
                }

        }

                 if (enableChat){

                    IZoomVideoSDKChatHelper* pChatHelper = video_sdk_obj->getChatHelper();
                            
                    // Check if chat is enabled in this session.
                    if (pChatHelper->isChatDisabled() == false && pChatHelper->isPrivateChatDisabled() == false) {
                        
                        // Send message to User.
                        pChatHelper->sendChatToAll("hello world");
                    }

                }


                if (enableCloudRecording){

                  IZoomVideoSDKRecordingHelper* m_pRecordhelper= video_sdk_obj->getRecordingHelper();
                  ZoomVideoSDKErrors err=   m_pRecordhelper->canStartRecording();
                  if(err==ZoomVideoSDKErrors_Success){
                    ZoomVideoSDKErrors err2=    m_pRecordhelper->startCloudRecording();

                    if (err2 != ZoomVideoSDKErrors_Success){

                        
                    }
                  }

                }

                if (enableCallOut){

                IZoomVideoSDKPhoneHelper* m_phonehelper= video_sdk_obj->getPhoneHelper();
                    if (m_phonehelper->isSupportPhoneFeature()){
                        
                        m_phonehelper->inviteByPhone("+65","12345678","alice");
                
                    }
                }
                if (enableLTT){
                    //needed for audio
                    IZoomVideoSDKAudioHelper* m_pAudiohelper=  video_sdk_obj->getAudioHelper();
                    if (m_pAudiohelper) {
                                    // Connect User's audio.
                                    printf("Starting Audio\n");
                                    m_pAudiohelper->startAudio();
                                    
                                    
                                    
                                }
                }

                if (enableLTT){
                IZoomVideoSDKSession* m_sessionhelper = video_sdk_obj->getSessionInfo();
                IZoomVideoSDKUser *user=   m_sessionhelper->getMyself();
                //IZoomVideoSDKUser* user=   m_sessionhelper->getRemoteUsers()->GetItem(0);
                if (user)
                {

                          IZoomVideoSDKLiveTranscriptionHelper* m_ltthelper= video_sdk_obj->getLiveTranscriptionHelper();
                         if (m_ltthelper){
                            //m_ltthelper->setSpokenLanguage(0);
                            //m_ltthelper->setTranslationLanguage(1);
                            bool canstartLTT = m_ltthelper->canStartLiveTranscription();
                            if (canstartLTT){
                                   ZoomVideoSDKErrors err= m_ltthelper->startLiveTranscription();
                                    //printf(">startLiveTranscription() status is : %s\n",err);
                            }
                         }//end if m_ltthelper
                        

                    
                }
                
            }
            if (enableStatistics){
                IZoomVideoSDKSession* m_sessionhelper = video_sdk_obj->getSessionInfo();
                
                ZoomVideoSDKSessionAudioStatisticInfo audioSendInfo;
	            ZoomVideoSDKSessionAudioStatisticInfo audiorecvInfo;
                m_sessionhelper->getSessionAudioStatisticInfo(audioSendInfo,audiorecvInfo);
                    audioSendInfo.frequency; 
                    audioSendInfo.latency; 
                    audioSendInfo.Jitter; 
                    audioSendInfo.packetLossAvg; 
                    audioSendInfo.packetLossMax; 

                    audiorecvInfo.frequency; 
                    audiorecvInfo.latency; 
                    audiorecvInfo.Jitter; 
                    audiorecvInfo.packetLossAvg; 
                    audiorecvInfo.packetLossMax; 


                ZoomVideoSDKSessionASVStatisticInfo shareSendInfo;
	            ZoomVideoSDKSessionASVStatisticInfo shareRecvInfo;
                m_sessionhelper->getSessionShareStatisticInfo(shareSendInfo, shareRecvInfo);
                	shareSendInfo.frame_width; 	
                    shareSendInfo.frame_height; 
                    shareSendInfo.fps; 
                    shareSendInfo.latency; 
                    shareSendInfo.Jitter; 
                    shareSendInfo.packetLossAvg; 
                    shareSendInfo.packetLossMax; 

                        shareRecvInfo.frame_width; 	
                    shareRecvInfo.frame_height; 
                    shareRecvInfo.fps; 
                    shareRecvInfo.latency; 
                    shareRecvInfo.Jitter; 
                    shareRecvInfo.packetLossAvg; 
                    shareRecvInfo.packetLossMax;


                ZoomVideoSDKSessionASVStatisticInfo sendInfo;
                ZoomVideoSDKSessionASVStatisticInfo recvInfo;
                m_sessionhelper->getSessionVideoStatisticInfo(sendInfo, recvInfo);
                	sendInfo.frame_width; 	
                    sendInfo.frame_height; 
                    sendInfo.fps; 
                    sendInfo.latency; 
                    sendInfo.Jitter; 
                    sendInfo.packetLossAvg; 
                    sendInfo.packetLossMax; 

                    recvInfo.frame_width; 	
                    recvInfo.frame_height; 
                    recvInfo.fps; 
                    recvInfo.latency; 
                    recvInfo.Jitter; 
                    recvInfo.packetLossAvg; 
                    recvInfo.packetLossMax; 

            }

            
    }
   


        /// \brief Triggered when session leaveSession
        virtual void onSessionLeave()
        {
            g_main_loop_unref(loop);
            printf("Already left session.\n");
            exit(1);
        };


        virtual void onError(ZoomVideoSDKErrors errorCode, int detailErrorCode)
        {
            printf("join session errorCode : %d  detailErrorCode: %d\n", errorCode, detailErrorCode);
        };


        virtual void onUserJoin(IZoomVideoSDKUserHelper *pUserHelper, IVideoSDKVector<IZoomVideoSDKUser *> *userList)
        {
            if (getRawVideo){
                if (userList)
                {
                    int count = userList->GetCount();
                    for (int index = 0; index < count; index++)
                    {
                        IZoomVideoSDKUser *user = userList->GetItem(index);
                        if (user)
                        {
                            ZoomVideoSDKRawDataPipeDelegate *encoder = new ZoomVideoSDKRawDataPipeDelegate(user);
                        }

                    }
                }
            }
      
              
        };

        virtual void onUserLeave(IZoomVideoSDKUserHelper *pUserHelper, IVideoSDKVector<IZoomVideoSDKUser *> *userList)
        {
               if (getRawVideo){
                    if (userList)
                    {
                        int count = userList->GetCount();
                        for (int index = 0; index < count; index++)
                        {
                            IZoomVideoSDKUser *user = userList->GetItem(index);
                            if (user)
                            {
                                ZoomVideoSDKRawDataPipeDelegate::stop_encoding_for(user);
                            }
                        }
                    }
               }
        
        };

   
        virtual void onUserVideoStatusChanged(IZoomVideoSDKVideoHelper *pVideoHelper,
                                            IVideoSDKVector<IZoomVideoSDKUser *> *userList){};


        virtual void onUserAudioStatusChanged(IZoomVideoSDKAudioHelper *pAudioHelper,
                                            IVideoSDKVector<IZoomVideoSDKUser *> *userList){

  if (getRawAudio){
            IZoomVideoSDKAudioHelper* m_pAudiohelper=  video_sdk_obj->getAudioHelper();
            if (m_pAudiohelper) {
            //needed for getting raw audio
            ZoomVideoSDKErrors err=  m_pAudiohelper->subscribe();
            printf("subscribe status is %d\n", err);
            }
        }

 };
        virtual void onUserShareStatusChanged(IZoomVideoSDKShareHelper *pShareHelper, IZoomVideoSDKUser *pUser, ZoomVideoSDKShareStatus status, ZoomVideoSDKShareType type) {

                                                if (getRawShare){
                                                    if (status == ZoomVideoSDKShareStatus_Start){
                                                          ZoomVideoSDKRawDataPipeDelegate *encoder = new ZoomVideoSDKRawDataPipeDelegate(pUser,true);
                                                    }
                                                    else if (status ==ZoomVideoSDKShareStatus_Stop){
                                                        ZoomVideoSDKRawDataPipeDelegate::stop_encoding_for(pUser,true);
                                                    }

                                                }

        }
   
         virtual void onUserRecordingConsent(IZoomVideoSDKUser* pUser) { };

 
        virtual void onLiveStreamStatusChanged(IZoomVideoSDKLiveStreamHelper *pLiveStreamHelper,
                                            ZoomVideoSDKLiveStreamStatus status){};


        virtual void onChatNewMessageNotify(IZoomVideoSDKChatHelper *pChatHelper, IZoomVideoSDKChatMessage *messageItem){

            if (enableChat){
                if (!messageItem)
                    return;

              
                const zchar_t* szMessageContent = messageItem->getContent();
                
            
                IZoomVideoSDKUser* pRecievingUser = messageItem->getReceiveUser();
                IZoomVideoSDKUser* pSendingUser = messageItem->getSendUser();
                 const zchar_t* sendUserName =pSendingUser->getUserName();
                 const zchar_t* recUserName="all";
                 if (pRecievingUser){
                  recUserName=pRecievingUser->getUserName();
                  }
                printf("New message from %s to %s  %s\n",  sendUserName, recUserName, szMessageContent);
          
            

                messageItem->isChatToAll(); // Returns false for private messages.
                messageItem->isSelfSend(); // Returns true if the current user sent the message.
                messageItem->getTimeStamp(); // The time at which the message was sent.
                messageItem->getReceiveUser(); // The recipient of a private message.


               //dreamtcs testing
               if (enableLTT){

          
                    size_t len = strlen(szMessageContent) + 1;
                    wchar_t* wstr = new wchar_t[len];
                    mbstowcs(wstr, szMessageContent, len);
                                
                

                    IZoomVideoSDKSession* m_sessionhelper = video_sdk_obj->getSessionInfo();
                    IZoomVideoSDKUser *user=   m_sessionhelper->getMyself();
                    //IZoomVideoSDKUser* user=   m_sessionhelper->getRemoteUsers()->GetItem(0);
                    if (user)
                        {

                                IZoomVideoSDKLiveTranscriptionHelper* m_ltthelper= video_sdk_obj->getLiveTranscriptionHelper();
                                if (m_ltthelper){
                                    if (wcscmp(wstr, L"set0")==0){
                                    m_ltthelper->setTranslationLanguage(-1);
                                
                                    }
                                         if (wcscmp(wstr, L"set1")==0){
                                    m_ltthelper->setTranslationLanguage(1);
                                
                                    }
                                    if (wcscmp(wstr, L"stopLTT")==0){
                                        m_ltthelper->stopLiveTranscription();
                                    }

                                    if (wcscmp(wstr, L"startLTT")==0){
                                            m_ltthelper->startLiveTranscription();
                                    }
                                    if (wcscmp(wstr, L"getSpoken")==0){
                                           ILiveTranscriptionLanguage *spokenLanguage =  m_ltthelper->getSpokenLanguage();
                                             printf("Spoken Language NAme: %s\n", spokenLanguage->getLTTLanguageName());
                                    }
                                    if (wcscmp(wstr, L"getLang")==0){
                                        IVideoSDKVector<ILiveTranscriptionLanguage*>* availableTranslateLanguages = m_ltthelper->getAvailableTranslationLanguages();
                                        IVideoSDKVector<ILiveTranscriptionLanguage*>* availableSpokenLanguages  =   m_ltthelper->getAvailableSpokenLanguages();



                                    if (availableTranslateLanguages) {
                                        for (size_t i = 0; i < availableTranslateLanguages->GetCount(); ++i) {
                                            ILiveTranscriptionLanguage* language = availableTranslateLanguages->GetItem(i);
                                            if (language) {
                                                printf("Translate Language ID: %d\n", language->getLTTLanguageID());
                                                printf("Translate Language Name: %s\n", language->getLTTLanguageName());
                                                // Print other properties as needed
                                                printf("---------------------\n");
                                            }
                                        }
                                    }

                                    if (availableSpokenLanguages) {
                                        for (size_t i = 0; i < availableSpokenLanguages->GetCount(); ++i) {
                                            ILiveTranscriptionLanguage* language = availableSpokenLanguages->GetItem(i);
                                            if (language) {
                                                printf("Spoken Language ID: %d\n", language->getLTTLanguageID());
                                                printf("Spoken Language Name: %s\n", language->getLTTLanguageName());
                                                // Print other properties as needed
                                                printf("---------------------\n");
                                            }
                                        }
                                    }

                                    }
                                }//end if m_ltthelper
                           }
                                

                            
                        
                        }


            }

        };

     
        virtual void onUserHostChanged(IZoomVideoSDKUserHelper *pUserHelper, IZoomVideoSDKUser *pUser){};

   
        virtual void onUserActiveAudioChanged(IZoomVideoSDKAudioHelper *pAudioHelper,
                                            IVideoSDKVector<IZoomVideoSDKUser *> *list){};

     
        virtual void onSessionNeedPassword(IZoomVideoSDKPasswordHandler *handler){};

      
        virtual void onSessionPasswordWrong(IZoomVideoSDKPasswordHandler *handler){};

        //this is a helper method, and not part of the implementation
        void savePcmBufferToFile(const std::string& filename, char* pcmBuffer, std::size_t bufferSize) {
            std::ofstream outfile(filename, std::ios::out | std::ios::binary | std::ios::app);
            outfile.write(reinterpret_cast<char*>(pcmBuffer), bufferSize);
            outfile.close();
            if (!outfile) {
                std::cerr << "Error writing PCM data to file!" << std::endl;
            } else {
                std::cout << "PCM data saved to file: " << filename << std::endl;
            }
        }

        virtual void onMixedAudioRawDataReceived(AudioRawData *data_){
            if (getRawAudio){

                    std::string filename = "output.pcm";

                    printf("onMixedAudioRawDataReceived\n");
                    if (data_){
                        savePcmBufferToFile(filename, data_->GetBuffer(),data_->GetBufferLen());
                        printf("Data buffer: %s\n", data_->GetBuffer());
                        printf("Length is : %d\n",data_->GetBufferLen());
                        printf("Sample is : %d\n",data_->GetSampleRate());
                        printf("Channel is : %d\n",data_->GetChannelNum());
                        }

            }   
        };


        virtual void onOneWayAudioRawDataReceived(AudioRawData *data_, IZoomVideoSDKUser *pUser){
          if (getRawAudio){
                std::string filename = pUser->getUserID();
                std::string extension = ".pcm";
                filename.append(extension);

                printf("onOneWayAudioRawDataReceived\n");
                if (data_){
                savePcmBufferToFile(filename, data_->GetBuffer(),data_->GetBufferLen());
                printf("Data buffer: %s\n", data_->GetBuffer());
                printf("Length is : %d\n",data_->GetBufferLen());
                printf("Sample is : %d\n",data_->GetSampleRate());
                printf("Channel is : %d\n",data_->GetChannelNum());
                }
          }
        };

        virtual void onSharedAudioRawDataReceived(AudioRawData *data_){};


        virtual void onUserManagerChanged(IZoomVideoSDKUser *pUser){};


        virtual void onUserNameChanged(IZoomVideoSDKUser *pUser){};


        virtual void onCameraControlRequestResult(IZoomVideoSDKUser *pUser, bool isApproved){};

        virtual void onCameraControlRequestReceived(
            IZoomVideoSDKUser *pUser,
            ZoomVideoSDKCameraControlRequestType requestType,
            IZoomVideoSDKCameraControlRequestHandler *pCameraControlRequestHandler){};


        virtual void onCommandReceived(IZoomVideoSDKUser *sender, const zchar_t *strCmd){
            if (enableCommandChannel){
            printf("onCommandReceived() Message: %s\n", strCmd);    
            }
        }
        virtual void onCommandChannelConnectResult(bool isSuccess){

             if (enableCommandChannel){
        
            }
        
        };
        virtual void onInviteByPhoneStatus(PhoneStatus status, PhoneFailedReason reason){};
        virtual void onCloudRecordingStatus(RecordingStatus status, IZoomVideoSDKRecordingConsentHandler* pHandler) {
                if (enableCloudRecording){


                }

        };
        virtual void onHostAskUnmute(){};


        virtual void onMultiCameraStreamStatusChanged(ZoomVideoSDKMultiCameraStreamStatus status, IZoomVideoSDKUser *pUser, IZoomVideoSDKRawDataPipe *pVideoPipe) {}
        virtual void onMicSpeakerVolumeChanged(unsigned int micVolume, unsigned int speakerVolume) {}
        virtual void onAudioDeviceStatusChanged(ZoomVideoSDKAudioDeviceType type, ZoomVideoSDKAudioDeviceStatus status) {}
        virtual void onTestMicStatusChanged(ZoomVideoSDK_TESTMIC_STATUS status) {}
        virtual void onSelectedAudioDeviceChanged() {}
  
        virtual void onLiveTranscriptionStatus(ZoomVideoSDKLiveTranscriptionStatus status) {
        if (enableLTT){
                printf("onLiveTranscriptionStatus() Status is : %d\n",status);
        }

        };
        virtual void onLiveTranscriptionMsgReceived(const zchar_t* ltMsg, IZoomVideoSDKUser* pUser, ZoomVideoSDKLiveTranscriptionOperationType type) {
                    if (enableLTT){
              //this is deprecating
              //printf("onLiveTranscriptionMsgReceived() Message is : %s\n",ltMsg);
              
        }
        };
        virtual void onLiveTranscriptionMsgInfoReceived(ILiveTranscriptionMessageInfo* messageInfo) {
                    if (enableLTT){
                printf("onLiveTranscriptionMsgInfoReceived() MessageInfoContent is : %s\n",messageInfo->getMessageContent());
                printf("onLiveTranscriptionMsgInfoReceived() MessageInfoType is : %d\n",messageInfo->getMessageType());
                
        }
        };
        virtual void onLiveTranscriptionMsgError(ILiveTranscriptionLanguage* spokenLanguage, ILiveTranscriptionLanguage* transcriptLanguage) {
                    if (enableLTT){
             printf("onLiveTranscriptionMsgError() LiveTranscriptionLanguage is : %s\n",transcriptLanguage->getLTTLanguageName());
        }
        };
        virtual void onChatMsgDeleteNotification(IZoomVideoSDKChatHelper* pChatHelper, const zchar_t* msgID, ZoomVideoSDKChatMessageDeleteType deleteBy){
            if (enableChat){


            }


        };
        virtual void onProxyDetectComplete() {};
        virtual void onProxySettingNotification(IZoomVideoSDKProxySettingHandler* handler){};
        virtual void onSSLCertVerifiedFailNotification(IZoomVideoSDKSSLCertificateInfo* info) {};	
        virtual void onUserVideoNetworkStatusChanged(ZoomVideoSDKNetworkStatus status, IZoomVideoSDKUser* pUser){};
    
    	virtual void onCallCRCDeviceStatusChanged(ZoomVideoSDKCRCCallStatus status) {};
        
       virtual void onVirtualSpeakerMixedAudioReceived(AudioRawData* data_){

                printf("onVirtualSpeakerMixedAudioReceived() main \n");
                printf("data %s \n",  data_->GetBuffer());

        };

        virtual void onVirtualSpeakerOneWayAudioReceived(AudioRawData* data_, IZoomVideoSDKUser* pUser) {

                 printf("onVirtualSpeakerOneWayAudioReceived() main\n");
                 printf("data %s \n",  data_->GetBuffer());
        };

        virtual void onVirtualSpeakerSharedAudioReceived(AudioRawData* data_) {
            printf("onVirtualSpeakerSharedAudioReceived() main\n");
                printf("data %s \n",  data_->GetBuffer());
        };

    virtual void onOriginalLanguageMsgReceived(ILiveTranscriptionMessageInfo* messageInfo){};
    virtual void onChatPrivilegeChanged(IZoomVideoSDKChatHelper* pChatHelper, ZoomVideoSDKChatPrivilegeType privilege){};
    virtual void onVideoCanvasSubscribeFail(ZoomVideoSDKSubscribeFailReason fail_reason, IZoomVideoSDKUser* pUser, void* handle){};
    virtual void onShareCanvasSubscribeFail(ZoomVideoSDKSubscribeFailReason fail_reason, IZoomVideoSDKUser* pUser, void* handle){};
    virtual void onAnnotationHelperCleanUp(IZoomVideoSDKAnnotationHelper* helper) {};
    virtual void onAnnotationPrivilegeChange(IZoomVideoSDKUser* pUser, bool enable) {};

    };



    void joinVideoSDKSession(std::string &session_name, std::string &session_psw, std::string &session_token)
    {
        ZoomVideoSDKRawDataMemoryMode heap = ZoomVideoSDKRawDataMemoryMode::ZoomVideoSDKRawDataMemoryModeHeap;
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
        session_context.audioOption.connect = false; 
        session_context.audioOption.mute = true;
 	
    
        if (getRawVideo){
            //nothing much to do before joining session
        }
        if (getRawShare){
            //nothing much to do before joining session
        }

        if (getRawAudio){
            //this code to load virtualaudiospeaker is needed if you are using headless linux, or linux which does not come with soundcard.
            //if you do not wish to load virtualaudiospeaker, you can alternatively install `apt install pulseaudio` on your linux distro
            //ZoomVideoSDKVirtualAudioSpeaker* vSpeaker  =new ZoomVideoSDKVirtualAudioSpeaker();
            //session_context.virtualAudioSpeaker =vSpeaker;
           
            session_context.audioOption.connect = true ;
       
    
            //dreamtcs check if this needed
            //ZoomVideoSDKVirtualAudioMic* vMic  =new ZoomVideoSDKVirtualAudioMic();
            //session_context.virtualAudioMic=vMic;
        }

        if (sendRawVideo){
            //needed for send raw video
            //the sdk uses a Video Source to send raw video
            //this needs to be done before joining session
            ZoomVideoSDKVideoSource* virtual_video_source = new ZoomVideoSDKVideoSource();
            session_context.externalVideoSource=virtual_video_source;
        }
        if (sendRawShare){
            //nothing much to do before joining session
        }


         if (sendRawAudio){
            session_context.audioOption.connect = true; //needed for sending raw audio data
            session_context.audioOption.mute = false; //needed for sending raw audio data

            //ZoomVideoSDKVirtualAudioMic is the object used to send audio
            ZoomVideoSDKVirtualAudioMic* vMic  =new ZoomVideoSDKVirtualAudioMic();
            session_context.virtualAudioMic=vMic;
        
        }
        	if (enableLTT) {
			session_context.audioOption.connect = true; //needed for sending raw audio data
			session_context.audioOption.mute = false; //needed for sending raw audio data

		}

        //join the session
        IZoomVideoSDKSession *session = NULL;
        if (video_sdk_obj)
            session = video_sdk_obj->joinSession(session_context);
            
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

        std::string session_name, session_psw, session_token;
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
        } while (false);

        if (session_name.size() == 0 || session_token.size() == 0)
        {
            return 0;
        }

        printf("begin to join: %s\n", self_dir.c_str());
        joinVideoSDKSession(session_name, session_psw, session_token);

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