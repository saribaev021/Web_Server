//
// Created by Kanat Saribaew on 3/5/21.
//

#include "RequestParser.hpp"
void RequestParser::_to_upper(std::string &str) {
	for (size_t i = 0; i < str.length(); ++i) {
		str[i] = std::toupper(str[i]);
	}
}
void RequestParser::_to_lower(std::string &str) {
	for (size_t i = 0; i < str.length(); ++i) {
		str[i] = std::tolower(str[i]);
	}
}
size_t RequestParser::_find(std::string &s1, std::string &s2) {
	for (size_t i = 0, pos = 0; i < s2.length(); ++i){
		if ((pos = s1.find_first_of(s2[i])) != std::string::npos){
			return pos;
		}
	}
	return std::string::npos;
}
size_t RequestParser::_findi(std::string &s1, std::string &s2, size_t n) {
	size_t  i = 0;
	for (; i < n; ++i){
		if (s1[i] != s2[i]){
			if ((isalpha(s1[i]) && isalpha(s2[i])) && (tolower(s1[i]) == tolower(s2[i]))) {
				continue;
			}
			return std::string::npos;
		}
	}
	return i;
}

bool RequestParser::_parser_head() {
	std::string header;
	std::string value;
	std::string invalid_character = "\"(),/:;<=>?@[\\]{} ";
	std::list<std::string>::iterator it = _tokens.begin();
	for (; it != _tokens.end(); ++it){
		_to_lower(*it);
	}
	it  = _tokens.begin();
	for (; it != _tokens.end(); ++it){
		size_t pos;
		if ((pos = it->find(":")) != std::string::npos) {
			header = it->substr(0, pos);
			value = it->substr(pos + 1, it->length());
		}
		if (_find(header, invalid_character) != std::string::npos){
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
				p.first->second += "," + value;
			}
		}
	}
	return true;
}
void RequestParser::_parser_location(std::string &uri){
	std::string location;
	size_t pos = uri.find("?");
	location = pos != std::string::npos ? uri.substr(0, pos) : uri;
	if (pos != std::string::npos){
		uri.erase(0, pos + 1);
		_start_line["query_string"] = uri;
	}
	pos = location.find_last_of("/");
	_start_line["location"] = location.substr(0, pos + 1);
	location.erase(0, pos + 1);
	_start_line["source"] = location;
}
bool RequestParser::_parser_uri() {
	std::string delimetr = "http://";
	std::string uri = _start_line["uri"];
	size_t pos;
	if (_findi( uri, delimetr, delimetr.length()) != std::string::npos) {
		uri.erase(0, delimetr.length());
		size_t i = 0;
		for (; i < uri.length(); ++i){
			if (uri[i] == '/' || uri[i] == '?'){
				break;
			}
		}
		_start_line["host"] = uri.substr(0, i);
		if (uri[i] == '/'){
			uri.erase(0, i);
			_parser_location(uri);
		}else if (uri[i] == '?'){
			uri.erase(0, i + 1);
			_start_line["location"] = "/";
			_start_line["source"] = "";
			_start_line["query_string"] = uri;
		} else {
			_start_line["location"] = "/";
			_start_line["source"] = "";
		}
	}else if (uri[0] == '/') {
		_start_line["host"] = _server_names.front();
		_parser_location(uri);
	}else{
		_status = ERROR;
		_error_flag = 400;
		return false;
	}
	return true;
}

bool RequestParser::_check_validation_start_line() {
	size_t pos;
	if (std::find(_supported_methods.begin(), _supported_methods.end(), _start_line["method"]) == _supported_methods.end()){
		_status = ERROR;
		_error_flag = 501;
		return false;
	}
	if (std::find(_server_names.begin(), _server_names.end(), _start_line["host"]) == _server_names.end() || (pos = _start_line["http_version"].find("HTTP/")) != 0){
		_status = ERROR;
		_error_flag = 400;
		return false;
	}
	if ((pos = _start_line["http_version"].find("1.1", 5)) == std::string::npos){
		_status = ERROR;
		_error_flag = 505;
		return false;
	}
	if (_start_line["http_version"].length() != 8){
		_status = ERROR;
		_error_flag = 400;
		return false;
	}
	return true;
}
bool RequestParser::_parser_start_line() {
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
	_start_line["method"] = *it++;
	_start_line["uri"] = *it++;
	_start_line["http_version"] = *it++;
	if (!_parser_uri())
		return false;
	return _check_validation_start_line();
}

bool RequestParser::_parser_tokens() {
	size_t pos = 0;
	std::string token;
	std::string delimiter = "\r\n\r\n";
	if (_buffer.substr(0, 2) == "\r\n") {
		_buffer.erase(0, 2);
	}
	if (_buffer.length() > 8000){
		_status = ERROR;
		_error_flag = 400;
		return false;
	}
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

int RequestParser::getErrorFlag() const {
	return _error_flag;
}

void RequestParser::parser(Http &http) {
	_buffer = http.getBuffer();
	if (!_parser_tokens() || !_parser_start_line() || !_parser_head()){
		std::cout << "error " << _error_flag;
		http.setErrorFlag(_error_flag);
		http.setStatus(_status);
		return;
	}
	std::map<std::string, std::string>::iterator it2 = _start_line.begin();
	for (; it2 != _start_line.end(); ++it2){
		std::cout << it2->first << ":" << it2->second<<std::endl;
	}
	std::cout <<std::endl<<std::endl;
	std::map<std::string, std::string>::iterator it = _headMap.begin();
	for (; it != _headMap.end(); ++it){
		std::cout << it->first << ":" << it->second<<std::endl;
	}
	std::cout <<std::endl<<std::endl;
	http.setStatus(_status);
	http.setErrorFlag(_error_flag);
	http.setHeadMap(_headMap);
	http.setStartLine(_start_line);
	_tokens.clear();
	_buffer.clear();
}

STATUS RequestParser::getStatus() const {
	return _status;
}

void RequestParser::setStatus(STATUS status) {
	_status = status;
}

const std::map<std::string, std::string> &RequestParser::getHeadMap() const {
	return _headMap;
}

void RequestParser::setHeadMap(const std::map<std::string, std::string> &headMap) {
	_headMap = headMap;
}

const std::map<std::string, std::string> &RequestParser::getStartLine() const {
	return _start_line;
}

void RequestParser::setStartLine(const std::map<std::string, std::string> &startLine) {
	_start_line = startLine;
}

const std::string &RequestParser::getBuffer() const {
	return _buffer;
}

void RequestParser::setBuffer(const std::string &buffer) {
	_buffer = buffer;
}

const std::list<std::string> &RequestParser::getTokens() const {
	return _tokens;
}

void RequestParser::setTokens(const std::list<std::string> &tokens) {
	_tokens = tokens;
}

void RequestParser::setErrorFlag(int errorFlag) {
	_error_flag = errorFlag;
}

int RequestParser::getParserFlag() const {
	return _parser_flag;
}

void RequestParser::setParserFlag(int parserFlag) {
	_parser_flag = parserFlag;
}

RequestParser::RequestParser(const std::vector<std::string> &server_name, const std::vector<std::string> &supported_methods) : _status(), _supported_methods(supported_methods), _server_names(server_name),
																															   _headMap(), _start_line(), _buffer(), _tokens(), _error_flag(), _parser_flag() {}



