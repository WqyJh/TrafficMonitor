#ifndef PLATE_RECOGNIZER_H
#define PLATE_RECOGNIZER_H

#include <string>

class PlateRecognizer
{
public:
	PlateRecognizer();
	~PlateRecognizer();

	/*
	* Summary: 识别图片上的车牌号
	* Parameters:
	*		filename: file's name with full path
	* Return:
	*		a string represents the plate number
	*/
	std::string recognize(const std::string &filename);
};

#endif // PLATE_RECOGNIZER_H



