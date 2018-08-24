//***************************************************************************
//
//  Writer.hpp -- Defintion of a class to serialize a structure of Nodes.
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

#ifndef WRITER_HPP
#define WRITER_HPP 1

#include "Cell.hpp"

#include <iostream>

class Writer{

public:

		Writer();
		~Writer();

void	toString( const RefCountedCell& a_head, std::ostream& a_out) const;
};

// declaration of test interface
int Writer_test( int argc = 0, char** argv = NULL );

#endif // WRITER_HPP
