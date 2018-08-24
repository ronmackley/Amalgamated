//***************************************************************************
//
//	Parser.hpp - Builds a tree from a Token stream
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

#ifndef PARSER_HPP
#define PARSER_HPP

#ifndef LEXER_HPP
#include "Lexer.hpp"
#endif

#ifndef CELL_HPP
#include "Cell.hpp"
#endif

#include <vector>

//****************************************************************************
//****************************************************************************
class Parser
{

  public:
  
	Parser();
	virtual ~Parser();


	bool	parse( 	const std::string&				a_input,
					const Lexer::TokenVector&		a_tokens,
					RefCountedCell*&				a_parseTree,
					Lexer::TokenVector&				a_remainingTokens );

  private:

 	std::vector<RefCountedCell*>					d_parseStack;
 	RefCountedCell*									d_parseTreeRoot;
 
};

#endif // PARSER_HPP
