
// Device713SettingDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFC_TCP_SFTP_PROJECT.h"
#include "MFC_TCP_SFTP_PROJECT_Dlg.h"
#include "afxdialogex.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDeviceSettingDlg 대화 상자



CDeviceSettingDlg::CDeviceSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEVICE713SETTING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDeviceSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDeviceSettingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHECK_CONNECTION, &CDeviceSettingDlg::OnBnClickedCheckConnection)
	ON_BN_CLICKED(IDC_APPLY_ALL, &CDeviceSettingDlg::OnBnClickedApplyAll)
END_MESSAGE_MAP()


// CDeviceSettingDlg 메시지 처리기

BOOL CDeviceSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// 작업 내용: 버튼 생성

	/*CStatic** m_pLabels;
	CStatic** m_pLamps;
	CComboBox** m_pSelectBoxes;
	CButton** m_pApplyButtons;*/	

	vector<Device> devices = CDeviceInfoManager::GetDevices();
	const size_t ITEMS = devices.size();

	const UINT
		LEFT = 30, TOP = 40,
		ITEM_HEIGHT = 40,
		BUTTON_HEIGHT = 25,

		LABEL_WIDTH = 160,
		LAMP_WIDTH = 40,
		SELECT_WIDTH = 180,
		APPLY_BUTTON_WIDTH = 70,
		DOWNLOAD_BUTTON_WIDTH = 120,

		SELECT_MARGIN = 10,
		BUTTON_MARGIN = 5,

		LABEL_LEFT = LEFT,
		LABEL_RIGHT = LABEL_LEFT + LABEL_WIDTH,

		LAMP_LEFT = LABEL_RIGHT,
		LAMP_RIGHT = LAMP_LEFT + LAMP_WIDTH,

		SELECT_LEFT = LAMP_RIGHT,
		SELECT_RIGHT = SELECT_LEFT + SELECT_WIDTH,

		APPLY_BUTTON_LEFT = SELECT_RIGHT + SELECT_MARGIN,
		APPLY_BUTTON_RIGHT = APPLY_BUTTON_LEFT + APPLY_BUTTON_WIDTH,

		DOWNLOAD_BUTTON_LEFT = APPLY_BUTTON_RIGHT + BUTTON_MARGIN,
		DOWNLOAD_BUTTON_RIGHT = DOWNLOAD_BUTTON_LEFT + DOWNLOAD_BUTTON_WIDTH
		;

	m_pLabels = new CStatic*[ITEMS];
	m_pLamps = new CStatic*[ITEMS];
	m_pSelectBoxes = new CComboBox*[ITEMS];
	m_pApplyButtons = new CButton*[ITEMS];
	m_pDownloadButtons = new CButton*[ITEMS];

	for (UINT i = 0; i < ITEMS; i++)
	{
		m_pLabels[i] = new CStatic;
		m_pLamps[i] = new CStatic;
		m_pSelectBoxes[i] = new CComboBox;
		m_pApplyButtons[i] = new CButton;
		m_pDownloadButtons[i] = new CButton;

		m_pLabels[i]->Create(CA2W(devices[i].name), WS_CHILD | WS_VISIBLE | SS_LEFT,
			CRect(LABEL_LEFT, TOP + i* ITEM_HEIGHT, LABEL_RIGHT, TOP + (i + 1) * ITEM_HEIGHT), this);

		m_pLamps[i]->Create(NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP,
			CRect(LAMP_LEFT, TOP + i * ITEM_HEIGHT, LAMP_RIGHT, TOP + (i + 1) * ITEM_HEIGHT), this);

		// CheckConncetion에서 그림을 입히므로 생략
		//SetBitmap(m_pLamps[i], IDB_NOT_CONNECTED);

		m_pSelectBoxes[i]->Create(CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE,
			CRect(SELECT_LEFT, TOP + i * ITEM_HEIGHT, SELECT_RIGHT, TOP + (i + 1) * ITEM_HEIGHT), this, NULL);
		for (UINT j = 0; j < ITEMS; j++)
		{
			m_pSelectBoxes[i]->AddString(CA2W(devices[j].name));
		}

		m_pApplyButtons[i]->Create(_T("적용"), WS_CHILD | WS_VISIBLE | SS_LEFT,
			CRect(APPLY_BUTTON_LEFT, TOP + i * ITEM_HEIGHT, APPLY_BUTTON_RIGHT, TOP + i * ITEM_HEIGHT + BUTTON_HEIGHT),
			this, IDC_APPLY_BUTTON_START + i);

		m_pDownloadButtons[i]->Create(_T("설정 가져오기"), WS_CHILD | WS_VISIBLE | SS_LEFT,
			CRect(DOWNLOAD_BUTTON_LEFT, TOP + i * ITEM_HEIGHT, DOWNLOAD_BUTTON_RIGHT, TOP + i * ITEM_HEIGHT + BUTTON_HEIGHT),
			this, IDC_DOWNLOAD_BUTTON_START + i);
	}

	CheckConnection();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}


// 리소스 뷰에서 추가함
void CDeviceSettingDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 작업내용: OnInitDialog에서 생성한 모든 버튼을 삭제
	vector<Device> devices = CDeviceInfoManager::GetDevices();
	const size_t ITEMS = devices.size();

	for (UINT i = 0; i < ITEMS; i++)
	{
		delete m_pLabels[i];
		delete m_pLamps[i];
		delete m_pSelectBoxes[i];
		delete m_pApplyButtons[i];
		delete m_pDownloadButtons[i];
	}
	delete[] m_pLabels;
	delete[] m_pLamps;
	delete[] m_pSelectBoxes;
	delete[] m_pApplyButtons;
	delete[] m_pDownloadButtons;
}

void CDeviceSettingDlg::OnBnClickedCheckConnection()
{
	CheckConnection();
}

void CDeviceSettingDlg::CheckConnection()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//AfxMessageBox(_T("연결 확인 버튼 클릭"));
	vector<Device> devices = CDeviceInfoManager::GetDevices();
	const size_t ITEMS = devices.size();
	Device device;
	bool connected;

	for (UINT i = 0; i < ITEMS; i++)
	{
		device = devices[i];
		connected = m_tcpConnector.Connect(device.chips[0].chipIP, device.tcpPort);
		if (connected)
		{
			SetBitmap(m_pLamps[i], IDB_CONNECTED);
		}
		else
		{
			SetBitmap(m_pLamps[i], IDB_NOT_CONNECTED);
		}
	}
}


void CDeviceSettingDlg::SetBitmap(CStatic *pLamp, const UINT IDB_BITMAP)
{
	CBitmap bitmap;
	HBITMAP oldBitmap;

	bitmap.LoadBitmap(IDB_BITMAP);
	oldBitmap = pLamp->SetBitmap((HBITMAP)bitmap.Detach());
	if (oldBitmap != NULL) DeleteObject(oldBitmap);
}


void CDeviceSettingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDeviceSettingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CDeviceSettingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




//void CDeviceSettingDlg::OnBnClickedApply()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//
//}


BOOL CDeviceSettingDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	vector<Device> devices = CDeviceInfoManager::GetDevices();
	const size_t ITEMS = devices.size();

	const UINT EVENT = HIWORD(wParam);
	const UINT BUTTON_ID = LOWORD(wParam);
	const UINT IDC_APPLY_BUTTON_END = IDC_APPLY_BUTTON_START + ITEMS-1;
	const UINT IDC_DOWNLOAD_BUTTON_END = IDC_DOWNLOAD_BUTTON_START + ITEMS - 1;

	if (EVENT == BN_CLICKED)
	{
		if (BUTTON_ID >= IDC_APPLY_BUTTON_START &&
			BUTTON_ID <= IDC_APPLY_BUTTON_END)
		{
			UINT targetIndex = BUTTON_ID - IDC_APPLY_BUTTON_START;
			UploadSFTP(devices, targetIndex);
		}
		else if (BUTTON_ID >= IDC_DOWNLOAD_BUTTON_START &&
				 BUTTON_ID <= IDC_DOWNLOAD_BUTTON_END)
		{
			UINT selectedIndex = BUTTON_ID - IDC_DOWNLOAD_BUTTON_START;
			Device selectedDevice = devices[selectedIndex];
			DownloadSFTP(selectedDevice);
		}


	}


	return CDialogEx::OnCommand(wParam, lParam);
}


void CDeviceSettingDlg::OnBnClickedApplyAll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	vector<Device> devices = CDeviceInfoManager::GetDevices();
	const size_t ITEMS = devices.size();

	for (UINT targetIndex = 0; targetIndex < ITEMS; targetIndex++)
	{
		UploadSFTP(devices, targetIndex);
	}

	CheckConnection();
}


//void CDeviceSettingDlg::UploadSftp()
//{
//	// TODO: 여기에 구현 코드 추가.
//}
void CDeviceSettingDlg::UploadSFTP(vector<Device> &devices, UINT targetIndex)
{
	// TODO: 여기에 구현 코드 추가.
	int selectedIndex = m_pSelectBoxes[targetIndex]->GetCurSel();
	if (selectedIndex >= 0)
	{
		Device targetDevice = devices[targetIndex];
		Device selectedDevice = devices[selectedIndex];
		vector<Chip> targetChips = targetDevice.chips;
		vector<Chip> selectedChips = selectedDevice.chips;

		const size_t TARGET_CHIP_NUM = targetChips.size();
		const size_t SELECTED_CHIP_NUM = selectedChips.size();

		if (TARGET_CHIP_NUM == SELECTED_CHIP_NUM)
		{
			char* chipIP;
			char* chipPath;
			char* selectedFileName;

			for (UINT i = 0; i < SELECTED_CHIP_NUM; i++)
			{
				chipIP = targetChips[i].chipIP;
				chipPath = targetChips[i].chipPath;
				selectedFileName = selectedChips[i].selectedFileName;

				m_sftpConncetor.UploadSftp(chipIP, chipPath, selectedFileName);
			}
		}
		else
		{
			char msg[100];
			char* targetName = targetDevice.name;
			char* selectedName = selectedDevice.name;
			sprintf_s(msg, 100,
				"%s 장치와 %s 장치는 칩의 갯수가 다르므로\n\
					 %s 장치를 %s 장치로 변경할 수 없습니다.",
				targetName, selectedName,
				targetName, selectedName);
			AfxMessageBox(CA2W(msg));
		}
	}
}


void CDeviceSettingDlg::DownloadSFTP(Device& selectedDevice)
{
	// TODO: 여기에 구현 코드 추가.	
	vector<Chip> selectedChips = selectedDevice.chips;
	const size_t SELECTED_CHIP_NUM = selectedChips.size();

	char name_filter[] = "쉘 스크립트 파일 (*.sh)|*.sh|모든 파일 (*.*)|*.*|";

	char* chipIP;
	char* chipPath;
	char* selectedFileName;

	for (UINT i = 0; i < SELECTED_CHIP_NUM; i++)
	{
		chipIP = selectedChips[i].chipIP;
		chipPath = selectedChips[i].chipPath;
		selectedFileName = selectedChips[i].selectedFileName;

		CFileDialog ins_dlg(FALSE, _T("sh"), CA2W(selectedFileName),
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT |
			OFN_NOCHANGEDIR, CA2W(name_filter), NULL);

		if (ins_dlg.DoModal() == IDOK)
		{
			//m_sftpConncetor.DownloadSftp(chipIP, chipPath, selectedFileName);
			char path[MAX_PATH];
			WideCharToMultiByte(CP_ACP, 0, ins_dlg.GetPathName(), MAX_PATH, path, MAX_PATH, NULL, NULL);
			m_sftpConncetor.DownloadSftp(chipIP, chipPath, path);
		}

	}
}


