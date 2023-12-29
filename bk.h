#ifndef BK_H
#define BK_H
#define MAX 1<<16

typedef struct
{
	char arr[MAX];
	char code[MAX];
	char *p;
	char *c;
}BK;

void make(BK *);
void run(BK *);
void read(BK *, FILE *);
#else
#endif
