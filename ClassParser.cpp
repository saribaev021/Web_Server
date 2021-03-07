/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassParser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarbera <fbarbera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:58:29 by fbarbera          #+#    #+#             */
/*   Updated: 2021/03/05 18:37:39 by fbarbera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClassParser.hpp"

void	ClassParser::fing_config_file()
{
	if (0) //error
		exit(1);
	this->config_addr = "/Users/ndreadno/web_server/webserv.conf";
}

void ClassParser::read_from_file()
{	
	std::string line;
 
    std::ifstream in(config_addr); // окрываем файл для чтения
    if (in.is_open())
    {
        while (getline(in, line))
			this->line_data = line_data + "\n" + delete_comments(line);
    }
	else
	{
		//std::cout << "error open" << std::endl; //error
		exit(1);
	}
    in.close();     // закрываем файл
	//std::cout << this->line_data << std::endl;
}

std::vector<std::string> ClassParser::split_servers()
{
	std::string::iterator i;
	std::string::iterator end;
	std::vector<std::string> lines_for_server;
	int		len_of_one_server;
	i = line_data.begin();
	end = line_data.end();
	i += ft_skip_spases(i);
	while (i != line_data.end())
	{
		if (found_block("server ", i) == 1)
		{
			len_of_one_server = found_last_bracket(i, end);
			lines_for_server.push_back(my_substr(i, len_of_one_server));
			i+=len_of_one_server;
		}
		else if (*i == ' ' || *i == '\n' || *i == '\t')
			i++;
		else
			ft_error_p();
	}
	return lines_for_server;
}

std::vector<std::string> set_vector(std::string &str, std::string found)
{
	std::vector<std::string> names;
	std::string s_line;
	std::string::iterator i;
	std::string::iterator end;
	int		len_of_one_server;
	i = str.begin();
	end = str.end();
	i += ft_skip_spases(i);
	while (i != str.end())
	{
		if (found_block(found, i) == 1)
		{
			len_of_one_server = found_last_newline(i, end);
			s_line = my_substr(i, len_of_one_server);
			str = my_substr(str.begin(), i) + my_substr(i + len_of_one_server, end);
			end = str.end();
			i++;
			names.push_back(s_line);
		}
		else
			i++;
	}
	return names;
}

std::string set_string_p(std::string &str, std::string found)
{
	std::string s_line;
	std::string::iterator i;
	std::string::iterator end;
	int		len_of_one_server;
	i = str.begin();
	end = str.end();
	i += ft_skip_spases(i);
	while (i != str.end())
	{
		if (found_block(found, i) == 1)
		{
			len_of_one_server = found_last_newline(i, end);
			s_line = my_substr(i, len_of_one_server);
			str = my_substr(str.begin(), i) + my_substr(i + len_of_one_server, end);
			end = str.end();
			i++;
		}
		else
			i++;
	}
	return s_line;
}

std::vector<t_locations> split_locations(std::string &str)
{
	std::string::iterator i;
	std::string::iterator end;
	std::vector<t_locations> loc;
	t_locations all;
	int		len_of_one_server;
	i = str.begin();
	end = str.end();
	i += ft_skip_spases(i);
	while (i != end)
	{
		if (found_block("location ", i) == 1)
		{
			len_of_one_server = found_last_location(i, end);
			all.full_loc = (my_substr(i, len_of_one_server));
			loc.push_back(all);
			str = my_substr(str.begin(), i) + my_substr(i + len_of_one_server, end);
			end = str.end();
			i++;
		}
		else
			i++;
	}
	return loc;
}

unsigned long set_size(std::string str)
{
	if (str.empty())
		return 0;
	std::string s = my_substr(str.begin() + 14, str.end());
	return 10;
}

bool set_auto(std::string str)
{
	if (str.length() < 1)
		return (false);
	size_t pos = str.find("on");
	if (pos != std::string::npos)
		return (true);
	return (false);
}

std::vector<std::string>	split_vector(std::string s, std::string type)
{
	std::vector<std::string> split;
	// //std::cout << s << std::endl;
	if (s.empty())
		return split;
	std::string str = my_substr(s.begin() + type.length(), s.end());
	std::string new_str;
	std::string::iterator i = str.begin();
	int n;
	while (i != str.end())
	{
		if (ft_spases_p(*i))
			i++;
		else
		{
			std::string new_str;
			while (ft_spases_p(*i) == 0 && i != str.end())
			{
				new_str += *i;
				i++;
			}
//			//std::cout << type << " - " <<  new_str <<std::endl;
			split.push_back(new_str);
		}
	}
	return (split);
	
}

std::string		split_string(std::string s, std::string type)
{
	if (s.empty())
		return "";
	std::string str = my_substr(s.begin() + type.length(), s.end());
//	//std::cout << type << " - " << str << std::endl;
	return (str);
}

std::string		set_port(std::string s)
{
	std::string::reverse_iterator i = s.rbegin();
	std::string::reverse_iterator end = s.rend();
	std::string port;
	while (i != end && isalnum(*i))
	{
		port+= *i;
		i++;
	}
	if (port.empty())
		return "";
	std::string new_port;
	for(int n = port.length()-1; n >= 0; n--)
    	new_port.push_back(port[n]);
//	//std::cout << "port - "<< new_port << std::endl;
	return (new_port);
}

std::string set_ip(std::string s)
{
	if (s.empty())
		exit(1);
	std::string::iterator i = s.begin();
	std::string ip;
	while (i != s.end() && *i != ':')
	{
		ip+=*i;
		i++;
	}
//	//std::cout << "ip - "<< ip << std::endl;
	return  ip;
}

void iset_data(t_server_config_data &s)
{
	s.server_name = split_vector(s.server_name[0], "server_name ");
	if (!s.index_types.empty())
		s.index_types = split_vector(s.index_types[0], "index ");
	s.root = split_string(s.root, "root ");
	if (s.ip.empty())
		exit(1);
	std::string copy = s.ip;
	s.ip = set_ip(split_string(copy, "listen "));
	s.port = set_port(copy);
	s.server_name.push_back(s.ip);
	int j = 0;
	while (j < s.location.size())
	{
		// s.location[j].location = set_string_p(s.location[j].full_loc, "location ");
		//std::cout << "loc # " << j << "\n{" << std::endl;
		if (s.location[j].root.empty())
			s.location[j].root = s.root;
		else
			s.location[j].root = s.root + split_string(s.location[j].root, "root ");
		if (s.location[j].index_types.empty())
			s.location[j].index_types = s.index_types;
		else
			s.location[j].index_types = split_vector(s.location[j].index_types[0], "index ");
		//std::cout << "autoindex - "<< s.location[j].autoindex << std::endl;
		//std::cout << "max_body_size - "<< s.location[j].max_body_size << std::endl;
		// s.location[j].method = set_vector(s.location[j].full_loc, "method ");
		if (s.location[j].cgi_path.empty())
			s.location[j].cgi_path = "";
		else
			s.location[j].cgi_path = s.location[j].root + '/' + split_string(s.location[j].cgi_path, "cgi_path ");
// s.location[j].cgi_extensions = set_vector(s.location[j].full_loc, "cgi_extensions ");

		if (!s.location[j].cgi_extensions.empty())
			s.location[j].cgi_extensions = split_vector(s.location[j].cgi_extensions[0], "cgi_extensions ");
		
		if (s.location[j].upload_storage.empty())
			s.location[j].upload_storage = "";
		else
			s.location[j].upload_storage = split_string(s.location[j].upload_storage, "cgi_path ");

		// s.location[j].upload_storage = set_string_p(s.location[j].full_loc, "upload_storage ");
		//std::cout << "}\n";
		j++;
	}
	// for (int i = 0; i < s.index_types.size(); i++)
	// 	//std::cout << s.index_types[i] << std::endl;
}

t_server_config_data	pars_data_for_servers(std::string str)
{
	t_server_config_data s;
	s.location = split_locations(str);
	int j = 0;
	while (j < s.location.size())
	{
		s.location[j].location = set_string_p(s.location[j].full_loc, "location ");
		s.location[j].root = set_string_p(s.location[j].full_loc, "root ");
		s.location[j].autoindex = set_auto(set_string_p(s.location[j].full_loc, "autoindex "));
		s.location[j].index_types = set_vector(s.location[j].full_loc, "index ");
		s.location[j].method = set_vector(s.location[j].full_loc, "method ");
		s.location[j].max_body_size = set_size(set_string_p(s.location[j].full_loc, "max_body_size "));
		s.location[j].cgi_extensions = set_vector(s.location[j].full_loc, "cgi_extensions ");
		s.location[j].cgi_path = set_string_p(s.location[j].full_loc, "cgi_path ");
		s.location[j].upload_storage = set_string_p(s.location[j].full_loc, "upload_storage ");
		j++;
	}
	s.server_name = set_vector(str, "server_name ");
	s.index_types = set_vector(str, "index ");
	s.root = set_string_p(str, "root ");
	s.ip = set_string_p(str, "listen ");
	s.usr = set_string_p(str, "usr ");
	s.error_page = set_vector(str, "error_page ");
	s.max_body_size = set_size(set_string_p(str, "max_body_size "));
	iset_data(s);
	return s;
}

void	ClassParser::pars_data()
{
//	//std::cout << "___________________________" << std::endl;
	std::vector<std::string> lines_for_server = split_servers();
	int j = 0;
	while (j < lines_for_server.size())
	{
//		//std::cout << "___________________________ server #" << j << std::endl;
		this->data.push_back(pars_data_for_servers(lines_for_server[j]));
		j++;
	}
}