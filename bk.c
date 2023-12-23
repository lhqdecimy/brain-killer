#include <stdlib.h>
#include <stdio.h>
#define MAX 1<<16
typedef struct
{
	char arr[MAX];
	char code[MAX];
	char *p;
	char *c;
}G;
void make(G* g);
void run(G *g);
int main(int argc, char **argv)
{
	if (argc<2) return 0;
	FILE *fp;
	if (fp = fopen(argv[1], "r"))
	{
		G g;
		char *ch=g.code;
		do
		{
			*ch = fgetc(fp);
			ch++;
		}while(ch-g.code < MAX);
		*ch = '\0';
		make(&g);
		run(&g);
	}
	return 0;
}
void make(G *g)
{
	g->p=g->arr;
	g->c=g->code;
}

void run(G* g)
{
	while (*g->c != '\0')
	{
		switch (*g->c)
		{
			case '`':
				do
				{
					g->c++;
				}while(*g->c!='`' && *g->c!='\0');
				if (*g->c=='\0') exit(0);
			case '+':
				*g->p = *g->p + 1;
				break;
			case '-':
				*g->p = *g->p - 1;
				break;
			case '>':
				g->p++;
				break;
			case '<':
				g->p--;
				break;
			case '.':
				putchar(*g->p);
				break;
			case ',':
				*g->p = getchar();
				break;
			case '=':
				g->p = g->arr + *g->p;
			case '[':
				if (!(*g->p))
				{
					int count = 1;
					do
					{
						g->c++;
						if (*g->c == '[') count++;
						if (*g->c == ']') count--;
					}while(count && !(*g->c=='\0'));
					if (*g->c=='\0') exit(0);
				}
				break;
			case ']':
				if (*g->p)
				{
					int count = 1;
					do
					{
						g->c--;
						if (*g->c == ']') count++;
						if (*g->c == '[') count--;
					}while(count && !(g->c < g->code));
					if (g->c < g->code) exit(0);
				}
				break;
			case '(':
				if (!(*g->p))
				{
					int count = 1;
					do
					{
						g->c++;
						if (*g->c == '(') count++;
						if (*g->c == ')') count--;
					}while(count && !(*g->c=='\0'));
					if (*g->c=='\0') exit(0);
				}
				break;
		}
		g->c++;
	}
}
