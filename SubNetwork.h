// SubNetwork.h : header file
//
#include "securechildbase.h"
/////////////////////////////////////////////////////////////////////////////
// CSubNetwork dialog

class CSubNetwork : public CSecureChildBase			
{
// Construction
public:
	BOOL LoadConfig(char* pszLoad);
	BOOL SaveConfig(char* pszSave);
	CSubNetwork(CWnd* pParent = NULL);   // standard constructor
	BOOL LoadSettings();
	int SaveSettings();
// Dialog Data
	//{{AFX_DATA(CSubNetwork)
	enum { IDD = IDD_SUBNETWORK };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubNetwork)
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubNetwork)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	afx_msg void OnCB(UINT nID);
	DECLARE_MESSAGE_MAP()
};
