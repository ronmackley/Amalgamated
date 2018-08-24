//***************************************************************************
//
//	ConsNode.hpp -- Declaration of a 2-way node
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

#ifndef _INCLUDE_CONSNODE_HPP_
#define _INCLUDE_CONSNODE_HPP_

#ifndef _INCLUDE_NODE_HPP_
#include "Node.hpp"
#endif

#ifndef _INCLUDE_NILNODE_HPP_
#include "NilNode.hpp"
#endif

#include <cstdlib>

class ConsNode : public Node
{
	// Conses are two way branched tree nodes
	Node*		d_left;
	Node*		d_right;

  public:
// 				ConsNode( );
				//TODO: There has to be something better than NULL for Nil nodes
				ConsNode( Node* a_left = NULL,
						  Node* a_right = NULL);
				ConsNode( const ConsNode& a_src );
	virtual		~ConsNode();

	ConsNode&	operator=( const ConsNode& a_src );

	// Functions to make the tree or list happen
	Node*		left()	   { return d_left; }
	Node*		right()	   { return d_right; }
  
};

#endif
