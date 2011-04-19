#include <cstdio>
#include <cstdlib>
#include <vector>

int main(int argc, char *argv[])
{
	FILE *f;
	static int array[256];
	int *p = array;

	std::vector<long int> brackets;

	int i;

	char c = 0;

	if (argc < 2)
	{
		fprintf(stderr, "Usage:\n\tbrainfuck FILE_TO_READ\n");
		exit(1);
	}

	if ((f = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "Cannot open the file\n");
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
				printf("%c", (char)(*p));
				break;
			case ',':
				if((*p = getchar()) == EOF)
				{
					fprintf(stderr, "Error: could not read the key\n");
					exit(4);
				}
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
				{
					brackets.push_back(ftell(f)-1);
				}
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
		fprintf(stderr, "The file was not closed properly\n");
		exit(3);
	}

	return 0;
}
