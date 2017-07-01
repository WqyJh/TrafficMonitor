#ifndef FILEINFO_H
#define FILEINFO_H

/*
* Summary: 用于描述文件信息的结构体，用作客户端和服务器之间传输数据的协议
*/

#include <string>
#include <sys/stat.h>
#include <cstring>

#define MAX_FILE_NAME 255

typedef struct
{
	/* 客户端发送的文件的文件名 */
	char filename[MAX_FILE_NAME];

	/* 该文件的长度 */
	long file_len;
} FileInfo;

/*
* Summary: 把用 std::string 表示的文件名复制到 FileInfo 对象中
* Parameters:
*		info: 文件信息对象
*		filename: 文件名
*/
void inline set_info_name(FileInfo &info, std::string filename)
{
	memcpy(info.filename, filename.c_str(), filename.length() + 1);
	// strncpy(info.filename, filename.c_str(), filename.length() + 1);
}

/*
* Summary: 读取文件长度，保存到 FileInfo 对象中
* Parameters:
*		info: 文件信息对象
*		path: 文件所在路径
*/
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

#endif // FILEINFO_H