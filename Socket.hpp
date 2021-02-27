//
// Created by Kanat Saribaew on 2/24/21.
//

#ifndef SOCKET_HPP
#define SOCKET_HPP
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Http.hpp"
class Socket {
private:
	char buf[2048];
public:
	Socket();
	Socket(const std::string &addres, const std::string &port);
	void listen_socket();
	int accept_socket();
	void connect_socket();
	const std::string &getAddres() const;
	void setAddres(const std::string &addres);
	const std::string &getPort() const;
	void setPort(const std::string &port);
	void close_socet(int sock);

	int getSock() const;

	std::pair<std::string, bool> receive(int sock_fd, Http &host);

	void response(int sock_fd, const std::string &val);

	class BadAddress : public std::exception{
	virtual const char * what() const throw();
	};

	class SocketError : public std::exception{
		virtual const char * what() const throw();
	};

	class BadPort : public std::exception{
		virtual const char * what() const throw();
	};
private:
	std::string _addres;
	std::string _port;
	int _sock;
	sockaddr_in _sock_addr;
	socklen_t _size_sock_addr;
};


#endif //SOCKET_HPP
