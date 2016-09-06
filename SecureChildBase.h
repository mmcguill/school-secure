// SecureChildBase.h : header file
//
#ifndef SECURECHILDBASE
	#define SECURECHILDBASE

/////////////////////////////////////////////////////////////////////////////
// CSecureChildBase dialog

class CSecureChildBase : public CDialog
{
// Construction
public:
	BOOL m_IsDirty;
	virtual BOOL Create(CWnd* pParent);
	CSecureChildBase(int nTemplate=0, CWnd* pParent = NULL);   // standard constructor
	virtual int SaveSettings();
	virtual BOOL LoadSettings();
	virtual BOOL SaveConfig(char* pszSave);
	virtual BOOL LoadConfig(char* pszLoad);
// Dialog Data
	//{{AFX_DATA(CSecureChildBase)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSecureChildBase)
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetDirty();

	// Generated message map functions
	//{{AFX_MSG(CSecureChildBase)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};
#endif //SECURECHILDBASE