del BarrelDrop.exe
c:\cygwin\bin\rm.exe -rf c:\colorcubes_release
c:\cygwin\bin\rm.exe -rf c:\colorcubes_demo
c:\cygwin\bin\rm.exe -rf c:\colorcubes_release_nopack
copy Release\BarrelDrop.exe .

echo  running asseter NODemo

del demoControl.ini
copy noDemoAssets.ini demoControl.ini
assetter -pak+ Assets.ini c:\colorcubes_release c:\colorcubes_release\pak1.package
assetter -pak- Assets.ini c:\colorcubes_release_nopack

echo  running asseter Demo
del demoControl.ini
copy demoAssets.ini demoControl.ini
assetter -pak+ Assets.ini c:\colorcubes_demo c:\colorcubes_demo\pak1.package
