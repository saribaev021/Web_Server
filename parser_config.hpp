/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarbera <fbarbera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:07:29 by fbarbera          #+#    #+#             */
/*   Updated: 2021/03/05 22:00:36 by fbarbera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_CONFIG_HPP
# define PARSER_CONFIG_HPP

# include <iostream>
# include <vector>
# include <list>
# include <string>
# include <fstream>

typedef struct	s_locations
{
	std::string					full_loc;
	std::string					location; //+
	std::string					root; //+
	unsigned long				max_body_size;
	bool						autoindex; //+
	std::vector<std::string>	method; //+
	std::vector<std::string>	all_method; // + GET HEAD POST PUT
	std::vector<std::string>	cgi_extensions; //+
    std::string					cgi_path; //+ если пусто то cgi не поддерживается
    std::string					upload_storage; //+
	std::vector<std::string>	index_types; //+
}				t_locations;

typedef struct	s_server_config_data
{
	std::vector<t_locations>	location;
	std::vector<std::string>	server_name; //имя сервера + ip
	std::string					ip; //+
	std::string					port; //+
    std::string					root; //+
    std::vector<std::string>	error_page;
	std::vector<std::string>	index_types; //+
    unsigned long				max_body_size;
	std::string					usr;
}				t_server_config_data;

int		ft_skip_spases(std::string::iterator i);
std::string		delete_comments(std::string line);
int		found_block(std::string str, std::string::iterator i);
int		ft_spases_p(char c);
void	ft_error_p();
std::string		my_substr(std::string::iterator i, std::string::iterator end);
int found_last_newline(std::string::iterator i, std::string::iterator end);
std::string		my_substr(std::string::iterator i, int len);
int				found_last_location(std::string::iterator i, std::string::iterator end);
int				found_last_bracket(std::string::iterator i, std::string::iterator end);
std::string	ft_trim_spases(std::string s);
std::string::iterator my_find(std::string &s, std::string des);
#endif