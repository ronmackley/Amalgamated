#ifndef _INCLUDE_FUNCTIONDICTIONARY_HPP_
#include "FunctionDictionary.hpp"
#endif

FunctionDictionary::FunctionDictionary()
{
	// nothing to do.
}


FunctionDictionary::~FunctionDictionary()
{
	// nothing to do.
}

// Add a new defintion.
void FunctionDictionary::define( std::string& a_name, 
			Function& a_function )
{
	FunctionMap::const_iterator iter = d_functionMap.find( a_name );
	if( iter == d_functionMap.end() )
	{
		std::cout << "defining: " << a_name << std::endl;
		d_functionMap.insert( std::pair<std::string, Function>(a_name, a_function) );
	}
	else
	{
		std::cout << "redefining: " << a_name << std::endl;
		d_functionMap.erase( a_name );
		d_functionMap.insert( std::pair<std::string, Function>(a_name, a_function) );
	}
}

// remove a definition.
Function& FunctionDictionary::undefine( std::string&  a_name )
{
	FunctionMap::const_iterator iter = d_functionMap.find( a_name );
	if( iter != d_functionMap.end() )
	{
		std::cout << "erasing: " << a_name << std::endl;
		d_functionMap.erase( a_name );
	}
	else
	{
		std::cout << "erase did not find: " << a_name << std::endl;
	}
}

// fetch a definition
Function* FunctionDictionary::find(	std::string& a_name)
{
	std::cout << '>' << a_name << '<' << std::endl;
	FunctionMap::iterator iter = d_functionMap.find( a_name );
	Function* retval = NULL;
	if( iter == d_functionMap.end() )
	{
		std::cout << "find did not find:" << a_name << ':' << retval <<std::endl;
	}
	else
	{
		std::cout << "find found: " << a_name << std::endl;
		retval = &(*iter).second;
	}
	std::cout << a_name << " lives at " << retval <<std::endl;
	return retval;
}
