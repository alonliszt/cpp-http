#include "pch.h"
#include "CppUnitTest.h"

#include <string>

#include "../CppHTTP/Common.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommonStandardTests
{
	TEST_CLASS(FormatTests)
	{
	public:
		
		TEST_METHOD(TestFormatStrings)
		{
			Assert::AreEqual(std::format("Hello %", "World"), std::string("Hello World"));
		}

		TEST_METHOD(TestFormatStringsWithRemainder)
		{
			Assert::AreEqual(std::format("Hello % world", "World"), std::string("Hello World world"));
		}

		TEST_METHOD(TestFormatStringsWithNumber)
		{
			Assert::AreEqual(std::format("Hello %", 5), std::string("Hello 5"));
		}

		TEST_METHOD(TestEmptyFormatStrings)
		{
			Assert::AreEqual(std::format("Hello", "World"), std::string("HelloWorld"));
		}
	};

	TEST_CLASS(StringsTests)
	{
	public:
		TEST_METHOD(RtrimString)
		{
			std::string x("Hello   ");
			std::rtrim_inplace(x);

			Assert::AreEqual(x, std::string("Hello"));
		}

		TEST_METHOD(LtrimString)
		{
			std::string x(" Hello   ");
			std::ltrim_inplace(x);

			Assert::AreEqual(x, std::string("Hello   "));
		}

		TEST_METHOD(TrimString)
		{
			std::string trimmed = std::trim(" Hello   World\n\r  ");
			Assert::AreEqual(trimmed, std::string("Hello   World"));
		}
	};
}
