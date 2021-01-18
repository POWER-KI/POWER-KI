/* ======================  ===================================================
		 XPLAB           Xplab s.a.s. - viale Sant Eufemia, 39
   Research in Automation                 25135 Brescia - Italy
	 www.xplab.net                       Tel +39 030 2350035
    *** RESERVED ***				  (C) 2020 XPLAB CAP
   ======================  ===================================================
   File name            :  PWK-WRP-LINK.cpp
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


#include "PWK-WRP-LINK.hpp"
#include <windows.h>


FUNCTION(PTR_TO(U_CHR), String Copy)
StrCpy( PTR_TO(U_CHR)d, PTR_TO(U_CHR)s)
	{
	if(!d)return d;
	if(!s){d[0]=0; return d;};

	return wcscpy(d,s);
	}

FUNCTION(int, Ordinal compare)
StrCmp(PTR_TO(U_CHR)s1, PTR_TO(U_CHR)s2)
	{
	if(!s1 && !s2) return 0;
	if(!s1) return -1;
	if(!s2) return 1;

	return wcscmp( s1,s2);
	}

FUNCTION(int, Ordinal compare case insensitive)
StrCmp_I(PTR_TO(U_CHR)s1, PTR_TO(U_CHR)s2)
	{
	if(!s1 && !s2) return 0;
	if(!s1) return -1;
	if(!s2) return 1;

	return _wcsicmp(s1,s2);
	}

FUNCTION(int, Ordinal compare n chr case insensitive)
StrCmp_IN(PTR_TO(U_CHR)s1, PTR_TO(U_CHR)s2, int n)
	{
	if(!s1 && !s2) return 0;
	if(!s1) return -1;
	if(!s2) return 1;

	return _wcsnicmp(s1,s2,n);
	}

FUNCTION(PTR_TO(U_CHR), Search s2 in s1)
StrStr(PTR_TO(U_CHR)s1, PTR_TO(U_CHR)s2)
	{
	if(!s1 || !s2)return NULL;

	return wcsstr(s1,s2);
	}

FUNCTION(int, Return string len)
StrLen(PTR_TO(A_CHR)s)
	{
	if(!s )return 0;
	return strlen(s);
	}

FUNCTION(int, Return string len)
StrLen(PTR_TO(U_CHR)s)
	{
	if(!s )return 0;
	return wcslen(s);
	}

FUNCTION(PTR_TO(U_CHR),Remove head and trailing spaces)
Nospaces(PTR_TO(U_CHR) s)
     {     
     int l,i,ol;
     U_CHR car;
     U_CHR space=U_CHR(' ');

     if(!s) return NULL;
     ol=l=StrLen( s );
     if( l<=0 ) return s;

	do	{
		car=s[l-1];
		if(car <= space )
			{
			l--;
			}
		else break;
		}while(l > 0);

	if(l<=0)
		{
		s[l]=0;
		return s;
		}

	if(ol!=l)
		{
		s[l]=0;		
		}		

     i=0;	 
     while( car=s[i], car <= space && i<l ) { i++;}

	if(i==l)
		{
		s[0]=0;
		return s; 
		}

     if( i>0 )	 
		{
		StrCpy(s,&s[i]);		
		}

	return s;
     }


FUNCTION(PTR_TO(U_CHR), From A_CHR to U_CHR - in a new string )
StrAtoU(PTR_TO(A_CHR)s)
	{
	PTR_TO(U_CHR) d;
	PTR_TO(U_CHR) r;
	int len;
	if(!s) return (U_CHR*)NULL;
	len=StrLen(s);
	if(!len) return (U_CHR*)NULL;
	r=d=new U_CHR[len+2];
	
	while(*s)
		{
		(*d)=*((U8*)s);
		d++;
		s++;
		}
	(*d)=NULL;
	return r;
	}		

FUNCTION(PTR_TO(A_CHR), From U_CHR to A_CHR - in a new string)
StrUtoA(PTR_TO(U_CHR)s)
	{
	PTR_TO(A_CHR) d;
	PTR_TO(A_CHR) r;
	int len;
	if(!s) return(A_CHR*)NULL;
	len=StrLen(s);
	if(!len) return (A_CHR*)NULL;
	r=d=new A_CHR[len+2];
		

	while(*s)
		{
		(*d)=(A_CHR)(*s);
		d++;
		s++;
		}
	(*d)=NULL;
	return r;
	}

FUNCTION(PTR_TO(A_CHR), From U_CHR to U_CHR/UTF - in a new string)
StrUtoUTF(PTR_TO(U_CHR)s)
	{
	int len;
	PTR_TO(A_CHR) ns;
	
	if(!s) return NULL;
	
	NOTE(Get the size)
		
	len=WideCharToMultiByte(CP_UTF8,0,s,-1,NULL,0, 0,0);

	if(!len) return NULL;
	ns=new A_CHR[len+1];	

	WideCharToMultiByte(CP_UTF8,0,s,-1,ns,len, 0,0);
	ns[len]=0;
	return ns;
	}

FUNCTION(PTR_TO(U_CHR), From U_CHR/UTF to U_CHR - in a new string)
StrUTFtoU(PTR_TO(A_CHR)s)
	{
	int len;	
	PTR_TO(U_CHR) ns;
	
	if(!s) return NULL;
	
	len=MultiByteToWideChar(CP_UTF8,0,s,-1,NULL,0);
	if(!len) return NULL;
	
	ns=new U_CHR[len+1];
	MultiByteToWideChar(CP_UTF8,0,s,-1,ns,len);
	ns[len]=0;
	return ns;
	}

FUNCTION(PTR_TO(U_CHR), Duplicate String)
StrDup( const PTR_TO(U_CHR)s)
	{
	if(!s )return NULL;
	unsigned ln= wcslen(s) + 1;
	
	return wmemcpy(new U_CHR[ln],s,ln);
	}	

FUNCTION(PTR_TO(U_CHR), Search s2 in s1 case insensitive)
StrStr_I(PTR_TO(U_CHR)s1, PTR_TO(U_CHR)s2)
	{
     size_t len2;
     size_t len1;

	if(!s1 || !s2)return NULL;

     len1 = wcslen(s1);
     len2 = wcslen(s2);

     if (!len2)
          {
	     return NULL;
	     }

     while (len2 <= len1)
          {
          if (StrCmp_IN(s1,s2,len2) == 0)
               {
			return s1;
	          }
	     s1++;
	     len1--;
          }

     return NULL;
	}


FUNCTION(int,return the idx+1 of val string in a comma separated list - ins=1 case insensitive)
StrSelect(PTR_TO(U_CHR)v, PTR_TO(U_CHR)str, int ins, U_CHR sep)
     {
	PTR_TO(U_CHR)val;
     PTR_TO(U_CHR)t;
     PTR_TO(U_CHR)f;
     PTR_TO(U_CHR)s;
     U_CHR c;
     int ct=1;
     int sl;
	U_CHR space=U_CHR(' ');
	U_CHR comma=sep;

     if(!v || !str) return 0;
	sl=StrLen(v);
     if(!sl) return 0;
     if(!StrLen(str)) return 0;

	if(v[0]<=L' ' || v[sl-1]<=L' ')
		{
		val=StrDup(v);
		Nospaces(val);

		sl=StrLen(val);
		if(!sl) return 0;
		}		
	else val=v;

     s=str;
	f=str;

     while(1)
          {
          if(ins)
			{
               f=StrStr_I(f,val);
			}
          else	{
               f=StrStr(f,val);
			}

          if(!f)
			{
			if(val !=v) delete val;
			return NULL;
			}
		
		if(f!=str) //verifica che prima ci sia un separatore
			{
			t=f;
			t--;
	          c=t[0];
	          if( !(!c || c<=space || c==comma ))
				{
				f+=sl;
				continue;
				}
			}
		
		//verifica che dopo ci sia un separatore	
          c=f[sl]; 
          if(!c || c<=space || c==comma )break;
          f+=sl;
          }

     while(s<f)
          {
          if(VAL_OF(s)==comma)ct++;
          s++;
          }
	
	if(val!=v) delete val;
     return ct;
     }

A_CHR * StrUpr(A_CHR* s)
	{
	A_CHR* os=s;
	
	while(VAL_OF(s))
		{
		VAL_OF(s)=toupper(VAL_OF(s));
		s++;
		}
	return os;
	}

U_CHR * StrUpr(U_CHR* s)
	{
	U_CHR* os=s;
	
	while(VAL_OF(s))
		{
		VAL_OF(s)=towupper(VAL_OF(s));
		s++;
		}
	return os;
	}


A_CHR * StrLwr(A_CHR*s)
	{
	A_CHR* os=s;
	
	while(VAL_OF(s))
		{
		VAL_OF(s)=tolower(VAL_OF(s));
		s++;
		}	
	return os;
	}

U_CHR * StrLwr(U_CHR*s)
	{
	U_CHR* os=s;
	
	while(VAL_OF(s))
		{
		VAL_OF(s)=towlower(VAL_OF(s));
		s++;
		}	
	return os;
	}

FUNCTION(int, Ordinal Compare case insensitive and ignore space at the begin and end)
StrCmp_IX(PTR_TO(A_CHR)s1, PTR_TO(A_CHR)s2)
	{	
	if(!s1 && !s2) return 0;
	if(!s1) return -1;
	if(!s2) return 1;

	while(VAL_OF(s1) )
		{
		if(VAL_OF(s1)==A_CHR(' '))
			{
			s1++;			
			}
		else break;
		}

	while(VAL_OF(s2) )
		{
		if(VAL_OF(s2)==A_CHR(' '))
			{
			s2++;			
			}
		else break;
		}

	while(VAL_OF(s1) || VAL_OF(s2))
		{
		if(VAL_OF(s1)==A_CHR(' ') && !VAL_OF(s2))
			{
			s1++;
			continue;
			}

		if(VAL_OF(s2)==A_CHR(' ') && !VAL_OF(s1))
			{
			s2++;
			continue;
			}

		if(VAL_OF(s1) != VAL_OF(s2))
			{
			if(toupper(VAL_OF(s1)) < toupper(VAL_OF(s2))) return -1;
			if(toupper(VAL_OF(s1)) > toupper(VAL_OF(s2))) return 1;		
			}
		
		s1++;
		s2++;
		}
	return 0;
	}

FUNCTION(int, Ordinal Compare  equal case insensitive  and ignore space at the begin and end)
StrCmp_IX(PTR_TO(U_CHR)s1, PTR_TO(U_CHR)s2)
	{
	if(!s1 && !s2) return 0;
	if(!s1) return -1;
	if(!s2) return 1;

	while(VAL_OF(s1) )
		{
		if(VAL_OF(s1)==U_CHR(' '))
			{
			s1++;			
			}
		else break;
		}

	while(VAL_OF(s2) )
		{
		if(VAL_OF(s2)==U_CHR(' '))
			{
			s2++;			
			}
		else break;
		}

	while(VAL_OF(s1) || VAL_OF(s2))
		{
		if(VAL_OF(s1)==U_CHR(' ') && !VAL_OF(s2))
			{
			s1++;
			continue;
			}

		if(VAL_OF(s2)==U_CHR(' ') && !VAL_OF(s1))
			{
			s2++;
			continue;
			}

		if(VAL_OF(s1) != VAL_OF(s2))
			{
			if(toupper(VAL_OF(s1)) < toupper(VAL_OF(s2))) return -1;
			if(toupper(VAL_OF(s1)) > toupper(VAL_OF(s2))) return 1;		
			}
		
		s1++;
		s2++;
		}
	return 0;
	}

FUNCTION(int, Ordinal compare n chr)
StrCmp_N(PTR_TO(A_CHR)s1, PTR_TO(A_CHR)s2, int n)
	{
	if(!s1 && !s2) return 0;
	if(!s1) return -1;
	if(!s2) return 1;

	return strncmp(s1,s2,n);
	}
	
FUNCTION(int, Ordinal compare n chr)
StrCmp_N(PTR_TO(U_CHR)s1, PTR_TO(U_CHR)s2, int n)
	{
	if(!s1 && !s2) return 0;
	if(!s1) return -1;
	if(!s2) return 1;

	return wcsncmp(s1,s2,n);
	}



FUNCTION(PTR_TO(A_CHR), String Copy N chr)
StrCpy_N(PTR_TO(A_CHR)d, PTR_TO(A_CHR)s, int n)
	{
	if(!d)return d;
	if(!s){d[0]=0; return d;};
	
	return strncpy(d,s,n);
	}

FUNCTION(PTR_TO(U_CHR), String Copy N chr)
StrCpy_N(PTR_TO(U_CHR)d, PTR_TO(U_CHR)s, int n)
	{
	if(!d)return d;
	if(!s){d[0]=0; return d;};
	
	return wcsncpy(d,s,n);
	}

FUNCTION(PTR_TO(A_CHR), Search chr c in s)
StrChr(PTR_TO(A_CHR)s, A_CHR c)
	{
	if(!s) return NULL;
	return (A_CHR*) strchr(s,c);
	}

FUNCTION(PTR_TO(U_CHR), Search chr c in s)
StrChr(PTR_TO(U_CHR)s, U_CHR c)
	{
	if(!s) return NULL;
	return wcschr(s,c);
	}

//=======================================
//math Conversion ..


#define MCV_TRAILER_SPACE_INT \
if (e && VAL_OF(e) != NULL) \
{ \
	while (VAL_OF(e)>0 && VAL_OF(e)<= 32 ) e++; \
	if(VAL_OF(e) != NULL && VAL_OF(e)!=L'.') return 0; \
}


#define MCV_TRAILER_SPACE \
if (e && VAL_OF(e) != NULL) \
{ \
	while (VAL_OF(e)>0 && VAL_OF(e)<= 32 ) e++; \
	if(VAL_OF(e) != NULL) return 0; \
}


//=======================================


FUNCTION(int,Return s as int)
StrValInt(PTR_TO(A_CHR)s,int base)
     {     
     int v=0;
     if(!s) return v;
	PTR_TO(A_CHR)e=NULL;

     v= strtol(s, &e, base);     

	MCV_TRAILER_SPACE_INT;

	return v;
     }     

FUNCTION(int,Return s as int)
StrValInt(PTR_TO(U_CHR)s,int base)
     {     
     int v=0;
     if(!s) return v;
	PTR_TO(U_CHR)e=NULL;

     v= wcstol(s, &e,base);

	MCV_TRAILER_SPACE_INT;

	return v;
     }     

FUNCTION(unsigned ,Return s as unsigned)
StrValUns(PTR_TO(A_CHR)s,int base)
     {     
     unsigned v=0;
     if(!s) return v;
	PTR_TO(A_CHR)e=NULL;
     
     v=strtoul(s,&e,base);

	MCV_TRAILER_SPACE_INT;
	return v;
     }     

FUNCTION(unsigned,Return s as unsigned)
StrValUns(PTR_TO(U_CHR)s,int base)
     {     
     unsigned v=0;
     if(!s) return v;
	PTR_TO(U_CHR)e=NULL;
	
     v= wcstoul(s,&e,base);   

	MCV_TRAILER_SPACE_INT;

	return v;
	}


FUNCTION(FLT,Return s as Flt)
StrValFlt(PTR_TO(U_CHR)s, int ndc)
	{     
     double v=0;
     if(!s) return FLT(v);
	PTR_TO(U_CHR)e=NULL;

     v=wcstod(s, &e);

	MCV_TRAILER_SPACE;

	return v;
	}

FUNCTION(FLT,Return s as Flt)
StrValFlt(PTR_TO(U_CHR)s)
	{     
     double v=0;
     if(!s) return FLT(v);
	PTR_TO(U_CHR)e=NULL;

     v=wcstod(s, &e);
     
	MCV_TRAILER_SPACE;

	return v;
     }     

FUNCTION(double,Return s as Dbl)
StrValDbl(PTR_TO(U_CHR)s)
	{     
     double v=0;
     if(!s) return v;
	PTR_TO(U_CHR)e=NULL;

     v=wcstod(s, &e);
                               
	MCV_TRAILER_SPACE;
	return v;
     }     

FUNCTION(double,Return s as LL uns)
StrValU64(PTR_TO(U_CHR)s)
	{     
     U64 v=0;
     if(!s) return v;
	PTR_TO(U_CHR)e=NULL;
     
     v=wcstoull(s, &e,0);

	MCV_TRAILER_SPACE_INT;
	return v;
     }     

FUNCTION(double,Return s as LL int)
StrValI64(PTR_TO(U_CHR)s)
	{     
     I64 v=0;
     if(!s) return v;
	PTR_TO(U_CHR)e=NULL;

     v=wcstoll(s, &e,0);
                               
	MCV_TRAILER_SPACE_INT;
	return v;
     }     

//---------------------------------------------------------------------------
// Is...
//---------------------------------------------------------------------------

FUNCTION(int, hex Number)
IsChrHex(U_CHR c)
	{
	return iswxdigit(c);
	}


FUNCTION(int, Is a-z | a-z | 0-9)
IsChrAlnum(U_CHR c)
	{
	return iswalnum(c);
	}

FUNCTION(int, Is a-z | a-z )
IsChrAlpha(U_CHR c)
	{
	return iswalpha(c);
	}

FUNCTION(int, Is 0-9 )
IsChrNum(U_CHR c)
	{
	return iswdigit(c);
	}

FUNCTION(int, Is 0x00 - 0x7F )
IsChrAscii(U_CHR c)
	{
	return iswascii(c);
	}

FUNCTION(int, Is 0x00 - 0x1F | 0x7F )
IsChrCntrl(U_CHR c)
	{
	return iswcntrl(c);
	}

FUNCTION(int, Is 0x09 - 0x0D | 0x20 )
IsChrSpace(U_CHR c)
	{
	return iswspace(c);
	}

FUNCTION(int, A - Z )
IsChrUpper(U_CHR c)
	{
	return iswupper(c);
	}

FUNCTION(int, a - z )
IsChrLower(U_CHR c)
	{
	return iswlower(c);
	}


//---------------------------------------------------------------------------
// XU_VAL
//---------------------------------------------------------------------------

int HaveSig(PTR_TO(U_CHR) s)
	{
	int res=0;	
	
	if(!s) return NULL;
	while(VAL_OF(s))
		{
		if(VAL_OF(s) == L' ')
			{
			s++;
			continue;
			}
		
		if(VAL_OF(s) == L'-')
			{
			return true;			
			}
		return false;	
		}
	return false;
	}

	METHOD(XU_VAL,PTR_TO(U_CHR),Reset s)
	Reset( )
		{
		PTR_TO(U_CHR) r;
		r=s;
		s=NULL;
		return r;
		};
		
	METHOD(XU_VAL,int, True if float)
	IsFlt()
		{
		if(!IsNum()) return false;
		
		if(!s) return false;
		if(StrChr(s, L'.'))
			{
			return true;
			}

		if (StrStr_I(s, L"E"))
			{
			return true;
			}

		return false;
		};

	METHOD(XU_VAL,NONE, Convert to HEX)
	ToHex()
		{		
		U_CHR buf[100];
		XU_VAL p;
		FLT nf;
		int ni;
		unsigned nu;
		unsigned long ul; 	
				
		if(!IsNum())
			{
			(*this)=L"0x0";			
			return;
			}
			
		if(IsFlt())
			{
			nf=(*this);
			ul=*(unsigned*)&nf;			
			_ultow_s(*(unsigned*)&ul,buf,16);
			}
		else {
			if(HaveSig(s))
				{
				ni=(*this);
				_itow_s(*(int*)&ni,buf,16);
				}			
			else {
				nu=(*this);
				ul=nu;
				_ultow_s(*(unsigned*)&ul,buf,16);
				}
			}
		
		(*this) = L"0x";	
		(*this) <<= buf;
		};

	METHOD(XU_VAL,NONE, Convert to Binary)
	ToBin()
		{		
		U_CHR buf[100];
		XU_VAL p;
		FLT nf;
		int ni; 	
		unsigned nu;
		unsigned long ul;
				
		if(!IsNum())
			{
			(*this)=L"0b0";			
			return;
			}
	
		if(IsFlt())
			{
			nf=(*this);
			ul=*(unsigned*)&nf;

			_ultow_s(*(unsigned*)&ul,buf,2);
			}
		else {
			if(HaveSig(s))
				{
				ni=(*this);
				_itow_s(*(int*)&ni,buf,2);
				}			
			else {
				nu=(*this);
				ul=nu;
				_ultow_s(*(unsigned*)&ul,buf,2);
				}
			}
		
		(*this) = L"0b";	
		(*this) <<= buf;
		};


	METHOD(XU_VAL,PTR_TO(U_CHR), True if Hex Number)
	IsHex()
		{		
		U_CHR * res=NULL;		
		int sts=0;	//1=beg, 2=end
		PTR_TO(U_CHR) c;		
		int i,l, ix;
		if(!s) return NULL;
		
		l=StrLen(s);
		if(!l) return NULL;
		ix=0;
		c=s;
		for(i=0; i<l;i++, c++)
			{ 
			if(VAL_OF(c) == L' ')
				{
				if(sts==1) sts=2;
				continue;
				}

			if(sts==2 && VAL_OF(c) != L' ')
				{
				return NULL;
				}

			if(sts==0)
				{
				if(VAL_OF(c) != L'0')
					{
					return NULL;
					}				
				ix=1;
				sts=1;
				continue;
				}

			if(sts==1)
				{
				if(ix==1)
					{
					if(VAL_OF(c) != L'x' && VAL_OF(c) != L'X' )
						{
						return NULL;
						}
					ix++;					
					continue;
					}
				
				if(!IsChrHex(VAL_OF(c)))
					{
					return NULL;
					}
		
				if(ix==2) res=c;
				
				ix++;
				continue;
				}
			return NULL;
			}
		return res;				
		};


	METHOD(XU_VAL,PTR_TO(U_CHR), True if Binary Number)
	IsBin()
		{
		U_CHR * res=NULL;		
		int sts=0;	//1=beg, 2=end
		PTR_TO(U_CHR) c;		
		int i,l, ix;
		if(!s) return NULL;
		
		l=StrLen(s);
		if(!l) return NULL;
		ix=0;
		c=s;
		for(i=0; i<l;i++, c++)
			{ 
			if(VAL_OF(c) == L' ')
				{
				if(sts==1) sts=2;
				continue;
				}

			if(sts==2 && VAL_OF(c) != L' ')
				{
				return NULL;
				}

			if(sts==0)
				{
				if(VAL_OF(c) != L'0')
					{
					return NULL;
					}
				ix=1;
				sts=1;
				continue;
				}

			if(sts==1)
				{
				if(ix==1)
					{
					if(VAL_OF(c) != L'b' && VAL_OF(c) != L'B')
						{
						return NULL;
						}
					ix++;
					continue;
					}
				
				if(VAL_OF(c) != L'0' && VAL_OF(c) != L'1')
					{
					return NULL;
					}
				
				if(ix==2) res=c;
					
				ix++;
				continue;
				}
			return NULL;
			}
		return res;				
		};


	METHOD(XU_VAL,int, True if Number)
	IsNum()
		{
		int sgn=false; // +- found
		int dec=false;	// dec separator found
		int res=false;		
		int sts=0;	//1=beg, 2=end
		PTR_TO(U_CHR) c;		
		int i,l;
		if(!s) return false;
		
		l=StrLen(s);
		if(!l) return false;
		
		if(IsBin()) return true;
		if(IsHex()) return true;
		
		c=s;
		for(i=0; i<l;i++, c++)
			{ 
			if(VAL_OF(c) == L' ')
				{
				if(sts==1) sts=2;
				continue;
				}
			
			if(sts==2) 			
				{
				if(VAL_OF(c) != L' ')return false;	
				continue;			
				}

			if(VAL_OF(c) == L'+' || VAL_OF(c) == L'-')
				{
				if(sgn) return false;				
				sgn=1; 
				if(sts==1) sts=2; //Se escluso consente di gestire il segno separatamente ma poi la conversione fallisce
				continue;
				}

			if(VAL_OF(c) == L'.' )
				{
				if(sts==0) 
					{
					sts=1; //Beg
					dec=1; 					
					}
				else {	
					if(sts==1)
						{
						if(dec) return false;
						dec=1;
						}	
					}
				continue;
				}
											
			if(IsChrNum(*c))
				{
				if(sts==0)
					{
					sts=1;
					}
				res=true;
				}
			else {
				if (*c == L'e' || *c == L'E')
					{
					if (sts == 0)
						{
						return false;
						}
					res = false;
					sgn = false;
					dec = 1;
					}
				else {
					return false;
					}
				}				
			}
		return res;				
		};
		
	METHOD(XU_VAL,NONE, delete string) // Può nascondere errori 
	DelS()
		{
		if(s)
			{			
			delete s;
			s = NULL;
			}		
		};

	METHOD(XU_VAL,NONE, Reset s )
	RstS()
		{
		s=NULL;	
		};


	METHOD(XU_VAL,XU_VAL&, Transfer the value of e)
	Move(XU_VAL& e)
		{
		SetS(e.s);
		e.s=NULL;
		return *this;	
		};

	METHOD(XU_VAL,XU_VAL&, Transfer the value of e)
	SetS(PTR_TO(U_CHR) s1)
		{
		if(this->s==s1)
			{
			return *this;	
			}
			
		DelS();
		this->s=s1;
		return *this;	
		};


	METHOD(XU_VAL,int, Return the lenght)
	Len()
		{
		if(s)
			{
			return StrLen(s);
			}
		return NULL;	
		};

	METHOD(XU_VAL,int, Set the lenght)
	Len(int sz)
		{
		PTR_TO(U_CHR) t;
		int l;
		if(!sz)
			{
			DelS();
			return 0;
			}
		t=new U_CHR[sz+1];						
		t[0]=0;
			
		if(s)
			{
			l=MIN(sz,Len());
			StrCpy_N(t,this->s,l);t[l]=0;	//Close str		
			}		
		SetS(t);
		return Len();
		};


	METHOD(XU_VAL,PTR_TO(U_CHR), Conversion to string)
	ToStr()
		{
		return s;	
		};
		
	DESTROYER(XU_VAL)
		{
		DelS();
		};

	BUILDER(XU_VAL)()
		{
		s=NULL;
		};
	
	BUILDER(XU_VAL)(const XU_VAL& e)
		{
		this->s=NULL;
		if(e.s)s=StrDup(e.s);
		};
		
	BUILDER(XU_VAL)(PTR_TO(U_CHR) s )
		{
		this->s=NULL;
		if(s) 
			{		
			this->s=StrDup(s);
			}
		};

	BUILDER(XU_VAL)(int v )
		{
		U_CHR buf[50];
		StrFormat(buf,50,L"%d",v);
		s=StrDup(buf);
		};

	BUILDER(XU_VAL)(unsigned v )
		{
		U_CHR buf[50];
		StrFormat(buf,50,L"%u",v);
		s=StrDup(buf);
		};
	
	BUILDER(XU_VAL)(FLT v )
		{
		U_CHR buf[50];
		
		if(v == int(v))
			{
			StrFormat(buf,50,L"%d",int(v));
			}
		else {
			StrFormat(buf,50,L"%f",v);
			}
		s=StrDup(buf);
		};	
		

	METHOD(XU_VAL,int,Test for all spaces or NULL)
	IsSpaces( )
		{		
		PTR_TO(U_CHR) p;
		if(!s) return TRUE;
		
		for(p=s; VAL_OF(p); p++)
			{
			if(VAL_OF(p)!=L' ') return false;
			}
		return true;
		}

	METHOD(XU_VAL,int,Test for true)
	IsTrue( )
		{	
		if(!s) return false;	

		if(IsNum())
			{
			if(IsFlt())
				{
				if(FLT64(*this)== FLT64(0) ) return FALSE;			
				}
			if(unsigned(*this)== unsigned(0) ) return FALSE;				
			return TRUE;
			}
		return IsSpaces()==1 ? 0:1;	
		};

	METHOD(XU_VAL,NONE,Set value)
	Set(PTR_TO(U_CHR) s )
		{		
		SetS(StrDup(s));		
		};

	//------------------------------------
	METHOD(XU_VAL,PTR_TO(U_CHR), Search a U_CHR )
	Find(U_CHR c)
		{
		if(!s) return NULL;
		return StrChr(s,c);
		};

	METHOD(XU_VAL,PTR_TO(U_CHR), Search a U_CHR )
	Find_I(U_CHR c)
		{
		U_CHR s1[2];
		s1[0]=c;
		s1[1]=0;

		return Find_I(s1);
		};

	METHOD(XU_VAL,PTR_TO(U_CHR), Search a String )
	Find(PTR_TO(U_CHR) s1)
		{
		int l1,l2;
		if(!s1 || !s) return NULL;
		
		l1=Len();
		l2=StrLen(s1);
		if(!l1 || !l2) return NULL;
		if(l2>l1)return NULL;

		return StrStr(s,s1);
		};

	METHOD(XU_VAL,PTR_TO(U_CHR), Search a String )
	Find_I(PTR_TO(U_CHR) s1)
		{
		int l1,l2;
		if(!s1 || !s) return NULL;
		
		l1=Len();
		l2=StrLen(s1);
		if(!l1 || !l2) return NULL;
		if(l2>l1)return NULL;

		return StrStr_I(s,s1);
		};

	METHOD(XU_VAL,PTR_TO(U_CHR), Search a U_CHR Reverse)
	FindRvs(U_CHR c)
		{
		int l;
		if(!s) return NULL;

		for(l=Len(); l>0; l--)
			{
			if(s[l-1]==c)
				{
				return &s[l-1];
				}
			}
		return NULL;		
		};

	METHOD(XU_VAL,PTR_TO(U_CHR), Search a U_CHR Reverse)
	FindRvs_I(U_CHR c)
		{
		U_CHR s1[2];
		s1[0]=c;
		s1[1]=0;

		return FindRvs_I(s1);		
		};


	METHOD(XU_VAL,PTR_TO(U_CHR), Search a String )
	FindRvs(PTR_TO(U_CHR) s1)
		{
		int l1,l2;
		if(!s1 || !s) return NULL;
		
		l1=Len();
		l2=StrLen(s1);
		if(!l1 || !l2) return NULL;
		if(l2>l1)return NULL;

		l1-=l2;
		
		do   {			
			if(!StrCmp_N(&s[l1],s1,l2))
				{
				return &s[l1];
				}
			l1--;
			}while(l1>=0);

		return NULL;
		};

	METHOD(XU_VAL,PTR_TO(U_CHR), Search a String )
	FindRvs_I(PTR_TO(U_CHR) s1)
		{
		int l1,l2;
		if(!s1 || !s) return NULL;
		
		l1=Len();
		l2=StrLen(s1);
		if(!l1 || !l2) return NULL;
		if(l2>l1)return NULL;

		l1-=l2;
		
		do   {			
			if(!StrCmp_IN(&s[l1],s1,l2))
				{
				return &s[l1];
				}
			l1--;
			}while(l1>=0);

		return NULL;
		};


	//-------------------
	METHOD(XU_VAL,PTR_TO(U_CHR), Get new XU_VAL up to th char )
	GetUpToChr(PTR_TO(U_CHR) c)
		{		
		PTR_TO(U_CHR) pc;
		int d;
		
		pc=Find(c);
		if(!pc) return NULL;
		d=pc-s;
		
		if(!d) return NULL;
		pc=new U_CHR[d+1];
		memcpy(pc,s,d*sizeof(U_CHR));
		
		pc[d]=0; // Close the item
		return pc;				
		};

	METHOD(XU_VAL,PTR_TO(U_CHR), Get new XU_VAL from th char )
	GetFromChr(PTR_TO(U_CHR) c)
		{		
		PTR_TO(U_CHR) pc;
		
		pc=Find(c);
		if(!pc) return NULL;
		
		return StrDup(&pc[StrLen(c)]);
		};


	METHOD(XU_VAL,PTR_TO(U_CHR), Get new XU_VAL up to th char )
	GetUpToChr(U_CHR c)
		{
		PTR_TO(U_CHR) pc;
		int d;
		
		pc=Find(c);
		if(!pc) return NULL;
		d=pc-s;
		
		if(!d) return NULL;
		pc=new U_CHR[d+1];
		memcpy(pc, s, d * sizeof(U_CHR));
		
		pc[d]=0; // Close the item
	
		return pc;		
		};

	METHOD(XU_VAL,PTR_TO(U_CHR), Get new XU_VAL from th char )
	GetFromChr(U_CHR c)
		{		
		PTR_TO(U_CHR) pc;
		
		pc=Find(c);
		if(!pc) return NULL;
		
		return StrDup(&pc[1]);
		};


	//-------------------
	METHOD(XU_VAL,PTR_TO(U_CHR), Get new XU_VAL up to th char )
	GetUpToChr_I(PTR_TO(U_CHR) c)
		{		
		PTR_TO(U_CHR) pc;
		int d;
		
		pc=Find_I(c);
		if(!pc) return NULL;
		d=pc-s;
		
		if(!d) return NULL;
		pc=new U_CHR[d+1];
		memcpy(pc, s, d * sizeof(U_CHR));
		
		pc[d]=0; // Close the item
		return pc;				
		};

	METHOD(XU_VAL,PTR_TO(U_CHR), Get new XU_VAL from th char )
	GetFromChr_I(PTR_TO(U_CHR) c)
		{		
		PTR_TO(U_CHR) pc;
		
		pc=Find_I(c);
		if(!pc) return NULL;
		
		return StrDup(&pc[StrLen(c)]);
		};


	METHOD(XU_VAL,PTR_TO(U_CHR), Get new XU_VAL up to th char )
	GetUpToChr_I(U_CHR c)
		{
		PTR_TO(U_CHR) pc;
		int d;
		
		pc=Find_I(c);
		if(!pc) return NULL;
		d=pc-s;
		
		if(!d) return NULL;
		pc=new U_CHR[d+1];
		memcpy(pc, s, d * sizeof(U_CHR));
		
		pc[d]=0; // Close the item
	
		return pc;		
		};

	METHOD(XU_VAL,PTR_TO(U_CHR), Get new XU_VAL from th char )
	GetFromChr_I(U_CHR c)
		{		
		PTR_TO(U_CHR) pc;
		
		pc=Find_I(c);
		if(!pc) return NULL;
		
		return StrDup(&pc[1]);
		};
	
	//-------------------
	METHOD(XU_VAL,PTR_TO(U_CHR), Get new XU_VAL up to th char )
	GetFromChrRvs(PTR_TO(U_CHR) c)	
		{		
		PTR_TO(U_CHR) pc;
		int d;
		
		pc=FindRvs(c);
		if(!pc) return NULL;
		d=pc-s;
		
		if(!d) return NULL;
		pc=new U_CHR[d+1];
		memcpy(pc, s, d * sizeof(U_CHR));
		
		pc[d]=0; // Close the item
		return pc;				
		};

	METHOD(XU_VAL,PTR_TO(U_CHR), Get new XU_VAL from th char )
	GetUpToChrRvs(PTR_TO(U_CHR) c)	
		{		
		PTR_TO(U_CHR) pc;
		
		pc=FindRvs(c);
		if(!pc) return NULL;
		
		return StrDup(&pc[StrLen(c)]);
		};


	METHOD(XU_VAL,PTR_TO(U_CHR), Get new XU_VAL up to th char )
	GetFromChrRvs(U_CHR c)	
		{
		PTR_TO(U_CHR) pc;
		int d;
		
		pc=FindRvs(c);
		if(!pc) return NULL;
		d=pc-s;
		
		if(!d) return NULL;
		pc=new U_CHR[d+1];
		
		memcpy(pc, s, d * sizeof(U_CHR));
		pc[d]=0; // Close the item
	
		return pc;		
		};

	METHOD(XU_VAL,PTR_TO(U_CHR), Get new XU_VAL from th char )
	GetUpToChrRvs(U_CHR c)
		{		
		PTR_TO(U_CHR) pc;
		
		pc=FindRvs(c);
		if(!pc) return NULL;
		
		return StrDup(&pc[1]);
		};

	//-------------------
	METHOD(XU_VAL,PTR_TO(U_CHR), Get new XU_VAL up to th char )
	GetFromChrRvs_I(PTR_TO(U_CHR) c)	
		{		
		PTR_TO(U_CHR) pc;
		int d;
		
		pc=FindRvs_I(c);
		if(!pc) return NULL;
		d=pc-s;
		
		if(!d) return NULL;
		pc=new U_CHR[d+1];
		memcpy(pc, s, d * sizeof(U_CHR));
		
		pc[d]=0; // Close the item
		return pc;				
		};

	METHOD(XU_VAL,PTR_TO(U_CHR), Get new XU_VAL from th char )
	GetUpToChrRvs_I(PTR_TO(U_CHR) c)	
		{		
		PTR_TO(U_CHR) pc;
		
		pc=FindRvs_I(c);
		if(!pc) return NULL;
		
		return StrDup(&pc[StrLen(c)]);
		};

	METHOD(XU_VAL,PTR_TO(U_CHR), Get new XU_VAL up to th char )
	GetFromChrRvs_I(U_CHR c)	
		{
		PTR_TO(U_CHR) pc;
		int d;
		
		pc=FindRvs_I(c);
		if(!pc) return NULL;
		d=pc-s;
		
		if(!d) return NULL;
		pc=new U_CHR[d+1];
		memcpy(pc, s, d * sizeof(U_CHR));
		
		pc[d]=0; // Close the item
	
		return pc;		
		};

	METHOD(XU_VAL,PTR_TO(U_CHR), Get new XU_VAL from th char )
	GetUpToChrRvs_I(U_CHR c)
		{		
		PTR_TO(U_CHR) pc;
		
		pc=FindRvs_I(c);
		if(!pc) return NULL;
		
		return StrDup(&pc[1]);
		};

	//-------------------
	METHOD(XU_VAL,U_CHR, Get the First U_CHR)
	Fst()
		{
		if(!s) return NULL;
		return s[0];
		};

	METHOD(XU_VAL,NONE, Set the First U_CHR)
	Fst(U_CHR c)
		{
		if(!StrLen(s)) 
			{
			(*this) <<= c;
			return;
			}
		s[0]=c;
		};

	METHOD(XU_VAL,U_CHR, Get the Last U_CHR)
	Lst()
		{
		if(!StrLen(s)) return NULL;		
		return s[StrLen(s)-1];
		};

	METHOD(XU_VAL,NONE, Set the Last U_CHR)
	Lst(U_CHR c)
		{
		if(!StrLen(s)) 
			{
			(*this) <<= c;
			return;
			}
		s[StrLen(s)-1]=c;
		};

	METHOD(XU_VAL,int, Check against NULL s pointer)
	IsNULL()
		{
		if(!s)return TRUE; 
		return FALSE;
		};


	OPERATOR(XU_VAL,~,int,Check existence)()
		{
		if(!s) return 0;
		if(s[0] ==0) return 0;
		if(IsSpaces()) return 0;
		return 1;		
		};		

	OPERATOR(XU_VAL,[],U_CHR&,Get Char)(int i)
		{
		if (!s || i > Len()) return *s;
		return s[i];		
		};		

	OPERATOR(XU_VAL,=,XU_VAL&,Assignement)(const XU_VAL& e)
		{				
		return SetS(StrDup(e.s));
		};
		
	OPERATOR(XU_VAL,=,XU_VAL&,String Assignement)(PTR_TO(U_CHR) s)
		{		
		return SetS(StrDup(s));
		};

	OPERATOR(XU_VAL,=,XU_VAL&,Int Assignement)(const int i)
		{		
		U_CHR buf[50];
		
		#ifdef WIN32
		_itow_s(i,buf,10);
		#else		
		StrFormat(buf,49,L"%d",i);
		#endif

		return SetS(StrDup(buf));
		};

	OPERATOR(XU_VAL,=,XU_VAL&,Int Assignement)(const unsigned i)
		{		
		U_CHR buf[50];
		unsigned long ul;

		#ifdef WIN32
		ul=i;
		_ultow_s(ul,buf,10);
		#else
		StrFormat(buf,49,L"%u",i);
		#endif

		return SetS(StrDup(buf));
		};

	OPERATOR(XU_VAL,=,XU_VAL&,Int Assignement)(const U64 i)
		{
		U_CHR buf[50];

		StrFormat(buf,49,L"%llu",i); //lli for signed

		return SetS(StrDup(buf));
		};

	OPERATOR(XU_VAL,=,XU_VAL&,Int Assignement)(const I64 i)
		{
		U_CHR buf[50];

		StrFormat(buf,49,L"%lli",i); //lli for signed

		return SetS(StrDup(buf));
		};


	//-------------------------------------
	
	OPERATOR(XU_VAL,=,XU_VAL&,FLT Assignement)(const FLT i)
		{		
		U_CHR buf[51];
		
		if(i == int(i))
			{
			#ifdef WIN32
			_itow_s(i,buf,10);			
			#else
			StrFormat(buf,49,L"%d",int(i));
			#endif
			}
		else {		
			StrFormat(buf,49,L"%f",i);
			}
				
		return SetS(StrDup(buf));
		};

	OPERATOR(XU_VAL,=,XU_VAL&,FLT64 Assignement)(const FLT64 i)
		{
		U_CHR buf[51];
		
		if(i == I64(i))
			{
			#ifdef WIN32
			_i64tow_s(i,buf,51,10);			
			#else
			StrFormat(buf,49,L"%d",int(i));
			#endif
			}
		else {			
			StrFormat(buf,49,L"%.20g",i);
			}
		
		return SetS(StrDup(buf));		
		};
	

	//----------------------------------

	OPERATOR(XU_VAL,<<=,XU_VAL&,Right Insert)(XU_VAL& e)
		{
		PTR_TO(U_CHR) ns;
		int len;
		int l1=StrLen(s);
		int l2=StrLen(e.s);

		if(!l2) return *this;

		len=l1+l2;		
				
		ns=new U_CHR[len+1];		

		ns[len]=0; //Forse non serve
		if(l1) StrCpy_N(ns,s,l1);
		StrCpy_N(&ns[l1],e.s,l2);
		
		return SetS(ns);
		};

	OPERATOR(XU_VAL,<<=,XU_VAL&,Right Insert)(PTR_TO(U_CHR) as)
		{
		PTR_TO(U_CHR) ns;
		int len;
		int l1=StrLen(s);
		int l2=StrLen(as);

		if(!l2) return *this;

		len=l1+l2;
				
		ns=new U_CHR[len+1];		

		ns[len]=0; // Forse non serve
		if(l1) StrCpy_N(ns,s,l1);
		StrCpy_N(&ns[l1],as,l2);
		
		return SetS(ns);
		};

	OPERATOR(XU_VAL,<<=,XU_VAL&,Right Insert)(U_CHR c)
		{
		U_CHR buf[2];
		buf[0]=c;
		buf[1]=0;
		
		(*this)<<=buf;
			
		return * this;	
		};


	//----------------------------------

	OPERATOR(XU_VAL,>>=,XU_VAL&,Left Insert)(XU_VAL& e)
		{
		PTR_TO(U_CHR) ns;
		int l1=StrLen(s);
		int len=l1+StrLen(e.s);

		ns=new U_CHR[len+1];
		ns[0]=0;
		ns[len]=0; // Forse non serve
		StrCpy(ns,s);
		StrCpy(&ns[l1],e.s);		

		e.SetS(ns);
						
		return e;	
		};

	//----------------------------------

	OPERATOR(XU_VAL,>>,XU_VAL&,Right shift)(const int i)
		{		
		unsigned u;
		if(IsNum()) 
			{
			u=*this;
			u>>=i;
			*this=u;
			}
		else {
			if(i>=0 && i<StrLen(s))
				{				
				s[StrLen(s)-i]=0;
				(*this)=s;
				}
			else DelS();	
			}			
		return * this;	
		};

	OPERATOR(XU_VAL,<<,XU_VAL&,Right shift)(const int i)
		{		
		unsigned u;
		if(IsNum()) 
			{
			u=*this;
			u<<=i;
			*this=u;
			}
		else {
			if(i>=0 && i<StrLen(s))
				{
				(*this)=&s[i];		
				}
			else DelS();	
			}	
		return * this;	
		};


	METHOD(XU_VAL,int,Exact Comparison for NNV)
	CMP( XU_VAL e)
		{
		XU_VAL s1,s2;
		s1=*this;
		s2=e;
		
		int r;
		if(s1.IsNum() && s2.IsNum())
			{
			if(FLT64(s1) == FLT64(s2)) return 0;
			if(FLT64(s1) <  FLT64(s2)) return -1;
			return 1;
			}
		
		r=StrCmp(s1.s,s2.s);
		
		return r;		
		};

	METHOD(XU_VAL,int,Exact Comparison for NNV)
	CMPI( XU_VAL e)
		{
		XU_VAL s1,s2;
		s1=*this;
		s2=e;
		
		int r;
		if(s1.IsNum() && s2.IsNum())
			{
			if(FLT64(s1) == FLT64(s2)) return 0;
			if(FLT64(s1) <  FLT64(s2)) return -1;
			return 1;
			}
		
		r=StrCmp_I(s1.s,s2.s);
		
		return r;
		};
	
	OPERATOR(XU_VAL,==,int, Comparison)( XU_VAL& e)
		{		
		int r;
		if(IsNum() && e.IsNum())
			{
			return int(FLT64(*this)==FLT64(e));
			}
		
		r=StrCmp_IX(s,e.s);
		
		if(!r) return 1;
		return 0;
		};

	OPERATOR(XU_VAL,!=,int, Comparison)( XU_VAL& e)
		{
		return !( (*this)==e);
		};


	OPERATOR(XU_VAL,==,int, Comparison)( PTR_TO(U_CHR) e)
		{
		int res;
		int r;
		XU_VAL s2;		
		s2.SetS(e);		
		
		if(IsNum() && s2.IsNum())
			{
			res= int(FLT64(*this)==FLT64(s2));
			s2.RstS();
			return res;
			}
		
		r=StrCmp_IX(s,s2.s);
		
		s2.RstS();
		if(!r) return 1;
		return 0;
		};

	OPERATOR(XU_VAL,!=,int, Comparison)( PTR_TO(U_CHR) e)
		{
		return !( (*this)==e);
		}
	
	XU_VAL::operator PTR_TO(U_CHR)()
		{
		return s;
		};
	
	XU_VAL::operator int()
		{		
		return StrValInt(s);
		};
	
	XU_VAL::operator unsigned()
		{		
		return StrValUns(s);
		};

	XU_VAL::operator FLT()
		{
		return StrValFlt(s);
		};

	XU_VAL::operator FLT64()
		{
		return StrValDbl(s);
		};

	XU_VAL::operator U64()
		{
		return StrValU64(s);
		};

	//OPERATOR(XU_VAL,I64,I64, Conv to LL int)()
	XU_VAL::operator I64()
		{
		return StrValI64(s);
		};


	METHOD(XU_VAL,int, return an int)
	StrValInt(PTR_TO(U_CHR)s)
		{
		PTR_TO(U_CHR) ss;
		int bs=10;				
		int v=0;		
		if(!s) return v;
		
		ss=IsHex();				
		if(ss) 
			{
			s=ss;
			bs=16;
			}
		else {
			ss=IsBin();
			if(ss) 
				{
				s=ss;
				bs=2;
				}
			}
							
		return ::StrValInt(s,bs);
		};     

	METHOD(XU_VAL,unsigned, return an unsigned)
	StrValUns(PTR_TO(U_CHR)s)
		{
		PTR_TO(U_CHR) ss;
		int bs=10;				
		int v=0;		
		if(!s) return v;
     
		ss=IsHex();				
		if(ss) 
			{
			s=ss;
			bs=16;
			}
		else {
			ss=IsBin();
			if(ss) 
				{
				s=ss;
				bs=2;
				}
			}
							
		return ::StrValUns(s,bs);
		};     


	METHOD(XU_VAL,FLT,Return s as Flt)
	StrValFlt(PTR_TO(U_CHR)s)
		{		
		double v=0;
		unsigned u=0;
		if(!s) return FLT(v);

		if(IsHex() || IsBin())
			{
			u=StrValUns(s);
			return FLT(u);
			}
     
		return ::StrValFlt(s);
		}     

	METHOD(XU_VAL,FLT64,Return s as Flt64)
	StrValDbl(PTR_TO(U_CHR)s)
		{		
		double v=0;
		unsigned u=0;
		if(!s) return FLT(v);

		if(IsHex() || IsBin())
			{
			u=StrValUns(s);
			return FLT64(u);
			}
     
		return ::StrValDbl(s);
		}     



