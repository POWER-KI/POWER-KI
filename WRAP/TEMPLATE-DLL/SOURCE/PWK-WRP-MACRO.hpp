// ======================  ===================================================
//         XPLAB           Xplab s.a.s. - via Bargnani, 9
// Research in Automation                 25135 Brescia - Italy
//     www.xplab.net                      Tel/Fax +39 030 2350035/2350035
//   *** RESERVED ***
// ======================  ===================================================
// File name            :  XU-MACRO.H
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
// Useful macro and inline functione for standart type manipolation - X86
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
#include "PWK-WRP-STILE.hpp"

// ============================================================================
// APPLICATION INCLUDE
// ============================================================================


// ****************************************************************************
// *********************************  C O D E  ********************************
// ****************************************************************************

DESCR(Zero a structure)
#define ZEROSTRUCT(x)		memset(&x,0,sizeof(x))

DESCR(find minimum of a and b)
#define MIN(a,b)			(((a)<(b))?(a):(b))

DESCR(find maximum of a and b)
#define MAX(a,b)			(((a)>(b))?(a):(b))

// a nible 4 bit
#define LOWB(x)	          ( (U8)(x) & 0xF)
#define HIGB(x)               ( (((U8)x) >> 4) & 0xF)

// a byte 8 bit
#define LOWW(x)	          ( (U16)(x) & 0xFF)
#define HIGW(x)               ( (((U16)x) >> 8) & 0xFF)

// a word 16 bit
#define LOWD(x)               ( U32(U32(x)) & 0xFFFF)
#define HIGD(x)               ( U32(U32(x) >>16))

// a dword 32 bit
#define LOWQ(x)               ( U64(U64(x)) & 0xFFFFFFFF)
#define HIGQ(x)               ( U64(U64(x) >>32))

FUNCTION(__inline U32, Mask of one winth len=l)
ONEMASK(int l)
	{
	return 0xFFFFFFFF>>(32-l);
	}

// get the bit field starting from bit hbit lenght len bit
#define GET_BIT_FLD(var,hbit,len)\
	(( var & (ONEMASK(len)<<(hbit-len+1)))>>(hbit-len+1))

// Set the bit field starting from bit hbit lenght len bit to val
#define SET_BIT_FLD(var,hbit,len, val)\
	(( var & (ONEMASK(len)<<(hbit-len+1))) | ((val & ONEMASK(len))<<(hbit-len+1)))


//===========================================================================
// SWAP Function
//===========================================================================


//----------------------------------------------
#ifdef X32
//----------------------------------------------

#define asm __asm

INLINE( U8, Excange half byte part)
SWAP8( U8 x)
     {
     asm  {
          mov  al,x
          rol  al,4;
          mov  x, al
          }
     return x;
     }

INLINE( U16, Excange byte in a word)
SWAP16( U16 x)
     {
     asm  {
          mov  ax,x;
          xchg ah,al;
          mov  x,ax;
          }
     return x;
     }

INLINE( U32, Excange word of a double word)
SWAP32( U32 x)
     {
     asm  {
          mov eax,x;
          bswap eax;
          mov x,eax;
          }
     return x;
     }

INLINE( PTR_TO(U8), Buffer Swap: Excange half byte part)
SWAPBUF8( PTR_TO(U8) b,int ne )
     {
     PTR_TO(U8) tb=b;
	while(ne>0)
		{
		SWAP8(VAL_OF(tb));
		ne--;
		tb++;
		};

     return b;
     }

INLINE( PTR_TO(U16), Buffer Swap: Excange byte in a word)
SWAPBUF16( PTR_TO(U16) b,int ne )
     {
     PTR_TO(U16) tb=b;
	while(ne>0)
		{
		SWAP16(VAL_OF(tb));
		ne--;
		tb++;
		}
     return b;
     }

INLINE( PTR_TO(U32), Buffer Swap: Excange word of a double word)
SWAPBUF32( PTR_TO(U32) b,int ne )
     {
     PTR_TO(U32) tb=b;
	while(ne>0)
		{
		SWAP32(VAL_OF(tb));
		ne--;
		tb++;
		}
     return b;
     }

//===========================================================================
// IO Function
//===========================================================================

void inline outpdw (U16 port, U32 value)
     {
     asm  {
          mov  dx,port
          mov  eax, value
          out  dx,eax
          }
     }

U32 inline inpdw (U16 port)
     {
     U32 value;

     asm  {
          mov  dx,port
          in   eax, dx
          mov  value, eax
          }

     return value;
     }

//----------------------------------------------
#else // MAC,WIN
//----------------------------------------------

INLINE( U8, Excange half byte part)
SWAP8( U8 x)
{
	return U8( (x>>4) | ((x << 4) & 0xF0));
}

INLINE( U16, Excange byte in a word)
SWAP16( U16 x)
{
	return U16( (x>>8) | ((x <<8) & 0xFF00));
}

INLINE( U32, Excange and swap word of a double word)
SWAP32( U32 x)
{
	return U32( SWAP16(x >> 16) | (SWAP16(x & 0xFFFF) << 16));	
}

INLINE( U32, Excange  word of a double word)
XCHG32( U32 x)
{
	return U32( (x >> 16) | ((x & 0xFFFF) << 16));	
}


INLINE( PTR_TO(U8), Buffer Swap: Excange half byte part)
SWAPBUF8( PTR_TO(U8) b,int ne )
{
	PTR_TO(U8) tb=b;
	while(ne>0)
	{
		VAL_OF(tb)=SWAP8(VAL_OF(tb));
		ne--;
		tb++;
	};
	
	return b;
}

INLINE( PTR_TO(U16), Buffer Swap: Excange byte in a word)
SWAPBUF16( PTR_TO(U16) b,int ne )
{
	PTR_TO(U16) tb=b;
	while(ne>0)
	{
		VAL_OF(tb)=SWAP16(VAL_OF(tb));
		ne--;
		tb++;
	}
	return b;
}

INLINE( PTR_TO(U32), Buffer Swap: Excange word of a double word)
SWAPBUF32( PTR_TO(U32) b,int ne )
{
	PTR_TO(U32) tb=b;
	while(ne>0)
	{
		VAL_OF(tb)=SWAP32(VAL_OF(tb));
		ne--;
		tb++;
	}
	return b;
}

//----------------------------------------------
// IO Function
//----------------------------------------------

void inline outpdw (U16 port, U32 value)
{
	return;
}

U32 inline inpdw (U16 port)
{
	return 0;
}
#endif

/*

//===========================================================================
// BIT Function
//===========================================================================

INLINE( UNS, Set bit n of a byte-word-dword)
BIT_SET( UNS x, UNS n ) // n: 0-31
     {
     //asm  {mov ecx,n; xor eax,eax; mov eax,x; BTS eax,ecx; mov x,eax;};

     return x;
     }

INLINE( UNS, Reset bit n of a byte-word-dword)
BIT_RST( UNS x, UNS n) // n: 0-31
     {
     //asm  {mov ecx,n; xor eax,eax; mov eax,x; BTR eax,ecx; mov x,eax;};
     return x;
     }

INLINE( UNS, Return the value of a bit in a byte-word-dword)
BIT_TST( UNS x, UNS n) // n: 0-31
     {
     //asm  {mov ecx,n; mov eax,x; BT eax,ecx; rcl eax,1; and eax,1; mov x,eax};
     return x;
     }

DEFINE(const U32, Bit mask used by BIT-FLD function)
BIT_MSK_VAL[32];
     

INLINE( UNS, set to a value v a bit field starting from bit n with lenght l)
BIT_FLD_SET( UNS x, UNS n, UNS l, UNS v) // n: 0-31, l=1-32
     {
     U32 msk;

     if(n>=l)
          {
          msk=BIT_MSK_VAL[n] & ~BIT_MSK_VAL[n-l];
          v <<=(n+1-l);
          }
     else {
          msk=BIT_MSK_VAL[n];
          }

     x= (x & ~msk) | v;

     return x;
     }

INLINE( UNS, get the value of a bit field starting from bit n with lenght l)
BIT_FLD_GET( UNS x, UNS n, UNS l)
     {
     U32 msk;

     if(n>=l)
          {
          msk=BIT_MSK_VAL[n] & ~BIT_MSK_VAL[n-l];
          x= x & msk;
          x >>=(n+1-l);
          }
     else {
          msk=BIT_MSK_VAL[n];
          x= x & msk;
          }

     return x;
     }

INLINE( NONE, in a bit stream vec set the bit num to a value val)
BIT_VCT_SET( PTR_TO(U8)vec, UNS num, BOOL val)
     {
     NOTE( Bit order is reversed 0..7)

     UNS bytAdd;                        // byte address
     UNS bitAdd;                        // bit  address

     bytAdd= num /8;
     bitAdd= 7 - (num %8);

     if(val)   // 1
          {
          vec[bytAdd]=BIT_SET( vec[bytAdd], bitAdd );
          }
     else {    // 0
          vec[bytAdd]=BIT_RST( vec[bytAdd], bitAdd );
          }
     }

INLINE( BOOL, get the value of a bit located in stream vec at num position)
BIT_VCT_GET( PTR_TO(U8)vec, UNS num)
     {
     NOTE( Bit order is reversed 0..7)

     UNS bytAdd;                        // byte address
     UNS bitAdd;                        // bit  address

     bytAdd= num /8;
     bitAdd= 7 - (num %8);

     return BOOL(BIT_TST( vec[bytAdd], bitAdd));
     }


INLINE( NONE, in a bit stream vec set the bit num to a value val)
BIT_FLD_VCT_SET( PTR_TO(U8)vec, UNS num, UNS val, UNS ln=1)
     {
     NOTE( Bit order is reversed 0..7)

     UNS bytAdd;                        // byte address
     UNS bitAdd;                        // bit  address

     num*=ln;
     bytAdd= (num) /8;
     bitAdd= 7-( num %8);

     vec[bytAdd]=BIT_FLD_SET( vec[bytAdd], bitAdd, ln, val);
     };



INLINE( U32, get the value of a bit located in stream vec at num position)
BIT_FLD_VCT_GET( PTR_TO(U8)vec, UNS num, UNS ln=1)
     {
     NOTE( Bit order is reversed 0..7)

     UNS bytAdd;                        // byte address
     UNS bitAdd;                        // bit  address

     num*=ln;
     bytAdd= (num) /8;
     bitAdd= 7- ( num %8);

     return BIT_FLD_GET( vec[bytAdd], bitAdd, ln);
     };

*/

