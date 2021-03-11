
#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include "../Client.hpp"
#include "CgiEnv.hpp"
#include "Executor.hpp"
#include "../Server.hpp"

std::vector<std::string> requestHead(const Client &client, t_server_config_data config, t_locations locations) {
	CgiEnv env(client, locations);
	char *tmp = strdup("/Users/avallie/Desktop/ndreadno/cgi/test/test.php");
	Executor executor(env.createEnv().getEnvArray(), locations.cgi_path, tmp,
				client.getHttp().getBody());
	executor.pipeFd();
	executor.launcher();
	executor.inputBody();
	std::string ret = executor.getBody();
	size_t t = ret.find("\r\n\r\n");
	std::vector<std::string> vectorResponse(2);
	if (t != std::string::npos) {
		vectorResponse[0] = ret.substr(0, t);
		vectorResponse[1] = "";
	}
	return vectorResponse;
}

std::vector<std::string> requestGet(const Client &client, t_server_config_data config, t_locations locations) {
	CgiEnv env(client, locations);
	char *tmp = strdup("/Users/avallie/Desktop/ndreadno/cgi/test/test.php");
	Executor executor(env.createEnv().getEnvArray(), locations.cgi_path, tmp,
				client.getHttp().getBody());
	executor.pipeFd();
	executor.launcher();
	executor.inputBody();
	std::string ret = executor.getBody();
	size_t t = ret.find("\r\n\r\n");
	std::vector<std::string> vectorResponse(2);
	if (t != std::string::npos) {
		vectorResponse[0] = ret.substr(0, t);
		vectorResponse[1] = ret.substr(t);
	}
	return vectorResponse;
}

std::vector<std::string> requestPost(const Client &client, t_server_config_data config, t_locations locations) {
	CgiEnv env(client, locations);
	char *tmp = strdup("/Users/avallie/Desktop/ndreadno/cgi/test/test.php");
	Executor executor(env.createEnv().getEnvArray(), locations.cgi_path, tmp,
					  client.getHttp().getBody());
	executor.pipeFd();
	executor.putBody();
	executor.launcher();
	executor.inputBody();
	std::string ret = executor.getBody();
	size_t t = ret.find("\r\n\r\n");
	std::vector<std::string> vectorResponse(2);
	if (t != std::string::npos) {
		vectorResponse[0] = ret.substr(0, t);
		vectorResponse[1] = ret.substr(t);
	}
	return vectorResponse;
}


std::vector<std::string> requestPut(const Client &client, t_server_config_data config, t_locations locations) {
	CgiEnv env(client, locations);
	char *tmp = strdup("/Users/avallie/Desktop/ndreadno/cgi/test/test.php");
	Executor executor(env.createEnv().getEnvArray(), locations.cgi_path, tmp,
					  client.getHttp().getBody());
	executor.pipeFd();
	executor.putBody();
	executor.launcher();
	executor.inputBody();
	std::string ret = executor.getBody();
	size_t t = ret.find("\r\n\r\n");
	std::vector<std::string> vectorResponse(2);
	if (t != std::string::npos) {
		vectorResponse[0] = ret.substr(0, t);
		vectorResponse[1] = ret.substr(t);
	}
	return vectorResponse;
}

std::vector<std::string> requestBody(const Client &client, t_server_config_data config, t_locations locations, std::string method){
	if (method == "HEAD")
		return requestHead(client, config, locations);
	else if (method == "POST")
		return requestPost(client, config, locations);
	else if (method == "GET")
		return requestGet(client, config, locations);
	else if (method == "PUT")
		return requestPut(client, config, locations);
	return std::vector<std::string>(2, "");
}

#endif