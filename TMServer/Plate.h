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

	//Plate 初始化时不赋予_id
	Plate(std::string, long, std::string);
	
	int get_id() const;
	void set_id(int);

	std::string get_number() const;
	void set_number(std::string);

	long get_time() const;
	void set_time(long);

	std::string get_path() const;
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
	* 从1970-1-1时开始的秒数 必须使用unix时间戳
	*/
	long _time;

	/*
	* 图片地址
	*/
	std::string _path;
};

#endif // !PLATE_H


