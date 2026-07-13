#ifndef BooleanStackDeckTest_cpp
#define BooleanStackDeckTest_cpp
#include "BooleanStackDeck.h"
#include "TestUtilities.cpp"
#include <vector>
#include <string>
#include <iostream>

class BooleanStackDeckTests {
	public:
		std::vector<TestUtilities::TestResult (*)()> tests;
	
		BooleanStackDeckTests(const bool& showDebugs){
			BooleanStackDeck::debug = showDebugs;
			tests.push_back(testDecimalConstructor);
			tests.push_back(testPercentageConstructor);
			tests.push_back(testDeckYesRate);
			tests.push_back(test0SuccessConstructor);
		}
		
		static TestUtilities::TestResult testDecimalConstructor(){
			if(BooleanStackDeck::debug)
				std::cout << "testDecimalConstructor() debugs:" << std::endl;
			BooleanStackDeck* testDeck = new BooleanStackDeck(0.38);
			TestUtilities::TestResult testResult = TestUtilities::TestResult("testDecimalConstructor()");
			
			testResult += TestUtilities::assertEqual<int>(100, testDeck->numCards);
			testResult += TestUtilities::assertEqual<int>(testDeck->numCards, testDeck->currDeck->size());
			testResult += TestUtilities::assertEqual<float>(0.38f, testDeck->yesRate);
			int yesCards = 0;
			int noCards = 0;
			for (std::vector<bool>::iterator card = testDeck->currDeck->begin(); card != testDeck->currDeck->end(); ++card){
				if (*card)
					++yesCards;
				else
					++noCards;
			}
			testResult += TestUtilities::assertEqual<int>(38, yesCards);
			testResult += TestUtilities::assertEqual<int>(62, noCards);
			
			delete testDeck;
			testDeck = nullptr;
			return testResult;
		}
		
		static TestUtilities::TestResult testPercentageConstructor(){
			if(BooleanStackDeck::debug)
				std::cout << "testPercentageConstructor() debugs:" << std::endl;
			BooleanStackDeck* testDeck = new BooleanStackDeck(38.4f);
			TestUtilities::TestResult testResult = TestUtilities::TestResult("testPercentageConstructor()");
			
			testResult += TestUtilities::assertEqual<int>(1000, testDeck->numCards);
			testResult += TestUtilities::assertEqual<int>(testDeck->numCards, testDeck->currDeck->size());
			testResult += TestUtilities::assertEqual<float>(38.4f, testDeck->yesRate);
			int yesCards = 0;
			int noCards = 0;
			for (std::vector<bool>::iterator card = testDeck->currDeck->begin(); card != testDeck->currDeck->end(); ++card){
				if (*card)
					++yesCards;
				else
					++noCards;
			}
			testResult += TestUtilities::assertEqual<int>(384, yesCards);
			testResult += TestUtilities::assertEqual<int>(616, noCards);
			
			delete testDeck;
			testDeck = nullptr;
			return testResult;
		}

		static TestUtilities::TestResult test0SuccessConstructor(){
			if(BooleanStackDeck::debug)
				std::cout << "test0SuccessConstructor() debugs:" << std::endl;
			BooleanStackDeck* testDeck = new BooleanStackDeck(0);
			TestUtilities::TestResult testResult = TestUtilities::TestResult("test0SuccessConstructor()");
			
			testResult += TestUtilities::assertEqual<int>(1, testDeck->numCards);
			testResult += TestUtilities::assertEqual<int>(testDeck->numCards, testDeck->currDeck->size());
			testResult += TestUtilities::assertEqual<float>(0.0f, testDeck->yesRate);
			
			delete testDeck;
			testDeck = nullptr;
			return testResult;
		}

		static TestUtilities::TestResult testDeckYesRate(){
			if(BooleanStackDeck::debug)
				std::cout << "testDeckYesRate() debugs:" << std::endl;
			BooleanStackDeck* testDeck = new BooleanStackDeck(0.536);
			TestUtilities::TestResult testResult = TestUtilities::TestResult("testDeckYesRate()");
			
			testResult += TestUtilities::assertEqual<int>(1000, testDeck->numCards);
			testResult += TestUtilities::assertEqual<float>(0.536f, testDeck->yesRate);
			
			int noRate = 0;
			int yesRate = 0;
			for (std::vector<bool>::const_iterator card = testDeck->currDeck->begin(); card != testDeck->currDeck->end(); ++card){
				if(*card)
					++yesRate;
				else
					++noRate;
			}
			if (BooleanStackDeck::debug)
				std::cout << "(debug) tested yesRate: " << yesRate << std::endl
					<< "(debug) tested noRate: " << noRate << std::endl;
			testResult += TestUtilities::assertEqual<int>(536,yesRate);
			testResult += TestUtilities::assertEqual<int>(464,noRate);
			
			delete testDeck;
			testDeck = nullptr;
			return testResult;
		}
};

#endif