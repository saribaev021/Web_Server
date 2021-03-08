/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarbera <fbarbera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:24:12 by fbarbera          #+#    #+#             */
/*   Updated: 2021/03/08 20:06:15 by fbarbera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_ERRORS_HPP
# define PARSER_ERRORS_HPP

# include "string"

# define ERROR_TOKEN 1
# define NO_METHOD 2
# define UN_METHOD 3
# define IP_ERROR 4

void	ft_exit(int error);
void ft_exit(int error, std::string::iterator i);

#endif