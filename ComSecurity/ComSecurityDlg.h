
// ComSecurityDlg.h : ��� ����
//

#pragma once


// CComSecurityDlg ��ȭ ����
class CComSecurityDlg : public CDialogEx
{
private:

public:
	

private:

public:
	void CheckOverComputer();

// �����Դϴ�.
public:
	CComSecurityDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_COMSECURITY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
