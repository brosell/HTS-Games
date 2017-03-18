del BarrelDrop.exe
c:\cygwin\bin\rm.exe -rf c:\colorcubes_debug
c:\cygwin\bin\rm.exe -rf c:\colorcubes_debug_demo
c:\cygwin\bin\rm.exe -rf c:\colorcubes_debug_nopack
copy Debug\BarrelDrop.exe .

echo  running asseter NoDemo
del demoControl.ini
copy noDemoAssets.ini demoControl.ini
assetter -pak+ Assets.ini c:\colorcubes_debug c:\colorcubes_debug\pak1.package
assetter -pak- Assets.ini c:\colorcubes_debug_nopack

echo  running asseter Demo
del demoControl.ini
copy demoAssets.ini demoControl.ini
assetter -pak+ Assets.ini c:\colorcubes_debug_demo c:\colorcubes_debug_demo\pak1.package
