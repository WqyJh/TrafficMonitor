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
	
	// todo: 添加 Getter 和 Setter

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


