#ifndef PLATE_H
#define PLATE_H

/*
* Summary: 数据表对应的数据类
*/

#include <string>

class Plate
{
public:
	Plate();
	~Plate();

	Plate(int, std::string, long, std::string);
	
	int get_id();
	void set_id(int);

	std::string get_number();
	void set_number(std::string);

	long get_time();
	void set_time(long);

	std::string get_path();
	void set_path(std::string);

private:

	/*
	* 数据库主键
	*/
	int _id;

	/*
	* 车牌号码
	*/
	std::string _number;

	/*
	* 拍照时间
	*/
	long _time;

	/*
	* 图片地址
	*/
	std::string _path;
};

#endif // !PLATE_H


