/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarbera <fbarbera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:23:42 by fbarbera          #+#    #+#             */
/*   Updated: 2021/03/08 20:07:10 by fbarbera         ###   ########.fr       */
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
		std::cout << "listen ip error" << std::endl;	break;
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