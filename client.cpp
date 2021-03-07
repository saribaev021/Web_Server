//
// Created by Kanat Saribaew on 3/5/21.
//

#include "Client.hpp"


int Client::getFd() const {
	return _fd;
}

void Client::setFd(int fd) {
	_fd = fd;
}

Client::Client(int fd, const std::string &addr, const std::vector<std::string> &methods, const t_server_config_data &conf): _fd(fd),
																					_parser_request(conf.server_name, methods, conf.max_body_size),_mehtod_send(false, 500),_remote_addr(addr), _config(conf){
	fcntl(_fd, F_SETFL, O_NONBLOCK);
}

const std::pair<bool, size_t> &Client::getMehtodSend() const {
	return _mehtod_send;
}

void Client::setMehtodSend(const std::pair<bool, size_t> &mehtodSend) {
	_mehtod_send = mehtodSend;
}

const Http &Client::getHttp() const {
	return _http;
}

void Client::setHttp(const Http &http) {
	_http = http;
}

const RequestParser &Client::getParserRequest() const {
	return _parser_request;
}
