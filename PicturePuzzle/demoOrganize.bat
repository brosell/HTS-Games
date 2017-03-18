c:\cygwin\bin\rm.exe Puzzle.exe

c:\cygwin\bin\rm.exe -rf c:\_Puzzle_demo
c:\cygwin\bin\rm.exe -rf c:\_Puzzle_demo_nopack
copy PicturePuzzle___Win32_Demo\PicturePuzzle.exe .\Puzzle.exe
echo  running asseter
assetter -pak- Assets_Demo.ini c:\_Puzzle_demo_nopack
assetter -pak+ Assets_Demo.ini c:\_Puzzle_demo c:\_Puzzle_demo\pak1.package

copy picpaks\Demo.picpak c:\_Puzzle_demo
copy picpaks\Demo.picpak c:\_Puzzle_demo_nopack