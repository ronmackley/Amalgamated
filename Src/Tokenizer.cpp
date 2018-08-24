//***************************************************************************
//
//	Tokenizer.cpp -- definition of a token generator for Lisp tokens
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

#ifndef _INCLUDE_TOKENIZER_HPP_
#include "Tokenizer.hpp"
#endif

#include <cctype>
#include <cassert>

// using declarations
using namespace std;

//*****************************************************************************
//
//
//
//*****************************************************************************
namespace
{
	// Character to start a quoted string
	char s_qStringChar = '"';
	char s_listOpenChar = '(';
	char s_listCloseChar = ')';
	
}

//*****************************************************************************
//
//
//
//*****************************************************************************
Tokenizer::Tokenizer( std::string& a_inputData ) : 
	d_inputData(a_inputData), 
	d_inputDataIter(d_inputData.begin()), 
	d_inputDataEnd(d_inputData.end())
{
	// nothing to do
}

//*****************************************************************************
//
//
//
//*****************************************************************************
Tokenizer::~Tokenizer() 
{
	// nothing to do
}


//*****************************************************************************
//
//
//
//*****************************************************************************
const Tokenizer::Token* Tokenizer::getNextToken()
{
	return parseFundamental( d_inputDataIter, d_inputDataEnd );	
}

//*****************************************************************************
//
//	Tokenizer::parseFundamental -	top level parse routeine. Calls
//									lower level routines. Returns one
//									token at a time.
//	
//	PARAMETERS;
//		a_string -	string to be parsed pointer is updated to the first
//					position after the token.
//
//	RETURNS:
//		token
//
//*****************************************************************************
const Tokenizer::Token* Tokenizer::parseFundamental( string::const_iterator& a_stringIter,
													 const string::const_iterator& a_stringEnd ) const
{
	while( a_stringIter != a_stringEnd )
	{
		if( isspace(*a_stringIter) )
		{
			a_stringIter++;
			continue;
		}
		else if( *a_stringIter == s_listOpenChar )
		{
			a_stringIter++;
			return new Token( listOpen, "(" );
		}
		else if( *a_stringIter == s_listCloseChar )
		{
			a_stringIter++;
			return new Token( listClose, ")" );
		}
		if( *a_stringIter == s_qStringChar )
		{
			return parseQString( a_stringIter, a_stringEnd );
		}
		//! TODO: create a better isgraph functor
		else if ( ::isgraph(*a_stringIter ) )
		{
			// decrement string so the matching char is still in the string
			return parseToken(  a_stringIter, a_stringEnd );
		}
		else
		{
			std::cout << "Tokenizer::parseFundamental - fatal error";
			throw "Tokenizer::parseFundamental - fatal error";
		}
		a_stringIter++;
	}
	// Default case
	return NULL;
}

//*****************************************************************************
//
//	Tokenizer::parseQString -	low level parse routine to parse a quoted
//								string
//	PARAMETERS;
//		a_string -	string to be parsed pointer is updated to the first
//					position after the token.
//
//	RETURNS:
//		token
//
//*****************************************************************************
inline const Tokenizer::Token* Tokenizer::parseQString( 
		string::const_iterator& a_stringIter,
		const string::const_iterator& a_stringEnd ) const
{
	string::const_iterator start = a_stringIter;

	// we should be on the opening s_qStringChar
	assert( *a_stringIter == s_qStringChar );

	string	quotedString;

	// consume the quote
	quotedString += *a_stringIter++;

	while( *a_stringIter != s_qStringChar )
	{
		// If we hit the end while parsing the token put back what we parsed so far
		// and return NULL. Let caller cope.
		if( a_stringIter == a_stringEnd )
		{
			a_stringIter = start;
			return NULL;
		}

		quotedString += *a_stringIter++;
	}
	// we should be on the closing s_qStringChar
	assert( *a_stringIter == s_qStringChar );
	// consume the closing quote.
	quotedString += *a_stringIter++;
	return new Token( qString, quotedString );
	
}

//*****************************************************************************
//
//	Tokenizer::parseToken -	low level parse routine to parse an
//							alphanumeric token
//	PARAMETERS;
//		a_string -	string to be parsed pointer is updated to the first
//					position after the token.
//
//	RETURNS:
//		token
//
//*****************************************************************************
inline const Tokenizer::Token* Tokenizer::parseToken(
		string::const_iterator& a_stringIter,
		const string::const_iterator& a_stringEnd ) const
{
	string	tokenString;

	while( a_stringIter != a_stringEnd )
	{
		if (	!::isgraph( *a_stringIter) || 
				*a_stringIter == ')' ||
				*a_stringIter == '(' )
		{
			break;
		}
		tokenString += *a_stringIter++;
	}
	return new Token( token, tokenString );
	
}
