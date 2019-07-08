#include <boost/chrono.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/cstdint.hpp>
#include <boost/variant.hpp>
#include <boost/pool/simple_segregated_storage.hpp>
#include <vector>
#include <cstddef>
#include <iostream>
#include <string>
using namespace boost::algorithm;
using namespace boost::chrono;

int main()
{
	f1();
	f2();
	f3();
	f4();
	f5();
}

//Chrono
//I picked this because it is useful when dealing with time
int f1()
{
	//Returns a system time
	std::cout << system_clock::now() << '\n';
#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY
	//This is used to return a time later on
	std::cout << steady_clock::now() << '\n';
#endif
	//This is a type deffinition for system_clock and steady_clock
	std::cout << high_resolution_clock::now() << '\n';

#ifdef BOOST_CHRONO_HAS_PROCESS_CLOCKS
	//Returns the CPU time for how long the application has been running
	std::cout << process_real_cpu_clock::now() << '\n';
	//Returns the CPU time the application has spend in user space
	std::cout << process_user_cpu_clock::now() << '\n';
	//Returns the time spent in the kernel space
	std::cout << process_system_cpu_clock::now() << '\n';
	//Returns a tuple with the CPU times of the data above this
	std::cout << process_cpu_clock::now() << '\n';
#endif

#ifdef BOOST_CHRONO_HAS_THREAD_CLOCK
	//Returns the time used by a thread
	std::cout << thread_clock::now() << '\n';
#endif
}

//String Algorithm
//This is useful if the data you are trying to collect has to be a certain case
int f2()
{
	std::string s = "Boost C++ Libraries";
	//This changes the above string to upper case
	std::cout << to_upper_copy(s) << '\n';
}

//Integer
int f3()
{
	boost::int8_t i8 = 1;
	std::cout << sizeof(i8) << '\n';

#ifndef BOOST_NO_INT64_T
	boost::uint64_t ui64 = 1;
	std::cout << sizeof(ui64) << '\n';
#endif

	boost::int_least8_t il8 = 1;
	std::cout << sizeof(il8) << '\n';

	boost::uint_least32_t uil32 = 1;
	std::cout << sizeof(uil32) << '\n';

	boost::int_fast8_t if8 = 1;
	std::cout << sizeof(if8) << '\n';

	boost::uint_fast16_t uif16 = 1;
	std::cout << sizeof(uif16) << '\n';
}

//Variant
int f4()
{
	boost::variant<double, char, std::string> v;
	v = 3.14;
	v = 'A';
	v = "Boost";
}

//Pool
int f5()
{
	boost::simple_segregated_storage<std::size_t> storage;
	std::vector<char> v(1024);
	storage.add_block(&v.front(), v.size(), 256);

	int *i = static_cast<int*>(storage.malloc());
	*i = 1;

	int *j = static_cast<int*>(storage.malloc_n(1, 512));
	j[10] = 2;

	storage.free(i);
	storage.free_n(j, 1, 512);
}