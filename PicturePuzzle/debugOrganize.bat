c:\cygwin\bin\rm.exe Puzzle.exe

c:\cygwin\bin\rm.exe -rf c:\_Puzzle_debug
c:\cygwin\bin\rm.exe -rf c:\_Puzzle_debug_nopack
copy Debug\PicturePuzzle.exe .\Puzzle.exe
echo  running asseter
assetter -pak- Assets_Full.ini c:\_Puzzle_debug_nopack
assetter -pak+ Assets_Full.ini c:\_Puzzle_debug c:\_Puzzle_debug\pak1.package

copy picpaks\*.picpak c:\_Puzzle_debug
copy picpaks\*.picpak c:\_Puzzle_debug_nopack

c:\cygwin\bin\rm.exe c:\_Puzzle_debug\Demo.picpak
c:\cygwin\bin\rm.exe c:\_Puzzle_debug_nopack\Demo.picpak
c:\cygwin\bin\rm.exe c:\_Puzzle_debug\Friends.picpak
c:\cygwin\bin\rm.exe c:\_Puzzle_debug_nopack\Friends.picpak
