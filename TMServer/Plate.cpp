
#include "Plate.h"



Plate::Plate()
{
}


Plate::~Plate()
{
}


Plate::Plate(std::string number, long time, std::string path)
{
	set_id(0);
	set_number(number);
	set_time(time);
	set_path(path);
}


int Plate::get_id() const
{
	return _id;
}
void Plate::set_id(int id)
{
	_id = id;
}


std::string Plate::get_number() const
{
	return _number;
}
void Plate::set_number(std::string number)
{
	_number = number;
}


long Plate::get_time() const
{
	return _time;
}
void Plate::set_time(long time)
{
	_time = time;
}


std::string Plate::get_path() const
{
	return _path;
}
void Plate::set_path(std::string path)
{
	_path = path;
}