// SecureDlg.cpp : implementation file
//
#include "stdafx.h"
#include "Secure.h"
#include "SecureDlg.h"
#include "mmcgutil.h"
#include "shlobj.h"
#include "setpass.h"

//child dlgs
#include "sublevel.h"
#include "subgeneral.h"
#include "SubDisplay.h"
#include "SubSystem.h"
#include "SubNetwork.h"
#include "SubPrinters.h"
#include "SubStartMenu.h"
//#include "SubDeskIcons.h"
#include "SubDrives.h"
#include "SubPassword.h"
#include "SubAddRemove.h"
#include "SubPWSet.h"


//#include "textdlg.h"
//#include "AddAppDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_ABOUT_ANIMATION_TIMER 1337
#define ABOUT_ANIMATION_INTERVAL 50
#define SAVE_DATALEN 32
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	//}}AFX_VIRTUAL

// Implementation
protected:
	char m_cAniIndex;
	void OnCancel();
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnBcontact();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HICON m_hIcon[8];
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BCONTACT, OnBcontact)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//
	char szOwner[32],szAboutTxt[MAX_PATH];
	GetRegStringText(HKEY_LOCAL_MACHINE,"Software\\McGuill\\Secure","RegOwner",szOwner,"<Unknown>");

#ifdef __DEMO__
	wsprintf(szAboutTxt,"\nMcGuill Secure Trial Version 1.1 \nRegistered To %s\n\nMcGuill Software Solutions\nCopyright © 2000",szOwner);
#else
	wsprintf(szAboutTxt,"\nMcGuill Secure Version 1.1\nRegistered To %s\n\nMcGuill Software Solutions\nCopyright © 2000",szOwner);
#endif
	//
	SetDlgItemText(IDC_STABOUT,szAboutTxt);
	//
	m_cAniIndex = 0;
	m_hIcon[0] = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon[1] = AfxGetApp()->LoadIcon(IDI_ABOUTANI0);
	m_hIcon[2] = AfxGetApp()->LoadIcon(IDI_ABOUTANI1);
	m_hIcon[3] = AfxGetApp()->LoadIcon(IDI_ABOUTANI2);
	m_hIcon[4] = AfxGetApp()->LoadIcon(IDI_ABOUTANI3);
	m_hIcon[5] = AfxGetApp()->LoadIcon(IDI_ABOUTANI4);
	m_hIcon[6] = AfxGetApp()->LoadIcon(IDI_ABOUTANI5);
	m_hIcon[7] = AfxGetApp()->LoadIcon(IDI_ABOUTANI6);
	
	CButton* pBtn = (CButton*)GetDlgItem(IDOK);
	pBtn->SetIcon(m_hIcon[m_cAniIndex]);

	CStatic* pSt = (CStatic*)GetDlgItem(IDC_STLOGO);
	pSt->SetBitmap((HBITMAP)LoadImage(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_MSSLOGO),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE | LR_LOADMAP3DCOLORS));
	//
	SetTimer(ID_ABOUT_ANIMATION_TIMER,ABOUT_ANIMATION_INTERVAL,NULL);	
	return TRUE;
}

void CAboutDlg::OnOK() 
{
	KillTimer(ID_ABOUT_ANIMATION_TIMER);
	CDialog::OnOK();
}

void CAboutDlg::OnTimer(UINT nIDEvent) 
{
	m_cAniIndex++;
	if(m_cAniIndex > 7) m_cAniIndex = 0;
	//
	CButton* pBtn = (CButton*)GetDlgItem(IDOK);
	pBtn->SetIcon(m_hIcon[m_cAniIndex]);
	CDialog::OnTimer(nIDEvent);
}

void CAboutDlg::OnCancel()
{
}

void CAboutDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	CStatic* pSt = (CStatic*)GetDlgItem(IDC_STLOGO);
	DeleteObject(pSt->GetBitmap());
}
/////////////////////////////////////////////////////////////////////////////
// CSecureDlg dialog

CSecureDlg::CSecureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSecureDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSecureDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_cSubIndex = 0;
	//
	lstrcpy(m_szSubArea[0],"Security Level"); //must be first page!!! - else app wont work
	lstrcpy(m_szSubArea[1],"General");
	lstrcpy(m_szSubArea[2],"Display");
	lstrcpy(m_szSubArea[3],"System");
	lstrcpy(m_szSubArea[4],"Network");
	lstrcpy(m_szSubArea[5],"Printers");
    lstrcpy(m_szSubArea[6],"Start Menu");
	//lstrcpy(m_szSubArea[7],"Desktop Icons");
	lstrcpy(m_szSubArea[7],"Show Drives");
	lstrcpy(m_szSubArea[8],"Passwords");
	lstrcpy(m_szSubArea[9],"A/D Programs");
	lstrcpy(m_szSubArea[10],"PW Settings");
	//
	m_hSubIcon[0] = AfxGetApp()->LoadIcon(IDI_LEVEL);
	m_hSubIcon[1] = AfxGetApp()->LoadIcon(IDI_GENERAL);
	m_hSubIcon[2] = AfxGetApp()->LoadIcon(IDI_DISPLAY);
	m_hSubIcon[3] = AfxGetApp()->LoadIcon(IDI_SYSTEM);
	m_hSubIcon[4] = AfxGetApp()->LoadIcon(IDI_NETWORK);
	m_hSubIcon[5] = AfxGetApp()->LoadIcon(IDI_PRINTERS);
	m_hSubIcon[6] = AfxGetApp()->LoadIcon(IDI_STARTMENU);
	//m_hSubIcon[7] = AfxGetApp()->LoadIcon(IDI_DESKICONS);
	m_hSubIcon[7] = AfxGetApp()->LoadIcon(IDI_DRIVES);
	m_hSubIcon[8] = AfxGetApp()->LoadIcon(IDI_PASSWORD);
	m_hSubIcon[9] = AfxGetApp()->LoadIcon(IDI_PROGRAMS);
	m_hSubIcon[10] = AfxGetApp()->LoadIcon(IDI_PASSWORD_SET);
	//
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bDirty = FALSE;
	//m_nApps=0;
	
}

BEGIN_MESSAGE_MAP(CSecureDlg, CDialog)
	//{{AFX_MSG_MAP(CSecureDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDAPPLY, OnApply)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_SUBAREAS, OnItemchangedSubareas)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_OPTIONS_SETSECURITYPASSWORD,OnSetPass)
	ON_COMMAND(ID_OPTIONS_SAVECURRENTCONFIGURATION,OnSaveConfig)
	ON_COMMAND(ID_OPTIONS_LOADCONFIGURATION,OnLoadConfig)
	ON_COMMAND(ID_HELP_ABOUT,OnAbout)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CSecureDlg message handlers

void CSecureDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else CDialog::OnSysCommand(nID, lParam);
}

/////////////////////////////////////////////////////////////////////

void CSecureDlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}

/////////////////////////////////////////////////////////////////////

HCURSOR CSecureDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/////////////////////////////////////////////////////////////////////

BOOL CSecureDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	//CMenu* pSysMenu = GetSystemMenu(FALSE);
	//CString strAboutMenu;
	//strAboutMenu.LoadString(IDS_ABOUTBOX);
	//if (!strAboutMenu.IsEmpty())
	//{
	//	pSysMenu->AppendMenu(MF_SEPARATOR);
	//	pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	//}
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

#ifdef __DEMO__
	SetWindowText("McGuill Secure Trial Version");
#endif
	//Set up Sub Area Font
	CFont font;
	font.CreateStockObject(ANSI_VAR_FONT);
	LOGFONT lf;
	font.GetLogFont(&lf);
	lf.lfHeight = 34;
	m_fnt.CreateFontIndirect(&lf);

	//Set up invalidation rectangle
	CRect rc1,rc2;
	GetDlgItem(IDC_STAREATEXT)->GetWindowRect(&rc1);
	GetDlgItem(IDC_AREAICON)->GetWindowRect(&rc2);
	ScreenToClient(&rc1);
	ScreenToClient(&rc2);
	m_rcInv.SetRect(rc2.left,rc2.top,rc1.right,rc1.bottom);

	//Set up Image List
	m_IL.Create(32,32,TRUE,NUM_SUBITEMS,0);
	for(int x=0;x<NUM_SUBITEMS;x++) m_IL.Add(m_hSubIcon[x]);
	
	//Set up Left Side Selector
	CListCtrl* pLC = (CListCtrl*)GetDlgItem(IDC_SUBAREAS);
	pLC->SetImageList(&m_IL,LVSIL_NORMAL);
	for(x=0;x<NUM_SUBITEMS;x++)	pLC->InsertItem(x,m_szSubArea[x],x);

	//Create and Move All Dialogs Into place
	pSubDlg[0] =  new CSubLevel(this);
	pSubDlg[1] =  new CSubGeneral(this);
	pSubDlg[2] =  new CSubDisplay(this);
	pSubDlg[3] =  new CSubSystem(this);
	pSubDlg[4] =  new CSubNetwork(this);
	pSubDlg[5] =  new CSubPrinters(this);
    pSubDlg[6] =  new CSubStartMenu(this);
	//pSubDlg[7] =  new CSubDeskIcons(this);
	pSubDlg[7] =  new CSubDrives(this);
	pSubDlg[8] =  new CSubPassword(this);
	pSubDlg[9] = new CSubAddRemove(this);
	pSubDlg[10] = new CSubPWSet(this);
	//
	CRect rect;
	GetDlgItem(IDC_STDLGPLACE)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	for(x=0;x<NUM_SUBITEMS;x++)	pSubDlg[x]->MoveWindow(rect);

	//Load All the Settings and disable apply button
	LoadSettings();
	GetDlgItem(IDAPPLY)->EnableWindow(FALSE);
	
	//do the thang
	pLC->SetItem(0,0,LVIF_STATE,0,0,LVIS_SELECTED,LVIS_SELECTED,0);
	m_cSubIndex=0;
	ShowDetails();
	return TRUE;  
}

/////////////////////////////////////////////////////////////////////

void CSecureDlg::OnItemchangedSubareas(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	GetSelItem();
	if(m_cSubIndex==-1) return;
	ShowDetails();	
	*pResult = 0;
}

/////////////////////////////////////////////////////////////////////

void CSecureDlg::ShowDetails()
{
	InvalidateRect(m_rcInv);

	//Show correct child dialog
	for(int x=0;x<NUM_SUBITEMS;x++) pSubDlg[x]->ShowWindow(SW_HIDE);
	pSubDlg[m_cSubIndex]->ShowWindow(SW_SHOW);
}

/////////////////////////////////////////////////////////////////////

void CSecureDlg::OnCancel() 
{
	if(m_bDirty)
	{
		if(MessageBox("Are You Sure You Want To Quit Without Implementing Changes?","Quit Without Implementing Changes?",MB_YESNO | MB_ICONQUESTION) == IDNO) return;
	}
	CDialog::OnCancel();
}

/////////////////////////////////////////////////////////////////////

void CSecureDlg::OnOK() 
{
	if(m_bDirty)
	{
		if(SaveSettings() == FALSE)
		{
			return;
		}

		//if(IDYES == MessageBox(
		//	"You have made changes which require a reboot.\n"
		//	"Do you want to restart your computer now?",
		//	"McGuill Secure - Changes Require Restart.",
		//	MB_YESNO | MB_ICONQUESTION))
		//{
		//	ExitWindowsEx(EWX_REBOOT,0);
		//}

		MessageBox(	"You have made changes which may require a reboot.\n",
					"McGuill Secure - Changes may require reboot.",MB_OK);

	}
	CDialog::OnOK();
}

/////////////////////////////////////////////////////////////////////

void CSecureDlg::OnApply() 
{
	if(m_bDirty)
	{
	    if(SaveSettings() == FALSE) return;
		SetDlgItemText(IDCANCEL,"Close");

		//if(IDYES == MessageBox(
		//	"You have made changes which require a reboot.\n"
		//	"Do you want to restart your computer now?",
		//	"McGuill Secure - Changes Require Restart.",
		//	MB_YESNO | MB_ICONQUESTION))
		//{
		//	ExitWindowsEx(EWX_REBOOT,0);
		//}

		MessageBox(	"You have made changes which may require a reboot.\n",
					"McGuill Secure - Changes may require reboot.",MB_OK);
	}
	m_bDirty = FALSE;
}

/////////////////////////////////////////////////////////////////////

void CSecureDlg::LoadSettings()
{
	for(int x=0;x<NUM_SUBITEMS;x++) pSubDlg[x]->LoadSettings();
	GetDlgItem(IDAPPLY)->EnableWindow(FALSE);
}

/////////////////////////////////////////////////////////////////////

BOOL CSecureDlg::SaveSettings()
{
	int nRet;
	for(int x=0;x<NUM_SUBITEMS;x++) 
	{
		if(pSubDlg[x]->m_IsDirty) 
		{
			nRet = pSubDlg[x]->SaveSettings();
			if(nRet== 0) //Means Error - Stop but dont quit app
			{
				return FALSE;
			}
			else if(nRet == 2) //Stop saving and continue as normal - used for level settings
			{
				break;
			}
		}
	}

	//reload
	for(x=0;x<NUM_SUBITEMS;x++) 
	{
		pSubDlg[x]->LoadSettings();
	}
			
	GetDlgItem(IDAPPLY)->EnableWindow(FALSE);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////

void CSecureDlg::OnSetPass()
{
	CSetPass dlg;
	dlg.DoModal();
}

/////////////////////////////////////////////////////////////////////

void CSecureDlg::OnSaveConfig()
{
	char szBuf[NUM_SUBITEMS][SAVE_DATALEN];
	memset(szBuf,255,NUM_SUBITEMS*SAVE_DATALEN); //fill spaces we dont need with char 255 not 0
	for(int x=0;x<NUM_SUBITEMS;x++) pSubDlg[x]->SaveConfig(szBuf[x]);

	char szSysDir[MAX_PATH];
	GetSystemDirectory(szSysDir,MAX_PATH);

	char szFile[MAX_PATH] = "\0";
	OPENFILENAME ofn;
	ofn.lStructSize =		sizeof(OPENFILENAME); 
	ofn.hwndOwner   =		this->m_hWnd; 
	ofn.lpstrFilter =		"Secure Configuration File\0*.sec\0\0";
	ofn.lpstrCustomFilter=	NULL; 
	ofn.nFilterIndex=		0; 
	ofn.lpstrFile=			szFile; 
	ofn.nMaxFile=			MAX_PATH; 
	ofn.lpstrFileTitle=		NULL; 
	ofn.lpstrInitialDir=	szSysDir; 
	ofn.lpstrTitle=			"Save Secure Configuration"; 
	ofn.Flags=				OFN_EXPLORER | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT; 
	if(GetSaveFileName(&ofn)) 
	{
		CFile fileCfg(szFile,CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);
		fileCfg.Write(szBuf,NUM_SUBITEMS * SAVE_DATALEN);
	}
}

/////////////////////////////////////////////////////////////////////

void CSecureDlg::OnLoadConfig()
{
	char szBuf[NUM_SUBITEMS][SAVE_DATALEN];
	char szFile[MAX_PATH] = "\0";
	OPENFILENAME ofn;

	char szSysDir[MAX_PATH];
	GetSystemDirectory(szSysDir,MAX_PATH);

	ofn.lStructSize =		sizeof(OPENFILENAME); 
	ofn.hwndOwner   =		this->m_hWnd; 
	ofn.lpstrFilter =		"Secure Configuration File\0*.sec\0\0";
	ofn.lpstrCustomFilter=	NULL; 
	ofn.nFilterIndex=		0; 
	ofn.lpstrFile=			szFile; 
	ofn.nMaxFile=			MAX_PATH; 
	ofn.lpstrFileTitle=		NULL; 
	ofn.lpstrInitialDir=	szSysDir; 
	ofn.lpstrTitle=			"Open Secure Configuration"; 
	ofn.Flags=				OFN_EXPLORER | OFN_HIDEREADONLY; 
	if(GetOpenFileName(&ofn))
	{
		CFile fileCfg(szFile,CFile::modeReadWrite | CFile::shareDenyNone);
		fileCfg.Read(szBuf,NUM_SUBITEMS * SAVE_DATALEN);
		fileCfg.Close();

		//Lock and Load
		for(int x=0;x<NUM_SUBITEMS;x++) pSubDlg[x]->LoadConfig(szBuf[x]);

		GetDlgItem(IDAPPLY)->EnableWindow(TRUE);
		m_bDirty = TRUE;
		MessageBox("Click Apply To Implement This Configuration","Secure",MB_ICONINFORMATION);
	}
}

/////////////////////////////////////////////////////////////////////

void CSecureDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // device context for painting

		//Get Text Rect and icon rc
		CRect rcTxt,rcIcon;
		GetDlgItem(IDC_STAREATEXT)->GetWindowRect(&rcTxt);
		GetDlgItem(IDC_AREAICON)->GetWindowRect(&rcIcon);
		ScreenToClient(&rcTxt);
		ScreenToClient(&rcIcon);

		//Background Mode
		dc.SetBkMode(TRANSPARENT);

		//Select Font
		CFont* pfnt = dc.SelectObject(&m_fnt);

		//Do the txt and icon
		dc.TextOut(rcTxt.left,rcTxt.top,m_szSubArea[m_cSubIndex],strlen(m_szSubArea[m_cSubIndex]));
		dc.DrawIcon(rcIcon.left,rcIcon.top,m_hSubIcon[m_cSubIndex]);
		
		//Cleanup
		dc.SelectObject(pfnt);
		CDialog::OnPaint();
	}
}

/////////////////////////////////////////////////////////////////////

void CSecureDlg::OnAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}

/////////////////////////////////////////////////////////////////////

void CSecureDlg::GetSelItem()
{
	CListCtrl* pLC = (CListCtrl*)GetDlgItem(IDC_SUBAREAS);	
	for(int x = 0;x < pLC->GetItemCount();x++)
	{
		if(pLC->GetItemState(x,LVIS_SELECTED)) 
		{
			m_cSubIndex = x;
			return;
		}
	}
	m_cSubIndex = -1;
	return;
}

/////////////////////////////////////////////////////////////////////

void CSecureDlg::SetDirty()
{
	m_bDirty = TRUE;
	GetDlgItem(IDAPPLY)->EnableWindow(TRUE);
}

/////////////////////////////////////////////////////////////////////

void CSecureDlg::PostNcDestroy() 
{
	for(int x=0;x<NUM_SUBITEMS;x++) delete pSubDlg[x];	
	CDialog::PostNcDestroy();
}

/////////////////////////////////////////////////////////////////////

void CAboutDlg::OnBcontact() 
{
	CDialog dlg(IDD_CONTACTINFO,this);	
	dlg.DoModal();
}

/////////////////////////////////////////////////////////////////////