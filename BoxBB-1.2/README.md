________________________________________________________________________________
# BoxBB-1.1
Optimización sobre regiones que son intervalos n-dimensionales.
necesitas:
Compilador g++
Para salida grafica el paquete tk.
El kv en el directoio home.
	kv necesita boost-devel

________________________________________________________________________________
# BoxCSLP-1.1
Si la caja monotona y borde ver si se reduce.
________________________________________________________________________________
# BoxCSLP-1.0
**Arreglado arghands() no tenia en cuenta la longitud de los flags**
BoxCSLC (Box over convex set with Linear constraints)  que se le pasen 
 - los vértices del convex set por un lado y
 - Las restricciones lineales por otro
Genere el interval convex hull del convex set y optimize teniendo en cuenta las restricciones.

Ahora mismo solo están preparadas:
SimplexEligius.txt y
SimplexGP.txt 

Bogi me mandó las LC para:
SimplexEligius
Hartman 6:
Michal5:
ST5:
Ver Constraints.txt donde están los datos generados por Bogi.


La idea es tener otro BoxBB para optimzar como siempre sobre cajas y funciones con box constraints.

**TODO**:
 - Ver si la caja es monotona hacia el borde de la inicial -> reducir a ese borde.


--------------------------------------------------------------------------------
# SLb-kv-7.1

TODO: Add problems with one less vertes. Remove second=number 1.


Remove pMaxDV (Max distance from vertex to other) Not needed and consume time.

By storing future simplices in the current one, we observe an increasing of simplices evaluation and a decreasing of monotonic ones -> motonicity test did a better work.

So,
For descendants in S, only F and G are evaluated.
The DescMaxLevel could not be reached (division/F and G evaluation stops) when 
  * current simplex will be discarded by RangueUp test.
  * current simplex is monotonic. -> monotonic do not use descendants ¿?
  These leafs are not Expandable. 
  We have to differentiate 
  	 - Monotonic by descendant, they use the descendants division. It has descendants.
	 - Monotonic by thenselves, they are divided in the traditional way. It has not descendants.
Un simplex con descencientes, siempre tendrá al manos el hijo de la izquierda y de la derecha.

In the way back of recursion, F and G union of descendants will update current F and G. 
We need to know when a tree is not Expandable because all leafs are RangeUP or monotonic. 
Every simplex has a label Expandable that is initially to true. 
In the recursion back Expandable of current simplex is BitOr Exapndable of sons.
TODO: Probe there could not be a non leaf node not expandable having expandable descendants. 
Monotonic with non monotonic descendants is not posible.
RangeUp with non RangeUp descendants is not possible.


More expansive decices as 
EvalLB and Monotonicity test are only done for sons of selected node to test them to reject or to insert them in the BTS.

* TODO: Border and OrigFacet should be done  only if simplex will be inserted in BTS. For that, V1 and V2 of the bisected edge in the parent and waht is the new in this simplex should be stored in the simplex. 

* TODO: differientate between EvalFG and EvalLB

-------------------------------------------------------------------------------
# SLb-kv-7.0
 * Every simplex will have a tree of descendants where F anf G are evaluated in order to get better F and G in the root simplex by the Union of F and G in their descendants.

* The union of F and G of two descendant can update F and G of the previous ancestor. Recursive binary tree **Postorder** traversal is needed. Once all descendants are generated and evaluated:
https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/

* F and G are only evaluated in the leafs. Lower bounds are tried to be improved in the way back of binary traversal when G is updated from the sons.

* If DescLevel==0 no descendants are stored. So division has to take into account:
	- normal division 
* if DescLevel>0
	- descendant creation.
	- If S is rejected or reduced, all descendants are rejected.
* If S is divided:
	- DescLevel==0 Generate S1 and S2, evalaute them and store them.
	- Desclevel>0. 
		* Generate the remaining descendats for S1 and S2. 
		* Recalculate F and G an store S1 and S2 (the first descendants).

In this way, hard devices as CV+local search, LP or MIP are done over simplices with better F and G, but not for all evaluated simplices at the cost of evaluate more simplices.

 * If the root simplex has to be divided, the next descendants has to decrease their descendants level, evaluate new descendants (F and G)  and then they can be stored.

* **TODO**: Descendant level can be tuned depending on the current data.

* The level can be limited by by the user. 
	Max=NDim. Number of descendants=2^NDim -> too much.

-------------------------------------------------------------------------------
To changue the program in scripts:
sed -i "s/SLb-kv-6.4/SLb-kv-7.0/g" RunSimplex-i.sh

-------------------------------------------------------------------------------
Instrctions hot to install SLb-kv-6.4-CPLEX.tgz.
Uncompress SLb-kv-6.4-CPLEX.tgz.
It requires:
kv, PNL, CPLEX:

 ** kv: http://verifiedby.me/kv/ (used 0.4.55) 
 	- Just copy or ln -s <Path To kv>/kv-0-4-55 ~/kv

 ** PNL: https://pnlnum.github.io/pnl/ (used 1.11.0) 
  Download to a temporal directory from: https://pnlnum.github.io/pnl
  To avoid output:
  As said in https://lpsolve.sourceforge.net/5.5/
  in src/optim/lp_solve-wrap, int pnl_optim_linprog(), before ret = solve(lp); 
  set_timeout(lp,1);
  
  To limit the time in a problem t 1 s:
  as before:
  set_verbose(lp,SEVERE);
  
  mkdir build
  cd  build
  cmake -DWITH_MPI=OFF -DCMAKE_BUILD_TYPE=Release -DPNL_INSTALL_PREFIX=$HOME/pnl-1.11.0 ..
  make
  make install
  Just copy or ln -s <Path To pnl-1.11.0>/pnl-1.11.0 ~/pnl

** CPLEX
Download ILOG CPLEX Studio from ibm.
There are 
	- free trial: CPLEX_Studio_Community2211
	- Free for academics: CPLEX_Studio221

Just run the downloaded bin as root.
It is installed on /opt/ibm/ILOG/
Uncomment the appropiate line of the SLb-kv-6.4-CPLEX/makefile.

There is a commend arguments help with 
$SLb-kv-6.4 --help

Examples to run: See Run*.bat

In case you want graphical output, you need tcl/tk.
I have tk package installed. Then finish the command line 
with:
-tcl 3 | WinZoom.tcl

-------------------------------------------------------------------------------
# SLb-kv-6.4-CPLEX
Add CPLEX for LP(6) LP(7), MIP8 and MIP9.
See MipLpCplex.hpp and MipLpCplex.cpp. Memory leaks solved.
Some functions could be reduced to just one. See Setd() and Sety().

-------------------------------------------------------------------------------
# SLb-kv-6.3-CPLEX
Add CPLEX for LP(6) LP(7), MIP8 and MIP9.
MIPDefinitions.h MIPandMP.h MIPandLP.cpp were added from Bogi.
There are memory leaks.

-------------------------------------------------------------------------------
# SLb-kv-6.2
He puesto en defines.h los nuevos typos y definiciones.
He usado nombres para los indices de pCounters[i].
En CounterDesc[i] está la descripción de pCounters[i].
He usado nombres para los indices de los tipos de inclusion.
He usado nombres para los indices de los test de monotonía.

He añadido a CtD.DoMonDDInS (6) por defecto True. No se activa si se pasa el parámetro -NoLPIn al ejecutable.

Si LPInS (6) falla se divide, no se hace LPF (7) para cada faceta hasta encontrar un Dir.Der. negativo.



-------------------------------------------------------------------------------
# SLb-kv-6.1

----------------------------------------------------
CtD.EvalVSim depends on the IncTyoe and CtD.SInSim.
----------------------------------------------------
LP data needed for IncType 4(CFbSim) and 7(LPBox).
----------------------------------------------------
Another LP data is needed for CtD.MonTest 4(LP) and 5(CV+LP).
----------------------------------------------------
For CtD.MonTest 1(C), 3(CV), 5 (CV+LP), 6(CV+LS) we need:
CtD.pCentreS and CtD.ppCentreF.
----------------------------------------------------
For CtD.MonTest 3(CV), 5 (CV+LP) and 6(CV+LS) wee need:
CtD.pFacetsOrder: Best order to visit Facets.
CtD.VCDirDerVect: Vertex centre Dir Derivatives.
----------------------------------------------------
For CtD.MonTest 6(CV+LS) wee need:
CtD.VVDirDerVect: All Vertex to Vertex DirDer.
CtD.pLastUpper: Last 3 upper bounds for LS.
CtD.pLastLower:  Last 3 lower bounds for LS.
CtD.ppFacetPoints: End points of Dir Der from vertex in opposite facet.
CtD.FacetDirDerVect: Dir. Der, for CtD.ppFacetPoints - v.
CtD.ppCPoints: centroids of removing ppFacetPoints[i].
CtD.CDirDerVect: dir vector from pFacetVertex to preovius C.
----------------------------------------------------
First we check initial S.
While (pS!=NULL and !termination criterion)
  //To avoid divisions.
  //Just reduced simplex, G is Monotonic: IA isotonicity.
  if (S in simplex and IsMon and Reduced and NOT AllZeroInGrad)
	  pS=**CheckMonoSInSimplex()**
	  
  if (SInBox and isMon and has border facets)
	  pS=**ReduceSInBox()**
  
  if (pS==NULL and No more simplices)
	  Leave the while.

  if (pS==NULL and exists simplices)
	  pS=extract one.

  //pS!=NULL and AllZeroInGrad.
  **DivideSimplex()** 
  **TestSimplex()**
  if (pS!=NULL)
  	 Insert S
  if (pS1!=NULL)
  	 Insert S1
  if (exists simplices in bts)
     pS=extract one.

Free mem.
Print statistics.

Summary of the Monocitity tests.
-------------------------------------------------------------
**TestSimplex()**:
Does:
  * **RangeUpTest()**
  * if 0\notin G
	  if ((S (in Simplex and FullDim) or in Box) and 
	      NBorderFacets==0
	     )
		 return pS=NULL;
	  if S\in Box with border facets **ReduceSInBox()**
	  if S\in Simplex **CheckMonoSInSimplex()**

-------------------------------------------------------------
Let's focus on S in simplex:
**CheckMonoSInSimplex()**:
Set
	* Set pDirDerFType[i]= False. i=Facet.
	* NNegGrad=0 //Number of facets with Neg DGrad.
	* NPosGrad=0 //Number of facets with Pos DGrad.

We have the following defines in utils.h.
Some of them usd for pDirDerFType[i]:
  * 0 False: 		Not Set.
  * 1 True: 		¿?
  * 2 ZeroInGrad:	0\in G
  * 3 PosGrad:	G>0
  * 4 NegGrad:	G<0
  * 5 Reject: 	Reject Simplex

if NVertices==2 -> ToDo=**GetDirDerV()** -> using Vertex to Vertex.
else (NVertices>2)
	switch MonTest:
	* 1: 		ToDo=**GetDirDerC()**
	* 2: 		ToDo=**GetDirDerV()**
	* 3,5,6: 	ToDo=**GetDirDerCV()**
	* 4:		ToDo=**GetDirDerLPMOn()**

	if ToDo!=Reject and ToDo!=Divide and NNegGrad==0 and MonTest==5 (CV+LP) 
	   ToDo=**GetDirDerLPMOn()**
	if ToDo!=Reject and ToDo!=Divide and NNegGrad==0 and MonTest==6 (CV+LS) 
	   ToDo=**CheckLSearchDDVToF()**

if ( ToDo==Reject ) return pS=NULL

//Exists NegGrad.
if NNegGrad>0 and NBorderFacets > 0
	if NewNVectices=(NVertices-NNegGrad) == 1 
	   **EvalOneVertex(NegGrad)**; return pS=NULL;
	//(Genero facetas MinInFacet. vertex=-1->NotGiven).
	**GenerateAndEvalRedS(-1,NegGrad)** 
	return pS=NULL;
	
//!Exists NegGrad.
if (NBorderFacets > 0 and (NPosGrad>0 || S is FullDim))
	if NewNVectices=(NVertices-1) == 1 
	   //This cannot happens. PosGrad in an edge without NegGrad.
	   **EvalOneVertex(ZeroInGrad)**; return pS=NULL;
	   return pS=NULL;
	foreach facet
	  if facet is border and pDirDerFType[facet]!=PosGrad
	     **GenerateAndEvalRedS( facet,ZeroInGrad)** (Genero facetas Unknown)
	return pS=NULL;

//!Exists PosGrad neither NegGrad.
pS is Reduced (full and Mon was checked, even with border facets).
pS->AllZeroInGrad=True
return pS!=NULL //->Divide.


-------------------------------------------------------------
**GetDirDerV()**: 
Para cada vertice
	Para los demás vertices
	     DirDer=**GetDirDeriv()**
	     ToDo = **SetAndCheckDirDerFType()** (Para * -1 también).
return ToDo=Reject o False.

--------------------------------------------------------------
**SetAndCheckDirDerFType()** (para una DirDer y Facet).
  * Establece pDirDerFType[facet] si el nuevo valor es más alto.
  		(Ver defines en utils.h).
  * Si pDirDerFType[facet] == NegGrad
       NNegGrad++
	   Si facet no boder return Reject. //Catch NegGrad without border facets.
  * Si pDirDerFType[facet] == PosGrad 
  	   PosGrad++ 
  	   Si faceta borde, label a no borde.
		  Si después del cambio no hay facetas borde
		      return Reject. //Exist mon DD without border facets.
return DirDerType.

--------------------------------------------------------------
**EvalOneVertex(GradType)**
Para cada vertice i
	Si pDirDerFType[i]!=GradType
	  Si (GradType==NegGrad ||
	      (GradType==ZeroInGrad && pIsBorderFacet[i]==True)
	     )
	     Evaluo el vertice i.
	     break; //Found.

--------------------------------------------------------------
**GenerateAndEvalRedS(,GradType)**
GradType must be NedGrad or ZeroInGrad.
if GradType==NegGrad
   pSNew=**ReducedSInSNegGrad()**
if GradType==ZeroInGrad
   pSNew=**ReducedSInSZeroInGrad()**

//Calculate distances, size, border labesl and NBorderFacets.
**UpdateReducedSInS(pSNew)** 
Evaluate pSNew.
if ( RangeUpTest())
   pSNew=NULL.
else
   Insert in BTS.

--------------------------------------------------------------
**ReducedSInSNegGrad()**  //En simplex.cpp
Coge memoria para el nuevo simplex pRedS.
Copia los vertices y sus estados (IsBorderFacet y pOrigFaceOfV) de pS, solo si no son NegGrad.
return pRedS

--------------------------------------------------------------
**ReducedSInSZeroInGrad(VToRem)**
Coge memoria para el nuevo simplex pRedS.
Copia todos ls vertices y sus estados (IsBorderFacet y pOrigFaceOfV) de pS, menos de VToRem
return pRedS

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
# SLb-kv-6.1
It is not clear when a positive dd is found if LS or LP search again in facet or if when a negative dd is found the search on other facets continue.

I am checking and cleaning the code for that.

My idea is that we can continue with C or V for all facets but stop for LP and LS after a negative is found. In case a negative is fouind in C or V, LP or LS are not done.
LS and LP have to check if in a current facet a positive was already found by CV. LP and LS will process facets if not negative was found.

-------------------------------------------------------------------------------
# SLb-kv-6.0

Clean 5.3 by removing all methods that do not bring improvements and their associated data. Now there are onlu 6 -mt methods. See --help.


-------------------------------------------------------------------------------
# SLb-kv-5.2
In CV+ (-mt 5 and so on) we evaluate first C and store in CtD.FacetOrder the order to visit the facets based on min \mu(h(c)) for each facet. 

-------------------------------------------------------------------------------
# SLb-kv-5.2
We check in CheckLSearchDDVToF  GetRemIter() using as LastUpper[2], LastLower[2]
the DD to C, and for 0 and 1 the best DD-V.
Then, if the RemIter < MPoints = #Facet vertices.

-------------------------------------------------------------------------------
# SLb-kv-5.1
Trying to determine when is not worth to do LP or Local search for a monotonic direction towards a facet.
I'll see how is c direction in comparison with v ones.
See -af option and GetCheckFacet() at test.cpp.
Basically we check if the distance to scape from cero in C direction is the best 
in {C,V} then we do the LP or LS.

-------------------------------------------------------------------------------
# SLb-kv-5.0
Try to estimate the number of remaining iterations in -mt 11
As in doi.org/10.1007/s10898-011-9771-5.
We store las three values of the new centroids to guess the remaining
number of iterations. If they are more than NPoints, we quit.
Stored values are for lower and upper bounds, so the min of both deternime 
the remaining number of iterations.


-------------------------------------------------------------------------------
# SLb-kv-4.9
Heuristics were not so good.
So, lets try a local search 

-mt 10: for Neg/Pos Dir. Der. towards a facet, by evaluating
the centre direction and remove the vertex with more positive/negative Dir. Der.
This fails in some cases in comparison with -mt 5 CV+LP (see THCB).

-mt 11: Check the new centroids, removing point i and store the best and
point i and worse centroids are removed.
This works but sometimes the number of iterations have to be large.


-------------------------------------------------------------------------------
# SLb-kv-4.8

In Heuristics the heuristic postivie and heuristic negative can be evlauted at once
because PerPos2=PerNeg1

-------------------------------------------------------------------------------
# SLb-kv-4.7

I coded three heuristic methods based on dir. der vi-vj and interpolation.
 * GetDDAvgPointDDInF: use DirDer in the facet. 
 * GetDDAvgPointDDVEdges: use Dir Der from v. 
 * As Before but initial points are facet vertices and their pos or neg were updated.
 
 best is the first.
 

-------------------------------------------------------------------------------
# SLb-kv-4.6
Reorder 
 * pCounters
 * -mt 
 
Add bounding box for new:
 * -mt 4 //LP
 * -mt 6 //Aligned vertices
 * -mt 7 //Heuristic

Heuristic Directional Derivatives base on directional derivatices at the facet.
Percentages per edge are calculated supposing edge lenght 1 and with z anf f(z) as in 
DOI: 10.1023/A:1022512411995


-------------------------------------------------------------------------------
# SLb-kv-4.5
Heuristic directional vector based ob directional derivatives from vertex to vertex.
(-mt 5) dir. der have to be stored.



-------------------------------------------------------------------------------
# SLb-kv-4.4

added:
 * -mt 7 : use -mt 5 and if it not success then -mt 2.

LP returns as one NegGrad is found.
If Lp could not be solved:
 *  the simplex is devided or 
 * the dir. deriv for the facet contains 0. 

-------------------------------------------------------------------------------
# SLb-kv-4.3

-mt 
 * 5 vi-center + vi-vj
 
 Later on try to order howto visit vertices.
-------------------------------------------------------------------------------
# SLb-kv-4.2

-mt
  * 1 v-c
  *	2 LP
  * 3 LP scaled S
  * 4 all v-v -> least to more significant ZeroIn, Pos, Neg Dir, Deriv.
  * 5 3+4
  * 6 Heuristic 5 only for vertices at max{xi} if G is negative or at min{xi} if G is positive. 

pnl output precision is in  pnl-1.10.4/src/optim/lp_solve/lp_report.c
void REPORT_lp(lprec *lp)
from %8g to %12g.

Try to avoid pnl "Unacceptable accuracy found (worse than required 5e-07)"
Changue lp_lib.c at  pnl-1.10.4/src/optim/lp_solve line 1493 to comment and uncomment  line 1489
set_break_numeric_accuracy(lp, DEF_INFINITE); 

Libraries required:
kv: http://verifiedby.me/kv/ (used 0.4.50) Just copy or ln -s kv-0-4-50 ~/kv

PNL: https://pnlnum.github.io/pnl/ (used 1.10.4) 
  Download to a temporal directory from: https://pnlnum.github.io/pnl
  mkdir build
  cd  build
  cmake -DWITH_MPI=OFF -DCMAKE_BUILD_TYPE=Release -DPNL_INSTALL_PREFIX=/home/leo/pnl-1.10.4 ..
  make
  make install
  Just copy or ln -s pnl-1.10.4 ~/pnl
Example: See Run*.bat

Other LP libraries:
https://www.math.unipd.it/~michela/software.html
GLPK
CDD
-------------------------------------------------------------------------------
# SLb-kv-4.1
We can have as imput regular simplices->
NVertices=NDim.
The initial simplex is a reduced one NVertices=NDim < NDim+1

CtD.SInBox is now CtD.SInSim
CtD.SInSim=0 -> feasible region is a Box
CtD.SInSim=1 -> feasible region is a n-simplex
CtD.SInSim=2 -> feasible region is a regular simplex



-------------------------------------------------------------------------------
# SLb-kv-4.0
Taken from 3.5

Implement the ideas in article.


-------------------------------------------------------------------------------
# SLb-kv-3.6
Normal vectors
https://es.wikipedia.org/wiki/Proceso_de_ortogonalizaci%C3%B3n_de_Gram-Schmidt


-------------------------------------------------------------------------------
# SLb-kv-3.5

Just to get directional interval gradients from centroid of ghe simplex instead of 
each centroid of a facet of the simplex.



--------------------------------------------------------------------------------
# SLb-kv-3.4


#Graphical output colors:
Box:
   Blackedges: 0\in G_i 
   Blue Edges: ub(G_i) < 0 ->  decrease as x_i increases (negative right or up)
   Red  Edges: lb(G_i) > 0 -> increases as x_i increases (negative left or down)

Directional gradient arrows:
  Black: 0\in G
  Red  : G decreasing to the face
  Blue : G increasing to the face

Simplex fill colors:
   #c08040 (brown): RangeUp test.
   #80ff80 (light green): reduced to facet 
   #00e000,(green) monotonous and interior 
   #008000, (dark green): monotonous with border facet and rejected.
   #806080, (purple): cutoff test.
   #008080, (blue-green): Reduction NegGrad.

Simplex border color:
   purple: selected.
   red   : reduced and pending of evaluation


#TODO:

Calls dependencies: Now Test for SInBox is different than !SInBox
TestSimplex -> 
 --
 ReduceSInBox:
    RemainingVerticesSInBox
    	Count and list vertices at limits with negative gradient.
    ReducedSInBoxAddV (in simplex.cpp):
		Generate new simplex with just those vertices. 
		UpdateIsBorderFacetSInBox:
			Update pIsBorderFacet.
   EvalSimplex.
 --	
 ReduceSInSimplex:
	GetDirGradTypeOnFacets: 
		GetDirGradTypeF: returns if facet has
					NegGrad  	2
					PosGrad		3
					ZeroInGrad	4	
	...


#TODO en ficheros
	simplex.cpp.
          InitSimplex() Se usa pIsBorderFacet en SInBox?
	  NewFacetRem1Vertex(): Rellabelling
	text.cpp: 
	  ReduceToFacets():how to mix vertices. 


Libraries required:
kv: http://verifiedby.me/kv/ (used 0.4.50) Just copy or ln -s kv-0-4-50 ~/kv

PNL: https://pnlnum.github.io/pnl/ (used 1.10.4) 
  Download to a temporal directory from: https://pnlnum.github.io/pnl
  mkdir build
  cd  build
  cmake -DWITH_MPI=OFF -DCMAKE_BUILD_TYPE=Release -DPNL_INSTALL_PREFIX=/home/leo/pnl-1.10.4 ..
  make
  make install
  Just copy or ln -s pnl-1.10.4 ~/pnl
Example: See Run*.bat

##Working
Check labels of vertices determining border faces after reduction.
Label by division are right: The new vertex get the label of the other vertex in the edge and that other vertex is set to non-border.

After reduction to facet:
	 Border vertices remains as border. 
	 Non-boder vertices have to check if the opposite facet with n-1 vertices has at least (n-2)(n-3)/2+1 border edges. In such a case the non-border vertex is relabelled  as border.
	 We will use one vector:
	 OrigEdOfV: Store the number of the border edge the vertex is on
	 No more than two vertex can be in the same edge.
	 To know the number of edges at border we have to count the occurrence of pairs in OrigEdOfV.
	 Initial vertices belongs to several edges because they are power of 2.
	 To know if a number x is power of two  x&(x-1)==0
	 For them, we have to do v_ini | v = v to know they are in the same edge. 
#TODO: Memory can save by storing how many vertices are at border and their border instead of the border of them all.

#TODO: In a reduction of a simplex, each vertex to reduce produce a new facet using NewFacetRem() We have to deal with the reduction of all at the same time.	   
	   
	   

##TODO
3.4.0 If directional derivative from vertex to cener of the facet is <=0 we do not have to check more facets. See  HasSReducedFacets in test.cpp
3.3.0 "FreeVertex:Vertex shared by" in LPSim 
3.0.1 Count how many Simplex reduction were done.
3.0.2 move PREAL to ub::vector <double> rVector.
3.3.3 -f20 -i 1 produces FreeVertex error. 
3.3.4 see results -f 20 -i 6 
2.0.3 Create a structure POINTS to hold temporal points.
1.5.1 Best directional derivatives.

--------------------------------------------------------------------------------
# SLb-kv-3.3

Example: See Run*.bat

##Working
If directional derivative from vertex to cener of the facet is <=0 we do not have to check more facets. See  HasSReducedFacets in test.cpp

##TODO:

3.3.0 "FreeVertex:Vertex shared by" in LPSim 
3.0.1 Count how many Simplex reduction were done.
3.0.2 move PREAL to ub::vector <double> rVector.
3.3.3 -f20 -i 1 produces FreeVertex error. 
3.3.4 see results -f 20 -i 6 
2.0.3 Create a structure POINTS to hold temporal points.
1.5.1 Best directional derivatives.




--------------------------------------------------------------------------------
# SLb-kv-3.2

Example: See Run*.bat

When center or bauman points in Box constraint search región is used, simplex vertices are not evaluated.
Anyway they are stored due to sharing.
Gradient is not evaluated on vertices (=points)
LP methods store/evaluate the vertices of boxes.


Add new lower bounds using centered form:
-i 5: Using as c the vertex whith the highest f value.


--------------------------------------------------------------------------------
# SLb-kv-3.1

Example: See Run*.bat

Added: -i 5 = centered form at simplex with box gradients.

##TODO:
3.1: Add New inclusion functions using centered and Baumann simplex points.
3.0.1 Count how many Simplex reduction were done.
3.0.2 move PREAL to ub::vector <double> rVector.
2.0.3, 
1.5.1

--------------------------------------------------------------------------------
# SLb-kv-3.0

C-xsc library has been completely removed.
Now only kv 0.4.50 libraries are used for IA.
Just install them in ~/kv directory from http://verifiedby.me/kv/
PNL 1.10.4 is also used.
Download to a temporal directory from: https://pnlnum.github.io/pnl
mkdir build
cd  build
cmake -DWITH_MPI=OFF -DCMAKE_BUILD_TYPE=Release -DPNL_INSTALL_PREFIX=/home/leo/pnl ..
make
make install

Example: See Run*.bat

Done: Use XLim to Draw and InitBox for search region in a box.

Note: gdb: break exit. to put a breakpoint in exit and see the bt before exit.

Done: Provide to Fred a simple code that evaluates Ia and AA over a simplex for time comparison with Ibex.
 
Done: Check why I run out of simplices for SLb-kv-3.0 -s SearchRegions/BoxMichal5.txt -a 1e-6 -f 16 -i 0
Using REAL_Prec 1e-14 I got:
ExtractNodeEqual: root=NULL
[-3.3007758036, -0.0000000385].
With REAL_Prec 1e-16 or directly a==b it works. 
 
Done: Put a flag to perform monotonicity test or not.
 
* Count the number or reduction of a simplex, and fulfilled rejection tests. RangeUp, Monotonicity,Cutoff.

* What to do with diam(x)=0 in AA (Affine Arithmetic).


To See: http://verifiedby.me/kv/rounding/index.html
-O3 -DKV_FASTROUND
 O3 -DKV_USE_AVX512 -mavx512f //No on my laptop.
kv has some #ifdef _OPENMP.
PNL detect MPI (not installed).

##Using gprof
compile with -pg 
execute <it>: it generates gmon.out

##TODO:
3.0.1 Count how many Simplex reduction were done.
3.0.2 move PREAL to ub::vector <double> rVector.
3.0.0
2.0.3, 
1.5.1
1.3.5

--------------------------------------------------------------------------------
# SimplexLB-3.0

Example: See Run*.bat

Done: adding lower bounf by affine Arithmetic on a simplex: -i 4
There is an overhead by moving from cxsc ivector (box) to kv itv (box).

kv AFFINE_SIMPLE =2 in affine.hpp because it add the dummy and error coef.
AFFINE_MULT=0, higher values results in run out of simplices.
Division by 0 is not handled. See Shekel functions.


TODO:
3.0.0: Remove C-XSC and use Kv interal alrithmetic.
2.0.3, 
1.5.1
1.3.5

--------------------------------------------------------------------------------
# SimplexLB-2.0
Example: See Run*.bat

The parameter -iw IncWidth is added.
Then the centered from, LR and LR-S are evaluated only if w(S)<=IncWidth. 

Working: 
2.1.0: Set a w(S) from where -i [1..3] is applied.
Count how many times where applied.


##TODO 
2.0.3, 
1.5.1
1.3.5

--------------------------------------------------------------------------------
# SimplexLB-2.0
Example:

./SimplexLB-2.0 -f 5 -s SearchRegions/SimplexFred.txt -a 1e-1 -i 2 -tcl 3 -w 800 | ./WinZoom.tcl

Done: 1.9.1.
Done 1.8.1: Combinatorial vertex triangulation of an hypre-rectangle.
XLim used for Draw it willl be also the Init Box. 
Done: 2.0.1: If search region= Box, evaluated vertices of a box improve the incumbent and are stored depending on -rv.
If Search region=Simplex, evaluated vertices of a box do not improve incumbent and are not stored.
Done 2.0.2: If search region=Box and monotonous. Check if the border is in the monotonous decreasing direction. Otherwise, reject. 
Done 2.0.4: Add test functions:
	*https://www.sfu.ca/~ssurjano/optimization.html
	*Soft/bb/C-XSC-Soft/JaGrow-1.0.5/funcion.C

##TODO
2.0.3: Create a structure POINTS to hold:
ppInitPoints
ppTPoints
ppTVertices
pTIndVert
1.5.1: Bogi's directional derivatives, 
1.3.5: (Blas & CBlas).

##Warnings
For parallel version:
*static variables should be delared as volatie and writed in exclusive way.


--------------------------------------------------------------------------------
# SimplexLB-1.9
Example:

./SimplexLB-1.9 -f 5 -s SearchRegions/SimplexFred.txt -a 1e-1 -i 2 -tcl 3 -w 800 | ./WinZoom.tcl

Done: Fred's LP LR-Lambda to improve lower bound with -i 3.


##TODO
1.9.1: Put LP routines in other file.
1.8.1: Combinatorial vertex triangulation of an hypre-rectangle.
1.5.1: Bogi's directional derivatives, 1.3.5(Blas & CBlas).
##Warnings
For parallel version:
*static variables should be celared as volatie and writed in exclusive way.
  

--------------------------------------------------------------------------------
# SimplexLB-1.8
Example:

./SimplexLB-1.8 -f 5 -s SearchRegions/SimplexFred.txt -a 1e-1 -i 2 -tcl 3 -w 800 | ./WinZoom.tcl

Coded Fred's LP LR to improve the lower bound with -i 2
C-XSC LinOpt does not help.
I decide to use PNL https://pnlnum.github.io/pnl/ which is thread safe which pnl_optim_linprog is a wrapper to LPsolve. 

##TODO
1.8.1: Combinatorial certex triangulation of an hypre-rectangle.
1.5.1: Bogi's directional derivatives, 1.3.5(Blas & CBlas).
--------------------------------------------------------------------------------
# SimplexLB-1.7
Example:

SimplexLB-1.7 -f 5 -s Simplices/SimplexFred.txt -a 1e-1 -i 1 -tcl 3 -w 800 | VentanasZoom.tcl

Done 1.6.1: To reduce the procedures parameters by joining related ones in a structure. 
I use struct ConstData (see utils.h) for common parameters.
I use struct iBOXES with two temporal ivectors Box1 and Box2
In main: 
*counters are in pCounters
*ppTPoints is a vertor of 2 temporal points (vector of doubles)
*ppTVertices is a vector of two vertices. ppTVertices[0] is the incumbent.
*TrVector is a rvector for compatibility with CXSC. See centered form in Evalsimplex.


##TODO
TODO 1.6.2, 1.5.1, 1.3.5


--------------------------------------------------------------------------------
# SimplexLB-1.6
Example:

SimplexLB-1.6 -f 3 -s Simplices/SimplexEligius.txt -a 0.1 -tcl 3 -w 800 | VentanasZoom.tcl

Done TODO 1.3.1: bts can be sorted by F directly, using min Inf(F) as first criterium and min Sup(F) as second. In this way the list in a node will have less elements (those with same F) resulting in a quiquier insertion. 

Done TODO: 1.5.2 use centered form. New parameter -i is used to activate centered form. The center evaluation could update the incumbent, but it is not stored in the BTV. 


##TODO
1.6.1 join common data in structures to reduce the number of parameters to procedures.
1.6.2 ChecK Fred's LP to improve the lower bound.
1.5.1 Check the bogi's idea of best directional derivatives.


--------------------------------------------------------------------------------
# SimplexLB-1.5
Example:

SimplexLB-1.5 -f 3 -s Simplices/SimplexEligius.txt -a 0.1 -tcl 3 -w 800 | VentanasZoom.tcl
We draw the directional derivatices: black 0in, red decreasing, blue increasing. 
Only form the opposite vertex to the centre of the facet is checked.

We reduce to facets when directional drivative is not possitive.
For facets with just 2 vertives only one direction has to be and is checked. 


##TODO: 

1.5.1 Check the bogi's idea of best directional derivatives.
1.5.2 use centered form
See TODO 1.3.1.
See TODO 1.2.2.

--------------------------------------------------------------------------------
# SimplexLB-1.4
Example:

SimplexLB-1.4 -f 3 -s Simplices/SimplexEligius.txt -a 0.1 -tcl 3 -w 800 | VentanasZoom.tcl 

For simplices having NDim+1 vertices,
If the simplex is inside the initial, IsBorder=False because all facets were inner and then pIsBorderFacet is freed to NULL. Otherwise each element i of the *pIsBorderFacet show if the facet removing vertex i is at the border or not. It is updated in the division: The possition of the new vertex has the lavel of the possition of the vertex in the bisected longest edge that is in the other subsimplex and after that the pIsBortherFacet for old positions of vertices of the bisected longest edge are set to False.

## TODO
1.4.1: We have BOOL with True and False, when in C++ the same bool and true and false exists.
1.4.2: If f is monotonous on S and has border facets we have to check if them are in monotonous decreasing direction. If they do not, the simplex is rejected.  Instead of TODO 1.3.4, we will check just one direction v_ic, where c is the centroid of the facet removing v_i. if the inner product of vic * F' is a positive interval, the facet can be removed, otherwise it is stored for further processing.

See TODO 1.3.1.

--------------------------------------------------------------------------------
# SimplexLB-1.3
Example:

SimplexLB-1.3 -f 3 -s Simplices/SimplexFred.txt -a 0.1 -tcl 3 -w 800 | VentanasZoom.tcl 

VSee GSL for Ax=b linear systems of equations and 
GLPK for Linear Programming.
C-XSC ToolBox also has 
Linear systems of equations, module Linsys; lss and 
Linear Optimization. See http://www2.math.uni-wuppertal.de/wrswt/xsc/cxsc_software.html#cxsc-toolbox 


TODO 1.2.6 done! More vertices are evaluated if removed.
TODO 1.2.5 done! Now a simplex and vertex is drawn when it is evaluated.
A simplex as lines and a vertex in Yellow.
When they are freed, the simplex is draw filled by the correspondig color and the vertex turn on gray.



## TODO:
1.3.1: bts can be sorted by F directly, using min Inf(F) as first criterium and min Sup(F) as second. In this way the list in a node will have less elements (those with same F) resulting in a quiquier insertion.
1.3.2: XLim and WWidth do not chague and they can be put on an structure.
1.3.4: Determine if a facet is border at a given direction:
       To solve if a facet V is at a border:
       Solve W*L=V, 
       With W a nx(n+1) inital set of vertices.
       L a (n+1)xm lambda combination of W vertices
       V a (nxm) set of vertices.
       In order to add Sum(col(L))=1 a row of ones is added to W and V.
       
       So, if a row of L is empty, V is at the border of W.
       We can use the baricenter of V=b to determine if the facet is border at a given direction x_i. Wolg let's see the right direction (x1)
       So, solving previous system with 
       W*L=br  
       and br={b1+ep,b2,....,bn,1) and ep a small number ex. 1e-10,
       if L (n+1)x1 has a negative value them br is outside W and V is a right facet at W border.
1.3.5: See  http://www2.math.uni-wuppertal.de/wrswt/xsc/cxsc/apidoc/html/index.html#mainpage_sec_thread      
To activate BLAS and CBLAS.
        


--------------------------------------------------------------------------------
# SimplexLB-1.2
Example:

SimplexLB-1.2 -f 3 -s Simplices/SimplexFred.txt -a 0.1 -tcl 3 -w 800 | VentanasZoom.tcl 

I change Functions.cpp to make it independent from a box: 
Instead of a class BOX, the ivectors:
	+ coordinates intervals 
	+ Function value interval
	+ Gradient value intervals are passed.
Then Box.cpp and Box.hpp are now deleted.

To get track of the incumbent the best vertex is copied in pVIncumb.
Simplices and Vertices counters added in NEvalSimplex and NEvalVertex.

Test.cpp: RangeUp and CuttOff tests added
	
##TODO
1.2.1: group parameters to procedures in a structure
1.2.2: add const to parameters that do not change.
1.2.3: Add monotonicity test.
1.2.4: CuttOffTest does not return the number of simplices removed.
1.2.5: Improve the graphical output.
1.2.6: Check why vertices are not removed when -rv parameter is used.

--------------------------------------------------------------------------------
# SimplexLB-1.1

Example:
SimplexLB-1.1 -f 1 -s Simplices/SimplexKearEx4.txt -a 0.1 -w 800 -tcl 1 | VentanasZoom.tcl

* Done: TODO 1.0.1 temporal PBOX for EvalSimplex and EvalVertex.
* Done: TODO 1.0.2. Now Simplices in the same list (because they have the same Inf(F) ) have been orderer by smaller Sup(F) first. 

* Simplex is draw as lines with its coordinates (vertices). Vertices are drawn independently y yellow. It may be useful to draw vertices with colour defining their gradients.
* We fix the number of graphical windows to 1. I left it open in routines in case it is needed.
* Termination criterion based on the width of the interval with 
[smaller lower bound and the incumbent value] can be checked when the simplex with smaller lower bound is extracted from the BTS.

##Graphical output
* Simplices are drawn when evaluated.
* Vertices are drawn when evaluated.
* Simplices change color when freed.
* Vertices are deleted when freed, but not at the end.
* Boxes: 
	+ Red edge : monotonous decreasing to left  (horizontal) down (vertical) 
	+ Blue edge: monotonous decreasing to right (horizontal) up   (vertical) 

## TODO
* 1.1.1: Counters for Evaluations are not updated. See fGEval* calls.
* Draw Boxes for simplices.

--------------------------------------------------------------------------------
# SimplexLB-1.0:

C-XSC has a problem with exceptions throw throw() routine.
So, headers have to be included with -isystem (see makefile).

C-XSC has to be installed in $(HOME)/cxsc

Functions are enumerated and defined in Problemns.cpp.
DimfProblem() returns the dimension of the function to evaluate.
Simplices are in text files. Currently, in Simplices subdirectory.
In this way different problems can have the same function evaluated on different simplices.

Vertices: are evaluated with Interval Arithmetic and stored in btvertex (no duplicates)

Simplices: are evaluated with Interval Aritmetic and stored in btsimplex by their lower bound. Actually, Inf(F). Those simplices with same lower bound are in the same Btsimplex node, and they are stored in a linked list sorter by simplex size. 

I checked
* The Interval Arithmetic evaluation of vertices and simplex. 
* The insertion and extraction in the binary tree of vertices and simplices.

## TODO: 
* 1.0.1 In EvalVertex() of vertex.cpp, and EvalSimplex() in simplex.cpp:
a BOX is created and destroyed every time it is called. A better solution is to use a pointer to a temporal BOX in main() to save new and Resize operations.
* 1.0.2 An ordering based on sup(F) for simplices with same Inf(F) should be better than by simplex's size in the list for a Btsimplex node. 
* 1.0.3 Add graphical output.
* 1.0.4 To create the test.cpp to 
  + Improve the lower bound SetInf(F)=
  + check if the simplex have to be divided or eliminated



make 2>kk.txt
grep EQ *
  

