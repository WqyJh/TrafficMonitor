#include "CppUnitTest.h"
#include "PlateRecognizer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TMClientUnitTest
{
	TEST_CLASS(PlateRecognizerTest)
	{
	public:
		TEST_METHOD(test_recognize)
		{
			PlateRecognizer pr;
			auto s = pr.recognize("plate_recognize.jpg");
			Assert::IsTrue(s.length() > 0);

			Assert::IsTrue(string("¿∂≈∆:À’EUK722")._Equal(s));
			Assert::IsFalse(string("’„E UK722")._Equal(s));
		}
	};
}