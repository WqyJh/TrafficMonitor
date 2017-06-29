#include "stdafx.h"
#include "CppUnitTest.h"
#include "PlateRecognizer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TMClientUnitTest
{
	TEST_CLASS(PlateRecognizerTest)
	{
	public:
		TEST_METHOD(test_recognize)
		{
			PlateRecognizer pr;
			Assert::IsFalse(pr.recognize("hello.jpg").empty());
		}
	};
}