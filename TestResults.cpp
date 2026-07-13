#include "TestResults.h"
namespace TestUtilities{
	TestResult::TestResult(const std::string& testName, const std::string& errors){
		this->testName = testName;
		if (errors == EMPTY_ERROR){
			success = true;
		}
		else{
			success = false;
			this->errors.push_back(errors);
		}
	}
	
	TestResult::TestResult(const TestResult& other){
		success = other.success;
		numErrors = other.numErrors;
		for (std::vector<std::string>::const_iterator otherError = other.errors.cbegin(); otherError != other.errors.cend(); ++otherError){
			errors.push_back(*otherError);
		}
		testName = other.testName;
	}
	
	std::string TestResult::getTestName(){
		return testName;
	}
	
	TestResult TestResult::unaffiliated(const std::string& error){
		return TestResult("", error);
	}

	void TestResult::operator+=(const TestResult& other){
		if (success){
			success = other.success;
		}
		if (!other.success){
			for (int i = 0; i < other.errors.size(); ++i){
				errors.push_back(other.errors[i]);
			}
		}
	}

	void TestResult::operator+=(const std::string& error){
		success = false;
		errors.push_back(error);
	}

	std::ostream& operator<<(std::ostream& out, const TestResult& testResult){
		out << "test name: " << testResult.testName;
		if (testResult.success){
			out << " (passed)";
		}
		else{
			out << " (failed)";
			for (int i = 0; i < testResult.errors.size(); ++i){
				out << std::endl << testResult.errors[i];
			}
		}
		return out;
	}
}