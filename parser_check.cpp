/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarbera <fbarbera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 18:32:18 by fbarbera          #+#    #+#             */
/*   Updated: 2021/03/12 12:36:16 by fbarbera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_config.hpp"

void	pars_check_name(std::vector<std::string> server_name)
{
	if (server_name.empty())
		ft_exit(NO_NAME);
}

static bool pars_check_ip_sim(std::string ip)
{
	for (int i = 0; i < ip.length(); i++)
	{
		if (ip[i] == '.' || isnumber(ip[i]))
			continue;
		else
			return true;
	}
	return false;
}
void	pars_check_ip(std::string ip)
{
	int  i = 0;
	std::string num_str;
	if (ip.length() > 16 || pars_check_ip_sim(ip))
		ft_exit(IP_ERROR);
	int number[4];
	for (int j = 0; j < 4; j++)
	{
		while (i < ip.length() && ip[i] != '.')
		{
			num_str+=ip[i];
			i++;
		}
		if (num_str.length() < 1)
			ft_exit(IP_ERROR);
		number[j] = std::stoi(num_str);
		if (number[j] >= 256 || number[j] < 0)
			ft_exit(IP_ERROR);
		i++;
		num_str.clear();
	}
}

void	pars_check_port(std::string port)
{
	if (port.empty() || port.length() > 6 || std::stoi(port) > 65535)
		ft_exit(NO_PORT);
}

static void  double_sl(std::string root)
{
	int count = 0;
	for (int i = 0; i < root.length(); i++)
	{
		if (count != 1)
			count = 0;
		if (root[i] == '/')
			count++;
		else
			count--;
		if (count == 2)
			ft_exit(DOUBLE_SL);
	}
}

void	pars_check_root(std::string &root)
{
	if (root.empty() || root == ".")
		root = "/";
	if (*root.rbegin() == '/')
		root = root.substr(0, root.size()-1);
	double_sl(root);
}

void	pars_check_max_body_size(unsigned long &size)
{
	if (size == 0)
		size = (1 << 30);
}

std::string adresscat(std::string root, std::string location)
{
	std::string str;
	str = root;
	if (*str.rbegin() == '/' && *location.begin() == '/')
		str+=my_substr(location.begin() + 1, location.end());
	else if (*str.rbegin() != '/' && *location.begin() != '/')
		str += ('/' + location);
	else
		str += location;
	return str;
}

void	adress_cat(std::string &location, std::string root)
{
	if (location.empty())
		location = "/"; //так?
	if (location == ".")
		location = "/";
	double_sl(location);
	location = adresscat(root, location);
}

void pars_check_location_root(std::string &root, std::string server_root)
{
	if (root.empty())
		root = server_root;
	pars_check_root(root);
}

void	pars_check_location_max_body_size(unsigned long &max_body_size, unsigned long server_max_body_size)
{
	if (max_body_size == 0)
		max_body_size = server_max_body_size;
}

void	pars_check_cgi(std::vector<std::string> path, std::vector<std::string> extensions)
{
	if (path.size() != extensions.size())
		ft_exit(PATH_EXTEN);
	for (int i = 0; i < extensions.size(); i++)
		if (extensions[i].length() < 2 || extensions[i][0] != '.')
			ft_exit(EXTENTION_DOT);
}


// void	pars_check_max_body_size(data[i].max_body_size);
// void	adress_cat(data[i].location[j].location);
// void	pars_check_location_root(data[i].location[j].root, data[i].root);
// void	pars_check_location_max_body_size(data[i].location[j].max_body_size, data[i].max_body_size);
// void	pars_check_location_cgi(data[i].location[i]);
// void	pars_check_location_index(data[i].location[j].index_types, data[i].index_types);
