
#include "PlateDao.h"
#include <iostream>


char* gszFile = "D:\\PlateForDao.db";

PlateDao::PlateDao(char* path)
{
	gszFile = path;
	CppSQLite3DB db;
	db.open(gszFile);
	if (!db.tableExists("Plate"))
	{
		db.execDML("CREATE TABLE Plate(_id integer primary key, number char(20), time int(20), path char(30))");
		db.execDML("CREATE INDEX numIndex ON plate(number)");
	}
}


PlateDao::~PlateDao()
{
}

int PlateDao::save(const Plate& plate)
{

	CppSQLite3DB db;
	db.open(gszFile);
	std::string num = plate.get_number();
	const char * number = num.c_str();
	long time = plate.get_time();
	std::string pa = plate.get_path();
	const char * path = pa.c_str();
	CppSQLite3Buffer bufSQL;
	bufSQL.format("INSERT INTO Plate(number, path, time) VALUES(%Q, %Q, %ld)", number, path, time);
	int flag = db.execDML(bufSQL);
	//int flag = db.execDML(buf);
	if (flag == 1)
		return 0;
	return 1;
}

int PlateDao::remove(const Plate& plate)
{
	CppSQLite3DB db;
	db.open(gszFile);
	//std::string number = plate.get_number();
	//std::string num = plate.get_number();
	//const char * number = num.c_str();
	//long time = plate.get_time();
	//std::string path = plate.get_path();
	//std::string pa = plate.get_path();
	//const char * path = pa.c_str();
	int id = plate.get_id();
	CppSQLite3Buffer bufSQL;
	bufSQL.format("DELETE FROM Plate WHERE _id=%d", id);
	int flag = db.execDML(bufSQL);
	if (flag != 0)
		return 0;
	return 1;
}

int PlateDao::update(const Plate& plate)
{
	CppSQLite3DB db;
	db.open(gszFile);
	int id = plate.get_id();
	//std::string number = plate.get_number();
	std::string num = plate.get_number();
	const char * number = num.c_str();
	long time = plate.get_time();
	//std::string path = plate.get_path();
	std::string pa = plate.get_path();
	const char * path = pa.c_str();
	CppSQLite3Buffer bufSQL;
	bufSQL.format("UPDATE Plate SET number=%Q, time=%ld, path=%Q WHERE _id=%d", number, time, path, id);
	int flag = db.execDML(bufSQL);
	if (flag == 1)
		return 0;
	return 1;
}

Plate* PlateDao::findById(int id)
{
	CppSQLite3DB db;
	db.open(gszFile);
	CppSQLite3Buffer bufSQL;
	bufSQL.format("SELECT * FROM plate WHERE _id=%d",id);
	CppSQLite3Table t = db.getTable(bufSQL);
	if (t.numFields() == 0)
		return nullptr;
	else
	{
		t.setRow(0);
		Plate* p = new Plate;
		p->set_id(atoi(t.fieldValue(0)));
		p->set_number(t.fieldValue(1));
		p->set_time(atol(t.fieldValue(2)));
		p->set_path(t.fieldValue(3));
		return p;
	}
}

std::vector<Plate *> PlateDao:: findByNumber(std::string number)
{
	int row;
	std::vector<Plate *> v;
	const char* num = number.c_str();
	CppSQLite3DB db;
	db.open(gszFile);
	CppSQLite3Buffer bufSQL;
	bufSQL.format("SELECT * FROM Plate WHERE number=%Q", num);
	CppSQLite3Table t = db.getTable(bufSQL);
	if (t.numFields() == 0)
		return v;
	else
		for (row = 0; row < t.numRows(); ++row)
		{
			t.setRow(row);
			Plate* p = new Plate;
			p->set_id(atoi(t.fieldValue(0)));
			p->set_number(t.fieldValue(1));
			p->set_time(atol(t.fieldValue(2)));
			p->set_path(t.fieldValue(3));
			v.push_back(p);
		}
	return v;
}

std::vector<Plate *> PlateDao::findByTime(std::string time)
{
	int row;
	std::vector<Plate *> v;
	const char* ti = time.c_str();
	CppSQLite3DB db;
	db.open(gszFile);
	//CppSQLite3Buffer bufSQL;
	//bufSQL.format("SELECT * FROM Plate WHERE date(time, 'unixepoch')==date(%Q)",ti);
	//CppSQLite3Table t = db.getTable(bufSQL);
	char buf[128];
	sprintf_s(buf, "SELECT * FROM Plate WHERE date(time, 'unixepoch')==date(\'%s\')", ti);
	CppSQLite3Table t = db.getTable(buf);
	if (t.numFields() == 0)
		return v;
	else
		for (row = 0; row < t.numRows(); ++row)
		{
			t.setRow(row);
			Plate* p = new Plate;
			p->set_id(atoi(t.fieldValue(0)));
			p->set_number(t.fieldValue(1));
			p->set_time(atol(t.fieldValue(2)));
			p->set_path(t.fieldValue(3));
			v.push_back(p);
		}
	return v;
}

std::vector<Plate *> PlateDao::findAll()
{
	int row;
	std::vector<Plate *> v;
	CppSQLite3DB db;
	db.open(gszFile);
	CppSQLite3Table t = db.getTable("SELECT * FROM Plate");
	if (t.numFields() == 0)
		return v;
	else
		for (row = 0; row < t.numRows(); ++row)
		{
			t.setRow(row);
			Plate* p = new Plate;
			p->set_id(atoi(t.fieldValue(0)));
			p->set_number(t.fieldValue(1));
			p->set_time(atol(t.fieldValue(2)));
			p->set_path(t.fieldValue(3));
			v.push_back(p);
		}
	return v;
}
