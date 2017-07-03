#include "stdafx.h"
#include "FileManager.h"
#include <stdio.h>
#include <direct.h>

using namespace std;

static const char const *_raw_path = "images/raw/";
static const char const *_recognized_path = "images/recognized/";
static const char const *_unrecognized_path = "images/unrecognized/";

const char *get_raw_path()
{
	return _raw_path;
}

const char *get_recognized_path()
{
	return _recognized_path;
}

const char *get_unrecognized_path()
{
	return _unrecognized_path;
}

void replace_char(string &s, char c1, char c2)
{
	for (auto it = s.begin(); it != s.end(); ++it)
		if (*it == c1)
			*it = c2;
}

std::string parse_filename(const char *full_name)
{
	if (full_name != NULL)
	{
		string full(full_name);
		replace_char(full, '/', '\\');

		long last_slash = full.find_last_of('\\');

		if (last_slash != string::npos)
		{
			return full.substr(last_slash + 1);
		}
		else {
			return full;
		}
	}
	return string();
}

std::string get_full_name(const char *path, const char *filename)
{
	string fn(filename);
	string pth(path);
	replace_char(pth, '/', '\\');
	long last_index = pth.size() - 1;
	if (pth.find_last_of('\\') == last_index)
	{
		return pth + fn;
	}
	else
	{
		return pth + string("\\") + fn;
	}
}

int move_to_path(const char *file, const char *dest)
{
	string fn = parse_filename(file);
	string newfn = get_full_name(dest, fn.c_str());
	if (rename(file, newfn.c_str()) != 0)
	{
		return 1;
	}
	return 0;
}

std::string get_postfix(int len)
{
	char *s = new char[len + 2];
	s[0] = '_';
	LARGE_INTEGER  large_interger;
	QueryPerformanceCounter(&large_interger);
	srand((unsigned int)large_interger.LowPart);
	//srand((unsigned int)clock());
	for (int i = 1; i < len + 1; ++i) {
		s[i] = 97 + rand() % 26;
	}
	s[len + 1] = '\0';
	auto rets = std::string(s);
	delete[] s;
	return rets;
}
