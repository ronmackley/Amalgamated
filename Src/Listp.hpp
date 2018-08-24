//***************************************************************************
//
//	ListP.hpp -- declaration a class for returning whether a Cell is an ListP
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

#ifndef _INCLUDE_LISTP_HPP_
#define _INCLUDE_LISTP_HPP_

// Application headers
#ifndef _INCLUDE_FUNCTION_HPP_
#include "Function.hpp"
#endif

#ifndef _INCLUDE_CELL_HPP_
#include "Cell.hpp"
#endif

// System headers
#include <cstdlib>
#include <iostream>


//**********************************************************************
// ListP class - a class for telling whether its argument is an atom
//**********************************************************************
class ListP : public Function {

public:

	ListP() 						{}
	ListP( const ListP& a_src )	{}
	ListP& operator=( const ListP& a_src ) {}
	virtual ~ListP() 			{}

	
	virtual RefCountedCell&	operator() ( RefCountedCell&	a_input ) 
	{
std::cerr << "enter listp operator()" << std::endl;
		Cell::Factory factory;
		RefCountedCell& result = factory.allocate(); 
		result->scalar(new Scalar("Flurble"));
		// t if a_input is a list
		if( a_input->isList() )
		{
			result->scalar( new Scalar("T") );
		}
std::cerr << "exit listp operator()" << std::endl;
		return result;
	}
};

#endif // _INCLUDE_ATOM_HPP
