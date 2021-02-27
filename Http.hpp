//
// Created by Kanat Saribaew on 2/26/21.
//

#ifndef HTTP_HPP
#define HTTP_HPP

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <list>
enum STATUS{
	CLOSE,
	ERROR,
	READ,
	WRITE,
	EXECUTE
};
class Http {
private:
	STATUS _status;
	std::string _body;
	std::string _head;
	std::map<std::string,std::string> _headMap;
	std::string _buffer;
public:
	Http();
	STATUS getStatus() const;

	void setStatus(STATUS status);

	const std::string &getBody() const;

	void setBody(const std::string &body);

	const std::string &getHead() const;

	void setHead(const std::string &head);

	const std::string &getBuffer() const;

	void setBuffer(const std::string &buffer);
	void parser_head();
};


#endif //HTTP_HPP
