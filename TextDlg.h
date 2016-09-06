// TextDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextDlg dialog

class CTextDlg : public CDialog
{
// Construction
public:
	void Setup(char* pszTitle = "",char* pszTip = "", char* pszText = "",char* pszItem = "", int nIcon = 0, BOOL boolBrowse = FALSE, char* pszDef = "");
	CTextDlg(CWnd* pParent = NULL,char* pszTitle = "",char* pszTip = "", char* pszText = "",char* pszItem = "", int nIcon = 0, BOOL boolBrowse = FALSE, char* pszDef = "");   // standard constructor
	char  m_szItemText[1024];
// Dialog Data
	//{{AFX_DATA(CTextDlg)
	enum { IDD = IDD_CHANGETEXT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextDlg)
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTextDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBbrowse();
	afx_msg void OnBdef();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	char  m_szTitle[MAX_PATH];
	char  m_szItem[MAX_PATH];
	char  m_szTip[MAX_PATH];
	HICON m_hIcon;
	BOOL  m_boolBrowse;
	char  m_szDefault[MAX_PATH];
};
