//***************************************************************************
//
//  Initializer.hpp -- Declaration of a class to initialize before calling
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

//***************************************************************************
//
//	An action to be run at startup. This class's doIt() sets up
//	class static variables.
//
//***************************************************************************

#ifndef _INCLUDE_INITIALIZER_HPP_
#define _INCLUDE_INITIALIZER_HPP_

#include "Action.hpp"

class Initializer : public Action
{
  public:
					Initializer() {}
					~Initializer() {}

	virtual	bool	doIt();

  private:
	Initializer( const Initializer& a_src );
	Initializer& operator= ( const Initializer& a_src );
};

#endif
