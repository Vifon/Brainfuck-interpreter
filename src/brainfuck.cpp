#include <cstdio>
#include <cstdlib>
#include <vector>

int main(int argc, char *argv[])
{
	FILE *f;
	static char array[30000];
	char *p = array;
	std::vector<long int> brackets;
	long int i;
	char c = 0;

	if (argc < 2)
	{
		fputs("Usage:\n\tbrainfuck FILE_TO_READ\n", stderr);
		exit(1);
	}

	if ((f = fopen(argv[1], "r")) == NULL)
	{
		fputs("Cannot open the file\n", stderr);
		exit(2);
	}


	while ((c = fgetc(f)) != EOF)
	{
		switch (c)
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
				*p = getchar()
				break;
			case '[':
				if (*p == 0)
				{
					i = 1;
					while (i != 0)
					{
						c = fgetc(f);
						if (c == '[')
							++i;
						else if (c == ']')
							--i;
					}
				}
				else
					brackets.push_back(ftell(f)-1);
				break;
			case ']':
				fseek(f, brackets.back(), SEEK_SET);
				brackets.pop_back();
				break;
			default:
				break;
		}
	}
	if (fclose(f))
	{
		fputs("The file was not closed correctly\n", stderr);
		exit(3);
	}

	return 0;
}
