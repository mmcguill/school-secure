// SubSystem.h : header file
//
#include "securechildbase.h"
/////////////////////////////////////////////////////////////////////////////
// CSubSystem dialog

class CSubSystem : public CSecureChildBase
{
// Construction
public:
	BOOL LoadConfig(char* pszLoad);
	BOOL SaveConfig(char* pszSave);
	CSubSystem(CWnd* pParent = NULL);   // standard constructor
	BOOL LoadSettings();
	int SaveSettings();
// Dialog Data
	//{{AFX_DATA(CSubSystem)
	enum { IDD = IDD_SUBSYSTEM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubSystem)
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubSystem)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	afx_msg void OnCB(UINT nID);
	DECLARE_MESSAGE_MAP()
};
