
// ComSecurityDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"

#include "./ListCtrl/ReportCtrl.h"

#include <vector>

using namespace std;

typedef enum {
	enWindows_10=0,
	enWindows_Server_2016,
	enWindows_8_1,
	enWindows_Server_2012_R2,
	enWindows_8,
	enWindows_Server_2012_6_2,
	enWindows_7,
	enWindows_Server_2008_R2_6_1,
	enWindows_Server_2008_6_0,
	enWindows_Vista_6_0,

	enWindows_Server_2003_R2,
	enWindows_Server_2003,
	enWindows_XP,
	enWindows_2000,

	enWindows_Unknown = -1

} enOS;

typedef struct {
	CString strDescription;
	CString strServiceName;

	CString strIP4v;
	CString strDhcpNameServer;

} STR_NETWORKCARD;


// CComSecurityDlg 대화 상자
class CComSecurityDlg : public CDialogEx
{
private:
	vector<STR_NETWORKCARD> m_vecNetworkCard;

public:
	

private:

public:
	void InitControl();

	void CheckOverComputer();
	enOS GetOSVersion();

	void CheckNetworkCards();

// 생성입니다.
public:
	CComSecurityDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_COMSECURITY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CReportCtrl m_CListNetwork;
	CIPAddressCtrl m_IPv4;
	afx_msg void OnHdnItemclickListNetworkcard(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListNetworkcard(NMHDR *pNMHDR, LRESULT *pResult);
	CIPAddressCtrl m_DHCPServer;
};
