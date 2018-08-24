//***************************************************************************
//
//	Parser.cpp - Builds a tree from a Token stream
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
#include "Parser.hpp"
#endif

//****************************************************************************
//****************************************************************************
Parser::Parser()
{
	// Nothing to do.
}

//****************************************************************************
//****************************************************************************
Parser::~Parser()
{
	// Nothing to do.
}


//****************************************************************************
//
//	RETURNS:
//		true - 	parsing complete, ready to evaluate ( last paren closed )
//		false -	parsing incomplete, nothing to eval, yet
//
//****************************************************************************
bool	Parser::parse(	const std::string&			a_input,
						const Lexer::TokenVector&	a_tokens,
						RefCountedCell*&			a_parseTree,
						Lexer::TokenVector&			a_remainingTokens )
{
	Cell::Factory	cellFactory;
	
	// Build the root or the parse tree
	RefCountedCell&	cell = cellFactory.allocate();
	a_parseTree = &cell;
		




	return true;
}
