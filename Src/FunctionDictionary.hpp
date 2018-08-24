#ifndef _INCLUDE_FUNCTIONDICTIONARY_HPP_
#define _INCLUDE_FUNCTIONDICTIONARY_HPP_

#include "Function.hpp"

#include <deque>
#include <map>


/**
	@author Ron Mackley <ronmackley@yahoo.com>
*/
class FunctionDictionary
{

	typedef std::map<std::string, Function> FunctionMap;
	FunctionMap	d_functionMap;

public:

    FunctionDictionary();

    ~FunctionDictionary();

	// Add a new defintion.
	void define( std::string& a_name, 
			Function& a_function );

	// Remove a definition.
	Function& undefine( std::string&  a_name );

	// Fetch a definition
	Function* find( std::string& a_name);
};

#endif // _INCLUDE_FUNCTIONDICTIONARY_HPP_
