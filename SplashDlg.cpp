// SplashDlg.cpp : implementation file
//

#include "stdafx.h"
#include "secure.h"
#include "SplashDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplashDlg dialog


CSplashDlg::CSplashDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSplashDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSplashDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CSplashDlg, CDialog)
	//{{AFX_MSG_MAP(CSplashDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplashDlg message handlers

BOOL CSplashDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowPos(&wndTopMost,0,0,269,122,SWP_NOMOVE);
	CStatic* pSt = (CStatic*)GetDlgItem(IDC_STBMP);
	
	m_hBmp = (HBITMAP)LoadImage(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_SPLASH),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE | LR_LOADMAP3DCOLORS);
	pSt->SetBitmap(m_hBmp);
	CenterWindow();
	SetTimer(1, 1250, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CSplashDlg::OnCancel() 
{
}

void CSplashDlg::OnOK() 
{
}

void CSplashDlg::OnTimer(UINT nIDEvent) 
{
	CDialog::OnTimer(nIDEvent);
	DestroyWindow();
}

void CSplashDlg::OnDestroy()
{
	DeleteObject(m_hBmp);
}