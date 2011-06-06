#include <cstdio>
#include <cstdlib>
#include <stack>

// source: http://www.anyexample.com/programming/c/how_to_load_file_into_memory_using_plain_ansi_c_language.xml
int loadfile(const char* name, char** script)
{
	int size = 0;
	FILE* f = fopen(name, "rb");
	if (f == NULL)
	{
		*script = NULL;
		return -1;
	}
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	*script = new char[size+1];
	if (size != (int)fread(*script, sizeof(char), size, f))
	{
		delete [] *script;
		return -2;
	}
	fclose(f);
	(*script)[size] = '\0';
	return size;
}

int main(int argc, char *argv[])
{
	static char array[30000];		// fields
	char *p = array;				// pointer to the current field
	std::stack<long int> brackets;		// loop beginnings locations

	char* script;		// script data
	int size;			// size of the script file

	if (argc < 2)		// Was the script name specified?
	{
		fputs("Usage:\n\tbrainfuck FILE_TO_READ\n", stderr);
		exit(1);
	}

	if ((size = loadfile(argv[1], &script)) < 0)		// Load the script. Have the script been loaded correctly?
	{
		fputs("Cannot open the file\n", stderr);
		exit(2);
	}


	long int i = 0;		// current script character number

	while (script[i] != '\0')		// main loop
	{
		switch (script[i++])
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
					int j = 1;
					char c;
					while (j != 0)		// find the loop end
					{
						c = script[i++];
						if (c == '[')
							++j;
						else if (c == ']')
							--j;
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

	delete [] script;		// free the memory allocated for the script

	return 0;
}
