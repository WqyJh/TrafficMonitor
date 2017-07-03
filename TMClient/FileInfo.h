#ifndef FILEINFO_H
#define FILEINFO_H

/*
* Summary: 用于描述文件信息的结构体，用作客户端和服务器之间传输数据的协议
*/

#include <string>

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
extern void inline set_info_name(FileInfo &info, const std::string &filename);

/*
* Summary: 读取文件长度，保存到 FileInfo 对象中
* Parameters:
*		info: 文件信息对象
*		path: 文件所在路径
*/
extern void set_info_len(FileInfo &info, const std::string &path, const std::string &filename);

#endif // FILEINFO_H