// SubPWSet.h : header file
//
#include "securechildbase.h"
/////////////////////////////////////////////////////////////////////////////
// CSubPWSet dialog

class CSubPWSet : public CSecureChildBase
{
// Construction
public:
	BOOL LoadConfig(char* pszLoad);
	BOOL SaveConfig(char* pszSave);
	CSubPWSet(CWnd* pParent = NULL);   // standard constructor
	BOOL LoadSettings();
	int SaveSettings();
// Dialog Data
	//{{AFX_DATA(CSubPWSet)
	enum { IDD = IDD_SUBPASS_SETTINGS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubPWSet)
	//}}AFX_VIRTUAL

// Implementation
protected:
    void SetupPwLen();
	virtual BOOL OnInitDialog();
	// Generated message map functions
	//{{AFX_MSG(CSubPWSet)
	afx_msg void OnPassCblen();
	afx_msg void OnDeltaposPassSplen(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg void OnCB(UINT nID);
	DECLARE_MESSAGE_MAP()
};
