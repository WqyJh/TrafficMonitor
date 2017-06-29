#include "stdafx.h"
#include "Uploader.h"


Uploader::Uploader()
{
}


Uploader::~Uploader()
{
}

int Uploader::connect_server(const std::string &ip, int port)
{
	// todo: to implement it
	return 1;
}

int Uploader::upload(const std::string &path, const std::string &filename)
{
	// todo: to implement it
	return 1;
}

int Uploader::batch_upload(const std::string &path,
	const std::vector<const std::string> &filenames)
{
	// todo: to implement it
	return 0;
}