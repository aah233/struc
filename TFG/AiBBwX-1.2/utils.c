#include "utils.h"

/*---------------------------------------------------------------------------*/
FILE * OpenFile (char *name, char const *mode)
{
 FILE *f;

 f=fopen(name,mode);
 if (f==NULL)
    {
     fprintf(stderr,"Can not open the file %s\n",name);
     exit(1);
    }
 return f;
}

/*---------------------------------------------------------------------------*/
void CloseFile (FILE *f)
{
  if (fclose(f))
      fprintf(stderr,"Unable to close file.\n");
}

/*---------------------------------------------------------------------------*/
ULINT CountSetBits(ULINT n)
{
 ULINT Count=0;
 while (n)
       {
        n &= (n-1);
        Count++;
       }
 return Count;
}

/*---------------------------------------------------------------------------*/
void PrintVR (FILE * FOut, PREAL vr, INT NDim)
{
 for (int i=0;i<NDim;i++)
     fprintf(FOut,"%g ",vr[i]);
 fprintf(FOut,"\n");
}

/*---------------------------------------------------------------------------*/
void PrintMR (FILE * FOut, PPREAL ppA, INT Rows, INT Cols)
{
 for (int i=0;i<Rows;i++)
	 PrintVR (FOut,ppA[i],Cols);
}


/*---------------------------------------------------------------------------*/
void PrintVINT (FILE * FOut, PINT vr, INT NDim)
{
 int i;

 for (i=0;i<NDim;i++)
     fprintf(FOut,"%d,",vr[i]);
 fprintf(FOut,"\n");    
}

/*---------------------------------------------------------------------------*/
/*void PrintVBOOL (FILE * FOut, PBOOL pB, INT NDim)*/
/*{*/
/* int i;*/
/* fprintf(FOut,"[");*/
/* for (i=0;i<NDim;i++)*/
/*     {*/
/*      if (pB[i]==True)*/
/*         fprintf(FOut,"T");*/
/*      if (pB[i]==False)*/
/*         fprintf(FOut,"F");  */
/*      if (pB[i]==NegGrad)*/
/*         fprintf(FOut,"N"); */
/*      if (pB[i]==PosGrad)*/
/*         fprintf(FOut,"P");    */
/*      if (pB[i]==ZeroInGrad)*/
/*         fprintf(FOut,"Z");      */
/*     }    */
/* fprintf(FOut,"]\n");    */
/*}*/

/*---------------------------------------------------------------------------*/
void CopyVR (PREAL PD, PREAL PO, INT NDim)
{
 INT i;
 
 for (i=0;i<NDim;i++) 
     PD[i]=PO[i];
}


/*---------------------------------------------------------------------------*/
void CopyVINT (PINT PD, PINT PO, INT NDim)
{
 INT i;
 
 for (i=0;i<NDim;i++) 
     PD[i]=PO[i];
}

/*---------------------------------------------------------------------------*/
void SwapPInt (int * x, int * y)
{
 int Temp;
 Temp=*x;
 *x=*y;
 *y=Temp;
}

/*---------------------------------------------------------------------------*/
void CopyVBOOL (PBOOL PD, PBOOL PO, INT NDim)
{
 INT i;
 
 for (i=0;i<NDim;i++) 
     PD[i]=PO[i];
}

/*---------------------------------------------------------------------------*/
BOOL IsFalseVBOOL(PBOOL pB, INT NDim)
{
 INT i;
 for (i=0;i<NDim;i++)
     if (pB[i]==True)
        return False;
 return True;       
}

/*---------------------------------------------------------------------------*/
COMPARE CompareVR (PREAL VR1, PREAL VR2, const INT NDim)
{
 INT i;
 COMPARE Result;
 
 Result=Equal;
 
 for (i=0;i<NDim;i++)
     if (VR1[i]!=VR2[i])
        {
	 if (VR1[i]<VR2[i])
	     Result=Smaller;
	 else
	     Result=Greater;
	 break;
	}
     
 return Result;
}

/*---------------------------------------------------------------------------*/
REAL RandomInt(INT n)
{
 return ((int)(drand48()*(REAL)n));
}

/*---------------------------------------------------------------------------*/
VOID DrawWait(const int NWin)
{
 printf("%d\n",NWin);
 printf("Wait\n");
}
/*---------------------------------------------------------------------------*/
//Value in [Lowerbound, Lowerbound+Width] is put in [0,1] interval.
double Normalice( double Value, double Lowerbound, double Width)
{
 return ( (Value-Lowerbound) / Width);
}

/*---------------------------------------------------------------------------*/
REAL XInWindow(PREAL pX, const itvV & XLim, const INT WWidth)
{
 double Pos;
 Pos = Normalice(pX[0],XLim(0).lower(),width(XLim(0)));
 //Enlarge to canvas x's width
 return Pos*WWidth;
}
//---------------------------------------------------------------------------
REAL YInWindow(PREAL pX, const itvV & XLim, const INT WWidth)
{
 double Pos;
 Pos = Normalice(pX[1],XLim(1).lower(),width(XLim(1)));
 //Change pos in [0,1] to [1,0]
 Pos*=-1.0;
 Pos+= 1.0;
 //Enlarge to canvas y's width
 return Pos*WWidth;
}

/*---------------------------------------------------------------------------*/
VOID DrawPoint(PREAL pX,ConstData CtD, const int NPoint, PCHARCt color)
{
 printf("%d\n",CtD.NWin);
 printf("DrawPoint\n");

 printf("%f\n",XInWindow(pX,CtD.XLim,CtD.WWidth));
 printf("%f\n",YInWindow(pX,CtD.XLim,CtD.WWidth));
 
 printf("%s\n",color);

 printf("%d\n",NPoint);
 
 fflush(stdout);
}

/*---------------------------------------------------------------------------*/
VOID DrawColorPoint(const BOOL Draw, const INT NWin, const INT NPoint, 
					PCHARCt color)
{
 printf("%d\n",NWin);
 printf("SetColorPoint\n");
 printf("%d\n",NPoint);
 printf("%s\n",color);
 //if (Draw>1)
 //   DrawWait(NWin);
}

/*---------------------------------------------------------------------------*/
VOID DelPoint(const INT NWin, const INT NPoint)
{
 printf("%d\n",NWin);
 printf("DelPoint\n");
 printf("%d\n",NPoint); 
}

/*---------------------------------------------------------------------------*/
VOID DrawPolygon (PPREAL ppPoints, int NPoints, int NDim, int NPoly, 
				  ConstData CtD, PCHARCt color)
{
 if (NDim!=2)
    {
     fprintf(stderr,"DrawPolygon:NDin=%d, != 2.\n",NDim);
     exit(1);
    }
 printf("%d\n",CtD.NWin);
 printf("DrawLinePoly\n");
 printf("%d\n",NPoints);
 for (int i=0;i<NPoints;i++)
	 {
	  printf("%f\n",XInWindow(ppPoints[i],CtD.XLim,CtD.WWidth));
	  printf("%f\n",YInWindow(ppPoints[i],CtD.XLim,CtD.WWidth));
	 }
  printf("%s\n",color);
  printf("%d\n",NPoly);
  fflush(stdout);
}

/*---------------------------------------------------------------------------*/
INT Fact(INT n)
{
 INT i;
 INT Result =1;
 
 for (i=2;i<=n;i++)
     Result*=i;
 return Result;    
}

/*---------------------------------------------------------------------------*/
PPINT CombNoRep(INT n, INT k, PINT pNComb)
{
 INT NComb,nk;
 INT i,j;
 PPINT S;
 
 NComb=0;
 nk=n-k;
 
 (*pNComb)=Fact(n)/(Fact(k)*Fact(nk));
  
 S=(PPINT) GetMem2D(*pNComb,k,(SIZE)sizeof(INT),"CombNoRep");
 
/* fprintf(stderr,"Convinaciones=%d.\n",Fact(n)/(Fact(k)*Fact(nk)) );
 fprintf(stderr,"Fact(%d)=%20d, Fact(%d)=%20d, Fact(%d)=%20d.\n",
                n,Fact(n),k,Fact(k),nk,Fact(nk));
 fprintf(stderr,"n=%d, k=%d.\n", n, k);
 fprintf(stderr,"NComb=%d, pNComb=%d.\n",NComb, (*pNComb));
*/
 
 for (i=0;i<k;i++)
     S[NComb][i]=i;
 
 
 /*PrintVINT(stderr,S[NComb],k);*/ 
 while (S[NComb][0] < nk)
       {	
        NComb++;
	CopyVINT(S[NComb],S[NComb-1],k);    
	
        if (S[NComb][k-1]<n-1)
	    S[NComb][k-1]++;
	else
	   {
	    j=1;
	    while (S[NComb][k-1-j]==n-1-j)
	          j++;
	    S[NComb][k-1-j]++;
	    for (i=k-j;i<k;i++) 
	       S[NComb][i]=S[NComb][i-1]+1;
	   } 
/*	fprintf(stderr,"NComb=%d = ",NComb);
	PrintVINT(stderr,S[NComb],k);       
*/	
       }
 return S;      
}


/*---------------------------------------------------------------------------*/
INT CombN2ToIndex(INT N, INT x, INT y)
{
 int Sum[17]={0,1,3,6,10,15,21,28,36,45,55,66,78,91,105,120,136};
 /*Sum(n)=n*(n-1)/2+n*/

 INT Tmp;
 if (x>y)
    {
     Tmp=x;
     x=y;
     y=Tmp;
    }

 return x*N-Sum[x]+(y-x)-1;
}

/*---------------------------------------------------------------------------*/
VOID IndexToCombN2(INT N, INT Index, PINT px, PINT py)
{
 int Sum[17]={0,1,3,6,10,15,21,28,36,45,55,66,78,91,105,120,136};
 /*Sum(n)=n*(n-1)/2+n*/
 INT x=N-2;
 INT y;
  
 while ( x*N - Sum[x] > Index )
       x--;
       
 y=x+Index+1-(x*N - Sum[x]);
 
 *px=x;
 *py=y;
}

/*---------------------------------------------------------------------------*/
REAL DistPoints(PREAL p1, PREAL p2, INT NDim)
{
 INT i;
 REAL Distance,Temp;
 
 Temp=p1[0] - p2[0];
 Distance=Temp*Temp;
 for (i=1;i<NDim;i++)
     {
      Temp      = p1[i] - p2[i];
      Distance += Temp*Temp;
     } 
     
 return sqrt(Distance);     
}

/*---------------------------------------------------------------------------*/
bool EQ(REAL a, REAL b)
{
 if (a <= b && b-a < REALPrec)
    return true;
    
 if (a >= b && a-b < REALPrec)
    return true;

 return false;
}

/*---------------------------------------------------------------------------*/
bool LT(REAL a, REAL b)
{
 if ( EQ(a,b) )
    return False;
    
 if ( a < b )
    return true;
    
 return false;
}

/*---------------------------------------------------------------------------*/
bool GT(REAL a, REAL b)
{
 if ( EQ(a,b) )
    return false;
    
 if ( a > b )
    return true;
    
 return False;
}

/*---------------------------------------------------------------------------*/
bool LE(REAL a, REAL b)
{
 if ( EQ(a,b) || a < b)
    return true;

 return false;
}

/*---------------------------------------------------------------------------*/
bool GE(REAL a, REAL b)
{
 if ( EQ(a,b) || a > b)
    return true;

 return false;
}

/*---------------------------------------------------------------------------*/
void MiddlePoint (PREAL pA, PREAL pB, PREAL pMiddle, INT NDim)
{
 int i;

 for (i=0;i<NDim;i++)
     {
      if (pA[i] < pB[i])
          pMiddle[i] = pA[i] + ( pB[i] - pA[i] ) / 2.0;
      else
          pMiddle[i] = pB[i] + ( pA[i] - pB[i] ) / 2.0;   
     } 
}

/*---------------------------------------------------------------------------*/
void SwapR (REAL &A, REAL &B)
{
 REAL t;
 
 t=A;
 A=B;
 B=t;
}


/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
