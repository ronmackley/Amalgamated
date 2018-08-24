//***************************************************************************
//
//	NilNode.cpp -- Defintion of a no-value Node
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
#include "NilNode.hpp"
#endif

#include <stdlib.h>

// The Nil node. Cover your eyes lest you melt.
Node*	nil = NULL;

//*****************************************************************************
//
//	IsNil - test to see whether a node is nil.
//
//	Parameters:
//		a_nodeToTest - the node to test for nilness
//
//	Returns:
//		true - the node is nil
//		false - the node is non-nil
//
//	Note:
//		The definition of nil-ness is if the address of the node is equal to
//		the address of The Nil Node
//
//*****************************************************************************
bool	IsNil( Node& a_nodeToTest )
{
	if( &a_nodeToTest != nil ) return false;
	return true;
}

//*****************************************************************************
//*****************************************************************************
Node*	MakeNilNode()
{
	// Cause one to be created, populating the global nil ptr
	NilNode	   nilNode;
	return nil;
}


//*****************************************************************************
//*****************************************************************************
NilNode::NilNode()
{
	if( nil == NULL )
	{
		// Create the one true nil node.
		//! Trust that the memory will be released when the app exits.
		nil = new NilNode();
	}
	
}

//*****************************************************************************
//*****************************************************************************
NilNode::~NilNode()
{
	// Empty
}

