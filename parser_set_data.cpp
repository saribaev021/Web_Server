/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_set_data.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarbera <login@student.21-school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:07:07 by fbarbera          #+#    #+#             */
/*   Updated: 2021/03/09 22:21:06 by fbarbera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_config.hpp"

std::string::iterator	&check_error_token(std::string::iterator &s, std::string::iterator end)
{
	while (s != end)
	{
		if (ft_spases_p(*s) || *s == '{'|| *s == '}')
			s++;
		else
			return s;
	}
	return s;
}


static bool set_auto(std::string str)
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
	return ft_trim_spases(str);
}

static std::string		set_port(std::string s)
{
	std::string::reverse_iterator i = s.rbegin();
	std::string::reverse_iterator end = s.rend();
	std::string port;
	while (i != end && ft_spases_p(*i))
		i++;
	while (i != end && isnumber(*i))
	{
		port+= *i;
		i++;
	}
	if (*i != ':')
		ft_exit(NO_PORT);
	if (port.empty())
		return "";
	std::string new_port;
	for(int n = port.length()-1; n >= 0; n--)
    	new_port.push_back(port[n]);
	return ft_trim_spases(new_port);
}

static std::string set_ip(std::string s)
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
	if (i == s.end())
		ft_exit(IP_ERROR);
	return  ip;
}

static std::vector<std::string>	set_all_method()
{
	std::vector<std::string> a;
	a.push_back("GET");
	a.push_back("HEAD");
	a.push_back("POST");
	a.push_back("PUT");
	return a;
}

static bool	check_method_pars(std::vector<std::string> method, std::vector<std::string> all_method)
{
	bool a;
	for (int i = 0; i < method.size(); i++)
	{
		a = false;
		for (int j = 0; j < all_method.size(); j++)
			if (all_method[j] == method[i])
				a = true;
		if (a == false)
			return false;
	}
	return a;
}

std::string set_loc(std::string s)
{
	std::string str;
	str = my_substr(s.begin(), my_find(s,"{"));
	str = ft_trim_spases(str);
	return str;
}

static void iset_data(t_server_config_data &s)
{
	if (s.server_name.empty())
		;
	else s.server_name = split_vector(s.server_name[0], "server_name ");
	if (!s.index_types.empty())
		s.index_types = split_vector(s.index_types[0], "index ");
	s.root = (split_string(s.root, "root "));
	if (s.ip.empty())
		ft_exit(IP_ERROR);
	std::string copy = s.ip;
	s.ip = ft_trim_spases(set_ip(split_string(copy, "listen ")));
	s.port = set_port(copy);
	s.server_name.push_back(s.ip);
	int j = 0;
	while (j < s.location.size())
	{
		s.location[j].location = set_loc(split_string(s.location[j].location, "location "));
		if (s.location[j].root.empty())
			s.location[j].root = s.root;
		else
			s.location[j].root = s.root + '/' + split_string(s.location[j].root, "root ");
		if (s.location[j].index_types.empty())
			s.location[j].index_types = s.index_types;
		else
			s.location[j].index_types = split_vector(s.location[j].index_types[0], "index ");
		s.location[j].all_method = set_all_method();
		if (s.location[j].method.empty())
			ft_exit(NO_METHOD);
		else
			s.location[j].method = split_vector(s.location[j].method[0], "method ");
		if (check_method_pars(s.location[j].method, s.location[j].all_method) == false)
			ft_exit(UN_METHOD);
		if (s.location[j].cgi_path.empty())
			s.location[j].cgi_path = "";
		else
			s.location[j].cgi_path = s.location[j].root + '/' + split_string(s.location[j].cgi_path, "cgi_path ");

		if (!s.location[j].cgi_extensions.empty())
			s.location[j].cgi_extensions = split_vector(s.location[j].cgi_extensions[0], "cgi_extensions ");
		
		if (s.location[j].upload_storage.empty())
			s.location[j].upload_storage = "";
		else
			s.location[j].upload_storage = split_string(s.location[j].upload_storage, "upload_storage ");
		j++;
	}
}

t_server_config_data	pars_data_for_servers(std::string str)
{
	t_server_config_data s;
	std::string::iterator iterator;
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
		iterator = s.location[j].full_loc.begin() + 7;
		if (check_error_token(iterator, s.location[j].full_loc.end()) != s.location[j].full_loc.end())
			ft_exit(ERROR_TOKEN, iterator);
		j++;
	}
	s.server_name = set_vector(str, "server_name ");
	s.index_types = set_vector(str, "index ");
	s.root = set_string_p(str, "root ");
	s.ip = set_string_p(str, "listen ");
	s.usr = set_string_p(str, "usr ");
	s.error_page = set_error_page(str, "error_page ");
	s.max_body_size = set_size(set_string_p(str, "max_body_size "));
	iterator = str.begin() + 7;
	if (check_error_token(iterator, str.end()) != str.end())
		ft_exit(ERROR_TOKEN, iterator);
	iset_data(s);
	return s;
}