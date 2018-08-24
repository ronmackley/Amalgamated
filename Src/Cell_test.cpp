#include "Cell.hpp"
#include "Scalar.hpp"
#include <iostream>

int Cell_test( int argc, char** argv )
{
	Cell::Factory	factory;
	std::cout << "Making nil cell: " << std::flush;
	RefCountedCell&	nilCell = factory.allocate();
	std::cout << "made." << std::endl;

	std::cout << "Testing nil cell: " << std::endl;
	std::cout << "isNil(): " << nilCell->isNil() << std::endl;
	std::cout << "isScalar(): " << nilCell->isScalar() << std::endl;
	std::cout << "isList(): " << nilCell->isList() << std::endl;
	std::cout << " Done." << std::endl;
	
	std::cout << "Making scalar cell: " << std::flush;
	RefCountedCell&	scalarCell = factory.allocate();
	Scalar* scalar = new Scalar("scalar");
	std::cout << "assignign scalar" << std::endl;
	scalarCell->scalar( scalar );
	std::cout << "assigned" << std::endl;
	std::cout << "made." << std::endl;
	std::cout << "Testing scalar cell: " << std::endl;
	std::cout << "isNil(): " << scalarCell->isNil() << std::endl;
	std::cout << "isScalar(): " << scalarCell->isScalar() << std::endl;
	std::cout << "isList(): " << scalarCell->isList() << std::endl;
	std::cout << " Done." << std::endl;
	
	
	std::cout << "Making list cell: " << std::flush;
	RefCountedCell&	listCell = factory.allocate();
	RefCountedCell&	firstCell = factory.allocate();
	std::cout << "assigning first" << std::endl;
	listCell->first( firstCell );
	std::cout << "assigned" << std::endl;
	std::cout << "made." << std::endl;
	std::cout << "Testing list cell: " << std::endl;
	std::cout << "isNil(): " << listCell->isNil() << std::endl;
	std::cout << "isScalar(): " << listCell->isScalar() << std::endl;
	std::cout << "isList(): " << listCell->isList() << std::endl;
	std::cout << " Done." << std::endl;

	return 0;
}

int main(int argc, char** argv)
{
	return Cell_test();
}