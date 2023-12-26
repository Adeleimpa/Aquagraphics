#!/bin/sh
bindir=$(pwd)
cd /home/parallels/Desktop/Parallels Shared Folders/Home/Downloads/Aquagraphics/Code/waterRendering/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "xYES" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		/usr/bin/gdb -batch -command=$bindir/gdbscript --return-child-result /home/parallels/Desktop/Parallels\ Shared\ Folders/Home/Downloads/Aquagraphics/Code/build/waterRendering 
	else
		"/home/parallels/Desktop/Parallels\ Shared\ Folders/Home/Downloads/Aquagraphics/Code/build/waterRendering"  
	fi
else
	"/home/parallels/Desktop/Parallels\ Shared\ Folders/Home/Downloads/Aquagraphics/Code/build/waterRendering"  
fi
