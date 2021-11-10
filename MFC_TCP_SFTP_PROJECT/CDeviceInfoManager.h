#pragma once

using namespace std;

#include <vector>


// �ſ� �߿�! (�߸��ϸ� ���� ��ũ��Ʈ ������ �׽�Ʈ�� ��¥ ��ũ��Ʈ ���Ϸ� ���)
//#define TARGET_FILENAME		"do-init.sh"
#define TARGET_FILENAME		"test.txt"


// �� ���α׷��� datafiles ������ �ִ� selectedFileName�� �ش��ϴ� ������ �����ͼ�
// sftp://chipIP:22/chipPath�� �����Ѵ�.
struct Chip {
	// IP�� ��� (��δ� ������ ������ ��� ����)
	char* chipIP;
	char* chipPath;
	// ����� ���� ����
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
		{"���뿪 ������ #1", 16500, {
			{"192.168.70.80", "/root/sd1", "do-init-���뿪1-1.sh"},
			{"192.168.70.90", "/root/sd2", "do-init-���뿪1-2.sh"}}},

		{"���뿪 ������ #1", 16500, {
			{"192.168.70.101", "/root/sd3", "do-init-���뿪1-1.sh"},
			{"192.168.70.103", "/root/sd4", "do-init-���뿪1-2.sh"}}},
		{"���뿪 ������ #2", 16500, {
			{"192.168.70.105", "/root/sd5", "do-init-���뿪2-1.sh"},
			{"192.168.70.107", "/root/sd6", "do-init-���뿪2-2.sh"}}},
		{"���뿪 ������ #3", 16500, {
			{"192.168.70.109", "/root/sd7", "do-init-���뿪3-1.sh"},
			{"192.168.70.111", "/root/sd8", "do-init-���뿪3-2.sh"}}},
		{"���뿪 ������ #4", 16500, {
			{"192.168.70.113", "/root/sd9", "do-init-���뿪4-1.sh"},
			{"192.168.70.115", "/root/sd10", "do-init-���뿪4-2.sh"}}},

		{"����Ž���� ������ #1", 16500, {
			{"192.168.70.11", "/root/sd11", "do-init-����Ž����1-1.sh"},
			{"192.168.70.12", "/root/sd12", "do-init-����Ž����1-2.sh"}}},
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

