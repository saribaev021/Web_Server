/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarbera <login@student.21-school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:23:42 by fbarbera          #+#    #+#             */
/*   Updated: 2021/03/14 21:22:33 by fbarbera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_errors.hpp"
# include <iostream>

void ft_exit(int error)
{
	std::cout << "Config error:" << std::endl;
	switch (error)
	{
	case NO_METHOD:
		std::cout << "no method" << std::endl;				break;
	case UN_METHOD:
		std::cout << "unknown method" << std::endl;			break;
	case IP_ERROR:
		std::cout << "ip error" << std::endl;				break;
	case NO_NAME:
		std::cout << "No name =(" << std::endl;				break;
	case NO_PORT:
		std::cout << "unknown port" << std::endl;			break;
	case DOUBLE_SL:
		std::cout << "Double '/'" << std::endl;				break;
	case NO_LOCATION:
		std::cout << "No location" << std::endl;			break;
	case MAX_SIZE_ERROR:
		std::cout << "No valid max_body_size" << std::endl;	break;
	case NO_BRAKET:
		std::cout << "Braket errors" << std::endl;			break;
	case ERROR_PAGE_ERROR:
		std::cout << "Unknown argument in error_page"
										<< std::endl;		break;
	case PATH_EXTEN:
		std::cout << "The number of paths is not equal to the number of extensions"
										<< std::endl;		break;
	case EXTENTION_DOT:
		std::cout << "Еhe extension must start with a dot"
										<< std::endl;		break;
	case NO_VALID_AUTH_FILE:
		std::cout << "auth_file must me\nAuthType Basic\nlogin:password"
										<< std::endl;		break;
	case UNICUE_IP:
		std::cout << "IP+PORT not unicue" << std::endl;		break;
	default:
		std::cout << "Error unknown error\n";				break;
	}
	exit(1);
}

void ft_exit(int error, std::string s)
{
	std::cout << "Config error:" << std::endl;
	switch (error)
	{
	case AUTH_PATH:
		std::cout << "Error file ot path:\n";
		std::cout << s << std::endl; break;
	default:
		std::cout << "Error unknown error\n";			break;
	}
	exit(1);
}

void ft_exit(int error, std::string::iterator i)
{
	std::cout << "Config error:" << std::endl;
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