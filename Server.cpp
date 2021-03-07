//
// Created by Kanat Saribaew on 3/5/21.
//

#include "Server.hpp"

Server::Server(const t_server_config_data &config) : _config(config), _client() {
	_socket.setAddres(config.ip);
	_socket.setPort(config.port);
	try {
		_socket.listen_socket();
		_socket_server = _socket.getSock();
	}catch(std::exception &except) {
		std::cerr << except.what()<<std::endl;
		exit(1);
	}
	_tmp.push_back("HEAD");
	_tmp.push_back("GET");
	_tmp.push_back("POST");
	_tmp.push_back("PUT");
}
std::string Server::_get_remote_addr(int fd, sockaddr_in *addr, socklen_t *len) {
	getsockname(fd, reinterpret_cast<sockaddr *>(addr), len);
	uint32_t ip = addr->sin_addr.s_addr;
	uint8_t octet1 = (ip >> 24) & 0xFF;
	uint8_t octet2 = (ip >> 16) & 0xFF;
	uint8_t octet3 = (ip >> 8) & 0xFF;
	uint8_t octet4 = ip & 0xFF;
	std::stringstream stream;
	stream << octet1 << "." << octet2 << "." << octet3 << "." << octet4;
	return std::string(stream.str());
}

int Server::getSocketServer() const {
	return _socket_server;
}

const std::vector<Client> &Server::getClient() const {
	return _client;
}

void Server::_controller(Client &client) {
	Http http = client.getHttp();
	if (http.getStatus() == "error"){
		http.setResponse(_error_page());
	}else{
		std::vector<std::string>response;
		response.push_back("HTTP/1.1 200 OK\r\n"
						   "Server: nginx/1.14.2\r\n"
						   "Date: Sat, 06 Mar 2021 17:46:49 GMT\r\n"
						   "Content-Type: text/html\r\n"
						   "Content-Length: 6\r\n"
						   "Last-Modified: Sat, 06 Mar 2021 17:46:27 GMT\r\n"
						   "Connection: keep-alive\r\n"
						   "ETag: \"6043bff3-6\"\r\n"
						   "Accept-Ranges: bytes\r\n\r\n");
		response.push_back("hello");
		http.setResponse(response);
		http.setStatus("write");
	}
	client.setHttp(http);
}

void Server::new_connection() {
	sockaddr_in addr;
	socklen_t size = sizeof(sockaddr_in);
	try {
		 int sock =_socket.accept_socket(&addr, &size);
		 std::string address = _get_remote_addr(sock, &addr, &size);
		_client.push_back(Client(sock, address, _tmp, _config));
	}catch (std::exception &except){
		std::cerr << except.what()<<std::endl;
	}
}

void Server::recive(int index_client) {
	Http http = _client[index_client].getHttp();
	RequestParser parser = _client[index_client].getParserRequest();
	if (_socket.receive(_client[index_client].getFd(), http)){
		parser.parser(http);
		_client[index_client].setHttp(http);
		if (http.getStatus() == "error" || http.getStatus() == "execute"){
			_execute_methods(_client[index_client]);
		}
	}else{
		_client.erase(_client.begin() + index_client);
	}
}

std::vector<std::string> Server::_error_page() {
	std::vector<std::string> response;
	response.push_back(std::string("HTTP/1.1 400 Bad Request\r\n"
								   "Server: nginx/1.14.2\r\n"
								   "Date: Sat, 06 Mar 2021 17:09:06 GMT\r\n"
								   "Content-Type: text/html\r\n"
								   "Content-Length: 173\r\n"
								   "Connection: close\r\n\r\n"));
	response.push_back(std::string("<html>\n<head><title>400 Bad Request</title></head>\n"
								   "<body bgcolor=\"white\">\n"
								   "<center><h1>400 Bad Request</h1></center>\n"
								   "<hr><center>nginx/1.14.2</center>\n"
								   "</body>\n"
								   "</html>"));
	return response;
}

void Server::response(int index_client) {
	for (size_t i = 0; i < _client[index_client].getHttp().getResponse().size() ; ++i) {
		_socket.response(_client[index_client].getFd(), _client[index_client].getHttp().getResponse()[i]);
	}
	Http http = _client[index_client].getHttp();
	http.setStatus("read_header");
	_client[index_client].setHttp(http);
}


void Server::_execute_methods(Client &client) {
	Http http = client.getHttp();
	size_t pos;
	std::map<std::string, std::string>::const_iterator it = http.getStartLine().find("location");
	std::map<std::string, std::string>m = http.getStartLine();
	m["location"].insert(0, _config.root);
	http.setStartLine(m);

	if (http.getStatus() != "error") {
		http.setStatus("write");
		std::pair<bool, size_t> p = _check_locations(it->second, _config.location);
		if (p.first) {
			it = http.getStartLine().find("method");
			if (_check_methods(it->second, _config.location[p.second].method)) {
				std::pair<bool, std::string> pp = _check_source(http.getStartLine().find("location")->second,
																http.getStartLine().find("source")->second);
				if (pp.first) {
					std::map<std::string, std::string> tmp = http.getStartLine();
					tmp["source"] = pp.second;
					http.setStartLine(tmp);
					client.setHttp(http);
					_controller(client);
				} else {
					http.setResponse(_error_page());
					client.setHttp(http);
				}
			} else {
				http.setResponse(_error_page());
				client.setHttp(http);
			}
		} else {
			http.setResponse(_error_page());
			client.setHttp(http);
		}
	} else{
		http.setResponse(_error_page());
		client.setHttp(http);
	}
//	if ((pos = client.getHttp().getResponse().front().find("Content-Length:")) != std::string::npos){
//		std::string len = client.getHttp().getResponse().front().substr(pos + 15);
//		for (size_t i = 0; i < len.length(); ++i){
//			if ((pos = len.find(" ")) != std::string::npos || (pos = len.find("\r\n")) != std::string::npos){
//				len.erase(len.begin() + pos);
//			}
//		}
//		client.setMehtodSend(std::pair<bool, size_t>(true, atol(len.c_str())));
//	}
}

std::pair<bool, size_t> Server::_check_locations(const std::string &loc, const std::vector<t_locations> &locs) {
	std::vector<t_locations>locations = locs;
	std::string location = loc;
	for (size_t i = 0; i < locations.size(); ++i){
		if (locations[i].location.find(location) != std::string::npos){
			return std::pair<bool, int>(true, i);
		}
	}
	return std::pair<bool, int>(false, 0);
}
bool Server::_check_methods(const std::string &method, const std::vector<std::string> &methods){
	for (size_t i = 0; i < methods.size(); ++i) {
		if (methods[i] == method){
			return true;
		}
	}
	return false;
}
std::pair<bool, std::string> Server::_check_source(const std::string &location, const std::string &source){
	int fd;
	DIR *dir;
	struct dirent	*entry;
	std::string full_path = location +source;
	if (source.empty()){
		dir = opendir(location.c_str());
		while (dir && (entry = readdir(dir)) != nullptr){
			for (size_t  i = 0; i < _config.index_types.size(); ++i) {
				if (entry->d_name == _config.index_types[i]){
					closedir(dir);
					return std::pair<bool, std::string>(true, std::string(entry->d_name));
				}
			}
		}
		if (dir){
			closedir(dir);
		}
		return std::pair<bool, std::string>(false, std::string());
	}
	if ((fd = open(full_path.c_str(), O_RDONLY)) < 0){
		return std::pair<bool, std::string>(false, std::string());
	}
	return std::pair<bool, std::string>(true, std::string(source));
}