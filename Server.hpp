//
// Created by Kanat Saribaew on 3/5/21.
//

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Client.hpp"
#include "Socket.hpp"
#include "ClassParser.hpp"
#include "HttpHeaders.hpp"
class Server {
private:
	HttpHeaders generate_headers;
	Socket _socket;
	int _socket_server;
	t_server_config_data _config;
	std::vector<Client> _client;
	std::vector<std::string> _tmp;
	void _controller(Client &, t_locations &, std::string&, std::pair<bool, size_t>);
	std::vector<std::string> _error_page();
	std::string _get_remote_addr(int fd, sockaddr_in *addr, socklen_t *len);
	std::pair<bool, std::pair<size_t, size_t> >  _checking_сorrectness_of_request(Http &http);
	void _execute_methods(Client &client);
	void _error_handler(Http &http, int);
	std::string _get_extensions(const std::string &);
	std::vector<std::string> _get_method(Http &http);
	std::pair<bool, size_t> who_execute(t_locations &loc, std::string &method, std::string execute);
	std::pair<bool, size_t> _check_locations(const std::string &loc, const std::vector<t_locations> &locs);
	std::pair<bool, std::string>  _check_source(const std::string &location, const std::string &source);
	std::pair<bool, size_t> _check_methods(const std::string &method, const std::vector<std::string> &methods);

public:
	const std::vector<Client> &getClient() const;
	Server(const t_server_config_data &config);
	void new_connection();
	int getSocketServer() const;
	void recive(int index_client);
	void response(int index_client);
};


#endif //SERVER_HPP
