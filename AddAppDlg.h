// AddAppDlg.h : header file
//
#ifndef LISTCTRLEX
	#include "ListCtrlEx.h"
#endif
/////////////////////////////////////////////////////////////////////////////
// CAddAppDlg dialog

class CAddAppDlg : public CDialog
{
// Construction
public:
	CAddAppDlg(CWnd* pParent = NULL);   // standard constructor
	char* m_pszApps[1024];
	char* m_pszExisting[1024];
	char* m_pszRemove[MAX_PATH];
	int m_nExistApps;
	int m_nApps;
	int m_nRemove;
// Dialog Data
	//{{AFX_DATA(CAddAppDlg)
	enum { IDD = IDD_ADDAPP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddAppDlg)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddAppDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangedTreestartmenu(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg LONG UpdateCheckData(UINT nItemAndState, LONG lhWnd);
	DECLARE_MESSAGE_MAP()
private:
	void RemoveAppString(char* pszString);
	BOOL IsAllowed(char* pszPath);
	void GetFullTreePath(HTREEITEM hItem, char* pszDir);
	void GetShortcutPath(char* pszPath, char* pszFullPath);
	void FillStartMenuTree(HTREEITEM hParent);
	void SetupLC();
	char m_szBaseDir[MAX_PATH];
	CListCtrlEx m_LCEx;
};
