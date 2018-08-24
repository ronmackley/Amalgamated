

#include "Writer.hpp"

#include "Scalar.hpp"
#include "Cell.hpp"

#include <iostream>

int Writer_test( int argc, char** argv )
{
	
	
	Writer	writer;

	Cell::Factory	cellFactory;
	
	typedef ref_counted<long>	RefCountedLong;
	
	{
		std::cout << "About to allocate cell " << std::endl;
		RefCountedCell&	cell = cellFactory.allocate();
		std::cout << "Allocated cell"  << std::endl;
		std::cout << "About to allocate scalar " << std::endl;
		Scalar* scalar = new Scalar("cell");
		cell->scalar( scalar );
		std::cout << "Allocated scalar"  << std::endl;
		std::cout << "Writing first: ";
		writer.toString( cell, std::cout );
		std::cout << std::endl;
	}
	
	{
		RefCountedCell&	nilList = cellFactory.allocate();
		
		std::cout << std::endl << "Writing nilList" << std::endl;
		writer.toString( nilList, std::cout );
		std::cout << std::endl << "Done" << std::endl;

	}

	{
		RefCountedCell&	first = cellFactory.allocate();
		first->scalar( new Scalar("first") );
	
		RefCountedCell&	second = cellFactory.allocate();
		second->scalar(  new Scalar("second") );
		
		RefCountedCell&	compound = cellFactory.allocate();
		compound->first( first );
		compound->second( second );
		
		std::cout << "Writing first: ";
		writer.toString( first, std::cout );
		std::cout << std::endl << "Done" << std::endl;
	
		std::cout << "Writing second: ";
		writer.toString( second, std::cout );
		std::cout << std::endl << "Done" << std::endl;
	
		std::cout << "Writing compound: ";
		writer.toString( compound, std::cout );
		std::cout << std::endl << "Done" << std::endl;
	
		RefCountedCell&	firster = cellFactory.allocate();
		firster->scalar( new Scalar("firster") );
		RefCountedCell&	seconder = cellFactory.allocate();
		seconder->first( compound );
		RefCountedCell&	outer = cellFactory.allocate();
		outer->first( firster );
		outer->second( seconder );
	
	
		std::cout << "Writing outer: ";
		writer.toString( outer, std::cout );
		std::cout << std::endl << "Done" << std::endl;

		RefCountedCell&	firsterer = cellFactory.allocate();
		firsterer->scalar( new Scalar("firsterer") );
		RefCountedCell&	outerer = cellFactory.allocate();
		outerer->first( firsterer );
		outerer->second( outer );
	
		std::cout << "Writing outerer: ";
		writer.toString( outerer, std::cout );
		std::cout << std::endl << "Done" << std::endl;
	}

	return 0;
	

	{
		std::cout << std::endl << "Start big kahuna " << std::endl;

	}
	return 0;	
}

int main(int argc, char** argv)
{
	return Writer_test();
}