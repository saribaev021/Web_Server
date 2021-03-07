/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassParser.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarbera <fbarbera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:58:47 by fbarbera          #+#    #+#             */
/*   Updated: 2021/03/05 18:44:16 by fbarbera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASSPARSER_HPP
# define  CLASSPARSER_HPP

#include "parser_config.hpp"

class ClassParser
{
private:
	std::string	config_addr;
	std::string	line_data;
	std::vector<std::string> split_servers();
public:
	std::vector<t_server_config_data> data;
	void	pars_data();
	void	fing_config_file();
	void	read_from_file();
};

#endif