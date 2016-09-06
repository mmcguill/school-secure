// SubNetwork.cpp : implementation file
//
#include "stdafx.h"
#include "Secure.h"
#include "SubNetwork.h"
#include "mmcgutil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubNetwork dialog


CSubNetwork::CSubNetwork(CWnd* pParent /*=NULL*/)
	: CSecureChildBase(CSubNetwork::IDD, pParent)
{
	CDialog::Create(CSubNetwork::IDD, pParent);
	//{{AFX_DATA_INIT(CSubNetwork)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CSubNetwork, CSecureChildBase)
	//{{AFX_MSG_MAP(CSubNetwork)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_NET_CBDISABLE,IDC_NET_CBNOMAPNETDRIVE,OnCB)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubNetwork message handlers

BOOL CSubNetwork::LoadSettings()
{
	CButton* pButton;
	pButton = (CButton*)GetDlgItem(IDC_NET_CBDISABLE);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoNetSetup",0));
	pButton = (CButton*)GetDlgItem(IDC_NET_CBHIDEIDPAGE);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoNetSetupIdPage",0));
	pButton = (CButton*)GetDlgItem(IDC_NET_CBHIDEACCCON);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoNetSetupSecurityPage",0));
	pButton = (CButton*)GetDlgItem(IDC_NET_CBNOMAPNETDRIVE);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoNetConnectDisconnect",0));

	//page no longer dirty
	m_IsDirty = FALSE;
	return TRUE;
}

int CSubNetwork::SaveSettings()
{
	CButton* pButton;
	pButton = (CButton*)GetDlgItem(IDC_NET_CBDISABLE);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoNetSetup",pButton->GetCheck());
	else				   DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoNetSetup");
	pButton = (CButton*)GetDlgItem(IDC_NET_CBHIDEIDPAGE);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoNetSetupIdPage",pButton->GetCheck());
	else				   DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoNetSetupIdPage");
	pButton = (CButton*)GetDlgItem(IDC_NET_CBHIDEACCCON);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoNetSetupSecurityPage",pButton->GetCheck());
	else				   DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoNetSetupSecurityPage");
	pButton = (CButton*)GetDlgItem(IDC_NET_CBNOMAPNETDRIVE);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoNetConnectDisconnect",1);
	else				   DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoNetConnectDisconnect");
	return 1;
}

void CSubNetwork::OnCB(UINT nID)
{
	SetDirty();
}

BOOL CSubNetwork::SaveConfig(char* pszSave)
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_NET_CBDISABLE);
	pszSave[0] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_NET_CBHIDEIDPAGE);
	pszSave[1] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_NET_CBHIDEACCCON);
	pszSave[2] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_NET_CBNOMAPNETDRIVE);
	pszSave[3] = pBtn->GetCheck() + 1;
	return TRUE;
}

BOOL CSubNetwork::LoadConfig(char* pszLoad)
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_NET_CBDISABLE);
	pBtn->SetCheck(pszLoad[0] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_NET_CBHIDEIDPAGE);
	pBtn->SetCheck(pszLoad[1] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_NET_CBHIDEACCCON);
	pBtn->SetCheck(pszLoad[2] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_NET_CBNOMAPNETDRIVE);
	pBtn->SetCheck(pszLoad[3] - 1);
	m_IsDirty=TRUE;
	return TRUE;
}
