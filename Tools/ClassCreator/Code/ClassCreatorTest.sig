Running the ClassCreator unit test:
 
The following test should build a DarkGold class, with public assignment, public copy ctor, no namespace:
Created DarkGold.h
Created DarkGold.cpp
Created DarkGold.icc
Created makefile
Created utDarkGold.cpp
make[1]: Entering directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o utDarkGold.o utDarkGold.cpp
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o DarkGold.o DarkGold.cpp
gcc -lgcc -o utDarkGold utDarkGold.o DarkGold.o /users1/jhubbard/ccm_wa/atc/tools/sxl/lib/sxl.a
make[1]: Leaving directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'


DarkGold Diagnostics dump 

The following test should build a DarkBlue class, with no icc file:
Created DarkBlue.h
Created DarkBlue.cpp
Created makefile
Created utDarkBlue.cpp
make[1]: Entering directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o utDarkBlue.o utDarkBlue.cpp
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o DarkBlue.o DarkBlue.cpp
gcc -lgcc -o utDarkBlue utDarkBlue.o DarkBlue.o /users1/jhubbard/ccm_wa/atc/tools/sxl/lib/sxl.a
make[1]: Leaving directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'


DarkBlue Diagnostics dump 

The following test should build a DarkishGreen class, with no (user-specified) ctor:
Created DarkishGreen.h
Created DarkishGreen.cpp
Created DarkishGreen.icc
Created makefile
Created utDarkishGreen.cpp
make[1]: Entering directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o utDarkishGreen.o utDarkishGreen.cpp
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o DarkishGreen.o DarkishGreen.cpp
gcc -lgcc -o utDarkishGreen utDarkishGreen.o DarkishGreen.o /users1/jhubbard/ccm_wa/atc/tools/sxl/lib/sxl.a
make[1]: Leaving directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'


DarkishGreen Diagnostics dump 

The following test should build a DarkishOrange class, with no CheckValid() function, and no (user-specified) ctor:
Created DarkishOrange.h
Created DarkishOrange.cpp
Created DarkishOrange.icc
Created makefile
Created utDarkishOrange.cpp
make[1]: Entering directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o utDarkishOrange.o utDarkishOrange.cpp
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o DarkishOrange.o DarkishOrange.cpp
gcc -lgcc -o utDarkishOrange utDarkishOrange.o DarkishOrange.o /users1/jhubbard/ccm_wa/atc/tools/sxl/lib/sxl.a
make[1]: Leaving directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'


DarkishOrange Diagnostics dump 

The following test should build a DarkishRed class, with no ctor, DumpDiagnostics(), or CheckValid():
Created DarkishRed.h
Created DarkishRed.cpp
Created DarkishRed.icc
Created makefile
Created utDarkishRed.cpp
make[1]: Entering directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o utDarkishRed.o utDarkishRed.cpp
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o DarkishRed.o DarkishRed.cpp
gcc -lgcc -o utDarkishRed utDarkishRed.o DarkishRed.o /users1/jhubbard/ccm_wa/atc/tools/sxl/lib/sxl.a
make[1]: Leaving directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
The following test should build a DarkishYellow class, with no DumpDiagnostics() function, no namespace, and with no (user-specified) ctor:
Created DarkishYellow.h
Created DarkishYellow.cpp
Created DarkishYellow.icc
Created makefile
Created utDarkishYellow.cpp
make[1]: Entering directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o utDarkishYellow.o utDarkishYellow.cpp
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o DarkishYellow.o DarkishYellow.cpp
gcc -lgcc -o utDarkishYellow utDarkishYellow.o DarkishYellow.o /users1/jhubbard/ccm_wa/atc/tools/sxl/lib/sxl.a
make[1]: Leaving directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
The following test should build a BrightRed class, with private assignment, public copy ctor:
Created BrightRed.h
Created BrightRed.cpp
Created BrightRed.icc
Created makefile
Created utBrightRed.cpp
make[1]: Entering directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o utBrightRed.o utBrightRed.cpp
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o BrightRed.o BrightRed.cpp
gcc -lgcc -o utBrightRed utBrightRed.o BrightRed.o /users1/jhubbard/ccm_wa/atc/tools/sxl/lib/sxl.a
make[1]: Leaving directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'


BrightRed Diagnostics dump 

The following test should build a Brown class, with public assignment, private copy ctor:
Created Brown.h
Created Brown.cpp
Created Brown.icc
Created makefile
Created utBrown.cpp
make[1]: Entering directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o utBrown.o utBrown.cpp
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o Brown.o Brown.cpp
gcc -lgcc -o utBrown utBrown.o Brown.o /users1/jhubbard/ccm_wa/atc/tools/sxl/lib/sxl.a
make[1]: Leaving directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'


Brown Diagnostics dump 

The following test should build a ForestGreen class, with no copy ctor:
Created ForestGreen.h
Created ForestGreen.cpp
Created ForestGreen.icc
Created makefile
Created utForestGreen.cpp
make[1]: Entering directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o utForestGreen.o utForestGreen.cpp
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o ForestGreen.o ForestGreen.cpp
gcc -lgcc -o utForestGreen utForestGreen.o ForestGreen.o /users1/jhubbard/ccm_wa/atc/tools/sxl/lib/sxl.a
make[1]: Leaving directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'


ForestGreen Diagnostics dump 

The following test should build a BurntOrange class, with no copy ctor, no assignment operator:
Created BurntOrange.h
Created BurntOrange.cpp
Created BurntOrange.icc
Created makefile
Created utBurntOrange.cpp
make[1]: Entering directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o utBurntOrange.o utBurntOrange.cpp
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o BurntOrange.o BurntOrange.cpp
gcc -lgcc -o utBurntOrange utBurntOrange.o BurntOrange.o /users1/jhubbard/ccm_wa/atc/tools/sxl/lib/sxl.a
make[1]: Leaving directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'


BurntOrange Diagnostics dump 

The following test should build a DarkRed class, with no destructor:
Created DarkRed.h
Created DarkRed.cpp
Created DarkRed.icc
Created makefile
Created utDarkRed.cpp
make[1]: Entering directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o utDarkRed.o utDarkRed.cpp
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o DarkRed.o DarkRed.cpp
gcc -lgcc -o utDarkRed utDarkRed.o DarkRed.o /users1/jhubbard/ccm_wa/atc/tools/sxl/lib/sxl.a
make[1]: Leaving directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'


DarkRed Diagnostics dump 

The following test should build a SkyBlue class, with no copy ctor:
Created SkyBlue.h
Created SkyBlue.cpp
Created SkyBlue.icc
Created makefile
Created utSkyBlue.cpp
make[1]: Entering directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o utSkyBlue.o utSkyBlue.cpp
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o SkyBlue.o SkyBlue.cpp
gcc -lgcc -o utSkyBlue utSkyBlue.o SkyBlue.o /users1/jhubbard/ccm_wa/atc/tools/sxl/lib/sxl.a
make[1]: Leaving directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'


SkyBlue Diagnostics dump 

The following test should build a Turquoise class, with Continuus keywords:
Created Turquoise.h
Created Turquoise.cpp
Created Turquoise.icc
Created makefile
Created utTurquoise.cpp
make[1]: Entering directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o utTurquoise.o utTurquoise.cpp
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o Turquoise.o Turquoise.cpp
gcc -lgcc -o utTurquoise utTurquoise.o Turquoise.o /users1/jhubbard/ccm_wa/atc/tools/sxl/lib/sxl.a
make[1]: Leaving directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'


Turquoise Diagnostics dump 

The following test should build a Magenta class, with SCCS keywords:
Created Magenta.h
Created Magenta.cpp
Created Magenta.icc
Created makefile
Created utMagenta.cpp
make[1]: Entering directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o utMagenta.o utMagenta.cpp
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o Magenta.o Magenta.cpp
gcc -lgcc -o utMagenta utMagenta.o Magenta.o /users1/jhubbard/ccm_wa/atc/tools/sxl/lib/sxl.a
make[1]: Leaving directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'


Magenta Diagnostics dump 

The following test should build a Yellow class, with an opensource notice:
Created Yellow.h
Created Yellow.cpp
Created Yellow.icc
Created makefile
Created utYellow.cpp
make[1]: Entering directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o utYellow.o utYellow.cpp
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o Yellow.o Yellow.cpp
gcc -lgcc -o utYellow utYellow.o Yellow.o /users1/jhubbard/ccm_wa/atc/tools/sxl/lib/sxl.a
make[1]: Leaving directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'


Yellow Diagnostics dump 

The following test should build a Gray class, with a copyright notice:
Created Gray.h
Created Gray.cpp
Created Gray.icc
Created makefile
Created utGray.cpp
make[1]: Entering directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o utGray.o utGray.cpp
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o Gray.o Gray.cpp
gcc -lgcc -o utGray utGray.o Gray.o /users1/jhubbard/ccm_wa/atc/tools/sxl/lib/sxl.a
make[1]: Leaving directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'


Gray Diagnostics dump 

The following test should build a Silver class, with all of the above features:
Created Silver.h
Created Silver.cpp
Created Silver.icc
Created makefile
Created utSilver.cpp
make[1]: Entering directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o utSilver.o utSilver.cpp
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o Silver.o Silver.cpp
gcc -lgcc -o utSilver utSilver.o Silver.o /users1/jhubbard/ccm_wa/atc/tools/sxl/lib/sxl.a
make[1]: Leaving directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'


Silver Diagnostics dump 

The following test should build a Purple and Gold class, in Colors.xxx files:
Created Colors.h
Created Colors.cpp
Created Colors.icc
Created makefile
Created utColors.cpp
make[1]: Entering directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o utColors.o utColors.cpp
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o Colors.o Colors.cpp
gcc -lgcc -o utColors utColors.o Colors.o /users1/jhubbard/ccm_wa/atc/tools/sxl/lib/sxl.a
make[1]: Leaving directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'


Purple Diagnostics dump 



Gold Diagnostics dump 

The following test should build a Blue class:
Created Blue.h
Created Blue.cpp
Created Blue.icc
Created makefile
Created utBlue.cpp
make[1]: Entering directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o utBlue.o utBlue.cpp
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o Blue.o Blue.cpp
gcc -lgcc -o utBlue utBlue.o Blue.o /users1/jhubbard/ccm_wa/atc/tools/sxl/lib/sxl.a
make[1]: Leaving directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'


Blue Diagnostics dump 

The following test should use the first class as the filename:
Created Orange.h
Created Orange.cpp
Created Orange.icc
Created makefile
Created utOrange.cpp
make[1]: Entering directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o utOrange.o utOrange.cpp
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o Orange.o Orange.cpp
gcc -lgcc -o utOrange utOrange.o Orange.o /users1/jhubbard/ccm_wa/atc/tools/sxl/lib/sxl.a
make[1]: Leaving directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'


Orange Diagnostics dump 



Apple Diagnostics dump 



Pear Diagnostics dump 

The following test should build an AtcGreen class, using settings specific to the atc project:
Created AtcGreen.h
Created AtcGreen.cpp
Created AtcGreen.icc
Created makefile
Created utAtcGreen.cpp
The following test should build a OsGold class, using settings specific to the opensource project:
Created OsGold.h
Created OsGold.cpp
Created OsGold.icc
Created makefile
Created utOsGold.cpp
make[1]: Entering directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o utOsGold.o utOsGold.cpp
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o OsGold.o OsGold.cpp
gcc -lgcc -o utOsGold utOsGold.o OsGold.o /users1/jhubbard/ccm_wa/atc/tools/sxl/lib/sxl.a
make[1]: Leaving directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'


OsGold Diagnostics dump 

The following test should FAIL to build a OsGold class, because -overwrite is not used and the files exist:
Did NOT create OsGold.h because it already exists.
Did NOT create OsGold.cpp because it already exists.
Did NOT create OsGold.icc because it already exists.
Did NOT create makefile because it already exists.
Did NOT create utOsGold.cpp because it already exists.
The following test should build a OsGold class, because the -overwrite flag is used:
Created OsGold.h
Created OsGold.cpp
Created OsGold.icc
Created makefile
Created utOsGold.cpp
make[1]: Entering directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o utOsGold.o utOsGold.cpp
gcc -DSOLARIS_SPARC -g -c -fhonor-std -fno-builtin -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused -I /users1/jhubbard/ccm_wa/atc/tools/sxl/include -c -o OsGold.o OsGold.cpp
gcc -lgcc -o utOsGold utOsGold.o OsGold.o /users1/jhubbard/ccm_wa/atc/tools/sxl/lib/sxl.a
make[1]: Leaving directory `/users1/jhubbard/ccm_wa/atc/tools/code_gen/ClassCreator/tmp001'


OsGold Diagnostics dump 

