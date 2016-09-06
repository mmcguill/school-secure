// SubLevel.h : header file
//
#include "SecureChildBase.h"
/////////////////////////////////////////////////////////////////////////////
// CSubLevel dialog

class CSubLevel : public CSecureChildBase
{
// Construction
public:
	CSubLevel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSubLevel)
	enum { IDD = IDD_SUBLEVEL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubLevel)
	//}}AFX_VIRTUAL

// Implementation
protected:
	int SaveSettings();
	BOOL LoadSettings();
	void DoTrafficLights();

	// Generated message map functions
	//{{AFX_MSG(CSubLevel)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
