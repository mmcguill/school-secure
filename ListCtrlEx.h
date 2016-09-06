// ListCtrlEx.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx window
#define LISTCTRLEX

class CListCtrlEx : public CListCtrl
{
// Construction
public:
	void SetCheck(int nItem,int nCheck);
	int InsertItem(int nItem, char* pszText, int nImage, int nState = 0);
	int GetSelItem();
	BOOL SetMode(int nMode);
	CListCtrlEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListCtrlEx();
	// Generated message map functions
protected:
	CBitmap m_bmpStates;
	//{{AFX_MSG(CListCtrlEx)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	int m_nMode;
	BOOL SetupSysIL();
	void GetStateIL();
	CImageList	m_ILStates;
};

/////////////////////////////////////////////////////////////////////////////
