// SubGeneral.cpp : implementation file
//

#include "stdafx.h"
#include "Secure.h"
#include "SubGeneral.h"
#include "mmcgutil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubGeneral dialog


CSubGeneral::CSubGeneral(CWnd* pParent)
	: CSecureChildBase(CSubGeneral::IDD, pParent)
{
	CDialog::Create(CSubGeneral::IDD, pParent);
	//{{AFX_DATA_INIT(CSubGeneral)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CSubGeneral, CSecureChildBase)
	//{{AFX_MSG_MAP(CSubGeneral)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_CB_NOTASKCM,IDC_CB_HIDEDESKTOPICONS,OnCB)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubGeneral message handlers

BOOL CSubGeneral::LoadSettings()
{
	CButton* pButton;
	//
	pButton = (CButton*)GetDlgItem(IDC_CB_MSDOS);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\WinOldApp","Disabled",0));
	pButton = (CButton*)GetDlgItem(IDC_CB_REGISTRY);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"DisableRegistryTools",0));
	pButton = (CButton*)GetDlgItem(IDC_CB_SINGLEMODEMSDOS);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\WinOldApp","NoRealMode",0));
	pButton = (CButton*)GetDlgItem(IDC_CB_HIDEDESKTOPICONS);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoDesktop",0));
	pButton = (CButton*)GetDlgItem(IDC_CB_ENTIRENET);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoEntireNetwork",0));
	pButton = (CButton*)GetDlgItem(IDC_CB_FOLDERS);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoSetFolders",0));
	pButton = (CButton*)GetDlgItem(IDC_CB_WORKGROUPCONT);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoWorkgroupContents",0));
	pButton = (CButton*)GetDlgItem(IDC_CB_NOTASKCM);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoTrayContextMenu",0));
	pButton = (CButton*)GetDlgItem(IDC_CB_NOEXPCM);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoViewContextMenu",0));

    //page no longer dirty
	m_IsDirty = FALSE;
	return TRUE;
}

int CSubGeneral::SaveSettings()
{
	CButton* pButton;
	//
	pButton = (CButton*)GetDlgItem(IDC_CB_MSDOS);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\WinOldApp",	"Disabled",pButton->GetCheck());
	else DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\WinOldApp",	"Disabled");
	pButton = (CButton*)GetDlgItem(IDC_CB_REGISTRY);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"DisableRegistryTools",pButton->GetCheck());
	else DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"DisableRegistryTools");
	pButton = (CButton*)GetDlgItem(IDC_CB_SINGLEMODEMSDOS);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\WinOldApp",	"NoRealMode",pButton->GetCheck());
	else DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\WinOldApp",	"NoRealMode");
	pButton = (CButton*)GetDlgItem(IDC_CB_HIDEDESKTOPICONS);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoDesktop",pButton->GetCheck());
	else DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoDesktop");
	pButton = (CButton*)GetDlgItem(IDC_CB_ENTIRENET);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoEntireNetwork",pButton->GetCheck());
	else DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoEntireNetwork");
	pButton = (CButton*)GetDlgItem(IDC_CB_FOLDERS);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoSetFolders",pButton->GetCheck());
	else DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoSetFolders");
	pButton = (CButton*)GetDlgItem(IDC_CB_WORKGROUPCONT);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoWorkgroupContents",pButton->GetCheck());
	else DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoWorkgroupContents");
	pButton = (CButton*)GetDlgItem(IDC_CB_NOTASKCM);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoTrayContextMenu",pButton->GetCheck());
	else DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoTrayContextMenu");
	pButton = (CButton*)GetDlgItem(IDC_CB_NOEXPCM);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoViewContextMenu",pButton->GetCheck());
	else DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoViewContextMenu");
	return 1;
}

void CSubGeneral::OnCB(UINT nID)
{
	SetDirty();
}

BOOL CSubGeneral::SaveConfig(char* pszSave)
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CB_MSDOS);
	pszSave[0] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_CB_REGISTRY);
	pszSave[1] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_CB_SINGLEMODEMSDOS);
	pszSave[2] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_CB_HIDEDESKTOPICONS);
	pszSave[3] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_CB_ENTIRENET);
	pszSave[4] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_CB_FOLDERS);
	pszSave[5] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_CB_WORKGROUPCONT);
	pszSave[6] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_CB_NOEXPCM);
	pszSave[7] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_CB_NOTASKCM);
	pszSave[8] = pBtn->GetCheck() + 1;

	return TRUE;
}	



BOOL CSubGeneral::LoadConfig(char* pszLoad)
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CB_MSDOS);
	pBtn->SetCheck(pszLoad[0] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_CB_REGISTRY);
	pBtn->SetCheck(pszLoad[1] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_CB_SINGLEMODEMSDOS);
	pBtn->SetCheck(pszLoad[2] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_CB_HIDEDESKTOPICONS);
	pBtn->SetCheck(pszLoad[3] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_CB_ENTIRENET);
	pBtn->SetCheck(pszLoad[4] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_CB_FOLDERS);
	pBtn->SetCheck(pszLoad[5] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_CB_WORKGROUPCONT);
	pBtn->SetCheck(pszLoad[6] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_CB_NOEXPCM);
	pBtn->SetCheck(pszLoad[7] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_CB_NOTASKCM);
	pBtn->SetCheck(pszLoad[8] - 1);
	m_IsDirty=TRUE;
	return TRUE;
}
