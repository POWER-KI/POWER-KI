// ======================  ===================================================
//         XPLAB           Xplab s.a.s. - viale Sant Eufemia, 39
// Research in Automation                 25135 Brescia - Italy
//     www.xplab.net                      Tel/Fax +39 030 2350035/2350035
//   *** RESERVED ***
// ======================  ===================================================
// File name            :  XU-LISTE.h
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
// List Management
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

// ============================================================================
// MACRO DEFINITION
// ============================================================================

#define ROSSO	
#define VERDE	


// ****************************************************************************
// *********************************  C O D E  ********************************
// ****************************************************************************



// ============================================================================
// DNODO - Double link Element
// ============================================================================

//USE: CLASS(pippo, Per prova):public DNODO 

CLASS(DNODO, Basic object for list)
     {
     PTR_TO(DNODO) prv;                // Previus
     PTR_TO(DNODO) nxt;                // Next

     public:

	D_BUILDER(DNODO)()
	     {
          prv=NULL;
          nxt=NULL;
          };

     D_METHOD(DNODO, void, Reset pointer to linked object)
     Clear()
          {
          prv=NULL;
          nxt=NULL;
          };

     D_METHOD(DNODO, PTR_TO(DNODO), Return the pointer to previous linked element)
     Prv()
          {
          return prv;
          };

     D_METHOD(DNODO, PTR_TO(DNODO), Return the pointer to next linked element)
     Nxt()
          {
          return nxt;
          };

     D_METHOD(DNODO, void, Add a new element before this )
     AddBef( PTR_TO(DNODO) nd)
          {
          nd->prv=prv;
          nd->nxt=this;

          if(prv)prv->nxt=nd;
          prv=nd;
          };

     D_METHOD(DNODO, void, Add a new element after this)
     AddAft( PTR_TO(DNODO) nd)
          {
          nd->prv=this;
          nd->nxt=nxt;

          if(nxt)nxt->prv=nd;
          nxt=nd;
          };

     D_METHOD(DNODO, BOOL, Return true if one link is not zero)
     IsLinked()
          {
          if(prv || nxt) return TRUE;
          return FALSE;
          };

     D_METHOD(DNODO,void, Remove the element from the list)
     Rem()
          {
          if(prv)prv->nxt=nxt;
          if(nxt)nxt->prv=prv;

          prv=nxt=NULL;
          };

     D_DESTROYER(DNODO)
          {
          Rem();
          };
     };



// =================================================================================
// TEMPLATE OBJ MNG
// =================================================================================

// CLASS(pippo,Oggetto pippo):public DNODO
//USE: LIST_OBJ_MNG<pippo> listaPippo

TCLASS(LIST_OBJ_MNG, List Object manager)
     {
     DATAV(INT,      tot,      Number of class T Obj);

     PTR_TO(T)      fst;                // First Obj of the chain
     PTR_TO(T)      lst;                // Last  Obj of the chain	
	
     public:
		
     TBUILDER(LIST_OBJ_MNG)()
          {
          tot=0;
          fst=NULL;
          lst=NULL;          
          };

     TMETHOD(LIST_OBJ_MNG, PTR_TO(T), Add an object at the end of the chain)
     Put( PTR_TO(T) obj)
          {
          if(!obj) return obj;
          ROSSO;
          tot++;

          obj->DNODO::Clear();

          if(!fst)
               {
               fst=lst=obj;
               }
          else {
               lst->DNODO::AddAft( obj);
               lst=obj;
               }

          VERDE;

          return obj;
          };


     TMETHOD(LIST_OBJ_MNG, PTR_TO(T), Return the ptr to an object removed from the beg)
     Get()
          {
          PTR_TO(T) obj;

          if(!tot) return NULL;

          ROSSO;

          obj=fst;

          if(obj)Remove(obj);

          VERDE;
          return obj;
          }


     TMETHOD(LIST_OBJ_MNG, PTR_TO(T), Push in an ordered way starting from the beginning)
     OrdPush( PTR_TO(T) obj, INT( * cmp)(ANY,ANY))
          {
          PTR_TO(T) o;

          NOTE( a compare function must be provided)

          if(!obj || !cmp ) return obj;

          ROSSO;

          if(!fst)
               {
               Add(obj);
               VERDE;
               return obj;
               }

          for(o=Fst(); o; o=Nxt(o))
               {
               if( (REF_BY(cmp))(o,obj) <=0)
                    {
                    InsBef(o,obj);
                    VERDE;
                    return obj;
                    }
               }
          Add(obj);
          VERDE;
          return obj;
          }

     TMETHOD(LIST_OBJ_MNG, PTR_TO(T), Push in an ordered way starting from the end)
     OrdAdd( PTR_TO(T) obj, INT( * cmp)(ANY,ANY))
          {
          PTR_TO(T) o;

          NOTE( a compare function must be provided)

          if(!obj || !cmp ) return obj;

          ROSSO;

          if(!fst)
               {
               Add(obj);
               VERDE;
               return obj;
               }

          for(o=Lst(); o; o=Prv(o))
               {
               if( (REF_BY(cmp))(o,obj) >=0)
                    {
                    InsAft(o,obj);
                    VERDE;
                    return obj;
                    }
               }
          Push(obj);
          VERDE;
          return obj;
          }



     TMETHOD(LIST_OBJ_MNG, PTR_TO(T), Add an object to the end)
     Add( PTR_TO(T) obj)
          {
          if(!obj) return obj;

          ROSSO;
          tot++;

          obj->DNODO::Clear();

          if(!fst)
               {
               fst=lst=obj;
               }
          else {
               lst->DNODO::AddAft( obj);
               lst=obj;
               }

          VERDE;

          return obj;
          };

     TMETHOD(LIST_OBJ_MNG, PTR_TO(T), Remove an Obj from the chain)
     Remove( PTR_TO(T) obj)
          {
          ROSSO;
          if(!tot || !obj )
               {
               VERDE;
               return NULL; // era obj
               }
	
		if(!obj->DNODO::IsLinked() && obj != fst)
			{
               VERDE;
               return obj; 
			}

          if( fst==obj)
               {
               fst=(PTR_TO(T))(obj->DNODO::Nxt());
               }

          if(lst==obj)
               {
               lst=(PTR_TO(T))(obj->DNODO::Prv());
               }
          
          obj->DNODO::Rem();
		tot--;

          VERDE;
          return obj;
          }

     TMETHOD(LIST_OBJ_MNG, PTR_TO(T), Push like a stack from beg)
     Push(PTR_TO(T) obj)
          {
          if(!obj) return obj;
          ROSSO;
          tot++;

          obj->DNODO::Clear();

          if(!fst)
               {
               fst=lst=obj;
               }
          else {
               fst->DNODO::AddBef( obj);
               fst=obj;
               }

          VERDE;

          return obj;
          };

     TMETHOD(LIST_OBJ_MNG, PTR_TO(T), Pop from like a stack from beg)
     Pop()
          {
          PTR_TO(T) obj;

          if(!tot) return NULL;

          ROSSO;

          obj=fst;

          if(obj)Remove(obj);

          VERDE;
          return obj;
          }


     TMETHOD(LIST_OBJ_MNG, PTR_TO(T), Add a nob before obj)
     InsBef(PTR_TO(T) obj, PTR_TO(T) nob)
          {
          if(!obj || ! nob) return nob;
          ROSSO;
          tot++;

          nob->DNODO::Clear();
          obj->DNODO::AddBef(nob);

          if(fst==obj)
               {
               fst=nob;
               }

          VERDE;

          return nob;
          };

     TMETHOD(LIST_OBJ_MNG, PTR_TO(T), Add nob after obj)
     InsAft(PTR_TO(T) obj, PTR_TO(T) nob)
          {
          if(!obj || ! nob) return nob;
          ROSSO;
          tot++;

          nob->DNODO::Clear();
          obj->DNODO::AddAft(nob);

          if(lst==obj)
               {
               lst=nob;
               }

          VERDE;

          return nob;
          };


     TMETHOD(LIST_OBJ_MNG, PTR_TO(T), return the prt to the last object)
     GetLst()
          {
          return lst;
          };


     TMETHOD(LIST_OBJ_MNG, PTR_TO(T), return the ptr to the first object)
     GetFst()
          {
          return fst;
          };

     TMETHOD(LIST_OBJ_MNG, PTR_TO(T), return the ptr to the next object)
     GetNxt(PTR_TO(T) obj)
          {          
          return Nxt(obj);
          };


     TMETHOD(LIST_OBJ_MNG, PTR_TO(T), return the ptr to the previous object)
     GetPrv(PTR_TO(T) obj)
          {          
          return Prv(obj);
          };

     TMETHOD(LIST_OBJ_MNG, PTR_TO(T), return the prt to the last object)
     Lst()
          {
          return lst;
          };


     TMETHOD(LIST_OBJ_MNG, PTR_TO(T), return the ptr to the first object)
     Fst()
          {
          return fst;
          };

     TMETHOD(LIST_OBJ_MNG, PTR_TO(T), return the ptr to the next object)
     Nxt(PTR_TO(T) obj)
          {		
          if(!obj) return NULL;
		ROSSO;
          obj= (PTR_TO(T))(obj->DNODO::Nxt());
		VERDE;
		return obj;
          };


     TMETHOD(LIST_OBJ_MNG, PTR_TO(T), return the ptr to the previous object)
     Prv(PTR_TO(T) obj)
          {		
          if(!obj) return NULL;
		ROSSO;
          obj= (PTR_TO(T))(obj->DNODO::Prv());
		VERDE;
		return obj;
          };


     TMETHOD(LIST_OBJ_MNG, INT, Return the number of object in the chain)
     GetNum()
          {
          INT t;

          ROSSO;
          t=tot;
          VERDE;

          return t;
          };

     TMETHOD(LIST_OBJ_MNG, NONE, Destroj all object)
     Clean()
          {
          PTR_TO(T) obj;
          ROSSO;
          if(tot)
               {
               while( fst)
                    {
				obj=Remove(fst);         
                    if(obj)delete obj;
                    }
               }
          VERDE;
          };

     TDESTROYER(LIST_OBJ_MNG)
          {
          NOTE( Delete the manager and all the object)
          Clean();
          };
     };


// =================================================================================
// TEMPLATE OBJ STK
// =================================================================================

//USE: STK_OBJ<pippo> stkPippo

TCLASS(STK_OBJ, Stack for Object )
     {
     PTR_TO(PTR_TO(T))		tbl;
     I32					usd;
     I32					num;
	I32					crs;

     public:

     TBUILDER(STK_OBJ)(I32 m=50)
          {		
		crs=0;
          usd=0;
          num=m;
		tbl=new PTR_TO(T) [num];
          };

	TDESTROYER(STK_OBJ)
		{
		Clean();
		delete tbl;
		};

	TMETHOD(STK_OBJ, NONE, extend)
	Extend(int n=0)
		{
		int i;
		if(n==0 || n<num) n=num*2;
		
		PTR_TO(PTR_TO(T))	t= new PTR_TO(T)[n];

		if(usd)memcpy(t,tbl,sizeof(T*)*usd);

		delete tbl;
		tbl=t;
		num=n;
		};

     TMETHOD(STK_OBJ, PTR_TO(T), Push like a stack from end)
     Push(PTR_TO(T) obj)
          {
		tbl[usd]=obj;
		usd++;
		if(usd>=num ) Extend();
		return obj;				
          };

     TMETHOD(STK_OBJ, PTR_TO(T), pop from the end)
     Pop()
          {
		PTR_TO(T) obj;

		if(!usd)return NULL;
		usd--;
		obj=tbl[usd];
		return obj;				
          };

     TMETHOD(STK_OBJ, PTR_TO(T), Get the last inserted)
     Fst()
		{		
		if (!usd)return NULL;
		crs=usd-1;
		return tbl[crs];
		};

     TMETHOD(STK_OBJ, PTR_TO(T), Get the First inserted)
     Lst()
		{		
		if (!usd)return NULL;		
		return tbl[0];
		};

     TMETHOD(STK_OBJ, PTR_TO(T), Get the next)
     Nxt()
		{
		PTR_TO(T) obj;
		if (!usd || !crs)return NULL;
		crs--;
		return tbl[crs];
		};
	
	TMETHOD(STK_OBJ, NONE, Reverse the list)
	Reverse()
		{
		int i;
		PTR_TO(T) obj;
		if (!usd)return;

		PTR_TO(PTR_TO(T))t = new PTR_TO(T)[num];		
		
		for(i=0; i<usd; i++)
			{
			t[i]=tbl[usd-1-i];			
			}
		delete tbl;
		tbl=t;		
		};

	TMETHOD(STK_OBJ, PTR_TO(T), get from last)
     Remove(int i)
		{		
		PTR_TO(T) obj;
		i=usd-i;
		if (!usd || i>=usd || i<0)return NULL;
		obj=tbl[i];

		usd--;
		if(usd>1 && i<usd) memcpy(&tbl[i],&tbl[i+1], sizeof(T*)* (usd-i));
	
		return obj;
		};

	TMETHOD(STK_OBJ, PTR_TO(T),Remove obj)
     Remove(PTR_TO(T)obj)
		{		
		int i;
		if(!usd) return NULL;

		for(i=0 ; i<usd; i++)
			{
			if(tbl[i] == obj)
				{
				usd--;
				if (usd>1 && i < usd) memcpy(&tbl[i], &tbl[i + 1], sizeof(T*)* (usd -i));

				return obj;
				}	
			}
	
		return obj;
		};

	TMETHOD(STK_OBJ, I32, Get the num)
     GetNum()
		{
		return usd;
		};
 

     TMETHOD(STK_OBJ, NONE, pop )
     Clean()
          {
		int i;
		PTR_TO(T) obj;
		if (!usd)return;
		
		for(i=0; i<usd; i++)
			{
			obj= tbl[i];
			if(obj)delete obj;
			}
		usd=0;	
          };

     };