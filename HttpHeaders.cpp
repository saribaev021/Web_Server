//
// Created by Kanat Saribaew on 3/12/21.
//

#include "HttpHeaders.hpp"

//std::vector<std::string> HttpHeaders::create_headers(Http &http, std::map<std::string, std::string>m, t_locations &loc, t_server_config_data &conf) {
//    std::map<std::string, std::string>star_line = http.getStartLine();
//    std::map<std::string, std::string>map_head = http.getHeadMap();
//    std::string header;
////	header +=
//    return std::vector<std::string>();
//}

HttpHeaders::HttpHeaders(const std::map<std::string, std::string> &mimeTypes) :_mime_types(mimeTypes) {
    _status["200"] = "HTTP/1.1 200 OK\r\n";
    _status["400"] = "HTTP/1.1 400 Bad Request\r\n";
    _status["404"] = "HTTP/1.1 404 Not Found\r\n";
    _status["405"] = "HTTP/1.1 405 Method Not Allowed\r\n";
}

const std::string HttpHeaders::get_date(time_t t) const{
    struct tm info;
    char buffer[64];

    std::string s = std::to_string(t);
    strptime(s.c_str(), " %s ", &info);
    strftime (buffer, sizeof(buffer), "%a, %d %b %Y %X %Z", &info);
    std::string str = buffer;
    return str;
}
const std::string HttpHeaders::get_server() const {
    return std::string("Server: web_server\r\n");
}

const std::string HttpHeaders::get_content_type(const std::string &extensions) const {
    std::map<std::string, std::string>::const_iterator  it;
    if ((it = _mime_types.find(extensions)) != _mime_types.end()){
        return std::string("Content-Type: " + it->second + "\r\n");
    }
    return std::string("Content-Type: application/octet-stream\r\n");
}

const std::string HttpHeaders::get_last_modified(const std::string &str) {
    struct stat	buf;
    int			result;

    result = stat(str.c_str(), &buf);
    if (result == 0){
        return "Last-Modified: " + get_date(buf.st_mtimespec.tv_sec) + "\r\n";
    }
    return  std::string();
}

const std::string HttpHeaders::get_server_date() const {
	struct timeval tv;
	time_t t;
	gettimeofday(&tv, NULL);
	t = tv.tv_sec;
    return "Date: "+get_date(t) + "\r\n";
}

const std::string HttpHeaders::generate_headers(std::map<std::string, std::string> &m) {
	std::string headers;
	headers = _status[m["status"]];
	headers += get_server();
	headers += get_server_date();
	headers += get_content_type(m["type"]);
	headers += "Content-length: " + m["length"] + "\r\n";
	if (m.find("file") != m.end())
		headers += get_last_modified(m["file"]);
	return headers;
}

const std::string &HttpHeaders::get_status(const std::string &code_status) {
	return _status[code_status];
}

const std::string HttpHeaders::get_content_length(const std::string &len) const {
	return std::string("Content-length: " + len + "\r\n");
}
