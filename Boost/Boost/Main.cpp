#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/cstdint.hpp>
#include <boost/variant.hpp>
#include <boost/pool/simple_segregated_storage.hpp>
#include <vector>
#include <cstddef>
#include <iostream>
#include <string>
#include <cmath>

using namespace boost::algorithm;

void f1();
void f2();
void f3();
void f4();
void f5();

int main()
{
	f1();//Tuple
	system("pause");
	f2();//String algorithm
	system("pause");
	f3();//Integer
	system("pause");
	f4();//Variant
	system("pause");
	f5();//Pool
	system("pause");
	return 0;
}

//Tuple
//I picked this because it is useful when storing only two values
void f1()
{
	//Creating what will be stored in the parameters
	typedef boost::tuple<std::string, int> animal;
	//The data that is stored
	animal a{ "cat", 4 };
	std::cout << a << '\n';
}

//String Algorithm
//This is useful if the data you are trying to collect has to be a certain case
void f2()
{
	std::string s = "Boost C++ Libraries";
	//This changes the above string to upper case
	std::cout << to_upper_copy(s) << '\n';
}

//Integer
void f3()
{
	//Carries the exact memory size of the name which is 8 bits
	boost::int8_t i8 = 1;
	std::cout << sizeof(i8) << '\n';

#ifndef BOOST_NO_INT64_T
	//Carries the exact memory size of the name which is 64 bits
	boost::uint64_t ui64 = 1;
	std::cout << sizeof(ui64) << '\n';
#endif
	//Carries atleast as many bits as the name says, 8 bits in this case
	boost::int_least8_t il8 = 1;
	std::cout << sizeof(il8) << '\n';
	//Carries atleast as many bits as the name says, 32 bits in this case
	boost::uint_least32_t uil32 = 1;
	std::cout << sizeof(uil32) << '\n';
	//Also has a minimum size but the size is based for performance, in this case 8 bits
	boost::int_fast8_t if8 = 1;
	std::cout << sizeof(if8) << '\n';
	//Also has a minimum size but the size is based for performance, in this case 32 bits
	boost::uint_fast16_t uif16 = 1;
	std::cout << sizeof(uif16) << '\n';
}

//Variant
//This is a template for data structures, this is useful for storing data
void f4()
{
	//Creating the variant, all of the data types that are being used must be in the parameter to be stored
	boost::variant<double, char, std::string> v;
	v = 3.14;
	std::cout << v << std::endl;
	v = 'A';
	std::cout << v << std::endl;
	v = "Boost";
	std::cout << v << std::endl;
}

//Pool
//This is used for maintaining storage making sure the next memory space to be used is clear
void f5()
{
	//Creates and manages segregated memory
	boost::simple_segregated_storage<std::size_t> storage;
	std::vector<char> v(1024);
	//This is called to pass a memory block of 1024 bytes
	storage.add_block(&v.front(), v.size(), 256);
	//Request memory from storage, this one returns a pointer to a free segment
	int *i = static_cast<int*>(storage.malloc());
	*i = 1;
	/*Request memory from storage, this one returns a pointer to one or more
	contigious segements that provide as many bytes in one block as requested*/
	int *j = static_cast<int*>(storage.malloc_n(1, 512));
	j[10] = 2;
	//These two calls frees up all the memory that was stored in those places
	storage.free(i);
	storage.free_n(j, 1, 512);
	//Nothing is displayed for this function
}