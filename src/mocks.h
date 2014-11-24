#include <time.h>
#include <unistd.h>
#include <chrono>
#include <cxxtest/Mock.h>


CXXTEST_MOCK_GLOBAL(time_t, // return type
		    time, // function name in mock namespace --> t::time
		    ( time_t *t ), // argument prototype
		    ( t )); // arugment list


CXXTEST_MOCK_GLOBAL(int, // return type
		    usleep, // function name in mock namespace --> t::time
		    ( useconds_t sleep_time ), 
		    ( sleep_time ));



