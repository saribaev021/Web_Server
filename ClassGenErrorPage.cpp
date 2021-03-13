/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassGenErrorPage.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarbera <fbarbera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 20:07:20 by fbarbera          #+#    #+#             */
/*   Updated: 2021/03/13 18:24:11 by fbarbera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClassGenErrorPage.hpp"

int ClassGenErrorPage::found_error(int error, std::string &error_page)
{
	error_page = data.error_page[error];
	if (!error_page.empty())
		return 1;
	return 0;
}

std::string ClassGenErrorPage::generate(int error)
{
	std::string error_page;
	
	if (found_error(error, error_page) == 1)
		return error_page;
	return (s1 + std::to_string(error) + s2);
}

std::string ClassGenErrorPage::generate(std::string error)
{
	return (s1 + error + s2);
}

ClassGenErrorPage::ClassGenErrorPage(s_server_config_data data) : data(data)
{
}

ClassGenErrorPage::~ClassGenErrorPage()
{
}