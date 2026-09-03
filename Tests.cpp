#include <vector>
#include <string>
#include <iostream>

#include "BooleanStackDeckTests.cpp"

// this test suit is not setting reporting these on the errors
int main(int argc, char *argb[]){
	bool showDebug = false;
	for (int i = 1; i < argc; ++i){
		std::string currArg(argb[i]);
		if (currArg == "debug" || currArg == "true")
			showDebug = true;
	}
	std::cout << showDebug << std::endl;
	BooleanStackDeckTests testClass(showDebug);
	
	for(std::vector<TestUtilities::TestResult (*)()>::iterator tests = testClass.tests.begin(); tests != testClass.tests.end(); ++tests){
		std::cout << (*tests)() << std::endl;
	}
}