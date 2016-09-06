// PasswordDlg.cpp : implementation file
// 
#include "stdafx.h"
#include "secure.h"
#include "PasswordDlg.h"
#include "stdafx.h"
#include "MMcGUtil.h"
 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
#define MAX_PWLEN 12
/////////////////////////////////////////////////////////////////////////////
// CPasswordDlg dialog


CPasswordDlg::CPasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPasswordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPasswordDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CPasswordDlg, CDialog)
	//{{AFX_MSG_MAP(CPasswordDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPasswordDlg message handlers
void CPasswordDlg::OnOK() 
{
	char szPass[MAX_PATH];
	unsigned char szEnc[MAX_PATH];
	DWORD dwLen = MAX_PATH;
	char szEntPass[MAX_PATH];
	char szKey[] = "McGuill Secure";
	GetDlgItemText(IDC_EDPASS,szEntPass, MAX_PATH);

	//Check Registry for szEnc and its length
	HKEY hKey;
	int nResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE,"software\\mcguill\\secure",0,KEY_READ,&hKey);
	if(nResult == ERROR_SUCCESS)
	{
		if(RegQueryValueEx(hKey,"optcheck",0,NULL,szEnc,(unsigned long*)&dwLen) == ERROR_SUCCESS)
		{
			RegCloseKey(hKey);
		}
		else EndDialog(IDCANCEL);
	}
	else EndDialog(IDCANCEL);
	
	///DECRYPT
	for(int x=0;x<(int)dwLen;x++) szPass[x] = szEnc[x] ^ szKey[x];
	szPass[x] = 0;

	//CHECK
	if(stricmp(szEntPass,szPass))
	{
		MessageBox("Incorrect Password.","Secure - Incorrect Password",MB_OK | MB_ICONEXCLAMATION);
		CDialog::OnCancel();
	}
	else CDialog::OnOK();
}
