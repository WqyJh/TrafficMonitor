#include "CppUnitTest.h"
#include "FileManager.h"
#include <direct.h>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TMClientUnitTest
{
	TEST_CLASS(FileManagerTest)
	{
		TEST_METHOD(test_parse_filename)
		{
			char *file1 = "c:\\dir1\\dir2\\test";
			Assert::AreEqual("test", parse_filename(file1).c_str());

			char *file2 = "c:\\dir1\\dir2\\test.c";
			Assert::AreEqual("test.c", parse_filename(file2).c_str());

			char *file3 = "images/raw/test";
			Assert::AreEqual("test", parse_filename(file3).c_str());

			char *file4 = "images/raw/";
			Assert::AreEqual("", parse_filename(file4).c_str());

			char *file5 = "";
			Assert::AreEqual("", parse_filename(file5).c_str());

			char *file6 = NULL;
			Assert::AreEqual("", parse_filename(file6).c_str());

			char *file7 = "test";
			Assert::AreEqual("test", parse_filename(file7).c_str());
		}

		TEST_METHOD(test_get_full_name)
		{
			char *path1 = "c:\\dir1";
			char *fn1 = "test";
			Assert::AreEqual("c:\\dir1\\test", get_full_name(path1, fn1).c_str());

			char *path2 = "images/raw";
			char *fn2 = "test.c";
			Assert::AreEqual("images\\raw\\test.c", get_full_name(path2, fn2).c_str());
		}

		TEST_METHOD(test_get_postfix)
		{
			string s1 = get_postfix(4);
			string s2 = get_postfix(4);
			Assert::AreEqual(5, (int)s1.length());
			Assert::AreEqual(5, (int)s2.length());
			Assert::AreNotEqual(s1, s2);

			s1 = get_postfix(6);
			s2 = get_postfix(6);
			Assert::AreEqual(7, (int)s1.length());
			Assert::AreEqual(7, (int)s2.length());
			Assert::AreNotEqual(s1, s2);
		}

		TEST_METHOD(test_move_to_path)
		{
			string dirname1 = get_postfix(4);
			Assert::AreEqual(mkdir(dirname1.c_str()), 0);

			string dirname2 = get_postfix(4);
			Assert::AreEqual(mkdir(dirname2.c_str()), 0);

			string filename = get_postfix(4);

			string fn1 = get_full_name(dirname1.c_str(), filename.c_str());
			ofstream file(fn1, ios::out);
			Assert::IsTrue(file.good());
			file << "hello";
			file.flush();
			file.close();

			Assert::AreEqual(0, move_to_path(fn1.c_str(), dirname2.c_str()));

			ifstream file2(fn1, ios::in);
			Assert::IsTrue(!file2);

			string fn2 = get_full_name(dirname2.c_str(), filename.c_str());
			ofstream file3(fn2);
			Assert::IsTrue(file3.is_open());

			//Assert::AreEqual(0, std::remove(fn1.c_str()));
			//Assert::AreEqual(0, rmdir(dirname1.c_str()));
			//Assert::AreEqual(0, std::remove(fn2.c_str()));
			//Assert::AreEqual(0, rmdir(dirname2.c_str()));
		}
	};
}