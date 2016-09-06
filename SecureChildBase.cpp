// SecureChildBase.cpp : implementation file
//

#include "stdafx.h"
#include "Secure.h"
#include "securechildbase.h"
#include "securedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSecureChildBase dialog


CSecureChildBase::CSecureChildBase(int nTemplate, CWnd* pParent) : CDialog(nTemplate, pParent)
{
	//{{AFX_DATA_INIT(CSecureChildBase)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_IsDirty = FALSE;
}

BEGIN_MESSAGE_MAP(CSecureChildBase, CDialog)
	//{{AFX_MSG_MAP(CSecureChildBase)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSecureChildBase message handlers

BOOL CSecureChildBase::LoadSettings()
{
	return TRUE;
}

int CSecureChildBase::SaveSettings()
{
	return TRUE;
}

void CSecureChildBase::SetDirty()
{
	CSecureDlg* pParent = (CSecureDlg*)GetParent();
	pParent->SetDirty();
	m_IsDirty = TRUE;
}

BOOL CSecureChildBase::Create(CWnd* pParent)
{
	return FALSE;
}

BOOL CSecureChildBase::SaveConfig(char* pszSave)
{
	return TRUE;
}

BOOL CSecureChildBase::LoadConfig(char* pszLoad)
{
	return TRUE;
}
