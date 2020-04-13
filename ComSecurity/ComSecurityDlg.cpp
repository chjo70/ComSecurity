
// ComSecurityDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "ComSecurity.h"
#include "ComSecurityDlg.h"
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
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CComSecurityDlg 대화 상자




CComSecurityDlg::CComSecurityDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CComSecurityDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComSecurityDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_NETWORKCARD, m_CListNetwork);
	DDX_Control(pDX, IDC_IPADDRESS, m_IPv4);
	DDX_Control(pDX, IDC_DNSSERVER, m_DHCPServer);
	DDX_Control(pDX, IDC_STATIC_LEASEOBTAINEDTIME, m_CStaticLeaseObtainedTime);
	DDX_Control(pDX, IDC_STATIC_LEASETERMINATESTIME, m_CStaticLeaseTerminatesTime);
	DDX_Control(pDX, IDC_STATIC_NETWORKCARD, m_CStaticGroupNetworkcard);
	DDX_Control(pDX, IDC_GATEWAY, m_CGateway);
}

BEGIN_MESSAGE_MAP(CComSecurityDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CComSecurityDlg::OnHdnItemclickListNetworkcard)
	ON_NOTIFY(NM_CLICK, IDC_LIST_NETWORKCARD, &CComSecurityDlg::OnNMClickListNetworkcard)
	ON_BN_CLICKED(IDOK, &CComSecurityDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CComSecurityDlg 메시지 처리기

BOOL CComSecurityDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	InitControl();

	GetOSVersion();
	CheckOverComputer();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CComSecurityDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CComSecurityDlg::OnPaint()
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
HCURSOR CComSecurityDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CComSecurityDlg::InitControl()
{
	CRect rt;

	// 이미지
	m_CListNetwork.SetImageList(IDB_BITMAP_HEADER);

	m_CListNetwork.GetWindowRect(&rt);
	m_CListNetwork.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );


	//m_CListNetwork.SetColumnHeader(_T("Member ID, 100; Register Date, 140; Salary, 90, 2; FooBar, 120"));

	m_CListNetwork.InsertColumn(0, _T("순번"), LVCFMT_LEFT, (int) ( rt.Width()*0.12), -1 );
	m_CListNetwork.InsertColumn(1, _T("네트워크 카드"), LVCFMT_LEFT, (int) ( rt.Width() * 0.8) , -1);
	m_CListNetwork.InsertColumn(2, _T("기타"), LVCFMT_LEFT, (int) (rt.Width() * 0.07), -1);

	//m_CListNetwork.SetHeaderImageList(IDB_BITMAP_HEADER);
	//m_CListNetwork.SetHeaderImage(0, 0);
	//m_CListNetwork.SetHeaderImage(1, 0, FALSE);
	//m_CListNetwork.SetHeaderImage(2, 0);

	m_CListNetwork.SetGridLines(TRUE);
	//m_CListNetwork.SetCheckboxeStyle(RC_CHKBOX_NORMAL); // Enable checkboxes
}

/**
 * @brief     
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/04/01 22:08:41
 * @warning   
 */
void CComSecurityDlg::CheckOverComputer()
{

	CheckNetworkCards();

}

void CComSecurityDlg::CheckNetworkCards()
{
	UINT i, j=1;

	int nIndex;

	LONG    ret;  

	HKEY hKey;  

	char    data_buffer[256];  
	DWORD   data_type;  
	DWORD   data_size;  

	DWORD dwType;
	DWORD dwBytes=100;

	CString strTemp;

	TCHAR subKey[300];
	TCHAR szValue[300];

	if( ERROR_SUCCESS == RegOpenKeyEx( HKEY_LOCAL_MACHINE ,                // 키 값  
		_T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\NetworkList\\Profiles"),    // 서브 키값   
		0,                                                  // 옵션 항상 0  
		KEY_READ,                                    // 접근 권한  
		&hKey                                               // 키 핸들  
		) ) {

	}  
	else {
		//AfxMessageBox( _T("Register Open Error") );
	}


	m_vecNetworkCard.clear();
	for( i=1 ; i < 100 ; ++i ) {
		STR_NETWORKCARD strNetworkCard;

		wsprintf( subKey, _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\NetworkCards\\%d") , i );
		if( ERROR_SUCCESS == RegOpenKeyEx( HKEY_LOCAL_MACHINE ,                // 키 값  
			subKey,
			0,                                                  // 옵션 항상 0  
			KEY_READ,                                    // 접근 권한  
			&hKey                                               // 키 핸들  
			) ) {
			strNetworkCard.strDescription = _T("");
			strNetworkCard.strServiceName = _T("");

			strNetworkCard.strIP4v = _T("");
			strNetworkCard.strDhcpNameServer = _T("");
			strNetworkCard.strDhcpServer = _T("");
			strNetworkCard.strGateway = _T("");
			strNetworkCard.tiLeaseObtainedTime = 0;
			strNetworkCard.tiLeaseTerminatesTime = 0;

			// Read Regstry Key
			ret = RegQueryValueEx( hKey, _T("ServiceName"), 0, &dwType, (LPBYTE) szValue, &dwBytes);
			strNetworkCard.strServiceName = szValue;

			ret = RegQueryValueEx( hKey, _T("Description"), 0, &dwType, (LPBYTE) szValue, &dwBytes);
			strNetworkCard.strDescription = szValue;

			m_vecNetworkCard.push_back( strNetworkCard );
			
			// 목록창에 전시
			strTemp.Format( _T("%d"), j++ );
			nIndex = m_CListNetwork.InsertItemEx(INT_MAX, strTemp, strNetworkCard.strDescription, "" );
			m_CListNetwork.SetItemImage( nIndex, 0, 4 );
			m_CListNetwork.SetItemImage( nIndex, 1, 0 );
// 			nIndex = m_CListNetwork.InsertItem( INT_MAX, strTemp, NULL );
// 			//m_CListNetwork.SetItemImage( nIndex, 1, 100 );
// 			
// 			m_CListNetwork.SetItem( nIndex, 1, LVIF_TEXT, szValue, 1, NULL, NULL, NULL);
// 			m_CListNetwork.SetItemImage( nIndex, 1, 0 );

		}  
		else {
			
		}
	}

	UINT uiVecSize=m_vecNetworkCard.size();
	vector<STR_NETWORKCARD>::pointer ptrNetworkCard;

	ptrNetworkCard = m_vecNetworkCard.data();
	for( i=0 ; i < uiVecSize ; ++i ) {
		wsprintf( subKey, _T("SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters\\Interfaces\\%s") , (*ptrNetworkCard).strServiceName );
		if( ERROR_SUCCESS == RegOpenKeyEx( HKEY_LOCAL_MACHINE ,                // 키 값  
			subKey,
			0,                                                  // 옵션 항상 0  
			KEY_READ,                                    // 접근 권한  
			&hKey                                               // 키 핸들  
			) ) {
			ret = RegQueryValueEx( hKey, _T("DhcpNameServer"), 0, &dwType, (LPBYTE) szValue, &dwBytes);
			(*ptrNetworkCard).strDhcpNameServer = szValue;

			ret = RegQueryValueEx( hKey, _T("DhcpIPAddress"), 0, &dwType, (LPBYTE) szValue, &dwBytes);
			(*ptrNetworkCard).strIP4v = szValue;

			ret = RegQueryValueEx( hKey, _T("DhcpServer"), 0, &dwType, (LPBYTE) szValue, &dwBytes);
			(*ptrNetworkCard).strDhcpServer = szValue;

			ret = RegQueryValueEx( hKey, _T("DhcpDefaultGateway"), 0, &dwType, (LPBYTE) szValue, &dwBytes);
			(*ptrNetworkCard).strGateway = szValue;

			ret = RegQueryValueEx( hKey, _T("LeaseObtainedTime"), 0, &dwType, (LPBYTE) szValue, &dwBytes);
			(*ptrNetworkCard).tiLeaseObtainedTime = szValue[0] | ( szValue[1] << 16 );

			ret = RegQueryValueEx( hKey, _T("LeaseTerminatesTime"), 0, &dwType, (LPBYTE) szValue, &dwBytes);
			(*ptrNetworkCard).tiLeaseTerminatesTime = szValue[0] | ( szValue[1] << 16 );
			
		}
		
		
		++ ptrNetworkCard;
	}

	strTemp.Format( _T("%d개의 네트워크 카드"), uiVecSize );
	m_CStaticGroupNetworkcard.SetWindowTextW( strTemp );

}

/**
 * @brief     
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/04/01 22:15:02
 * @warning   
 */
enOS CComSecurityDlg::GetOSVersion()
{
	enOS enWhatOS=enWindows_Unknown;
	OSVERSIONINFO osvi;

	ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osvi);

	switch( osvi.dwMajorVersion ) {
	case 5 :
		if( osvi.dwMinorVersion == 0 ) {
			enWhatOS = enWindows_2000;
		}
		else if( osvi.dwMinorVersion == 1 ) {
			enWhatOS = enWindows_XP;
		}
		else if( osvi.dwMinorVersion == 2 ) {
			if( GetSystemMetrics(SM_SERVERR2) != 0 )
				enWhatOS = enWindows_Server_2003_R2;
			else
				enWhatOS = enWindows_Server_2003;
		}

	case 6 :
		break;
	}

	return enWhatOS;
}


void CComSecurityDlg::OnHdnItemclickListNetworkcard(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}

static TCHAR weekday[10][10] = { _T("일"), _T("월"), _T("화"), _T("수"), _T("목"), _T("금"), _T("토") } ;
void CComSecurityDlg::OnNMClickListNetworkcard(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iSelItem;
	int nField1, nField2, nField3, nField4;

	struct tm *pTimeInfo;

	CString strTemp;

	STR_NETWORKCARD stNetworkCard;

	strTemp = m_CListNetwork.GetItemText( pNMItemActivate->iItem, 0 );
	swscanf( strTemp.GetBuffer(), _T("%d"), & iSelItem );

	if( iSelItem >= 0 ) {
		stNetworkCard = m_vecNetworkCard.at(iSelItem-1);

		swscanf( stNetworkCard.strIP4v.GetBuffer(), _T("%d.%d.%d.%d"), & nField1, & nField2, & nField3, & nField4 );
		m_IPv4.SetAddress( nField1, nField2, nField3, nField4 );

		swscanf( stNetworkCard.strDhcpNameServer.GetBuffer(), _T("%d.%d.%d.%d"), & nField1, & nField2, & nField3, & nField4 );
		m_DHCPServer.SetAddress( nField1, nField2, nField3, nField4 );

		swscanf( stNetworkCard.strGateway.GetBuffer(), _T("%d.%d.%d.%d"), & nField1, & nField2, & nField3, & nField4 );
		m_CGateway.SetAddress( nField1, nField2, nField3, nField4 );

		if( stNetworkCard.tiLeaseObtainedTime != 0 ) {
			pTimeInfo = localtime( & stNetworkCard.tiLeaseObtainedTime );
			strTemp.Format( _T("%d년 %d월 %d일 %s요일 %d시 %d분 %d초"), pTimeInfo->tm_year+1900, pTimeInfo->tm_mon+1, pTimeInfo->tm_mday, weekday[ pTimeInfo->tm_wday ], pTimeInfo->tm_hour, pTimeInfo->tm_min, pTimeInfo->tm_sec );
		}
		else {
			strTemp = _T("기록 없음");
		}
		m_CStaticLeaseObtainedTime.SetWindowText( strTemp );

		if( stNetworkCard.tiLeaseTerminatesTime != 0 ) {
			pTimeInfo = localtime( & stNetworkCard.tiLeaseTerminatesTime );
			strTemp.Format( _T("%d년 %d월 %d일 %s요일 %d시 %d분 %d초"), pTimeInfo->tm_year+1900, pTimeInfo->tm_mon+1, pTimeInfo->tm_mday, weekday[ pTimeInfo->tm_wday ], pTimeInfo->tm_hour, pTimeInfo->tm_min, pTimeInfo->tm_sec );
		}
		else {
			strTemp = _T("기록 없음");
		}
		m_CStaticLeaseTerminatesTime.SetWindowText( strTemp );

	}

	*pResult = 0;
}


/**
 * @brief     
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/04/14 0:13:20
 * @warning   
 */
void CComSecurityDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_CListNetwork.DeleteAllItems();

	GetOSVersion();
	CheckOverComputer();

	DisplaySecurityResult();
	//CDialogEx::OnOK();
}

void CComSecurityDlg::DisplaySecurityResult()
{

}