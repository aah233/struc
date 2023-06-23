/******************************************************************************
			listbox.h  - description
			----------------------
	begin		: April 2023
	copywirght	: (C) 2023 by L.G.Casado.
	
     ********************************************************************	

     Purpose: Define a list of boxes which will have the same sort
     		key value.
     
     LBNODE: Node of the list:
     Stores:
     	A box.
	A pointer to the next node in the list.     
    Functions:
    	NewLSNode(): generates a new node of the list of  boxes.
	FreeLSNode(): Free a node of the list of boxes.
				
     LISTB: List of boxes.				
     Stores:
     	NElem: Number of Elemets in the list..
	pFirstLB: First pointer to the list. 
	
    Functions:
    	NewListB(): Get memory and initiates the list.
	FreeListB(): Free al the nodes of the list and the memory allocated by
		the list.
	InsertListB(): Insert the box in the list. All the boxes in the
	list have the same SelectIndex. The box with smallest size is inserted
	before than others.
	InsertFinalListB(): Insert as they arrive.	
	ExtractListB(): Return the box at the head of the list and delete
	the list node.
       PrintListB(): Print the contents of the List.
          
*******************************************************************************/
#ifndef __LISTB__
#define __LISTB__

/*---------------------------------------------------------------------------*/ 
struct lbnode
       {
        PBOX pB;
        struct lbnode * pnext;
       };

typedef struct lbnode LBNODE;
typedef LBNODE *      PLBNODE;


/*---------------------------------------------------------------------------*/
struct ListB
      {
       int NElem;
       int MaxNElem;
       PLBNODE pFirstLB;
      };
      
typedef struct ListB LISTB;
typedef LISTB  *     PLISTB;
typedef PLISTB  *    PPLISTB;

/*---------------------------------------------------------------------------*/
PLISTB	NewListB		(PLISTB pls);
PLISTB	FreeListB		(PLISTB pls, ConstData CtD, 
						 const BOOL Fill, PCHARCt Color);
VOID	InsertListB		(PLISTB pls, PBOX pB);
PBOX	ExtractListB	(PLISTB pls);
VOID	PrintListB		(FILE * FOut, PLISTB pls,
							const INT NDim, const INT MonTest);
VOID	DrawListB		(PLISTB pls, ConstData &CtD, const BOOL Fill, 
						 PCHARCt color);
#endif /*__LISTB__*/
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
