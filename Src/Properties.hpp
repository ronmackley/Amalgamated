//***************************************************************************
//
//  Properties.Hpp -- Declaration of an a set of keys associated 
//                     with an object
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

#ifndef PROPERTIES_HPP
#define PROPERTIES_HPP

// TODO: Build out Properties class

class Properties{
public:

	Properties();
	~Properties();

	// See cpp for implementation. se pimpl pattern to encapsulate
	class _impl;
	_impl*		d_impl;

};

#endif // PROPERTIES_HPP
