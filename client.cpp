//
// Created by Kanat Saribaew on 2/23/21.
//
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main(int argc, char **argv, char **envp) {
	sockaddr_in hint;
	socklen_t size_hint = sizeof(hint);
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1){
		std::cerr << "error"<<std::endl;
	}
	hint.sin_family = AF_INET;
	hint.sin_port = static_cast<unsigned short>((8000 << 8) | (8000 >> 8));
	hint.sin_addr.s_addr = inet_addr("");
	char str[256];
	memset(str, 0, sizeof(str));
	char str2[] = "hello";
	if (connect(sock, (sockaddr*)&hint, size_hint) != 0){
		std::cerr << "error"<<std::endl;
	}else{
		while (recv(sock, str, sizeof(str), 0) > 0) {
			std::cout << str << std::endl;
		}
	}
//	std::cout << "Hello, World!" << std::endl;
//	closocket(sock);
	close(sock);
	return 0;
}