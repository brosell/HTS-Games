/* ****************************************************************************
 *
 *  LocalEventGenerator.h
 *  Created by Bert Rosell, on Mon Nov 03 2003, 11:23:07 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the LocalEventGenerator component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__LOCALEVENTGENERATOR_H
#define ATC__LOCALEVENTGENERATOR_H
 

/** Purpose: TODO: Describe the purpose of the class.
 *  (Everything that you write here will show up in the
 *  doc++ generated documentation.)
 */
class LocalEventGenerator
{
public:
    /// Constructor.
    LocalEventGenerator();
public:
    virtual ~LocalEventGenerator();
private:
	// Copying of this class is prohibited:
    LocalEventGenerator(const LocalEventGenerator&);
private:
	// Assignment to this class is prohibited:
    LocalEventGenerator& operator=(const LocalEventGenerator&);

};
#endif // #ifndef ATC__LOCALEVENTGENERATOR_H
 
