// SubSystem.cpp : implementation file
//
#include "stdafx.h"
#include "Secure.h"
#include "SubSystem.h"
#include "mmcgutil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubSystem dialog


CSubSystem::CSubSystem(CWnd* pParent /*=NULL*/)
	: CSecureChildBase(CSubSystem::IDD, pParent)
{
	CDialog::Create(CSubSystem::IDD, pParent);
	//{{AFX_DATA_INIT(CSubSystem)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CSubSystem, CSecureChildBase)
	//{{AFX_MSG_MAP(CSubSystem)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_SYS_CBVMB,IDC_SYS_CBFSB,OnCB)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubSystem message handlers

BOOL CSubSystem::LoadSettings()
{
	CButton* pButton;
	pButton = (CButton*)GetDlgItem(IDC_SYS_CBDEVMAN);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDevMgrPage",0));
	pButton = (CButton*)GetDlgItem(IDC_SYS_CBHARDW);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoConfigPage",0));
	pButton = (CButton*)GetDlgItem(IDC_SYS_CBFSB);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoFileSysPage",0));
	pButton = (CButton*)GetDlgItem(IDC_SYS_CBVMB);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoVirtMemPage",0));

	//page no longer dirty
	m_IsDirty = FALSE;
	return TRUE;
}

int CSubSystem::SaveSettings()
{
	CButton* pButton;
	pButton = (CButton*)GetDlgItem(IDC_SYS_CBDEVMAN);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDevMgrPage",pButton->GetCheck());
	else				   DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDevMgrPage");
	pButton = (CButton*)GetDlgItem(IDC_SYS_CBHARDW);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoConfigPage",pButton->GetCheck());
	else				   DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoConfigPage");
	pButton = (CButton*)GetDlgItem(IDC_SYS_CBFSB);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoFileSysPage",pButton->GetCheck());
	else				   DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoFileSysPage");
	pButton = (CButton*)GetDlgItem(IDC_SYS_CBVMB);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoVirtMemPage",pButton->GetCheck());
	else				   DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoVirtMemPage");
	return 1;
}

void CSubSystem::OnCB(UINT nID)
{
	SetDirty();
}

BOOL CSubSystem::SaveConfig(char* pszSave)
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_SYS_CBFSB);
	pszSave[0] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_SYS_CBVMB);
	pszSave[1] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_SYS_CBHARDW);
	pszSave[2] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_SYS_CBDEVMAN);
	pszSave[3] = pBtn->GetCheck() + 1;
	return TRUE;
}

BOOL CSubSystem::LoadConfig(char* pszLoad)
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_SYS_CBFSB);
	pBtn->SetCheck(pszLoad[0] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_SYS_CBVMB);
	pBtn->SetCheck(pszLoad[1] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_SYS_CBHARDW);
	pBtn->SetCheck(pszLoad[2] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_SYS_CBDEVMAN);
	pBtn->SetCheck(pszLoad[3] - 1);
	m_IsDirty=TRUE;
	return TRUE;
}
