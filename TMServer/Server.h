#ifndef SERVER_H
#define SERVER_H

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <string>

class Server
{
public:
	Server();
	~Server();
	Server(std::string ip, int port);
	void serve();
	void stop();
private:

	WSADATA _wsa_data;

	SOCKET _sock;

	std::string _ip;

	int _port;

	int _buf_size;

	void loop();

	int accept_file(int clnt_sock);
};

#endif // SERVER_H

