
#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include "../Client.hpp"
#include "CgiEnv.hpp"
#include "Executor.hpp"
#include "../Server.hpp"

std::vector<std::string> parseResponse(std::string response) {
    std::vector<std::string> ret(3, "");
    int status;
    std::string stringStatus;

    size_t check = response.find("Status:");
    size_t len = response.find("\r\n\r\n");
    if (check == std::string::npos) {
        ret[0] = "200";
        if (!response.empty()) {
        	if (len != std::string::npos) {
				ret[1] = response.substr(0, len + 2);
				ret[2] = response.substr(len + 4);
			} else{
				ret[2] = response;
        	}

		}
    } else {
		if (!response.empty()) {
			ret[0] = response.substr(8, 3);
			ret[1] = response.substr(response.find('\n') + 1, len + 1 - response.find('\n'));
			ret[2] = response.substr(len + 4);
		}
    }
    return ret;
}

std::vector<std::string> requestHead(CgiEnv env) {
    Executor executor(env.createEnv().getEnvArray(), env.getCgiPath(), (
                              env.getClient().getHttp().getStartLine().find("source")->second),
                      env.getClient().getHttp().getBody(), env.getClient());
    executor.pipeFd();
    executor.launcher();
    executor.outputBody();
    std::string ret = executor.getBody();
    return parseResponse(ret);
}

std::vector<std::string> requestGet(CgiEnv env) {
    Executor executor(env.createEnv().getEnvArray(), env.getCgiPath(), (
                              env.getClient().getHttp().getStartLine().find("source")->second),
                      env.getClient().getHttp().getBody(), env.getClient());
    executor.pipeFd();
    executor.putBody();
    executor.launcher();
    executor.outputBody();
    std::string ret = executor.getBody();
    return parseResponse(ret);
}

std::vector<std::string> requestPost(CgiEnv env) {
    Executor executor(env.createEnv().getEnvArray(), env.getCgiPath(), (
                              env.getClient().getHttp().getStartLine().find("source")->second),
                      env.getClient().getHttp().getBody(), env.getClient());
    executor.pipeFd();
    executor.putBody();
    executor.launcher();
    executor.outputBody();
    std::string ret = executor.getBody();
    return parseResponse(ret);
}

std::vector<std::string> requestBody(const Client &client, t_server_config_data config,
                                     t_locations locations, std::string method, std::string cgi_path) {
    CgiEnv env(client, locations, cgi_path, config);
    if (method == "HEAD")
        return requestHead(env);
    else if (method == "POST")
        return requestPost(env);
    else if (method == "GET")
        return requestGet(env);
    return std::vector<std::string>(2, "");
}

#endif