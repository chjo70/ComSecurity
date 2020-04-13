
// ComSecurityDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ComSecurity.h"
#include "ComSecurityDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CComSecurityDlg ��ȭ ����




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


// CComSecurityDlg �޽��� ó����

BOOL CComSecurityDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	InitControl();

	GetOSVersion();
	CheckOverComputer();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CComSecurityDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CComSecurityDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CComSecurityDlg::InitControl()
{
	CRect rt;

	// �̹���
	m_CListNetwork.SetImageList(IDB_BITMAP_HEADER);

	m_CListNetwork.GetWindowRect(&rt);
	m_CListNetwork.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );


	//m_CListNetwork.SetColumnHeader(_T("Member ID, 100; Register Date, 140; Salary, 90, 2; FooBar, 120"));

	m_CListNetwork.InsertColumn(0, _T("����"), LVCFMT_LEFT, (int) ( rt.Width()*0.12), -1 );
	m_CListNetwork.InsertColumn(1, _T("��Ʈ��ũ ī��"), LVCFMT_LEFT, (int) ( rt.Width() * 0.8) , -1);
	m_CListNetwork.InsertColumn(2, _T("��Ÿ"), LVCFMT_LEFT, (int) (rt.Width() * 0.07), -1);

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
 * @author    ��ö�� (churlhee.jo@lignex1.com)
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

	if( ERROR_SUCCESS == RegOpenKeyEx( HKEY_LOCAL_MACHINE ,                // Ű ��  
		_T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\NetworkList\\Profiles"),    // ���� Ű��   
		0,                                                  // �ɼ� �׻� 0  
		KEY_READ,                                    // ���� ����  
		&hKey                                               // Ű �ڵ�  
		) ) {

	}  
	else {
		//AfxMessageBox( _T("Register Open Error") );
	}


	m_vecNetworkCard.clear();
	for( i=1 ; i < 100 ; ++i ) {
		STR_NETWORKCARD strNetworkCard;

		wsprintf( subKey, _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\NetworkCards\\%d") , i );
		if( ERROR_SUCCESS == RegOpenKeyEx( HKEY_LOCAL_MACHINE ,                // Ű ��  
			subKey,
			0,                                                  // �ɼ� �׻� 0  
			KEY_READ,                                    // ���� ����  
			&hKey                                               // Ű �ڵ�  
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
			
			// ���â�� ����
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
		if( ERROR_SUCCESS == RegOpenKeyEx( HKEY_LOCAL_MACHINE ,                // Ű ��  
			subKey,
			0,                                                  // �ɼ� �׻� 0  
			KEY_READ,                                    // ���� ����  
			&hKey                                               // Ű �ڵ�  
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

	strTemp.Format( _T("%d���� ��Ʈ��ũ ī��"), uiVecSize );
	m_CStaticGroupNetworkcard.SetWindowTextW( strTemp );

}

/**
 * @brief     
 * @return    void
 * @author    ��ö�� (churlhee.jo@lignex1.com)
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}

static TCHAR weekday[10][10] = { _T("��"), _T("��"), _T("ȭ"), _T("��"), _T("��"), _T("��"), _T("��") } ;
void CComSecurityDlg::OnNMClickListNetworkcard(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
			strTemp.Format( _T("%d�� %d�� %d�� %s���� %d�� %d�� %d��"), pTimeInfo->tm_year+1900, pTimeInfo->tm_mon+1, pTimeInfo->tm_mday, weekday[ pTimeInfo->tm_wday ], pTimeInfo->tm_hour, pTimeInfo->tm_min, pTimeInfo->tm_sec );
		}
		else {
			strTemp = _T("��� ����");
		}
		m_CStaticLeaseObtainedTime.SetWindowText( strTemp );

		if( stNetworkCard.tiLeaseTerminatesTime != 0 ) {
			pTimeInfo = localtime( & stNetworkCard.tiLeaseTerminatesTime );
			strTemp.Format( _T("%d�� %d�� %d�� %s���� %d�� %d�� %d��"), pTimeInfo->tm_year+1900, pTimeInfo->tm_mon+1, pTimeInfo->tm_mday, weekday[ pTimeInfo->tm_wday ], pTimeInfo->tm_hour, pTimeInfo->tm_min, pTimeInfo->tm_sec );
		}
		else {
			strTemp = _T("��� ����");
		}
		m_CStaticLeaseTerminatesTime.SetWindowText( strTemp );

	}

	*pResult = 0;
}


/**
 * @brief     
 * @return    void
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/04/14 0:13:20
 * @warning   
 */
void CComSecurityDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_CListNetwork.DeleteAllItems();

	GetOSVersion();
	CheckOverComputer();

	DisplaySecurityResult();
	//CDialogEx::OnOK();
}

void CComSecurityDlg::DisplaySecurityResult()
{

}