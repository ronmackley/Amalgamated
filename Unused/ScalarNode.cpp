//*****************************************************************************
//
//
//
//*****************************************************************************

#ifndef _INCLUDE_SCALARNODE_HPP_
#include "ScalarNode.hpp"
#endif

#include <cstring>
#include <cstdlib>
#include <cstdio>

#include <sstream>
  
//*****************************************************************************
//*****************************************************************************
ScalarNode::ScalarNode( const ScalarNode& a_src ) 
: 	Node( a_src ), 
	d_longVal(a_src.d_longVal), 
	d_stringVal(a_src.d_stringVal)
{
	// Nothing special
}

//*****************************************************************************
//*****************************************************************************
ScalarNode::ScalarNode( long a_longVal )
{
	d_longVal = a_longVal;
//!	d_stringVal << d_longVal;
}

//*****************************************************************************
//*****************************************************************************
ScalarNode::ScalarNode( const char* a_stringVal )
{
	d_stringVal = a_stringVal;
	d_longVal = atoi( a_stringVal );
}

//*****************************************************************************
//*****************************************************************************
ScalarNode::~ScalarNode()
{
	// Nothing to do
}

//*****************************************************************************
//*****************************************************************************
ScalarNode&		ScalarNode::operator=( const ScalarNode& a_src )
{
	return *(new ScalarNode( a_src ));
}

