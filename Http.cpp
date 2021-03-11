//
// Created by Kanat Saribaew on 2/26/21.
//

#include "Http.hpp"

Http::Http() : _status("read_header"), _body(), _buffer(), _length(1000), _headMap(), _start_line(), _error_flag(){}

const std::string &Http::getStatus() const {
	return _status;
}

void Http::setStatus(const std::string &status) {
	_status = status;
}


const std::string &Http::getBody() const {
	return _body;
}

const std::vector<std::string> &Http::getResponse() const {
	return response;
}

void Http::setResponse(const std::vector<std::string> &response) {
	Http::response = response;
}

void Http::setBody(const std::string &body) {
	_body = body;
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


void Http::setErrorFlag(int errorFlag) {
	_error_flag = errorFlag;
}

void Http::clear() {
	_headMap.clear();
	_buffer.clear();
	_body.clear();
	response.clear();
	_start_line.clear();
	_error_flag = 0;
	_length = 500;
}

int Http::getErrorFlag() const {
	return _error_flag;
}
