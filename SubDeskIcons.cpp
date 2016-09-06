// SubDeskIcons.cpp : implementation file
//
#include "stdafx.h"
#include "Secure.h"
#include "SubDeskIcons.h"
#include "mmcgutil.h"
#include <shlobj.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_LCEX_ITEMSTATE WM_USER+1
//#define WM_UPDATECHECKDATA WM_USER+5
/////////////////////////////////////////////////////////////////////////////
// CSubDeskIcons dialog


CSubDeskIcons::CSubDeskIcons(CWnd* pParent /*=NULL*/)
	: CSecureChildBase(CSubDeskIcons::IDD, pParent)
{
	CDialog::Create(CSubDeskIcons::IDD, pParent);
	m_nDesktopItemIndex=0;
	//{{AFX_DATA_INIT(CSubDeskIcons)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CSubDeskIcons, CSecureChildBase)
	//{{AFX_MSG_MAP(CSubDeskIcons)
	ON_WM_DESTROY()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LCMAIN, OnGetdispinfoLcmain)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_LCEX_ITEMSTATE,OnItemCheck)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubDeskIcons message handlers
BOOL CSubDeskIcons::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	m_LC.SubclassDlgItem(IDC_LCMAIN,this);
	m_LC.SetMode(0);
	return TRUE;
}

BOOL CSubDeskIcons::LoadSettings()
{
	DeleteItems();
	int nState;
	SHFILEINFO FileInfo;
	//My Computer
	nState = 3;
	char szTest[MAX_PATH];
	wsprintf(szTest,".%s","{20D04FE0-3AEA-1069-A2D8-08002B30309D}");
	SHGetFileInfo(szTest,0,&FileInfo,sizeof(FileInfo),SHGFI_USEFILEATTRIBUTES | SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_DISPLAYNAME);
	GetRegStringText(HKEY_CLASSES_ROOT,"CLSID\\{20D04FE0-3AEA-1069-A2D8-08002B30309D}","",szTest,"My Computer");
	CreateLCItem(szTest,FileInfo.iIcon,nState,"{20D04FE0-3AEA-1069-A2D8-08002B30309D}");
	//
	//Printers
	LPITEMIDLIST pIDL;
	SHGetSpecialFolderLocation(this->m_hWnd,CSIDL_PRINTERS,&pIDL);
	SHGetFileInfo((char*)pIDL,0,&FileInfo,sizeof(FileInfo),SHGFI_PIDL | SHGFI_SMALLICON | SHGFI_SYSICONINDEX | SHGFI_DISPLAYNAME);
	nState=4;
	CreateLCItem(FileInfo.szDisplayName,FileInfo.iIcon,nState,"{2227A280-3AEA-1069-A2DE-08002B30309D}");
	//Control Panel
	SHGetSpecialFolderLocation(this->m_hWnd,CSIDL_CONTROLS,&pIDL);
	SHGetFileInfo((char*)pIDL,0,&FileInfo,sizeof(FileInfo),SHGFI_PIDL | SHGFI_SMALLICON | SHGFI_SYSICONINDEX | SHGFI_DISPLAYNAME);
	nState=4;
	CreateLCItem(FileInfo.szDisplayName,FileInfo.iIcon,nState,"{21EC2020-3AEA-1069-A2DD-08002B30309D}");
	//////////////////////
	HKEY hKey;
	if(RegOpenKeyEx(HKEY_CLASSES_ROOT,"CLSID",0,KEY_READ,&hKey) == ERROR_SUCCESS)
	{
		int nIndex = 0;
		int nResult;
        HKEY hKey2;
		char szKeyName[2048];
		char szTemp[2048];
		unsigned long cbSize;
		FILETIME ft;
		do
		{
			cbSize = 2048;
			nResult = RegEnumKeyEx(hKey,nIndex,szKeyName,&cbSize,0,NULL,NULL,&ft);
			wsprintf(szTemp,"%s\\ShellFolder",szKeyName);
			if(RegOpenKeyEx(hKey,szTemp,0,KEY_READ,&hKey2) == ERROR_SUCCESS)
			{
				char szDes[MAX_PATH];
				unsigned long nDesSize;
				nDesSize = MAX_PATH;
				RegCloseKey(hKey2);
				if(!RegOpenKeyEx(hKey,szKeyName,0,KEY_READ,&hKey2))
				{
					if(!RegQueryValueEx(hKey2,"",0,NULL,(unsigned char*)szDes,&nDesSize))
					{
						RegCloseKey(hKey2);
						nState=1;
						char szTest[MAX_PATH];
						wsprintf(szTest,".%s",szKeyName);
						SHGetFileInfo(szTest,0,&FileInfo,sizeof(FileInfo),SHGFI_USEFILEATTRIBUTES | SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
						//Check If Visible
						wsprintf(szTest,"Software\\Microsoft\\Windows\\CurrentVersion\\explorer\\desktop\\namespace\\%s",szKeyName);
						if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,szTest,0,KEY_READ,&hKey2) == ERROR_SUCCESS)
						{
							nState=2;
							RegCloseKey(hKey2);
						}
						CreateLCItem(szDes,FileInfo.iIcon,nState,szKeyName);
					}
				}
			}
			nIndex++;
		}while(nResult == ERROR_SUCCESS);
		RegCloseKey(hKey);
	}
	//Extra Icons
	//Network Neighbourhood
	SHGetSpecialFolderLocation(this->m_hWnd,CSIDL_NETWORK,&pIDL);
	SHGetFileInfo((char*)pIDL,0,&FileInfo,sizeof(FileInfo),SHGFI_PIDL | SHGFI_SMALLICON | SHGFI_SYSICONINDEX | SHGFI_DISPLAYNAME);
	nState=GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer","NoNetHood",0);
	if(nState==0) nState = 2;
	else		  nState = 1;
	CreateLCItem(FileInfo.szDisplayName,FileInfo.iIcon,nState,"{208D2C60-3AEA-1069-A2D7-08002B30309D}");
	
	//Display them
	for(int x=0;x<m_nDesktopItemIndex;x++) m_LC.InsertItem(x,LPSTR_TEXTCALLBACK,I_IMAGECALLBACK);

	//page no longer dirty
	m_IsDirty = FALSE;
	return TRUE;
}

int CSubDeskIcons::SaveSettings()
{
	for(int x = 0;x<m_nDesktopItemIndex;x++)
	{
		//Nethood
		if(!stricmp(m_pDesktopItem[x]->szDataEx,"{208D2C60-3AEA-1069-A2D7-08002B30309D}"))
		{
			if(m_pDesktopItem[x]->nState == 1)	SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer","NoNetHood",1);
			else								DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer","NoNetHood");
			continue;
		}
		if(!stricmp(m_pDesktopItem[x]->szDataEx,"Control Panel"))
		{
			continue;
		}
		if(!stricmp(m_pDesktopItem[x]->szDataEx,"Printers"))
		{
			continue;
		}
		if(m_pDesktopItem[x]->nState == 2)
		{
			char szTemp[MAX_PATH];
			wsprintf(szTemp,"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Desktop\\Namespace\\%s",m_pDesktopItem[x]->szDataEx);
			SetRegString(HKEY_LOCAL_MACHINE,szTemp,"",m_pDesktopItem[x]->szText);
		}
		if(m_pDesktopItem[x]->nState == 1)
		{
			char szTemp[MAX_PATH];
			wsprintf(szTemp,"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Desktop\\Namespace\\%s",m_pDesktopItem[x]->szDataEx);
			DeleteRegKey(HKEY_LOCAL_MACHINE,szTemp);
		}
	}
	//
	LoadSettings();
	return 1;
}

void CSubDeskIcons::DeleteItems()
{
	if(m_nDesktopItemIndex)
	{
		for(int y=0;y<m_nDesktopItemIndex;y++) delete m_pDesktopItem[y];
		m_nDesktopItemIndex=0;
	}
	m_LC.DeleteAllItems();
}

void CSubDeskIcons::OnDestroy() 
{
	CSecureChildBase::OnDestroy();
	DeleteItems();
}

void CSubDeskIcons::CreateLCItem(char* pszDes,int nIcon,int nState,char* pszDataEx)
{
	if(m_nDesktopItemIndex<200)
	{
		m_pDesktopItem[m_nDesktopItemIndex] = new LC_ITEM;		
		lstrcpy(m_pDesktopItem[m_nDesktopItemIndex]->szText,pszDes);
		m_pDesktopItem[m_nDesktopItemIndex]->nIcon = nIcon;
		m_pDesktopItem[m_nDesktopItemIndex]->nState =nState;
		memcpy(m_pDesktopItem[m_nDesktopItemIndex]->szDataEx,pszDataEx,MAX_PATH);
		m_nDesktopItemIndex++;
	}
}

LONG CSubDeskIcons::OnItemCheck(UINT wParam,LONG lParam)
{
	if(m_pDesktopItem[wParam]->nState == 1)
	{
		m_pDesktopItem[wParam]->nState = 2;
	}
	else if(m_pDesktopItem[wParam]->nState == 2)
	{
		m_pDesktopItem[wParam]->nState = 1;
	}
	m_LC.Update(wParam);
	SetDirty();
	return 0;
}

void CSubDeskIcons::OnGetdispinfoLcmain(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	pDispInfo->item.mask		= LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	pDispInfo->item.state		= INDEXTOSTATEIMAGEMASK(m_pDesktopItem[pDispInfo->item.iItem]->nState); 
	pDispInfo->item.stateMask	= LVIS_STATEIMAGEMASK; 
	pDispInfo->item.pszText		= m_pDesktopItem[pDispInfo->item.iItem]->szText;	 
	pDispInfo->item.cchTextMax	= strlen(m_pDesktopItem[pDispInfo->item.iItem]->szText); 
	pDispInfo->item.iImage		= m_pDesktopItem[pDispInfo->item.iItem]->nIcon;
	pDispInfo->item.lParam		= 0;    
	*pResult = 0;
}
