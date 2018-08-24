//***************************************************************************
//
//	Lexer.cpp -- Hard-coded Lexical Analyzer for Lisp
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

#ifndef LEXER_HPP
#include "Lexer.hpp"
#endif

#include <cctype>
#include <cstdlib>
#include <cassert>
#include <iostream>

using std::string;



//****************************************************************************
//****************************************************************************

Lexer::Lexer()
{
	// Nothing to do.
}

//****************************************************************************
//****************************************************************************
Lexer::~Lexer()
{
	// Nothing to do.
}

	
//****************************************************************************
//****************************************************************************
bool	Lexer::parse(	const std::string&	a_input,
						TokenVector&		a_tokens,
						std::string&		a_remainder,
						long				a_numTokens )
{
	//verify that remainder is not input
	//! For some reason this is lighting up (18Feb05)
	//assert( &a_remainder != &a_input );

	string::const_iterator current = a_input.begin();
	string::const_iterator end = a_input.end();

	string::const_iterator tokenStart;

std::cerr << "About to parse: "<< a_input << std::endl;

	for(;;)
	{
		if( current == end ) break;
		
		// set up to parse the next token. This is where remainder will start
		// if parsing ends. tokenStart is effectively const after this point.
		tokenStart = current;
		
		if( *current == '(' )
		{
			if( parseListOpen( tokenStart, end, current, a_tokens ) == false )
			{
				break;
			}
			// assert that current has moved past where parsing started
			assert( current > tokenStart );
			continue;			
		}
		else if( *current == ')' )
		{
			if( parseListClose( tokenStart, end, current, a_tokens ) == false )
			{
				break;
			}
			// assert that current has moved past where parsing started
			assert( current > tokenStart );
			continue;			
		}

		else if( *current == '"' )
		{
			if( parseQuotedString( tokenStart, end, current, a_tokens ) == false )
			{
				break;
			}
			// assert that current has moved past where parsing started
			assert( current > tokenStart );
			continue;			
		}

		else if( *current == ';' )
		{
			if( parseComment( tokenStart, end, current, a_tokens ) == false )
			{
				break;
			}
			// assert that current has moved past where parsing started
			assert( current > tokenStart );
			continue;			
		}

		else if( ::isspace(*current) )
		{
			parseWhiteSpace( tokenStart, end, current, a_tokens );
			// assert that current has moved past where parsing started
			assert( current > tokenStart );
			continue;			
		}

		// If it's not any of the above try to parse a token
		else
		{
			parseToken( tokenStart, end, current, a_tokens );
			// assert that current has moved past where parsing started
			assert( current > tokenStart );
			continue;			
		}
	}
	a_remainder.assign( tokenStart, end );
	return true;	
}

	

//****************************************************************************
//****************************************************************************
bool Lexer::parseQuotedString(	const string::const_iterator&	a_tokenStart,
								const string::const_iterator&	a_end,
								string::const_iterator&			a_current,
								TokenVector&					a_tokens )
{
	assert( a_tokenStart == a_current );

	// parse characters until the end of the line

	string	tokenText;
	char	escdChar;
	
	// get past opening quote
	++a_current;
	
	while( *a_current != '"' )
	{
		if( *a_current == '\\' )
		{
			// deal with an escaped character
			string::const_iterator	seqStart = a_current;
			parseEscapeSequence( seqStart, a_end, a_current, escdChar );
			
			assert( a_current != seqStart );	
			tokenText += escdChar;
		}
		else
		{
			// otherwise append the next character
			tokenText += *a_current;
			++a_current;
		}
		if( a_current == a_end )
		{
			return false;
		}
		
	}
	
	++a_current;
	
	Token	tok;
	tok.d_type = quotedString;
	tok.d_text.assign( tokenText );
std::cerr << "parseQuotedString::tokenText: " << tokenText << std::endl;
	a_tokens.push_back( tok );

	return true;
	
	
	
}

//****************************************************************************
//****************************************************************************
bool Lexer::parseToken(		const string::const_iterator&	a_tokenStart,
							const string::const_iterator&	a_end,
							string::const_iterator&			a_current,
							TokenVector&					a_tokens )
{
	//TODO: Do better than just ! whitespace	
	assert( a_tokenStart == a_current );

	string	tokenText;
	char	escdChar;
	while( a_current != a_end )
	{
		if( ::isspace( *a_current ) )
		{
			break;
		}
		else if( *a_current == '\\' )
		{
			// deal with an escaped character
			string::const_iterator	seqStart = a_current;
			parseEscapeSequence( seqStart, a_end, a_current, escdChar );
			
			assert( a_current != seqStart );	
			tokenText += escdChar;
		}
		else
		{
			// otherwise append the next character
			tokenText += *a_current;
			++a_current;
		}
	}
	// Current should be whitespace or there should be no more test to parse

	assert( ::isspace( *a_current ) || a_current == a_end );


	Token	tok;
	tok.d_text.assign( tokenText );
	// Check for the special case of the token being "quote"
	if( tokenText == "quote" )
	{
		tok.d_type = quote;
	}
	else
	{
		tok.d_type = token;
	}

	a_tokens.push_back( tok );

	return true;
	
	
}

//****************************************************************************
//****************************************************************************
bool Lexer::parseQuote(	const string::const_iterator&	a_tokenStart,
						const string::const_iterator&	a_end,
						string::const_iterator&			a_current,
						TokenVector&					a_tokens )
{
	// Trivial case. Token is exactly one character.
	assert( a_tokenStart == a_current );

	Token	tok;
	tok.d_type = quote;
	tok.d_text.assign( a_tokenStart, a_current );
	a_tokens.push_back( tok );
	++a_current;
	return true;
}


//****************************************************************************
//****************************************************************************
bool Lexer::parseListOpen(	const string::const_iterator&	a_tokenStart,
							const string::const_iterator&	a_end,
							string::const_iterator&			a_current,
							TokenVector&					a_tokens )
{
	// Trivial case. Token is exactly one character.
	assert( a_tokenStart == a_current );

	Token	tok;
	tok.d_type = listOpen;
	tok.d_text.assign( a_tokenStart, a_current );
	a_tokens.push_back( tok );
	++a_current;
	return true;
}

//****************************************************************************
//****************************************************************************
bool Lexer::parseListClose(	const string::const_iterator&	a_tokenStart,
							const string::const_iterator&	a_end,
							string::const_iterator&			a_current,
							TokenVector&					a_tokens )
{
	// Trivial case. Token is exactly one character.
	assert( a_tokenStart == a_current );

	Token	tok;
	tok.d_type = listClose;
	tok.d_text.assign( a_tokenStart, a_current );
	a_tokens.push_back( tok );
	++a_current;
	return true;
}


//****************************************************************************
//****************************************************************************
bool Lexer::parseWhiteSpace(	const string::const_iterator&	a_tokenStart,
								const string::const_iterator&	a_end,
								string::const_iterator&			a_current,
								TokenVector&					a_tokens )
{
	assert( a_tokenStart == a_current );

	string	tokenText;
	while( ::isspace(*a_current) )
	{
		tokenText += *a_current;
		++a_current;
	}
	// Current should not be whitespace

	assert( ! ::isspace( *a_current ) );

	Token	tok;
	tok.d_type = whiteSpace;
	tok.d_text.assign( tokenText );
	a_tokens.push_back( tok );

	return true;
}
//****************************************************************************
//****************************************************************************
bool Lexer::parseComment(	const string::const_iterator&	a_tokenStart,
							const string::const_iterator&	a_end,
							string::const_iterator&			a_current,
							TokenVector&					a_tokens )
{
	assert( a_tokenStart == a_current );

	// parse characters until the end of the line
	string	tokenText;
	while( *a_current != '\r' && *a_current != '\n' )
	{
		tokenText += *a_current;
		++a_current;
	}
	
	// Slurp up \n in \r\n
	if( *a_current == '\r' )
	{
		if( *(a_current+1) == '\n' )
		{
			++a_current;
		}
	}
	// Current should not be whitespace

	assert( ! ::isspace( *a_current ) );

	Token	tok;
	tok.d_type = whiteSpace;
	tok.d_text.assign( tokenText );
	a_tokens.push_back( tok );

	return true;
}

//****************************************************************************
//****************************************************************************
bool Lexer::parseEscapeSequence(	const string::const_iterator&	a_tokenStart,
									const string::const_iterator&	a_end,
									string::const_iterator&			a_current,
									char&							a_escapedChar )
{
	assert( a_tokenStart == a_current );
	// advance past the escape character
	++a_current;
	
	for(;;)
	{
		if( *a_current == 'x' )
		{
			// Increment past the 'x'
			++a_current;

			string::const_iterator shadowTokenStart = a_current;
			
			do			
			{
				++a_current;
			}
			while( isxdigit(*a_current) );

			// a_current should be in the first non-hex digit
			string	hexString( shadowTokenStart, a_current);

			//TODO: Get a better way than strtol to get a hex string into a long
			// get a char* for the string of characters to use for the conversion
			//? Can I pas a string::const_iterator for a const char*
			const char*	hexChars = hexString.c_str();
			char*		endChars;

			long	hexValue = strtol( hexChars, &endChars, 16 );

			// Mask out the HOB and return only what is in the LOB
			a_escapedChar = hexValue & 0x00FF;
			break;
		}
		else if( *a_current == '0' )
		{
			// do octal things
			
			string::const_iterator shadowTokenStart = a_current;
			
			//! 8 and 9 are valid octal digits in this scheme
			do
			{
				++a_current;
			}
			while( ::isdigit(*a_current) );
			
			// a_current should be in the first non-octal digit
			string	octalString( shadowTokenStart, a_current );

			//TODO: Get a better way than strtol to get an octgal string into a long
			// get a char* for the string of characters to use for the conversion
			//? Can I pas a string::const_iterator for a const char*
			const char*	octalChars = octalString.c_str();
			char*		endChars;

			long	octalValue = strtol( octalChars, &endChars, 8 );

			// Mask out the HOB and return only what is in the LOB
			a_escapedChar = octalValue & 0x00FF;
			break;
		}
		else if( *a_current == '#' )
		{
			// do decimal things
			
			// Increment past the '#'
			++a_current;
			
			string::const_iterator shadowTokenStart = a_current;
			
			do
			{
				++a_current;
			}
			while( isdigit(*a_current) );

			// a_current should be in the first non-octal digit
			string	decString( shadowTokenStart, a_current);

			//TODO: Get a better way than strtol to get an octgal string into a long
			// get a char* for the string of characters to use for the conversion
			//? Can I pas a string::const_iterator for a const char*
			const char*	decChars = decString.c_str();
			char*		endChars;

			long		decValue = strtol( decChars, &endChars, 10 );

			// Mask out the HOB and return only what is in the LOB
			a_escapedChar = decValue & 0x00FF;
			break;
		}
		else if( *a_current == 'a' )
		{
			// beep
			a_escapedChar='\a';
			++a_current;
			break;
		}
		else if( *a_current == 't' )
		{
			// tab
			a_escapedChar='\t';
			++a_current;
			break;
		}
		else if( *a_current == 'n' )
		{
			// linefeed
			a_escapedChar='\n';
			++a_current;
			break;
		}
		else if( *a_current == 'r' )
		{
			// carriage return
			a_escapedChar='\r';
			++a_current;
			break;
		}
		else if( *a_current == 'v' )
		{
			// vertical tab
			a_escapedChar='\v';
			++a_current;
			break;
		}
		else if( *a_current == 'f' )
		{
			// form feed
			a_escapedChar='\f';
			++a_current;
			break;
		}
		else if( *a_current == 'b' )
		{
			// backspace
			a_escapedChar='\b';
			++a_current;
			break;
		}
		else if( *a_current == ' ' )
		{
			// space
			a_escapedChar=' ';
			++a_current;
			break;
		}
		else if( *a_current == '\\' )
		{
			// backslash
			a_escapedChar='\\';
			++a_current;
			break;
		}
		else if( *a_current == '"' )
		{
			// double quote
			a_escapedChar='"';
			++a_current;
			break;
		}
		else if( *a_current == '\'' )
		{
			// single quote
			a_escapedChar='\'';
			++a_current;
			break;
		}
		else if( *a_current == ';' )
		{
			// single quote
			a_escapedChar='\'';
			++a_current;
			break;
		}
		
	
	}
	return true;
}
