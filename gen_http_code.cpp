/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_http_code.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarbera <fbarbera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 20:18:33 by fbarbera          #+#    #+#             */
/*   Updated: 2021/03/13 20:28:44 by fbarbera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system_include.hpp"
#include "parser_config.hpp"

std::map<std::string, std::string> gen_http_code()
{
	std::string s1("100 101 102 103 200 201 202 203 204 205 206 300 301 302 303 304 305 306 307 308 400 401 402 403 404 405 406 407 408 409 410 411 412 413 414 415 416 417 500 501 502 503 504 505 ");
	std::string s2("Continue\nSwitching Protocol\nProcessing\nEarly Hints\nOK\nCreated\nAccepted\nNon-Authoritative Information\nNo Content\nReset Content\nPartial Content\nMultiple Choice\nMoved Permanently\nFound\nSee Other\nNot Modified\nUse Proxy\nSwitch Proxy\nTemporary Redirect\nPermanent Redirect\nBad Request\nUnauthorized\nPayment Required\nForbidden\nNot Found\nMethod Not Allowed\nNot Acceptable\nProxy Authentication Required\nRequest Timeout\nConflict\nGone\nLength Required\nPrecondition Failed\nRequest Entity Too Large\nRequest-URI Too Long\nUnsupported Media Type\nRequested Range Not Satisfiable\nExpectation Failed\nInternal Server Error\nNot Implemented\nBad Gateway\nService Unavailable\nGateway Timeout\nHTTP Version Not Supported\n");
	std::vector<std::string> v1 = ft_split_string_to_vector(s1, ' ');
	std::vector<std::string> v2 = ft_split_string_to_vector(s2, '\n');
	std::map<std::string, std::string> m;
	for (int i = 0; i < v2.size(); i++)
	{
		v2[i] = "HTTP/1.1 " + v1[i] + " " + v2[i] + "\r\n";
		m.insert(std::pair<std::string, std::string>(v1[i], v2[i]));
	}
	return m;
}
//"HTTP/1.1 404 Not Found\r\n";