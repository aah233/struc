time timeout 15m BoxBB-1.1 -s SearchRegions/BoxFred.txt -a 1e-6 -f 3 -i 2 
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxEligius.txt -a 1e-6 -f 3 -i 2 
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxGP.txt -a 1e-6 -f 4 -i 2 
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxTHCB.txt -a 1e-6 -f 5 -i 2 
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxSHCB.txt -a 1e-6 -f 6 -i 2 
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxGriew7.txt -a 1e-6 -f 7 -i 2 
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxShekel.txt -a 1e-6 -f 8 -i 2 
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxHartman3.txt -a 1e-6 -f 9 -i 2
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxHartman4.txt -a 1e-6 -f 10 -i 2 
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxHartman6.txt -a 1e-6 -f 11 -i 2 
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxLevy8.txt -a 1e-6 -f 12 -i 2 
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxSchubert.txt -a 1e-6 -f 13 -i 2
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxMcCorm.txt -a 1e-6 -f 14 -i 2
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxRS7.txt -a 1e-6 -f 15 -i 2
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxMichal2.txt -a 1e-6 -f 16 -i 2
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxMichal5.txt -a 1e-6 -f 16 -i 2
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxStybTang2.txt -a 1e-6 -f 17 -i 2
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxStybTang5.txt -a 1e-6 -f 17 -i 2
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxDixonPrice2.txt -a 1e-6 -f 18 -i 2
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxDixonPrice5.txt -a 1e-6 -f 18 -i 2
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxAckley5.txt -a 1e-6 -f 24 -i 2

%convex function
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxTrid2.txt -a 1e-6 -f 19 -i 2
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxTrid3.txt -a 1e-6 -f 19 -i 2
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxTrid5.txt -a 1e-6 -f 19 -i 2

%concave function
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxTrid2.txt -a 1e-6 -f 20 -i 2
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxTrid3.txt -a 1e-6 -f 20 -i 2
time timeout 15m BoxBB-1.1 -s SearchRegions/BoxTrid5.txt -a 1e-6 -f 20 -i 2

#For graphical view of 2D cases add " -tcl 1 | WinZoom.tcl "