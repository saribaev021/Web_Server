/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarbera <fbarbera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:07:29 by fbarbera          #+#    #+#             */
/*   Updated: 2021/03/08 20:09:29 by fbarbera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_CONFIG_HPP
# define PARSER_CONFIG_HPP

# include "parser_errors.hpp"

# include <iostream>
# include <vector>
# include <list>
# include <string>
# include <fstream>

typedef struct	s_locations
{
	std::string					full_loc; //мусорная строка для отлова лишнего
	std::string					location; //+
	std::string					root; //корневая папка локейшена (если нет в клнфиге заменяю на дефолтный серверный рут)
	unsigned long				max_body_size; // заменяю на серверный (если нет в кофиге)
	bool						autoindex; //+ (по дефолту off)
	std::vector<std::string>	method; //+ (если нет методов/не сущетвующий - выдаю ошибку)
	std::vector<std::string>	all_method; // + GET HEAD POST PUT // для каната
	std::vector<std::string>	cgi_extensions; // если нет, то (не знаю???? )
    std::string					cgi_path; //+ если пусто то cgi не поддерживается
    std::string					upload_storage; //+ путь куда исполнить медот PUT (если нет метода пут - ошибка?)
	std::vector<std::string>	index_types; //+ если не указано - дефолт по серверу
}				t_locations;

typedef struct	s_server_config_data
{
	std::vector<t_locations>	location;
	std::vector<std::string>	server_name; //имя сервера + ip
	std::string					ip; //+
	std::string					port; //+
    std::string					root; //+ по дефлту .
    std::vector<std::string>	error_page; //- 
	std::vector<std::string>	index_types; //+
    unsigned long				max_body_size; // - не указано (по дефолту максимальный?)
	std::string					usr;
}				t_server_config_data;

int						ft_skip_spases(std::string::iterator i);
std::string				delete_comments(std::string line);
int						found_block(std::string str, std::string::iterator i);
int						ft_spases_p(char c);
void					ft_error_p();
std::string				my_substr(std::string::iterator i, std::string::iterator end);
int 					found_last_newline(std::string::iterator i, std::string::iterator end);
std::string				my_substr(std::string::iterator i, int len);
int						found_last_location(std::string::iterator i, std::string::iterator end);
int						found_last_bracket(std::string::iterator i, std::string::iterator end);
std::string				ft_trim_spases(std::string s);
std::string::iterator	my_find(std::string &s, std::string des);
std::string 			set_string_p(std::string &str, std::string found);
std::vector<t_locations> split_locations(std::string &str);
unsigned long long 		set_size(std::string str);
std::vector<std::string> set_vector(std::string &str, std::string found);
t_server_config_data	pars_data_for_servers(std::string str);
void	pars_check_name(std::vector<std::string> &server_name);
std::vector<std::string> set_error_page(std::string &str, std::string found);

#endif