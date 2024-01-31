#pragma once
/* ======================  ===================================================
		 XPLAB           Xplab s.a.s. - viale Sant Eufemia, 39
   Research in Automation                 25135 Brescia - Italy
	 www.xplab.net                       Tel +39 030 2350035
    *** RESERVED ***				  (C) 2020 XPLAB CAP
   ======================  ===================================================
   File name            :  PWK-WRP-LINK.hpp
   Version              :  01
   Date                 :  18/11/20
   Author               :  CAP
   ----------------------  ---------------------------------------------------
   Project              :  POWER-KI
   Workpakage           :  WRAP
   Task                 :  GLUE
  ----------------------  ---------------------------------------------------
   License              :  APACHE 2
  ======================  ===================================================

   ABSTRACT:
   ---------------------------------------------------------------------------
   HELPER - String and Useful Function for POWER-Ki connection
  ---------------------------------------------------------------------------

   REVISION HISTORY:
  ----------------------  ---------------------------------------------------
   01                     First version
  ----------------------  ---------------------------------------------------
*/


#include "PWK-WRP-STILE.hpp"
#include "PWK-WRP-LISTE.hpp"
#include "PWK-WRP-MACRO.hpp"

#define _CRT_SECURE_DEPRECATE_MEMORY
// _CRT_SECURE_NO_WARNINGS

#include <wchar.h>


typedef char		A_CHR;
typedef wchar_t	U_CHR;
typedef U_CHR*		U_STRG;

#define	CHR	U_CHR

FUNCTION(PTR_TO(U_CHR), String Copy)
StrCpy( PTR_TO(U_CHR)d, PTR_TO(U_CHR)s);

FUNCTION(int, Ordinal compare)
StrCmp(PTR_TO(U_CHR)s1, PTR_TO(U_CHR)s2);

FUNCTION(int, Ordinal compare case insensitive)
StrCmp_I(PTR_TO(U_CHR)s1, PTR_TO(U_CHR)s2);

FUNCTION(int, Ordinal compare n chr case insensitive)
StrCmp_IN(PTR_TO(U_CHR)s1, PTR_TO(U_CHR)s2, int n);

FUNCTION(PTR_TO(U_CHR), Search s2 in s1)
StrStr(PTR_TO(U_CHR)s1, PTR_TO(U_CHR)s2);

FUNCTION(int, Return string len)
StrLen(PTR_TO(A_CHR)s);

FUNCTION(int, Return string len)
StrLen(PTR_TO(U_CHR)s);

FUNCTION(PTR_TO(U_CHR),Remove head and trailing spaces)
Nospaces(PTR_TO(U_CHR) s);


//DESCR(String conversion)
FUNCTION(PTR_TO(U_CHR), From A_CHR to U_CHR - in a new string )
StrAtoU(PTR_TO(A_CHR)s);

FUNCTION(PTR_TO(A_CHR), From U_CHR to A_CHR - in a new string)
StrUtoA(PTR_TO(U_CHR)s);

FUNCTION(PTR_TO(A_CHR), From U_CHR to U_CHR/UTF - in a new string)
StrUtoUTF(PTR_TO(U_CHR)s);

FUNCTION(PTR_TO(U_CHR), From U_CHR/UTF to U_CHR - in a new string)
StrUTFtoU(PTR_TO(A_CHR)s);

FUNCTION(PTR_TO(U_CHR), Duplicate String)
StrDup( const PTR_TO(U_CHR)s);

FUNCTION(PTR_TO(U_CHR), Search s2 in s1 case insensitive)
StrStr_I(PTR_TO(U_CHR)s1, PTR_TO(U_CHR)s2);

#define StrFormat swprintf

FUNCTION(int,return the idx+1 of val string in a comma separated list - ins=1 case insensitive)
StrSelect(PTR_TO(U_CHR)v, PTR_TO(U_CHR)str, int ins=1, U_CHR sep = U_CHR(','));

A_CHR * StrUpr(A_CHR* s);

U_CHR * StrUpr(U_CHR* s);

A_CHR * StrLwr(A_CHR*s);

U_CHR * StrLwr(U_CHR*s);

FUNCTION(int, Ordinal Compare case insensitive and ignore space at the begin and end)
StrCmp_IX(PTR_TO(A_CHR)s1, PTR_TO(A_CHR)s2);

FUNCTION(int, Ordinal Compare  equal case insensitive  and ignore space at the begin and end)
StrCmp_IX(PTR_TO(U_CHR)s1, PTR_TO(U_CHR)s2);

FUNCTION(int, Ordinal compare n chr)
StrCmp_N(PTR_TO(A_CHR)s1, PTR_TO(A_CHR)s2, int n);
	
FUNCTION(int, Ordinal compare n chr)
StrCmp_N(PTR_TO(U_CHR)s1, PTR_TO(U_CHR)s2, int n);

FUNCTION(PTR_TO(A_CHR), String Copy N chr)
StrCpy_N(PTR_TO(A_CHR)d, PTR_TO(A_CHR)s, int n);

FUNCTION(PTR_TO(U_CHR), String Copy N chr)
StrCpy_N(PTR_TO(U_CHR)d, PTR_TO(U_CHR)s, int n);

FUNCTION(PTR_TO(A_CHR), Search chr c in s)
StrChr(PTR_TO(A_CHR)s, A_CHR c);

FUNCTION(PTR_TO(U_CHR), Search chr c in s)
StrChr(PTR_TO(U_CHR)s, U_CHR c);


//---------------------------------------------------------------------------

#define XU_VAL_NULL ((CHR*)NULL)

CLASS(XU_VAL, Value element)
	{
	public:	
	DATA(PTR_TO(U_CHR),			s,			String rapresentation);

	D_DESTROYER(XU_VAL);

	D_BUILDER(XU_VAL)();
	
	D_BUILDER(XU_VAL)(const XU_VAL& e);
		
	D_BUILDER(XU_VAL)(PTR_TO(CHR) s );

	D_BUILDER(XU_VAL)(int v );

	D_BUILDER(XU_VAL)(unsigned v );

	D_BUILDER(XU_VAL)(FLT v );


	D_METHOD(XU_VAL,PTR_TO(U_CHR),Reset s)
	Reset( );

	D_METHOD(XU_VAL,NONE, Convert to HEX)
	ToHex();

	D_METHOD(XU_VAL,NONE, Convert to Binary)
	ToBin();

	D_METHOD(XU_VAL,PTR_TO(CHR), Conversion to string)
	ToStr();

	D_METHOD(XU_VAL,int,Test for true)
	IsTrue( );

	D_METHOD(XU_VAL,int, Check against NULL s pointer)
	IsNULL();

	D_METHOD(XU_VAL,int, True if float)
	IsFlt();

	D_METHOD(XU_VAL,PTR_TO(U_CHR), True if Hex Number)
	IsHex();

	D_METHOD(XU_VAL,PTR_TO(U_CHR), True if Binary Number)
	IsBin();

	D_METHOD(XU_VAL,int, True if Number)
	IsNum();
		
	D_METHOD(XU_VAL,NONE, delete string)
	DelS();

	D_METHOD(XU_VAL,NONE, Reset s )
	RstS();

	D_METHOD(XU_VAL,XU_VAL&, Transfer the value of e)
	Move(XU_VAL& e);

	D_METHOD(XU_VAL,XU_VAL&, Transfer the value of e)
	SetS(PTR_TO(U_CHR) s1);

	D_METHOD(XU_VAL,XU_VAL&, Assign a string pointer !! NON USARE)
	Assign(PTR_TO(U_CHR) s);

	D_METHOD(XU_VAL,int, Return the lenght)
	Len();

	D_METHOD(XU_VAL,int, Set the lenght)
	Len(int sz);
				
	D_METHOD(XU_VAL,int,Test for all spaces or NULL)
	IsSpaces( );

	D_METHOD(XU_VAL,NONE,Set value)
	Set(PTR_TO(U_CHR) s );

	//-----------
	D_METHOD(XU_VAL,PTR_TO(CHR), Search a CHR )
	Find(CHR c);

	D_METHOD(XU_VAL,PTR_TO(CHR), Search a String )
	Find(PTR_TO(CHR) s);

	D_METHOD(XU_VAL,PTR_TO(CHR), Search a CHR )
	FindRvs(CHR c);

	D_METHOD(XU_VAL,PTR_TO(CHR), Search a String )
	FindRvs(PTR_TO(CHR) s);

	//-----------
	D_METHOD(XU_VAL,PTR_TO(CHR), Get new XU_VAL up to th char )
	GetUpToChr(PTR_TO(CHR) c);

	D_METHOD(XU_VAL,PTR_TO(CHR), Get new XU_VAL from th char )
	GetFromChr(PTR_TO(CHR) c);

	D_METHOD(XU_VAL,PTR_TO(CHR), Get new XU_VAL up to th char )
	GetUpToChr(CHR c);

	D_METHOD(XU_VAL,PTR_TO(CHR), Get new XU_VAL from th char )
	GetFromChr(CHR c);

	D_METHOD(XU_VAL,PTR_TO(CHR), Get new XU_VAL up to th char )
	GetUpToChrRvs(PTR_TO(CHR) c);

	D_METHOD(XU_VAL,PTR_TO(CHR), Get new XU_VAL from th char )
	GetFromChrRvs(PTR_TO(CHR) c);

	D_METHOD(XU_VAL,PTR_TO(CHR), Get new XU_VAL up to th char )
	GetUpToChrRvs(CHR c);

	D_METHOD(XU_VAL,PTR_TO(CHR), Get new XU_VAL from th char )
	GetFromChrRvs(CHR c);
	
	//---------------

	D_METHOD(XU_VAL,PTR_TO(CHR), Search a CHR )
	Find_I(CHR c);

	D_METHOD(XU_VAL,PTR_TO(CHR), Search a String )
	Find_I(PTR_TO(CHR) s);

	D_METHOD(XU_VAL,PTR_TO(CHR), Search a CHR )
	FindRvs_I(CHR c);

	D_METHOD(XU_VAL,PTR_TO(CHR), Search a String )
	FindRvs_I(PTR_TO(CHR) s);

	//-----------

	D_METHOD(XU_VAL,PTR_TO(CHR), Get new XU_VAL up to th char )
	GetUpToChr_I(PTR_TO(CHR) c);

	D_METHOD(XU_VAL,PTR_TO(CHR), Get new XU_VAL from th char )
	GetFromChr_I(PTR_TO(CHR) c);

	D_METHOD(XU_VAL,PTR_TO(CHR), Get new XU_VAL up to th char )
	GetUpToChr_I(CHR c);

	D_METHOD(XU_VAL,PTR_TO(CHR), Get new XU_VAL from th char )
	GetFromChr_I(CHR c);

	D_METHOD(XU_VAL,PTR_TO(CHR), Get new XU_VAL up to th char )
	GetUpToChrRvs_I(PTR_TO(CHR) c);

	D_METHOD(XU_VAL,PTR_TO(CHR), Get new XU_VAL from th char )
	GetFromChrRvs_I(PTR_TO(CHR) c);

	D_METHOD(XU_VAL,PTR_TO(CHR), Get new XU_VAL up to th char )
	GetUpToChrRvs_I(CHR c);

	D_METHOD(XU_VAL,PTR_TO(CHR), Get new XU_VAL from th char )
	GetFromChrRvs_I(CHR c);

	//------------

	D_METHOD(XU_VAL,CHR, Get the First CHR)
	Fst();

	D_METHOD(XU_VAL,NONE, Set the First CHR)
	Fst(CHR c);

	D_METHOD(XU_VAL,CHR, Get the Last CHR)
	Lst();

	D_METHOD(XU_VAL,NONE, Set the Last CHR)
	Lst(CHR c);

	D_OPERATOR(XU_VAL,~,int,Check existence)();

	D_OPERATOR(XU_VAL,[],CHR&,Get Char)(int i);

	D_OPERATOR(XU_VAL,=,XU_VAL&,Assignement)(const XU_VAL& e);
		
	D_OPERATOR(XU_VAL,=,XU_VAL&,String Assignement)(PTR_TO(CHR) s);

	D_OPERATOR(XU_VAL,=,XU_VAL&,Int Assignement)(const int i);

	D_OPERATOR(XU_VAL,=,XU_VAL&,Int Assignement)(const unsigned i);

	D_OPERATOR(XU_VAL, =, XU_VAL&, Int Assignement)(const U64 i);

	D_OPERATOR(XU_VAL, =, XU_VAL&, Int Assignement)(const I64 i);

	D_OPERATOR(XU_VAL,=,XU_VAL&,FLT Assignement)(const FLT i);

	D_OPERATOR(XU_VAL,=,XU_VAL&,FLT64 Assignement)(const FLT64 i);

	//----------------------------------

	D_OPERATOR(XU_VAL,<<=,XU_VAL&,Right Insert)(XU_VAL& e);

	D_OPERATOR(XU_VAL,<<=,XU_VAL&,Right Insert)(PTR_TO(CHR) as);

	D_OPERATOR(XU_VAL,<<=,XU_VAL&,Right Insert)(CHR c);

	//----------------------------------

	D_OPERATOR(XU_VAL,>>=,XU_VAL&,Left Insert)(XU_VAL& e);

	//----------------------------------

	D_OPERATOR(XU_VAL,>>,XU_VAL&,Right shift)(const int i);

	D_OPERATOR(XU_VAL,<<,XU_VAL&,Right shift)(const int i);

	D_METHOD(XU_VAL,int,Exact Comparison for NNV)
	CMP( XU_VAL e);

	D_METHOD(XU_VAL,int,Exact Comparison for NNV)
	CMPI( XU_VAL e);

	D_OPERATOR(XU_VAL,==,int, Comparison)( XU_VAL& e);

	D_OPERATOR(XU_VAL,!=,int, Comparison)( XU_VAL& e);

	D_OPERATOR(XU_VAL,==,int, Comparison)( PTR_TO(CHR) e);

	D_OPERATOR(XU_VAL,!=,int, Comparison)( PTR_TO(CHR) e);

	operator PTR_TO(CHR)();
	
	operator int();
	
	operator unsigned();

	operator FLT();

	operator FLT64();

	operator U64();

	operator I64();

	D_METHOD(XU_VAL,int, return an int)
	StrValInt(PTR_TO(U_CHR)s);

	D_METHOD(XU_VAL,unsigned, return an unsigned)
	StrValUns(PTR_TO(U_CHR)s);

	D_METHOD(XU_VAL,FLT,Return s as Flt)
	StrValFlt(PTR_TO(U_CHR)s);

	D_METHOD(XU_VAL,FLT64,Return s as Flt64)
	StrValDbl(PTR_TO(U_CHR)s);
	};



CLASS(XU_VAL_TMP, Value element):public XU_VAL
	{
	public:

	D_BUILDER(XU_VAL_TMP)(PTR_TO(U_CHR)s)
		{
		this->s=s;
		}; 		
	
	D_METHOD(XU_VAL_TMP,NONE, delete string)
	DelS()
		{
		s=NULL;
		};
		
	D_DESTROYER(XU_VAL_TMP)
		{
		DelS();
		};
	
	};

#undef CHR
//---------------------------------------------------------------------------
DEFINE(struct, Buf Matrix)
BUF_MTX_DATA
	{	
	DATA(unsigned,				esz,			Element size);	
	DATA(unsigned,				ten,			Element number);
	DATA(unsigned,				msz,			matrix size in byte);
	DATA(unsigned,				mnd,			matrix number of dimension);
	DATA(PTR_TO(unsigned),		dim,			dimension size in element);	
	DATA(ANY,					pkp,			Buf pointer);
	DATA(ANY,					dat,			PTR to raw data);
	DATA(XU_VAL,				typ,			Type);
	};

//---------------------------------------------------------------------------

class WRP_SMF
{
	HANDLE mtx;
	bool flag;

public:
	WRP_SMF() {
		mtx = CreateMutex(NULL, FALSE, NULL);
		flag = false;
	};

	~WRP_SMF() {
		CloseHandle(mtx);
	};

	void Rosso() {
		WaitForSingleObject(mtx, INFINITE);
		flag = true;
	};

	void Verde() {
		flag = false;
		ReleaseMutex(mtx);
	}
};