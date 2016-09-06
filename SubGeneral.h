// SubGeneral.h : header file
//
#include "securechildbase.h"
/////////////////////////////////////////////////////////////////////////////
// CSubGeneral dialog

class CSubGeneral : public CSecureChildBase
{
// Construction
public:
	BOOL LoadConfig(char* pszLoad);
	BOOL SaveConfig(char* pszSave);
	CSubGeneral(CWnd* pParent = NULL);   // standard constructor
	BOOL LoadSettings();
	int SaveSettings();
// Dialog Data
	//{{AFX_DATA(CSubGeneral)
	enum { IDD = IDD_SUBGENERAL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubGeneral)
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSubGeneral)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	afx_msg void OnCB(UINT nID);
	DECLARE_MESSAGE_MAP()
};
