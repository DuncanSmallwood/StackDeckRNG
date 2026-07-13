#ifndef TestResults_h
#define TestResults_h

#include <string>
#include <vector>
#include <ostream>
namespace TestUtilities {
	const static std::string EMPTY_ERROR = "";
	class TestResult {
		public:
			bool success;
		private:
			unsigned int numErrors;
			std::vector<std::string> errors;
			std::string testName;

		public:
			TestResult(const std::string& testName, const std::string& errors = EMPTY_ERROR);
			TestResult(const TestResult& other);
			std::string getTestName();
		
			static TestResult unaffiliated(const std::string& error = EMPTY_ERROR);

			void operator+=(const TestResult& other);
			void operator+=(const std::string& error);

			friend std::ostream& operator<<(std::ostream& out, const TestResult& testResult);
	};
}
#endif