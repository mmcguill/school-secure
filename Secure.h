// Secure.h : main header file for the SECURE application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#define WM_LCEX_ITEMSTATE WM_USER+1
#define WM_UPDATECHECKDATA WM_USER+5
/////////////////////////////////////////////////////////////////////////////
// CSecureApp:
// See Secure.cpp for the implementation of this class
//

class CSecureApp : public CWinApp
{
public:
	CSecureApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSecureApp)
	public:
	virtual BOOL InitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSecureApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void TrialUninstall();
};


/////////////////////////////////////////////////////////////////////////////
