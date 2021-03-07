/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarbera <fbarbera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:14:33 by fbarbera          #+#    #+#             */
/*   Updated: 2021/03/03 20:18:42 by fbarbera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_config.hpp"

int		ft_skip_spases(std::string::iterator i)
{
	int num = 0;
	while (*i == ' ' || *i == '\t' || *i == '\n')
	{
		num++;
		i++;
	}
	return num;
}

std::string		delete_comments(std::string line)
{
	return line.substr(0, line.find('#'));
}

int		found_block(std::string str, std::string::iterator i)
{
	int j;
	j = 0;
	while (j < str.size())
	{
		if (str[j] != *i)
			return 0;
		j++;
		i++;
	}
	return (1);
}

int		ft_spases_p(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return 1;
	return 0;
}

void	ft_error_p()
{
	std::cout << "ERROR" << std::endl;
	exit(1);
}


int				found_last_bracket(std::string::iterator i, std::string::iterator end)
{
	int num = 0;
	int count = 0;
	i+=6;
	num+=6;
	while (i != end && *i != '{')
	{
		if (ft_spases_p(*i))
		{
			i++;
			num++;
		}
		else 
			ft_error_p();
	}
	if (i == end)
		return (-1);
	count++;
	i++;
	num++;
	while (i != end && count != 0)
	{
		if (*i == '}')
			count--;
		if (*i == '{')
			count++;
		i++;
		num++;
	}
	if (count == 0)
		return num;
	else
		return (-1);
}

int				found_last_location(std::string::iterator i, std::string::iterator end)
{
	int num = 0;
	int count = 0;
	int word = 0;
	i+=8;
	num+=8;
	while (i != end && *i != '{')
	{
		if (ft_spases_p(*i))
		{
			i++;
			num++;
		}
		else if (word == 1) 
			ft_error_p();
		else
		{
			while (ft_spases_p(*i) == 0)
			{
				i++;
				num++;
			}
			word++;
		}
	}
	if (i == end)
		return (-1);
	count++;
	i++;
	num++;
	while (i != end && count != 0)
	{
		if (*i == '}')
			count--;
		if (*i == '{')
			count++;
		i++;
		num++;
	}
	if (count == 0)
		return num;
	else
		return (-1);
}

std::string		my_substr(std::string::iterator i, int len)
{
	std::string str;
	int n=0;

	while (n < len)
	{
		str += *i;
		i++;
		n++;
	}
	return str;
}

std::string		my_substr(std::string::iterator i, std::string::iterator end)
{
	std::string str;

	while (i != end)
	{
		str += *i;
		i++;
	}
	return str;
}

int found_last_newline(std::string::iterator i, std::string::iterator end)
{
	int num;
	num = 0;
	while (i != end && *i != '\n')
	{
		num++;
		i++;
	}
	return num;
}