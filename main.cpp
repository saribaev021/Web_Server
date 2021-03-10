
#include "Server.hpp"
bool compare(const t_locations &s1, const t_locations &s2){
	size_t key = 0;
	size_t key2 = 0;
	for (size_t i = 0; i < s1.location.length(); ++i){
		if (s1.location[i] == '/'){
			key++;
		}
	}
	for (size_t i = 0; i < s2.location.length(); ++i){
		if (s2.location[i] == '/'){
			key2++;
		}
	}
	return key < key2;
}
// std::vector<t_server_config_data>		parser_config(void)
// {
// 	ClassParser	p;

// 	p.fing_config_file();
// 	p.read_from_file();
// 	p.pars_data();
// 	p.data[0].location[0].root = "/Users/ndreadno/web_server";
// 	p.data[0].location[0].location = p.data[0].location[0].root + "/";
// 	p.data[0].location[0].method[0] = "GET";
// 	p.data[0].location[0].cgi_path = "/usr/bin/php";
// 	for (size_t i = 0; i < p.data.size(); ++i){
// 		std::sort(p.data[i].location.begin(), p.data[i].location.end(), compare);
// 	}
// 	return (p.data);
// }
std::vector<t_server_config_data>		parser_config(void)
{
	ClassParser	p;

	p.fing_config_file(); // поиск конфига
	p.read_from_file(); // чтение конфига
	p.pars_data(); // разбитие на токены
	p.set_default_values(); // установка значений (дефолтные/по серверу)
	return (p.get_data());
}

int main()  {
	timeval time_out;
//	Socket socket1("127.0.0.1", "8000");
//	server_name  = 127.0.0.1:80
//	socket1.listen_socket();
	std::vector<t_server_config_data> configs = parser_config();
	std::vector<Server>servers;
	for (size_t i = 0; i < configs.size(); ++i){
		servers.push_back(Server(configs[i]));
	}
//	socket1.listen_socket();
	std::vector<int>client_fd;
	volatile int a = 1;
	int max_d = servers[0].getSocketServer();
//	max_d = socket1.getSock();
//	exit(0);
	for (size_t i = 0; i < servers.size(); ++i){
		if (max_d < servers[i].getSocketServer()){
			max_d = servers[i].getSocketServer();
		}
	}
	int s = 0;
	while (a){
		fd_set readFds, writeFds;
		FD_ZERO(&readFds);
		FD_ZERO(&writeFds);
		for (size_t i = 0; i < servers.size(); ++i){
			FD_SET(servers[i].getSocketServer(), &readFds);
			for (size_t j = 0; j < servers[i].getClient().size(); ++j) {
				FD_SET(servers[i].getClient()[j].getFd(), &readFds);
				if (servers[i].getClient()[j].getHttp().getStatus() == "write") {
					FD_SET(servers[i].getClient()[j].getFd(), &writeFds);
				}
				if (servers[i].getClient()[j].getFd() > max_d)
					max_d = servers[i].getClient()[j].getFd();
			}
		}
		time_out.tv_sec = 5;
		time_out.tv_usec = 000000;
		int res = select(max_d + 1, &readFds, &writeFds, nullptr, &time_out);
		if (res == 0){
//			std::cout << "res"<<std::endl;
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
		for (size_t i = 0; i < servers.size(); ++i){
			if (FD_ISSET(servers[i].getSocketServer(), &readFds)){
				std::cout << "new connection"<<std::endl;
				servers[i].new_connection();
			}
		}
		for (size_t i = 0; i < servers.size(); ++i){
			for (size_t k = 0; k < servers[i].getClient().size(); ++k){
				if (FD_ISSET(servers[i].getClient()[k].getFd(), &readFds)){
					servers[i].recive(k);
//					std::cout <<"QWERT"<<servers[i].getClient()[k].getHttp().getStatus()<<std::endl;
				}
			}
		}
		for (size_t i = 0; i < servers.size(); ++i){
			for (size_t k = 0; k < servers[i].getClient().size(); ++k){
				if (FD_ISSET(servers[i].getClient()[k].getFd(), &writeFds)){
					servers[i].response(i);
				}
			}
		}
	}
	return 0;
}
