/******************************************************************************
			btbox.h  - description
			----------------------
	begin		: August 2004
	copywirght	: (C) 2004 by L.G.Casado.
	
     ********************************************************************	

     Purpose: Define a balance binary tree of boxes sorted by their
              SelectIndex and define the nodes of the balance binary tree. 
     
     BTBNODE: Node of the balances binary tree of boxes:
     Stores:
     	plB: A list of boxes with the same SelectIndex.
	BALANCETYPE: The balance of the subtree which has this node as root.
	pleft,pright: Pointers to the lest and right braches.
				
     BTB: Balanced Binary Tree of boxes.				
     Stores:
     	NElem: Number of Elemets in the tree.
	MaxNElem: Maximum number of vertexes ever in the tree.
	pFirstBTBNode: Pointer to the fisrt node in the tree. 
		
    Functions:
	NewBTB: Gets memory for a BTB.
	PrintBTB: Print the BTB.
	InsertBTB: Insert the box pB in the BTB sorted by the SelectIndex. 
        ExtratEqualBTB: Given a select Index, if Pop=true extract a box
		with that SelectIndex. If Pop=False remove all the boxes
		with that SelectIndex. 
	Termination criterion can be checked after extranting the box with 	
	smaller lower bound.		
	  
*******************************************************************************/
#ifndef __BTB__
#define __BTB__

#define LEFT  -1
#define EQUAL  0
#define RIGHT  1

/*---------------------------------------------------------------------------*/ 
struct btsnode
       {
       	CHAR Balance;
        PLISTB plB;
        struct btsnode * pleft;
	struct btsnode * pright;
       };

typedef struct btsnode BTBNODE;
typedef BTBNODE *      PBTBNODE;
typedef PBTBNODE *     PPBTBNODE;


/*---------------------------------------------------------------------------*/
struct BalancedTreeB
      {
       int NElem;
       int MaxNElem;
       double SmallerLB;
       PBTBNODE pFirstBTBNode;
      };
      
typedef struct BalancedTreeB BTB;
typedef BTB  *     PBTB;
typedef PBTB *    PPBTB;


/*---------------------------------------------------------------------------*/
PBTB NewBTB	           (PBTB pBTB);
PBTB FreeBTB 	       (PBTB pbtb, ConstData CtD,
                        const BOOL Fill, PCHARCt Color);
int CountNElemBTB      (PBTB pbtb);  
void CheckBTBOrder     (PBTB pbtb);                      
VOID PrintBTB  	       (FILE * FOut, PBTB pbtb, const INT NDim);
VOID InsertBTB 	       (PBTB pbtb, PBOX pB);
VOID ExtractSmallerBTB (PBTB pbtb, PPBOX ppB, ConstData & CtD,
                        const BOOL Fill, PCHARCt Color);
itv GetMaxBTBKey       (PBTB pbtb);    
VOID ExtractEqualBTB   (PBTB pbtb, PPBOX ppB, ConstData & CtD, 
                        itv & SelectIndex, const BOOL Pop, 
                        const BOOL Fill, PCHARCt Color);
    
#endif /*__BTB__*/		     
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
