//***************************************************************************
//
//  Scalar.hpp -- Declaration of a class to hold something
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

#ifndef SCALAR_HPP
#define SCALAR_HPP

#include <string>

class Scalar{
	
	class _impl;
	_impl*				d_impl;

	// called by factory

	// not defined
	Scalar();
	Scalar&	operator=( const Scalar& a_other ) const;

public:


	Scalar( const char*	a_value );
	Scalar( const std::string& a_value );
	Scalar( const Scalar& a_other );
	~Scalar();

//	// Class to manage the allocation and release of Scalars
//	class Factory
//	{
//		public:
//			Factory();
//			~Factory();
//			Scalar*		allocate( const char*	a_value );
//			Scalar*		allocate( const std::string& a_value );
//			void		release( Scalar* a_scalar );
//	};
//
	// Force eql and equal to be used.
	bool	operator==( const Scalar& ) const;
	
	bool	eql( const Scalar& a_other ) const
	{
		// two scalars are eql iff they have the same address
		return this == &a_other;
	}
	bool	equal( const Scalar& a_other ) const;
	
	long				asLong()	const;
	double				asDouble()	const;
	const std::string&	asString()	const;

	static bool			test();
	
};

// test declaration
int Scalar_test( int argc =0, char** argv = NULL);

#endif // SCALAR_HPP
