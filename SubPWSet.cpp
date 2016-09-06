// SubPWSet.cpp : implementation file
//
#include "stdafx.h"
#include "Secure.h"
#include "SubPWSet.h"
#include "mmcgutil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubPWSet dialog


CSubPWSet::CSubPWSet(CWnd* pParent /*=NULL*/)
	: CSecureChildBase(CSubPWSet::IDD, pParent)
{
	CDialog::Create(CSubPWSet::IDD, pParent);
	//{{AFX_DATA_INIT(CSubPWSet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CSubPWSet, CSecureChildBase)
	//{{AFX_MSG_MAP(CSubPWSet)
	ON_BN_CLICKED(IDC_PASS_CBLEN, OnPassCblen)
	ON_NOTIFY(UDN_DELTAPOS, IDC_PASS_SPLEN, OnDeltaposPassSplen)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_PW_CBLASTUSER,IDC_PASS_CBALPHA,OnCB)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubPWSet message handlers
BOOL CSubPWSet::OnInitDialog()
{
	CDialog::OnInitDialog();
	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_PASS_SPLEN);
	pSpin->SetBuddy(GetDlgItem(IDC_PASS_EDLEN));
	pSpin->SetRange(1,8);	
	return TRUE;
}

BOOL CSubPWSet::LoadSettings()
{
	CButton* pButton;
	pButton = (CButton*)GetDlgItem(IDC_PASS_CBALPHA);
	pButton->SetCheck(GetRegInt(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"AlphanumPwds",0));
	pButton = (CButton*)GetDlgItem(IDC_PASS_CBCACHE);
	pButton->SetCheck(GetRegInt(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"DisablePwdCaching",0));
	pButton = (CButton*)GetDlgItem(IDC_PASS_CBSHARE);
	pButton->SetCheck(GetRegInt(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"HideSharePwds",0));
	pButton = (CButton*)GetDlgItem(IDC_PW_CBLASTUSER);
	pButton->SetCheck(GetRegString(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\WinLogon","DontDisplayLastUserName","1",0));
	//
	int nMinPwLen = GetRegInt(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network", "MinPwdLen",0);
	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_PASS_SPLEN);
	pButton = (CButton*)GetDlgItem(IDC_PASS_CBLEN);
	pSpin->SetPos(nMinPwLen);	
	if(nMinPwLen) pButton->SetCheck(1);
	else			pButton->SetCheck(0);
	SetupPwLen();

	//page no longer dirty
	m_IsDirty = FALSE;
	return TRUE;
}

int CSubPWSet::SaveSettings()
{
	CButton* pButton;
	pButton = (CButton*)GetDlgItem(IDC_PASS_CBALPHA);
	if(pButton->GetCheck())SetRegInt(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"AlphanumPwds",pButton->GetCheck());
	else				   DeleteRegValue(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"AlphanumPwds");
	pButton = (CButton*)GetDlgItem(IDC_PASS_CBCACHE);
	if(pButton->GetCheck())SetRegInt(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"DisablePwdCaching",pButton->GetCheck());
	else				   DeleteRegValue(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"DisablePwdCaching");
	pButton = (CButton*)GetDlgItem(IDC_PASS_CBSHARE);
	if(pButton->GetCheck())SetRegInt(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"HideSharePwds",pButton->GetCheck());
	else				   DeleteRegValue(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"HideSharePwds");
	pButton = (CButton*)GetDlgItem(IDC_PW_CBLASTUSER);
	if(pButton->GetCheck()) SetRegString(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\WinLogon","DontDisplayLastUserName","1");
	else					DeleteRegValue(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\WinLogon","DontDisplayLastUserName");
	//Min Length
	pButton = (CButton*)GetDlgItem(IDC_PASS_CBLEN);
	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_PASS_SPLEN);
	if(pButton->GetCheck()) SetRegInt(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network", "MinPwdLen",pSpin->GetPos());
	else					DeleteRegValue(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network", "MinPwdLen");
	return 1;
}

void CSubPWSet::SetupPwLen()
{
	CButton* pButton = (CButton*)GetDlgItem(IDC_PASS_CBLEN);
	if(pButton->GetCheck())
	{
		GetDlgItem(IDC_PASS_EDLEN)->EnableWindow(TRUE);
		GetDlgItem(IDC_PASS_SPLEN)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_PASS_EDLEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_PASS_SPLEN)->EnableWindow(FALSE);
	}
}

void CSubPWSet::OnPassCblen() 
{
	SetupPwLen();	
	SetDirty();
}

void CSubPWSet::OnDeltaposPassSplen(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	SetDirty();
	*pResult = 0;
}

void CSubPWSet::OnCB(UINT nID)
{
	SetDirty();
}

BOOL CSubPWSet::SaveConfig(char* pszSave)
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_PASS_CBCACHE);
	pszSave[0] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_PASS_CBALPHA);
	pszSave[1] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_PASS_CBSHARE);
	pszSave[2] = pBtn->GetCheck() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_PASS_CBLEN);
	pszSave[3] = pBtn->GetCheck() + 1;
	CSpinButtonCtrl* pSp = (CSpinButtonCtrl*)GetDlgItem(IDC_PASS_SPLEN);
	pszSave[4] = pSp->GetPos() + 1;
	pBtn = (CButton*)GetDlgItem(IDC_PW_CBLASTUSER);
	pszSave[5] = pBtn->GetCheck() + 1;
	return TRUE;
}

BOOL CSubPWSet::LoadConfig(char* pszLoad)
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_PASS_CBCACHE);
	pBtn->SetCheck(pszLoad[0] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_PASS_CBALPHA);
	pBtn->SetCheck(pszLoad[1] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_PASS_CBSHARE);
	pBtn->SetCheck(pszLoad[2] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_PASS_CBLEN);
	pBtn->SetCheck(pszLoad[3] - 1);
	CSpinButtonCtrl* pSp = (CSpinButtonCtrl*)GetDlgItem(IDC_PASS_SPLEN);
	pSp->SetPos(pszLoad[4] - 1);
	pBtn = (CButton*)GetDlgItem(IDC_PW_CBLASTUSER);
	pBtn->SetCheck(pszLoad[5] - 1);
	SetupPwLen();
	m_IsDirty=TRUE;
	return TRUE;
}
