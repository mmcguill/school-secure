// AddAppDlg.cpp : implementation file
//
#include "stdafx.h"
#include "secure.h"
#include "AddAppDlg.h"
#include "shlobj.h"
#include "MMcGUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define WM_UPDATECHECKDATA WM_USER+5
/////////////////////////////////////////////////////////////////////////////
// CAddAppDlg dialog
CAddAppDlg::CAddAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddAppDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddAppDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nApps=0;
	m_nRemove =0;
}

BEGIN_MESSAGE_MAP(CAddAppDlg, CDialog)
	//{{AFX_MSG_MAP(CAddAppDlg)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREESTARTMENU, OnSelchangedTreestartmenu)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_UPDATECHECKDATA, UpdateCheckData)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddAppDlg message handlers

BOOL CAddAppDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetupLC();
	GetRegStringText(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders","Start Menu",m_szBaseDir,"C:\\Windows\\Start Menu");
	char szTemp[MAX_PATH];
	wsprintf(szTemp,"%s\\Programs",m_szBaseDir);
	CTreeCtrl* pTC = (CTreeCtrl*)GetDlgItem(IDC_TREESTARTMENU);
	HTREEITEM hThis = pTC->InsertItem("Programs",36,36,TVI_ROOT);
	SetCurrentDirectory(szTemp);
	FillStartMenuTree(hThis);
	return TRUE;
}

void CAddAppDlg::SetupLC()
{
	m_LCEx.SubclassDlgItem(IDC_LCPROGRAMS,this);
	m_LCEx.SetMode(9);
	HIMAGELIST hIL = GetSysImageList();
	if(hIL != NULL)
	{
		CImageList IL;
		CTreeCtrl* pTC = (CTreeCtrl*)GetDlgItem(IDC_TREESTARTMENU);
		IL.Attach(hIL);
		pTC->SetImageList(&IL,TVSIL_NORMAL);
		IL.Detach();
	}
}

void CAddAppDlg::PostNcDestroy() 
{
//	AfxOleTerm();
	CDialog::PostNcDestroy();
}

void CAddAppDlg::OnOK() 
{
	CDialog::OnOK();
}

void CAddAppDlg::FillStartMenuTree(HTREEITEM hParent)
{
	HANDLE			hCurSearch;
	WIN32_FIND_DATA FindData;
	hCurSearch=FindFirstFile("*.*",&FindData);
	if(hCurSearch==NULL) return;
	char szCurDir[MAX_PATH];
	char szTemp[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,szCurDir);
	//
	CTreeCtrl* pTC = (CTreeCtrl*)GetDlgItem(IDC_TREESTARTMENU);
	do
	{
		if(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(lstrcmp(FindData.cFileName,".") && lstrcmp(FindData.cFileName,".."))
			{
				lstrcpy(szTemp,szCurDir);
				if(szTemp[strlen(szTemp)-1] != '\\') lstrcat(szTemp,"\\");
				lstrcat(szTemp,FindData.cFileName);
				//
				HTREEITEM hThis = pTC->InsertItem(FindData.cFileName,36,36,hParent);
				if(SetCurrentDirectory(szTemp))	FillStartMenuTree(hThis);
			}
		}
	}while(FindNextFile(hCurSearch,&FindData));
	FindClose(hCurSearch);
}

void CAddAppDlg::OnSelchangedTreestartmenu(NMHDR* pNMHDR, LRESULT* pResult) 
{
	char szDir[MAX_PATH];
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	GetFullTreePath(pNMTreeView->itemNew.hItem, szDir);
	SetCurrentDirectory(szDir);
	CTreeCtrl* pTC = (CTreeCtrl*)GetDlgItem(IDC_TREESTARTMENU);	
	m_LCEx.DeleteAllItems();
	//
	//
	int x=0;
	HANDLE			hCurSearch;
	WIN32_FIND_DATA FindData;
	hCurSearch=FindFirstFile("*.lnk",&FindData);
	if(hCurSearch==INVALID_HANDLE_VALUE) return;
	do
	{
		if(!(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			char szFindExt[MAX_PATH];
			SHFILEINFO FI;
			SHGetFileInfo(FindData.cFileName,NULL,&FI,sizeof(SHFILEINFO),SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_DISPLAYNAME);
			char szFullPath[MAX_PATH];
			lstrcpy(szFullPath,szDir); 
			if(szFullPath[strlen(szFullPath)-1] != '\\') lstrcat(szFullPath,"\\");
			lstrcat(szFullPath,FindData.cFileName);
			//
			lstrcpy(szFindExt,&FindData.cFileName[strlen(FindData.cFileName) - 4]);	
			if(!stricmp(szFindExt,".lnk"))	
			{
				char szPath[MAX_PATH];
				GetShortcutPath(szPath, szFullPath);
				lstrcpy(szFindExt,&szPath[strlen(szPath) - 4]);
				if(!stricmp(szFindExt,".exe"))
				{
					if(IsAllowed(szPath))
					{
						m_LCEx.InsertItem(x,FI.szDisplayName,FI.iIcon,2);
					}
					else
					{
						m_LCEx.InsertItem(x,FI.szDisplayName,FI.iIcon,1);
					}
					x++;
				}
			}
		}
	}while(FindNextFile(hCurSearch,&FindData));
	FindClose(hCurSearch);
	*pResult = 0;
}

void CAddAppDlg::GetFullTreePath(HTREEITEM hItem, char* pszDir)
{
	char szTemp[MAX_PATH]="\0";
	char szTemp2[MAX_PATH]="\0";
	CTreeCtrl* pTC = (CTreeCtrl*)GetDlgItem(IDC_TREESTARTMENU);	
	if(hItem != TVI_ROOT && hItem != NULL)
	{
		
		CString strText = pTC->GetItemText(hItem);
		lstrcpy(szTemp,(LPCTSTR)strText);
		do
		{
			hItem = pTC->GetParentItem(hItem);
			if(hItem != TVI_ROOT && hItem != NULL)
			{
				strText = pTC->GetItemText(hItem);
				wsprintf(szTemp2,"%s\\%s",(LPCTSTR)strText,szTemp);
				lstrcpy(szTemp,szTemp2);
			}
		}while(hItem != TVI_ROOT && hItem != NULL);
	}
	wsprintf(pszDir,"%s\\%s",m_szBaseDir,szTemp);
}

BOOL CAddAppDlg::IsAllowed(char* pszPath)
{
	char* pCh = strrchr(pszPath,'\\') + 1;
	if(pCh == NULL) pCh=pszPath;
	for(int x=0;x<m_nExistApps;x++)
	{
		if(!stricmp(m_pszExisting[x],pCh)) return TRUE;
	}
	return FALSE;
}

LONG CAddAppDlg::UpdateCheckData(UINT nItemAndState, LONG lhWnd)
{
	int nItem =			LOWORD(nItemAndState);
	int nItemState =	HIWORD(nItemAndState);
	if(nItemState == 2)
	{
		char szText[MAX_PATH];
		m_LCEx.GetItemText(nItem,0,szText,MAX_PATH);
		CTreeCtrl* pTC = (CTreeCtrl*)GetDlgItem(IDC_TREESTARTMENU);
		HTREEITEM hItem = pTC->GetSelectedItem();
		char szFullPath[MAX_PATH];
		char szPath[MAX_PATH];
		GetFullTreePath(hItem, szPath);
		wsprintf(szFullPath,"%s\\%s.lnk",szPath,szText);
		GetShortcutPath(szPath,szFullPath);
		//
		if(!IsAllowed(szPath))
		{
			char* pCh = strrchr(szPath,'\\') + 1;
			if(pCh != NULL)
			{
				m_pszApps[m_nApps] = new char[MAX_PATH];
				m_pszExisting[m_nExistApps] = new char[MAX_PATH];
				lstrcpy(m_pszApps[m_nApps],pCh);
				lstrcpy(m_pszExisting[m_nExistApps],pCh);
				m_nApps++;
				m_nExistApps++;
			}
		}
	}
	else if(nItemState == 1)
	{
		char szText[MAX_PATH];
		m_LCEx.GetItemText(nItem,0,szText,MAX_PATH);
		CTreeCtrl* pTC = (CTreeCtrl*)GetDlgItem(IDC_TREESTARTMENU);
		HTREEITEM hItem = pTC->GetSelectedItem();
		char szFullPath[MAX_PATH];
		char szPath[MAX_PATH];
		GetFullTreePath(hItem, szPath);
		wsprintf(szFullPath,"%s\\%s.lnk",szPath,szText);
		GetShortcutPath(szPath,szFullPath);
		//
		char* pCh = strrchr(szPath,'\\') + 1;
		if(pCh != NULL)
		{
			RemoveAppString(pCh);
		}
	}
	return 0;
}

void CAddAppDlg::RemoveAppString(char* pszString)
{
	m_pszRemove[m_nRemove] = new char[MAX_PATH];
	lstrcpy(m_pszRemove[m_nRemove],pszString);
	m_nRemove++;
	for(int x=0;x<m_nApps;x++)
	{
		if(!stricmp(m_pszApps[x],pszString))
		{
			delete m_pszApps[x];
			for(int y=x;y<m_nApps;y++)
			{
				m_pszApps[y] = m_pszApps[y+1];
			}
			m_nApps--;
			return;
		}
	}
}

void CAddAppDlg::GetShortcutPath(char* pszPath, char* pszFullPath)
{
	LPPERSISTFILE ppf;
	IShellLink* psl;
	OLECHAR wsz[MAX_PATH];
	int nRes = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl);
	if(nRes == S_OK)
	{
		psl->QueryInterface(IID_IPersistFile, (LPVOID*) &ppf);
		MultiByteToWideChar(CP_ACP, 0, pszFullPath, -1, wsz, MAX_PATH);
		ppf->Load(wsz, STGM_READ);
		WIN32_FIND_DATA wfd;
		psl->GetPath(pszPath,MAX_PATH,&wfd,SLGP_UNCPRIORITY);
		ppf->Release();
		psl->Release();
	}
}