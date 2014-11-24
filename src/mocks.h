#define CXXTEST_MOCK_NAMESPACE Mocked //define before Mock.h is included
#include <cxxtest/Mock.h>

#include <time.h>
#include <unistd.h>
#include <chrono>





CXXTEST_MOCK_GLOBAL(time_t, // return type
		    time, // function name in mock namespace --> t::time
		    ( time_t *t ), // argument prototype
		    ( t )); // arugment list


CXXTEST_MOCK_GLOBAL(int, // return type
		    usleep, // function name in mock namespace --> t::time
		    ( useconds_t sleep_time ), 
		    ( sleep_time ));



