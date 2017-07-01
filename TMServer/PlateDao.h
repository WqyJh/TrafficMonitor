#ifndef PLATE_DAO_H
#define PLATE_DAO_H

#include "Plate.h"
#include <vector>
#include "CppSQLite3.h"


class PlateDao
{
public:

	/*
	*实例化PlateDao对象时新建数据库以及table
	*/
	PlateDao();
	~PlateDao();

	/*
	* Summary: 将一个Plate实例保存到数据库中
	* Parameters:
	*		plate: 一个Plate实例
	* Return: 
	*		0表示成功，非0表示失败
	* Tips:
	*       Plate对象的_number _time _path存入数据库   _id为自增主键，数据库自动赋值
	*/
	int save(const Plate &plate);

	/*
	* Summary: 从数据库中移除一个Plate实例对应的数据项
	* Parameters:
	*		plate: 一个Plate实例
	* Return:
	*		0表示成功，非0表示失败
	* Tips:
	*       根据_id删除
	*/
	int remove(const Plate &plate);

	/*
	* Summary: 更新一个Plate实例对应的数据项
	* Parameters:
	*		plate: 一个Plate实例
	* Return:
	*		0表示成功，非0表示失败
	* Tips:
	*       由_id查询到数据，更改_number _time _path
	*/
	int update(const Plate &plate);

	/*
	* Summary: 按id查询一个数据
	* Parameters:
	*		id: 数据项的id
	* Return:
	*		如果查询成功，返回一个指向一个Plate实例的指针，失败则返回 nullptr
	*/
	Plate *findById(int id);

	/*
	* Summary: 按车牌号查询数据
	* Parameters:
	*		number: 表示车牌号的字符串
	* Return:
	*		如果查询成功，返回一组符合条件的Plate的指针，失败则返回一个长度为0的向量。
	*/
	std::vector<Plate *> findByNumber(std::string number);

	/*
	* Summary: 按时间查询数据
	* Parameters:
	*		time: 表示时间的字符串，以天为单位，格式为 "yy-mm-dd"，
	*				y表示年，m表示月，d表示日。
	* Return:
	*		如果查询成功，返回一组符合条件的Plate的指针，失败则返回一个长度为0的向量。
	*/
	std::vector<Plate *> findByTime(std::string time);
};

#endif // !PLATE_DAO_H



