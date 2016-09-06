// SubAddRemove.cpp : implementation file
//

#include "stdafx.h"
#include "Secure.h"
#include "SubAddRemove.h"
#include "mmcgutil.h"
#include "addappdlg.h"
#include "textdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubAddRemove dialog


CSubAddRemove::CSubAddRemove(CWnd* pParent /*=NULL*/)
	: CSecureChildBase(CSubAddRemove::IDD, pParent)
{
	CDialog::Create(CSubAddRemove::IDD, pParent);
	m_nApps=0;
	//{{AFX_DATA_INIT(CSubAddRemove)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CSubAddRemove, CSecureChildBase)
	//{{AFX_MSG_MAP(CSubAddRemove)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CB_ALLOWALL, OnCbAllowall)
	ON_BN_CLICKED(IDC_BADDNONSM, OnBaddnonsm)
	ON_BN_CLICKED(IDC_RUN_BADD, OnRunBadd)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	ON_COMMAND(IDM_CTXT_REMOVE,RunRemoveItem)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubAddRemove message handlers
BOOL CSubAddRemove::LoadSettings()
{
	HKEY hKey;
	int nRun = 0;
	CListCtrl* pLC = (CListCtrl*)GetDlgItem(IDC_RUN_LC);
	pLC->DeleteAllItems();
	if(RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\RestrictRun",0,KEY_READ,&hKey) == ERROR_SUCCESS)
	{
		int nRes;
		do
		{
			char szValue[MAX_PATH];
			unsigned long nValue = MAX_PATH;
			char szData[MAX_PATH];
			unsigned long nData = MAX_PATH;
			nRes = RegEnumValue(hKey,nRun,szValue, &nValue,0,NULL,(unsigned char*)szData,&nData);
			if(nRes == ERROR_SUCCESS)
			{
				pLC->InsertItem(nRun,szData,2);
				nRun++;	
			}
		}while(nRes == ERROR_SUCCESS);
		RegCloseKey(hKey);
	}
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CB_ALLOWALL);
	pBtn->SetCheck(!nRun);
	m_nApps=nRun;
	EnableLC();

	//page no longer dirty
	m_IsDirty = FALSE;
	return TRUE;
}

int CSubAddRemove::SaveSettings()
{
	DeleteRegKey(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\RestrictRun");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer","RestrictRun");
	if(m_nApps)
	{
		CListCtrl* pLC = (CListCtrl*)GetDlgItem(IDC_RUN_LC);
		char szValue[MAX_PATH];
		char szData[MAX_PATH];
		BOOL boolMyApp =	FALSE;
		BOOL boolSysTray =	FALSE;
		int x;
		for(x=0;x < (int)m_nApps;x++)
		{
			pLC->GetItemText(x,0,szData,MAX_PATH);
			if(!stricmp(szData,"secure.exe")) boolMyApp	=TRUE;
			if(!stricmp(szData,"systray.exe")) boolSysTray	=TRUE;
			itoa(x,szValue,10);
			SetRegString(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\RestrictRun",szValue,szData);
		}
		if(!boolMyApp)
		{
			itoa(x+1,szValue,10);
			SetRegString(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\RestrictRun",szValue,"secure.exe");
		}
		if(!boolSysTray)
		{
			itoa(x+1,szValue,10);
			SetRegString(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\RestrictRun",szValue,"systray.exe");
		}
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer","RestrictRun",1);
	}	
	return 1;
}

BOOL CSubAddRemove::OnInitDialog()
{
	CImageList ImageList;
	HIMAGELIST hImageList = GetSysImageList();
	ImageList.Attach(hImageList);
	CListCtrl* pLC = (CListCtrl*)GetDlgItem(IDC_RUN_LC);
	pLC->SetImageList(&ImageList,LVSIL_SMALL);
	ImageList.Detach();

	CButton* pBtn;
	pBtn = (CButton*)GetDlgItem(IDC_RUN_BADD);
	pBtn->SetBitmap((HBITMAP)LoadImage(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_BADD),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE | LR_LOADMAP3DCOLORS));
	pBtn = (CButton*)GetDlgItem(IDC_BADDNONSM);
	pBtn->SetBitmap((HBITMAP)LoadImage(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_BCUSTOM),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE | LR_LOADMAP3DCOLORS));
	return TRUE;
}

void CSubAddRemove::OnDestroy() 
{
	CSecureChildBase::OnDestroy();
	
	CButton* pBtn;
	pBtn = (CButton*)GetDlgItem(IDC_RUN_BADD);
	if(pBtn->GetBitmap() != NULL) DeleteObject(pBtn->GetBitmap());
	pBtn = (CButton*)GetDlgItem(IDC_BADDNONSM);
	if(pBtn->GetBitmap() != NULL) DeleteObject(pBtn->GetBitmap());
}

void CSubAddRemove::OnCbAllowall() 
{
	EnableLC();
	SetDirty();
}

void CSubAddRemove::EnableLC()
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CB_ALLOWALL);
	GetDlgItem(IDC_RUN_LC)->EnableWindow(!pBtn->GetCheck());
	GetDlgItem(IDC_ST1)->EnableWindow(!pBtn->GetCheck());
	if(!pBtn->GetCheck())	
	{
		GetDlgItem(IDC_RUN_BADD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BADDNONSM)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_RUN_BADD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BADDNONSM)->ShowWindow(SW_HIDE);
	}
	//
	CListCtrl* pLC = (CListCtrl*)GetDlgItem(IDC_RUN_LC);
	if(!pBtn->GetCheck())
	{
		if(m_nApps == 0)
		{
			pLC->InsertItem(0,"secure.exe",2);
			pLC->InsertItem(1,"Systray.exe",2);
			m_nApps=2;
		}
	}
	else
	{
		pLC->DeleteAllItems();
		m_nApps = 0;
	}
}

void CSubAddRemove::RunAddItem()
{
	CAddAppDlg dlgAddApp;
	CListCtrl* pLC = (CListCtrl*)GetDlgItem(IDC_RUN_LC);
	for(int x=0;x<m_nApps;x++)
	{
		dlgAddApp.m_pszExisting[x] = new char[MAX_PATH];
		pLC->GetItemText(x,0,dlgAddApp.m_pszExisting[x],MAX_PATH);
	}
	dlgAddApp.m_nExistApps=m_nApps;
	if(dlgAddApp.DoModal() == IDOK)
	{
		//Take Away the remove items here
		for(int x=0;x<dlgAddApp.m_nRemove;x++)
		{
			LV_FINDINFO lvfi;
			lvfi.flags = LVFI_STRING;
			lvfi.psz   = dlgAddApp.m_pszRemove[x];
			int nIndex = pLC->FindItem(&lvfi); 
			if(nIndex != -1)
			{
				pLC->DeleteItem(nIndex);
				m_nApps--;
			}
		}
		//add new ones
		for(x=0;x < dlgAddApp.m_nApps;x++)
		{
			pLC->InsertItem(m_nApps,dlgAddApp.m_pszApps[x],2);
			m_nApps++;
		}	
		SetDirty();
	}
	for(x=0;x<dlgAddApp.m_nApps;x++)		delete dlgAddApp.m_pszApps[x];
	for(x=0;x<dlgAddApp.m_nExistApps;x++)	delete dlgAddApp.m_pszExisting[x];
	for(x=0;x<dlgAddApp.m_nRemove;x++)		delete dlgAddApp.m_pszRemove[x];
}


void CSubAddRemove::OnBaddnonsm() 
{
	CTextDlg dlgAddCustom(this,"Add Non Start Menu Program","Type the name of the executable in the space provided. The full path is not necessary.","example.exe","Program:",IDI_APP,FALSE,"\0");
	if(dlgAddCustom.DoModal() == IDOK)
	{
		if(!IsAllowed(dlgAddCustom.m_szItemText))
		{
			CListCtrl* pLC = (CListCtrl*)GetDlgItem(IDC_RUN_LC);
			pLC->InsertItem(m_nApps,dlgAddCustom.m_szItemText,2);
			m_nApps++;
		}
		SetDirty();
	}		
}

void CSubAddRemove::OnRunBadd() 
{
	RunAddItem();		
}

void CSubAddRemove::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	if(pWnd->m_hWnd == GetDlgItem(IDC_RUN_LC)->m_hWnd)
	{
		CMenu mnu;
		mnu.CreatePopupMenu();
		mnu.InsertMenu(0,MF_BYCOMMAND,IDM_CTXT_REMOVE,"Remove");
		mnu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x, point.y,this);
	}
}

void CSubAddRemove::RunRemoveItem()
{
	int x;
	CListCtrl* pLC = (CListCtrl*)GetDlgItem(IDC_RUN_LC);
	for(x = 0;x < (int)m_nApps;x++) if(pLC->GetItemState(x,LVIS_SELECTED)) break;
	if(x == (int)m_nApps) return;
	pLC->DeleteItem(x);
	pLC->Arrange(LVA_ALIGNLEFT);
	m_nApps--;
	SetDirty();
}



BOOL CSubAddRemove::IsAllowed(char* pszTest)
{
	CListCtrl* pLC = (CListCtrl*)GetDlgItem(IDC_RUN_LC);	
	for(int x=0;x<m_nApps;x++)
	{
		char szData[MAX_PATH];
		pLC->GetItemText(x,0,szData,MAX_PATH);
		if(!stricmp(szData,pszTest)) return TRUE;
	}
	return FALSE;
}
