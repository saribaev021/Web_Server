/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_auto_page.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarbera <fbarbera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 13:35:00 by fbarbera          #+#    #+#             */
/*   Updated: 2021/03/12 15:55:04 by fbarbera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_config.hpp"
#include "system_include.hpp"

int count_dir(std::string str)
{
	int num = 0;
	for (int i = 0; i < str.length(); i++)
		if (str[i] == '/')
			num++;
	return num;
}

std::string gen_auto_page(std::string path, std::string location)
{
	std::string head1 = "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=windows-1252\"><title>Index of ";
	std::string head2 = "</title></head><body bgcolor=\"white\"><h1>Index of ";
	std::string head3 = "</h1><hr><pre>";
	std::string head = head1 + location + head2 + location + head3;
	std::string tail = "</pre><hr></body></html>";
	std::string body;
	int fd;
	DIR *dir;
	struct dirent	*entry;
	std::string full_path = path;
	add_first_slash(location);
	add_last_slash(location);
	dir = opendir(path.c_str());
	while (dir && (entry = readdir(dir)) != nullptr)
	{
		if (std::string(entry->d_name) == ".")
			continue ;
		int n = body.length();
		if (std::string(entry->d_name) == ".." && count_dir(location) == 1)
			body += "<a href=\"/\">../</a>";
		else
		{
			if (entry->d_type == DT_DIR)
				body += "<a href=\"" + std::string(entry->d_name) + "/\">" + std::string(entry->d_name) + "/</a>";
			else	
				body += "<a href=\"" + std::string(entry->d_name) + "\">" + std::string(entry->d_name) + "</a>";
		}
		// _____trash?
		int sp = body.length() - n - std::string(entry->d_name).length();
		while (sp < 80)
		{
			body += " ";
			sp++;
		}
		if (entry->d_type == DT_DIR)
			body+=" -\n";
		else
			body+="0\n";
		// _____trash?
		
	}
	if (dir){
		closedir(dir);
	}
	return head+body+tail;
}

// <a href="pwd.html">pwd.html</a>