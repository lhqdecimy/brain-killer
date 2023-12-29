#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#define MAX 1<<16
typedef struct
{
	char arr[MAX];
	char code[MAX];
	char *p;
	char *c;
}BK;
void make(BK*);
void run(BK*);
int main(int argc, char **argv)
{
	if (argc<2)
	{
		printf("Hello World!\n");
		printf("BK - Brain Killer.\n");
		printf("`bk yourcode.bk` to execute your bk code.\n");
	}
	FILE *fp;
	if (fp = fopen(argv[1], "r"))
	{
		BK bk;
		char *ch=bk.code;
		do
		{
			*ch = fgetc(fp);
			ch++;
		}while(ch-bk.code < MAX);
		*ch = '\0';
		make(&bk);
		run(&bk);
	}
	return 0;
}
void make(BK *bk)
{
	bk->p=bk->arr;
	bk->c=bk->code;
}

void run(BK* bk)
{
	int count = 1;
	while (*bk->c != '\0')
	{
		switch (*bk->c)
		{
			case '+':
				*bk->p = *bk->p + count;
				break;
			case '-':
				*bk->p = *bk->p - count;
				break;
			case '>':
				bk->p += count;
				break;
			case '<':
				bk->p -= count;
				break;
			case '.':
				putchar(*bk->p);
				break;
			case ',':
				*bk->p = getchar();
				break;
			case '=':
				bk->p = bk->arr + *bk->p;
			case '[':
				if (!(*bk->p))
				{
					int count = 1;
					do
					{
						bk->c++;
						if (*bk->c == '[') count++;
						if (*bk->c == ']') count--;
					}while(count && !(*bk->c=='\0'));
					if (*bk->c=='\0') exit(0);
				}
				break;
			case ']':
				if (*bk->p)
				{
					int count = 1;
					do
					{
						bk->c--;
						if (*bk->c == ']') count++;
						if (*bk->c == '[') count--;
					}while(count && !(bk->c < bk->code));
					if (bk->c < bk->code) exit(0);
				}
				break;
			case '(':
				if (!(*bk->p))
				{
					int count = 1;
					do
					{
						bk->c++;
						if (*bk->c == '(') count++;
						if (*bk->c == ')') count--;
					}while(count && !(*bk->c=='\0'));
					if (*bk->c=='\0') exit(0);
				}
				break;
			default:
				if (isdigit(*bk->c))
				{
					sscanf(bk->c, "%d", &count);
					do
					{
						bk->c++;
					}while (isdigit(*bk->c));
					continue;
				}
		}
		count = 1;
		bk->c++;
	}
}
