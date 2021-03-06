//***************************************************************************
//
//	ConsNode.cpp -- Definition of a 2-way node
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
#include "ConsNode.hpp"
#endif

#ifndef _INCLUDE_NILNODE_HPP_
#include "NilNode.hpp"
#endif

//*****************************************************************************
//*****************************************************************************
// ConsNode::ConsNode( )
//   : d_left(NULL), d_right(NULL)
// {
// 	// Empty
// }

//*****************************************************************************
//*****************************************************************************
ConsNode::ConsNode( Node* a_left, Node* a_right )
  : d_left(a_left),	d_right(a_right)
{
	// Empty
}

//*****************************************************************************
//*****************************************************************************
ConsNode::ConsNode( const ConsNode& a_src )
  : d_left(a_src.d_left), d_right(a_src.d_right)
{
	// Empty
}

//*****************************************************************************
//*****************************************************************************
ConsNode::~ConsNode()
{
	// Nothing to do
}

//*****************************************************************************
//*****************************************************************************
ConsNode&		ConsNode::operator=( const ConsNode& a_src )
{
	return *(new ConsNode( a_src ));
}

