/* ****************************************************************************
 *
 *  Star.h
 *  Created by Bert Rosell, on Sat Nov 01 2003, 12:24:37 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the Star component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__STAR_H
#define ATC__STAR_H
 
#include "Entity.h"
#include "AM.h"
/** Purpose: TODO: Describe the purpose of the class.
 *  (Everything that you write here will show up in the
 *  doc++ generated documentation.)
 */
class Star: public Entity
{
public:
    /// Constructor.
    Star();
    virtual ~Star();

    virtual void logic(float factor);


private:
	// Copying of this class is prohibited:
    Star(const Star&);
private:
	// Assignment to this class is prohibited:
    Star& operator=(const Star&);

    RotateSkinHandle m_skin;

};
#endif // #ifndef ATC__STAR_H
 
