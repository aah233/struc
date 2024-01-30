#!/bin/sh
# the next line restarts using wish \
exec wish "$0" "$@"

proc CreaMarco { w  font font2} {
	global datos ancho alto
	
	frame .win$w.fup -bg White
	label .win$w.fup.tfunction -text "Function =" -font $font -bg White
	label .win$w.fup.function -text $datos(function,.win$w.c) -font $font \
		-bg White
		
	label .win$w.fup.simplex -text $datos(simplex,.win$w.c) -font $font \
		-bg White	
	
	pack  .win$w.fup.tfunction -side left	
	pack  .win$w.fup.function -side left
	pack  .win$w.fup.simplex -side right
	
	
	
	frame .win$w.fbottom -bg White
	label .win$w.fbottom.talpha -text "a =" -font $font -bg White
	label .win$w.fbottom.alpha  -text $datos(alpha,.win$w.c) -font $font \
		-bg White
	label .win$w.fbottom.tmethod -text "method =" -font $font -bg White
	label .win$w.fbottom.method  -textvariable datos(method,.win$w.c) -font $font \
		-bg White
	label .win$w.fbottom.tnsimplex -text "NSimplex =" -font $font -bg White
    label .win$w.fbottom.nsimplex -textvariable datos(nsimplex,.win$w.c) -font $font \
		-bg White	

	pack  .win$w.fbottom.talpha -side left
	pack  .win$w.fbottom.alpha -side left
	pack  .win$w.fbottom.tmethod -side left
	pack  .win$w.fbottom.method -side left
	pack  .win$w.fbottom.nsimplex -side right
	pack  .win$w.fbottom.tnsimplex -side right


	frame .win$w.fbottom1 -bg White
	label .win$w.fbottom1.tlb -text "lb =" -font $font -bg White
	label .win$w.fbottom1.lb  -textvariable datos(lb,.win$w.c) -font $font \
		-bg White
	label .win$w.fbottom1.tub -text "ub =" -font $font -bg White
	label .win$w.fbottom1.ub  -textvariable datos(ub,.win$w.c) -font $font \
		-bg White

	pack  .win$w.fbottom1.tlb -side left
	pack  .win$w.fbottom1.lb -side left
	pack  .win$w.fbottom1.tub -side left
	pack  .win$w.fbottom1.ub -side left


	frame .win$w.botones -bg white
	button .win$w.botones.salida -text Exit -command exit
	button .win$w.botones.postscript -text Postscript \
	       -command "FicheroPostscript $w"
	#Poner comillas para que tome las variables de cuando se creo el boton
	button .win$w.botones.continuar -text Next \
		-command "incr datos(Sigue,.win$w.c)"

	pack .win$w.botones.salida \
	     .win$w.botones.postscript \
	     .win$w.botones.continuar -side left -fill x -expand true
	
	
	canvas .win$w.c -width $ancho -heigh $alto -bg Gray80 -borderwidth 0 \
		-highlightthickness 0        
	
	
	pack .win$w.fup -side top -fill x 
	pack .win$w.c -side top
	pack .win$w.fbottom -side top -fill x 
	pack .win$w.fbottom1 -side top -fill x
	pack .win$w.botones -side bottom -fill x
}


proc FicheroPostscript { w } {
global datos
.win$w.c postscript -file \
f$datos(function,.win$w.c)-$datos(simplex,.win$w.c)-$datos(alpha,.win$w.c).ps 
#puts "f$datos(function,.win$w.c)-$datos(Sigue,.win$w.c).ps"
}


proc Mayor { x y } {
 if { $x < $y } {
    return $y
 }
 return $x
}

proc Menor { x y } {
 if { $x < $y } {
    return $x
 }
 return $y
}

proc BoxInit {c} {
  bind $c <Button-1> {BoxBegin %W %x %y}
  bind $c <B1-Motion> {BoxDrag %W %x %y}
  bind $c <B1-ButtonRelease> {BoxEnd %W %x %y}
  bind $c <Button-3> {BoxUnZoom %W}
}

proc BoxBegin { w x y } {
	global box
	
	set box(anchor,$w) [list $x $y]
	catch {unset box(last,$w)}
}

proc BoxDrag { w x y } {
	global box
	
	catch {$w delete $box(last,$w)}
	set x0 [lindex $box(anchor,$w) 0]
	set y0 [lindex $box(anchor,$w) 1]
	set dist [Mayor [expr abs($x0-$x)] [expr abs($y0-$y)]]
	set x1 [expr $x0 - $dist]
	set x2 [expr $x0 + $dist]
	set y1 [expr $y0 - $dist]
	set y2 [expr $y0 + $dist]
	set box(last,$w) [eval {$w create rect} {$x1 $y1 $x2 $y2 -tag box \
	-outline red}]
}


proc BoxEnd { w x y } {
  global box Zoom ZLevel

  catch {$w delete $box(last,$w)}
 
  set dist [Mayor [expr abs ([lindex $box(anchor,$w) 0]-$x)] \
                  [expr abs ([lindex $box(anchor,$w) 1]-$y)]]
 
  if {$dist > 10} { 
 
     set ZLevel($w) [expr $ZLevel($w) +1]

     set Zoom(xmed,$ZLevel($w),$w) [lindex $box(anchor,$w) 0]
     set Zoom(ymed,$ZLevel($w),$w) [lindex $box(anchor,$w) 1]
     set x1 [expr $Zoom(xmed,$ZLevel($w),$w) - $dist]
     set x2 [expr $Zoom(xmed,$ZLevel($w),$w) + $dist]
     set y1 [expr $Zoom(ymed,$ZLevel($w),$w) + $dist]
     set y2 [expr $Zoom(ymed,$ZLevel($w),$w) - $dist]

   #New ancho and new alto
   #Factor x e y es la proporcion entre la ventana inicial y la nueva.
     set Zoom(ancho,$ZLevel($w),$w)  [expr abs ($x2 - $x1)]
     set Zoom(alto,$ZLevel($w),$w)   [expr abs ($y2 - $y1)]
     set factorx \
         [expr $Zoom(ancho,0,$w).0 / $Zoom(ancho,$ZLevel($w),$w).0]
     set factory \
         [expr $Zoom(alto,0,$w).0 / $Zoom(alto,$ZLevel($w),$w).0]

   #desplazamiento en x y en y de los datos ya escalados
     set Zoom(xdesp,$ZLevel($w),$w) \
         [expr $Zoom(xmed,0,$w) - $Zoom(xmed,$ZLevel($w),$w)]
     set Zoom(ydesp,$ZLevel($w),$w) \
         [expr $Zoom(ymed,0,$w) - $Zoom(ymed,$ZLevel($w),$w)]


     $w scale all $Zoom(xmed,$ZLevel($w),$w) \
                  $Zoom(ymed,$ZLevel($w),$w) $factorx $factory 
     $w move  all $Zoom(xdesp,$ZLevel($w),$w) \
                  $Zoom(ydesp,$ZLevel($w),$w)

     catch {$w delete text}
     $w create text 30 10 -text "Zoom $ZLevel($w)" -fill Red -tag text

     update idletask
  }   
}

proc BoxUnZoom {w} {
  global box Zoom ZLevel
 
  catch {$w delete text} 
 
  if { $ZLevel($w) > 0 } { 
     set factorx \
         [expr $Zoom(ancho,$ZLevel($w),$w).0 / $Zoom(ancho,0,$w).0]
     set factory \
         [expr $Zoom(alto,$ZLevel($w),$w).0 / $Zoom(alto,0,$w).0]

     $w scale all $Zoom(xmed,0,$w) $Zoom(ymed,0,$w) $factorx $factory
     $w move  all \
        [expr -1.0 * $Zoom(xdesp,$ZLevel($w),$w)] \
	[expr -1.0 * $Zoom(ydesp,$ZLevel($w),$w)]

     set ZLevel($w) [expr $ZLevel($w) -1]
     
     if { $ZLevel($w) > 0 } {
        $w create text 30 10 -text "Zoom $ZLevel($w)" -fill Red -tag text
     }
  }   
}

proc ObjectZoom { w objeto } {
  global box Zoom ZLevel
 
  if { $ZLevel($w) > 0 } {
     for { set i 1 } {$i <= $ZLevel($w) } {incr i} { 
	 set factorx [expr $Zoom(ancho,0,$w).0 / $Zoom(ancho,$i,$w).0]
	 set factory [expr $Zoom(alto,0,$w).0 / $Zoom(alto,$i,$w).0]
	 $w scale $objeto $Zoom(xmed,$i,$w) $Zoom(ymed,$i,$w) \
	    $factorx $factory 
	 $w move  $objeto $Zoom(xdesp,$i,$w) $Zoom(ydesp,$i,$w)
     }	 
  }   

}



##############         PINCIPAL       #################
set tcl_precision 10

gets stdin ancho
gets stdin alto

set font -*-fixed-*-*-*-*-*-[expr $ancho / 8 + [expr $ancho / 4 % 10] ]-*-*-*-*-*-* 
set font2 -*-symbol-*-*-*-*-*-[expr $ancho / 6 + [expr $ancho / 2 % 10]]-*-*-*-*-*-*  

gets stdin NWin
gets stdin Algo
gets stdin alpha


for {set w 0} {$w<$NWin} {incr w} {	
	toplevel .win$w
	wm title .win$w              $Algo
	wm iconname .win$w           $Algo
	set datos(alpha,.win$w.c)    $alpha
	gets stdin function
	set datos(function,.win$w.c) $function
	gets stdin simplex
	set datos(simplex,.win$w.c)  $simplex
	set datos(Sigue,.win$w.c)    0
	set datos(nsimplex,.win$w.c) nan 
	set datos(method,.win$w.c)   nan
	set datos(lb,.win$w.c)   nan
	set datos(ub,.win$w.c)   nan

	CreaMarco  $w $font $font2
       
	set ZLevel(.win$w.c) 0
	
	set Zoom(ancho,$ZLevel(.win$w.c),.win$w.c) $ancho
	set Zoom(alto,$ZLevel(.win$w.c),.win$w.c) $alto 
	set Zoom(xmed,$ZLevel(.win$w.c),.win$w.c) [expr $ancho.0/2.0] 
	set Zoom(ymed,$ZLevel(.win$w.c),.win$w.c) [expr $alto.0/2.0] 
}

#Solo al -c para que los botones no cojan el bind.
for {set w 0} {$w<$NWin} {incr w} {
	BoxInit .win$w.c
}

update idletask

if { $NWin>1 } {
    set wold 0
    .win$wold.c configure -background bisque1
}

while { ( 0 < [ gets stdin w ] )} {
      if { $NWin> 1 && $wold != $w } {
          catch {.win$wold.c configure -background gray80}
          .win$w.c configure -background bisque1
          set wold $w
         }
    gets stdin accion 
    switch $accion {
        "DrawPolygon" { 
		    gets stdin NPoints
			set Points {}
			for {set i 0} {$i < $NPoints} {incr i} {
				gets stdin x1
				gets stdin y1
			lappend Points $x1 $y1
			}
		    gets stdin color
		    gets stdin NPoly
            
            set datos(npoly,.win$w.c) $NPoly
            update idletask

		    catch { .win$w.c delete Poly$NPoly }
		    .win$w.c create polygon $Points \
		    -fill "" -outline $color -width 3 -tag Poly$NPoly 
		    
		    ObjectZoom .win$w.c Poly$NPoly
		    .win$w.c addtag Poly withtag Poly$NPoly

#		    tkwait variable datos(Sigue,.win$w.c)
            update idletask 
	}
        "DelPolygon" {
            gets stdin NPoly
            catch { .win$w.c delete Poly$NPoly}
#		   tkwait variable datos(Sigue,.win$w.c)
            update idletask
	}
        "DrawTriangle" { 
		    gets stdin x1
		    gets stdin y1
		    gets stdin x2
		    gets stdin y2
		    gets stdin x3
		    gets stdin y3
		    gets stdin colorIn
		    gets stdin NTrian
            
            set datos(nsimplex,.win$w.c) $NTrian
            update idletask

		    catch { .win$w.c delete Trian$NTrian }
		    .win$w.c create polygon $x1 $y1 $x2 $y2 $x3 $y3 $x1 $y1\
		     -fill $colorIn -outline Black -width 3 -tag Trian$NTrian 
		    
		    ObjectZoom .win$w.c Trian$NTrian
		    .win$w.c addtag Trian withtag Trian$NTrian

		    catch {.win$w.c raise Poly Trian}
		    catch {.win$w.c raise Point Trian}
		    catch {.win$w.c raise Line Trian}
            catch {.win$w.c raise Arrow Trian}
            catch {.win$w.c raise DirDer Trian}
#		    tkwait variable datos(Sigue,.win$w.c)
            update idletask 
	}
        "DelTriangle" {
            gets stdin NTrian
            catch { .win$w.c delete Trian$NTrian }
#		   tkwait variable datos(Sigue,.win$w.c)
            update idletask
	}
	
    "DrawLineTriangle" {
		    gets stdin x1
		    gets stdin y1
		    gets stdin x2
		    gets stdin y2
		    gets stdin x3
		    gets stdin y3
		    gets stdin Color
		    gets stdin NTrian

            set datos(nsimplex,.win$w.c) $NTrian
            update idletask

		    catch { .win$w.c delete LineTrian$NTrian }
		    .win$w.c create line $x1 $y1 $x2 $y2 $x3 $y3 $x1 $y1\
		     -fill $Color -width 3 -tag LineTrian$NTrian
		     

		    ObjectZoom .win$w.c LineTrian$NTrian

		    .win$w.c addtag LineTrian withtag LineTrian$NTrian
		    catch {.win$w.c raise Poly LineTrian}
		    catch {.win$w.c raise Point LineTrian}
		    catch {.win$w.c raise BOX LineTrian}
            catch {.win$w.c raise Arrow LineTrian}
            catch {.win$w.c raise DirDer LineTrian}
            update idletask
	}
	"ColorLineTriangle" {
	       gets stdin NTrian
           set datos(nsimplex,.win$w.c) $NTrian 
           update idletask
	       gets stdin color
		   .win$w.c itemconfigure LineTrian$NTrian -fill $color
		    
            .win$w.c addtag LineTrian withtag LineTrian$NTrian 

		   catch {.win$w.c raise Poly LineTrian}
		   catch {.win$w.c raise LineTrian$NTrian LineTrian}
           catch {.win$w.c raise LineTrian$NTrian LineTrian}
		   catch {.win$w.c raise Arrow LineTrian}
		   catch {.win$w.c raise DirDer LineTrian}
		   update idletask 
	}
    "DelLineTriangle" {
           gets stdin NTrian
           set datos(nsimplex,.win$w.c) $NTrian 
           update idletask
           catch { .win$w.c delete LineTrian$NTrian }
           catch { .win$w.c delete LineTrianV1$NTrian }
           catch { .win$w.c delete LineTrianV2$NTrian }
           catch { .win$w.c delete LineTrianV3$NTrian }
#		   tkwait variable sigue
           update idletask
	}	
	
	
    "DrawLine" { 
		    gets stdin x1
		    gets stdin y1
		    gets stdin x2
		    gets stdin y2
		    gets stdin colorIn
		    gets stdin NLine
		    .win$w.c create line $x1 $y1 $x2 $y2 \
		     -fill $colorIn -width 3 -tag Line$NLine
		    
            set datos(nsimplex,.win$w.c) $NLine 

		    ObjectZoom .win$w.c Line$NLine
		    
		    .win$w.c addtag Line withtag Line$NLine
		    
            catch {.win$w.c raise Poly Line}
            catch {.win$w.c raise Arrow Line}
		    catch {.win$w.c raise Point Line}
			catch {.win$w.c raise DirDer Line}
#		    tkwait variable datos(Sigue,.win$w.c)
            update idletask 
	}
	"ColorLine" {
	        gets stdin NLine
	        gets stdin color
		    .win$w.c itemconfigure Line$NLine -fill $color

            set datos(nsimplex,.win$w.c) $NLine  
		    
		    #catch {.win$w.c raise Line$NLine all}
		    catch {.win$w.c raise Poly Line}
		    catch {.win$w.c raise Arrow Line}
		    catch {.win$w.c raise DirDer Line}
		    update idletask 
	}	
    "DelLine" {
            gets stdin NLine
            catch { .win$w.c delete Line$NLine }

           set datos(nsimplex,.win$w.c) $NLine  

#		   tkwait variable datos(Sigue,.win$w.c)
            update idletask
	}		
    "DrawArrow" { 
		    gets stdin x1
		    gets stdin y1
		    gets stdin x2
		    gets stdin y2
		    gets stdin colorIn
		    gets stdin NArrow
		    .win$w.c create line $x1 $y1 $x2 $y2 \
		     -fill $colorIn -width 3 -arrowshape {8 8 6} -arrow last -tag Arrow$NArrow
		    
		    ObjectZoom .win$w.c Arrow$NArrow
		    
            .win$w.c addtag Arrow withtag Arrow$NArrow 
            catch {.win$w.c raise Arrow all}
		    #catch {.win$w.c raise Point Arrow$NArrow}
            update idletask 
	}
    "DelArrow" {
                   gets stdin NArrow
                   catch { .win$w.c delete Arrow$NArrow }
                   update idletask
	}
    "DrawDirDer" { 
		    gets stdin x1
		    gets stdin y1
		    gets stdin x2
		    gets stdin y2
		    gets stdin colorIn
		    gets stdin NDirDer
		    gets stdin lb
		    gets stdin ub
		    .win$w.c create line $x1 $y1 $x2 $y2 \
		     -fill $colorIn -width 4 -arrowshape {10 10 7} \
		     -arrow last -tag DirDer$NDirDer
		    
		    ObjectZoom .win$w.c DirDer$NDirDer
		    
            .win$w.c addtag DirDer withtag DirDer$NDirDer 
            catch {.win$w.c raise DirDer all}
#		    #catch {.win$w.c raise Point DirDer$NDirDer}
		    set datos(lb,.win$w.c) $lb
		    set datos(ub,.win$w.c) $ub
            update idletask 
	}
    "DelDirDer" {
                   gets stdin NDirDer
                   catch {.win$w.c delete DirDer$NDirDer }
                   update idletask
	}		
    "DrawPoint" { 
		    gets stdin x1
		    gets stdin y1
		    gets stdin color
		    gets stdin NPoint
		    set border black
		    
		    set Point [.win$w.c find withtag Point$NPoint]
		    if { [llength $Point] == 0 } {
		    .win$w.c create rect [expr $x1-3] [expr $y1-3] \
		    [expr $x1+3] [expr $y1+3]  -fill $color \
		    -width 1 -fill $color -outline $border \
		    -tag Point$NPoint

			ObjectZoom .win$w.c Point$NPoint
			
			.win$w.c addtag Point withtag Point$NPoint 
		    catch {.win$w.c raise Point$NPoint all}
		    catch {.win$w.c raise DirDer Point}
#			tkwait variable datos(Sigue,.win$w.c)
                    }
            #unset Point$NPoint
            update idletask 
	}
	"ColorPoint" {
	              gets stdin NPoint
	              gets stdin color
		          .win$w.c itemconfigure Point$NPoint -fill $color
				  catch {.win$w.c raise DirDer Point}
		          update idletask
    }		    	
    "DelPoint" {
                gets stdin NPoint
                catch { .win$w.c delete Point$NPoint }
#		   tkwait variable datos(Sigue,.win$w.c)
                update idletask
	}	
	
    "DrawBox" { 
		    gets stdin x1
		    gets stdin y1
		    gets stdin x2
		    gets stdin y2
		    gets stdin color1
		    gets stdin color2
		    gets stdin NBox
		    .win$w.c create line \
		    $x1 $y1 $x2 $y1 -fill $color1 -width 2 -tag Box$NBox
		    .win$w.c create line \
		    $x2 $y1 $x2 $y2 -fill $color2 -width 2 -tag Box$NBox
		    .win$w.c create line \
		    $x2 $y2 $x1 $y2 -fill $color1 -width 2 -tag Box$NBox 
		    .win$w.c create line \
		    $x1 $y2 $x1 $y1 -fill $color2 -width 2 -tag Box$NBox
		    
		    ObjectZoom .win$w.c Box$NBox 
		    
		    .win$w.c addtag BOX withtag Box$NBox 
		    .win$w.c addtag nozoom withtag Box$NBox 
		    catch {.win$w.c raise Poly BOX}
		    
#		     tkwait variable sigue
            update idletask 
	}
    "DrawFillBox" { 
		    gets stdin x1
		    gets stdin y1
		    gets stdin x2
		    gets stdin y2
		    gets stdin color
		    gets stdin NBox
		    
		    catch { .win$w.c delete Box$NBox }
		    .win$w.c create polygon $x1 $y1 $x2 $y1 $x2 $y2 $x1 $y2 \
		     -fill $color -outline Black -width 0 -tag Box$NBox 
		    ObjectZoom .win$w.c Box$NBox 
		    
		    .win$w.c addtag BOX withtag Box$NBox 
		    .win$w.c addtag nozoom withtag Box$NBox 
		    catch {.win$w.c raise Poly BOX}
#		     tkwait variable sigue
            update idletask 
	}
        "DelBox" {
                   gets stdin NBox
                   catch { .win$w.c delete Box$NBox }
                   update idletask	
	}
	
	"DrawCircle" { 
		    gets stdin x1
		    gets stdin y1
		    gets stdin color
		    gets stdin NCircle
		    set border black
		  
		    set datos(nsimplex,.win$w.c) $NCircle
		   
		    .win$w.c create oval [expr $x1-10] [expr $y1-10] \
		    [expr $x1+10] [expr $y1+10] -fill $color \
		    -width 1 -fill $color -outline $border \
		     -tag Circle$NCircle

            ObjectZoom .win$w.c Circle$NCircle
		    
		    catch {.win$w.c raise Poly Circle }
		    catch {.win$w.c raise Circle$NCircle Circle }
		    catch {.win$w.c raise Circle$NCircle all}
		      
		    .win$w.c addtag Circle withtag Circle$NCircle 
		    #tkwait variable datos(Sigue,.win$w.c)
                    
            #unset Circle
            update idletask 
	}
    "DelCircle" {
                 gets stdin NCircle
                 catch { .win$w.c delete Circle$NCircle }
#		   tkwait variable datos(Sigue,.win$w.c)
                 update idletask
	}
	"method" {
			  gets stdin method
			  set datos(method,.win$w.c) $method
			  update idletask
	}
    "Wait" {
	           tkwait variable datos(Sigue,.win$w.c)
                update idletask
	}	
    }
    
}
update idletask    
