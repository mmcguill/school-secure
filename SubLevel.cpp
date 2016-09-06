// SubLevel.cpp : implementation file
//

#include "stdafx.h"
#include "Secure.h"
#include "SubLevel.h"
#include "mmcgutil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubLevel dialog


CSubLevel::CSubLevel(CWnd* pParent /*=NULL*/) : CSecureChildBase(CSubLevel::IDD, pParent)
{
	
	CDialog::Create(CSubLevel::IDD, pParent);
	//{{AFX_DATA_INIT(CSubLevel)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CSubLevel, CSecureChildBase)
	//{{AFX_MSG_MAP(CSubLevel)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubLevel message handlers

BOOL CSubLevel::OnInitDialog() 
{
	CSecureChildBase::OnInitDialog();
	CSliderCtrl* pSld = (CSliderCtrl*)GetDlgItem(IDC_SLDLEVEL);
	pSld->SetRange(0,3,TRUE);
	return TRUE; 
}

void CSubLevel::DoTrafficLights()
{
	CSliderCtrl* pSld = (CSliderCtrl*)GetDlgItem(IDC_SLDLEVEL);
	CStatic* pNone = (CStatic*)GetDlgItem(IDC_STNONE);
	CStatic* pCust  = (CStatic*)GetDlgItem(IDC_STCUSTOM);
	CStatic* pStd  = (CStatic*)GetDlgItem(IDC_STSTD);
	CStatic* pHigh = (CStatic*)GetDlgItem(IDC_STHIGH);
	switch(pSld->GetPos())
	{
	case 3: //None ie Red
		pNone->SetIcon(AfxGetApp()->LoadIcon(IDI_LEVELNONE));
		pCust->SetIcon(AfxGetApp()->LoadIcon(IDI_LEVELCUSTOM_OFF));
		pStd->SetIcon( AfxGetApp()->LoadIcon(IDI_LEVELSTANDARD_OFF));
		pHigh->SetIcon(AfxGetApp()->LoadIcon(IDI_LEVELHIGH_OFF));
		break;
	case 2: //Custom
		pNone->SetIcon(AfxGetApp()->LoadIcon(IDI_LEVELNONE_OFF));
		pCust->SetIcon(AfxGetApp()->LoadIcon(IDI_LEVELCUSTOM));
		pStd->SetIcon( AfxGetApp()->LoadIcon(IDI_LEVELSTANDARD_OFF));
		pHigh->SetIcon(AfxGetApp()->LoadIcon(IDI_LEVELHIGH_OFF));
		break;
	case 1:
		pNone->SetIcon(AfxGetApp()->LoadIcon(IDI_LEVELNONE_OFF));
		pCust->SetIcon(AfxGetApp()->LoadIcon(IDI_LEVELCUSTOM_OFF));
		pStd->SetIcon( AfxGetApp()->LoadIcon(IDI_LEVELSTANDARD));
		pHigh->SetIcon(AfxGetApp()->LoadIcon(IDI_LEVELHIGH_OFF));
		break; //Standard
	case 0:
		pNone->SetIcon(AfxGetApp()->LoadIcon(IDI_LEVELNONE_OFF));
		pCust->SetIcon(AfxGetApp()->LoadIcon(IDI_LEVELCUSTOM_OFF));
		pStd->SetIcon( AfxGetApp()->LoadIcon(IDI_LEVELSTANDARD_OFF));
		pHigh->SetIcon(AfxGetApp()->LoadIcon(IDI_LEVELHIGH));
		break; //High
	default:
		MessageBox("Error - Invalid Slider Value");
		break;
	}
	//Invalidate();
}

void CSubLevel::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	SetDirty();
	DoTrafficLights();
	CSecureChildBase::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CSubLevel::LoadSettings()
{
	CSliderCtrl* pSld = (CSliderCtrl*)GetDlgItem(IDC_SLDLEVEL);
	pSld->SetPos(GetRegInt(HKEY_LOCAL_MACHINE,"Software\\McGuill\\Secure","SecLevel",2));
	DoTrafficLights();
	return TRUE;
}

int CSubLevel::SaveSettings()
{
	CSliderCtrl* pSld = (CSliderCtrl*)GetDlgItem(IDC_SLDLEVEL);
	int nLevel = pSld->GetPos();
	if(nLevel != 2) 
	{
		if(MessageBox("You have chosen a non custom security level.\n\nThis means MSS Secure will override any of your settings and implement its own settings.\n Is This OK?","Non Custom Security Level",MB_YESNO | MB_ICONEXCLAMATION) == IDNO) return 0; //stop processing - error, but dont quit
	}

	switch(nLevel)
	{
	case 0: //High
		SetRegInt(HKEY_LOCAL_MACHINE,"Software\\McGuill\\Secure","SecLevel",0);
		//
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoSetFolders",1); //No CP
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"DisableRegistryTools",1); //No Regedit
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\WinOldApp",	"Disabled",1);//no Dos Prompt
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoEntireNetwork",1); //No Entire Net
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoWorkgroupContents",1); // no Workg
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDispCPL",1); // no disp in CP
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDevMgrPage",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoConfigPage",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoFileSysPage",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoVirtMemPage",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoNetSetup",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoPrinterTabs",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoAddPrinter",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoDeletePrinter",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoFind",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoRun",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoSetTaskbar",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoSecCPL",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoPwdPage",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoAdminPage",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoProfilePage",1);
		//now High Settings
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoDesktop",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\WinOldApp",	"NoRealMode",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoTrayContextMenu",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoViewContextMenu",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoNetConnectDisconnect",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoClose",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoStartMenuSubFolders",1);
		SetRegInt(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"AlphanumPwds",1);
		SetRegInt(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"DisablePwdCaching",1);
		SetRegString(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\WinLogon","DontDisplayLastUserName","1");
		SetRegInt(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network", "MinPwdLen",8);
		SetRegInt(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"HideSharePwds",1);
		//
		return 2; //2 means stop processing other settings and quit saving after this
		break;
	case 1: //Standard
		SetRegInt(HKEY_LOCAL_MACHINE,"Software\\McGuill\\Secure","SecLevel",1);
		//
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoSetFolders",1); //No CP
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"DisableRegistryTools",1); //No Regedit
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\WinOldApp",	"Disabled",1);//no Dos Prompt
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoEntireNetwork",1); //No Entire Net
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoWorkgroupContents",1); // no Workg
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDispCPL",1); // no disp in CP
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoDevMgrPage",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoConfigPage",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoFileSysPage",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoVirtMemPage",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"NoNetSetup",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoPrinterTabs",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoAddPrinter",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoDeletePrinter",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoFind",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoRun",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",	"NoSetTaskbar",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoSecCPL",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoPwdPage",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoAdminPage",1);
		SetRegInt(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",	"NoProfilePage",1);
		SetRegInt(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",	"HideSharePwds",1);
		//
		return 2; //2 means stop processing other settings and quit saving after this
		break;
	case 2:
		SetRegInt(HKEY_LOCAL_MACHINE,"Software\\McGuill\\Secure","SecLevel",2);
		return 1; //custom so process as many other settings as u want
		break;
	case 3: //None
		SetRegInt(HKEY_LOCAL_MACHINE,"Software\\McGuill\\Secure","SecLevel",3);
		//
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
		//
		return 2; //2 means stop processing other settings and quit saving after this
		break;
	}
	return 1;
}
