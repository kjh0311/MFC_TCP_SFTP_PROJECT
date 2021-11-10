#pragma once

using namespace std;

#include <vector>


// 매우 중요! (잘못하면 실제 스크립트 파일을 테스트용 가짜 스크립트 파일로 덮어씀)
//#define TARGET_FILENAME		"do-init.sh"
#define TARGET_FILENAME		"test.txt"


// 본 프로그램의 datafiles 폴더에 있는 selectedFileName에 해당하는 파일을 가져와서
// sftp://chipIP:22/chipPath로 전송한다.
struct Chip {
	// IP와 경로 (경로는 리눅스 절대경로 사용 가능)
	char* chipIP;
	char* chipPath;
	// 사용할 설정 파일
	char* selectedFileName;
};

struct Device {
	char* name;
	int tcpPort;
	vector<Chip> chips;
};

class CDeviceInfoManager {
public:
	const vector<Device> devices = {
		{"광대역 수신판 #1", 16500, {
			{"192.168.70.80", "/root/sd1", "do-init-광대역1-1.sh"},
			{"192.168.70.90", "/root/sd2", "do-init-광대역1-2.sh"}}},

		{"협대역 수신판 #1", 16500, {
			{"192.168.70.101", "/root/sd3", "do-init-협대역1-1.sh"},
			{"192.168.70.103", "/root/sd4", "do-init-협대역1-2.sh"}}},
		{"협대역 수신판 #2", 16500, {
			{"192.168.70.105", "/root/sd5", "do-init-협대역2-1.sh"},
			{"192.168.70.107", "/root/sd6", "do-init-협대역2-2.sh"}}},
		{"협대역 수신판 #3", 16500, {
			{"192.168.70.109", "/root/sd7", "do-init-협대역3-1.sh"},
			{"192.168.70.111", "/root/sd8", "do-init-협대역3-2.sh"}}},
		{"협대역 수신판 #4", 16500, {
			{"192.168.70.113", "/root/sd9", "do-init-협대역4-1.sh"},
			{"192.168.70.115", "/root/sd10", "do-init-협대역4-2.sh"}}},

		{"방향탐지기 수신판 #1", 16500, {
			{"192.168.70.11", "/root/sd11", "do-init-방향탐지기1-1.sh"},
			{"192.168.70.12", "/root/sd12", "do-init-방향탐지기1-2.sh"}}},
	};

	static CDeviceInfoManager& GetInstance() {
		static CDeviceInfoManager instance;
		return instance;
	}

	static const vector<Device>& GetDevices() {
		const vector<Device>* pDevices = &(GetInstance().devices);
		return *pDevices;
	}

	static const char* GetTargetFileName() {
		return TARGET_FILENAME;
	}
};

