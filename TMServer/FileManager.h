#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>

/*
* Summary: 解析一个完整的路径，该路径表示的文件的名称
* Parameters: 
*		full_name: 完整的路径名，由目录和文件名两部分组成
* Return: 不含路径的文件名
*/
std::string parse_filename(const char *full_name);

/*
* Summary: 把目录和文件名拼成一个完整的路径名
* Parameters: 
*		path: 目录名
*		filename: 文件名
*/
std::string get_full_name(const char *path, const char *filename);

/*
* Summary: 返回一个形如"_xxx"的随机字符串
* Parameters:
*		len: 字符串长度，不包括开头的'_'字符和结尾的'\0'字符
*/
std::string get_postfix(int len);

/*
* Summary: 将一个文件 file 移动到 dest 表示的目录中
* Parameters:
*		file: 文件路径，它应该能正确地被访问到
*		dest: 目标目录
*/
int move_to_path(const char *file, const char *dest);

/*
* Summary: 把字符串 s 中所有的 c1 字符替换成 c2
*/
void replace_char(std::string &s, char c1, char c2);

const char *get_raw_path();

const char *get_recognized_path();

const char *get_unrecognized_path();

#endif // !FILE_MANAGER_H








