#include "stdafx.h"
#include "CppUnitTest.h"
#include "PlateDao.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TMServerUnitTest
{
	TEST_CLASS(TestPlate)
	{
	public:

		TEST_METHOD(test_plate)
		{
			remove("D:\\PlateForDao.db");
			Plate p1("123", 1498824286, "D:\\vs-c");
			Assert::AreEqual(0, p1.get_id());
			std::string str1("空A 0QV05");
			p1.set_number(str1);
			Plate p2("空A HZ553", 1498872847, "E:\\c");
			Plate p3("空B HZ553", 1498874814, "E:\\c");

			//PlateDao()  save()  remove()
			PlateDao dao;
			Assert::AreEqual(dao.save(p1), 0);
			dao.save(p1);
			dao.save(p1);
			dao.save(p2);
			dao.save(p2);
			dao.save(p3);
			Assert::AreEqual(dao.remove(p1), 0);

			//findById
			Plate *p4 = dao.findById(4);
			Assert::AreEqual(p4->get_id(), 4);
			std::string str("空A HZ553");
			Assert::AreEqual(p4->get_number(), str);

			//update()
			p4->set_time(1498875999);
			dao.update(*p4);
			Plate *p5 = dao.findById(4);
			Assert::AreEqual(p5->get_time(),(long)1498875999);

			//findByNumber()
			std::vector<Plate *> v1 = dao.findByNumber("空A HZ553");
			Assert::AreEqual((int)v1.size(), 2);
			Plate *p6 = v1.front();
			Assert::AreEqual(p6->get_id(), 4);

			//findByTime()
			PlateDao dao2;
			std::vector<Plate *> v2 = dao2.findByTime("2017-07-01");
			Assert::AreEqual((int)v2.size(), 3);
			Plate *p7 = v2.front();
			std::string got = p7->get_path();
			const char * path = got.c_str();
			Assert::AreEqual(path, "E:\\c");
		}

	};
}