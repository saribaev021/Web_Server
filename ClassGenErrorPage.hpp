/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassGenErrorPage.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarbera <fbarbera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 19:38:39 by fbarbera          #+#    #+#             */
/*   Updated: 2021/03/13 18:20:03 by fbarbera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASSGENERRORPAGE_HPP
# define CLASSGENERRORPAGE_HPP

# include "parser_config.hpp"

class ClassGenErrorPage
{
private:
	std::string s1 = "<html><head><title>ERROR PAGE</title></head><body><br /><br /><br /><p align=\"center\" style=\"color:#ff4444;font-size:80px\"> <b>ERROR ";
	std::string s2 = ".</b></p></body></html>";
	s_server_config_data data;
	int found_error(int error, std::string &error_page);
	ClassGenErrorPage();
public:
	ClassGenErrorPage(s_server_config_data data);
	~ClassGenErrorPage();
	std::string generate(int error);
	std::string generate(std::string error);
};

# endif