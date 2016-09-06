// SubPrinters.cpp : implementation file
//

#include "stdafx.h"
#include "Secure.h"
#include "SubPrinters.h"
#include "mmcgutil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubPrinters dialog


CSubPrinters::CSubPrinters(CWnd* pParent /*=NULL*/)
	: CSecureChildBase(CSubPrinters::IDD, pParent)
{
	CDialog::Create(CSubPrinters::IDD, pParent);
	//{{AFX_DATA_INIT(CSubPrinters)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CSubPrinters, CSecureChildBase)
	//{{AFX_MSG_MAP(CSubPrinters)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_PRN_CBGENDET,IDC_PRN_CBDEL,OnCB)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubPrinters message handlers

BOOL CSubPrinters::LoadSettings()
{
	CButton* pButton;
	pButton = (CButton*)GetDlgItem(IDC_PRN_CBGENDET);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoPrinterTabs",0));
	pButton = (CButton*)GetDlgItem(IDC_PRN_CBADD);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoAddPrinter",0));
	pButton = (CButton*)GetDlgItem(IDC_PRN_CBDEL);
	pButton->SetCheck(GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoDeletePrinter",0));

	//page no longer dirty
	m_IsDirty = FALSE;
	return TRUE;
}

int CSubPrinters::SaveSettings()
{
	CButton* pButton; 
	pButton = (CButton*)GetDlgItem(IDC_PRN_CBGENDET);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoPrinterTabs",pButton->GetCheck());
	else				   DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoPrinterTabs");
	pButton = (CButton*)GetDlgItem(IDC_PRN_CBADD);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoAddPrinter",pButton->GetCheck());
	else				   DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoAddPrinter");
	pButton = (CButton*)GetDlgItem(IDC_PRN_CBDEL);
	if(pButton->GetCheck())SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoDeletePrinter",pButton->GetCheck());
	else				   DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoDeletePrinter");
	//
	return 1;
}

void CSubPrinters::OnCB(UINT nID)
{
	SetDirty();
}

BOOL CSubPrinters::SaveConfig(char* pszSave)
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_PRN_CBGENDET);
	pszSave[0] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_PRN_CBADD);
	pszSave[1] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_PRN_CBDEL);
	pszSave[2] = pBtn->GetCheck() + 1;
	return TRUE;
}

BOOL CSubPrinters::LoadConfig(char* pszLoad)
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_PRN_CBGENDET);
	pBtn->SetCheck(pszLoad[0] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_PRN_CBADD);
	pBtn->SetCheck(pszLoad[1] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_PRN_CBDEL);
	pBtn->SetCheck(pszLoad[3] - 1);
	m_IsDirty=TRUE;
	return TRUE;
}
