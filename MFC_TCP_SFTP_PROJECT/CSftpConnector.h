#pragma once

using namespace std;

#include <vector>
#include <iostream>
#include <afxinet.h>
#include <CkGlobal.h>
#include <CkSFtp.h>


class CSftpConnector
{
private:
	const int SFTP_PORT = 22;
	const char* ID = "root";
	const char* PW = "root";
	const int FTP_PORT = 21;
	const char* LOCAL_DIR = "datafiles";

	bool m_bConnected;

public:
	CSftpConnector();
	bool UploadSftp(const char* chipIP, const char* chipPath, const char* selectedFileName);
	bool DownloadSftp(const char* chipIP, const char* chipPath, const char* selectedFileName);
	//BOOL UploadFtp(int index);
protected:
	bool InitializeSftp(CkSFtp& sftp, const char* chipIP);
	void FinalizeSftp(CkSFtp& sftp, bool success);
	char* MakeDevicePath(const char* relativePath);
	char* MakeSettingAppPath(const char* filename);
	//TCHAR* MakeDirectoryPathW(TCHAR* relativePath);
	//TCHAR* MakeAbsolutePathW(TCHAR* relativePath);
	void ChilkatUnlock();
};

