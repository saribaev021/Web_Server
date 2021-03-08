/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarbera <fbarbera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:40:54 by fbarbera          #+#    #+#             */
/*   Updated: 2021/03/08 18:12:52 by fbarbera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClassParser.hpp"

std::vector<t_server_config_data>		parser_config(void)
{
	ClassParser	p;

	p.fing_config_file(); // поиск конфига
	p.read_from_file(); // чтение конфига
	p.pars_data(); // разбитие на токены
	p.set_default_values(); // установка значений (дефолтные/по серверу)
	return (p.get_data());
}

int main()
{
    std::vector<t_server_config_data> p = parser_config();
	int i = 0;
	int j;
	int k;
	while (i < p.size())
	{
		j = 0;
		std::cout << "_________serv___________"  << std::endl;
		for (k = 0; k < p[i].server_name.size(); k++)
			std::cout << p[i].server_name[k] << std::endl;
		std::cout << p[i].ip << std::endl;
		std::cout << p[i].port << std::endl;
		std::cout << p[i].root << std::endl;
		for (k = 0; k < p[i].index_types.size(); k++)
			std::cout << p[i].index_types[k] << std::endl;
		while (j < p[i].location.size())
		{	
			std::cout << "_________loc___________"  << std::endl;
			std::cout << p[i].location[j].location << std::endl;
			std::cout << p[i].location[j].root << std::endl;
			std::cout << p[i].location[j].max_body_size << std::endl;
			std::cout << p[i].location[j].autoindex << std::endl;
			for (k = 0; k < p[i].location[j].method.size(); k++)
				std::cout << p[i].location[j].method[k] << std::endl;
			for (k = 0; k < p[i].location[j].cgi_extensions.size(); k++)
				std::cout << p[i].location[j].cgi_extensions[k] << std::endl;
			std::cout << p[i].location[j].cgi_path << std::endl;
			std::cout << p[i].location[j].upload_storage << std::endl;			
			for (k = 0; k < p[i].location[j].index_types.size(); k++)
				std::cout << p[i].location[j].index_types[k] << std::endl;
			std::cout << "____________________" << std::endl;
			j++;
		}
		i++;
	}
	return 0;
}