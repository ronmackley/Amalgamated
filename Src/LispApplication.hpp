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
#define _INCLUDE_LISPAPPLICATION_HPP_

#ifndef	_INCLUDE_APPLICATION_HPP_
#include "Application.hpp"
#endif

#ifndef _INCLUDE_CELL_HPP_
#include "Cell.hpp"
#endif

#ifndef _INCLUDE_FUNCTIONDICTIONARY_HPP_
#include "FunctionDictionary.hpp"
#endif

#include <fstream>
#include <string>
#include <cstdio>

class LispApplication : public Application
{
					//not defined
					LispApplication& operator=(const LispApplication&);

					// dictionaries to hold builtin and user-defined functions.
					FunctionDictionary	d_builtinFunctionDictionary;
					FunctionDictionary	d_userFunctionDictionary;

  public:	
	explicit		LispApplication( const char* a_name = "UntitledApp" );
	virtual			~LispApplication();

	virtual	int		doRun();
	virtual bool	doInitialize();
	virtual bool	doShutdown();

	RefCountedCell&	eval(	RefCountedCell& a_inTree );

};

#endif
