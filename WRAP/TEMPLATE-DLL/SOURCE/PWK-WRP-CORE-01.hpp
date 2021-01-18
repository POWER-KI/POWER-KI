#pragma once
/* ======================  ===================================================
		 XPLAB           Xplab s.a.s. - viale Sant Eufemia, 39
   Research in Automation                 25135 Brescia - Italy
	 www.xplab.net                       Tel +39 030 2350035
    *** RESERVED ***				  (C) 2020 XPLAB CAP
   ======================  ===================================================
   File name            :  PWK-WRP-CORE.hpp
   Version              :  01
   Date                 :  28/02/20
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
    Core implementation for user Wrap DLL
  ---------------------------------------------------------------------------

   REVISION HISTORY:
  ----------------------  ---------------------------------------------------
   01                     First version
   02				 24/06/2020
   03				 25/11/2020	
  ----------------------  ---------------------------------------------------

  USE :
  ---------------------------------------------------------------------------
  Include this file in your  "Wrap" 

	---------
	WRAP NAME for use as LikeNative should be in the form:
	---------

			Prefix-WRP-Name ....dll

			Prefix is  tree char: OS+Hw+bit

				WX2		windows x86 32 bit
				WX4		windows x86 64 bit
				WA2		windows ARM 32 bit

			e.g.
			dll  file		WX2-WRP-TPL-01.dll
			help file		PWK-WRP-TPL-01.odt

   -----------------------------------------------------------------------

  the wrap function shoud be like:
	
	WRP_FUNC(SUM,Perform a sum)	
		{
		WRP_DCLBEG;

		WRP_DCLPAR(int, a);			// declare an input par
		WRP_DCLPAR_DEF(int, b, 20);	// with default parameter

		WRP_DCLRES(int, c);		//declare the return value if any

		WRP_DCLEND;					

		//-----------------------------	
		//now your code !! never before
		//-----------------------------

		c=a+b;

		WRP_RET_OK;				// 1=ok  0 or less Error (in POWER-KI -> NULL)
								// use WRP_RET_ERR; for error
		}
	
  Remember to list your function :

	WRP_INIT(Sum, otherfunction);
	
-----------------------------------------------
  Parameter Type:	I8, U8, I16, U16, I32 int, U32 unsigned, I64, U64, 
				F32 float, F64 double, U_STRG U_CHR*, ANY, PTR(POWER-KI PTR)

   KeyWORD:		WRP_DCLBEG;	  				//Section Begin
	
				WRP_DCLPAR(typ, parName, Comment);	
				WRP_DCLPAR_DEF(typ, parName, defValue, Comment);

				WRP_DCLRES(typ, resName, Comment);				//Return Value (Only The Fst is returned)

				WRP_DCLRES_AS( resName, stringAs, Comment);		//the type is ANY (void*)
				
				WRP_DCLEND;				//Section End

				--------------------------------

				During the execution you can change the as parameter with

				WRP_SETRES_AS_PAY(nam, as, pay, ...) // change the PAY (NV) like buffer size 
				WRP_SETRES_AS_TYP(nam, as, TYP, ...) // change the TYP (string) is added to as whith : before

				WRP_GETAS(nam);			// retrive AS so you can compare or also change

				WRP_TRIGSYNC;				// Trigger call
				WRP_TRIGPARL;
				WRP_TRIGSYNC_With( par/resName enum);
				WRP_TRIGPARL_With( par/resName enum);

				WRP_TRIG_LCKS;				// Lock Set the Trig semaphore 
				WRP_TRIG_LCKR;				// Lock Reset the Trig semaphore 

				WRP_INIT(FuncName );		//comma separated list of function

				WRP_RET_OK;				// 1=ok  
				WRP_RET_ERR;				// 0 or less Error (in POWER-KI -> NULL)


				To manage PWK PTR:
				WRP_PTR(PTR,WHT)			// return WHT: PTR, LIB(U_CHR*), TAG(U_CHR*), TYP(U_CHR*), PAY(ANY)
				WRP_PTR_LCKS(ptr)			// LOCK Set of semaphore
				WRP_PTR_LCKR(ptr)			// LOCK ReSet of semaphore

				WRP_PTR_NEW(ptr,AS)			// Create a PWK_PTR for PTR if passed to POWER-KI shoud be as ANY
				WRP_PTR_DEL(ptr)			// DELETE a PWK_PTR

				WRP_PWK_EXEC(clc)			// Execute a PWK code calc(U_CHR*) return a PTR_TO(U_CHR)

-----------------------------------------------

  To declare a PWK PTR res type use:

	WRP_DCLRES_AS(nam,as);			// the type is PTR

  Where "as": 

		IS:		LIB:TAG:TYP:PAY

	 For BUF:		LIB -> BUF 
		and:		TAG -> BUF, CHK		
		and:		TYP -> see above
		and:		PAY -> size in byte
				
	 For MAT:		LIB -> OCV 
		and:		TAG -> MAT		
	 (OpenCv)

  You can declare AS in an implicit way whith only the TYP
	in this case WRP:EXT are added by PWK

  If LIB=WRP and you are using the LIB in a like Native way WRP is replaced by the LIB name	  


  During the execution you can change the AS parameter with

	WRP_SETRES_AS (nam, as) // change the whole as
	WRP_SETRES_AS_PAY(nam, as, pay, ...) // change the PAY
	WRP_SETRES_AS_TYP(nam, as, TYP, ...) // change the TYP

	Note typ -> (user typ to return in your WRP_DEL(ptr,typ) function )	

  To get the AS of any parameter/result use 	

	WRP_GETAS(nam);    //and you will get the U_STRG or NULL

  	
-----------------------------------------------
  TRIGGER: a way to call PWK EXO or METHOD from inside your function

	Immediate execution	
	   Sync:		WRP_TRIGSYNC;
				WRP_TRIGSYNC_with(par1,..); //parameter WRP_DCLared and also in TRIG

	Execution in a new Thread (parallel)   	
	   ASyn:		WRP_TRIGPARL;
				WRP_TRIGPARL_with(par1,..);

	Syncronization of TRIG access
				WRP_TRIG_LCKS;				// Lock Set the Trig semaphore
				WRP_TRIG_LCKR;				// Lock ReSet the Trig semaphore 
	
*/
#include <windows.h>

#include "PWK-WRP-LINK.hpp"

#ifndef WRP_EXPORTS
	#define WRP_EXPORTS __declspec(dllexport)
#endif

#define _CRT_SECURE_DEPRECATE_MEMORY
// _CRT_SECURE_NO_WARNINGS


// ============================================================================

typedef WRP_EXPORTS int(* WRPPWK_EXC)(ANY _parBuf_, int _parNum_, PTR_TO(U8)bpp, PTR_TO(U_CHR*)_asBuf_);
typedef NONE(CALLBACK* WRPPWK_TCB)(ANY, PTR_TO(U_CHR), int mode);// Trig call back 0=Sync 1=asinc 2=Lock SEt 3=Lock RESET
typedef ANY(CALLBACK* WRPPWK_CBS)(int sel, PTR_TO(U_CHR), ANY, ANY);// Call back  for PWK services

#define PAR2FNC(n)	(n*-1-1)

#pragma pack(push,1)
DEFINE(struct,WRP_PAR)
WRP_PAR
	{
	DATA(PTR_TO(U_CHR),			par,			Par name);
	DATA(int,					off,			offset);
	DATA(int,					siz,			size in byte);
	DATA(PTR_TO(U_CHR),			typ,			Type: U8 I8 I16 U16 I32 U32 I64 U64 F32 F64 PTR  );	
	};

DEFINE(struct, WRP_FNC)
WRP_FNC
	{
	DATA(PTR_TO(U_CHR),			fnc,			function name);
	DATA(WRPPWK_EXC,			ptr,			Function Pointer);	
	DATA(int,					np,			Number of parameter);
	DATA(PTR_TO(WRP_PAR),		par,			Ptr to input par);	
	DATA(int,					psz,			Size in byte of par buffer);	
	DATA(int,					nr,			Number of res 0=no res);	
	DATA(PTR_TO(WRP_PAR),		res,			Ptr to return par - only one);
	DATA(int,					rsz,			Size in byte of res buffer);	
	};

DEFINE(struct, WRP_TBL)
WRP_TBL
	{
	DATA(int,					nf,			Number of function);
	DATA(PTR_TO(WRP_FNC),		pf,			Ptr to function);	
	};

#pragma pack(pop)

/*---------------------------------------------
#define __STR2WSTR(str) L##str
#define _STR2WSTR(str) __STR2WSTR(str)
#define __FUNCTIONW__ _STR2WSTR(__FUNCTION__)
//---------------------------------------------
*/

typedef WRP_EXPORTS PTR_TO(WRP_TBL)(CALLBACK* WRPPWK_GETTBL)(WRPPWK_TCB, WRPPWK_CBS);
typedef WRP_EXPORTS NONE(CALLBACK* WRPPWK_PTRDEL)(ANY,ANY);

extern PTR_TO(WRP_TBL) wrpTbl;			// Main data table
extern WRPPWK_TCB	PWK_TRIGGER;		// POWER-KI Trigger CallBack
extern WRPPWK_CBS	PWK_CBS;			// POWER-KI Services CallBack	

// =======================================================================

DEFINE(struct, Function poiter container)
lisParElm: public DNODO
	{
	WRP_PAR p;
	};

extern LIST_OBJ_MNG<lisParElm> lisPar;
extern LIST_OBJ_MNG<lisParElm> lisRes;

// =======================================================================
// PWK_GLUE
// =======================================================================

FUNCTION(NONE, Register Parameter)
PWK_WRP_PAR_REG(PTR_TO(U_CHR)id, PTR_TO(U_CHR)typ, int szt);

FUNCTION(NONE, Register Return res)
PWK_WRP_RES_REG(PTR_TO(U_CHR)id, PTR_TO(U_CHR)typ, int szt);

FUNCTION(NONE, Set Func Par)
PWK_WRP_PAR_SET(int idx);

FUNCTION(PTR_TO(WRP_TBL), Add function to init)
PWK_WRP_Init(WRPPWK_EXC fnc, ...);

//------------------------------------------------------
ANY WRP_GETRET(PTR_TO(U_CHR)id, ANY buf, int szt, PTR_TO(U_CHR) typ, const PTR_TO(U_CHR) fun, const PTR_TO(U_CHR)as, int init, PTR_TO(U_CHR*)asBuf);

//------------------------------------------------------
PTR_TO(U_CHR) WRP_GETPAR_AS(PTR_TO(U_CHR)id,const PTR_TO(U_CHR) fun, PTR_TO(U_CHR*));

int WRP_GETPAR_IDX(PTR_TO(U_CHR)id,const PTR_TO(U_CHR) fun);

ANY WRP_GETPAR(PTR_TO(U_CHR)id, ANY buf, int szt, const PTR_TO(U_CHR) fun);

ANY WRP_SET_DCLPAR(int pn, PTR_TO(U_CHR)nam, PTR_TO(U_CHR)typ, int tySz, ANY parBuf, PTR_TO(U_CHR)FUNCTIONW);

// -----------------------------------------------------------------------
FUNCTION(PTR_TO(U_CHR), Build an AS return signature e.g. for BUF size)
WRP_RES_PAY(const PTR_TO(U_CHR)fxp,unsigned pay);

// -----------------------------------------------------------------------
FUNCTION(PTR_TO(U_CHR), Build an AS return signature e.g. for BUF size)
WRP_RES_TYP(const PTR_TO(U_CHR)fxp, PTR_TO(U_CHR) typ);

// -----------------------------------------------------------------------
FUNCTION(NONE, Send a text to POWER - KI chat)
WRP_TRACE(PTR_TO(U_CHR)t);

// =======================================================================


// -----------------------------------------------------------------------	
#define	WRP_DCLBEG \
if(_parNum_<0) wrpTbl->pf[PAR2FNC(_parNum_)].fnc=StrDup((U_CHR*)__FUNCTIONW__);	\
ANY& _wtp_= *(ANY*)&((U8*)_parBuf_)[0];

#define WRP_DCLEND	if(_parNum_<0) return 1;
//------------------------------------------------------

#define WRP_DCLPAR(typ,nam, ...) \
	typ &nam =*(typ*) WRP_SET_DCLPAR(_parNum_,(U_CHR*)L#nam,(U_CHR*)L#typ,sizeof(typ),_parBuf_, (U_CHR*) __FUNCTIONW__);

#define WRP_DCLPAR_DEF(typ,nam,def, ...) \
	typ &nam =*(typ*) WRP_SET_DCLPAR(_parNum_,(U_CHR*)L#nam,(U_CHR*)L#typ,sizeof(typ),_parBuf_, (U_CHR*) __FUNCTIONW__);\
	if(_parNum_>0 && _bpp_)\
		{\
		int idx=WRP_GETPAR_IDX((U_CHR*)L#nam,(U_CHR*) __FUNCTIONW__);\
		if(idx>=0)\
			{\
			if(_bpp_[idx]==0)\
				{\
				nam=def; \
				} \
			} \
		}
//------------------------------------------------------
#define WRP_DCLRES(typ,nam, ...) \
	typ &nam= *(typ*) WRP_GETRET((U_CHR*)L#nam, _parBuf_, sizeof(typ),(U_CHR*) L#typ,(U_CHR*) __FUNCTIONW__,NULL, _parNum_< 0, NULL);

#define WRP_DCLRES_AS(nam,as, ...) \
	ANY &nam= *(ANY*) WRP_GETRET((U_CHR*)L#nam, _parBuf_, sizeof(ANY), (U_CHR*)L"PTR",(U_CHR*) __FUNCTIONW__, (U_CHR*) as, _parNum_< 0, _asBuf_);

#define WRP_SETRES_AS(nam, as, ...) \
	if(_parNum_>= 0)\
		{\
		WRP_GETRET((U_CHR*)L#nam, _parBuf_, sizeof(ANY), (U_CHR*)L"PTR",(U_CHR*) __FUNCTIONW__, (U_CHR*) as, _parNum_< 0, _asBuf_);\
		}

#define WRP_SETRES_AS_PAY(nam, as, pay, ...) \
	if(_parNum_>= 0)\
		{\
		PTR_TO(U_CHR)pas = (U_CHR*)as; \
		pas = WRP_RES_PAY(as, pay);\
		WRP_GETRET((U_CHR*)L#nam, _parBuf_, sizeof(ANY), (U_CHR*)L"PTR",(U_CHR*) __FUNCTIONW__, (U_CHR*) pas, _parNum_< 0, _asBuf_);\
		if(pas) delete pas;\
		}

#define WRP_SETRES_AS_TYP(nam, as, typ, ...) \
	PTR_TO(U_CHR)pas= (U_CHR*)as;\
	if(_parNum_>= 0)\
		{\
		PTR_TO(U_CHR)pas= (U_CHR*)as;\
		pas = WRP_RES_TYP(as, typ);\
		WRP_GETRET((U_CHR*)L#nam, _parBuf_, sizeof(ANY), (U_CHR*)L"PTR",(U_CHR*) __FUNCTIONW__, (U_CHR*) pas, _parNum_< 0, _asBuf_);\
		if(pas)delete pas;\
		}

#define WRP_GETAS(nam)\
	WRP_GETPAR_AS((U_CHR*)L#nam, (U_CHR*)__FUNCTIONW__, _asBuf_);

// -----------------------------------------------------------------------
extern "C" NONE WRP_CALL_PWK_TRIG(ANY parTrg, PTR_TO(U_CHR)parLis, int mode);

#define WRP_TRIGSYNC \
	if(_wtp_)\
		{\
		WRP_CALL_PWK_TRIG(_wtp_, NULL,0 );\
		}

#define WRP_TRIGPARL\
	if(_wtp_)\
		{\
		WRP_CALL_PWK_TRIG(_wtp_, NULL,1 );\
		}

#define WRP_TRIGSYNC_With(...) \
	if(_wtp_)\
		{\
		WRP_CALL_PWK_TRIG(_wtp_,(U_CHR*) L#__VA_ARGS__,0 );\
		}

#define WRP_TRIGPARL_With(...)\
	if(_wtp_)\
		{\
		WRP_CALL_PWK_TRIG(_wtp_, (U_CHR*) L#__VA_ARGS__,1 );\
		}

// Set / Reset TRIG Smf
#define WRP_TRIG_LCKS\
	if(_wtp_)\
		{\
		WRP_CALL_PWK_TRIG(_wtp_, NULL,2);\
		}

#define WRP_TRIG_LCKR\
	if(_wtp_)\
		{\
		WRP_CALL_PWK_TRIG(_wtp_, NULL,3);\
		}

// =======================================================================
// POWER-KI Service Interface
// -----------------------------------------------------------------------

// -----------------------------------------------------------------------
// Create a new PWK PTR return PTR or NULL
// -----------------------------------------------------------------------
#define WRP_PTR_NEW(PTR,AS)\
	(PWK_CBS)(3,(U_CHR*) AS, PTR, NULL) 

// -----------------------------------------------------------------------
// DELETE a PWK 
// -----------------------------------------------------------------------
#define WRP_PTR_DEL(PTR)\
	(PWK_CBS)(4,NULL, PTR, NULL) 

// -----------------------------------------------------------------------
// Get info from a PWK PTR - WHT : PTR, LIB, TAG, TYP, PAY
// -----------------------------------------------------------------------
#define WRP_PTR(PTR,WHT)\
	(PWK_CBS)(1,(U_CHR*) L#WHT, PTR, NULL) 

// -----------------------------------------------------------------------
// Set info from a PWK PTR - WHT : PTR, LIB, TAG, TYP, PAY
// -----------------------------------------------------------------------
#define WRP_PTR_SET(PTR,WHT,P1)\
	(PWK_CBS)(6,(U_CHR*) L#WHT, PTR, P1) 


// -----------------------------------------------------------------------
// PWK PTR  SMF 
// -----------------------------------------------------------------------
#define WRP_PTR_LCKS(PTR)\
	(PWK_CBS)(2, (U_CHR*)L"LCKS", PTR, NULL);

#define WRP_PTR_LCKR(PTR)\
	(PWK_CBS)(2, (U_CHR*)L"LCKR", PTR, NULL); 

#define WRP_PTR_TRY(PTR)\
	(int)(PWK_CBS)(2, (U_CHR*)L"TRY", PTR, NULL)

// -----------------------------------------------------------------------
// EXECute a PWK calc and return the result
// -----------------------------------------------------------------------
#define WRP_PWK_EXEC(CLC)\
	(PWK_CBS)(5,(U_CHR*) CLC, NULL, NULL) 
// Return PTR_TO(U_CHR)

// =======================================================================

// =======================================================================

#define WRP_DEL(PTR,TYP, ...)\
FUNCTION(extern "C" WRP_EXPORTS NONE, Delete User created pointer) \
PWK_PTRDEL(ANY PTR, PTR_TO(U_CHR) TYP, ANY PAY)

// -----------------------------------------------------------------------
#define WRP_FUNC(nam,...) extern "C" \
	int nam (ANY _parBuf_, int _parNum_, PTR_TO(U8) _bpp_, PTR_TO(U_CHR*) _asBuf_ )

// -----------------------------------------------------------------------

#define WRP_INIT(...) \
extern "C" \
WRP_EXPORTS PTR_TO(WRP_TBL) PWK_GETTBL(WRPPWK_TCB trig, WRPPWK_CBS cbs) \
	{ \
	if(trig)PWK_TRIGGER=trig;\
	if(cbs) PWK_CBS=cbs;\
	if(!wrpTbl)\
		{\
		return PWK_WRP_Init(__VA_ARGS__,NULL,NULL);\
		}\
	return wrpTbl;\
	}

// -----------------------------------------------------------------------
#define WRP_RET_OK		return 1
#define WRP_RET_ERR		return 0



// =======================================================================
// PWK WRP - END
// =======================================================================





