//
// Created by Kanat Saribaew on 2/26/21.
//

#include "Http.hpp"

Http::Http() : _status(READ), _body(), _head(), _buffer(){}

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
void Http::parser_head() {

	size_t pos = 0;
	std::list<std::string>tokens;
	std::string delimiter = "\r\n";
	while ((pos = _buffer.find(delimiter)) != std::string::npos) {
		tokens.push_back(_buffer.substr(0, pos));
		_buffer.erase(0, pos + delimiter.length());
		if (tokens.back().length() == 0){
			if (_buffer)
		}
	}
	std::list<std::string>::iterator it = tokens.begin();
	for (; it != tokens.end(); ++it){
		std::cout << *it << std::endl;
	}
}