// SecureDlg.h : header file
//
#include "securechildbase.h"
#define NUM_SUBITEMS 11
/////////////////////////////////////////////////////////////////////////////
// CSecureDlg dialog

class CSecureDlg : public CDialog
{
// Construction
public:
	CSecureDlg(CWnd* pParent = NULL);	// standard constructor
	void SetDirty();
// Dialog Data
	//{{AFX_DATA(CSecureDlg)
	enum { IDD = IDD_SECURE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSecureDlg)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CSecureChildBase* pSubDlg[NUM_SUBITEMS];
	char		m_cSubIndex;
	HICON		m_hSubIcon[NUM_SUBITEMS];
	char		m_szSubArea[NUM_SUBITEMS][16];
	HICON		m_hIcon;
	CImageList	m_IL;
	BOOL		m_bDirty;
	CRect		m_rcInv;
	CFont		m_fnt;
	void		GetSelItem();
	void		ShowDetails();
	void		LoadSettings();
	BOOL		SaveSettings();

	// Generated message map functions
	//{{AFX_MSG(CSecureDlg)
	virtual BOOL	OnInitDialog();
	afx_msg void	OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void	OnDestroy();
	afx_msg void	OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void	OnOK();
	afx_msg void	OnApply();
	virtual void OnCancel();
	afx_msg void OnItemchangedSubareas(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg void OnSetPass();
	afx_msg void OnSaveConfig();
	afx_msg void OnLoadConfig();
	afx_msg void OnAbout();
	DECLARE_MESSAGE_MAP()
};
