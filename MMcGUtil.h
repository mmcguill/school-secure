#ifndef MMCG_UTILS
	#define MMCG_UTILS
#endif

BOOL	ValueExists(HKEY hRootKey,char* pszSubkey,char* pszValue);
BOOL	DeleteRegValue(HKEY hRootKey,const char* pszSubKey,const char* pszValueName);
void	DeleteRegKey(HKEY hRootKey,const char* pszSubKey);
void	SetRegString(HKEY hRootKey,const char* pszSubKey,const char* pszValueName,const char* pszData);
void	SetRegData(HKEY hRootKey,char* pszSubKey,char* pszValueName,unsigned char* pcData,int nLen);
void	SetRegInt(HKEY hRootKey,const char* pszSubKey,const char* pszValueName, int nData);
int		GetRegString(HKEY hRootKey,const char* pszSubKey,const char* pszValueName,const char* pszStrCmp, int nDefaultRet);
int		GetRegInt(HKEY hRootKey,const char* pszSubKey,const char* pszValueName, int nDefaultRet);
BOOL	GetRegStringText(HKEY hRootKey,const char* pszSubKey,const char* pszValueName,char* pszReturn,char* pszFail);
BOOL    GetRegData(HKEY hRootKey,char* pszSubKey,char* pszValueName,unsigned char* pcData,int nLen);
void	CopyRegKey(HKEY hRootDest,const char* pszDestSubKey,HKEY hKeySrc);
void	CopyRegValue(HKEY hRootKey,char* pszSubkey,char* pszValue, char* pszDest);
void	MoveRegKey(HKEY hRootDest,const char* pszDestSubKey,HKEY hKeySrc);
HIMAGELIST GetSysImageList();
int		GetIconIndexFromExt(char* pszExt);
int		GetIconIndexFromActFile(char* pszFile);
int RegItemNumChildren(HKEY hRootKey,char* pszSubkey);
