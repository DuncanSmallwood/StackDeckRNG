#ifndef BooleanStackDeckTest_cpp
#define BooleanStackDeckTest_cpp
#include "BooleanStackDeck.h"
#include "TestUtilities.cpp"
#include <vector>
#include <string>
#include <iostream>
#include "StackDeckTests.cpp"

class BooleanStackDeckTests {
	public:
		std::vector<TestUtilities::TestResult (*)()> tests;
	
		BooleanStackDeckTests(bool showDebugs){
			StackDeckTests::debug<bool>(showDebugs);
			tests.push_back(testDecimalConstructor);
			tests.push_back(testPercentageConstructor);
			tests.push_back(test0SuccessConstructor);
			tests.push_back(testDeckYesRate);
		}
		
		static TestUtilities::TestResult testDecimalConstructor(){
			if(StackDeckTests::debug<bool>())
				std::cout << "testDecimalConstructor() debugs:" << std::endl;
			StackDeck<bool>* testDeck = new BooleanStackDeck(0.38);
			TestUtilities::TestResult testResult = TestUtilities::TestResult("testDecimalConstructor()");
			
			StackDeckTests::waitForDeckReset(*testDeck);
			
			testResult += TestUtilities::assertEqual<int>(100, StackDeckTests::numCards(*testDeck));
			testResult += TestUtilities::assertEqual<int>(StackDeckTests::numCards(*testDeck), StackDeckTests::currDeck(*testDeck).size());
			testResult += TestUtilities::assertEqual<float>(0.38f, StackDeckTests::possibilitiesMap(*testDeck).at(true));
			testResult += TestUtilities::assertEqual<float>(0.62f, StackDeckTests::possibilitiesMap(*testDeck).at(false));
			int yesCards = 0;
			int noCards = 0;
			for (bool card : StackDeckTests::currDeck(*testDeck)){
				if (card)
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
			if(StackDeckTests::debug<bool>())
				std::cout << "testPercentageConstructor() debugs:" << std::endl;
			BooleanStackDeck* testDeck = new BooleanStackDeck(38.4f);
			TestUtilities::TestResult testResult = TestUtilities::TestResult("testPercentageConstructor()");
			
			StackDeckTests::waitForDeckReset(*testDeck);
			
			testResult += TestUtilities::assertEqual<int>(1000, StackDeckTests::numCards(*testDeck));
			testResult += TestUtilities::assertEqual<int>(StackDeckTests::numCards(*testDeck), StackDeckTests::currDeck(*testDeck).size());
			testResult += TestUtilities::assertEqual<float>(38.4f, StackDeckTests::possibilitiesMap(*testDeck).at(true));
			testResult += TestUtilities::assertEqual<float>(61.6f, StackDeckTests::possibilitiesMap(*testDeck).at(false));
			int yesCards = 0;
			int noCards = 0;
			for (bool card : StackDeckTests::currDeck(*testDeck)){
				if (card)
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
			
			StackDeckTests::waitForDeckReset(*testDeck);
			
			testResult += TestUtilities::assertEqual<int>(1, StackDeckTests::numCards(*testDeck));
			testResult += TestUtilities::assertEqual<int>(StackDeckTests::numCards(*testDeck), StackDeckTests::currDeck(*testDeck).size());
			testResult += TestUtilities::assertEqual<float>(0.0f, StackDeckTests::possibilitiesMap(*testDeck).at(true));
			testResult += TestUtilities::assertEqual<float>(1.0f, StackDeckTests::possibilitiesMap(*testDeck).at(false));
			
			delete testDeck;
			testDeck = nullptr;
			return testResult;
		}

		static TestUtilities::TestResult testDeckYesRate(){
			if(BooleanStackDeck::debug)
				std::cout << "testDeckYesRate() debugs:" << std::endl;
			BooleanStackDeck* testDeck = new BooleanStackDeck(0.536);
			TestUtilities::TestResult testResult = TestUtilities::TestResult("testDeckYesRate()");
			
			StackDeckTests::waitForDeckReset(*testDeck);
			
			testResult += TestUtilities::assertEqual<int>(1000, StackDeckTests::numCards(*testDeck));
			testResult += TestUtilities::assertEqual<float>(0.536f, StackDeckTests::possibilitiesMap(*testDeck).at(true));
			testResult += TestUtilities::assertEqual<float>(0.464f, StackDeckTests::possibilitiesMap(*testDeck).at(false));
			
			int noRate = 0;
			int yesRate = 0;
			for (bool card : StackDeckTests::currDeck(*testDeck)){
				if(card)
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