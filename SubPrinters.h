// SubPrinters.h : header file
//
#include "securechildbase.h"
/////////////////////////////////////////////////////////////////////////////
// CSubPrinters dialog

class CSubPrinters : public CSecureChildBase
{
// Construction
public:
	BOOL LoadConfig(char* pszLoad);
	BOOL SaveConfig(char* pszSave);
	CSubPrinters(CWnd* pParent = NULL);   // standard constructor
	BOOL LoadSettings();
	int SaveSettings();
// Dialog Data
	//{{AFX_DATA(CSubPrinters)
	enum { IDD = IDD_SUBPRINTERS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubPrinters)
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubPrinters)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	afx_msg void OnCB(UINT nID);
	DECLARE_MESSAGE_MAP()
};
