#!/bin/sh
bindir=$(pwd)
cd /media/psf/Home/Downloads/Aquagraphics/Code/waterRendering/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "xYES" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		/usr/bin/gdb -batch -command=$bindir/gdbscript --return-child-result /media/psf/Home/Downloads/Aquagraphics/Code/build/waterRendering 
	else
		"/media/psf/Home/Downloads/Aquagraphics/Code/build/waterRendering"  
	fi
else
	"/media/psf/Home/Downloads/Aquagraphics/Code/build/waterRendering"  
fi
