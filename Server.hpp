//
// Created by Kanat Saribaew on 3/5/21.
//
#pragma once
enum STATUS{
	CLOSE,
	ERROR,
	READ,
	PARSER,
	WRITE,
	EXECUTE
};
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <list>
#include "Http.hpp"
#include "RequestParser.hpp"



//class Http;
//class RequestParser;