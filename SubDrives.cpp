// SubDrives.cpp : implementation file
//

#include "stdafx.h"
#include "Secure.h"
#include "SubDrives.h"
#include "mmcgutil.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubDrives dialog


CSubDrives::CSubDrives(CWnd* pParent /*=NULL*/)
	: CSecureChildBase(CSubDrives::IDD, pParent)
{
	CDialog::Create(CSubDrives::IDD, pParent);
	//{{AFX_DATA_INIT(CSubDrives)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CSubDrives, CSecureChildBase)
	//{{AFX_MSG_MAP(CSubDrives)
	ON_WM_DESTROY()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LCMAIN, OnGetdispinfoLcmain)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_LCEX_ITEMSTATE,OnItemCheck)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubDrives message handlers

BOOL CSubDrives::LoadSettings()
{
	DeleteItems();
	char szDrives[MAX_PATH];
	BOOL bExit = FALSE;
	char* pChar;
	GetLogicalDriveStrings(MAX_PATH,szDrives);
	pChar = szDrives;
	int y = GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer","NoDrives",0);
	//int z = GetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer","NoDriveAutoRun",0);
	int x;
	do
	{
		char szData[MAX_PATH];
		//Visible
		x = (int)pow(2,(int)toupper(pChar[0]) - 65) ;
		int nState;
		if(y & x)	nState=1;
		else		nState=2;
		//Autorun
	//	if(z & x)	szData[0] = 0;
	//	else		szData[0] = 1;
		//Drive Value
		szData[1] = pChar[0];
		//
		SHFILEINFO FileInfo;
		SHGetFileInfo(pChar,0,&FileInfo,sizeof(FileInfo),SHGFI_SMALLICON | SHGFI_SYSICONINDEX | SHGFI_DISPLAYNAME);
		//if(!(pChar[0] == 'a' || pChar[0] == 'b'))
		//{
		//	char szTemp[MAX_PATH];
		//	lstrcpy(szTemp,pChar);
			//lstrcat(szTemp,"autorun.inf");
			//GetPrivateProfileString("autorun","icon","\0\0",&szData[2],MAX_PATH,szTemp);
		//}
		//else
		//{
		//	lstrcpy(&szData[2],"\0\0");
		//}
		//
		CreateLCItem(FileInfo.szDisplayName,FileInfo.iIcon,nState,szData);
		pChar=strchr(pChar,0);
		pChar++;
		if(*pChar == 0) bExit = TRUE;
	}while(!bExit);

	//Display them
	for(x=0;x<m_nDriveItemIndex;x++) m_LC.InsertItem(x,LPSTR_TEXTCALLBACK,I_IMAGECALLBACK);

	//page no longer dirty
	m_IsDirty = FALSE;
	return TRUE;
}

int CSubDrives::SaveSettings()
{
	int nNoDrives = 0;
	//int nAutoRun  = 0;
	for(int x=0;x<m_nDriveItemIndex;x++)	
	{
		//char szTemp[MAX_PATH];
		//szTemp[0] = m_pDriveItem[x]->szDataEx[1];
		//szTemp[1] = 0;
		//lstrcat(szTemp,":\\autorun.inf");
		int y = (int)pow(2,(int)toupper(m_pDriveItem[x]->szDataEx[1]) - 65) ;
		if(m_pDriveItem[x]->nState == 1) nNoDrives+=y;
		//if(!m_pDriveItem[x]->szDataEx[0])nAutoRun+=y;
		//if(!(m_pDriveItem[x]->szDataEx[1] == 'a' || m_pDriveItem[x]->szDataEx[1] == 'b'))
		//{
		//	if(!m_pDriveItem[x]->szDataEx[2] == 0) WritePrivateProfileString("Autorun","icon",&m_pDriveItem[x]->szDataEx[2],szTemp);
		//	else DeleteFile(szTemp);
		//}
	}
	if(nNoDrives)	SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer","NoDrives",nNoDrives);
	else			DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer","NoDrives");
	//if(nAutoRun)	SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer","NoDriveAutoRun",nAutoRun);
	//else			DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer","NoDriveAutoRun");
	return 1;
}

BOOL CSubDrives::OnInitDialog() 
{
	CSecureChildBase::OnInitDialog();
	m_LC.SubclassDlgItem(IDC_LCMAIN,this);
	m_LC.SetMode(0);
	return TRUE;
}

LONG CSubDrives::OnItemCheck(UINT wParam,LONG lParam)
{
	if(m_pDriveItem[wParam]->nState == 1)
	{
		m_pDriveItem[wParam]->nState = 2;
	}
	else if(m_pDriveItem[wParam]->nState == 2)
	{
		m_pDriveItem[wParam]->nState = 1;
	}
	m_LC.Update(wParam);
	SetDirty();
	return 0;
}

void CSubDrives::DeleteItems()
{
	if(m_nDriveItemIndex)
	{
		for(int y=0;y<m_nDriveItemIndex;y++) delete m_pDriveItem[y];
		m_nDriveItemIndex=0;
	}
	m_LC.DeleteAllItems();
}

void CSubDrives::CreateLCItem(char* pszDes, int nIcon, int nState, char* pszDataEx)
{
	if(m_nDriveItemIndex<32)
	{
		m_pDriveItem[m_nDriveItemIndex] = new LC_ITEM;		
		lstrcpy(m_pDriveItem[m_nDriveItemIndex]->szText,pszDes);
		m_pDriveItem[m_nDriveItemIndex]->nIcon = nIcon;
		m_pDriveItem[m_nDriveItemIndex]->nState =nState;
		memcpy(m_pDriveItem[m_nDriveItemIndex]->szDataEx,pszDataEx,MAX_PATH);
		m_nDriveItemIndex++;
	}
}

void CSubDrives::OnDestroy() 
{
	CSecureChildBase::OnDestroy();
	DeleteItems();	
}

void CSubDrives::OnGetdispinfoLcmain(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo      = (LV_DISPINFO*)pNMHDR;
	pDispInfo->item.mask		= LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	pDispInfo->item.state		= INDEXTOSTATEIMAGEMASK(m_pDriveItem[pDispInfo->item.iItem]->nState); 
	pDispInfo->item.stateMask	= LVIS_STATEIMAGEMASK; 
	pDispInfo->item.pszText		= m_pDriveItem[pDispInfo->item.iItem]->szText;	 
	pDispInfo->item.cchTextMax	= strlen(m_pDriveItem[pDispInfo->item.iItem]->szText); 
	pDispInfo->item.iImage		= m_pDriveItem[pDispInfo->item.iItem]->nIcon;
	pDispInfo->item.lParam		= 0;    
	*pResult = 0;
}

