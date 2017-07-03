#ifndef SERVER_H
#define SERVER_H

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <string>
#include <mutex>
#include <vector>

/*******************************************************************************
* Author: WqyJh
* Date: 2017/06/29
* Summary: 一个简单的socket服务器，可以接受从客户端传来的文件，
*			客户端发送文件内容之前，必须发送一个 FileInfo 实例，
*			该实例包含了文件名和文件长度，一次请求可以按顺序发送多个文件
*			注意：这个类没有默认构造函数，在构造的时候必须传入地址和端口
*******************************************************************************/

class Server
{
public:

	~Server();

	/*
	* Summary: 创建一个服务器实例
	*		ip: 服务器绑定的 ip 地址，一般来说是 "127.0.0.1"
	*		port: 监听的端口号
	*/
	Server(std::string ip, int port);

	/*
	* Summary: 初始化服务器，使用服务器之前必须初始化，
	*			最好在应用程序初始化的时候调用这个函数
	* Return: 0 表示初始化成功，服务器可以使用，否则不能使用服务器
	*/
	int init();

	/*
	* Summary: 开始服务，服务器会运行在一个新线程里，不会阻塞当前线程
	* Return: 0 表示开启服务成功，1 表示失败，原因可能是已经有一个服务在运行
	*/
	int serve();

	/*
	* Summary: 停止服务
	*/
	void stop();

	/*
	* Summary: 判断服务器是否正在运行
	* Return: true 表示服务器正在运行
	*/
	bool is_running();

private:

	Server() = delete;

	Server(const Server &) = delete;

	Server &operator=(const Server &) = delete;

	WSADATA _wsa_data;

	SOCKET _sock;

	std::string _ip;

	int _port;

	int _buf_size;

	volatile bool _running;

	std::mutex _running_mutex;

	std::thread *_serv_thread;

	void set_running(bool running);

	int create_bind_listen();

	void loop();

	int accept_file(int clnt_sock);

	int send_message(SOCKET clnt_sock, std::string msg);

};

#endif // SERVER_H

