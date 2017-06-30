#include "CppUnitTest.h"
#include "FileInfo.hpp"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TMClientUnitTest
{
	TEST_CLASS(FileINfoTest)
	{
	public:

		TEST_METHOD(test_set_info_name)
		{
			FileInfo info;
			string s = "hello";
			set_info_name(info, s);
			Assert::AreEqual("hello", info.filename);

			string s2 = "world";
			set_info_name(info, s2);
			Assert::IsTrue(s2._Equal(info.filename));
		}

		TEST_METHOD(test_set_file_len)
		{
			FileInfo info;
			long len = 100;
			// todo: 
			Assert::Fail();
		}

	};
}