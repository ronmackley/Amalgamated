/***************************************************************************
 *   Copyright (C) 2006 by Ron Mackley   *
 *   ronmackley@yahoo.com   *
 *                                                                         *
 *   Permission is hereby granted, free of charge, to any person obtaining *
 *   a copy of this software and associated documentation files (the       *
 *   "Software"), to deal in the Software without restriction, including   *
 *   without limitation the rights to use, copy, modify, merge, publish,   *
 *   distribute, sublicense, and/or sell copies of the Software, and to    *
 *   permit persons to whom the Software is furnished to do so, subject to *
 *   the following conditions:                                             *
 *                                                                         *
 *   The above copyright notice and this permission notice shall be        *
 *   included in all copies or substantial portions of the Software.       *
 *                                                                         *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       *
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    *
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. *
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR     *
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, *
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR *
 *   OTHER DEALINGS IN THE SOFTWARE.                                       *
 ***************************************************************************/
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

#ifndef _INCLUDE_CELL_HPP_
#define _INCLUDE_CELL_HPP_

// Application headers
#ifndef _INCLUDE_SCALAR_HPP_
#include "Scalar.hpp"
#endif

#ifndef _INCLUDE_PROPERTIES_HPP_
#include "Properties.hpp"
#endif

#ifndef _INCLUDE_REFCOUNTED_HPP_
#include "ref_counted.hpp"
#endif
	
// System headers
#include <cstdlib>


//**********************************************************************
// Forward Declaraions
//**********************************************************************

class Cell;
typedef ref_counted<Cell> RefCountedCell;
typedef ref_counted<Scalar> RefCountedScalar;
typedef ref_counted<Properties> RefCountedProperties;

//**********************************************************************
// Class Cell
//**********************************************************************
class Cell{

	// Cell can be either a list or an atom
	RefCountedCell			d_first;
	RefCountedCell			d_second;
	RefCountedScalar		d_scalar;
	RefCountedProperties	d_properties;
	
public:

	explicit Cell();
	explicit Cell( const Cell& a_src );
	Cell& operator=( const Cell& a_src );
	~Cell();

	RefCountedScalar::ConstRefType
					scalar() const		{ return *d_scalar.constPtr(); }
	void			scalar( Scalar* a_scalar )	{ d_scalar.set( a_scalar ); }

	RefCountedProperties::ConstRefType	
					properties() const 	{ return *d_properties.constPtr(); }

	// this should be const
	RefCountedCell&	first()	{ return *(new RefCountedCell(d_first)); }
	void			first( Cell* a_first )	{ d_first.set(a_first); }
	void			first( RefCountedCell& a_first )	{ d_first = a_first; }
	
	// this should be const
	RefCountedCell&	second()	{ return *(new RefCountedCell(d_second)); }
	void			second( Cell* a_second )	{ d_second.set(a_second); }
	void			second( RefCountedCell& a_second )	{ d_second = a_second; }

	// A cell is nil of all pointers are NULL
	bool			isNil()	const { 
		bool assigned =	d_first.assigned() || 
						d_second.assigned() ||
						d_scalar.assigned();
		return !assigned;
	}

	// A cell is list if d_scalar is null and d_first or d_second are
	// non-null
	bool	isList()	const { 
		bool result =	(d_first.assigned() || d_second.assigned()) &&
					!d_scalar.assigned();
		return result;
	}

	// A cell is scalar if d_scalar has a value and d_first and d_second are
	// null
	bool	isScalar()	const { 
		return d_scalar.assigned() && 
				!( d_first.assigned() || d_second.assigned() );
	}

	class Factory
	{
		public:
			Factory();
			~Factory();
			RefCountedCell&		allocate();
			void				release( RefCountedCell& a_cell );
	};
};

// declaration of test interface
int Cell_test( int argc = 0, char** argv = NULL );

#endif // CELL_HPP
