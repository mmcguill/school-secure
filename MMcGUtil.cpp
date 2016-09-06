#include "stdafx.h"
#include "MMcGUtil.h"

void DeleteRegKey(HKEY hRootKey,const char* pszSubKey)
{
	RegDeleteKey(hRootKey,pszSubKey);
}

BOOL DeleteRegValue(HKEY hRootKey,const char* pszSubKey,const char* pszValueName)
{
	HKEY hKey;
	int nResult = RegOpenKeyEx(hRootKey, pszSubKey,0,KEY_WRITE,&hKey);
	if(nResult == ERROR_SUCCESS)
	{
		if(RegDeleteValue(hKey, pszValueName) != ERROR_SUCCESS) return FALSE;
	}
	else return FALSE;
	return TRUE;
}

void SetRegString(HKEY hRootKey,const  char* pszSubKey,const  char* pszValueName,const char* pszData)
{
	HKEY hKey;
	unsigned long nDisp;
	int nResult = RegCreateKeyEx(hRootKey,pszSubKey,0,"",REG_OPTION_NON_VOLATILE,KEY_WRITE,NULL,&hKey,&nDisp);
	if(nResult == ERROR_SUCCESS)
	{
		RegSetValueEx(hKey,pszValueName,0,REG_SZ,(unsigned char*)pszData,strlen(pszData));
		RegCloseKey(hKey);
	}
}

void SetRegData(HKEY hRootKey,char* pszSubKey,char* pszValueName,unsigned char* pcData,int nLen)
{
	HKEY hKey;
	unsigned long nDisp;
	int nResult = RegCreateKeyEx(hRootKey,pszSubKey,0,"",REG_OPTION_NON_VOLATILE,KEY_WRITE,NULL,&hKey,&nDisp);
	if(nResult == ERROR_SUCCESS)
	{
		RegSetValueEx(hKey,pszValueName,0,REG_BINARY,pcData,nLen);
		RegCloseKey(hKey);
	}
}

void SetRegInt(HKEY hRootKey,const char* pszSubKey,const char* pszValueName, int nData)
{
	HKEY hKey;
	unsigned long nDisp;
	int nResult = RegCreateKeyEx(hRootKey,pszSubKey,0,"",REG_OPTION_NON_VOLATILE,KEY_WRITE,NULL,&hKey,&nDisp);
	if(nResult == ERROR_SUCCESS)
	{
		RegSetValueEx(hKey,pszValueName,0,REG_DWORD,(unsigned char*)&nData,sizeof(nData));
		RegCloseKey(hKey);
	}
}

int GetRegInt(HKEY hRootKey,const char* pszSubKey,const char* pszValueName, int nDefaultRet)
{
	HKEY hKey;
	int nTemp;
	unsigned long cbSize;
	int nResult = RegOpenKeyEx(hRootKey,pszSubKey,0,KEY_READ,&hKey);
	if(nResult == ERROR_SUCCESS)
	{
		cbSize=sizeof(nTemp);
		nResult = RegQueryValueEx(hKey,pszValueName,0,NULL,(unsigned char*)&nTemp,&cbSize);
		RegCloseKey(hKey);
		if(nResult == ERROR_SUCCESS)return nTemp;
		else						return nDefaultRet;
	}
	else return nDefaultRet;
}

int GetRegString(HKEY hRootKey,const char* pszSubKey,const char* pszValueName,const char* pszStrCmp, int nDefaultRet)
{
	HKEY hKey;
	char szTemp[2048];
	unsigned long  cbSize;
	int nResult = RegOpenKeyEx(hRootKey,pszSubKey,0,KEY_READ,&hKey);
	if(nResult == ERROR_SUCCESS)
	{
		cbSize=2048;
		nResult = RegQueryValueEx(hKey,pszValueName,0,NULL,(unsigned char*)szTemp,&cbSize);
		RegCloseKey(hKey);
		if(nResult == ERROR_SUCCESS) 
		{
			if(!stricmp(szTemp,pszStrCmp))return !nDefaultRet;
			else return nDefaultRet;
		}else	 return nDefaultRet;
	}else		 return nDefaultRet;
}

BOOL GetRegStringText(HKEY hRootKey,const char* pszSubKey,const char* pszValueName,char* pszReturn,char* pszFail)
{
	HKEY hKey;
	if(RegOpenKeyEx(hRootKey,pszSubKey,0,KEY_READ,&hKey)== ERROR_SUCCESS)
	{
		char			szTemp[2048];
		unsigned long	cbSize = 2048;
		if(RegQueryValueEx(hKey,pszValueName,0,NULL,(unsigned char*)szTemp,&cbSize) == ERROR_SUCCESS)
		{
			if(szTemp[0] != 0)
			{
				lstrcpy(pszReturn,szTemp);
				return TRUE;
			}
			else				lstrcpy(pszReturn,pszFail);
		}
		else
		{
			lstrcpy(pszReturn,pszFail);
		}
		RegCloseKey(hKey);
		return FALSE;
	}
	else
	{
		lstrcpy(pszReturn,pszFail);
		return FALSE;
	}
}

void CopyRegKey(HKEY hRootDest,const char* pszDestSubKey,HKEY hKeySrc)
{
	//this will not move all branches of a key just its values
	HKEY hKeyDest;
	unsigned long nDisp;	
	int nRes;
	int dwIndex=0;
	if(RegCreateKeyEx(hRootDest,pszDestSubKey,0,"",REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKeyDest,&nDisp) != ERROR_SUCCESS) return;
	do
	{
		char szVal[MAX_PATH];
		unsigned long nVal = MAX_PATH;
		char szData[2048];
		unsigned long nData = 2048;
		unsigned long nType;
		nRes = RegEnumValue(hKeySrc,dwIndex,szVal,&nVal,0,&nType,(unsigned char*)szData,&nData);
		if(nRes == ERROR_SUCCESS)
		{
			RegSetValueEx(hKeyDest,szVal,0,nType,(unsigned char*)szData,nData);
		}
		dwIndex++;
	}while(nRes == ERROR_SUCCESS);
	RegCloseKey(hKeyDest);
}

void MoveRegKey(HKEY hRootDest,const char* pszDestSubKey,HKEY hKeySrc)
{
	CopyRegKey(hRootDest,pszDestSubKey,hKeySrc);
	DeleteRegKey(hKeySrc,"");
}

void CopyRegValue(HKEY hRootKey,char* pszSubkey,char* pszValue, char* pszDest)
{
	HKEY hKey;
	unsigned long nDisp;	
	unsigned long nType;
	unsigned long nSize = MAX_PATH;
	char szBuf[MAX_PATH];
	if(RegCreateKeyEx(hRootKey,pszSubkey,0,"",REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&nDisp) != ERROR_SUCCESS) return;
	if(RegQueryValueEx(hKey,pszValue,0,&nType,(unsigned char*)szBuf,&nSize) == ERROR_SUCCESS)
	{
		RegSetValueEx(hKey,pszDest,0,nType,(unsigned char*)szBuf,nSize);
	}
}

BOOL GetRegData(HKEY hRootKey,char* pszSubKey,char* pszValueName,unsigned char* pcData,int nLen)
{
	HKEY hKey;
	int nResult = RegOpenKeyEx(hRootKey,pszSubKey,0,KEY_READ,&hKey);
	if(nResult == ERROR_SUCCESS)
	{
		if(RegQueryValueEx(hKey,pszValueName,0,NULL,pcData,(unsigned long*)&nLen) == ERROR_SUCCESS)
		{
			RegCloseKey(hKey);
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}

BOOL ValueExists(HKEY hRootKey,char* pszSubkey,char* pszValue)
{
	HKEY hKey;
	char			szTemp[MAX_PATH];
	unsigned long	cbSize = MAX_PATH;
	if(RegOpenKeyEx(hRootKey,pszSubkey,0,KEY_READ,&hKey)== ERROR_SUCCESS)
	{
		if(RegQueryValueEx(hKey,pszValue,0,NULL,(unsigned char*)szTemp,&cbSize) == ERROR_SUCCESS)
		{
			RegCloseKey(hKey);
			return TRUE;
		}
		else
		{
			RegCloseKey(hKey);
			return FALSE;
		}
	}
	return FALSE;
}

int RegItemNumChildren(HKEY hRootKey,char* pszSubkey)
{
	HKEY hKey;
	if(RegOpenKeyEx(hRootKey,pszSubkey,0,KEY_READ,&hKey)== ERROR_SUCCESS)
	{
		char szClass[MAX_PATH];
		unsigned long nClasslen = MAX_PATH;
		unsigned long nSubKeys,nMaxSubKeyLen,nMaxClassLen,nNumValues,nMaxValueNameLen,nMaxValueLen;
		FILETIME ftLWT;
		if(RegQueryInfoKey(hKey,szClass,&nClasslen,0,&nSubKeys,&nMaxSubKeyLen,&nMaxClassLen,&nNumValues,&nMaxValueNameLen,&nMaxValueLen,NULL,&ftLWT) == ERROR_SUCCESS)
		{
			return nSubKeys;
		}
	}
	return 0;
}

HIMAGELIST GetSysImageList()
{
	SHFILEINFO FileInfo;
	HIMAGELIST hImageList = (HIMAGELIST)SHGetFileInfo(".dll",NULL,&FileInfo,sizeof(FileInfo),SHGFI_SMALLICON | SHGFI_SYSICONINDEX | SHGFI_USEFILEATTRIBUTES);
	return hImageList;
}

int GetIconIndexFromExt(char* pszExt)
{
	SHFILEINFO FI;
	SHGetFileInfo(pszExt,0,&FI,sizeof(SHFILEINFO),SHGFI_USEFILEATTRIBUTES | SHGFI_SMALLICON | SHGFI_SYSICONINDEX);
	return FI.iIcon;
}

int GetIconIndexFromActFile(char* pszFile)
{
	SHFILEINFO FI;
	SHGetFileInfo(pszFile,0,&FI,sizeof(SHFILEINFO), SHGFI_SMALLICON | SHGFI_SYSICONINDEX);
	return FI.iIcon;
}