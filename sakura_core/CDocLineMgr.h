/*!	@file
	@brief �s�f�[�^�̊Ǘ�

	@author Norio Nakatani
	@date 1998/3/5  �V�K�쐬
	@date 2001/06/23 N.Nakatani WhereCurrentWord_2()�ǉ� static�����o
	@date 2001/12/03 hor ������(bookmark)�@�\�ǉ��ɔ����֐��ǉ�
*/
/*
	Copyright (C) 1998-2001, Norio Nakatani
	Copyright (C) 2000, genta
	Copyright (C) 2001, hor, genta
	Copyright (C) 2002, aroka, MIK, hor
	Copyright (C) 2003, Moca, ryoji

	This source code is designed for sakura editor.
	Please contact the copyright holder to use this code for other purpose.
*/

class CDocLineMgr;

#ifndef _CDOCLINEMGR_H_
#define _CDOCLINEMGR_H_

#include <windows.h>
#include "global.h" // 2002/2/10 aroka
#include "CEol.h" // 2002/2/10 aroka
class CDocLine; // 2002/2/10 aroka
class CMemory; // 2002/2/10 aroka
class CBregexp; // 2002/2/10 aroka

struct DocLineReplaceArg {
	int			nDelLineFrom;		/* �폜�͈͍s  From ���s�P�ʂ̍s�ԍ� 0�J�n) */
	int			nDelPosFrom;		/* �폜�͈͈ʒuFrom ���s�P�ʂ̍s������̃o�C�g�ʒu 0�J�n) */
	int			nDelLineTo;			/* �폜�͈͍s  To   ���s�P�ʂ̍s�ԍ� 0�J�n) */
	int			nDelPosTo;			/* �폜�͈͈ʒuTo   ���s�P�ʂ̍s������̃o�C�g�ʒu 0�J�n) */
	CMemory*	pcmemDeleted;		/* �폜���ꂽ�f�[�^��ۑ� */
	int			nDeletedLineNum;	/* �폜�����s�̑��� */
	const char*	pInsData;			/* �}������f�[�^ */
	int			nInsDataLen;		/* �}������f�[�^�̒��� */
	int			nInsLineNum;		/* �}���ɂ���đ������s�̐� */
	int			nNewLine;			/* �}�����ꂽ�����̎��̈ʒu�̍s */
	int			nNewPos;			/* �}�����ꂽ�����̎��̈ʒu�̃f�[�^�ʒu */
};

/*-----------------------------------------------------------------------
�N���X�̐錾
-----------------------------------------------------------------------*/
class SAKURA_CORE_API CDocLineMgr
{
public:
	/*
	||  Constructors
	*/
	CDocLineMgr();
	~CDocLineMgr();

	/*
	||  �Q�ƌn
	*/
	char* GetAllData( int* );	/* �S�s�f�[�^��Ԃ� */
	int GetLineCount( void ) { return m_nLines; }	/* �S�s����Ԃ� */
	const char* GetLineStr( int , int* );
	const char* GetLineStrWithoutEOL( int , int* ); // 2003.06.22 Moca
	const char* GetFirstLinrStr( int* );	/* ���A�N�Z�X���[�h�F�擪�s�𓾂� */
	const char* GetNextLinrStr( int* );	/* ���A�N�Z�X���[�h�F���̍s�𓾂� */

	int WhereCurrentWord( int , int , int* , int*, CMemory*, CMemory* );	/* ���݈ʒu�̒P��͈̔͂𒲂ׂ� */
	// 2001/06/23 N.Nakatani WhereCurrentWord_2()�ǉ� static�����o
	static int WhereCurrentWord_2( const char*, int, int , int* , int*, CMemory*, CMemory* );	/* ���݈ʒu�̒P��͈̔͂𒲂ׂ� */

	static int WhatKindOfChar( const char*, int, int );	/* ���݈ʒu�̕����̎�ނ𒲂ׂ� */
	int PrevOrNextWord( int , int , int* , BOOL bLEFT, BOOL bStopsBothEnds );	/* ���݈ʒu�̍��E�̒P��̐擪�ʒu�𒲂ׂ� */
	//	pLine�i�����FnLineLen�j�̕����񂩂玟�̒P���T���B�T���n�߂�ʒu��nIdx�Ŏw��B
	static int SearchNextWordPosition(
		const char* pLine,
		int			nLineLen,
		int			nIdx,		//	����
		int*		pnColmNew,	//	���������ʒu
		BOOL		bStopsBothEnds	//	�P��̗��[�Ŏ~�܂�
	);
	//	Jun. 26, 2001 genta	���K�\�����C�u�����̍����ւ�
	int SearchWord( int , int , const char* , int , int , int , int , int* , int* , int*, CBregexp* ); /* �P�ꌟ�� */
//	static char* SearchString( const unsigned char*, int, int , const unsigned char* , int, int*, int*, int ); /* �����񌟍� */
	static char* SearchString( const unsigned char*, int, int , const unsigned char* , int, int*, int ); /* �����񌟍� */
	static void CreateCharCharsArr( const unsigned char*, int, int** );	/* ���������̏�� */
//	static void CreateCharUsedArr( const unsigned char*, int, const int*, int** ); /* ���������̏��(�L�[������̎g�p�����\)�쐬 */



	void DUMP( void );
//	void ResetAllModifyFlag( BOOL );	/* �s�ύX��Ԃ����ׂă��Z�b�g */
	void ResetAllModifyFlag( void );	/* �s�ύX��Ԃ����ׂă��Z�b�g */


// From Here 2001.12.03 hor
	void ResetAllBookMark( void );			/* �u�b�N�}�[�N�̑S���� */
	int SearchBookMark( int , int , int* ); /* �u�b�N�}�[�N���� */
// To Here 2001.12.03 hor

	//@@@ 2002.05.25 MIK
	void ResetAllDiffMark( void );			/* �����\���̑S���� */
	int SearchDiffMark( int , int , int* ); /* �������� */
	void SetDiffMarkRange( int nMode, int nStartLine, int nEndLine );	/* �����͈͂̓o�^ */
	bool IsDiffUse( void ) const { return m_bIsDiffUse; }	/* DIFF�g�p�� */

// From Here 2002.01.16 hor
	void MarkSearchWord( const char* , int , int , int , CBregexp* ); /* ���������ɊY������s�Ƀu�b�N�}�[�N���Z�b�g���� */
	void SetBookMarks( char* ); /* �����s�ԍ��̃��X�g����܂Ƃ߂čs�}�[�N */
	char* GetBookMarks( void ); /* �s�}�[�N����Ă镨���s�ԍ��̃��X�g����� */
// To Here 2001.01.16 hor

	/*
	|| �X�V�n
	*/
	void Init();
	void Empty();
//	void InsertLineStr( int );	/* �w��s�̑O�ɒǉ����� */

#if 0
	void AddLineStrSz( const char* );	/* �����ɍs��ǉ� Ver0 */
	void AddLineStr( const char*, int );	/* �����ɍs��ǉ� Ver1 */
	void AddLineStr( CMemory& );	/* �����ɍs��ǉ� Ver2 */
#endif
	//	May 15, 2000 genta
	void AddLineStrX( const char*, int, CEOL );	/* �����ɍs��ǉ� Ver1.5 */

	void DeleteData_CDocLineMgr(
		int			nLine,
		int			nDelPos,
		int			nDelLen,
		int*		pnModLineOldFrom,	/* �e���̂������ύX�O�̍s(from) */
		int*		pnModLineOldTo,		/* �e���̂������ύX�O�̍s(to) */
		int*		pnDelLineOldFrom,	/* �폜���ꂽ�ύX�O�_���s(from) */
		int*		pnDelLineOldNum,	/* �폜���ꂽ�s�� */
		CMemory&	cmemDeleted			/* �폜���ꂽ�f�[�^ */
	);

	/* �w��͈͂̃f�[�^��u��(�폜 & �f�[�^��}��)
	  From���܂ވʒu����To�̒��O���܂ރf�[�^���폜����
	  From�̈ʒu�փe�L�X�g��}������
	*/
	void CDocLineMgr::ReplaceData(
		DocLineReplaceArg*
#if 0
		int			nDelLineFrom,		/* �폜�͈͍s  From ���s�P�ʂ̍s�ԍ� 0�J�n) */
		int			nDelPosFrom,		/* �폜�͈͈ʒuFrom ���s�P�ʂ̍s������̃o�C�g�ʒu 0�J�n) */
		int			nDelLineTo,			/* �폜�͈͍s  To   ���s�P�ʂ̍s�ԍ� 0�J�n) */
		int			nDelPosTo,			/* �폜�͈͈ʒuTo   ���s�P�ʂ̍s������̃o�C�g�ʒu 0�J�n) */
		CMemory*	pcmemDeleted,		/* �폜���ꂽ�f�[�^��ۑ� */
		int*		pnDeletedLineNum,	/* �폜�����s�̑��� */
		const char*	pInsData,			/* �}������f�[�^ */
		int			nInsDataLen,		/* �}������f�[�^�̒��� */
		int*		pnInsLineNum,		/* �}���ɂ���đ������s�̐� */
		int*		pnNewLine,			/* �}�����ꂽ�����̎��̈ʒu�̍s */
		int*		pnNewPos			/* �}�����ꂽ�����̎��̈ʒu�̃f�[�^�ʒu */
#endif
	);
	void DeleteNode( CDocLine* );/* �s�I�u�W�F�N�g�̍폜�A���X�g�ύX�A�s��-- */
	void InsertNode( CDocLine*, CDocLine* );	/* �s�I�u�W�F�N�g�̑}���A���X�g�ύX�A�s��++ */

	/* �f�[�^�̑}�� */
	void InsertData_CDocLineMgr(
		int			nLine,
		int			nInsPos,
		const char*	pInsData,
		int			nInsDataLen,
		int*		pnInsLineNum,	/* �}���ɂ���đ������s�̐� */
		int*		pnNewLine,		/* �}�����ꂽ�����̎��̈ʒu�̍s */
		int*		pnNewPos		/* �}�����ꂽ�����̎��̈ʒu�̃f�[�^�ʒu */
	);

	//	Nov. 12, 2000 genta �����ǉ�
	//	Jul. 26, 2003 ryoji BOM�����ǉ�
	int ReadFile( const char*, HWND, HWND, int, FILETIME*, int extraflag, BOOL* pbBomExist = NULL );
	//	Feb. 6, 2001 genta �����ǉ�(���s�R�[�h�ݒ�)
	//	Jul. 26, 2003 ryoji BOM�����ǉ�
	int WriteFile( const char*, HWND, HWND, int, FILETIME*, CEOL, BOOL bBomExist = FALSE );
	CDocLine* GetLineInfo( int );
	// 2002/2/10 aroka �����o�� private �ɂ��ăA�N�Z�T�ǉ�
	CDocLine* GetDocLineTop() const { return m_pDocLineTop; }
	CDocLine* GetDocLineBottom() const { return m_pDocLineBot; }

private:

	/*
	|| �����o�ϐ�
	*/
	CDocLine*	m_pDocLineTop;
	CDocLine*	m_pDocLineBot;
	CDocLine*	m_pDocLineCurrent;	/* ���A�N�Z�X���̌��݈ʒu */
	int			m_nLines;		/* �S�s�� */
	int			m_nPrevReferLine;
	CDocLine*	m_pCodePrevRefer;
	bool		m_bIsDiffUse;	/* DIFF�����\�����{�� */	//@@@ 2002.05.25 MIK
protected:

	/*
	|| �����w���p�n
	*/
protected:



};


///////////////////////////////////////////////////////////////////////
#endif /* _CDOCLINEMGR_H_ */


/*[EOF]*/