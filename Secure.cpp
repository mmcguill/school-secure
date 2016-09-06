// Secure.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Secure.h"
#include "SecureDlg.h"
#include "splashdlg.h"
#include "passworddlg.h"
#include "mmcgutil.h"
#include "setpass.h"
#include <shlobj.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define HELPFILE "secure.hlp"

#ifdef __DEMO__ 
	#define TRIAL_ENCODE 0xCC1FBA29
	#define TRIAL_DAYS 30
#endif
/////////////////////////////////////////////////////////////////////////////
// CSecureApp

BEGIN_MESSAGE_MAP(CSecureApp, CWinApp)
	//{{AFX_MSG_MAP(CSecureApp)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSecureApp construction

CSecureApp::CSecureApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSecureApp object

CSecureApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSecureApp initialization

BOOL CSecureApp::InitInstance()
{
	if(__argc > 1){
		if(!stricmp(__argv[1],"/trial")){
			#ifndef __DEMO__
				return FALSE;
			#endif
		}
	}

	AfxOleInit();

	#ifdef __DEMO__
		int nInstall= 0;
		int nEncode = 0;
		char szTrial[MAX_PATH];
		nInstall = GetRegInt(HKEY_LOCAL_MACHINE,"Software\\McGuill\\Secure","InstallTod",0);
		if(!nInstall)
		{
			TrialUninstall();
			MessageBox(NULL,"The Registry for McGuill Secure has been interfered with, McGuill Secure has been uninstalled.","Registry Problem",MB_OK);
			return FALSE;
		}
		else{
			int nDays = TRIAL_DAYS - ((time(NULL)/(24*60*60)) - (nInstall ^ TRIAL_ENCODE));
			if(nDays < 0 || nDays > 30){
				TrialUninstall();
				MessageBox(NULL,"McGuill Secure has expired. McGuill Secure has been uninstalled.","Trial Expiration",MB_OK);
				return FALSE;
			}
			else 
			{
				//evrything should still be functioning
				if(__argc > 1){
					if(!stricmp(__argv[1],"/trial")) return FALSE; //if its a startup check then close
				}
				wsprintf(szTrial,"This is a trial version of McGuill Secure.\nYou have %d days left, before Secure stops functioning.",nDays);
				MessageBox(NULL,szTrial,"Trial Version",MB_OK);
			}
		}
	#endif
	//
	if(ValueExists(HKEY_LOCAL_MACHINE,"Software\\McGuill\\Secure","optcheck"))
	{
		CPasswordDlg* pDlg = new CPasswordDlg;
		if(pDlg->DoModal() == IDOK)
		{
			delete pDlg;
		}
		else
		{
			delete pDlg;
			return FALSE;
		}

	}
	//else
	//{
	//	MessageBox(NULL,"Fault In Registry.","Fault - Closing Secure",MB_ICONEXCLAMATION);
	//	//CSetPass dlg;
	//	//dlg.DoModal();
	//	//Setup sets password
	//	return FALSE;
	//}


	//
	CSecureDlg dlg;
	m_pMainWnd = &dlg;
	//
	CSplashDlg dlgSplash;
	dlgSplash.Create(IDD_SPLASH);
	//
	dlg.DoModal();
	AfxOleTerm();
	return FALSE;
}


void CSecureApp::WinHelp(DWORD dwData, UINT nCmd) 
{
	//::WinHelp(m_pMainWnd->m_hWnd,HELPFILE,HELP_FINDER,0);
	//CWinApp::WinHelp(0,HELP_FINDER);
	//CWinApp::WinHelp(dwData, nCmd);
}

void CSecureApp::TrialUninstall()
{
	//remove shortcut
	LPITEMIDLIST pidl;
	if(SHGetSpecialFolderLocation(NULL, CSIDL_STARTMENU,&pidl) == NOERROR)
	{
		char szShortcut[MAX_PATH];
		SHGetPathFromIDList(pidl,szShortcut);
		//create accessories\system tools
		//lstrcat(szShortcut,"McGuill Secure.lnk");
		lstrcat(szShortcut,"\\Programs\\Accessories\\System Tools\\McGuill Secure.lnk");
		DeleteFile(szShortcut);
	}
	//Delete Actual Secure.exe
	char szTemp[MAX_PATH];
	if(GetRegStringText(HKEY_LOCAL_MACHINE,"Software\\McGuill\\Secure","InstallFile",szTemp,""))
	{
		char szWinInitFile[MAX_PATH];
		GetWindowsDirectory(szWinInitFile, MAX_PATH);
		lstrcat(szWinInitFile, "\\WININIT.INI");
		WritePrivateProfileString("Rename", "NUL", szTemp, szWinInitFile);
	}
	//Take reg entries
	DeleteRegKey(HKEY_LOCAL_MACHINE,"Software\\McGuill\\Secure");
	//Disable all restrictions
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\WinOldApp",	"Disabled");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"DisableRegistryTools");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\WinOldApp",	"NoRealMode");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoDesktop");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoEntireNetwork");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoFind");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoSetFolders");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoRun");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoClose");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoStartMenuSubFolders");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoSetTaskbar");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoWorkgroupContents");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoTrayContextMenu");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoViewContextMenu");
	//Display
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDispCPL");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDispBackgroundPage");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDispScrSavPage");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDispAppearancePage");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDispSettingsPage");
	//Network
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoNetSetup");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoNetSetupIdPage");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoNetSetupSecurityPage");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoNetConnectDisconnect");
	//Passwords CPL
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoSecCPL");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoPwdPage");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoAdminPage");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoProfilePage");
	//Printers 
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoPrinterTabs");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoAddPrinter");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoDeletePrinter");
	//System Cpl			
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDevMgrPage");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoConfigPage");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoFileSysPage");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoVirtMemPage");
	//Drives
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer","NoDrives");
	//Passwords
	DeleteRegValue(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"AlphanumPwds");
	DeleteRegValue(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"DisablePwdCaching");
	DeleteRegValue(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"HideSharePwds");
	DeleteRegValue(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\WinLogon","DontDisplayLastUserName");
	//Min Length
	DeleteRegValue(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network", "MinPwdLen");
	//Run Apps
	DeleteRegKey(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\RestrictRun");
	DeleteRegValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer","RestrictRun");	
}
