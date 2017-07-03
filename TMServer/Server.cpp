#include <string>
#include <sstream>
#include <ctime>
#include <iostream>
#include <fstream>
#include <thread>
#include <direct.h>
#include "Server.h"
#include "..\TMClient\FileInfo.h"
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll


static std::string get_postfix(int len)
{
	char *s = new char[len + 2];
	s[0] = '_';
	srand((unsigned int)clock());
	for (int i = 1; i < len + 1; ++i) {
		s[i] = 97 + rand() % 26;
	}
	s[len + 1] = '\0';
	auto rets = std::string(s);
	delete[] s;
	return rets;
}

static inline std::string get_file_name(std::string filename)
{
	std::string postfix = get_postfix(4);
	unsigned long index = filename.find_last_of('.');
	if (index == std::string::npos)
		return filename.append(postfix);
	else
		return filename.insert(index, postfix);
}

Server::~Server()
{
	if (_sock > 0 || _serv_thread != nullptr) {
		stop();
	}
}

int Server::init()
{
	WORD version = MAKEWORD(2, 2);
	int ret = WSAStartup(version, &_wsa_data);
	if (ret != 0)
	{
		std::cout << "加载 ws2_32.dll 失败" << std::endl;
	}
	return ret;
}

void Server::stop()
{
	set_running(false);

	if (_sock > 0) {
		shutdown(_sock, SD_BOTH);
		closesocket(_sock);
	}
	if (_serv_thread != nullptr)
	{
		_serv_thread->join();
		delete _serv_thread;
		_serv_thread = nullptr;
	}

	WSACleanup();
}

Server::Server(std::string ip, int port)
	: _sock(0), _ip(ip), _port(port), _buf_size(1024), _running(false),
	_serv_thread(nullptr)
{
}

int Server::create_bind_listen()
{
	//创建套接字
	_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (_sock == INVALID_SOCKET) {
		fprintf(stderr, "Failed to create socket\n");
		goto create_bind_listen_fail;
	}
	printf("Succeed to create socket\n");

	//将套接字和IP、端口绑定
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
	serv_addr.sin_family = AF_INET;  //使用IPv4地址
	serv_addr.sin_addr.s_addr = inet_addr(_ip.c_str());  //具体的IP地址
	serv_addr.sin_port = htons(_port);  //端口
	if (bind(_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) != 0)
	{
		fprintf(stderr, "Bind port %d failed\n", _port);
		goto create_bind_listen_fail;
	}
	printf("Bind port %d\n", _port);

	//进入监听状态，等待用户发起请求，请求队列长度为10
	if (listen(_sock, 10) != 0)
	{
		fprintf(stderr, "listen on socket failed\n");
		goto create_bind_listen_fail;
	}
	printf("Server Socket Port:%d\n", _port);
	printf("Starting accepting...\n");

	return 0;
create_bind_listen_fail:
	return 1;
}

int Server::serve()
{
	if (_serv_thread != nullptr)
		return 1;

	set_running(true);
	_serv_thread = new std::thread([this]() {
		if (create_bind_listen() == 0)
		{
			loop();
		}
		printf("server thread ended\n");
	});
	return 0;
}

void Server::set_running(bool running)
{
	_running_mutex.lock();
	_running = running;
	_running_mutex.unlock();
}


int Server::accept_file(int clnt_sock)
{
	FileInfo info;
	char *buf = new char[_buf_size];
	int len;
	int total(0);
	int ret = 0;
	// 接收客户端传来的文件信息，包括文件名和文件长度
	int size = recv(clnt_sock, (char *)&info, sizeof(FileInfo), 0);
	// 接收文件内容
	if (size == sizeof(FileInfo))
	{
		printf("Receiving %s  length = %d\n", info.filename, info.file_len);
		// 新建一个文件，准备写入数据
		std::string filename = get_file_name(info.filename);
		std::ofstream file;
		file.open(filename, std::ios::out | std::ios::trunc | std::ios::binary);
		while (total < info.file_len) {
			if (total + _buf_size <= info.file_len) {
				len = recv(clnt_sock, buf, _buf_size, 0);
				total += len;
			}
			else {
				len = recv(clnt_sock, buf, info.file_len - total, 0);
				total += len;
			}
			printf("Receive %d\r", total);
			file.write(buf, len);
		}
		putchar('\n');
		file.flush();
		file.close();

		/*sprintf(buf, "file %s accepted\n", info.filename);
		send(clnt_sock, buf, _buf_size, 0);*/
	}
	else
	{
		printf("No more files\n");
		ret = 1;
	}

	delete[] buf;
	return ret;
}

bool Server::is_running()
{
	bool b;
	_running_mutex.lock();
	b = _running;
	_running_mutex.unlock();
	return b;
}

int Server::send_message(SOCKET clnt_sock, std::string msg)
{
	char *buf = new char[_buf_size];
	sprintf(buf, "%s", msg);
	int size = send(clnt_sock, buf, _buf_size, 0);
	delete[] buf;
	return size == _buf_size;
}

void Server::loop()
{
	fd_set socket_set;
	fd_set read_set;
	FD_ZERO(&socket_set);
	FD_SET(_sock, &socket_set);
	timeval tv;

	while (true)
	{
		_running_mutex.lock();
		if (!_running) {
			_running_mutex.unlock();
			goto stop;
		}
		_running_mutex.unlock();

		FD_ZERO(&read_set);
		read_set = socket_set;
		tv = { (long)5, (long)0 };

		if (select(0, &read_set, NULL, NULL, &tv) > 0)
		{
			for (int i = 0; i < socket_set.fd_count; ++i)
			{
				if (FD_ISSET(socket_set.fd_array[i], &read_set))
				{
					SOCKADDR clnt_addr;
					int clnt_addr_size = sizeof(SOCKADDR);
					SOCKET clnt_sock;
					if (socket_set.fd_array[i] == _sock) // server socket
					{
						clnt_sock = accept(_sock, (struct sockaddr *) &clnt_addr, &clnt_addr_size);
						if (clnt_sock == INVALID_SOCKET) // accept failed
						{
							std::cout << "failed to accept" << std::endl;
							goto stop;
						}
						else // accept succeed
						{
							//send_message(clnt_sock, "connect success");
							std::cout << "new connection come\n";
							printf("clnt_sock: %d\n", clnt_sock);
							FD_SET(clnt_sock, &socket_set);
						}
					}
					else // client socket
					{
						SOCKET s = socket_set.fd_array[i];
						while (accept_file(s) == 0);
						closesocket(s);
						FD_CLR(s, &socket_set);
					}
				}
			}
		}
	}

stop:
	for (int j = 0; j < socket_set.fd_count; ++j)
	{
		closesocket(socket_set.fd_array[j]);
	}
}