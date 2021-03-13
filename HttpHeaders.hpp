//
// Created by Kanat Saribaew on 3/12/21.
//

#ifndef HTTPHEADERS_HPP
#define HTTPHEADERS_HPP
#include "system_include.hpp"

class HttpHeaders {
private:
	std::map<std::string, std::string> _mime_types;
	std::map<std::string, std::string> _status;
	const std::string get_date(time_t t) const;
public:
	HttpHeaders(const std::map<std::string, std::string>&);
	const std::string &get_status(const std::string &);
	const std::string get_server() const;
	const std::string get_server_date() const;
	const std::string get_content_type(const std::string &) const;
	const std::string get_content_length(const std::string &) const;
	const std::string get_last_modified(const std::string &);
	const std::string generate_headers(std::map<std::string, std::string> &m);
};



#endif //HTTPHEADERS_HPP
