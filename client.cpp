//
// Created by Kanat Saribaew on 2/23/21.
//
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
int main(int argc, char **argv, char **envp) {
	sockaddr_in hint;
	socklen_t size_hint = sizeof(hint);
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1){
		std::cerr << "error"<<std::endl;
	}
	hint.sin_family = AF_INET;
	hint.sin_port = static_cast<unsigned short>((80 << 8) | (80 >> 8));
	hint.sin_addr.s_addr = inet_addr("192.168.99.156");
	std::string requset("GET / HTTP/1.1\r\n"
						"Host:ndreadno\r\n"
	  "Connection: keep-alive\r\n\r\n");
	std::ofstream file("server.log");

 	if (connect(sock, (sockaddr*)&hint, size_hint) != 0) {
		std::cerr << "error" << std::endl;
	} else{
		volatile int a = 1;
		int k = 0;
		int j = 0;
		while (a){
			fd_set readFds, writeFds;
			FD_ZERO(&readFds);
			FD_ZERO(&writeFds);
			FD_SET(sock, &readFds);
			FD_SET(sock, &writeFds);
			int i = select(sock + 1, &readFds, &writeFds, NULL, NULL);
			if (i < 0){
				std::cout << "error "<<strerror(errno)<<std::endl;
				exit(0);
			}
			if (i == 0){
				continue;
			}

			if (FD_ISSET(sock, &writeFds)){
				ssize_t count;
				if (k == 0)
					count = send(sock, requset.c_str(), requset.length(), 0);
//				else {
//					count = send(sock, "abc\r\n", 3, 0);
//				}
				k++;
//				std::cout <<"i: " <<i<<std::endl;
//				std::cout <<"count send: " <<count<<std::endl;
//				std::cout <<"request length: " <<requset.length()<<std::endl;

			}
			if (FD_ISSET(sock, &readFds)){
				j++;
				char buf[1000];
				memset(buf, 0, 1000);
				ssize_t count = recv(sock, buf, 1000, 0);
				if (count > 0) {
					std::cout << buf << std::endl;
					std::cout << "k: " << k << std::endl;
					std::cout << "j: " << j << std::endl;
					std::cout << "i: " << i << std::endl;
					std::cout << "count recv: " << count << std::endl;
				}
			}
		}
	}
	close(sock);
	return 0;
}