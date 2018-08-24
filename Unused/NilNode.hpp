//***************************************************************************
//
//	NilNode.hpp -- Declaration of a no-value Node
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

#ifndef _INCLUDE_NILNODE_HPP_
#define _INCLUDE_NILNODE_HPP_

#ifndef _INCLUDE_NODE_HPP_
#include "Node.hpp"
#endif

// The definition of Nil. Revere in all of its splendour.
extern	Node*	nil;
#define	Nil		*nil

bool	IsNil( Node&	a_nodeToTest );
Node*	MakeNilNode();

class NilNode : public Node
{
	friend Node* MakeNilNode();
	// All ctor's are private Nobody should be instantiating this
				NilNode();
				NilNode( const NilNode& a_src );

	NilNode&	operator=( const NilNode& a_src );

  public:
	virtual		~NilNode();
};

#endif
