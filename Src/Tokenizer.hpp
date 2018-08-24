//***************************************************************************
//
//	Tokenizer.hpp -- declaration of a token generator for Lisp tokens
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
#define _INCLUDE_TOKENIZER_HPP_

#include <iostream>
#include <string>

//*****************************************************************************
//
//*****************************************************************************
class Tokenizer
{
public:
	struct Token;
	// Class specific types
	enum	State
	{
		fundamental = 0,
		qString		= 1,
		token		= 2,
		listOpen	= 10,
		listClose	= 11,
		error 		= 99
	};
	
	private:
	// Data members			
	const std::string					d_inputData;
	mutable std::string::const_iterator	d_inputDataIter;
	const std::string::const_iterator	d_inputDataEnd;
	// Keep default ctors and operators from being implied	
	Tokenizer( const Tokenizer& a_src );
	Tokenizer& operator = ( const Tokenizer& a_src );

	// Worker functions
	const Token*	parseToken( std::string::const_iterator& a_stringIter,
								const std::string::const_iterator& a_stringEnd ) const ;
	const Token*	parseQString( std::string::const_iterator& a_stringIter,
								  const std::string::const_iterator& a_stringEnd ) const;
	const Token*	parseFundamental( std::string::const_iterator& a_stringIter,
									  const std::string::const_iterator& a_stringEnd ) const;
	
  public:
	Tokenizer( std::string& a_inputData );
	~Tokenizer();
		
	const Token*	getNextToken();
		
	//***********************************************************************************************
	// The token type that gets returned by the get method	
	//***********************************************************************************************
	struct	Token
	{
		State		d_state;
		std::string	d_data;
		
		Token(  State a_state,
				std::string a_data ) :
			d_state( a_state),
			d_data( a_data )
		{
			// Nothing else to do
		}

		// Accessor functions
		const std::string&		getData() const {	return d_data;	}
		State					getState() const	{	return d_state;	}

	  private:
	  	// Keep defaults from being implied
  		Token();
  		Token( const Token& );
  		Token& operator = ( const Token& );

			
	};	
	
};

#endif
