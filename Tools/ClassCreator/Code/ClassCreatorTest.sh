#!/bin/sh
#########################################################################
# ClassCreatorTest.sh
# Created by John F. Hubbard on Wed Sep 07 2000, 16:43:10 PST
#
# File Contents: unit test data for the CommandLine project.
#
#  %version: 2.30 %
#  %date_modified: Thu Nov 16 20:03:12 2000 %
#  %created_by: jhubbard %
#
#########################################################################

echo "Running the ClassCreator unit test:"
echo " "
if [ -d tmp001 ]; then
	rm -r tmp001;
fi

    mkdir tmp001
	cd tmp001

	echo "The following test should build a DarkGold class, with public assignment, public copy ctor, no namespace:"
	../fcc -verbose -public_assignment_operator -public_copy_ctor -overwrite -continuus_keywords -class DarkGold -author "John F. Hubbard"
	make
	utDarkGold

	echo "The following test should build a DarkBlue class, with no icc file:"
	../fcc -verbose -no_icc -overwrite -continuus_keywords -class DarkBlue -namespace colors -author "John F. Hubbard"
	make
	utDarkBlue

	echo "The following test should build a DarkishGreen class, with no (user-specified) ctor:"
	../fcc -verbose -no_ctor -overwrite -continuus_keywords -class DarkishGreen -namespace colors -author "John F. Hubbard"
	make
	utDarkishGreen

	echo "The following test should build a DarkishOrange class, with no CheckValid() function, and no (user-specified) ctor:"
	../fcc -verbose -no_ctor -no_check_valid -overwrite -continuus_keywords -class DarkishOrange -namespace colors -author "John F. Hubbard"
	make
	utDarkishOrange

	echo "The following test should build a DarkishRed class, with no ctor, DumpDiagnostics(), or CheckValid():"
	../fcc -verbose -no_ctor -no_cv -no_dd -overwrite -continuus_keywords -class DarkishRed -namespace colors -author "John F. Hubbard"
	make
	utDarkishRed

	echo "The following test should build a DarkishYellow class, with no DumpDiagnostics() function, no namespace, and with no (user-specified) ctor:"
	../fcc -verbose -no_ctor -no_dump_diagnostics -overwrite -continuus_keywords -class DarkishYellow -author "John F. Hubbard"
	make
	utDarkishYellow

	echo "The following test should build a BrightRed class, with private assignment, public copy ctor:"
	../fcc -verbose -public_copy_ctor  -overwrite -continuus_keywords -class BrightRed -namespace colors -author "John F. Hubbard"
	make
	utBrightRed

	echo "The following test should build a Brown class, with public assignment, private copy ctor:"
	../fcc -verbose -public_assignment_operator -overwrite -continuus_keywords -class Brown -namespace colors -author "John F. Hubbard"
	make
	utBrown

	echo "The following test should build a ForestGreen class, with no copy ctor:"
	../fcc -verbose -no_copy_ctor -ow -ct -class ForestGreen -namespace colors -author "John F. Hubbard"
	make
	utForestGreen

	echo "The following test should build a BurntOrange class, with no copy ctor, no assignment operator:"
	../fcc -verbose -no_copy_ctor -no_op= -overwrite -continuus_keywords -class BurntOrange -ns colors -author "John F. Hubbard"
	make
	utBurntOrange

	echo "The following test should build a DarkRed class, with no destructor:"
	../fcc -verbose -no_dtor -overwrite -ct -class DarkRed -ns colors -author "John F. Hubbard"
	make
	utDarkRed

	echo "The following test should build a SkyBlue class, with no copy ctor:"
	../fcc -verbose -no_copy_ctor -overwrite -continuus_keywords -class SkyBlue -ns colors -author "John F. Hubbard"
	make
	utSkyBlue

	echo "The following test should build a Turquoise class, with Continuus keywords:"
	../fcc -verbose -overwrite -continuus_keywords -class Turquoise -namespace colors -author "John F. Hubbard"
	make
	utTurquoise

	echo "The following test should build a Magenta class, with SCCS keywords:"
	../fcc -verbose -overwrite -sccs_keywords -class Magenta -namespace rainbow -author "Jesus Jones"
	make
	utMagenta

	echo "The following test should build a Yellow class, with an opensource notice:"
	../fcc -verbose -overwrite -os -class Yellow -namespace colors -author "George G. Gerard"
	make
	utYellow

	echo "The following test should build a Gray class, with a copyright notice:"
	../fcc  -verbose -overwrite -copyright "Copyright (c) 2010, Outworld Technology" -class Gray -namespace colors -author "Sam Smith"
	make
	utGray

	echo "The following test should build a Silver class, with all of the above features:"
	../fcc -open_source_notice -continuus_keywords -sccs_keywords -c "Copyright (c) 2010, Outworld Technology" -verbose -overwrite -class Silver -namespace colors -author "John F. Hubbard"
	make
	utSilver

	echo "The following test should build a Purple and Gold class, in Colors.xxx files:"
	../fcc -settings_file "../many_colors_test.ini" -continuus_keywords -overwrite
	make
	utColors

	echo "The following test should build a Blue class:"
	../fcc -verbose -overwrite -class Blue -namespace colors -author "John F. Hubbard"
	make
	utBlue

	echo "The following test should use the first class as the filename:"
	../fcc -verbose -overwrite -class "Orange Apple Pear" -namespace fruits -author "Joe Smith"
	make
	utOrange

	echo "The following test should build an AtcGreen class, using settings specific to the atc project:"
	../fcc -overwrite -verbose -project atc -class AtcGreen -namespace tools -author "John F. Hubbard"
	#make
	# utAtcGreen (commented out to allow automatic unit tests to run--no date stamps allowed).
	echo "The following test should build a OsGold class, using settings specific to the opensource project:"
	../fcc -overwrite -verbose -project opensource -class OsGold -namespace tools -author "John F. Hubbard"
	make
	utOsGold
	echo "The following test should FAIL to build a OsGold class, because -overwrite is not used and the files exist:"
	../fcc -verbose -project opensource -class OsGold -namespace tools -author "John F. Hubbard"
	echo "The following test should build a OsGold class, because the -overwrite flag is used:"
	../fcc -overwrite -verbose -project opensource -class OsGold -namespace tools -author "John F. Hubbard"
	make
	utOsGold
