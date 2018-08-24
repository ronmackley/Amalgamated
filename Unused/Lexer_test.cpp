
#include <iostream>
#include <string>

#include "Lexer.hpp"


using std::cin;
using std::cout;
using std::endl;

using std::string;

int	Lexer_test( int argc, char** argv )
{
	
	
	string				input;
	string				remainder;
	Lexer::TokenVector	tokens;	
	Lexer				luthor;
	
	cout << ">";
	//	cin >> input;
	getline(cin, input);
	
	luthor.parse( input, tokens, remainder );

	Lexer::TokenVector::const_iterator current = tokens.begin();
	Lexer::TokenVector::const_iterator end = tokens.end();
	while( current != end )
	{
		cout << '(' << current->d_type << " : " << current->d_text << ')' << endl;
		++current;
	}
	
	cout << "Skipped: " << remainder << endl;
	
	(void) argc;
	(void) argv;
	
	return 0;	
}
