

# include "system_include.hpp"
# include "parser_config.hpp"


class test
{
private:

public:
	std::string _status;
	std::string _buffer;
	std::string _body;
	bool _big_changus;
	bool _count_body;
	size_t size_of_body;
	size_t _to_int(std::string str);
	void _body_chunked();
};