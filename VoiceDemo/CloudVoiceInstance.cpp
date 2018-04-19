#include "stdafx.h"
#include "CloudVoiceInstance.h"


#define APPID "1344036499"
#define  APPKEY "5562eda69154615c15cd612eb18aee44"

#define GUID_LEN 64


CloudVoiceInstance::CloudVoiceInstance()
{
	mInstanceErrorCode = GV_ON_NET_ERR;
	mInstanceState = FALSE;
}


CloudVoiceInstance::~CloudVoiceInstance()
{
}



BOOL CloudVoiceInstance::Init()
{
	//³õÊ¼»¯
	 mCloudEngine = GetVoiceEngine();
	 if (!mCloudEngine)
	 {

		 mErrorCode = 1;
		 return FALSE;
	 }
	 string OpenID = getGuid();
	 if (OpenID.size() == 0)
	 {
		 mErrorCode = 100;
		 return FALSE;
	 }
	 GCloudVoiceErrno  errorCode = GCLOUD_VOICE_SUCC;
	 if (GCLOUD_VOICE_SUCC != (errorCode = mCloudEngine->SetAppInfo(APPID, APPKEY, OpenID.c_str())))
	 {
		 mErrorCode =  (DWORD)errorCode;
		 return FALSE;
	 }

	 if (GCLOUD_VOICE_SUCC != (errorCode= mCloudEngine->Init()))
	 {
		 mErrorCode = (DWORD)errorCode;
		 return FALSE;
	 }

	 CloudVoiceNotify * pNotiy = new CloudVoiceNotify(this);
	 if (!pNotiy )
	 {
		 mErrorCode = 101;
		 return FALSE;
	 }

	 mCloudEngine->SetNotify(pNotiy);

	 if (GCLOUD_VOICE_SUCC != (errorCode = mCloudEngine->SetMode(IGCloudVoiceEngine::RealTime)))
	 {
		 mErrorCode = (DWORD)errorCode;
		 return FALSE;
	 }

	 if (GCLOUD_VOICE_SUCC != (errorCode = mCloudEngine->ApplyMessageKey()))
	 {
		 mErrorCode = (DWORD)errorCode;
		 return FALSE;
	 }

	 mCloudEngine->CloseMic();
	 mCloudEngine->OpenSpeaker();
	 //mCloudEngine->SetMicVolume(100);
	 return TRUE;
}

void CloudVoiceInstance::SetErroInfo(BOOL bState, GCloudVoiceCompleteCode code)
{
	mInstanceErrorCode = code;
	mInstanceState = bState;
}

gcloud_voice::IGCloudVoiceEngine* CloudVoiceInstance::GetEngine()
{
	if (mInstanceState)
	{
		return mCloudEngine;
	}
	return NULL;
}

void CloudVoiceInstance::setReady()
{
	if (!mCloudEngine)
	{
		return;
	}
}

void CloudVoiceInstance::setRoomStatus(GCloudVoiceCompleteCode roomCode)
{
	mRoomStatus = roomCode; 
}

BOOL CloudVoiceInstance::joinRoom(const char *pRoomName)
{
	if (!mInstanceState)
	{
		return FALSE;
	}
	GCloudVoiceErrno resCode  = mCloudEngine->JoinTeamRoom(pRoomName, 5000);
	if (resCode != GCLOUD_VOICE_SUCC)
	{
		return FALSE;
	}
	return TRUE;
}

void CloudVoiceInstance::Poll()
{
	if (mCloudEngine)
	{
		mCloudEngine->Poll();
	}
}

BOOL CloudVoiceInstance::openMic()
{
	if (mRoomStatus == GV_ON_JOINROOM_SUCC &&mInstanceState)
	{
		mCloudEngine->OpenMic();
		return FALSE;
	}
	return FALSE;
}

BOOL CloudVoiceInstance::closeMc()
{
	if (mRoomStatus == GV_ON_JOINROOM_SUCC &&mInstanceState)
	{
		mCloudEngine->CloseMic();
		return TRUE;
	}
	return FALSE;
}

std::string CloudVoiceInstance::getGuid()
{
	string strRes = "";
	char buffer[GUID_LEN] = { 0 };
	GUID guid;

	if (CoCreateGuid(&guid))
	{
		fprintf(stderr, "create guid error\n");
		return strRes;
	}
	sprintf_s(buffer,"%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",guid.Data1, guid.Data2, guid.Data3,guid.Data4[0], guid.Data4[1], guid.Data4[2],guid.Data4[3], guid.Data4[4], guid.Data4[5],guid.Data4[6], guid.Data4[7]);
	strRes = buffer;
	return strRes;
}


CloudVoiceNotify::CloudVoiceNotify(CloudVoiceInstance* pInstance)
{
	m_pVoiceInstance = pInstance;
}

CloudVoiceNotify::~CloudVoiceNotify()
{
}

void CloudVoiceNotify::OnJoinRoom(GCloudVoiceCompleteCode code, const char *roomName, int memberID)
{
	IGCloudVoiceNotify::OnJoinRoom(code, roomName, memberID);
	BOOL bStatus = code == GV_ON_JOINROOM_SUCC ? TRUE : FALSE;
	m_pVoiceInstance->setRoomStatus(code);
	m_pVoiceInstance->SetErroInfo(bStatus, code);
}

void CloudVoiceNotify::OnStatusUpdate(GCloudVoiceCompleteCode status, const char *roomName, int memberID)
{
	IGCloudVoiceNotify::OnStatusUpdate(status, roomName, memberID);
}

void CloudVoiceNotify::OnQuitRoom(GCloudVoiceCompleteCode code, const char *roomName)
{
	IGCloudVoiceNotify::OnQuitRoom(code, roomName);
}

void CloudVoiceNotify::OnMemberVoice(const unsigned int *members, int count)
{
	IGCloudVoiceNotify::OnMemberVoice(members, count);
	int nArraycount = sizeof(members);
	int na2 =  sizeof(members[0]);
	if (count > 1)
	{
		for (int i = 0; i < count+1; ++i)
		{
			unsigned int nst = members[i * 2];
			unsigned int  nid = members[i * 2 + 1];
		}
	}

}

void CloudVoiceNotify::OnMemberVoice(const char *roomName, unsigned int member, int status)
{
	IGCloudVoiceNotify::OnMemberVoice(roomName, member, status);
}

void CloudVoiceNotify::OnUploadFile(GCloudVoiceCompleteCode code, const char *filePath, const char *fileID)
{
	IGCloudVoiceNotify::OnUploadFile(code, filePath, fileID);
}

void CloudVoiceNotify::OnDownloadFile(GCloudVoiceCompleteCode code, const char *filePath, const char *fileID)
{
	IGCloudVoiceNotify::OnDownloadFile(code, filePath, fileID);
}

void CloudVoiceNotify::OnPlayRecordedFile(GCloudVoiceCompleteCode code, const char *filePath)
{
	IGCloudVoiceNotify::OnPlayRecordedFile(code,filePath);
}

void CloudVoiceNotify::OnApplyMessageKey(GCloudVoiceCompleteCode code)
{
	IGCloudVoiceNotify::OnApplyMessageKey(code);

	BOOL bStatus = GCloudVoiceCompleteCode::GV_ON_MESSAGE_KEY_APPLIED_SUCC == code ? TRUE : FALSE;
	
	if (bStatus)
	{
		m_pVoiceInstance->setReady();
	}
	m_pVoiceInstance->SetErroInfo(bStatus, code);
}

void CloudVoiceNotify::OnSpeechToText(GCloudVoiceCompleteCode code, const char *fileID, const char *result)
{
	IGCloudVoiceNotify::OnSpeechToText(code, fileID, result);
}

void CloudVoiceNotify::OnRecording(const unsigned char* pAudioData, unsigned int nDataLength)
{
	IGCloudVoiceNotify::OnRecording(pAudioData, nDataLength);
}

void CloudVoiceNotify::OnStreamSpeechToText(GCloudVoiceCompleteCode code, int error, const char *result, const char *voicePath)
{
	IGCloudVoiceNotify::OnStreamSpeechToText(code, error, result, voicePath);
}

void CloudVoiceNotify::OnRoleChanged(GCloudVoiceCompleteCode code, const char *roomName, int memberID, int role)
{
	IGCloudVoiceNotify::OnRoleChanged(code, roomName, memberID, role);
}
