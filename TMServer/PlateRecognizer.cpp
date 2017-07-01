#include "stdafx.h"
#include "PlateRecognizer.h"
#include "easypr.h"


PlateRecognizer::PlateRecognizer()
{
}


PlateRecognizer::~PlateRecognizer()
{
}

std::string PlateRecognizer::recognize(const std::string &filename)
{
	auto result = easypr::api::plate_recognize(filename.c_str(), NULL, NULL);
	
	if (result.size() > 0)
		return result.at(0);

	return "";
}