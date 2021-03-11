//
// Created by Elwin Babaew on 3/6/21.
//

#ifndef WEBSERVER_CGIENV_HPP
#define WEBSERVER_CGIENV_HPP

#include <list>
#include <unistd.h>
#include "../Client.hpp"

class CgiEnv{
private:
	Client client;
	t_locations locations;

	std::list<std::string> env;
public:
	CgiEnv(const Client &_client):client(_client){
	}

	CgiEnv(const Client &_client, t_locations _locations):client(_client){
		std::map<std::string, std::string>m = client.getHttp().getStartLine();

		locations.cgi_path = _locations.cgi_path;
		locations.location = _locations.location;
		locations.method = _locations.method;
		locations.autoindex = _locations.autoindex;
		locations.cgi_extensions = _locations.cgi_extensions;
		locations.full_loc = _locations.full_loc;
		locations.index_types = _locations.index_types;
		locations.max_body_size = _locations.max_body_size;
		locations.root = _locations.root;
		locations.upload_storage = _locations.upload_storage;
	}

	const std::list<std::string> &getEnv() const {
		return env;
	}
	CgiEnv &createEnv();
	char **getEnvArray();

private:
	std::string getAuthType();
	std::string getContentLength();
	std::string getContentType();
	std::string getGatewayInterface();
	std::string getPathInfo();
	std::string	getPathTranslated();
	std::string getQueryString();
	std::string getRemoteAddr();
	std::string getRemoteIdent();
	std::string getRemoteUser();
	std::string getRequestMethod();
	std::string getRequestUri();
	std::string getScriptName();
	std::string getServerName();
	std::string getServerPort();
	std::string getServerProtocol();
	std::string getServerSoftware();
};

CgiEnv &CgiEnv::createEnv() {
	env.push_back(getAuthType());
	env.push_back(getContentLength());
	env.push_back(getGatewayInterface());
	env.push_back(getPathInfo());
	env.push_back(getPathTranslated());
	env.push_back(getQueryString());
	env.push_back(getRemoteAddr());
	env.push_back(getRemoteAddr());
	env.push_back(getRemoteIdent());
	env.push_back(getRemoteUser());
	env.push_back(getRequestMethod());
	env.push_back(getRequestUri());
	env.push_back(getScriptName());
	env.push_back(getServerName());
	env.push_back(getServerPort());
	env.push_back(getServerProtocol());
	env.push_back(getServerSoftware());
	return *this;
}

std::string CgiEnv::getAuthType() {
	/* Возможно стоит поменять на поиск из auth-scheme    Authorization: Basic YWxhZGRpbjpvcGVuc2VzYW1l*/
	return std::string("AUTH_TYPE=Basic");
}

std::string CgiEnv::getContentLength() {
	if (client.getHttp().getHeadMap().find("content-length") != client.getHttp().getHeadMap().end())
		return std::string("CONTENT_LENGTH=" + client.getHttp().getHeadMap().find("content-length")->second);
	else
		return std::string("CONTENT_LENGTH=");
}

std::string CgiEnv::getContentType() {
	if (client.getHttp().getHeadMap().find("content-type") != client.getHttp().getHeadMap().end())
		return std::string("CONTENT_TYPE=" + client.getHttp().getHeadMap().find("content-type")->second);
	else
		return std::string("CONTENT_TYPE=");
}

std::string CgiEnv::getGatewayInterface() {
	/* Версия CGI/1.1 */
	return std::string("GATEWAY_INTERFACE=CGI/1.1");
}

std::string CgiEnv::getPathInfo() {
	/* Полный путь до файла  getcwd add */
	return std::string("PATH_INFO=" + client.getHttp().getStartLine().find("location")->second);
}

std::string CgiEnv::getPathTranslated() {
	/* Полный путь до файла */
	return std::string("PATH_TRANSLATED=" + client.getHttp().getStartLine().find("location")->second);
}

std::string CgiEnv::getQueryString() {
	if (client.getHttp().getStartLine().find("query_string") != client.getHttp().getStartLine().end())
		return std::string("QUERY_STRING=" + client.getHttp().getStartLine().find("query_string")->second);
	else
		return std::string("QUERY_STRING=");

}

std::string CgiEnv::getRemoteAddr() {
	/* адресс клиента */
//	return client.get_remote_addr();
	return std::string("REMOTE_ADDR=192.168.1.0");
}

std::string CgiEnv::getRemoteIdent() {
	/* пока нет */
//	return client.get_remote_ident();
	return std::string("REMOTE_IDENT=user");
}

std::string CgiEnv::getRemoteUser() {
	/* пока нет */
//	return client.get_remote_user();
	return std::string("REMOTE_USER=user");
}

std::string CgiEnv::getRequestMethod() {
	if (client.getHttp().getStartLine().find("method") != client.getHttp().getStartLine().end())
		return std::string("REQUEST_METHOD=" + client.getHttp().getStartLine().find("method")->second);
	else
		return std::string("REQUEST_METHOD=");
}

std::string CgiEnv::getRequestUri() {
	if (client.getHttp().getStartLine().find("uri") != client.getHttp().getStartLine().end())
		return std::string("REQUEST_URI=" + client.getHttp().getStartLine().find("uri")->second);
	else
		return std::string("REQUEST_URI=");
}

std::string CgiEnv::getScriptName() {
	/* name scrypt / не работает*/
//	return client
	return std::string("SCRYPT_NAME=" + locations.cgi_path);
}

std::string CgiEnv::getServerName() {
	/* сервер name в confige / не работает*/
//	return std::string(client.config.getServername());
	return std::string("SERVER_NAME=MeServer");
}

std::string CgiEnv::getServerPort() {
	/* getPort сервер порт */
//	return std::string("SERVER_PORT=" + client.config.getPort);
	return std::string("SERVER_PORT=80");
}

std::string CgiEnv::getServerProtocol() {
	return std::string("SERVER_PROTOCOL=HTTP/1.1");
}

std::string CgiEnv::getServerSoftware() {
	return std::string("SERVER_SOFTWARE=GavnoIsBrevna&Palock");
}

char **CgiEnv::getEnvArray() {
	char **pString = (char**)malloc(sizeof (char**) * (getEnv().size() + 1));
	std::list<std::string>::const_iterator j = getEnv().begin();
	int i = 0;
	for (; i < getEnv().size(); ++i) {
		pString[i] = strdup(j->c_str());
		j++;
	}
	pString[i] = NULL;
	return pString;
}

/* getServerPort
 * getServerName
 * getScriptName
 * getRemoteUser
 * getRemoteIdent
 * не работают так как нужно искать или в config или по папкам
 */
#endif //WEBSERVER_CGIENV_HPP
