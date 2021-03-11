/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassGenErrorPage.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarbera <login@student.21-school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 19:38:39 by fbarbera          #+#    #+#             */
/*   Updated: 2021/03/11 20:05:40 by fbarbera         ###   ########.fr       */
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
public:
	ClassGenErrorPage();
	std::string generate(int error);
	std::string generate(std::string error);
	~ClassGenErrorPage();
};

ClassGenErrorPage::ClassGenErrorPage(/* args */)
{
}

ClassGenErrorPage::~ClassGenErrorPage()
{
}


# endif