//***************************************************************************
//
//  Action.hpp -- Declaration of a class to do something.
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


#ifndef __INCLUDED_ACTION_HPP__
#define __INCLUDED_ACTION_HPP__

class Action			// law suit
{

public:
						Action();
	virtual				~Action();

	virtual bool		doIt() = 0;

protected:
  // declared but not defined
						Action( const Action& );
						Action& operator= ( const Action& );
  
};

#endif // __INCLUDED_ACTION_HPP__
