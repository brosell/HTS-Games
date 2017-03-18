rm BigGolf.exe
rm IGMapper.exe
c:\cygwin\bin\rm.exe -rf c:\BigGolf_release
copy Release\IndustrialGolf.exe .\BigGolf.exe
copy Release\IGMapper.exe .\
echo  running asseter
assetter -pak- Assets.ini c:\BigGolf_release
