//***************************************************************************
//
//	Cell.hpp -- declaration a class for holing either a value or a list node
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

#ifndef _INCLUDE_FUNCTION_HPP_
#define _INCLUDE_FUNCTION_HPP_

// Application headers
#ifndef _INCLUDE_CELL_HPP_
#include "Cell.hpp"
#endif

// System headers
#include <cstdlib>



//**********************************************************************
// Function class - a class for functions operating on lists
//**********************************************************************
class Function{

public:

	Function()				{}
	Function( const Function& a_src ) {}
	Function& operator=( const Function& a_src ) { return *this;}
	virtual ~Function() {}

	
	virtual RefCountedCell&	operator() ( RefCountedCell&	a_input ) 
	{
		// For the default function just return the input
		return a_input;
	}
};

#endif // _INCLUDE_FUNCTION_HPP
