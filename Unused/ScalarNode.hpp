//*****************************************************************************
//
//
//
//*****************************************************************************

#ifndef _INCLUDE_SCALARNODE_HPP_
#define _INCLUDE_SCALARNODE_HPP_

#ifndef _INCLUDE_NODE_HPP_
#include	"Node.hpp"
#endif

#include <string>

using std::string;
  
class ScalarNode : Node
{
	long					d_longVal;
	string					d_stringVal;
			
  public:
	ScalarNode( const ScalarNode& a_src );
	ScalarNode( long			a_longVal );
//TODO: Add double ctor
//	ScalarNode( double			a_longVal );
	ScalarNode(	const char*		a_stringVal );	
	ScalarNode(	const string&	a_stringVal );	
	~ScalarNode();

	ScalarNode&	operator=( const ScalarNode& a_src );

	operator	long() const		{ return getLong(); }
    operator	const char*() const	{ return getCharPtr(); }
    operator	const string&() const	{ return getString(); }

	long		getLong() const		{ return d_longVal; }
	const string& getString() const	{ return d_stringVal; }
	const char* getCharPtr() const	{ return d_stringVal.c_str(); }
};

#endif
