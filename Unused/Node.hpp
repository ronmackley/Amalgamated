//***************************************************************************
//
//	Node.hpp -- Declaration of an object to hold a value
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

#ifndef _INCLUDE_NODE_HPP_
#define _INCLUDE_NODE_HPP_


// Abstract base class for node types to derive off of

class Node
{
  public:
				Node();
				Node( const Node& a_src );
	virtual		~Node();

	Node&		operator=( const Node& a_src );
};

#endif
