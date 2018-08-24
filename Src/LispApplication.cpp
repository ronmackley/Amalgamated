//***************************************************************************
//
//	LispApplication.cpp -- definition an application for lisp
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

//***************************************************************************
//
//	Class that takes care of "being an application".
//	* It calls initializers to initialize classes.
//	* It contains the main try block and exception catcher.
//	* It sets up a logging facility
//
//
//***************************************************************************

#ifndef _INCLUDE_LISPAPPLICATION_HPP_
#include "LispApplication.hpp"
#endif

#ifndef _INCLUDE_TOKENIZER_HPP_
#include "Tokenizer.hpp"
#endif

#ifndef _INCLUDE_WRITER_HPP_
#include "Writer.hpp"
#endif

#include "NilP.hpp"
#include "Atom.hpp"
#include "Listp.hpp"

// System includes for this module
#include <istream>
#include <sstream>
#include <vector>
#include <cassert>

// Using declarations for this module
using namespace std;

//***************************************************************************
//***************************************************************************
LispApplication::LispApplication( const char* a_name )
  : Application( a_name )
{
	// Nothing to do
}

//***************************************************************************
//***************************************************************************
/*
LispApplication::LispApplication( const char* a_name, const char* a_logFile )
  : d_name( a_name )
{
  d_logFile.open(a_logFile);
}
*/

//***************************************************************************
//***************************************************************************
LispApplication::~LispApplication()
{
  // nothing to do.
}

//***************************************************************************
//***************************************************************************
bool LispApplication::doInitialize()
{
	Log("Initializing builtin functions");
	std::string  name="listp";
	ListP listp;
	d_builtinFunctionDictionary.define( name, listp );
	name="nilp";
	NilP nilp;
	d_builtinFunctionDictionary.define( name, nilp );
	return true;
}

//***************************************************************************
//***************************************************************************
bool LispApplication::doShutdown()
{
	Log("Shutting down Lisp");
	return true;
}

//***************************************************************************
//***************************************************************************
int				LispApplication::doRun()
{
	Log("doRun");

#ifdef RUN_TESTS
	Log("Running tests");
	Cell_test();
	Scalar_test();
	Writer_test();
	Log("Completed tests");
#endif

	string inLine;
	string remainder;
//! TODO: Turn off skipws in cin
//! TODO: Get remainder of line back from tokenizer

	Cell::Factory		factory;
	RefCountedCell&		treeRoot = factory.allocate();
	RefCountedCell&		resultTree = factory.allocate();

	RefCountedCell*		current = &treeRoot;
	vector<RefCountedCell> parseStack;
	parseStack.push_back( treeRoot );

	while( !cin.eof() )
	{
		char	inArray[1024];
		cin.getline( inArray, 1024);
		inLine = inArray;

		Tokenizer	tokenizer( inLine );

		const Tokenizer::Token* token;
		while( (token = tokenizer.getNextToken()) != NULL )
		{
			switch( token->getState() )
			{
				// The current cell should always be nil so new data or structureAction
				// can be added.
				assert( (*current)->isNil() );

				case Tokenizer::qString:
				{
// 					Log("Tokenizer::qString");
					// stow the data
					RefCountedCell& valueCell = factory.allocate();
					valueCell->scalar( new Scalar( token->getData() ) );
					// attach the data to the first (value) side of current
					(*current)->first(valueCell);
					// create new structure cell and attach it to the structure
					// side of current
					RefCountedCell& structureCell = factory.allocate();
					(*current)->second(structureCell);
					// and set current to the newly attached structureCell
					current = &(*current)->second();
					break;
				}

				case Tokenizer::token:
				{
// 					Log("Tokenizer::token");
					// stow the data
					RefCountedCell& valueCell = factory.allocate();
					valueCell->scalar( new Scalar( token->getData() ) );
					// attach the data to the first (value) side of current
					(*current)->first(valueCell);
					// create new structure cell and attach it to the structure
					// side of current
					RefCountedCell& structureCell = factory.allocate();
					(*current)->second(structureCell);
					// and set current to the newly attached structureCell
					current = &(*current)->second();
					break;
				}

				case Tokenizer::listOpen:
				{
					// create a new strcuture cell and set it to the first (value)
					// side of current
					RefCountedCell& structureCell = factory.allocate();
					(*current)->first(structureCell);
					// push this new structure cell on the parse stack and set
					// current to it
					parseStack.push_back( structureCell );
					current = &(*current)->first();
					break;
				}

				case Tokenizer::listClose:
				{
					//! get the back and evaluate it. Put it back onto the stack.
					// pop the current stack head off of parseStack
					parseStack.pop_back();
					// and set current to the new stack head
					current = &parseStack.back();
					break;
				}

				default:
					throw "Unknown token state";
			}
		}

	}
	Writer writer;
	cout << "Done reading -- about to eval." << endl;
	writer.toString( treeRoot, cout );
	cout << endl;
	resultTree = eval( treeRoot );

	cout << "=>";
	writer.toString( resultTree, cout );
	cout << endl;
	cout << "Releasing result" << flush << endl;
	factory.release( resultTree );
	cout <<  endl << "Bye." << endl;
	cout << "Releasing treeRoot" << flush << endl;
	factory.release( treeRoot );
	return 0;
}

//***************************************************************************
//***************************************************************************
RefCountedCell& LispApplication::eval(	RefCountedCell& a_inTree )
{
	std::cout << "Evaluating:" << std::endl;
	Writer writer;
	writer.toString( a_inTree, std::cout);
	std::cout << std::endl;

	RefCountedCell& meat = a_inTree->first();
	std::string name = ((meat->first())->scalar()).asString();
	Function* func = d_builtinFunctionDictionary.find( name );
	std::cout << "func=" << func << std::endl;
	RefCountedCell resultTree = RefCountedCell();
	if( func != NULL )
	{
		writer.toString( meat->second(), std::cout);
		std::cout << std::endl << std::flush;
		if((meat->second())->isList())
		{
			return (*func)( eval( meat->second()) );
		}
		else
		{
			return (*func)(meat->second());
		}
	}
	else
	{
		Cell::Factory factory;
		return factory.allocate();	
	}
}

