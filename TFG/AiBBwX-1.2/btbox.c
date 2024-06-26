/******************************************************************************
			btbox.c  - description
			----------------------
	begin		: August 2004
	copywirght	: (C) 2004 by L.G.Casado.
	
******************************************************************************/
#include "btbox.h"

/*---------------------------------------------------------------------------*/
PBTBNODE NewBTBNODE(PBOX pB)
{
 PBTBNODE pBTBNode;
 
 pBTBNode	   = (PBTBNODE)GetMem(1,sizeof(BTBNODE),"NewBTBNODE");
 pBTBNode->plB     = NewListB(pBTBNode->plB);
 InsertListB(pBTBNode->plB, pB);
 pBTBNode->Balance = EQUAL;
 pBTBNode->pleft   = NULL;
 pBTBNode->pright  = NULL;
 return pBTBNode;
}

/*---------------------------------------------------------------------------*/
PBTBNODE FreeBTBNode(PBTBNODE pBTBNode, ConstData & CtD,
                     const BOOL Fill, PCHARCt Color)
{
 if (pBTBNode==NULL)
    {
     fprintf(stderr,"Trying to free a NULL BTBNODE pointer.\n");
     exit(1);
    }
 pBTBNode->plB=FreeListB(pBTBNode->plB,CtD,Fill,Color);
 free((PVOID)pBTBNode);
 pBTBNode=NULL;
 return pBTBNode;   
}

/*----------------------------------------------------------------------------*/
/*Swap the nodes, but the structure of the BLTree does not change.            */
VOID SwapBTBNode(PBTBNODE pBTBNodeO, PBTBNODE pBTBNodeT)
{
 PLISTB plB;
 
 plB            = pBTBNodeO->plB;
 pBTBNodeO->plB = pBTBNodeT->plB;
 pBTBNodeT->plB = plB;
}

/*----------------------------------------------------------------------------*/
/*Swap the data and copy the Balance and pointers of the BTBNodes.            */
/*Node2 will be removed with data of node1 after exchange.                    */
/*----------------------------------------------------------------------------*/
VOID ExchangeNode(PBTBNODE node1, PBTBNODE node2)
{
 SwapBTBNode(node1,node2);
 node1->Balance = node2->Balance;
 node1->pleft   = node2->pleft;
 node1->pright  = node2->pright;

 node2->pleft   = NULL;
 node2->pright  = NULL;
} 

/*---------------------------------------------------------------------------*/
void PrintBTBSubTreeInOrder(FILE * FOut, PBTBNODE node, const INT NDim)
{
 if (node!=NULL)
    {
     PrintBTBSubTreeInOrder(FOut,node->pleft,  NDim);
     fprintf(FOut,"BTB(%d)->",node->Balance);
     //PrintListB (FOut,node->plB,NDim,MonTest);
     cerr << "SelectIndex=" <<  node->plB->pFirstLB->pB->F << endl;
     PrintBTBSubTreeInOrder(FOut,node->pright, NDim);
    }
  else
     fprintf(FOut,"BTB:N\n");
}

/*---------------------------------------------------------------------------*/
void NElemBTBSubTree(PBTBNODE node, int &NElem)
{
 if (node!=NULL)
    {
     NElem+=node->plB->NElem;
     NElemBTBSubTree(node->pleft,  NElem);
     NElemBTBSubTree(node->pright, NElem);
    }
}

/*---------------------------------------------------------------------------*/
//Traverses the AVL tree in Order to see if data is ordered 
void CheckBTBSubTreeOrder(PBTBNODE node, itv & PrevItv, BOOL & First)
{
 if (node!=NULL)
    {
     CheckBTBSubTreeOrder(node->pleft, PrevItv, First);
     if (First)
        {
         PrevItv=node->plB->pFirstLB->pB->F;
         //cerr << "First PrevItv=" << PrevItv << endl;
         First=False;
        }
     else
        {
         if (iLE(PrevItv,node->plB->pFirstLB->pB->F))
            {
             //cerr << "-----------------------" << endl;
             //cerr << "PrevItv=" << PrevItv << endl;
             //cerr << "CurrItv=" << node->plB->pFirstLB->pB->F << endl;
             PrevItv=(node->plB->pFirstLB->pB->F);
            } 
         else
            {
             cerr << "-----------------------" << endl;
             cerr << "PrevItv=" << PrevItv << endl;
             cerr << "CurrItv=" << node->plB->pFirstLB->pB->F << endl;
             exit(1);
            } 
         }              
     CheckBTBSubTreeOrder(node->pright, PrevItv, First);     
    }
}

/*---------------------------------------------------------------------------*/
void CheckBTBOrder(PBTB pbtb)
{
 itv PrevItv;
 BOOL First=True;
 
 if ( pbtb->pFirstBTBNode==NULL || 
     (pbtb->pFirstBTBNode->pleft==NULL && pbtb->pFirstBTBNode->pright==NULL))
    return;
 else    
    CheckBTBSubTreeOrder(pbtb->pFirstBTBNode, PrevItv, First);     
}


/*---------------------------------------------------------------------------*/
void PrintBTBSubTree(FILE * FOut,PBTBNODE node, const INT NDim)
{
 if (node!=NULL)
    {
     fprintf(FOut,"BTB(%d)->",node->Balance);
     //PrintListB (FOut,node->plB,NDim,MonTest);
     cerr << "SelectIndex=" <<  node->plB->pFirstLB->pB->F << endl;
     PrintBTBSubTree(FOut,node->pleft,  NDim);
     PrintBTBSubTree(FOut,node->pright, NDim);
    }
  else
     fprintf(FOut,"BTB:N\n");
}


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
PBTB NewBTB(PBTB pBTB)
{
 pBTB                 = (PBTB) GetMem(1,sizeof(BTB),"NewBTB");
 pBTB->NElem          = 0;
 pBTB->MaxNElem       = 0;	
 pBTB->pFirstBTBNode  = NULL;
 return pBTB;
}

/*----------------------------------------------------------------------------*/
void FreeBTBSubTree(PBTBNODE root, ConstData &CtD,
                    const BOOL Fill, PCHARCt Color)
{
 if (root!=NULL)
    {
     //fprintf(stderr,"FreeBTBSubTree:Left,\n");
     FreeBTBSubTree(root->pleft,CtD,Fill,Color);
     //fprintf(stderr,"FreeBTBSubTree:Right,\n");
     FreeBTBSubTree(root->pright,CtD,Fill,Color);
     //fprintf(stderr,"FreeBTBSubTree: FreeBTBNode,\n");
     root=FreeBTBNode(root,CtD,Fill,Color);     
    }
// else
//    fprintf(stderr,"FreeBTBSubTree: NULL,\n");   
}

/*----------------------------------------------------------------------------*/
PBTB FreeBTB(PBTB pbtb, ConstData CtD, const BOOL Fill, 
             PCHARCt Color)
{
 if (pbtb!=NULL)
    {
    //////////////////
     FreeBTBSubTree(pbtb->pFirstBTBNode,CtD,Fill,Color);
     pbtb->pFirstBTBNode=NULL;
     free((PVOID)pbtb);
     pbtb=NULL;
    }
 return NULL;   
}

/*---------------------------------------------------------------------------*/
int CountNElemBTB(PBTB pbtb)
{
 int NElem=0;
 NElemBTBSubTree(pbtb->pFirstBTBNode,NElem);     
 return NElem;
}

/*---------------------------------------------------------------------------*/
void PrintBTB(FILE * FOut, PBTB pbtb, const INT NDim)
{
 fprintf(FOut,"\n---------------------PrintBTB-----------------------\n");
 if (pbtb!=NULL)
    {
     fprintf(FOut,"BTB:Number of Elements     = %d\n",pbtb->NElem);
     fprintf(FOut,"BTB:Max Number of Elements = %d\n",pbtb->MaxNElem);
     PrintBTBSubTree(FOut,pbtb->pFirstBTBNode,NDim);    
    }
  else
     fprintf(stderr,"BTB:N\n");
 fputs("---------------------End-PrintBTB-------------------\n",stderr);     
}


/*----------------------------------------------------------------------------*/
/*Rotate left a binary Tree                                                   */
/*----------------------------------------------------------------------------*/
PBTBNODE RotateTreeLeft(PBTBNODE root)
{
 PBTBNODE Temp;

 if (root==NULL)
    {
     fprintf(stderr,"BTBimplex::RotateTreeLeft :");;
     fprintf(stderr," Can not rotate to left an empty tree \n");
     exit(1);
    }
 else
    if (root->pright==NULL)
       {
        fprintf(stderr,"BTBimplex::RotateTreeLeft : Can not rotate to left\n");
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
PBTBNODE RotateTreeRight(PBTBNODE root)
{
 PBTBNODE Temp;
 
 if (root==NULL)
    {
     fprintf(stderr,"BTBimplex::RotateTreeRight :");
     fprintf(stderr," Can not rotate to right an empty tree \n");
     exit(1);
    }
 else
    if (root->pleft==NULL)
       {
        fprintf(stderr,"BTBimplex::RotateTreeRight:Can not rotate to right\n");
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
PBTBNODE LeftInsertTreeBalance(PBTBNODE root, PBOOL ptaller)
{
 PBTBNODE Left, LeftRight;

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
              fprintf(stderr,"BTBimplex:LeftInsertTreeBalance :");
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
PBTBNODE RightInsertTreeBalance(PBTBNODE root, PBOOL ptaller)
{
 PBTBNODE Right, RightLeft;

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
              fprintf(stderr,"BTBimplex:RightInsertTreeBalance: ");
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
/*Do the actual insertion in the BTBimplex.                                  */
/*---------------------------------------------------------------------------*/ 
PBTBNODE InsertTree (PBTBNODE root, PBOX pB, PBOOL ptaller)
{
 if (root==NULL)
    {
     root     = NewBTBNODE(pB); /*Initiate the list with pB.*/
     *ptaller = True; /*Only in this case the tree balanced label are changed*/
    }
 else
    {
     if (iEQ(pB->F,root->plB->pFirstLB->pB->F))
         InsertListB(root->plB, pB);
     else
         if (iLT(pB->F,root->plB->pFirstLB->pB->F))
            {
             root->pleft=InsertTree(root->pleft,pB,ptaller);
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
             root->pright=InsertTree(root->pright,pB,ptaller);
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
VOID InsertBTB(PBTB pbtb, PBOX pB)
{
 BOOL taller = False;

 pbtb->pFirstBTBNode=InsertTree(pbtb->pFirstBTBNode,pB,&taller);

 pbtb->NElem++;
 
 if (pbtb->NElem > pbtb->MaxNElem)
     pbtb->MaxNElem = pbtb->NElem;
	
}


/*---------------------------------------------------------------------------*/
/*Update the balance factors and do the necesary rotations when a left node  */
/*is removed.                                                                */
/*---------------------------------------------------------------------------*/
PBTBNODE LeftDelTreeBalance (PBTBNODE root, PBOOL pshorter)
{
 PBTBNODE Left, LeftRight;

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
PBTBNODE RightDelTreeBalance (PBTBNODE root, PBOOL pshorter)
{
 PBTBNODE Right, RightLeft;

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
/*With Pop=False the whole list is removed and pB=NULL                       */
/*---------------------------------------------------------------------------*/
PBTBNODE ExtractNodeEqual (PBTBNODE root, PPBOX ppB, ConstData &CtD, 
                           itv & SelectIndex, 
                           PBOOL pshorter, const BOOL Pop, 
			               PINT pNFree, const BOOL Fill, PCHARCt Color)
{
 PBTBNODE Temp;
 
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
     if (iEQ(SelectIndex,root->plB->pFirstLB->pB->F))
        {
	     if (Pop)
	        {
	         (*ppB)=ExtractListB(root->plB);
	         (*pNFree)=1;
	        }	
	    
	     /*The later and next can run at the same time*/           
         if (Pop == False || root->plB->NElem == 0) /*Remove the hole node*/
	        {
	         if (Pop==False)
	            (*pNFree)=root->plB->NElem;
	            
	         if (root->pleft==NULL && root->pright==NULL)
        	    { 
		         root=FreeBTBNode(root,CtD,Fill,Color);
        	     (*pshorter)=True;     
        	    }    	    
	         else
        	    if (root->pleft==NULL)
        	       {
        	        Temp=root->pright;
        	        ExchangeNode(root,Temp); 
        	        (*pshorter)=True;   
        	        Temp=FreeBTBNode(Temp,CtD,Fill,Color);
        	       } 
        	    else
        	       if (root->pright==NULL)
                      {
                       Temp=root->pleft;
                       ExchangeNode(root,Temp);
                       (*pshorter)=True;   
                       Temp=FreeBTBNode(Temp,CtD,Fill,Color);
                      } 
        	       else
                      {
                       for (Temp=root->pright;Temp->pleft!=NULL;Temp=Temp->pleft);
                       SwapBTBNode(root,Temp);  
                       root->pright=ExtractNodeEqual(root->pright,ppB,CtD, 
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
        if (iLT(SelectIndex,root->plB->pFirstLB->pB->F) )
           {
            root->pleft=ExtractNodeEqual(root->pleft,ppB,CtD, 
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
            root->pright=ExtractNodeEqual(root->pright,ppB,CtD, 
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
VOID ExtractEqualBTB (PBTB pbtb, PPBOX ppB, ConstData & CtD, 
                      itv & SelectIndex, const BOOL Pop, const BOOL Fill,
                      PCHARCt Color)
{
 BOOL shorter = False;
 INT NFree=0;	
 //
 /*INT OldEl,CalcOldEl,CalcNewEl;
 
 OldEl=pbtb->NElem;
 CalcOldEl=CountNElemBTB(pbtb);;
 
 if (OldEl!=CalcOldEl)
    {
     fprintf(stderr,"OldEl=%d, CalcOldEl=%d.\n", OldEl, CalcOldEl);
     exit(1);
    }
 else
    fprintf(stderr,"pbtb->NElem=%d.\n", OldEl);  
 */
 //
 pbtb->pFirstBTBNode = ExtractNodeEqual(pbtb->pFirstBTBNode,ppB,CtD,
                                        SelectIndex,&shorter,Pop,&NFree,
                                        Fill,Color);
 pbtb->NElem-=NFree;
 
 //
 /*
 CalcNewEl=CountNElemBTB(pbtb);
 if (pbtb->NElem != CalcNewEl)
    {
     fprintf(stderr,"OldEl=%d, NFree=%d, pbtb->NElem=%d, CaclNewEl=%d.\n",
                     OldEl,NFree,pbtb->NElem,CalcNewEl);
     exit(1);       
    }
 //
 */   
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
PBTBNODE ExtractSmallerNode(PBTBNODE root, PPBOX ppB, ConstData & CtD,
                            itv & SelectIndex, 
                            PBOOL pshorter, const BOOL Fill, PCHARCt Color)
{
 PBTBNODE Temp;
 
 if (root==NULL)
    {
     fprintf(stderr,"BTBNODE,ExtractSmallerNode: Empty BTB\n");
     exit(1);
    }     

 if (root->pleft!=NULL)
    root->pleft= ExtractSmallerNode(root->pleft,ppB,CtD,SelectIndex, 
     				    pshorter,Fill,Color);	     
 else
    {
     (*ppB)        = ExtractListB(root->plB);
     SelectIndex = (*ppB)->F;
    } 
    
 /*Check if the node have to be removed*/ 
 if (root->plB->NElem==0 || iEQ(SelectIndex,root->plB->pFirstLB->pB->F) ) 
    { 
     if (root->plB->NElem == 0 ) 
        {
	     if (root->pleft==NULL && root->pright==NULL)
	        {
	         root=FreeBTBNode(root,CtD,Fill,Color);
	         (*pshorter)=True; 
	         /*The new Smaller value was given in the path*/    
	        } 
	     else //I have a right branch
	        {
	         Temp=root->pright;
	         ExchangeNode(root,Temp); 
	         *pshorter=True;   
	         Temp=FreeBTBNode(Temp,CtD,Fill,Color);
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
VOID ExtractSmallerBTB (PBTB pbtb, PPBOX ppB, ConstData & CtD,
                        const BOOL Fill, PCHARCt Color)
{
 BOOL shorter = False;
 itv SelectIndex; //kv type.	

 pbtb->pFirstBTBNode=ExtractSmallerNode(pbtb->pFirstBTBNode,ppB,CtD,
                                        SelectIndex,&shorter,Fill,Color);
 pbtb->NElem--;
}

/*---------------------------------------------------------------------------*/
itv GetMaxBTBKey(PBTB pbtb)
{
 PBTBNODE Temp;
 
 if (pbtb->pFirstBTBNode==NULL)
    {
     fprintf(stderr,"GetMaxBTBKey: Empty BTB.\n");
     exit(1);
    } 
 Temp=pbtb->pFirstBTBNode;
 while (Temp->pright!=NULL)
       Temp=Temp->pright;
 return Temp->plB->pFirstLB->pB->F;  
}
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
