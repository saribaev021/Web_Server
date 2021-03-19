#include <iostream>
#include <fstream>
int main(){
    std::ifstream in("./file_should_exist_after");
    std::string line;
    std::string body;
    if (in.is_open()){
        while (getline(in, line))
        {
            body += line;
        }
        std::cout <<body.length()<<std::endl;
    }else{
        std::cerr << "not open" <<std::endl;
    }
}