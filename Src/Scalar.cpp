//***************************************************************************
//
//  Scalar.cpp -- Defintion of a class to hold something
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

#include "Scalar.hpp"

#include <cerrno>
#include <cstdlib>
#include <iostream>

//***************************************************************************
//***************************************************************************
class Scalar::_impl
{
	std::string d_string;
	
	// Keep default creation mechanisms from being called accidentally
	_impl(); // undefined default ctor
// 	_impl& operator=(const _impl& a_src); // undefined assignment operator
  public:
	_impl(const std::string& a_string): d_string(a_string)	{}
	_impl(const char* a_string): d_string(a_string)			{}
	_impl(const _impl& a_src) :	d_string( a_src.d_string )	{}
	_impl& operator=(const _impl& a_src) 
	{	this->d_string = a_src.d_string; 
		return *this; 
	}

	const char* c_str() const			{ return d_string.c_str(); }
	const std::string& string() const	{ return d_string; }

	//TODO: do I need something other than == here?
	bool  equal( const _impl& a_other ) { return d_string == a_other.d_string; }

};

//***************************************************************************
//***************************************************************************
Scalar::Scalar() : d_impl( new _impl("") )
{
}

//***************************************************************************
//***************************************************************************
Scalar::Scalar( const char*	a_value ) : d_impl( new _impl(a_value) )
{
}

//***************************************************************************
//***************************************************************************
Scalar::Scalar( const std::string&	a_value ) : d_impl( new _impl(a_value ) )
{
}

//***************************************************************************
//***************************************************************************
Scalar::Scalar( const Scalar& a_src ) : d_impl( new _impl(*a_src.d_impl ) )
{
}
//***************************************************************************
//***************************************************************************
Scalar::~Scalar()
{
	delete d_impl;
}

//***************************************************************************
//***************************************************************************
long				Scalar::asLong() const
{
	const char* string= d_impl->c_str();
	char*	endptr = (char*)string + strlen(string);
	long result = strtol( string, &endptr, 10 );

	// if conversion failed return 0
	if( errno != 0 ) result = 0L;

	return result;
}

//***************************************************************************
//***************************************************************************
double				Scalar::asDouble() const
{
	const char* string= d_impl->c_str();
	char*	endptr = (char*)string + strlen(string);
	double result = strtod( string, &endptr );

	// if conversion failed return 0
	if( errno != 0 ) result = 0.0;

	return result;
}

//***************************************************************************
//***************************************************************************
const std::string&	Scalar::asString() const
{
	return d_impl->string();
}	

//***************************************************************************
//***************************************************************************
bool Scalar::equal( const Scalar& a_other) const
{
	return d_impl->equal( *(a_other.d_impl) );
}	

//***************************************************************************
//***************************************************************************
bool			Scalar::test()
{
	return false;
}
