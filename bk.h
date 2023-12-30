#ifndef BK_H
#define BK_H
#define MAX 1<<16

typedef struct
{
	char *p[MAX>>6];
	char **top;
}PStack;

typedef struct
{
	PStack *pstack;
	char arr[MAX];
	char code[MAX];
	char *p;
	char *c;
}BK;

void make(BK *);
void run(BK *);
void read(BK *, FILE *);

void push(PStack *, char *);
char *pop(PStack *);
#else
#endif
