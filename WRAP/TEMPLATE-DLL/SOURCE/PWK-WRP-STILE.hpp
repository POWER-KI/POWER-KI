// ======================  ===================================================
//         XPLAB           Xplab s.a.s. - viale Sant Eufemia, 39
// Research in Automation                 25135 Brescia - Italy
//     www.xplab.net                      Tel/Fax +39 030 2350035/2350035
//   *** RESERVED ***
// ======================  ===================================================
// File name            :  XU-STILE.H
// Version              :  1.0.0
// Date                 :  08/04/08
// Author               :  CAP
// ----------------------  ---------------------------------------------------
// Project              :  XPOLYPLUS - Universal
// Workpakage           :  
// Task                 :  
// ======================  ===================================================

// ABSTRACT:
// ---------------------------------------------------------------------------
// Data types and definition common to all the applications
// ---------------------------------------------------------------------------

// REVISION HISTORY:
// ----------------------  ---------------------------------------------------
// 1.0.0                   First version
// ----------------------  ---------------------------------------------------

// ****************************************************************************

// BUG:
// ---------  ----------------------------------------------------------------
// DATE       FILE         FUNCTION                                     AUTHOR
// ---------  -----------  -------------------------------------------  ------
// XX/XX/XX
//
// PROBLEM :
//
// CAUSE   :
//
// SOLUTION:
// ----------------------------------------------------------------------------

// ****************************************************************************

#pragma once

// ============================================================================
// STANDARD INCLUDE
// ============================================================================

// ============================================================================
// APPLICATION INCLUDE
// ============================================================================

// ============================================================================
// MACRO DEFINITION
// ============================================================================

// ********************************************************************* *******
// *********************************  C O D E  ********************************
// ****************************************************************************


// ============================================================================
// DATA TYPE
// ============================================================================

#define VLONG	long long		
//#define VLONG __int64	

//===========================================================================
// MACRO for ERROR
//===========================================================================

#define DECL_ERR(code,string) (((int)&(L#code L":" L string))*-1)  

typedef int				RSLT;		//Result
#define RSLT_ERR(x)			(x*-1)
#define IS_RSLT_ERR(x)		(x<=0)

//===========================================================================

#ifdef _WIN64
     typedef unsigned long long    PTRU;     //64 bit 
#else
     typedef unsigned long         PTRU;     //32 bit 
     typedef unsigned char         BYTE;	// 8 bit
     typedef unsigned short        WORD;	//16 bit
	typedef unsigned long         DWORD;	//32 bit
#endif
	
typedef unsigned VLONG		QWORD;		//64 bit

typedef unsigned char         U8;
typedef unsigned short        U16;
typedef unsigned long         U32;
typedef unsigned VLONG 		U64;

typedef char                  I8;
typedef short                 I16;
typedef int                   I32;
typedef  VLONG				I64;

typedef float                 FLT32;
typedef double                FLT64;

typedef float                 F32;
typedef double                F64;

typedef U32                   UNS;
typedef int                   BOOL;
typedef I32                   INT;
typedef FLT32                 FLT;
typedef double                DBL;


// ============================================================================
// USEFUL DEFINE
// ============================================================================

#define DEFINE(type, descr) type
#define NOTE(descr)
#define TODO(descr)
#define DESCR(descr)


#define WITH                  __with
#define ANY                   void *
#define NONE                  void
//#define PTR                   *
#define PTR_TO(type)          type *
#define AS_PTR_TO(type)       (type *)
#define AS(type)              (type)

#define VAL_OF(ptr)           *ptr
#define ADR_OF(var)           &var
#define REF_BY(ptr)           *ptr

#ifndef NULL
	#define NULL              0
#endif
#define YES                   1
#define NOT                   0
#define TRUE                  1
#define FALSE                 0

//For parameter
#define IN
#define OUT
#define OPTIONAL

//For Data Bloc definition
#define STRING(len,name,descr)          I8  name[len]
#define BUFFER(len,name,descr)          U8  name[len]
#define VECTOR( typ, len, name, descr)  typ name[len]

#define DATA(typ, name, descr)		typ name
#define EXTRN(typ, name, descr)		extern typ name;
#define DATAV(typ, name, descr)		typ volatile name

// ============================================================================
// MACRO for FUNCTION
// ============================================================================

#define FUNCTION(type, descr) type
#define INLINE(type, descr) inline type

#define TFUNCTION(descr) template

//USE:	TFUNCTION(Remove head and trailing spaces)<class T>
//		PTR_TO(T) Nospaces( PTR_TO(T) parola ){...}

// ============================================================================
// MACRO for TEMPLATE
// ============================================================================

//A class with the type embedded like RTT
#define OBJ_CLASS( name, descr) \
static U32 OBJECT<class name>::typ=0;\
class name:public OBJECT<class name>

//Template Class
#define TCLASS(name, descr)\
template<class T>\
class name

#define TBUILDER(class)   class
#define TMETHOD( class, ret, descr) ret
#define TDESTROYER(class) ~class()
#define TOPERATOR(class, op, ret, descr) ret operator op

// ============================================================================
// MACRO for CLASS
// ============================================================================
#define CLASS( name, descr) \
class name 

#define BUILDER(class)   class::class
#define DESTROYER(class) class::~class()
#define METHOD(class, ret, descr) ret class::
#define OPERATOR(class, op,ret, descr) ret class::operator op

#define D_BUILDER(class)   class
#define D_DESTROYER(class) ~class()
#define D_METHOD(class, ret, descr) ret 
#define D_OPERATOR(class, op,ret, descr) ret operator op



//===========================================================================
// MODUL
//===========================================================================

#define DECLARE_MODUL(name, parIn, parOut)\
struct __PARIN_##name parIn;\
struct __PAROUT_##name parOut;\
void name( __PARIN_##name& __pi, __PAROUT_##name& __po);

#define BEG_MODUL(name, descr)\
void name( __PARIN_##name& __pi, __PAROUT_##name& __po){WITH( __pi) WITH (__po)

#define END_MODUL ;}

#define CALL_MODUL(name, pi, po)\
{ \
__PARIN_##name __pi; \
__PAROUT_##name __po; \
WITH(__pi) \
pi;\
name( __pi,__po);\
WITH(__po) \
po;\
};


#ifdef DEBUG
     #define PRECOND(cnd) cnd
     #define POSTCOND(cnd) cnd
     #define BODY
#else
     #define PRECOND(cnd)
     #define POSTCOND(cnd)
     #define BODY
#endif


/* EXAMPLE
   =======
DECLARE_MODUL(Modulo, {U32 a;U32 b;}, {U32 c; U32 d;});

BEG_MODUL(Modulo)
     {
     c=a;
     d=b;
     }
END_MODUL

CALL_MODUL(Modulo,{a=1;b=2;},{e=c;f=d;});
*/

