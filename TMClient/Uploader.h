#ifndef UPLOADER_H
#define UPLOADER_H

/*******************************************************************************
* Author: WqyJh
* Date: 2017/06/29
* Summary: 与服务器连接，向服务器上传文件
*******************************************************************************/

#include <string>
#include <vector>

class Uploader
{
public:
	Uploader();
	~Uploader();

	/*
	* Summary: 连接服务器
	* Parameters:
	*		ip: A std::string represents the ipv4 address
	*		port: A integer value represents the port number
	* Return:
	*		0 represents successfully connecting with server,
	*		otherwise connection failed
	*/
	int connect_server(const std::string &ip, int port);

	/*
	* Summary: 上传一个文件
	* Parameters:
	*		path: the file's parent directory
	*		filename: the file's name
	* Return:
	*		0 represents successfully uploading a file,
	*		otherwise uploading failed
	*/
	int upload(const std::string &path, const std::string &filename);

	/*
	* Summary: 批量上传文件
	* Parameters:
	*		path: these file's parent directory
	*		filenames: a vector contains serveral filename
	* Return:
	*		number of files that successfully uploaded
	*/
	int batch_upload(const std::string &path, const std::vector<const std::string> &filenames);
};

#endif // !UPLOADER_H



