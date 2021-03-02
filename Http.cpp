//
// Created by Kanat Saribaew on 2/26/21.
//

#include "Http.hpp"

Http::Http() : _status(READ), _body(), _head(), _buffer(), _length(500), _headMap(), _tokens(), _error_flag(), _parser_flag(){}

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
void Http::to_upper(std::string &str) {
	for (size_t i = 0; i < str.length(); ++i) {
		str[i] = std::toupper(str[i]);
	}
}
void Http::to_lower(std::string &str) {
	for (size_t i = 0; i < str.length(); ++i) {
		str[i] = std::tolower(str[i]);
	}
}
size_t Http::find(std::string &s1, std::string &s2) {
	for (size_t i = 0, pos = 0; i < s2.length(); ++i){
		if ((pos = s1.find_first_of(s2[i])) != std::string::npos){
			return pos;
		}
	}
	return std::string::npos;
}

bool Http::parser_head() {
	std::string header;
	std::string value;
	std::string invalid_character = "\"(),/:;<=>?@[\\]{} ";
	std::list<std::string>::iterator it = _tokens.begin();
	for (; it != _tokens.end(); ++it){
		to_lower(*it);
	}
	it  = _tokens.begin();
	for (; it != _tokens.end(); ++it){
		size_t pos;
		if ((pos = it->find(":")) != std::string::npos) {
			header = it->substr(0, pos);
			value = it->substr(pos + 1, it->length());
		}
		if (find(header, invalid_character) != std::string::npos){
			_status = ERROR;
			_error_flag = 400;
			return false;
		} else{
			std::pair<std::map<std::string, std::string>::iterator, bool>p = _headMap.insert(std::pair<std::string, std::string>(header, value));
			if (!p.second){
				if (header == "host" || header == "content-length"){
					_status = ERROR;
					_error_flag = 400;
					return false;
				}
//				std::cout << "SSSSS" <<value<<std::endl;
				p.first->second += "," + value;
			}
		}
	}
	return true;
}

bool Http::_parser_start_line() {
	size_t pos = 0;
	std::list<std::string> tokens;
	while ((pos = _tokens.front().find(" ")) != std::string::npos) {
		tokens.push_back(_tokens.front().substr(0, pos));
		_tokens.front().erase(0, pos + 1);
	}
	tokens.push_back(_tokens.front().substr(0, _tokens.front().length()));
	_tokens.pop_front();
	if (tokens.size() != 3) {
		_status = ERROR;
		_error_flag = 400;
		return false;
	}
	std::list<std::string>::iterator it = tokens.begin();
	_headMap["method"] = *it++;
	_headMap["uri"] = *it++;
	_headMap["http_version"] = *it++;
	return true;
}

bool Http::_parser_tokens() {
	size_t pos = 0;
	std::string token;
	std::string delimiter = "\r\n\r\n";
	if (_buffer.substr(0, 2) == "\r\n")
		_buffer.erase(0, 2);
	if ((pos = _buffer.find(delimiter)) != std::string::npos) {
		token += _buffer.substr(0, pos);
		_buffer.erase(0, pos + delimiter.length());
		delimiter = "\r\n";
		while ((pos = token.find(delimiter)) != std::string::npos) {
			_tokens.push_back(token.substr(0, pos));
			token.erase(0, pos + delimiter.length());
		}
		_tokens.push_back(token.substr(0, token.length()));
		if (_tokens.size() < 2) {
			_tokens.clear();
			_buffer.clear();
			_status = ERROR;
			_error_flag = 400;
			return false;
		}
		_status = PARSER;
		return true;
	}
	return false;
}

int Http::getErrorFlag() const {
	return _error_flag;
}

void Http::setErrorFlag(int errorFlag) {
	_error_flag = errorFlag;
}

void Http::parser() {
	std::cout << _buffer<<std::endl<<std::endl;
	if (!_parser_tokens()){
		std::cout << "error tokens"<<std::endl;
		return;
	}
	if (!_parser_start_line()){
		std::cout << "error start line"<<std::endl;
		return;
	}
	if (!parser_head()){
		std::cout << "error headers"<<std::endl;
		return;
	}
	std::map<std::string, std::string>::iterator it = _headMap.begin();
	for (; it != _headMap.end(); ++it){
		std::cout << it->first << ":" << it->second<<std::endl;
	}
	std::cout <<std::endl<<std::endl;
	_tokens.clear();
	_buffer.clear();
}

int Http::getParserFlag() const {
	return _parser_flag;
}
