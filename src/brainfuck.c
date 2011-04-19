#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *f;
	static int array[16];
	int *p = array;

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
				if(!scanf("%c", (char*)p))
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
				break;
			case ']':
				i = 1;
				fseek(f, -1, SEEK_CUR);
				while (i != 0)
				{
					fseek(f, -1, SEEK_CUR);
					c = fgetc(f);
					fseek(f, -1, SEEK_CUR);
					if (c == ']')
						++i;
					else if (c == '[')
						--i;
				}
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
