#include "FileInfo.h"
#include <sys/stat.h>
#include <cstring>

void inline set_info_name(FileInfo &info, std::string filename)
{
	memcpy(info.filename, filename.c_str(), filename.length() + 1);
	// strncpy(info.filename, filename.c_str(), filename.length() + 1);
}


void set_info_len(FileInfo &info, std::string path, std::string filename)
{
	struct stat s;
	std::string fn;
	if (path.at(path.length() - 1) != '/')
		path.append("/");

	fn = path + filename;

	if (stat(fn.c_str(), &s) < 0)
		info.file_len = -1;
	info.file_len = s.st_size;
}