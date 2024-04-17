#!/bin/sh

#To add comments after a command, add a ;
#No lines among witch options.
# the next line restarts using wish \
exec wish "$0" "$@"

proc CreateFrame { w  font font2} {
 global datos width height

 #Top frame---------------------------------------------------------------------
 frame .win$w.fup -bg White
 label .win$w.fup.tfunction -text "Function =" -font $font -bg White
 label .win$w.fup.function -text $datos(function,.win$w.c) -font $font -bg White
 label .win$w.fup.tinfile -text "InputFile =" -font $font -bg White
 label .win$w.fup.infile -text $datos(InputFile,.win$w.c) -font $font -bg White

 pack  .win$w.fup.tfunction -side left
 pack  .win$w.fup.function  -side left
 pack  .win$w.fup.infile    -side right
 pack  .win$w.fup.tinfile   -side right

 #Fisrt bottom frame------------------------------------------------------------
 frame .win$w.fbottom -bg White
 label .win$w.fbottom.talpha -text "a =" -font $font -bg White
 label .win$w.fbottom.alpha  -text $datos(alpha,.win$w.c) -font $font -bg White
 label .win$w.fbottom.tnpoly -text "NPoly =" -font $font -bg White
 label .win$w.fbottom.npoly -textvariable datos(npoly,.win$w.c) -font $font -bg White

 pack  .win$w.fbottom.talpha -side left
 pack  .win$w.fbottom.alpha  -side left
 pack  .win$w.fbottom.npoly  -side right
 pack  .win$w.fbottom.tnpoly -side right

 #Second bottom frame-----------------------------------------------------------
 frame .win$w.fbottom1 -bg White
 label .win$w.fbottom1.tlb -text "lb =" -font $font -bg White
 label .win$w.fbottom1.lb  -textvariable datos(lb,.win$w.c) -font $font -bg White
 label .win$w.fbottom1.tub -text "ub =" -font $font -bg White
 label .win$w.fbottom1.ub  -textvariable datos(ub,.win$w.c) -font $font -bg White
 label .win$w.fbottom1.tc0 -text "C0 =" -font $font -bg White
 label .win$w.fbottom1.c0  -textvariable datos(c0,.win$w.c) -font $font -bg White
 label .win$w.fbottom1.tc1 -text "C1 =" -font $font -bg White
 label .win$w.fbottom1.c1  -textvariable datos(c1,.win$w.c) -font $font -bg White

 pack  .win$w.fbottom1.tc0 -side left
 pack  .win$w.fbottom1.c0  -side left
 pack  .win$w.fbottom1.tc1 -side left
 pack  .win$w.fbottom1.c1  -side left
 pack  .win$w.fbottom1.ub  -side right
 pack  .win$w.fbottom1.tub -side right
 pack  .win$w.fbottom1.lb  -side right
 pack  .win$w.fbottom1.tlb -side right

 #Last bottom frame for buttons-------------------------------------------------
 frame .win$w.buttons -bg white
 button .win$w.buttons.salida -text Exit -command exit
 #Put quotes so it takes the variables from when the button was created
 button .win$w.buttons.postscript -text Postscript -command "GenPostscrip $w"
 button .win$w.buttons.continuar -text Next -command "incr datos(Sigue,.win$w.c)"

 pack .win$w.buttons.salida \
      .win$w.buttons.postscript \
      .win$w.buttons.continuar -side left -fill x -expand true

 #Create canvas-----------------------------------------------------------------
 canvas .win$w.c -width $width -heigh $height -bg Gray80 -borderwidth 0 \
  -highlightthickness 0

 pack .win$w.fup      -side top -fill x 
 pack .win$w.c        -side top
 pack .win$w.fbottom  -side top -fill x 
 pack .win$w.fbottom1 -side top -fill x
 pack .win$w.buttons  -side bottom -fill x
}

#Generate a postcript fro canvas------------------------------------------------
proc GenPostscrip { w } {
 global datos
 .win$w.c postscript -file \
 f$datos(function,.win$w.c)-$datos(InputFile,.win$w.c)-$datos(alpha,.win$w.c).ps 
 #puts "f$datos(function,.win$w.c)-$datos(Sigue,.win$w.c).ps"
}

#Great than---------------------------------------------------------------------
proc GT { x y } {
 if { $x < $y } {
  return $y
 }
 return $x
}


#Init the buttons' behavior to generate the box to be zoomed--------------------
proc BoxInit {c} {
 bind $c <Button-1> {BoxBegin %W %x %y}
 bind $c <B1-Motion> {BoxDrag %W %x %y}
 bind $c <B1-ButtonRelease> {BoxEnd %W %x %y}
 bind $c <Button-3> {BoxUnZoom %W}
}

#Set the initial corner. See BoxInit--------------------------------------------
proc BoxBegin { w x y } {
 global box
 set box(anchor,$w) [list $x $y]
 catch {unset box(last,$w)}
}

#Enlarge the box from first corner. See BoxInit---------------------------------
proc BoxDrag { w x y } {
 global box
 catch {$w delete $box(last,$w)}
 set x0 [lindex $box(anchor,$w) 0]
 set y0 [lindex $box(anchor,$w) 1]
 set dist [GT [expr abs($x0-$x)] [expr abs($y0-$y)]]
 set x1 [expr $x0 - $dist]
 set x2 [expr $x0 + $dist]
 set y1 [expr $y0 - $dist]
 set y2 [expr $y0 + $dist]
 set box(last,$w) [eval {$w create rect} {$x1 $y1 $x2 $y2 -tag box -outline red}]
}

#Perform the calculations for the zoom. See Boxinit-----------------------------
proc BoxEnd { w x y } {
 global box Zoom ZLevel
 catch {$w delete $box(last,$w)}
 set dist [GT [expr abs ([lindex $box(anchor,$w) 0]-$x)] \
              [expr abs ([lindex $box(anchor,$w) 1]-$y)]]

 if {$dist > 5} { 
  set ZLevel($w) [expr $ZLevel($w) +1]
  set Zoom(xmed,$ZLevel($w),$w) [lindex $box(anchor,$w) 0]
  set Zoom(ymed,$ZLevel($w),$w) [lindex $box(anchor,$w) 1]
  set x1 [expr $Zoom(xmed,$ZLevel($w),$w) - $dist]
  set x2 [expr $Zoom(xmed,$ZLevel($w),$w) + $dist]
  set y1 [expr $Zoom(ymed,$ZLevel($w),$w) + $dist]
  set y2 [expr $Zoom(ymed,$ZLevel($w),$w) - $dist]

  #New width and new height
  #Factor x and y is the ratio between the initial window and the new one.
  set Zoom(width,$ZLevel($w),$w)  [expr abs ($x2 - $x1)]
  set Zoom(height,$ZLevel($w),$w) [expr abs ($y2 - $y1)]
  set factorx [expr $Zoom(width,0,$w).0  / $Zoom(width,$ZLevel($w),$w).0]
  set factory [expr $Zoom(height,0,$w).0 / $Zoom(height,$ZLevel($w),$w).0]

  #displacement in x and y of the already scaled data
  set Zoom(xdesp,$ZLevel($w),$w) [expr $Zoom(xmed,0,$w) - $Zoom(xmed,$ZLevel($w),$w)]
  set Zoom(ydesp,$ZLevel($w),$w) [expr $Zoom(ymed,0,$w) - $Zoom(ymed,$ZLevel($w),$w)]

  $w scale all $Zoom(xmed,$ZLevel($w),$w)  $Zoom(ymed,$ZLevel($w),$w) $factorx $factory 
  $w move  all $Zoom(xdesp,$ZLevel($w),$w) $Zoom(ydesp,$ZLevel($w),$w)

  catch {$w delete text}
  $w create text 30 10 -text "Zoom $ZLevel($w)" -fill Red -tag text

  update idletask
 }
}

#Back to previous calculations for zoom. See BoxInit----------------------------
proc BoxUnZoom {w} {
 global box Zoom ZLevel
 catch {$w delete text} 
 if { $ZLevel($w) > 0 } { 
  set factorx [expr $Zoom(width,$ZLevel($w),$w).0 / $Zoom(width,0,$w).0]
  set factory [expr $Zoom(height,$ZLevel($w),$w).0 / $Zoom(height,0,$w).0]
  $w scale all $Zoom(xmed,0,$w) $Zoom(ymed,0,$w) $factorx $factory
  $w move  all [expr -1.0 * $Zoom(xdesp,$ZLevel($w),$w)] \
               [expr -1.0 * $Zoom(ydesp,$ZLevel($w),$w)]
  set ZLevel($w) [expr $ZLevel($w) -1]
  if { $ZLevel($w) > 0 } {
   $w create text 30 10 -text "Zoom $ZLevel($w)" -fill Red -tag text
  }
 }
}

#Does object zoom.--------------------------------------------------------------
proc ObjectZoom { w objeto } {
 global box Zoom ZLevel
 if { $ZLevel($w) > 0 } {
  for { set i 1 } {$i <= $ZLevel($w) } {incr i} {
   set factorx [expr $Zoom(width,0,$w).0 / $Zoom(width,$i,$w).0]
   set factory [expr $Zoom(height,0,$w).0 / $Zoom(height,$i,$w).0]
   $w scale $objeto $Zoom(xmed,$i,$w) $Zoom(ymed,$i,$w) $factorx $factory 
   $w move  $objeto $Zoom(xdesp,$i,$w) $Zoom(ydesp,$i,$w)
  }
 }
}



#Main===========================================================================
set tcl_precision 10
gets stdin width;	#Width of the canvas.
gets stdin height;	#Height of the canvas

set font -*-fixed-*-*-*-*-*-[expr $width / 8 + [expr $width / 4 % 10] ]-*-*-*-*-*-* 
set font2 -*-symbol-*-*-*-*-*-[expr $width / 6 + [expr $width / 2 % 10]]-*-*-*-*-*-*  

gets stdin NWin;	#Number of canvas.
gets stdin Algo;	#Algorithm mname.
gets stdin alpha;	#Precision.

#for each canvas-------------------
for {set w 0} {$w<$NWin} {incr w} {
 toplevel .win$w
 wm title .win$w              $Algo
 wm iconname .win$w           $Algo
 set datos(alpha,.win$w.c)    $alpha
 gets stdin function;	#Function name
 set datos(function,.win$w.c) $function
 gets stdin InputFile;	#Input file
 set datos(InputFile,.win$w.c)  $InputFile
 gets stdin c0;			#First real word coordinate.
 set datos(c0,.win$w.c) $c0
 gets stdin c1;			#First real word coordinate.
 set datos(c1,.win$w.c) $c1
 set datos(Sigue,.win$w.c) 0
 set datos(npoly,.win$w.c) nan 
 set datos(lb,.win$w.c)    nan
 set datos(ub,.win$w.c)    nan

 CreateFrame  $w $font $font2

 set ZLevel(.win$w.c) 0

 set Zoom(width,$ZLevel(.win$w.c),.win$w.c) $width
 set Zoom(height,$ZLevel(.win$w.c),.win$w.c) $height 
 set Zoom(xmed,$ZLevel(.win$w.c),.win$w.c) [expr $width.0/2.0] 
 set Zoom(ymed,$ZLevel(.win$w.c),.win$w.c) [expr $height.0/2.0] 
}

#Solo al -c para que los buttons no cojan el bind.
for {set w 0} {$w<$NWin} {incr w} {
 BoxInit .win$w.c
}

update idletask

if { $NWin>1 } {
 set wold 0
 .win$wold.c configure -background bisque1
}

#while--------------------------------------------------------------------------
while { ( 0 < [ gets stdin w ] )} {
 if { $NWin > 1 && $wold != $w } {
  catch {.win$wold.c configure -background gray80}
  .win$w.c configure -background bisque1
   set wold $w
 }

 gets stdin action

 #switch------------------------------------------------------------------------
 switch $action {

  "DrawPoly" {
   gets stdin NVert
   set coords {}
   for {set i 1} {$i<=$NVert} {incr i} {
    gets stdin x
    gets stdin y
    lappend coords $x $y
   }
   gets stdin colorIn
   gets stdin NPoly
   set datos(npoly,.win$w.c) $NPoly
   catch { .win$w.c delete Poly$NPoly }
   .win$w.c create polygon $coords -fill $colorIn -outline Black \
    -width 3 -tag Poly$NPoly

   ObjectZoom .win$w.c Poly$NPoly

   .win$w.c addtag Poly withtag Poly$NPoly
   catch {.win$w.c raise LinePoly   Poly}
   catch {.win$w.c raise Point      Poly}
  }

  "DelPoly" {
   gets stdin NPoly
   catch { .win$w.c delete Poly$NPoly }
  }

  "DrawLinePoly" {
   gets stdin NVert
   set coords {}
   for {set i 1} {$i<=$NVert} {incr i} {
    gets stdin x
    gets stdin y
    lappend coords $x $y
   }
   #For a line we do not add first point at the end.
   if {$NVert>2} {
    append coords " " [lrange $coords 0 1]
   }
   gets stdin colorIn
   gets stdin NPoly
   set datos(npoly,.win$w.c) $NPoly
   catch { .win$w.c delete Poly$NPoly }
   .win$w.c create line $coords -fill $colorIn -width 3 -tag LinePoly$NPoly

   ObjectZoom .win$w.c LinePoly$NPoly

   .win$w.c addtag Poly withtag LinePoly$NPoly
   catch {.win$w.c raise Poly$NPoly  all}
   catch {.win$w.c raise Point  LinePoly}
  }

  "SetColorLinePoly" {
   gets stdin NPoly
   set datos(npoly,.win$w.c) $NPoly
   gets stdin color
   .win$w.c itemconfigure LinePoly$NPoly -fill $color
   catch {.win$w.c raise Poly$NPoly all}
   catch {.win$w.c raise Point  LinePoly}
  }

  "DelLinePoly" {
   gets stdin NPoly
   catch { .win$w.c delete LinePoly$NPoly }
  }

  "DrawPoint" {
   gets stdin x
   gets stdin y
   gets stdin color
   gets stdin NPoint
   set border black
   set Point [.win$w.c find withtag Point$NPoint]
   #if point did not already exists.
   if { [llength $Point] == 0 } {
    .win$w.c create rect \
     [expr $x-3] [expr $y-3] \
     [expr $x+3] [expr $y+3] -fill $color -width 1 -fill $color \
     -outline $border -tag Point$NPoint

    ObjectZoom .win$w.c Point$NPoint

    .win$w.c addtag Point withtag Point$NPoint 
    catch {.win$w.c raise Point$NPoint all}
   } 
  }

  "SetColorPoint" {
   gets stdin NPoint
   gets stdin color
   .win$w.c itemconfigure Point$NPoint -fill $color
   catch {.win$w.c raise Point$NPoint all}
  }

  "DelPoint" {
   gets stdin NPoint
   catch { .win$w.c delete Point$NPoint }
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
   set datos(nbox,.win$w.c) $NBox
   
   ObjectZoom .win$w.c Box$NBox 

   .win$w.c addtag BOX withtag Box$NBox 
   catch {.win$w.c raise Poly BOX}
  }

  "DrawLineBox" {
   gets stdin x1
   gets stdin y1
   gets stdin x2
   gets stdin y2
   gets stdin color1
   gets stdin color2
   gets stdin NBox
   .win$w.c create line $x1 $y1 $x2 $y1 -fill $color1 -width 2 -tag Box$NBox
   .win$w.c create line $x2 $y1 $x2 $y2 -fill $color2 -width 2 -tag Box$NBox
   .win$w.c create line $x2 $y2 $x1 $y2 -fill $color1 -width 2 -tag Box$NBox 
   .win$w.c create line $x1 $y2 $x1 $y1 -fill $color2 -width 2 -tag Box$NBox

   ObjectZoom .win$w.c Box$NBox 

   .win$w.c addtag BOX withtag Box$NBox 
   catch {.win$w.c raise Poly BOX}
   catch {.win$w.c raise Point BOX}
  }

  "DelBox" {
   gets stdin NBox
   catch { .win$w.c delete Box$NBox }
  }

  "method" {
   gets stdin method
   set datos(method,.win$w.c) $method
  }

  "Wait" {
   tkwait variable datos(Sigue,.win$w.c)
  }
 }
 update idletask
}
update idletask