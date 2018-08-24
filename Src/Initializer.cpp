//***************************************************************************
//
//  Initializer.cpp -- Definition of a class to initialize before calling
//                     the program's main loop.
//
//  $LastChangedBy$
//  $LastChangedDate$
//  $LastChangedRevision$
//  $HeadURL$
//
//  Copyright (C) 2004-2009 Ronald G. Mackley.
//  All rights reserved.
//
//  $Id$
//
//***************************************************************************

//
//	An action to be run at startup. This class's doIt() sets up
//	class static variables.
//
//	There has to be a better way to get a list of initializers to call.
//	Perhaps an array with pointers to static initializeClass functions?
//
//***************************************************************************

#ifndef _INCLUDE_INITIALIZER_HPP_
#include "Initializer.hpp"
#endif

// classes to be initialized

//***************************************************************************
//***************************************************************************
bool	 Initializer::doIt()
{
	//! this should have an initializeClass member as well

	// Add the list of things to be initialized here
	return true;
}
