//
// Created by Kanat Saribaew on 3/5/21.
//

#include "Server.hpp"


Server::Server(const t_server_config_data &config) : _config(config), _client(), generate_headers(config.mime_map){
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
std::vector<std::string> Server::_get_method(Http &http) {
	std::vector<std::string>response(2, "");
	std::string body;
	std::string line;
	std::string header;
	std::string target_file = http.getStartLine().find("change_location")->second;
	target_file += http.getStartLine().find("source")->second;
	std::ifstream in(target_file);
	if (in.is_open()){
		while (std::getline(in, line)){
			body += line;
			if (!in.eof()){
				body += "\n";
			}
		}
		header = generate_headers.get_status("200");
		header += generate_headers.get_server();
		header += generate_headers.get_server_date();
		header += generate_headers.get_content_type(_get_extensions( http.getStartLine().find("source")->second));
		header += generate_headers.get_content_length(std::to_string(body.length()));
		header += generate_headers.get_last_modified(target_file);
		header += "\r\n";
		response[0] = header;
		response[1] = body;
	}
	return response;
}
void Server::_controller(Client &client, t_locations &locations, std::string &method, std::pair<bool, size_t>p)
{
	Http http = client.getHttp();
	if (p.first && method != "PUT"){
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
		response.push_back("hello\n");
		http.setResponse(response);
		http.setStatus("write");
	}else{
		http.setResponse(_get_method(http));
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
	response.push_back(std::string("HTTP/1.1 404 Not Found\r\n"
								   "Server: nginx/1.14.2\r\n"
								   "Date: Sat, 06 Mar 2021 17:09:06 GMT\r\n"
								   "Content-Type: text/html\r\n"
								   "Content-Length: 165\r\n"
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
	Http http = _client[index_client].getHttp();
	std::vector<std::string> response = http.getResponse();
	std::string status;
	size_t length = 500;
	size_t index = 0;
	if (response[0].length()){
		index = 0;
		length = response[0].length() < length ? response[0].length() : length;
	}else if (response[1].length()){
		index = 1;
		length = response[1].length() < length ? response[1].length() : length;
	}
	_socket.response(_client[index_client].getFd(), response[index], length);
	response[index].erase(0, length);
	http.setResponse(response);
	if (response[0].empty() && response[1].empty()) {
		http.setStatus("read_header");
		http.clear();
	}
	_client[index_client].setHttp(http);
}


void Server::_execute_methods(Client &client) {
	Http http = client.getHttp();
	std::pair<bool, std::pair<size_t, size_t> >p = std::make_pair(false, std::make_pair(http.getErrorFlag(), 0));

	if (http.getStatus() != "error") {
		http.setStatus("write");
		if ((p = _checking_сorrectness_of_request(http)).first){
			client.setHttp(http);
			t_locations loc = _config.location[p.second.first];
			std::string method = loc.method[p.second.second];
			_controller(client, loc, method, who_execute(loc, method, http.getStartLine().find("source")->second));
			return;
		}
	}
	_error_handler(http, p.second.first);
	client.setHttp(http);
}

std::pair<bool, size_t> Server::_check_locations(const std::string &loc, const std::vector<t_locations> &locs) {
	std::vector<t_locations>locations = locs;
	std::string location = loc;
	for (size_t i = 0; i < locations.size(); ++i){
		if (locations[i].location.find(location) != std::string::npos){
			return std::pair<bool, int>(true, i);
		}
	}
	return std::pair<bool, int>(false, 404);
}
std::pair<bool, size_t> Server::_check_methods(const std::string &method, const std::vector<std::string> &methods){
	for (size_t i = 0; i < methods.size(); ++i) {
		if (methods[i] == method){
			return std::pair<bool, size_t>(true, i);
		}
	}
	return std::pair<bool, size_t>(false, 405);
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
	close(fd);
	return std::pair<bool, std::string>(true, std::string(source));
}
void Server::_error_handler(Http &http, int cod_error) {
//	std::vector<std::string>respons;
	http.setStatus("write");
	http.setErrorFlag(cod_error);
	http.setResponse(_error_page());
}

std::pair<bool, std::pair<size_t, size_t> > Server::_checking_сorrectness_of_request(Http &http) {
	std::string location = http.getStartLine().find("location")->second;
	location.insert(0, _config.root);
	std::pair<bool, size_t> p_method(false, 0);
	std::pair<bool, std::string> p_source(false, "");
	std::pair<bool, size_t> p_loc(false, 0);
	if (!(p_loc = _check_locations(location, _config.location)).first) {
		return std::make_pair(false, std::make_pair(404, 0));
	}
	if (!(p_method = _check_methods(http.getStartLine().find("method")->second, _config.location[p_loc.second].method)).first){
		return std::make_pair(false, std::make_pair(405, 0));
	}
	if ((p_source = _check_source(_config.location[p_loc.second].root, http.getStartLine().find("source")->second)).first) {
		std::map<std::string, std::string>m_start_line = http.getStartLine();
		m_start_line["source"] = p_source.second;
		m_start_line["change_location"] = _config.location[p_loc.second].root;
		m_start_line["path_info"].insert(0,m_start_line["change_location"] + m_start_line["source"]);
		http.setStartLine(m_start_line);
		return std::make_pair(true, std::make_pair(p_loc.second, p_method.second));
	}else{
		return std::make_pair(false, std::make_pair(404, 0));
	}
}

std::pair<bool, size_t> Server::who_execute(t_locations &loc, std::string &method, std::string execute) {
	size_t pos;
	std::vector<std::string>extensions = loc.cgi_extensions;
	for (size_t  i = 0; i < extensions.size(); ++i) {
		if ((pos = execute.find(extensions[i])) != std::string::npos && execute.substr(pos) == extensions[i] && execute.length() != extensions[i].length()){
			return std::make_pair(true, i);
		}
	}
	return std::make_pair(false, 0);;
}

std::string Server::_get_extensions(const std::string &str) {
	for (size_t i = str.length(); i > 0; --i) {
		if (str[i] == '.'){
			return str.substr(i);
		}
	}
	return std::string();
}
