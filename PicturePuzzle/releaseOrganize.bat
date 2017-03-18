c:\cygwin\bin\rm.exe Puzzle.exe

c:\cygwin\bin\rm.exe -rf c:\_Puzzle_release
c:\cygwin\bin\rm.exe -rf c:\_Puzzle_release_nopack
copy Release\PicturePuzzle.exe .\Puzzle.exe
echo  running asseter
assetter -pak- Assets_Full.ini c:\_Puzzle_release_nopack
assetter -pak+ Assets_Full.ini c:\_Puzzle_release c:\_Puzzle_release\pak1.package

copy picpaks\*.picpak c:\_Puzzle_release
copy picpaks\*.picpak c:\_Puzzle_release_nopack

c:\cygwin\bin\rm.exe c:\_Puzzle_release\Demo.picpak
c:\cygwin\bin\rm.exe c:\_Puzzle_release_nopack\Demo.picpak
c:\cygwin\bin\rm.exe c:\_Puzzle_release\Friends.picpak
c:\cygwin\bin\rm.exe c:\_Puzzle_release_nopack\Friends.picpak
