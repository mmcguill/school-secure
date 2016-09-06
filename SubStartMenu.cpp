// SubStartMenu.cpp : implementation file
//

#include "stdafx.h"
#include "Secure.h"
#include "SubStartMenu.h"
#include "mmcgutil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubStartMenu dialog


CSubStartMenu::CSubStartMenu(CWnd* pParent /*=NULL*/)
	: CSecureChildBase(CSubStartMenu::IDD, pParent)
{
	CDialog::Create(CSubStartMenu::IDD, pParent);
	//{{AFX_DATA_INIT(CSubStartMenu)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CSubStartMenu, CSecureChildBase)
	//{{AFX_MSG_MAP(CSubStartMenu)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_SM_CBREMOVERUN,IDC_SM_CBSUBFOLDERS,OnCB)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubStartMenu message handlers

BOOL CSubStartMenu::LoadSettings()
{
	CButton* pButton = (CButton*)GetDlgItem(IDC_SM_CBFIND);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoFind",0));
	pButton = (CButton*)GetDlgItem(IDC_SM_CBREMOVERUN);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoRun",0));
	pButton = (CButton*)GetDlgItem(IDC_SM_CBSHUTDOWN);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoClose",0));
	pButton = (CButton*)GetDlgItem(IDC_SM_CBSUBFOLDERS);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoStartMenuSubFolders",0));
	pButton = (CButton*)GetDlgItem(IDC_SM_CBTASKBAR);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoSetTaskbar",0));

	m_IsDirty = FALSE;

	return TRUE;
}

int CSubStartMenu::SaveSettings()
{
	CButton* pButton = (CButton*)GetDlgItem(IDC_SM_CBFIND);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoFind",pButton->GetCheck());
	else DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoFind");
	pButton = (CButton*)GetDlgItem(IDC_SM_CBREMOVERUN);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoRun",pButton->GetCheck());
	else DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoRun");
	pButton = (CButton*)GetDlgItem(IDC_SM_CBSHUTDOWN);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoClose",pButton->GetCheck());
	else DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoClose");
	pButton = (CButton*)GetDlgItem(IDC_SM_CBSUBFOLDERS);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoStartMenuSubFolders",pButton->GetCheck());
	else DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoStartMenuSubFolders");
	pButton = (CButton*)GetDlgItem(IDC_SM_CBTASKBAR);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoSetTaskbar",pButton->GetCheck());
	else DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoSetTaskbar");

	return 1;
}

void CSubStartMenu::OnCB(UINT nID)
{
	SetDirty();
}

BOOL CSubStartMenu::SaveConfig(char* pszSave)
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_SM_CBFIND);
	pszSave[0] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_SM_CBREMOVERUN);
	pszSave[1] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_SM_CBSHUTDOWN);
	pszSave[2] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_SM_CBSUBFOLDERS);
	pszSave[3] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_SM_CBTASKBAR);
	pszSave[4] = pBtn->GetCheck() + 1;
	return TRUE;
}

BOOL CSubStartMenu::LoadConfig(char* pszLoad)
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_SM_CBFIND);
	pBtn->SetCheck(pszLoad[0] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_SM_CBREMOVERUN);
	pBtn->SetCheck(pszLoad[1] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_SM_CBSHUTDOWN);
	pBtn->SetCheck(pszLoad[2] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_SM_CBSUBFOLDERS);
	pBtn->SetCheck(pszLoad[3] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_SM_CBTASKBAR);
	pBtn->SetCheck(pszLoad[4] - 1);
	m_IsDirty=TRUE;
	return TRUE;
}
