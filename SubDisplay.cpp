// SubDisplay.cpp : implementation file
//
#include "stdafx.h"
#include "Secure.h"
#include "SubDisplay.h"
#include "mmcgutil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubDisplay dialog


CSubDisplay::CSubDisplay(CWnd* pParent /*=NULL*/)
	: CSecureChildBase(CSubDisplay::IDD, pParent)
{
	CDialog::Create(CSubDisplay::IDD, pParent);
	//{{AFX_DATA_INIT(CSubDisplay)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CSubDisplay, CSecureChildBase)
	//{{AFX_MSG_MAP(CSubDisplay)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_DISP_CBDISABLE,IDC_DISP_CBSET,OnCB)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubDisplay message handlers
//
BOOL CSubDisplay::LoadSettings()
{
	CButton* pButton;
	//
	pButton = (CButton*)GetDlgItem(IDC_DISP_CBDISABLE);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDispCPL",0));
	pButton = (CButton*)GetDlgItem(IDC_DISP_CBBG);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDispBackgroundPage",0));
	pButton = (CButton*)GetDlgItem(IDC_DISP_CBSCR);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDispScrSavPage",0));
	pButton = (CButton*)GetDlgItem(IDC_DISP_CBAPP);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDispAppearancePage",0));
	pButton = (CButton*)GetDlgItem(IDC_DISP_CBSET);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDispSettingsPage",0));

	//page no longer dirty
	m_IsDirty = FALSE;
	return TRUE;
}

int CSubDisplay::SaveSettings()
{
	CButton* pButton;
	pButton = (CButton*)GetDlgItem(IDC_DISP_CBDISABLE);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDispCPL",pButton->GetCheck());
	else				   DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDispCPL");
	pButton = (CButton*)GetDlgItem(IDC_DISP_CBBG);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDispBackgroundPage",pButton->GetCheck());
	else				   DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDispBackgroundPage");
	pButton = (CButton*)GetDlgItem(IDC_DISP_CBSCR);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDispScrSavPage",pButton->GetCheck());
	else				   DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDispScrSavPage");
	pButton = (CButton*)GetDlgItem(IDC_DISP_CBAPP);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDispAppearancePage",pButton->GetCheck());
	else				   DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDispAppearancePage");
	pButton = (CButton*)GetDlgItem(IDC_DISP_CBSET);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDispSettingsPage",pButton->GetCheck());
	else				   DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDispSettingsPage");
	return 1;
}

void CSubDisplay::OnCB(UINT nID)
{
	SetDirty();
}

BOOL CSubDisplay::SaveConfig(char* pszSave)
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_DISP_CBSCR);
	pszSave[0] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_DISP_CBAPP);
	pszSave[1] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_DISP_CBSET);
	pszSave[2] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_DISP_CBBG);
	pszSave[3] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_DISP_CBDISABLE);
	pszSave[4] = pBtn->GetCheck() + 1;
	return TRUE;
}

BOOL CSubDisplay::LoadConfig(char* pszLoad)
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_DISP_CBSCR);
	pBtn->SetCheck(pszLoad[0] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_DISP_CBAPP);
	pBtn->SetCheck(pszLoad[1] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_DISP_CBSET);
	pBtn->SetCheck(pszLoad[2] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_DISP_CBBG);
	pBtn->SetCheck(pszLoad[3] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_DISP_CBDISABLE);
	pBtn->SetCheck(pszLoad[4] - 1);

	m_IsDirty=TRUE;
	return TRUE;
}
