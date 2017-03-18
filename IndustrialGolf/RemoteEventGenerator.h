/* ****************************************************************************
 *
 *  RemoteEventGenerator.h
 *  Created by Bert Rosell, on Mon Nov 03 2003, 11:23:16 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the RemoteEventGenerator component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__REMOTEEVENTGENERATOR_H
#define ATC__REMOTEEVENTGENERATOR_H
 

/** Purpose: TODO: Describe the purpose of the class.
 *  (Everything that you write here will show up in the
 *  doc++ generated documentation.)
 */
class RemoteEventGenerator
{
public:
    /// Constructor.
    RemoteEventGenerator();
public:
    virtual ~RemoteEventGenerator();
private:
	// Copying of this class is prohibited:
    RemoteEventGenerator(const RemoteEventGenerator&);
private:
	// Assignment to this class is prohibited:
    RemoteEventGenerator& operator=(const RemoteEventGenerator&);

};
#endif // #ifndef ATC__REMOTEEVENTGENERATOR_H
 
