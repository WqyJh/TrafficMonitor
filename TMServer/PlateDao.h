#ifndef PLATE_DAO_H
#define PLATE_DAO_H

#include "Plate.h"
#include <vector>

class PlateDao
{
public:
	PlateDao();
	~PlateDao();

	int save(const Plate &plate);

	int remove(const Plate &plate);

	int update(const Plate &plate);

	Plate &findById(int id);

	std::vector<Plate *> &findByNumber(std::string number);

	std::vector<Plate *> findByTime(std::string time);
};

#endif // !PLATE_DAO_H



