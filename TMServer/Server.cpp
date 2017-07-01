#include <string>
#include <sstream>
#include <ctime>
#include <iostream>
#include <fstream>
#include "Server.h"
#include "..\TMClient\FileInfo.h"
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll

using namespace std;


static string get_postfix(int len)
{
	char *s = new char[len + 2];
	s[0] = '_';
	srand((unsigned int)clock());
	for (int i = 1; i < len + 1; ++i) {
		s[i] = 97 + rand() % 26;
	}
	s[len + 1] = '\0';
	auto rets = string(s);
	delete[] s;
	return rets;
}

static inline std::string get_file_name(std::string filename)
{
	std::string postfix = get_postfix(4);
	unsigned long index = filename.find_last_of('.');
	if (index == string::npos)
		return filename.append(postfix);
	else
		return filename.insert(index, postfix);
}

Server::Server()
	: _sock(0), _ip(""), _port(0), _buf_size(1024)
{
}

Server::~Server()
{
	if (_sock > 0) {
		stop();
	}
}

void Server::stop()
{
	if (_sock > 0) {
		closesocket(_sock);
	}
}

Server::Server(std::string ip, int port)
	: _sock(0), _ip(ip), _port(port), _buf_size(1024)
{
}

void Server::serve()
{
	//创建套接字
	_sock = socket(AF_INET, SOCK_STREAM, 0);
	//将套接字和IP、端口绑定
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
	serv_addr.sin_family = AF_INET;  //使用IPv4地址
	serv_addr.sin_addr.s_addr = inet_addr(_ip.c_str());  //具体的IP地址
	serv_addr.sin_port = htons(_port);  //端口
	bind(_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	//进入监听状态，等待用户发起请求
	listen(_sock, 20);
	printf("Server Socket Port:%d\n", _port);
	printf("Starting accepting...\n");
	loop();
}

static bool open_file(ofstream &ofs, string &filename)
{
	int count = 0;
	do {
		ofs.open(get_file_name(filename));
	} while (!ofs.is_open() && ++count < 5);
	return count < 5;
}

int Server::accept_file(int clnt_sock)
{
	FileInfo info;
	char *buf = new char[_buf_size];
	int len;
	int total(0);
	int ret = 0;
	//    FILE *fp;
	// 接收客户端传来的文件信息，包括文件名和文件长度
	if (recv(clnt_sock, (char *)&info, sizeof(FileInfo), 0) > 0) {
		// 新建一个文件，准备写入数据
		std::string filename = get_file_name(info.filename);
		ofstream file;
		file.open(filename, ios::out | ios::trunc | ios::binary);
		while (total < info.file_len) {
			if (total + _buf_size <= info.file_len) {
				len = recv(clnt_sock, buf, _buf_size, 0);
				total += len;
			}
			else {
				len = recv(clnt_sock, buf, info.file_len - total, 0);
				total += len;
			}
			file.write(buf, len);
		}
		file.flush();
		file.close();
	}
	else {
		ret = 1;
	}
	delete[] buf;
	return ret;
}

void Server::loop()
{
	while (1) {
		//接收客户端请求
		SOCKADDR clnt_addr;
		int clnt_addr_size = sizeof(SOCKADDR);
		int clnt_sock;
		char *buf = new char[_buf_size];
		memset(buf, '\0', _buf_size);
		clnt_sock = accept(_sock, (struct sockaddr *) &clnt_addr, &clnt_addr_size);
		printf("new connection come\n");
		while (accept_file(clnt_sock) == 0);
		closesocket(clnt_sock);
		delete[] buf;
	}
}