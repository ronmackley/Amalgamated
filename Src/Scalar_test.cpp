#include "Scalar.hpp"
#include <iostream>

int Scalar_test( int argc, char** argv )
{
	std::cout << "string test" << std::endl;
	Scalar*	scalar1 = new Scalar( "Hi" );
	std::cout << scalar1->asString() << std::endl;
	std::cout << scalar1->asLong() << std::endl;
	std::cout << scalar1->asDouble() << std::endl;

	delete scalar1;

	std::cout << "long test" << std::endl;
	Scalar*	scalar2 = new Scalar( "1" );
	std::cout << scalar2->asString() << std::endl;
	std::cout << scalar2->asLong() << std::endl;
	std::cout << scalar2->asDouble() << std::endl;

	delete scalar2;

	std::cout << "double test" << std::endl;
	Scalar*	scalar3 = new Scalar( "1.1" );
	std::cout << scalar3->asString() << std::endl;
	std::cout << scalar3->asLong() << std::endl;
	std::cout << scalar3->asDouble() << std::endl;

	Scalar*	scalar4 = new Scalar( "1.2" );
	std::cout << "equality test" << std::endl;
	std::cout << scalar4->eql( *scalar3) << std::endl;
	std::cout << scalar4->equal( *scalar3) << std::endl;
	std::cout << scalar4->eql( *scalar4) << std::endl;
	std::cout << scalar4->equal( *scalar4) << std::endl;
	
	Scalar*	scalar5 = new Scalar( *scalar2 );
	std::cout << "copy ctor test" << std::endl;
	std::cout << scalar2->asString() << std::endl;
	std::cout << scalar2->asLong() << std::endl;
	std::cout << scalar2->asDouble() << std::endl;
	
	delete scalar3;
	delete scalar4;
	delete scalar5;

	return 0;
}

int main(int argc, char** argv)
{
	return Scalar_test();
}