//***************************************************************************
//
//	Cell.cpp -- definition a class for holing either a value or a list node
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

#include <cassert>
#include <iostream>
#include <vector>

#include "Cell.hpp"

//***************************************************************************
//
//	Cell::Cell() - Default constructor for a Cell
//
//	Sets the cell to hold nothing, the atom and list values are NULL
//
//***************************************************************************
Cell::Cell() : d_first( NULL ), d_second( NULL ), d_scalar( NULL ), d_properties( NULL )
{
  // Nothing to do
}

//***************************************************************************
//
//	Cell::Cell() - Default constructor for a Cell
//
//	Sets the cell to hold nothing, the atom and list values are NULL
//
//***************************************************************************
Cell::~Cell()
{
	if( isScalar() )
		std::cout << "s" << std::flush;
	else if (isNil() )
		std::cout << "n" << std::flush;
	else
		std::cout << "l" << std::flush;
	
	
  // Nothing to do
}

//***************************************************************************
//
//	Cell::Cell() - Default constructor for a Cell
//
//	Sets the cell to hold nothing, the atom and list values are NULL
//
//***************************************************************************
Cell::Cell( const Cell& a_src )
{}

//***************************************************************************
// Cell Factory member functions
//***************************************************************************

//***************************************************************************
//***************************************************************************
Cell::Factory::Factory()
{
  // nothing to do.
}

//***************************************************************************
//***************************************************************************
Cell::Factory::~Factory()
{
  // nothing to do.
}

//***************************************************************************
//***************************************************************************
RefCountedCell&	Cell::Factory::allocate()
{
  //	std::cout << "Allocate: ";
  RefCountedCell * cell = new RefCountedCell( new Cell() );
  //	std::cout << "new Cell created ";
  //	std::cout << std::endl;
  return *cell;
}

//***************************************************************************
//***************************************************************************
void	Cell::Factory::release( RefCountedCell& a_cell )
{
  //	std::cout << "Release: " << &a_cell;
  delete & a_cell;
  //	std::cout  << std::endl;
}

