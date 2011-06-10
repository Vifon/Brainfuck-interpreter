#include "functions.hpp"
#include <iostream>

std::string loadfile(const char* name)
{
	std::ifstream f;
	std::stringbuf sb;
	f.exceptions(std::ios::failbit);

	f.open(name, std::ios::binary | std::ios::in);
	f.get(sb, EOF);
	f.close();
	std::string str(sb.str());
	return str;
}

void stripComments(std::string& str)
{
	size_t from;
	size_t to;

	while ((from = str.find_first_not_of("+-<>.,[]")) != std::string::npos)
	{
		to = str.find_first_of("+-<>.,[]", from);
		if (to != std::string::npos)
			to -= from;
		str.erase(from, to);
	}
}
