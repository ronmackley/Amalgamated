//***************************************************************************
//
//  Writer.cpp -- Defintion of a class to serialize a structure of Cells.
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

#include "Writer.hpp"

#include "Cell.hpp"
#include "Scalar.hpp"

using namespace std;

//***************************************************************************
//***************************************************************************
Writer::Writer()
{
	// Nothing to do.
}

//***************************************************************************
//***************************************************************************
Writer::~Writer()
{}

//***************************************************************************
//***************************************************************************
void	Writer::toString( const RefCountedCell& a_head, std::ostream& a_out ) const
{
	//! TODO: smarter writer that can do the right thing with spaces between tokens

// 	a_out.setf( std::ios_base::hex, std::ios_base::basefield );
// 	a_out << a_head.ptr() << ":" << a_head->first().ptr() << '.' << a_head->second().ptr();

	// If the first (value) side is a list write out the open paren
	if( a_head.assigned() && a_head->first().assigned() && a_head->first()->isList() )
	{
		a_out << '(';
	}
	if( a_head->isNil() ) 
	{
		a_out << "nil" << endl;
	}
	else if( a_head->isScalar() )
	{
		a_out << a_head->scalar().asString();
	}
	else if( a_head->isList() )
	{
		toString( a_head->first(), a_out );
	}
	
	if( a_head->second().assigned() && a_head->second()->first().assigned() /*&& a_head->second()->first()->isScalar() */)
	{
		a_out << " ";
	}

	if( a_head->second().assigned() )
	{
		if( false && a_head->second()->isNil() )
		{
			a_out << "nil" << std::endl;
		}
		else if( a_head->second()->isScalar() )
		{
			a_out << " . ";
			a_out << a_head->second()->scalar().asString();
		}
		else if( a_head->second()->isList() )
		{
			toString( a_head->second(), a_out);
		}
/*		else
		{
			a_out << "Don't know what to do with second.";
			throw "Don't know what to do with second.";
		}*/
	}

	// If the first (value) side is a list write out the close paren
	if( a_head.assigned() && a_head->first().assigned() && a_head->first()->isList() )
	{
		a_out << ')';
	}
}
