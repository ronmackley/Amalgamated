#include "ref_counted.hpp"

//#include <ios>
#include <iostream>
//#include <iomanip>

class Long
{
	long	d_val;
	public:
		Long( long a_val = 0 ) : d_val(a_val) 
		{
			std::cout 	<< "Just set ";
			std::cout.setf( std::ios_base::hex, std::ios_base::basefield );
			std::cout << this;
			std::cout.setf( std::ios_base::dec, std::ios_base::basefield );
			std::cout << "'s d_val to: " << d_val << std::endl;
		} 
		
		long value () const
		{
			return d_val;
		}
		
		void print() const
		{
			std::cout 	<< "Long ";
			std::cout.setf( std::ios_base::hex, std::ios_base::basefield );
			std::cout << this;
			std::cout.setf( std::ios_base::dec, std::ios_base::basefield );
			std::cout << "'s d_val is: " << d_val << std::endl;
		} 
};

int ref_counted_test()
{
	typedef ref_counted<Long>	RefCountedLong;

	RefCountedLong first(new Long(123));
	std::cout << "." << std::endl;
	RefCountedLong second( first );
	std::cout << "." << std::endl;
	first->print();
	std::cout << "." << std::endl;
	second->print();

	std::cout << first->value() << std::endl;

	return 0;
}

int main(int argc, char** argv) {
	return ref_counted_test();
}
