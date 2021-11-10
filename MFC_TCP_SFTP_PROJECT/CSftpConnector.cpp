#include "pch.h"
#include "CSftpConnector.h"
#include "CDeviceInfoManager.h"

static const int TIMEOUT_MSEC = 3000;


CSftpConnector::CSftpConnector()
{
	ChilkatUnlock();
}


bool CSftpConnector::InitializeSftp(CkSFtp& sftp, const char* chipIP)
{
	// Set some timeouts, in milliseconds:
	sftp.put_ConnectTimeoutMs(TIMEOUT_MSEC);
	sftp.put_IdleTimeoutMs(TIMEOUT_MSEC);

	// Connect to the SSH server.  
	// The standard SSH port = 22
	// The hostname may be a hostname or IP address.
	bool success = sftp.Connect(chipIP, SFTP_PORT);
	if (success == true) {
		m_bConnected = true;

		// Authenticate with the SSH server.  Chilkat SFTP supports
		// both password-based authenication as well as public-key
		// authentication.  This example uses password authenication.
		success = sftp.AuthenticatePw(ID, PW);
		if (success == true) {
			// After authenticating, the SFTP subsystem must be initialized:
			success = sftp.InitializeSftp();
		}		
	}
	return success;
}


void CSftpConnector::FinalizeSftp(CkSFtp& sftp, bool success) {
	if (success == true) {
		std::cout << "Success." << "\r\n";
		//AfxMessageBox(_T("성공"));
	}
	else {
		std::cout << sftp.lastErrorText() << "\r\n";
		//AfxMessageBox(CA2W(sftp.lastErrorText()));
	}

	if (m_bConnected) {
		sftp.Disconnect();
	}
}



bool CSftpConnector::UploadSftp(const char* chipIP, const char* chipPath, const char* selectedFileName)
{
	CkSFtp sftp;

	bool success = InitializeSftp(sftp, chipIP);

	if (success == true) {
		// Upload from the local file to the SSH server.
		// Important -- the remote filepath is the 1st argument,
		// the local filepath is the 2nd argument;
		const char *settingAppFilePath = MakeSettingAppPath(selectedFileName);
		const char *deviceFilePath = MakeDevicePath(chipPath);

		success = sftp.UploadFileByName(deviceFilePath, settingAppFilePath);
		//success = sftp.UploadFileByName(settingAppFilePath, deviceFilePath);

		delete[] deviceFilePath;
		delete[] settingAppFilePath;
	}

	FinalizeSftp(sftp, success);

	return success;
}


bool CSftpConnector::DownloadSftp(const char* chipIP, const char* chipPath, const char* selectedFilePath)
{
	//AfxMessageBox(_T("SFTP 다운로드"));
	CkSFtp sftp;

	bool success = InitializeSftp(sftp, chipIP);

	if (success == true) {
		// Upload from the local file to the SSH server.
		// Important -- the remote filepath is the 1st argument,
		// the local filepath is the 2nd argument;
		const char *deviceFilePath = MakeDevicePath(chipPath);
		//const char *settingAppFilePath = MakeSettingAppPath(selectedFilePath);

		//success = sftp.DownloadFileByName(deviceFilePath, settingAppFilePath);
		success = sftp.DownloadFileByName(deviceFilePath, selectedFilePath);

		delete[] deviceFilePath;
		//delete[] settingAppFilePath;
	}

	FinalizeSftp(sftp, success);

	return success;
}


char* CSftpConnector::MakeDevicePath(const char* relativePath)
{
	char* absolutePath = new char[MAX_PATH];
	sprintf_s(absolutePath, MAX_PATH, "%s/%s", relativePath, CDeviceInfoManager::GetTargetFileName());
	return absolutePath;
}

char* CSftpConnector::MakeSettingAppPath(const char* filename)
{
	char* absolutePath = new char[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, absolutePath);
	sprintf_s(absolutePath, MAX_PATH, "%s/%s/%s", absolutePath, LOCAL_DIR, filename);
	return absolutePath;
}

//BOOL CSftpConnector::UploadFtp(int index)
//{
//	AfxMessageBox(_T("FTP 업로드"));
//	SftpUploadInfo info = UPLOAD_VECTOR[index];
//
//	CInternetSession session;
//	CFtpConnection* pConnection;
//	BOOL result = FALSE;
//
//	if (!AfxSocketInit()) // 소켓 초기화
//	{
//		AfxMessageBox(_T("소켓 초기화 실패"));
//		return FALSE;
//	}
//	else
//	{
//		
//	}
//	// CA2W 결과는 변수화 불가능
//
//
//	pConnection = session.GetFtpConnection(CA2W(IP), CA2W(ID), CA2W(PW), FTP_PORT);
//	if (!pConnection)
//	{
//		AfxMessageBox(_T("연결 실패"));
//		return FALSE;
//	}
//	else
//	{
//		AfxMessageBox(_T("소켓 초기화 성공"));
//
//		//TCHAR* remoteFilePath = MakeDirectoryPathW(CA2W(info.dst));
//		TCHAR* absoluteSrcPath = MakeAbsolutePathW(CA2W(info.src));
//		//AfxMessageBox(remoteFilePath);
//		AfxMessageBox(absoluteSrcPath);
//
//		// 디렉토리 존재 유무 검사가 목적
//		result = pConnection->SetCurrentDirectory(CA2W(DST_DIR));
//		if (result == FALSE)
//		{
//			AfxMessageBox(_T("디렉토리 생성"));
//			pConnection->CreateDirectory(CA2W(DST_DIR));
//			pConnection->SetCurrentDirectory(CA2W(DST_DIR));
//		}
//		else
//		{
//			AfxMessageBox(_T("디렉토리 생성 안 함"));
//			//result = pConnection->SetCurrentDirectory(_T(".."));
//		}
//
//		// 이거 result 디렉토리 없으면 전송 실패 처리되는데,
//		// 해야할 일은 FTP가 아니라, SFTP이므로 일단 안 고치고 넘어간다.
//		result = pConnection->PutFile(absoluteSrcPath, CA2W(info.dst));
//		if (result == FALSE)
//		{
//			AfxMessageBox(_T("전송 실패"));
//		}
//		else
//		{
//			AfxMessageBox(_T("전송 성공"));
//		}
//		//delete[] remoteFilePath;
//		delete[] absoluteSrcPath;
//		return result;
//
//		pConnection->Close();
//		delete pConnection;
//	}
//	session.Close();		
//
//	return TRUE;
//}
//
//
//TCHAR* CSftpConnector::MakeDirectoryPathW(TCHAR* relativePath)
//{
//	TCHAR* absolutePath = new TCHAR[MAX_PATH];
//	const int BUF_LEN = strlen(DST_DIR) + 1;
//	TCHAR* tDstDir = new TCHAR[BUF_LEN];
//
//	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, DST_DIR, BUF_LEN, tDstDir, BUF_LEN);
//
//	swprintf_s(absolutePath, MAX_PATH, L"/%s/%s", tDstDir, relativePath);
//	delete[] tDstDir;
//	return absolutePath;
//}
//
//
//// 사용 완료 후에는 delete[]로 반환해야함
//TCHAR* CSftpConnector::MakeAbsolutePathW(TCHAR* relativePath)
//{
//	TCHAR* absolutePath = new TCHAR[MAX_PATH];
//	GetCurrentDirectory(MAX_PATH, absolutePath);
//	return StrCat(absolutePath, relativePath);
//}


void CSftpConnector::ChilkatUnlock(void)
{
	// The Chilkat API can be unlocked for a fully-functional 30-day trial by passing any
	// string to the UnlockBundle method.  A program can unlock once at the start. Once unlocked,
	// all subsequently instantiated objects are created in the unlocked state. 
	// 
	// After licensing Chilkat, replace the "Anything for 30-day trial" with the purchased unlock code.
	// To verify the purchased unlock code was recognized, examine the contents of the LastErrorText
	// property after unlocking.  For example:
	CkGlobal glob;
	bool success = glob.UnlockBundle("Anything for 30-day trial");
	if (success != true) {
		std::cout << glob.lastErrorText() << "\r\n";
		return;
	}

	int status = glob.get_UnlockStatus();
	if (status == 2) {
		std::cout << "Unlocked using purchased unlock code." << "\r\n";
	}
	else {
		std::cout << "Unlocked in trial mode." << "\r\n";
	}

	// The LastErrorText can be examined in the success case to see if it was unlocked in
	// trial more, or with a purchased unlock code.
	std::cout << glob.lastErrorText() << "\r\n";
}