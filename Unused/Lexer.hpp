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
#define LEXER_HPP


#include <vector>
#include <string>

//****************************************************************************
//****************************************************************************
class Lexer{

  public:
  
	Lexer();
	virtual ~Lexer();

	enum	tokenType
	{
		nil				= 0,
		listOpen 		= '(',
		listClose		= ')',
		whiteSpace		= 32,
		comment			= 42,
		quotedString	= 10,	
		quote			= 50,
		token			= 100,
		attListOpen		= 500,
		attListClose	= 501,
		attKey			= 502,
		attValue		= 503,
		end				= 999
	};
	
	struct	Token
	{
		tokenType	d_type;
		std::string	d_text;
	};
	
	typedef	std::vector<Token>	TokenVector;
	
	bool	parse(	const std::string&	a_input,
					TokenVector&		a_tokens,
					std::string&		a_remainder,
					long				a_numTokens = 0 );

	

  private:

  	// used to parse individual atom types

  	bool parseToken(		const std::string::const_iterator&	a_tokenStart,
  							const std::string::const_iterator&	a_end,
							std::string::const_iterator&		a_current,
							TokenVector&						a_tokens );

  	bool parseListOpen(		const std::string::const_iterator&	a_tokenStart,
  							const std::string::const_iterator&	a_end,
							std::string::const_iterator&		a_current,
							TokenVector&						a_tokens );

  	bool parseListClose(	const std::string::const_iterator&	a_tokenStart,
  							const std::string::const_iterator&	a_end,
							std::string::const_iterator&		a_current,
							TokenVector&						a_tokens );

  	bool parseWhiteSpace(	const std::string::const_iterator&	a_tokenStart,
  							const std::string::const_iterator&	a_end,
							std::string::const_iterator&		a_current,
							TokenVector&						a_tokens );

  	bool parseQuotedString(	const std::string::const_iterator&	a_tokenStart,
  							const std::string::const_iterator&	a_end,
							std::string::const_iterator&		a_current,
							TokenVector&						a_tokens );

  	bool parseQuote(		const std::string::const_iterator&	a_tokenStart,
  							const std::string::const_iterator&	a_end,
							std::string::const_iterator&		a_current,
							TokenVector&						a_tokens );

  	bool parseComment(		const std::string::const_iterator&	a_tokenStart,
  							const std::string::const_iterator&	a_end,
							std::string::const_iterator&		a_current,
							TokenVector&						a_tokens );

	// used completely internally
  	bool parseEscapeSequence(	const std::string::const_iterator&	a_tokenStart,
	  							const std::string::const_iterator&	a_end,
								std::string::const_iterator&		a_current,
								char&								a_escapedChar );
  	
  
};

#endif // LEXER_HPP
