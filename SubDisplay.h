// SubDisplay.h : header file
//
#include "securechildbase.h"
/////////////////////////////////////////////////////////////////////////////
// CSubDisplay dialog

class CSubDisplay : public CSecureChildBase
{
// Construction
public:
	BOOL LoadConfig(char* pszLoad);
	BOOL SaveConfig(char* pszSave);
	CSubDisplay(CWnd* pParent = NULL);   // standard constructor
	BOOL LoadSettings();
	int SaveSettings();
// Dialog Data
	//{{AFX_DATA(CSubDisplay)
	enum { IDD = IDD_SUBDISPLAY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubDisplay)
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubDisplay)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	afx_msg void OnCB(UINT nID);
	DECLARE_MESSAGE_MAP()
};
