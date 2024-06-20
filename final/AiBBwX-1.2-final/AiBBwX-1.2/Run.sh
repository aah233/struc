time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxFred.txt -e 1e-6 -f 3 -i 2 
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxEligius.txt -e 1e-6 -f 3 -i 2 
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxGP.txt -e 1e-6 -f 4 -i 2  #falla
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxTHCB.txt -e 1e-6 -f 5 -i 2 
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxSHCB.txt -e 1e-6 -f 6 -i 2 
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxGriew7.txt -e 1e-6 -f 7 -i 2 #falla
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxShekel.txt -e 1e-6 -f 8 -i 2 
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxHartman3.txt -e 1e-6 -f 9 -i 2 
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxHartman4.txt -e 1e-6 -f 10 -i 2 
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxHartman6.txt -e 1e-6 -f 11 -i 2 
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxLevy8.txt -e 1e-6 -f 12 -i 2 
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxSchubert.txt -e 1e-6 -f 13 -i 2
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxMcCorm.txt -e 1e-6 -f 14 -i 2
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxRS7.txt -e 1e-6 -f 15 -i 2       #falla
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxMichal2.txt -e 1e-6 -f 16 -i 2
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxMichal5.txt -e 1e-6 -f 16 -i 2
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxStybTang2.txt -e 1e-6 -f 17 -i 2
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxStybTang5.txt -e 1e-6 -f 17 -i 2
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxDixonPrice2.txt -e 1e-6 -f 18 -i 2 #falla segmento core
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxDixonPrice5.txt -e 1e-6 -f 18 -i 2
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxAckley5.txt -e 1e-6 -f 24 -i 2

%convex function
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxTrid2.txt -e 1e-6 -f 19 -i 2
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxTrid3.txt -e 1e-6 -f 19 -i 2
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxTrid5.txt -e 1e-6 -f 19 -i 2

%concave function
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxTrid2.txt -e 1e-6 -f 20 -i 2
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxTrid3.txt -e 1e-6 -f 20 -i 2
time timeout 15m AiBBwX-1.2 -s SearchRegions/BoxTrid5.txt -e 1e-6 -f 20 -i 2

#For graphical view of 2D cases add " -tcl 1 | WinZoom.tcl "
AiBBwX-1.2 -s SearchRegions/BoxHartman6.txt -e 1e-6 -f 11 -i 2 
