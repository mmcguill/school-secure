// SetPass.cpp : implementation file
//
#include "stdafx.h"
#include "Secure.h"
#include "SetPass.h"
#include "mmcgutil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_PWLEN 12
/////////////////////////////////////////////////////////////////////////////
// CSetPass dialog


CSetPass::CSetPass(CWnd* pParent /*=NULL*/)
	: CDialog(CSetPass::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetPass)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CSetPass, CDialog)
	//{{AFX_MSG_MAP(CSetPass)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetPass message handlers

void CSetPass::OnOK() 
{
	//Password
	char szPass[MAX_PATH];
	char szConfirm[MAX_PATH];
	GetDlgItemText(IDC_EDNEW,szPass,MAX_PATH);
	GetDlgItemText(IDC_EDNEWCONFIRM,szConfirm,MAX_PATH);
	if(strlen(szPass) > MAX_PWLEN) 
	{
		MessageBox("This password exceeds maximum length of 12.","Secure - Password Error",MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	//
	if(!stricmp(szPass,szConfirm))
	{
		unsigned char szEnc[MAX_PWLEN];
		unsigned char szKey[] = "McGuill Secure";
		for(int x=0;x<(int)strlen(szPass);x++) szEnc[x] = szPass[x] ^ szKey[x];
		SetRegData(HKEY_LOCAL_MACHINE,"Software\\McGuill\\Secure","optcheck",szEnc,(int)strlen(szPass));
	}
	else
	{
		MessageBox("Password Error: Confirm password is not the same as actual password.","Secure - Password Error",MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	CDialog::OnOK();

	//char szKey[] = "McGuill Secure";
	//char szPass[] = "thisisatest";
	//char szEnc[] = "thisisatest";
	//for(int x=0;x<strlen(szPass);x++) szEnc[x] = szPass[x] ^ szKey[x];
	//MessageBox(szEnc);
	//szPass[0]=0;
	//for(x=0;x<strlen(szEnc);x++) szPass[x] = szEnc[x] ^ szKey[x];
	//MessageBox(szPass);
}
