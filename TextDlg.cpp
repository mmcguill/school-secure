// TextDlg.cpp : implementation file
//

#include "stdafx.h"
#include "secure.h"
#include "TextDlg.h"
#include "shlobj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextDlg dialog


CTextDlg::CTextDlg(CWnd* pParent,char* pszTitle,char* pszTip, char* pszText,char* pszItem, int nIcon, BOOL boolBrowse, char* pszDef)
	: CDialog(CTextDlg::IDD, pParent)
{
	Setup(pszTitle,pszTip,pszText,pszItem,nIcon,boolBrowse, pszDef);
	//{{AFX_DATA_INIT(CTextDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


BEGIN_MESSAGE_MAP(CTextDlg, CDialog)
	//{{AFX_MSG_MAP(CTextDlg)
	ON_BN_CLICKED(IDC_BBROWSE, OnBbrowse)
	ON_BN_CLICKED(IDC_BDEF, OnBdef)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextDlg message handlers
BOOL CTextDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText(m_szTitle);
	SetDlgItemText(IDC_EDITEMTEXT,	m_szItemText);
	SetDlgItemText(IDC_STITEM,		m_szItem);
	SetDlgItemText(IDC_STTIP,		m_szTip);
	CStatic* pstIcon = (CStatic*)GetDlgItem(IDC_STICON);
	if(m_hIcon != NULL)	pstIcon->SetIcon(m_hIcon);
	if(m_boolBrowse) GetDlgItem(IDC_BBROWSE)->ShowWindow(SW_SHOW);
	if(m_szDefault[0] != 0) GetDlgItem(IDC_BDEF)->ShowWindow(SW_SHOW);
	return TRUE;
}

void CTextDlg::OnOK() 
{
	GetDlgItemText(IDC_EDITEMTEXT,	m_szItemText, 1024);
	CDialog::OnOK();
}

void CTextDlg::OnBbrowse() 
{
	BROWSEINFO BrowseInfo;
	LPITEMIDLIST pidlSelDir;
	//
    BrowseInfo.hwndOwner =		this->GetSafeHwnd();
    BrowseInfo.pidlRoot  =		NULL;
    BrowseInfo.pszDisplayName = NULL;
    BrowseInfo.lpszTitle=		"Browse For System Folder Location.";
    BrowseInfo.ulFlags=			BIF_RETURNONLYFSDIRS;
    BrowseInfo.lpfn   =			NULL;
	BrowseInfo.lParam=			0;
	//
	pidlSelDir=SHBrowseForFolder(&BrowseInfo);
	if(pidlSelDir != NULL)
	{
		SHGetPathFromIDList(pidlSelDir,m_szItemText);
		SetDlgItemText(IDC_EDITEMTEXT,m_szItemText);
	}	
}

void CTextDlg::Setup(char* pszTitle,char* pszTip, char* pszText,char* pszItem, int nIcon, BOOL boolBrowse, char* pszDef)
{
	lstrcpy(m_szTitle,pszTitle);
	lstrcpy(m_szItem,pszItem);
	lstrcpy(m_szTip,pszTip);
	lstrcpy(m_szItemText,pszText);	
	lstrcpy(m_szDefault,pszDef);	
	if(nIcon) m_hIcon = AfxGetApp()->LoadIcon(nIcon);
	m_boolBrowse =  boolBrowse;
}

void CTextDlg::OnBdef() 
{
	SetDlgItemText(IDC_EDITEMTEXT, m_szDefault);
	OnOK();
}
