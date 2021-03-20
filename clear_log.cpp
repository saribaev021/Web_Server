//
// Created by Kanat Saribaew on 3/20/21.
//
#include "system_include.hpp"
#include <fstream>
int main(){
	std::ifstream in("request.log");
	std::ifstream in2("response.log");
	std::ofstream out("request2.txt");
	std::ofstream out2("response.txt");
	std::string line;
	std::string str;
	size_t pos;
	size_t pos2;
	size_t pos3;
	size_t pos4;
	if (in.is_open()) {
		while (!in.eof()) {
			getline(in, line);
			pos = line.find("eeee");
			pos2 = line.find("xxx");
			pos3 = line.find("bbbb");
			pos4 = line.find("8000");
			if (pos != std::string::npos || pos2 != std::string::npos || pos3 != std::string::npos ||
				pos4 != std::string::npos) {
				continue;
			} else {
				str += line;
				str += "\n";
			}
		}
		out << str;
		str.clear();
	} else{
		std::cerr << "not open requset.log"<<std::endl;
	}
	if (in2.is_open()) {
		while (!in2.eof()) {
			getline(in, line);
			pos = line.find("EEEE");
			pos2 = line.find("XXXX");
			pos3 = line.find("BBBB");
			pos4 = line.find("8000");
			if (pos != std::string::npos || pos2 != std::string::npos || pos3 != std::string::npos ||
				pos4 != std::string::npos) {
				continue;
			} else {
				str += line;
				str += "\n";
			}
		}
	}else{
		std::cerr << "not open response.log"<<std::endl;
	}

	out2 << str;
}