/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassGenErrorPage.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarbera <login@student.21-school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 20:07:20 by fbarbera          #+#    #+#             */
/*   Updated: 2021/03/11 20:08:42 by fbarbera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClassGenErrorPage.hpp"

std::string ClassGenErrorPage::generate(int error)
{
	return (s1 + std::to_string(error) + s2);
}

std::string ClassGenErrorPage::generate(std::string error)
{
	return (s1 + error + s2);
}