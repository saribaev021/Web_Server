#include "Socket.hpp"
#include <vector>
#include <ctime>
#include <fcntl.h>
#include <sys/select.h>
timeval time_out;
int main()  {
	Socket socket1("127.0.0.1", "8000");
	socket1.listen_socket();
	std::vector<int>client_fd;
	volatile int a = 1;
	int max_d = socket1.getSock();
	int s = 0;
	while (a){
		fd_set readFds, writeFds;
		FD_ZERO(&readFds);
		FD_ZERO(&writeFds);
		FD_SET(socket1.getSock(), &readFds);
		for(int i = 0; i < client_fd.size(); ++i){
			FD_SET(client_fd[i], &readFds);
			if ()
				FD_SET(client_fd[i], &writeFds);
			if (client_fd[i] > max_d)
				max_d = client_fd[i];
		}
		time_out.tv_sec = 5;
		time_out.tv_usec = 000000;
		int res = select(max_d + 1, &readFds, &writeFds, nullptr, &time_out);
		if (res == 0){
			continue;
		}
		if (res < 0){
			if (errno != EINTR) {
				std::cerr << "error " <<res << std::endl;
				std::cout << strerror(errno) << std::endl;
			}
			else
			{
				std::cout << "error signal"<<std::endl;
				break;
			}
			continue;
		}
		if (FD_ISSET(socket1.getSock(), &readFds)){
			client_fd.push_back(socket1.accept_socket());
			fcntl(client_fd.back(), F_SETFL, O_NONBLOCK);
		}
		for(int i = 0; i < client_fd.size(); ++i){
			if (FD_ISSET(client_fd[i], &readFds)){
				std::cout << "S = "<< s<<std::endl;
				std::cout << "I = "<< i<<std::endl;
				std::pair<std::string, bool> res;
				res = socket1.receive(client_fd[i]));
				if (!res.second){
					close(client_fd[i]);
					std::vector<int>::iterator it =client_fd.begin();
					client_fd.erase(it + i);
				}
			}
			std::cout << "I = "<< i<<std::endl;
			if (FD_ISSET(client_fd[i], &writeFds)){
				std::cout << "ya tut" << std::endl;
				socket1.response(client_fd[i], "Hello, it's my first server!!!");
			}
		}
	}
	return 0;
}
