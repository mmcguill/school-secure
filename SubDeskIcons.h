// SubDeskIcons.h : header file
//
#include "securechildbase.h"
#include "listctrlex.h"
/////////////////////////////////////////////////////////////////////////////
// CSubDeskIcons dialog

class CSubDeskIcons : public CSecureChildBase
{
// Construction
public:
	CSubDeskIcons(CWnd* pParent = NULL);   // standard constructor
	BOOL LoadSettings();
	int SaveSettings();
// Dialog Data
	//{{AFX_DATA(CSubDeskIcons)
	enum { IDD = IDD_SUBDESKTOPICONS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubDeskIcons)
	//}}AFX_VIRTUAL

// Implementation
protected:
	CListCtrlEx m_LC;
	void CreateLCItem(char* pszDes,int nIcon,int nState,char* pszDataEx);
	int m_nDesktopItemIndex;
	void DeleteItems();
	struct LC_ITEM
	{
		char szText[MAX_PATH];
		int nIcon;
		int nState;
		char szDataEx[MAX_PATH];
	};
	LC_ITEM*	m_pDesktopItem[200];

	// Generated message map functions
	//{{AFX_MSG(CSubDeskIcons)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnGetdispinfoLcmain(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg LONG OnItemCheck(UINT wParam,LONG lParam);
	DECLARE_MESSAGE_MAP()
};
