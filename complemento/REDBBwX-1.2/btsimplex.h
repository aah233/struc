/******************************************************************************
			btsimplex.h  - description
			----------------------
	begin		: August 2004
	copywirght	: (C) 2004 by L.G.Casado.
	
     ********************************************************************	

     Purpose: Define a balance binary tree of simplexes sorted by their
              SelectIndex and define the nodes of the balance binary tree. 
     
     BTSNODE: Node of the balances binary tree of simplexes:
     Stores:
     	plS: A list of simplexes with the same SelectIndex.
	BALANCETYPE: The balance of the subtree which has this node as root.
	pleft,pright: Pointers to the lest and right braches.
				
     BTS: Balanced Binary Tree of simplexes.				
     Stores:
     	NElem: Number of Elemets in the tree.
	MaxNElem: Maximum number of vertexes ever in the tree.
	pFirstBTSNode: Pointer to the fisrt node in the tree. 
		
    Functions:
	NewBTS: Gets memory for a BTS.
	PrintBTS: Print the BTS.
	InsertBTS: Insert the simplex pS in the BTS sorted by the SelectIndex. 
        ExtratEqualBTS: Given a select Index, if Pop=true extract a simplex
		with that SelectIndex. If Pop=False remove all the simplexes
		with that SelectIndex. 
	Termination criterion can be checked after extranting the simplex with 	
	smaller lower bound.		
	  
*******************************************************************************/
#ifndef __BTS__
#define __BTS__

/*---------------------------------------------------------------------------*/ 
struct btsnode
       {
       	CHAR Balance;
        PLISTS plS;
        struct btsnode * pleft;
	struct btsnode * pright;
       };

typedef struct btsnode BTSNODE;
typedef BTSNODE *      PBTSNODE;
typedef PBTSNODE *     PPBTSNODE;


/*---------------------------------------------------------------------------*/
struct BalancedTreeS
      {
       int NElem;
       int MaxNElem;
       double SmallerLB;
       PBTSNODE pFirstBTSNode;
      };
      
typedef struct BalancedTreeS BTS;
typedef BTS  *     PBTS;
typedef PBTS *    PPBTS;


/*---------------------------------------------------------------------------*/
PBTS NewBTS	           (PBTS pBTS);
PBTS FreeBTS 	       (PBTS pbts, PBTV pbtv, ConstData CtD,
                        const BOOL Fill, PCHARCt Color);
int CountNElemBTS      (PBTS pbts);  
void CheckBTSOrder     (PBTS pbts);                      
VOID PrintBTS  	       (FILE * FOut, PBTS pbts, const INT NDim);
VOID InsertBTS 	       (PBTS pbts, PSIMPLEX pS);
VOID ExtractSmallerBTS (PBTS pbts, PPSIMPLEX ppS, ConstData & CtD, PBTV pbtv,
                        const BOOL Fill, PCHARCt Color);
itv GetMaxBTSKey       (PBTS pbts);    
VOID ExtractEqualBTS   (PBTS pbts, PPSIMPLEX ppS, ConstData & CtD, PBTV pbtv, 
                        itv & SelectIndex, const BOOL Pop, 
                        const BOOL Fill, PCHARCt Color);
    
#endif /*__BTS__*/		     
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
