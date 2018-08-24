//***************************************************************************
//
//  Application.cpp -- Defintion of a class to manage being an application.
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
#include "Application.hpp"
#endif

#include <iostream>
#include <string>

#include <unistd.h>

using namespace std;

//***************************************************************************
//***************************************************************************
Application::Application( const char* a_name ) : 	d_name( a_name ), 
													d_logStream(std::clog)
{
	// Nothing to do.
}
//***************************************************************************
//***************************************************************************
Application::Application( const char* a_name,
						  std::ostream a_logStream ) : 	d_name( a_name ), 
														d_logStream(a_logStream)
{
	// Nothing to do.
}

//***************************************************************************
//***************************************************************************
Application::~Application()
{
	// nothing to do.
}

//***************************************************************************
//***************************************************************************
bool			Application::initialize()
{
	Log("Initialize");
	// create the initializer class and run it
	return doInitialize();
}

//***************************************************************************
//***************************************************************************
bool			Application::shutdown()
{
	Log("De-Initialize");
	// have the initializer de-initialize
	return doShutdown();
}

//***************************************************************************
//***************************************************************************
void			Application::Log( const char* a_msg )
{
	d_logStream << d_name << " : " << a_msg << std::endl;
}

//***************************************************************************
//***************************************************************************
void			Application::Log( const string& a_msg )
{
	d_logStream << d_name << " : " << a_msg << std::endl;
}

//***************************************************************************
//***************************************************************************
int				Application::run()
{
	try
	{
		return doRun();

	}
	catch( char* cp )
	{
		d_logStream << "Caught char exception: " << cp << std::endl;
		std::exit(-1);
	}
	catch( std::string& s )
	{
		d_logStream << "Caught string exception: " << s << std::endl;
		std::exit(-1);
	}
	catch( ... )
	{
		d_logStream << "Caught exception" << std::endl;
		std::exit(-1);
	}
	return 0;
}
