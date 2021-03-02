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
	PARSER,
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
	size_t _length;
	std::list<std::string>_tokens;
	int _error_flag;
	int _parser_flag;
	bool _parser_tokens();
	bool _parser_start_line();
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
	bool parser_head();
	size_t find(std::string &s1, std::string &s2);
	void to_upper(std::string &str);
	void to_lower(std::string &str);
	void parser();
};


#endif //HTTP_HPP
