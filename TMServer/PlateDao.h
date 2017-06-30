#ifndef PLATE_DAO_H
#define PLATE_DAO_H

#include "Plate.h"
#include <vector>

class PlateDao
{
public:
	PlateDao();
	~PlateDao();

	/*
	* Summary: 将一个Plate实例保存到数据库中
	* Parameters:
	*		plate: 一个Plate实例
	* Return: 
	*		0表示成功，非0表示失败
	*/
	int save(const Plate &plate);

	/*
	* Summary: 从数据库中移除一个Plate实例对应的数据项
	* Parameters:
	*		plate: 一个Plate实例
	* Return:
	*		0表示成功，非0表示失败
	*/
	int remove(const Plate &plate);

	int update(const Plate &plate);

	Plate &findById(int id);

	std::vector<Plate *> &findByNumber(std::string number);

	std::vector<Plate *> findByTime(std::string time);
};

#endif // !PLATE_DAO_H



