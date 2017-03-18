rm BigGolf.exe
rm IGMapper.exe
c:\cygwin\bin\rm.exe -rf c:\BigGolf_debug
copy Debug\IndustrialGolf.exe .\BigGolf.exe
copy IGMapper___Win32_Debug\IGMapper.exe .\
echo  running asseter
assetter -pak- Assets.ini c:\BigGolf_debug
