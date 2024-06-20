/******************************************************************************
			btsimplex.c  - description
			----------------------
	begin		: August 2004
	copywirght	: (C) 2004 by L.G.Casado.
	
******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include "defines.h"
#include "getmem.h"
#include "iutils.hpp"
#include "vertex.hpp"
#include "Functions.hpp"  
#include "btvertex.h"
#include "simplex.hpp"
#include "listsimplex.h"
#include "InputOutput.hpp"
#include "btsimplex.h"


using namespace std;


/*---------------------------------------------------------------------------*/
PBTSNODE NewBTSNODE(PSIMPLEX pS)
{
 PBTSNODE pBTSNode;
 
 pBTSNode	   = (PBTSNODE)GetMem(1,sizeof(BTSNODE),"NewBTSNODE");
 pBTSNode->plS     = NewListS(pBTSNode->plS);
 InsertListS(pBTSNode->plS, pS);
 pBTSNode->Balance = EQUAL;
 pBTSNode->pleft   = NULL;
 pBTSNode->pright  = NULL;
 return pBTSNode;
}

/*---------------------------------------------------------------------------*/
PBTSNODE FreeBTSNode(PBTSNODE pBTSNode, ConstData & CtD,PBTV pbtv,
                     const BOOL Fill, PCHARCt Color)
{
 if (pBTSNode==NULL)
    {
     fprintf(stderr,"Trying to free a NULL BTSNODE pointer.\n");
     exit(1);
    }
 pBTSNode->plS=FreeListS(pBTSNode->plS,CtD,pbtv,Fill,Color);
 free((PVOID)pBTSNode);
 pBTSNode=NULL;
 return pBTSNode;   
}

/*----------------------------------------------------------------------------*/
/*Swap the nodes, but the structure of the BLTree does not change.            */
VOID SwapBTSNode(PBTSNODE pBTSNodeO, PBTSNODE pBTSNodeT)
{
 PLISTS plS;
 
 plS            = pBTSNodeO->plS;
 pBTSNodeO->plS = pBTSNodeT->plS;
 pBTSNodeT->plS = plS;
}

/*----------------------------------------------------------------------------*/
/*Swap the data and copy the Balance and pointers of the BTSNodes.            */
/*Node2 will be removed with data of node1 after exchange.                    */
/*----------------------------------------------------------------------------*/
VOID ExchangeNode(PBTSNODE node1, PBTSNODE node2)
{
 SwapBTSNode(node1,node2);
 node1->Balance = node2->Balance;
 node1->pleft   = node2->pleft;
 node1->pright  = node2->pright;

 node2->pleft   = NULL;
 node2->pright  = NULL;
} 

/*---------------------------------------------------------------------------*/
void PrintBTSSubTreeInOrder(FILE * FOut, PBTSNODE node, const INT NDim)
{
 if (node!=NULL)
    {
     PrintBTSSubTreeInOrder(FOut,node->pleft,  NDim);
     fprintf(FOut,"BTS(%d)->",node->Balance);
     //PrintListS (FOut,node->plS,NDim,MonTest);
     cerr << "SelectIndex=" <<  node->plS->pFirstLS->pS->F << endl;
     PrintBTSSubTreeInOrder(FOut,node->pright, NDim);
    }
  else
     fprintf(FOut,"BTS:N\n");
}

/*---------------------------------------------------------------------------*/
void NElemBTSSubTree(PBTSNODE node, int &NElem)
{
 if (node!=NULL)
    {
     NElem+=node->plS->NElem;
     NElemBTSSubTree(node->pleft,  NElem);
     NElemBTSSubTree(node->pright, NElem);
    }
}

/*---------------------------------------------------------------------------*/
//Traverses the AVL tree in Order to see if data is ordered 
void CheckBTSSubTreeOrder(PBTSNODE node, itv & PrevItv, BOOL & First)
{
 if (node!=NULL)
    {
     CheckBTSSubTreeOrder(node->pleft, PrevItv, First);
     if (First)
        {
         PrevItv=node->plS->pFirstLS->pS->F;
         //cerr << "First PrevItv=" << PrevItv << endl;
         First=False;
        }
     else
        {
         if (iLE(PrevItv,node->plS->pFirstLS->pS->F))
            {
             //cerr << "-----------------------" << endl;
             //cerr << "PrevItv=" << PrevItv << endl;
             //cerr << "CurrItv=" << node->plS->pFirstLS->pS->F << endl;
             PrevItv=(node->plS->pFirstLS->pS->F);
            } 
         else
            {
             cerr << "-----------------------" << endl;
             cerr << "PrevItv=" << PrevItv << endl;
             cerr << "CurrItv=" << node->plS->pFirstLS->pS->F << endl;
             exit(1);
            } 
         }              
     CheckBTSSubTreeOrder(node->pright, PrevItv, First);     
    }
}

/*---------------------------------------------------------------------------*/
void CheckBTSOrder(PBTS pbts)
{
 itv PrevItv;
 BOOL First=True;
 
 if ( pbts->pFirstBTSNode==NULL || 
     (pbts->pFirstBTSNode->pleft==NULL && pbts->pFirstBTSNode->pright==NULL))
    return;
 else    
    CheckBTSSubTreeOrder(pbts->pFirstBTSNode, PrevItv, First);     
}


/*---------------------------------------------------------------------------*/
void PrintBTSSubTree(FILE * FOut,PBTSNODE node, const INT NDim)
{
 if (node!=NULL)
    {
     fprintf(FOut,"BTS(%d)->",node->Balance);
     //PrintListS (FOut,node->plS,NDim,MonTest);
     cerr << "SelectIndex=" <<  node->plS->pFirstLS->pS->F << endl;
     PrintBTSSubTree(FOut,node->pleft,  NDim);
     PrintBTSSubTree(FOut,node->pright, NDim);
    }
  else
     fprintf(FOut,"BTS:N\n");
}


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
PBTS NewBTS(PBTS pBTS)
{
 pBTS                 = (PBTS) GetMem(1,sizeof(BTS),"NewBTS");
 pBTS->NElem          = 0;
 pBTS->MaxNElem       = 0;	
 pBTS->pFirstBTSNode  = NULL;
 return pBTS;
}

/*----------------------------------------------------------------------------*/
void FreeBTSSubTree(PBTSNODE root, ConstData &CtD, PBTV pbtv,
                    const BOOL Fill, PCHARCt Color)
{
 if (root!=NULL)
    {
     //fprintf(stderr,"FreeBTSSubTree:Left,\n");
     FreeBTSSubTree(root->pleft,CtD,pbtv,Fill,Color);
     //fprintf(stderr,"FreeBTSSubTree:Right,\n");
     FreeBTSSubTree(root->pright,CtD,pbtv,Fill,Color);
     //fprintf(stderr,"FreeBTSSubTree: FreeBTSNode,\n");
     root=FreeBTSNode(root,CtD,pbtv,Fill,Color);     
    }
// else
//    fprintf(stderr,"FreeBTSSubTree: NULL,\n");   
}

/*----------------------------------------------------------------------------*/
PBTS FreeBTS(PBTS pbts, PBTV pbtv, ConstData CtD, const BOOL Fill, 
             PCHARCt Color)
{
 if (pbts!=NULL)
    {
    //////////////////
     FreeBTSSubTree(pbts->pFirstBTSNode,CtD,pbtv,Fill,Color);
     pbts->pFirstBTSNode=NULL;
     free((PVOID)pbts);
     pbts=NULL;
    }
 return NULL;   
}

/*---------------------------------------------------------------------------*/
int CountNElemBTS(PBTS pbts)
{
 int NElem=0;
 NElemBTSSubTree(pbts->pFirstBTSNode,NElem);     
 return NElem;
}

/*---------------------------------------------------------------------------*/
void PrintBTS(FILE * FOut, PBTS pbts, const INT NDim)
{
 fprintf(FOut,"\n---------------------PrintBTS-----------------------\n");
 if (pbts!=NULL)
    {
     fprintf(FOut,"BTS:Number of Elements     = %d\n",pbts->NElem);
     fprintf(FOut,"BTS:Max Number of Elements = %d\n",pbts->MaxNElem);
     PrintBTSSubTree(FOut,pbts->pFirstBTSNode,NDim);    
    }
  else
     fprintf(stderr,"BTS:N\n");
 fputs("---------------------End-PrintBTS-------------------\n",stderr);     
}


/*----------------------------------------------------------------------------*/
/*Rotate left a binary Tree                                                   */
/*----------------------------------------------------------------------------*/
PBTSNODE RotateTreeLeft(PBTSNODE root)
{
 PBTSNODE Temp;

 if (root==NULL)
    {
     fprintf(stderr,"BTSimplex::RotateTreeLeft :");;
     fprintf(stderr," Can not rotate to left an empty tree \n");
     exit(1);
    }
 else
    if (root->pright==NULL)
       {
        fprintf(stderr,"BTSimplex::RotateTreeLeft : Can not rotate to left\n");
        exit(1);
       }
    else
       {
        Temp         = root->pright;
        root->pright = Temp->pleft;
        Temp->pleft  = root;
        root=Temp;
       }
 return Temp;      
}
/*----------------------------------------------------------------------------*/
/*Rotate right a binary Tree                                                  */
/*----------------------------------------------------------------------------*/
PBTSNODE RotateTreeRight(PBTSNODE root)
{
 PBTSNODE Temp;
 
 if (root==NULL)
    {
     fprintf(stderr,"BTSimplex::RotateTreeRight :");
     fprintf(stderr," Can not rotate to right an empty tree \n");
     exit(1);
    }
 else
    if (root->pleft==NULL)
       {
        fprintf(stderr,"BTSimplex::RotateTreeRight:Can not rotate to right\n");
        exit(1);
       }
    else
       {
        Temp         = root->pleft;
        root->pleft  = Temp->pright;
        Temp->pright = root;
        root=Temp;
       }
 return Temp;      
}

/*---------------------------------------------------------------------------*/
/*Insert in the left branch maintaining the global balance. Taller noticed if*/
/*the insertion has increased the heigh or not. So the balance factors can be*/
/*changed appropiately and rotations may be done. Taller has efects only as  */
/*return value. We initiate it to false.                                     */
/*---------------------------------------------------------------------------*/
PBTSNODE LeftInsertTreeBalance(PBTSNODE root, PBOOL ptaller)
{
 PBTSNODE Left, LeftRight;

 Left=root->pleft;
 switch (Left->Balance)
        {
         case LEFT:
              root->Balance=EQUAL;
              Left->Balance=EQUAL;
              root=RotateTreeRight(root);
              *ptaller=False;
              break;
         case EQUAL:
              fprintf(stderr,"BTSimplex:LeftInsertTreeBalance :");
	      fprintf(stderr," The tree is already balanced\n");
              exit(1);
              break;
         case RIGHT:
              LeftRight=Left->pright;
              switch (LeftRight->Balance)
                     {
                      case LEFT:
                           root->Balance=RIGHT;
                           Left->Balance=EQUAL;
                           break;
                      case EQUAL:
                           root->Balance=EQUAL;
                           Left->Balance=EQUAL;
                           break;
                      case RIGHT:
                           root->Balance=EQUAL;
                           Left->Balance=LEFT;
                           break;
                     }
              LeftRight->Balance=EQUAL;
              root->pleft=RotateTreeLeft(root->pleft);
              root=RotateTreeRight(root);
              *ptaller=False;
              break;
        }
 return root;	
}


/*---------------------------------------------------------------------------*/
/*Analogous to previous one but on the right.                                */
/*---------------------------------------------------------------------------*/
PBTSNODE RightInsertTreeBalance(PBTSNODE root, PBOOL ptaller)
{
 PBTSNODE Right, RightLeft;

 Right=root->pright;
 switch (Right->Balance)
        {
         case LEFT:
              RightLeft=Right->pleft;
              switch (RightLeft->Balance)
                     {
                      case LEFT:
                           root->Balance=EQUAL;
                           Right->Balance=RIGHT;
                           break;
                      case EQUAL:
                           root->Balance=EQUAL;
                           Right->Balance=EQUAL;
                           break;
                      case RIGHT:
                           root->Balance=LEFT;
                           Right->Balance=EQUAL;
                           break;
                     }
              RightLeft->Balance=EQUAL;
              root->pright=RotateTreeRight(root->pright);
              root=RotateTreeLeft(root);
              *ptaller=False;
              break;
         case EQUAL:
              fprintf(stderr,"BTSimplex:RightInsertTreeBalance: ");
	      fprintf(stderr,"The tree is already balanced\n");
              exit(1);
              break;
         case RIGHT:
              root->Balance=EQUAL;
              Right->Balance=EQUAL;
              root=RotateTreeLeft(root);
              *ptaller=False;
              break;
        }
 return root;	
}


/*---------------------------------------------------------------------------*/
/*Do the actual insertion in the BTSimplex.                                  */
/*---------------------------------------------------------------------------*/ 
PBTSNODE InsertTree (PBTSNODE root, PSIMPLEX pS, PBOOL ptaller)
{
 if (root==NULL)
    {
     root     = NewBTSNODE(pS); /*Initiate the list with pS.*/
     *ptaller = True; /*Only in this case the tree balanced label are changed*/
    }
 else
    {
     if (iEQ(pS->F,root->plS->pFirstLS->pS->F))
         InsertListS(root->plS, pS);
     else
         if (iLT(pS->F,root->plS->pFirstLS->pS->F))
            {
             root->pleft=InsertTree(root->pleft,pS,ptaller);
             if (*ptaller)
                switch (root->Balance)
                       {
                        case LEFT:
                                 root=LeftInsertTreeBalance(root,ptaller);
                                 break;
                        case EQUAL:
                                 root->Balance=LEFT;
                                 break;
                        case RIGHT:
                                 root->Balance=EQUAL;
                                 *ptaller=False;
                                 break;
                       }
            }
         else
            {
             root->pright=InsertTree(root->pright,pS,ptaller);
             if (*ptaller)
                switch (root->Balance)
                       {
                        case LEFT:
                                 root->Balance=EQUAL;
                                 *ptaller=False;
                                 break;
                        case EQUAL:
                                 root->Balance=RIGHT;
                                 break;
                        case RIGHT:
                                 root=RightInsertTreeBalance(root,ptaller);
                                 break;
                       }
            }
    }
 return root;   
}

/*---------------------------------------------------------------------------*/
VOID InsertBTS(PBTS pbts, PSIMPLEX pS)
{
 BOOL taller = False;

 pbts->pFirstBTSNode=InsertTree(pbts->pFirstBTSNode,pS,&taller);

 pbts->NElem++;
 
 if (pbts->NElem > pbts->MaxNElem)
     pbts->MaxNElem = pbts->NElem;
	
}


/*---------------------------------------------------------------------------*/
/*Update the balance factors and do the necesary rotations when a left node  */
/*is removed.                                                                */
/*---------------------------------------------------------------------------*/
PBTSNODE LeftDelTreeBalance (PBTSNODE root, PBOOL pshorter)
{
 PBTSNODE Left, LeftRight;

 Left=root->pleft;
 switch (Left->Balance)
        {
         case LEFT:
              root->Balance=Left->Balance=EQUAL;
              root=RotateTreeRight(root);
              break;
         case EQUAL:
              root->Balance=LEFT;
              Left->Balance=RIGHT;
              root=RotateTreeRight(root);
              *pshorter=False;
              break;
         case RIGHT:
              LeftRight=Left->pright;
              switch (LeftRight->Balance)
                     {
                      case LEFT:
                           root->Balance=RIGHT;
                           Left->Balance=EQUAL;
                           break;
                      case EQUAL:
                           root->Balance=Left->Balance=EQUAL;
                           break;
                      case RIGHT:
                           root->Balance=EQUAL;
                           Left->Balance=LEFT;
                           break;
                     }
              LeftRight->Balance=EQUAL;
              root->pleft=RotateTreeLeft(root->pleft);
              root=RotateTreeRight(root);
              break;
        }
 return root;
}

/*---------------------------------------------------------------------------*/
/*Analogous to previous one but on the right.                                */
/*---------------------------------------------------------------------------*/
PBTSNODE RightDelTreeBalance (PBTSNODE root, PBOOL pshorter)
{
 PBTSNODE Right, RightLeft;

 Right=root->pright;
 switch (Right->Balance)
        {
         case LEFT:
              RightLeft=Right->pleft;
              switch (RightLeft->Balance)
                     {
                      case LEFT:
                           root->Balance=EQUAL;
                           Right->Balance=RIGHT;
                           break;
                      case EQUAL:
                           root->Balance=Right->Balance=EQUAL;
                           break;
                      case RIGHT:
                           root->Balance=LEFT;
                           Right->Balance=EQUAL;
                           break;
                     }
              RightLeft->Balance=EQUAL;
              root->pright=RotateTreeRight(root->pright);
              root=RotateTreeLeft(root);
              break;
         case EQUAL:
              root->Balance=RIGHT;
              Right->Balance=LEFT;
              root=RotateTreeLeft(root);
              *pshorter=False;
              break;
         case RIGHT:
              root->Balance=Right->Balance=EQUAL;
              root=RotateTreeLeft(root);
              break;
        }
 return root;	
}

/*---------------------------------------------------------------------------*/
/*With Pop=False the whole list is removed and pS=NULL                       */
/*---------------------------------------------------------------------------*/
PBTSNODE ExtractNodeEqual (PBTSNODE root, PPSIMPLEX ppS, ConstData &CtD, 
                           PBTV pbtv, itv & SelectIndex, 
                           PBOOL pshorter, const BOOL Pop, 
			               PINT pNFree, const BOOL Fill, PCHARCt Color)
{
 PBTSNODE Temp;
 
 if (root==NULL)
    {
     fprintf(stderr,"ExtractNodeEqual: root=NULL\n");
     fprintf(stderr,"[%10.10f, %10.10f].\n", 
                     SelectIndex.lower(), SelectIndex.upper());
     raise(SIGINT); //signal an interrupt to stop gdb and see bt 
     exit(1);
    }     
 else  
    {     	      
     if (iEQ(SelectIndex,root->plS->pFirstLS->pS->F))
        {
	     if (Pop)
	        {
	         (*ppS)=ExtractListS(root->plS);
	         (*pNFree)=1;
	        }	
	    
	     /*The later and next can run at the same time*/           
         if (Pop == False || root->plS->NElem == 0) /*Remove the hole node*/
	        {
	         if (Pop==False)
	            (*pNFree)=root->plS->NElem;
	            
	         if (root->pleft==NULL && root->pright==NULL)
        	    { 
		         root=FreeBTSNode(root,CtD,pbtv,Fill,Color);
        	     (*pshorter)=True;     
        	    }    	    
	         else
        	    if (root->pleft==NULL)
        	       {
        	        Temp=root->pright;
        	        ExchangeNode(root,Temp); 
        	        (*pshorter)=True;   
        	        Temp=FreeBTSNode(Temp,CtD,pbtv,Fill,Color);
        	       } 
        	    else
        	       if (root->pright==NULL)
                      {
                       Temp=root->pleft;
                       ExchangeNode(root,Temp);
                       (*pshorter)=True;   
                       Temp=FreeBTSNode(Temp,CtD,pbtv,Fill,Color);
                      } 
        	       else
                      {
                       for (Temp=root->pright;Temp->pleft!=NULL;Temp=Temp->pleft);
                       SwapBTSNode(root,Temp);  
                       root->pright=ExtractNodeEqual(root->pright,ppS,CtD,pbtv, 
		                                         SelectIndex,pshorter,
						                         Pop,pNFree,Fill,Color);
                       if (*pshorter)
                	      switch (root->Balance)
                        	     {
                        	      case LEFT:
                                       root=LeftDelTreeBalance(root, pshorter);
                                       break;
                        	      case EQUAL:
                                       root->Balance=LEFT;
                                       *pshorter=False;
                                       break;
                        	     case RIGHT:
                                       root->Balance=EQUAL;
                                       break;
                        	     }
                      } 
	        }
	}    	      
     else
        if (iLT(SelectIndex,root->plS->pFirstLS->pS->F) )
           {
            root->pleft=ExtractNodeEqual(root->pleft,ppS,CtD,pbtv, 
		                                 SelectIndex,pshorter,
				                         Pop,pNFree,Fill,Color);
            if (*pshorter)
               switch (root->Balance)
                      {
                       case LEFT:
                            root->Balance=EQUAL;
                            break;
                       case EQUAL:
                            root->Balance=RIGHT;
                            *pshorter=False;
                            break;
                       case RIGHT:
                            root=RightDelTreeBalance(root, pshorter);
                            break;
                      }              
           }
        else
           {
            root->pright=ExtractNodeEqual(root->pright,ppS,CtD,pbtv, 
		                                  SelectIndex,pshorter,
				                          Pop,pNFree,Fill,Color);
            if (*pshorter)
                switch (root->Balance)
                      {
                       case LEFT:
                            root=LeftDelTreeBalance(root, pshorter);
                            break;
                       case EQUAL:
                            root->Balance=LEFT;
                            *pshorter=False;
                            break;
                       case RIGHT:
                            root->Balance=EQUAL;
                            break;
                      }
           }
    }	   
 return root;
}

/*---------------------------------------------------------------------------*/
VOID ExtractEqualBTS (PBTS pbts, PPSIMPLEX ppS, ConstData & CtD, PBTV pbtv, 
                      itv & SelectIndex, const BOOL Pop, const BOOL Fill,
                      PCHARCt Color)
{
 BOOL shorter = False;
 INT NFree=0;	
 //
 /*INT OldEl,CalcOldEl,CalcNewEl;
 
 OldEl=pbts->NElem;
 CalcOldEl=CountNElemBTS(pbts);;
 
 if (OldEl!=CalcOldEl)
    {
     fprintf(stderr,"OldEl=%d, CalcOldEl=%d.\n", OldEl, CalcOldEl);
     exit(1);
    }
 else
    fprintf(stderr,"pbts->NElem=%d.\n", OldEl);  
 */
 //
 pbts->pFirstBTSNode = ExtractNodeEqual(pbts->pFirstBTSNode,ppS,CtD,pbtv,
                                        SelectIndex,&shorter,Pop,&NFree,
                                        Fill,Color);
 pbts->NElem-=NFree;
 
 //
 /*
 CalcNewEl=CountNElemBTS(pbts);
 if (pbts->NElem != CalcNewEl)
    {
     fprintf(stderr,"OldEl=%d, NFree=%d, pbts->NElem=%d, CaclNewEl=%d.\n",
                     OldEl,NFree,pbts->NElem,CalcNewEl);
     exit(1);       
    }
 //
 */   
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
PBTSNODE ExtractSmallerNode(PBTSNODE root, PPSIMPLEX ppS, ConstData & CtD,
                            PBTV pbtv, itv & SelectIndex, 
                            PBOOL pshorter, const BOOL Fill, PCHARCt Color)
{
 PBTSNODE Temp;
 
 if (root==NULL)
    {
     fprintf(stderr,"BTSNODE,ExtractSmallerNode: Empty BTS\n");
     exit(1);
    }     

 if (root->pleft!=NULL)
    root->pleft= ExtractSmallerNode(root->pleft,ppS,CtD,pbtv,SelectIndex, 
     				    pshorter,Fill,Color);	     
 else
    {
     (*ppS)        = ExtractListS(root->plS);
     SelectIndex = (*ppS)->F;
    } 
    
 /*Check if the node have to be removed*/ 
 if (root->plS->NElem==0 || iEQ(SelectIndex,root->plS->pFirstLS->pS->F) ) 
    { 
     if (root->plS->NElem == 0 ) 
        {
	     if (root->pleft==NULL && root->pright==NULL)
	        {
	         root=FreeBTSNode(root,CtD,pbtv,Fill,Color);
	         (*pshorter)=True; 
	         /*The new Smaller value was given in the path*/    
	        } 
	     else
	        {
	         Temp=root->pright;
	         ExchangeNode(root,Temp); 
	         *pshorter=True;   
	         Temp=FreeBTSNode(Temp,CtD,pbtv,Fill,Color);
	        } 
 	    }
    }    	      
 else /*root->Key > SelectIndex */
    {
     if (*pshorter)
	    switch (root->Balance)
               {
        	    case LEFT:
                     root->Balance=EQUAL;
                     break;
        	    case EQUAL:
                     root->Balance=RIGHT;
                     *pshorter=False;
                     break;
        	    case RIGHT:
                     root=RightDelTreeBalance(root, pshorter);
                     break;
               }              
    }
    
 return root;
}


/*---------------------------------------------------------------------------*/
VOID ExtractSmallerBTS (PBTS pbts, PPSIMPLEX ppS, ConstData & CtD, PBTV pbtv,
                        const BOOL Fill, PCHARCt Color)
{
 BOOL shorter = False;
 itv SelectIndex; //kv type.	

 pbts->pFirstBTSNode=ExtractSmallerNode(pbts->pFirstBTSNode,ppS,CtD,pbtv,
                                        SelectIndex,&shorter,Fill,Color);
 pbts->NElem--;
}

/*---------------------------------------------------------------------------*/
itv GetMaxBTSKey(PBTS pbts)
{
 PBTSNODE Temp;
 
 if (pbts->pFirstBTSNode==NULL)
    {
     fprintf(stderr,"GetMaxBTSKey: Empty BTS.\n");
     exit(1);
    } 
 Temp=pbts->pFirstBTSNode;
 while (Temp->pright!=NULL)
       Temp=Temp->pright;
 return Temp->plS->pFirstLS->pS->F;  
}
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
