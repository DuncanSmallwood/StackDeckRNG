#ifndef TestUtilities_cpp
#define TestUtilities_cpp

#include <string>
#include <vector>

#include "TestResults.h"

namespace TestUtilities {

	TestResult assertTrue(const bool& test){
		if (test)
			return TestResult::unaffiliated();
		
		return TestResult::unaffiliated("Expected true, found false");
	}
	
	TestResult assertFalse(const bool& test){
		if (test)
			return TestResult::unaffiliated("Expected false, found true");
		
		return TestResult::unaffiliated();
	}

	template <class T> TestResult assertEqual(const T& expected, const T& found){
		if (expected == found){
			return TestResult::unaffiliated();
		}
		
		return TestResult::unaffiliated("Expected " + std::to_string(expected) + " found " + std::to_string(found));
	}
}

#endif