//***************************************************************************
//
//  Application.hpp -- Defintion of a class to manage being an application.
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

#ifndef _INCLUDE_APPLICATION_HPP_
#define _INCLUDE_APPLICATION_HPP_

// system includes for this module
#include <fstream>
#include <string>
#include <cstdio>
#include <memory>
#include <iostream>


class Application
{
	std::string		d_name;
	std::ostream&	d_logStream;
  
					//not defined
					Application& operator=(const Application&);

  public:
					Application( const char* 	a_name );
					Application( const char* 	a_name,
								 std::ostream	a_logStream );
	virtual			~Application();

			int		run();
	virtual	int		doRun() = 0;

	bool			initialize();
	virtual bool	doInitialize()	{ return true; }

	bool			shutdown();
	virtual bool	doShutdown()	{ return true; }
	
	void			Log( const char* );
	void			Log( const std::string& );
  
};

#endif
