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
	int _id;
	std::string _number;
	long _time;
	std::string _path;
};

#endif // !PLATE_H


