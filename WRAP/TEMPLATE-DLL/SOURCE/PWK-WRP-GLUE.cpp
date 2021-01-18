// =======================================================================
// PWK_GLUE
// =======================================================================
#include "PWK-WRP-CORE-01.hpp"

PTR_TO(WRP_TBL) wrpTbl = NULL;			// Main data table
WRPPWK_TCB	PWK_TRIGGER = NULL;			// POWER-KI Trigger CallBack
WRPPWK_CBS	PWK_CBS = NULL;			// POWER-KI Services CallBack	

LIST_OBJ_MNG<lisParElm> lisPar;
LIST_OBJ_MNG<lisParElm> lisRes;


// =======================================================================
extern "C" NONE WRP_CALL_PWK_TRIG(ANY parTrg, PTR_TO(U_CHR)parLis, int mode)
	{
	(PWK_TRIGGER)(parTrg, parLis, mode); \
	}

// =======================================================================
FUNCTION(NONE, Send a text to POWER-KI chat)
WRP_TRACE(PTR_TO(U_CHR)t)
	{
	int l= StrLen(t) + 100;
	PTR_TO(U_CHR)tx;

	tx=new U_CHR[l];
	StrFormat(tx,l,L"Chatput(\"%s\")",t);
	WRP_PWK_EXEC(tx);
	delete tx;
	};


FUNCTION(NONE, Register Parameter)
PWK_WRP_PAR_REG(PTR_TO(U_CHR)id, PTR_TO(U_CHR)typ, int szt)
	{
	PTR_TO(lisParElm) pe=new lisParElm;
	pe->p.par=StrDup(id);
	pe->p.typ=StrDup(typ);
	pe->p.siz=szt;	
	lisPar.Add(pe);
	}

FUNCTION(NONE, Register Return res)
PWK_WRP_RES_REG(PTR_TO(U_CHR)id, PTR_TO(U_CHR)typ, int szt)
	{
	PTR_TO(lisParElm) pe=new lisParElm;
	pe->p.par=StrDup(id);
	pe->p.typ=StrDup(typ);
	pe->p.siz=szt;	
	lisRes.Add(pe);
	}

FUNCTION(NONE, Set Func Par)
PWK_WRP_PAR_SET(int idx)
	{
	PTR_TO(WRP_PAR)par;
	PTR_TO(lisParElm) pe;
	int i, in;
	int szt=0;
	int off=sizeof(ANY);
	int sz=0;

	in=wrpTbl->pf[idx].np= lisPar.GetNum();

	if(!in)
		{
		wrpTbl->pf[idx].par = NULL;		
		wrpTbl->pf[idx].psz = 0;				
		}
	else {	
		par=wrpTbl->pf[idx].par = new WRP_PAR[in];
	
		for(i=0; i<in; i++)
			{
			pe=lisPar.Get();
			par[i].off=off;
			par[i].par= pe->p.par;
			par[i].siz=pe->p.siz;
			par[i].typ = pe->p.typ;
			off+= par->siz;
			sz += par->siz;
			delete pe;
			}	
		wrpTbl->pf[idx].psz=sz;
		lisPar.Clean();
		}

	in=wrpTbl->pf[idx].nr= lisRes.GetNum();

	if(!in)
		{
		wrpTbl->pf[idx].res = NULL;		
		wrpTbl->pf[idx].rsz = 0;
		}
	else {			
		par=wrpTbl->pf[idx].res = new WRP_PAR[in];
		sz=0;
		for(i=0; i<in; i++)
			{
			pe=lisRes.Get();
			par[i].off=off;
			par[i].par= pe->p.par;
			par[i].siz=pe->p.siz;
			par[i].typ = pe->p.typ;			
			off+= par->siz;
			sz+= par->siz;
			delete pe;
			}	
		wrpTbl->pf[idx].rsz=sz;
		lisRes.Clean();
		}
	}

FUNCTION(PTR_TO(WRP_TBL), Add function to init)
PWK_WRP_Init(WRPPWK_EXC fnc, ...)
	{
	int cnt=0;	
	WRPPWK_EXC fbeg=fnc;

	va_list v1;		
	va_start(v1,fnc);
	
	while(fnc!=NULL)
		{
		cnt++;
		fnc=va_arg(v1, WRPPWK_EXC);
		}
		
	wrpTbl = new WRP_TBL;

	wrpTbl->nf = cnt;
	wrpTbl->pf = new WRP_FNC[cnt];	

	fnc = fbeg;
	va_start(v1, fnc);

	cnt=0;
	while(fnc!=NULL)
		{
		wrpTbl->pf[cnt].ptr = fnc;
		(fnc)(NULL,(cnt+1)*-1,NULL, NULL);
		PWK_WRP_PAR_SET(cnt);

		cnt++;
		fnc=va_arg(v1, WRPPWK_EXC);
		}
	va_end(v1);

	return wrpTbl;
	}


//------------------------------------------------------
ANY WRP_GETRET(PTR_TO(U_CHR)id, ANY buf, int szt, PTR_TO(U_CHR) typ, const PTR_TO(U_CHR) fun, const PTR_TO(U_CHR)as, int init, PTR_TO(U_CHR*) asBuf)
	{
	if (init)
		{	
		PWK_WRP_RES_REG(id, typ, szt); 
		return NULL;
		}
	
	int i,in, y, yn;
	PTR_TO(WRP_PAR)par;

	in= wrpTbl->nf;

	for(i=0; i<in; i++)
		{
		if(!_wcsicmp(fun,wrpTbl->pf[i].fnc))
			{
			par = wrpTbl->pf[i].res;
			yn= wrpTbl->pf[i].nr;

			for(y=0; y<yn; y++)
				{
				if(!_wcsicmp(id, par[y].par))
					{								
					if(asBuf)
						{
						PTR_TO(U_CHR)t= asBuf[y];
						asBuf[y] = StrDup(as);
						if (t)delete t;						
						}									
					return &((U8*)buf)[par[y].off];
					}
				}			
			}
		}
	return NULL;
	}

//------------------------------------------------------

PTR_TO(U_CHR) WRP_GETPAR_AS(PTR_TO(U_CHR)id,const PTR_TO(U_CHR) fun, PTR_TO(U_CHR*) asBuf)
	{
	int i,in, y, yn;
	PTR_TO(WRP_PAR)par;

	if(!asBuf) return NULL;

	in= wrpTbl->nf;

	for(i=0; i<in; i++)
		{
		if(!_wcsicmp(fun,wrpTbl->pf[i].fnc))
			{
			par = wrpTbl->pf[i].res;
			yn = wrpTbl->pf[i].nr;

			for(y=0; y<yn; y++)
				{
				if(!_wcsicmp(id, par[y].par))
					{									
					return asBuf[y];
					}
				}			
			}
		}

	return NULL;
	}


int WRP_GETPAR_IDX(PTR_TO(U_CHR)id,const PTR_TO(U_CHR) fun)
	{
	int i,in, y, yn;
	PTR_TO(WRP_PAR)par;

	in= wrpTbl->nf;

	for(i=0; i<in; i++)
		{
		if(!_wcsicmp(fun,wrpTbl->pf[i].fnc))
			{
			par = wrpTbl->pf[i].par;
			yn= wrpTbl->pf[i].np;

			for(y=0; y<yn; y++)
				{
				if(!_wcsicmp(id, par[y].par))
					{
					return y;
					}
				}			
			}
		}

	return -1;
	}

ANY WRP_GETPAR(PTR_TO(U_CHR)id, ANY buf, int szt, const PTR_TO(U_CHR) fun)
	{
	int i,in, y, yn;
	PTR_TO(WRP_PAR)par;

	in= wrpTbl->nf;

	for(i=0; i<in; i++)
		{
		if(!_wcsicmp(fun,wrpTbl->pf[i].fnc))
			{
			par = wrpTbl->pf[i].par;
			yn= wrpTbl->pf[i].np;

			for(y=0; y<yn; y++)
				{
				if(!_wcsicmp(id, par[y].par))
					{
					return &((U8*)buf)[par[y].off];
					}
				}			
			}
		}
	return NULL;
	}

ANY WRP_SET_DCLPAR(int pn, PTR_TO(U_CHR)nam, PTR_TO(U_CHR)typ, int tySz, ANY parBuf, PTR_TO(U_CHR)FUNCTIONW)
	{
	if(pn< 0)
		{		
		PWK_WRP_PAR_REG((U_CHR*)nam, (U_CHR*)typ, tySz);
		return NULL;
		}
	return WRP_GETPAR(nam, parBuf, tySz, FUNCTIONW);		
	}

// -----------------------------------------------------------------------
FUNCTION(PTR_TO(U_CHR), Build an AS return signature e.g. for BUF size)
WRP_RES_PAY(const PTR_TO(U_CHR)fxp,unsigned pay)
	{
	PTR_TO(U_CHR) b=new U_CHR[50];

	wsprintfW(b,L"%s:%d",fxp,pay);
	return b;
	}

// -----------------------------------------------------------------------
FUNCTION(PTR_TO(U_CHR), Build an AS return signature e.g. for BUF size)
WRP_RES_TYP(const PTR_TO(U_CHR)fxp, PTR_TO(U_CHR) typ)
	{
	PTR_TO(U_CHR) b=new U_CHR[50];

	wsprintfW(b,L"%s:%s",fxp,typ);
	return b;
	}




