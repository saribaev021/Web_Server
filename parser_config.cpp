/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarbera <fbarbera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:40:54 by fbarbera          #+#    #+#             */
/*   Updated: 2021/03/12 17:34:42 by fbarbera         ###   ########.fr       */
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
 
 #include <sys/time.h>


std::string Get_local_time()
{
	struct timeval tv;
	time_t t;
	struct tm info;
	char buffer[64];

	gettimeofday(&tv, NULL);
	t = tv.tv_sec;
	std::string s = std::to_string(t);
	strptime(s.c_str(), " %s ", &info);
	strftime (buffer, sizeof(buffer), "%a, %d %b %Y %X %Z", &info);
	std::string str = buffer;
	return str;
}


int main()
{
	std::vector<t_server_config_data> p = parser_config();
	int i = 0;
	int j;
	int k;

	std::cout << Get_local_time() << std::endl;
	// std::cout << gen_auto_page(std::string("/Users/fbarbera/21/"), std::string("21/")) << std::endl;
	// while (i < p.size())
	// {
	// 	j = 0;
	// 	std::cout << "_________serv___________"  << std::endl;
	// 	for (k = 0; k < p[i].server_name.size(); k++)
	// 		std::cout << p[i].server_name[k] << "\t\t\t server_name" << std::endl;
	// 	std::cout << p[i].ip << "\t\t\t ip" << std::endl;
	// 	std::cout << p[i].port << "\t\t\t\t port"<< std::endl;
	// 	std::cout << p[i].root << "\t\t\t root" << std::endl;
	// 	std::cout << p[i].max_body_size << "\t\t max_size"<< std::endl;
	// 	for (k = 0; k < p[i].index_types.size(); k++)
	// 		std::cout << p[i].index_types[k] << "\t\t\t index" << std::endl;
	// 	for(std::map<int, std::string>::iterator it = p[i].error_page.begin(); it != p[i].error_page.end(); ++it)
	// 	{
	// 		std::cout << it->first << " : " << it->second << std::endl;///вывод на экран
	// 	}
	// 	while (j < p[i].location.size())
	// 	{	
	// 		std::cout << "_________loc___________" << j  << std::endl;
	// 		std::cout << p[i].location[j].location << "\t\t\t location" << std::endl;
	// 		std::cout << p[i].location[j].root << "\t\t\t root" << std::endl;
	// 		std::cout << p[i].location[j].autoindex << "\t\t\t autoindex"<< std::endl;
	// 		for (k = 0; k < p[i].location[j].method.size(); k++) 
	// 			std::cout << p[i].location[j].method[k] << "\t\t\t method "<< std::endl;
	// 		for (k = 0; k < p[i].location[j].cgi_extensions.size(); k++)
	// 			std::cout << p[i].location[j].cgi_path[k] << " : " << p[i].location[j].cgi_extensions[k] << "\t\t cji"<< std::endl;
	// 		std::cout << p[i].location[j].upload_storage << "\t\t\t storage"<< std::endl;
	// 		j++;
	// 	}
	// 	i++;
	// }
	return 0;
}