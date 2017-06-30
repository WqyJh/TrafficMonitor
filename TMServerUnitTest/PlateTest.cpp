#include "stdafx.h"
#include "CppUnitTest.h"
#include "Plate.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TMServerUnitTest
{
	TEST_CLASS(TestPlate)
	{
	public:

		TEST_METHOD(test_plate)
		{
			Plate p(1, "123", 20170630, "D:\\vs-c");
			Assert::AreEqual(1, p.get_id());

			std::string str1("1234");
			p.set_number(str1);
			p.set_id(2);
			Assert::AreEqual(2, p.get_id());
			Assert::AreEqual(str1, p.get_number());
			// TODO: 在此输入测试代码
		}

	};
}