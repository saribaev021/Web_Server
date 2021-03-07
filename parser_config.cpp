/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarbera <fbarbera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:40:54 by fbarbera          #+#    #+#             */
/*   Updated: 2021/03/05 18:45:22 by fbarbera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClassParser.hpp"


std::vector<t_server_config_data>		parser_config(void)
{
	ClassParser	p;

	p.fing_config_file();
	p.read_from_file();
	p.pars_data();
	return (p.data);
}
 
int main()
{
    std::vector<t_server_config_data> p = parser_config();
	std::cout << p[0].port << std::endl;
    return 0;
}