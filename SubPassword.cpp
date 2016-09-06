// SubPassword.cpp : implementation file
//

#include "stdafx.h"
#include "Secure.h"
#include "SubPassword.h"
#include "mmcgutil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubPassword dialog


CSubPassword::CSubPassword(CWnd* pParent /*=NULL*/)
	: CSecureChildBase(CSubPassword::IDD, pParent)
{
	CDialog::Create(CSubPassword::IDD, pParent);
	//{{AFX_DATA_INIT(CSubPassword)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CSubPassword, CSecureChildBase)
	//{{AFX_MSG_MAP(CSubPassword)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_PW_CBHIDEUSERPROFILES,IDC_PW_CBDISABLE,OnCB)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubPassword message handlers

BOOL CSubPassword::LoadSettings()
{
	CButton* pButton;
	pButton = (CButton*)GetDlgItem(IDC_PW_CBDISABLE);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoSecCPL",0));
	pButton = (CButton*)GetDlgItem(IDC_PW_CBHIDECHANGEPW);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoPwdPage",0));
	pButton = (CButton*)GetDlgItem(IDC_PW_CBHIDEREMADM);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoAdminPage",0));
	pButton = (CButton*)GetDlgItem(IDC_PW_CBHIDEUSERPROFILES);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoProfilePage",0));

	//page no longer dirty
	m_IsDirty = FALSE;
	return TRUE;
}

int CSubPassword::SaveSettings()
{
	CButton* pButton;
	pButton = (CButton*)GetDlgItem(IDC_PW_CBDISABLE);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoSecCPL",pButton->GetCheck());
	else				   DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoSecCPL");
	pButton = (CButton*)GetDlgItem(IDC_PW_CBHIDECHANGEPW);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoPwdPage",pButton->GetCheck());
	else				   DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoPwdPage");
	pButton = (CButton*)GetDlgItem(IDC_PW_CBHIDEREMADM);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoAdminPage",pButton->GetCheck());
	else				   DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoAdminPage");
	pButton = (CButton*)GetDlgItem(IDC_PW_CBHIDEUSERPROFILES);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoProfilePage",pButton->GetCheck());
	else				   DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoProfilePage");
	return 1;
}

void CSubPassword::OnCB(UINT nID)
{
	SetDirty();
}

BOOL CSubPassword::SaveConfig(char* pszSave)
{
	CButton*	pBtn = (CButton*)GetDlgItem(IDC_PW_CBDISABLE);
	pszSave[0] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_PW_CBHIDECHANGEPW);
	pszSave[1] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_PW_CBHIDEUSERPROFILES);
	pszSave[2] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_PW_CBHIDEREMADM);
	pszSave[3] = pBtn->GetCheck() + 1;
	return TRUE;
}

BOOL CSubPassword::LoadConfig(char* pszLoad)
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_PW_CBDISABLE);
	pBtn->SetCheck(pszLoad[0] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_PW_CBHIDECHANGEPW);
	pBtn->SetCheck(pszLoad[1] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_PW_CBHIDEUSERPROFILES);
	pBtn->SetCheck(pszLoad[2] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_PW_CBHIDEREMADM);
	pBtn->SetCheck(pszLoad[3] - 1);
	m_IsDirty=TRUE;
	return TRUE;
}
