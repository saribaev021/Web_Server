/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarbera <login@student.21-school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:23:42 by fbarbera          #+#    #+#             */
/*   Updated: 2021/03/09 23:03:23 by fbarbera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_errors.hpp"
# include <iostream>

void ft_exit(int error)
{
	switch (error)
	{
	case NO_METHOD:
		std::cout << "no method" << std::endl;			break;
	case UN_METHOD:
		std::cout << "unknown method" << std::endl;		break;
	case IP_ERROR:
		std::cout << "ip error" << std::endl;			break;
	case NO_NAME:
		std::cout << "No name =(" << std::endl;			break;
	case NO_PORT:
		std::cout << "unknown port" << std::endl;		break;
	case DOUBLE_SL:
		std::cout << "Double '/'" << std::endl;			break;
	case NO_LOCATION:
		std::cout << "No location" << std::endl;		break;
	default:
		std::cout << "Error unknown error\n";			break;
	}
	exit(1);
}
void ft_exit(int error, std::string::iterator i)
{
	switch (error)
	{
	case ERROR_TOKEN:
		std::cout << "Error line:\n";
		while (*i!='\n')
		{
			std::cout << *i;
			i++;
		}
		std::cout << std::endl; break;
	default:
		std::cout << "Error unknown error\n";			break;
	}
	exit(1);
}