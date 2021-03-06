﻿/*!	@file
	@brief CDicMgrクラス定義

	@author Norio Nakatani
	@date	1998/11/05 作成
*/
/*
	Copyright (C) 1998-2001, Norio Nakatani

	This source code is designed for sakura editor.
	Please contact the copyright holder to use this code for other purpose.
*/

#ifndef _CDICMGR_H_
#define _CDICMGR_H_

#include <Windows.h>
#include "util/container.h"
#include "_main/global.h"

/*-----------------------------------------------------------------------
クラスの宣言
-----------------------------------------------------------------------*/
class CDicMgr
{
public:
	/*
	||  Constructors
	*/
	CDicMgr();
	~CDicMgr();

	/*
	||  Attributes & Operations
	*/
//	BOOL Open( char* );
	static BOOL Search( const wchar_t* pszKey, const int nCmpLen,
						CNativeW** ppcmemKey, CNativeW** ppcmemMean,
						const TCHAR* pszKeyWordHelpFile, int * pLine );	// 2006.04.10 fon (const int,CMemory**,int*)引数を追加
	static int HokanSearch( const wchar_t* pszKey, bool bHokanLoHiCase,
							vector_ex<std::wstring>& vKouho, int nMaxKouho,
							const TCHAR* pszKeyWordFile );
//	BOOL Close( char* );


protected:
	/*
	||  実装ヘルパ関数
	*/
};



///////////////////////////////////////////////////////////////////////
#endif /* _CDICMGR_H_ */



