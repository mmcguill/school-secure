// SubAddRemove.h : header file
//
#include "securechildbase.h"
/////////////////////////////////////////////////////////////////////////////
// CSubAddRemove dialog

class CSubAddRemove : public CSecureChildBase
{
// Construction
public:
	CSubAddRemove(CWnd* pParent = NULL);   // standard constructor
	BOOL LoadSettings();
	int SaveSettings();
// Dialog Data
	//{{AFX_DATA(CSubAddRemove)
	enum { IDD = IDD_SUBADDREMOVE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubAddRemove)
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL IsAllowed(char* pszTest);
	void RunAddItem();
	void RunRemoveItem();
	int	 m_nApps;
	void EnableLC();
	BOOL OnInitDialog();

	// Generated message map functions
	//{{AFX_MSG(CSubAddRemove)
	afx_msg void OnDestroy();
	afx_msg void OnCbAllowall();
	afx_msg void OnBaddnonsm();
	afx_msg void OnRunBadd();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
