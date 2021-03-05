//
// Created by Kanat Saribaew on 2/26/21.
//

#ifndef HTTP_HPP
#define HTTP_HPP

#include "Server.hpp"

class RequestParser;
class Http {
private:
	STATUS _status;
	std::string _body;
	std::string _head;
	std::map<std::string,std::string> _headMap;
	std::map<std::string,std::string> _start_line;
	std::string _buffer;
	size_t _length;
	int _error_flag;
public:
	const std::map<std::string, std::string> &getHeadMap() const;

	void setHeadMap(const std::map<std::string, std::string> &headMap);

	const std::map<std::string, std::string> &getStartLine() const;

	void setStartLine(const std::map<std::string, std::string> &startLine);

	void setParserFlag(int parserFlag);

private:
	int _parser_flag;
public:
	int getParserFlag() const;
	int getErrorFlag() const;

	void setErrorFlag(int errorFlag);

	size_t getLength() const;

	void setLength(size_t length);

	Http();
	STATUS getStatus() const;

	void setStatus(STATUS status);

	const std::string &getBody() const;

	void setBody(const std::string &body);

	const std::string &getHead() const;

	void setHead(const std::string &head);

	const std::string &getBuffer() const;

	void setBuffer(const std::string &buffer);
};


#endif //HTTP_HPP
