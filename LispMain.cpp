//***************************************************************************
//
//	LispMain.cpp -- entry point for lisp application
//
//  $LastChangedBy$
//  $LastChangedDate$
//  $LastChangedRevision$
//  $HeadURL$
//
//  Copyright (C) 2004-2010 Ronald G. Mackley.
//  All rights reserved.
//
//  $Id$
//
//***************************************************************************

#ifndef _INCLUDE_LISPAPPLICATION_HPP_
#include "Src/LispApplication.hpp"
#endif

#include <stdio.h>

int		main( int argc, char** argv )
{
	LispApplication	theApp( argv[0] );
	theApp.initialize();
	int result = theApp.run();
	theApp.shutdown();
	return result;
};

