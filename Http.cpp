//
// Created by Kanat Saribaew on 2/26/21.
//

#include "Http.hpp"

Http::Http() : _status(READ), _body(), _head(), _buffer(), _length(500), _headMap(), _start_line(), _error_flag(), _parser_flag(){}

STATUS Http::getStatus() const {
	return _status;
}

void Http::setStatus(STATUS status) {
	_status = status;
}


const std::string &Http::getBody() const {
	return _body;
}

void Http::setBody(const std::string &body) {
	_body = body;
}

const std::string &Http::getHead() const {
	return _head;
}

void Http::setHead(const std::string &head) {
	_head = head;
}

const std::string &Http::getBuffer() const {
	return _buffer;
}

void Http::setBuffer(const std::string &buffer) {
	_buffer = buffer;
}

size_t Http::getLength() const {
	return _length;
}

void Http::setLength(size_t length) {
	_length = length;
}


int Http::getParserFlag() const {
	return _parser_flag;
}

const std::map<std::string, std::string> &Http::getHeadMap() const {
	return _headMap;
}

void Http::setHeadMap(const std::map<std::string, std::string> &headMap) {
	_headMap = headMap;
}

const std::map<std::string, std::string> &Http::getStartLine() const {
	return _start_line;
}

void Http::setStartLine(const std::map<std::string, std::string> &startLine) {
	_start_line = startLine;
}

void Http::setParserFlag(int parserFlag) {
	_parser_flag = parserFlag;
}

void Http::setErrorFlag(int errorFlag) {
	_error_flag = errorFlag;
}
