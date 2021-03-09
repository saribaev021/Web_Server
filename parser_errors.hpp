/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarbera <login@student.21-school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:24:12 by fbarbera          #+#    #+#             */
/*   Updated: 2021/03/09 23:01:31 by fbarbera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_ERRORS_HPP
# define PARSER_ERRORS_HPP

# include "string"

# define ERROR_TOKEN 1
# define NO_METHOD 2
# define UN_METHOD 3
# define IP_ERROR 4
# define NO_NAME 5
# define NO_PORT 6
# define DOUBLE_SL 7
# define NO_LOCATION 8

void	ft_exit(int error);
void	ft_exit(int error, std::string::iterator i);

#endif