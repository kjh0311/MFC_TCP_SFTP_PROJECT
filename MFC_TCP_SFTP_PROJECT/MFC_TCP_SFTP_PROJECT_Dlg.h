
// Device713SettingDlg.h: 헤더 파일
//

#pragma once

#include "CTcpConnector.h"
#include "CSftpConnector.h"

// 레이블, 불빛, 콤보박스, 버튼 추가 및 이벤트 구현을 위해 추가함
#include "CDeviceInfoManager.h"


// CDeviceSettingDlg 대화 상자
class CDeviceSettingDlg : public CDialogEx
{
// 생성입니다.
public:
	CDeviceSettingDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEVICE713SETTING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;

	CFont   m_font;

	CStatic** m_pLabels;
	CStatic** m_pLamps;
	CComboBox** m_pSelectBoxes;
	CButton** m_pApplyButtons;
	CButton** m_pDownloadButtons;

	CTcpConnector m_tcpConnector;
	CSftpConnector m_sftpConncetor;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	void SetBitmap(CStatic *pLamp, const UINT IDB_BITMAP);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedCheckConnection();
	void CheckConnection();

//	afx_msg void OnBnClickedApply();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedApplyAll();

	void DownloadSFTP(Device& selectedDevice);
	void UploadSFTP(vector<Device> &devices, UINT targetIndex);
};
