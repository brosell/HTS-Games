/* ****************************************************************************
 *
 *  EventGenerator.h
 *  Created by Bert Rosell, on Mon Nov 03 2003, 11:23:01 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the EventGenerator component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__EVENTGENERATOR_H
#define ATC__EVENTGENERATOR_H
 

/** Purpose: TODO: Describe the purpose of the class.
 *  (Everything that you write here will show up in the
 *  doc++ generated documentation.)
 */
class EventGenerator
{
public:
    /// Constructor.
    EventGenerator();
public:
    virtual ~EventGenerator();
private:
	// Copying of this class is prohibited:
    EventGenerator(const EventGenerator&);
private:
	// Assignment to this class is prohibited:
    EventGenerator& operator=(const EventGenerator&);

};
#endif // #ifndef ATC__EVENTGENERATOR_H
 
