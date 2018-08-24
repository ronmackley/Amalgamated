//***************************************************************************
//
//	Atom.hpp -- declaration a class for returning whether a Cell is an Atom
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

#ifndef _INCLUDE_ATOM_HPP_
#define _INCLUDE_ATOM_HPP_

// Application headers
#ifndef _INCLUDE_FUNCTION_HPP_
#include "Function.hpp"
#endif

#ifndef _INCLUDE_CELL_HPP_
#include "Cell.hpp"
#endif

// System headers
#include <cstdlib>



//**********************************************************************
// Atom class - a class for telling whether its argument is an atom
//**********************************************************************
class Atom : Function {

public:

	Atom() 						{}
	Atom( const Atom& a_src )	{}
	Atom& operator=( const Atom& a_src ) {}
	virtual ~Atom() 			{}

	
	virtual RefCountedCell&	operator() ( RefCountedCell&	a_input ) 
	{
		Cell::Factory factory;
		RefCountedCell& result = factory.allocate(); 

		// t if a_input is Nil
		if( a_input->isScalar() )
		{
			result->scalar( new Scalar("T") );
		}
		return result;
	}
};

#endif // _INCLUDE_ATOM_HPP
