#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "bk.h"

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
		PStack pstack;
		bk.pstack = &pstack;
		read(&bk, fp);
		fclose(fp);
		make(&bk);
		run(&bk);
	}
	return 0;
}

void read(BK *bk, FILE *fp)
{
	char *ch=bk->code;
	do
	{
		*ch = fgetc(fp);
		if (ferror(fp)) exit(1);
		ch++;
	}while (ch-bk->code < MAX);
	*ch = '\0';
}

void make(BK *bk)
{
	bk->p=bk->arr;
	bk->c=bk->code;
	bk->pstack->top = bk->pstack->p;
}

void push(PStack *ps, char *p)
{
	if (ps->top - ps->p >= MAX>>6) exit(1);
	*(ps->top)++ = p;
}

char *pop(PStack *ps)
{
	if (ps->top == ps->p) exit(1);
	return *--(ps->top);
}

void run(BK* bk)
{
	int count = 1;
	
	while (*bk->c != '\0')
	{
		switch (*bk->c)
		{
			case '\'':
				*bk->p = *++(bk->c);
				break;
			case '{':
				push(bk->pstack, bk->p);
				break;
			case '}':
				bk->p = pop(bk->pstack);
				break;
			case '+':
				*bk->p = *bk->p + count;
				break;
			case '-':
				*bk->p = *bk->p - count;
				break;
			case '>':
				bk->p += count;
				if (bk->p - bk->arr >= MAX) bk->p = bk->arr;
				break;
			case '<':
				bk->p -= count;
				if (bk->p < bk->arr) bk->p = &bk->arr[MAX];
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
