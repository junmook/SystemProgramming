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
typedef struct _symbol{
	char sym[10];
	int address;
	struct _symbol *link;
}symbol;
typedef struct _ext_symbol{
	char name[20];
	int length;
	int addr;
	struct _ext_symbol *link;
} ext_symbol;
enum registers{
	A = 0,
	X,
	L, 
	B,
	S, 
	T,
	F,
	P,
	PC,
	SW
};
hash *return_opcode_node(hash **header, char *opcode);
int decision_format(unsigned char **memory, int current_loc);
int decision_xbp(unsigned char **memory, int current_loc);
int decision_ni(unsigned char **memory, int current_loc);
int decision_opcode(unsigned char **memory, int current_loc, int ni);

