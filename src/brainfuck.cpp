#include <iostream>
#include <cstdlib>
#include <stack>
#include "functions.hpp"

int main(int argc, char *argv[])
{
	static char array[30000];		// fields
	char* p = array;				// pointer to the current field
	std::stack<std::string::iterator> brackets;		// loop beginnings' locations

	std::string script;		// script data
	int size;			// size of the script file

	if (argc < 2)		// was the script name specified?
	{
		std::cerr << "Usage:\n\tbrainfuck FILE_TO_READ" << std::endl;
		exit(1);
	}

	try
	{
		script = loadfile(argv[1]);
	}
	catch (std::ifstream::failure)
	{
		std::cerr << "Cannot open the file" << std::endl;
		exit(2);
	}


	stripComments(script);

	std::string::iterator i = script.begin();

	while (*i != '\0')		// main loop
	{
		switch (*i++)
		{
			case '+':
				++(*p);
				break;
			case '-':
				--(*p);
				break;
			case '>':
				++p;
				break;
			case '<':
				--p;
				break;
			case '.':
				putchar(*p);
				break;
			case ',':
				*p = getchar();
				break;
			case '[':
				if (*p == 0)
				{
					int nestLevel = 1;
					char c;
					while (nestLevel != 0)		// find the loop end
					{
						c = *i++;
						if (c == '[')
							++nestLevel;
						else if (c == ']')
							--nestLevel;
					}
				}
				else
					brackets.push(i-1);		// save the loop beginning location
				break;
			case ']':
				if (*p != 0)
					i = brackets.top();		// return to the saved location
				brackets.pop();
				break;
			default:
				break;
		}
	}

	return 0;
}
