// SubDrives.h : header file
//
#include "securechildbase.h"

#ifndef LISTCTRLEX 
   #include "listctrlex.h"
#endif
/////////////////////////////////////////////////////////////////////////////
// CSubDrives dialog

class CSubDrives : public CSecureChildBase
{
// Construction
public:
	CSubDrives(CWnd* pParent = NULL);   // standard constructor
	BOOL LoadSettings();
	int SaveSettings();
// Dialog Data
	//{{AFX_DATA(CSubDrives)
	enum { IDD = IDD_SUBDRIVES };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubDrives)
	//}}AFX_VIRTUAL

// Implementation
protected:
	void CreateLCItem(char* pszDes, int nIcon, int nState, char* pszDataEx);
	void DeleteItems();

	// Generated message map functions
	//{{AFX_MSG(CSubDrives)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnGetdispinfoLcmain(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg LONG OnItemCheck(UINT wParam,LONG lParam);
	DECLARE_MESSAGE_MAP()
private:
	CListCtrlEx m_LC;
	struct LC_ITEM
	{
		char szText[MAX_PATH];
		int nIcon;
		int nState;
		char szDataEx[MAX_PATH];
	};
	LC_ITEM*	m_pDriveItem[32];
	int			m_nDriveItemIndex;
};
