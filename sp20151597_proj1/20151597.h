#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
typedef struct _history{
	char name[100];
	int index;
	struct _history* link;
} history;
typedef struct _hash{
	char opcode[10];
	char instructions[10];
	char ss[10];
	struct _hash *link;
}hash;

