// ListCtrlEx.cpp : implementation file
//
#include "stdafx.h"
#include "secure.h"
#include "ListCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define WM_UPDATECHECKDATA WM_USER+5
/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx

CListCtrlEx::CListCtrlEx()
{
	GetStateIL();
}

CListCtrlEx::~CListCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlEx)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx message handlers
void CListCtrlEx::OnLButtonDown(UINT nFlags, CPoint point) 
{
	unsigned int nTest;
	int nItem = HitTest(point,&nTest);
	if(nTest & LVHT_ONITEMSTATEICON)
	{
		if(m_nMode == 9)
		{
			if(GetItemState(nItem,LVIS_STATEIMAGEMASK) == INDEXTOSTATEIMAGEMASK(1))
			{
				SetItemState(nItem,INDEXTOSTATEIMAGEMASK(2),LVIS_STATEIMAGEMASK);
				::SendMessage(this->GetParent()->m_hWnd, WM_UPDATECHECKDATA,MAKEWPARAM(nItem,2),(long)this->m_hWnd);
			}
			else if(GetItemState(nItem,LVIS_STATEIMAGEMASK) == INDEXTOSTATEIMAGEMASK(2))
			{
				SetItemState(nItem,INDEXTOSTATEIMAGEMASK(1),LVIS_STATEIMAGEMASK);
				::SendMessage(this->GetParent()->m_hWnd,WM_UPDATECHECKDATA,MAKEWPARAM(nItem,1),(long)this->m_hWnd);
			}
			RedrawItems(nItem,nItem);
		}
		else ::SendMessage(GetParent()->m_hWnd,WM_LCEX_ITEMSTATE,nItem,0);
	}
	CListCtrl::OnLButtonDown(nFlags, point);
}

BOOL CListCtrlEx::SetMode(int nMode)
{
	m_nMode = nMode;
	DeleteAllItems();
	DeleteColumn(1);
	DeleteColumn(0);
	ModifyStyle(0,LVS_NOCOLUMNHEADER);
	SetupSysIL();
	switch(m_nMode)
	{
	case 0:
		InsertColumn(0,"",LVCFMT_LEFT,195,0);
		SetImageList(&m_ILStates,LVSIL_STATE);
		break;
	case 1:
		InsertColumn(0,"",LVCFMT_LEFT,195,0);
		SetImageList(&m_ILStates,LVSIL_STATE);
		break;
	case 2:
		InsertColumn(0,"",LVCFMT_LEFT,195,0);
		SetImageList(NULL,LVSIL_STATE);
		break;
	case 3:
		InsertColumn(0,"",LVCFMT_LEFT,195,0);
		SetImageList(&m_ILStates,LVSIL_STATE);
		break;
	case 4:
		InsertColumn(0,"",LVCFMT_LEFT,195,0);
		SetImageList(NULL,LVSIL_STATE);
		break;
	case 5:
		ModifyStyle(LVS_NOCOLUMNHEADER,0);
		SetImageList(NULL,LVSIL_STATE);
		InsertColumn(0,"Folder",LVCFMT_LEFT,80,0);
		InsertColumn(1,"Location",LVCFMT_LEFT,400,0);
		break;
	case 6:
		ModifyStyle(LVS_NOCOLUMNHEADER,0);
		SetImageList(NULL,LVSIL_STATE);
		InsertColumn(0,"Tip No.",LVCFMT_LEFT,40,0);
		InsertColumn(1,"Tip",LVCFMT_LEFT,440,0);
		break;
	case 7:
		InsertColumn(0,"",LVCFMT_LEFT,295,0);
		SetImageList(NULL,LVSIL_STATE);
		break;
	case 8:
		InsertColumn(0,"",LVCFMT_LEFT,395,0);
		SetImageList(NULL,LVSIL_STATE);
		break;
	case 9: //Checked Lc Replacement
		SetImageList(&m_ILStates,LVSIL_STATE);
		break;
	}
	return TRUE;
}

void CListCtrlEx::GetStateIL()
{
	m_ILStates.Create(13,11,TRUE,4,0);
	m_bmpStates.LoadBitmap(IDB_STATE_CHECK);
	m_ILStates.Add(&m_bmpStates,RGB(255,255,255));
}

BOOL CListCtrlEx::SetupSysIL()
{
	CImageList ImageList;
	SHFILEINFO FileInfo;
	HIMAGELIST hImageList = (HIMAGELIST)SHGetFileInfo(".dll",NULL,&FileInfo,sizeof(FileInfo),SHGFI_SMALLICON | SHGFI_SYSICONINDEX | SHGFI_USEFILEATTRIBUTES);
	ImageList.Attach(hImageList);
	SetImageList(&ImageList,LVSIL_SMALL);
	ImageList.Detach();
	return TRUE;
}

int CListCtrlEx::GetSelItem()
{
	for(int x = 0;x < GetItemCount();x++)
	{
		if(GetItemState(x,LVIS_SELECTED)) return x;
	}
	return -1;
}

int CListCtrlEx::InsertItem(int nItem, char* pszText, int nImage, int nState/*=0*/)
{
	if(m_nMode == 9)
	{
		//Do CheckLC Thing
		return CListCtrl::InsertItem(LVIF_IMAGE | LVIF_TEXT | LVIF_STATE,nItem,pszText,INDEXTOSTATEIMAGEMASK(nState),LVIS_STATEIMAGEMASK,nImage,0);
	}
	else return CListCtrl::InsertItem(nItem,pszText,nImage);
}

void CListCtrlEx::SetCheck(int nItem,int nCheck)
{
	if(m_nMode == 9)
	{
		//Do CheckLC Thing
		SetItemState(nItem,INDEXTOSTATEIMAGEMASK(nCheck),LVIS_STATEIMAGEMASK);
		RedrawItems(nItem,nItem);
	}	
}
