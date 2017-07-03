#include "CppUnitTest.h"
#include "Server.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TMClientUnitTest
{
	TEST_CLASS(ServerTest)
	{
		TEST_METHOD(test_init)
		{
			Server server("127.0.0.1", 15001);
			int ret = server.init();
			Assert::AreEqual(0, ret);
		}

		TEST_METHOD(test_serve)
		{
			Server server("127.0.0.1", 15001);
			int ret;
			ret = server.init();
			Assert::AreEqual(0, ret);
			ret = server.serve();
			Assert::AreEqual(0, ret);
			Assert::IsTrue(server.is_running());
			server.stop();
			Assert::IsFalse(server.is_running());
		}
	};
}