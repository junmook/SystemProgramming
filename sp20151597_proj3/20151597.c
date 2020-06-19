
#define _CRT_SECURE_NO_WARNINGS
#include "20151597.h"

//for print help
void print_help(){
	printf("h[elp]\n");
	printf("d[ir]\n");
	printf("q[uit]\n");
	printf("hi[stroy]\n");
	printf("du[mp] [start, end]\n");
	printf("e[dit] address, value\n");
	printf("f[ill] start, end, value\n");
	printf("reset\n");
	printf("opcode\n");
	printf("opcodelist \n");
	printf("assemble filename\n");
	printf("type filename\n");
	printf("symbol\n");
	printf("progaddr\n");
	printf("load\n");
	printf("run\n");
	printf("bp\n");

	
}
void type_filename(char *input){


	FILE *fp;
	char c;

	DIR *dir;

	dir = opendir(input);
	if(dir)
		printf("this is directory");

//	file_name[strlen(file_name)-1] = '\0';

	fp = fopen(input, "r");
//	printf("file name : %s\n", input);
	if(!fp){
		printf("file open error!\n");
		return ;
	}
	else{	
		while(1){
		//	fgets(line, sizeof(line), fp);
	//		if(line)
		//	printf("%s", line);
			c = fgetc(fp);
			if(c==EOF)
				break;
			else
				printf("%c", c);
		}
	}
	printf("\n");
	fclose(fp);
}

	


//string convert to decimal
int convert_dec(char *input){
	int i, len, result;
	len = strlen(input);

	result = 0;
	
	for(i = 0; i<len; i++){
		if(input[i]>='0' && input[i]<='9'){
			result = 16*result+(input[i]-'0');
		}
		else if(input[i]>='A' && input[i]<= 'F'){
			result = 16*result+(input[i]-'A'+10);
		}
		else if(input[i]>='a' && input[i]<= 'f')
			result = 16*result+(input[i]-'a'+10);
		else if(input[i]=='x')
			result = 16 * result + (input[i] - 'x');
		else if(input[i]=='X')
			result = 16 * result + (input[i] - 'X');
		else
			result = -1;
	}
	return result;
}
//memory array 0
void reset(unsigned char **memory){
	int i, j;
	for(i = 0; i<65536; i++){
		for(j = 0; j<16; j++){
			memory[i][j] = 0;
		}
	}
}



//dump1(no start address, no end address)
void print_dump1(unsigned char **memory, int *start){
	int start1, end1, i, j;
	int first_column;
	int start_index, end_index;
	int start_index2, end_index2;
	start1 = *start;
	first_column = 0;

	end1 = start1 +159;

	start_index = start1/16;
	start_index2 = start1%16;
	first_column = start_index*16;

	if(end1>1048575){
		end1 = 1048575;
		end_index = end1/16;
		end_index2 = end1%16;
	}

	else{
		end_index = end1/16;
		end_index2 = end1%16;
	}
	

	for(i = start_index; i<=end_index; i++){
		printf("%05X\t", first_column);
		first_column = first_column+16;

		if(i == start_index){
			for(j = 0; j<start_index2; j++)
				printf("\t");
			for(j = start_index2; j<16; j++){
				printf("%02X\t", memory[i][j]);
			}
			printf(";");

			for (j = 0; j < start_index2; j++)
				printf(".");
			for(j = start_index2; j<16; j++){
				if(memory[i][j]>=32&&memory[i][j]<=126)
					printf("%c", memory[i][j]);
				else
					printf(".");
			}
			printf("\n");
		}
		else if(i==end_index){
			for(j = 0; j<=end_index2; j++){
				printf("%02X\t", memory[i][j]);
			}
			for(j = end_index2+1; j<16; j++)
				printf("\t");
			printf(";");
			for(j = 0; j<=end_index2; j++){
				if(memory[i][j]>=32&&memory[i][j]<=126)
					printf("%c", memory[i][j]);
				else
					printf(".");
			}
			for (j = end_index2 + 1; j<16;j++)
				printf(".");
			printf("\n");
		}
		else{
			for(j = 0; j<16; j++)
				printf("%02X\t", memory[i][j]);
			printf(";");

			for(j = 0; j<16; j++){
				if(memory[i][j]>=32&&memory[i][j]<=126)
					printf("%c", memory[i][j]);
				else
					printf(".");
			}
			printf("\n");
		}

	
	}



	if(end1 == 1048575){
		*start = 0;
	}
	else{
		*start = end1+1;
	}
}

//dump2(start address, no end address)
int print_dump2(unsigned char **memory, char *input, int *start){
	int start1, end1, i, j;
	int first_column;
	int start_index, end_index;
	int start_index2, end_index2;

	char *start_point;

	int flag = 0;

	
	start_point = strtok(input, "_");

	start_point = strtok(NULL, "");


	start1 = convert_dec(start_point);

	if(start1<0||start1>1048575){
		printf("dump error : start input range over\n");
		flag = -1;
	}
	else {
		end1 = start1 + 159;
		

		start_index = start1 / 16;
		start_index2 = start1 % 16;
		first_column = start_index * 16;

		if (end1 > 1048575) {
			end1 = 1048575;
			end_index = end1 / 16;
			end_index2 = end1 % 16;
		}
		else {
			end_index = end1 / 16;
			end_index2 = end1 % 16;
		}


		for (i = start_index; i <= end_index; i++) {
			printf("%05X\t", first_column);
			first_column = first_column + 16;

			if (i == start_index) {
				for(j = 0; j<start_index2; j++){
					printf("\t");
				}
				for (j = start_index2; j < 16; j++) {
					printf("%02X\t", memory[i][j]);
				}
				printf(";");
				for(j = 0; j<start_index2; j++){
					printf(".");
				}
				for (j = start_index2; j < 16; j++) {
					if (memory[i][j] >= 32 && memory[i][j] <= 126) {
						printf("%c", memory[i][j]);
					}
					else
						printf(".");
				}
				printf("\n");
			}
			else if (i == end_index) {
				for (j = 0; j <= end_index2; j++) {
					printf("%02X\t", memory[i][j]);
				}
				for(j=end_index2+1; j<16; j++)
					printf("\t");
				printf(";");

				for(j = end_index2+1;j<16; j++)
					printf(" ");
				for (j = 0; j <= end_index2; j++) {
					if (memory[i][j] >= 32 && memory[i][j] <= 126) {
						printf("%c", memory[i][j]);
					}
					else
						printf(".");
				}
			
				printf("\n");
			}
			else {
				for (j = 0; j < 16; j++) {
					printf("%02X\t", memory[i][j]);
				}
				printf(";");
				for (j = 0; j < 16; j++) {
					if (memory[i][j] >= 32 && memory[i][j] <= 126) {
						printf("%c", memory[i][j]);
					}
					else
						printf(".");
				}
				printf("\n");
			}
		}
		if (end1 == 1048575)
			*start = 0;
		else
			*start = end1 + 1;
	}
	return flag;
	
}
//dump3(start address, end address)
int print_dump3(unsigned char **memory, char *input, int *start) {

	int start1, end1, i, j;
	int first_column;
	int start_index, start_index2;
	int end_index, end_index2;
	int flag;
	char *start_point, *end_point, *temp;

	 
	flag = 0;
	temp = strtok(input, "_");
	start_point = strtok(NULL, ",");
	end_point = strtok(NULL, "");

	start1 = convert_dec(start_point);
	end1 = convert_dec(end_point);

	if (start1 < 0 || start1>1048575) {
		printf("dump error : start input range over\n");
		flag = -1;
	}
	if (end1 < 0 || end1>1048575) {
		printf("dump error : end input range over\n");
		flag = -1;
	}

	if (start1 > end1) {
		printf("dump error : start input larger than end input\n");
		flag = -1;
	}
	
	if (flag == 0) {

		start_index = start1 / 16;
		start_index2 = start1 % 16;
		first_column = start_index * 16;

		end_index = end1 / 16;
		end_index2 = end1 % 16;

		for (i = start_index; i <= end_index; i++) {
			printf("%05X\t", first_column);
			first_column = first_column + 16;

			if (i == start_index && i == end_index) {
				for (j = 0; j < start_index2; j++)
					printf("\t");
				for (j = start_index2; j <= end_index2; j++)
					printf("%02X\t", memory[i][j]);
				for (j = end_index2 + 1; j < 16; j++)
					printf("\t");
				printf(";");

				for (j = 0; j < start_index2; j++)
					printf(".");
				for (j = start_index2; j <= end_index2; j++) {
					if (memory[i][j] >= 32 && memory[i][j] <= 126)
						printf("%c", memory[i][j]);
					else
						printf(".");
				}
				for (j = start_index2 + 1; j < 16; j++)
					printf(".");
				printf("\n");
			}
			else if (i == start_index) {
				for (j = 0; j < start_index2; j++)
					printf("\t");
				for (j = start_index2; j < 16; j++)
					printf("%02X\t", memory[i][j]);
				printf(";");

				for (j = 0; j < start_index2; j++)
					printf(".");
				for (j = start_index2; j < 16; j++) {
					if (memory[i][j] >= 32 && memory[i][j] <= 126)
						printf("%c", memory[i][j]);
					else
						printf(".");
				}
				printf("\n");
			}
			else if (i == end_index) {
				for (j = 0; j <= end_index2; j++)
					printf("%02X\t", memory[i][j]);
				for (j = end_index2 + 1; j < 16; j++)
					printf("\t");
				printf(";");

				for (j = 0; j <= end_index2; j++) {
					if (memory[i][j] >= 32 && memory[i][j] <= 126)
						printf("%c", memory[i][j]);
					else
						printf(".");
				}
				for (j = end_index2 + 1; j < 16; j++)
					printf(".");
				printf("\n");
			}
			else {
				for (j = 0; j < 16; j++)
					printf("%02X\t", memory[i][j]);
				printf(";");
				for (j = 0; j < 16; j++) {
					if (memory[i][j] >= 32 && memory[i][j] <= 126)
						printf("%c", memory[i][j]);
					else
						printf(".");
				}
				printf("\n");
			}
		}

		if (end1 < 1048575)
			*start = end1 + 1;
		else if (end1 == 1048575)
			*start = 0;
	}
	return flag;

}
//target address's value -> value of user input 
int edit(unsigned char **memory, char *input) {
	char *value_, *target_point, *temp;
	int target, value;
	int target_index, target_index2;
	int flag = 0;

	temp = strtok(input, "_");
	target_point = strtok(NULL, ",");
	value_ = strtok(NULL, "");

	target = convert_dec(target_point);
	value = convert_dec(value_);

	if (target < 0 || target>1048575) {
		printf("edit error : target point range over!\n");
		flag = -1;
	}

	
	if (value > 255 || value < 0) {
		printf("edit error : value range over!\n");
		flag = -1;
	}


	if (flag == 0) {
		target_index = target / 16;
		target_index2 = target % 16;

		memory[target_index][target_index2] = value;
	}
	return flag;
}
//from start address to end address, memory's value->value of user input 
int fill(unsigned char **memory, char *input) {
	char *start_point, *end_point, *value_, *temp;
	int start_index, end_index;
	int start_index2, end_index2;
	int value, start, end;
	int i, j;

	int flag = 0;
	
	temp = strtok(input, "_");
	start_point = strtok(NULL, ",");
	end_point = strtok(NULL, ",");
	value_ = strtok(NULL, "");

	start = convert_dec(start_point);
	end = convert_dec(end_point);
	value = convert_dec(value_);

	if (start < 0 || start>1048575) {
		printf("fill error : start input range over!\n");
		flag = -1;

	}
	if (end < 0 || end>104875) {
		printf("fill error : end input range over!\n");
		flag = -1;
	}
	if (value < 0 || value>255) {
		printf("fill error : value input range over!\n");
		flag = -1;
	}
	if(start>end){
		printf("fill error : start input more than end input!\n");
		flag = -1;
	}

	if (flag == 0) {
		start_index = start / 16;
		start_index2 = start % 16;
		end_index = end / 16;
		end_index2 = end % 16;

		for (i = start_index; i <= end_index; i++) {
			if (i == start_index && i == end_index) {
				for (j = start_index2; j <= end_index2; j++) {
					memory[i][j] = value;
				}
			}
			else if (i == start_index) {
				for (j = start_index2; j < 16; j++)
					memory[i][j] = value;
			}
			else if (i == end_index) {
				for (j = 0; j <= end_index2; j++)
					memory[i][j] = value;
			}
			else {
				for (j = 0; j < 16; j++)
					memory[i][j] = value;
			}

		}
	}
	return flag;

}
//print file, directory in current directory
void print_directory(){
	DIR *dir;
	struct dirent *dir_entry;
	struct stat astat;

	dir = opendir(".");

	while((dir_entry = readdir(dir))!=NULL){
		
		lstat(dir_entry->d_name, &astat);


			if(S_ISDIR(astat.st_mode)){
				if(strncmp(dir_entry->d_name, ".", 1)!=0 && strncmp(dir_entry->d_name, "..",2)!=0){
					printf("%s",dir_entry->d_name);
					printf("/\n");
				}
			}
			else{
				if(astat.st_mode & S_IXUSR){
					printf("%s*\n", dir_entry->d_name);
				
				}	
				else
					printf("%s\n", dir_entry->d_name);		
			}	
		
	}
}
//create history node for history linked list
history *create_history_node(char *input){
	history *tmp;

	tmp = (history*)malloc(sizeof(history));
	strcpy(tmp->name, input);
	tmp->link = NULL;

	return tmp;
}
//make history linked list
void history_made(history **header, history *newnode){
	history *tmp = *header;

	if(header == NULL){
		*header = newnode;
		
	}
	else{
		while(tmp->link != NULL){
			tmp = tmp->link;
		}
		tmp->link = newnode;
		tmp->link->index = tmp->index+1; 
	}
}

//print history linked list 
void print_history(history *header){
	history *ptr = header;
	while(ptr->link !=NULL){
		printf("%d\t%s\n", ptr->link->index, ptr->link->name);
		ptr = ptr->link;
	}
}

//generate hash key for mnemonic
int hash_function(char *input) {
	int result,i, len;
	result = 0;

	len = strlen(input);
	for(i = 0; i<len; i++){
		result = (int)input[i]+result;
	}
	result = result%20;

	
	return result;
}
//create hash node for hash table 
hash *create_hash_node(FILE *fp) {
	hash *tmp;
	tmp = (hash*)malloc(sizeof(hash));
	fscanf(fp, "%s%s%s", tmp->opcode, tmp->instructions, tmp->ss);
	
	tmp->link = NULL;
	return tmp;
}
//make hash table
void hashtable_made(hash *header[20], FILE *fp) {
	hash *pointer;
	hash *newnode;
	int i, index;
	for (i = 0; i < 58; i++) {
		newnode = create_hash_node(fp);
		index = hash_function(newnode->instructions);
		pointer = header[index];
		if (header[index] == NULL)
			header[index] = newnode;
		else {
			while (pointer->link != NULL)
				pointer = pointer->link;
			pointer->link = newnode;
		}
	}
}
hash *return_opcode_node(hash **header, char *opcode){
	int hash_key;
	hash *ptr;
	hash *temp=NULL;
	hash_key = hash_function(opcode);
	if(hash_key>=0 && hash_key<20){
		ptr = header[hash_key];
		while(ptr != NULL){
			if(strcmp(ptr->instructions, opcode)==0){
				temp = ptr;
				break;
			}
			ptr = ptr->link;
		}
	}
	return temp;
}

//print hash table 
void opcodelist_print(hash **header) {
	int i;
	hash *ptr;
	for (i = 0; i < 20; i++) {
		ptr = header[i];
		printf("%d : ", i); 
		if(ptr!=NULL){
			printf("[%s, %s]", ptr->instructions, ptr->opcode);
			ptr = ptr->link;
		}
		while (ptr != NULL) {
			printf("->[%s, %s]", ptr->instructions, ptr->opcode);
			ptr = ptr->link;
		}
		printf("\n");
	}
}
//search mnemonic's opcode in hash table 
int search_opcode_mnemonic(hash **header, char *input){
	char *opcode, *mnemonic;
	int hash_key, flag;
	int result = 0;
	hash *ptr;
	flag = 0;
	opcode = strtok(input, "_");
	mnemonic = strtok(NULL, "");
	printf("input: %s\n", input);
	hash_key = hash_function(mnemonic);
	ptr = header[hash_key];

	while(ptr!=NULL){
		if(strcmp(ptr->instructions, mnemonic)==0){
			flag++;
			break;
		}
		ptr = ptr->link;
	}
	if(flag==1)
		printf("opcode is %s\n", ptr->opcode);
	else {
		printf("this mnemonic doesn't exist in hash table\n");
		result = -1;
	}
	return result;
}
symbol *create_symbol_node(char *ssymbol, int addr){
	symbol *tmp;
	tmp = (symbol*)malloc(sizeof(symbol));
	strcpy(tmp->sym, ssymbol);
	tmp->address = addr;
	tmp->link = NULL;
	return tmp;
}
symbol *search_symbol_table(char *ssymbol, symbol **header){
	int hash_key, result;
	symbol *ptr;
	symbol *tmp=NULL;

	hash_key = ssymbol[0]-'A';
	if(hash_key>=0 && hash_key<=25){
		ptr = header[hash_key];

		while(ptr !=NULL){
			if(strcmp(ptr->sym, ssymbol)==0){
				tmp = ptr;
				break;
			}
			ptr = ptr->link;
		}
	}
//	printf("symbol search\n");
	return tmp;
}
void print_symbol_table(symbol **header){
	int i;
	symbol *pointer;
	for(i = 25; i>=0; i--){
		pointer = header[i];
		if(pointer != NULL){
			while(pointer != NULL){
				printf("%s %04X\n", pointer->sym, pointer->address);
				pointer = pointer->link;
			}
		}
	}
}
void make_symbol_table(symbol **header, int addr, char *ssymbol){
	int index = 0;
	int i;

	symbol *newnode;
	symbol *pointer;
	symbol *prev;
	symbol *ptr;
	
	newnode = create_symbol_node(ssymbol, addr);

	index = ssymbol[0] - 'A';

	if(header[index] == NULL){
		header[index] = newnode;
//		printf("symbol table : %s\n", header[index]->sym);
	}
	else{
		if(strcmp(newnode->sym, header[index]->sym)>0){
			newnode->link = header[index];
			header[index] = newnode;
		}
		else{
			pointer = header[index];
			while(pointer != NULL && strcmp(newnode->sym, pointer->sym)<0){
				prev = pointer;
				pointer = pointer->link;
			}
			newnode->link = prev->link;
			prev->link = newnode;
		}
	}
}
int char_dec(char *input){
	int i;
	int result = 0;
	for(i = 0; i<strlen(input); i++){
		if(input[i] >= '0' && input[i] <= '9'){
			result = result*10 + input[i]-'0';
		}
	}
	return result;
}
int format2(char *opcode, char *operand){
	int sum, opcd;
	int value_reg1, value_reg2;

	char reg1[10] = {0};
	char reg2[10] = {0};
	value_reg1 = -1;
	value_reg2 = -1;
	opcd = convert_dec(opcode);
	strncpy(reg1, operand, 1);
	strncpy(reg2, operand+2, 1);
	if(reg2[0]==' ')
		value_reg2 = 0;




	if(strcmp(reg1, "A")==0)
		value_reg1 = 0;
	else if(strcmp(reg1, "X")==0)
		value_reg1 = 1;
	else if(strcmp(reg1, "L")==0)
		value_reg1 = 2;
	else if(strcmp(reg1, "PC")==0)
		value_reg1 = 8;
	else if(strcmp(reg1, "SW")==0)
		value_reg1 = 9;
	else if(strcmp(reg1, "B")==0)
		value_reg1 = 3;
	else if(strcmp(reg1, "S")==0)
		value_reg1 = 4;
	else if(strcmp(reg1, "T")==0)
		value_reg1 = 5;
	else if(strcmp(reg1, "F")==0)
		value_reg1 = 6;
	
//	printf("value reg1 : %d\n", value_reg1);

//뒤에 아무것도 없는 경우 value_reg2 = 0
	if(strcmp(reg2, "A")==0)
		value_reg2 = 0;
	else if(strcmp(reg2, "X")==0)
		value_reg2 = 1;
	else if(strcmp(reg2, "L")==0)
		value_reg2 = 2;
	else if(strcmp(reg2, "PC")==0)
		value_reg2 = 8;
	else if(strcmp(reg2, "SW")==0)
		value_reg2 = 9;
	else if(strcmp(reg2, "B")==0)
		value_reg2 = 3;
	else if(strcmp(reg2, "S")==0)
		value_reg2 = 4;
	else if(strcmp(reg2, "T")==0)
		value_reg2 = 5;
	else if(strcmp(reg2, "F")==0)
		value_reg2  = 6;
	
//	printf("reg1, reg2 : %s, %s\n", reg1, reg2);
	if(value_reg1<0 || value_reg2<0)
		sum = value_reg1+value_reg2;
	else if(value_reg1>=0 && value_reg2>=0){
		opcd = opcd<<8;
		value_reg1 = value_reg1<<4;
		sum = opcd+value_reg1+value_reg2;
	}
//	printf("reg1, reg2, sum : %s %s %d\n", reg1, reg2, sum);

	
	return sum;
}
int format3(char *opcode, int nixbpe, int disp){
	int opcd, sum, temp, disp2;
	opcd = 0;
	sum = 0;
//	printf("format3 opcode : %s\n", opcode);	
	opcd = convert_dec(opcode);
	
	//opcd2 = opcd&temp;
	opcd = opcd<<16;
	nixbpe = nixbpe<<12;

	if(disp>=0)
		sum = opcd+nixbpe+disp;
	else{
		disp2 = (0x000FFF & disp);
		sum = opcd+nixbpe+disp2;
	}
//	printf(" opcode : %s disp : %04X\n", opcode, disp2);
	return sum;
}

int format4(char *opcode, int nixbpe, int disp){
	int opcd, sum, disp2;

	opcd = convert_dec(opcode);
	sum = 0;

	opcd = opcd<<24;
	nixbpe = nixbpe<<20;

	if(disp>=0)
		sum = opcd+nixbpe+disp;
	else{
		disp2 = (0x0FFFFF & disp);
		sum = opcd+nixbpe+disp2;
	}
}

	
int pass1(char *file_name, int *length, int *base_address, symbol **symbol_header, hash **hash_header, int *object_code_len){
	FILE *fp1, *fp2;
	char line[128], line2[128], line3[128];
	char *name1, *name2;
//	buffer = strtok(std_input, "_");
//	file_name = strtok(NULL, "");
	char buffer[20];
	char *k, *kk;
	char *label, *Operator, *operand, *operand2, *temp;
	char base_operand[10];
	int addr = 0;
	int start_addr = 0;
	int oidx = 0;
	int enter_flag = 0;
	int end_flag = 0;

	int assemble_error_flag = 0;
	int file_error_flag = 0;
	strcpy(buffer, file_name);
//	printf("FIle name : %s", buffer);
	name1 = strtok(file_name, ".");
	name2 = strtok(NULL, "");
//	printf("name1, name2 : %s %s\n", name1, name2);
	fp2 = fopen("intermediate.txt","w");

	if(!name2){
		file_error_flag = 1;
		printf("not assembley file !\n");
		return file_error_flag;
	}
	else if(strcmp(name2, "asm")!=0){
		file_error_flag = 1;
		printf("not assembly file!\n");
		return file_error_flag;
	}



	if(file_error_flag == 0){
		fp1 = fopen(buffer, "r");
		if(fp1 == NULL){
			file_error_flag = 1;
			printf("file open error!\n");
			return file_error_flag;
		}
		else{
			fgets(line, sizeof(line), fp1);
			line[strlen(line)-1] = '\0';
			strcpy(line2, line);
			if(line[0]==' '){
				label = "      ";
				Operator = strtok(line, " \t");
				operand = strtok(NULL, "");
			}
			else{
				label = strtok(line, " \t");
				Operator = strtok(NULL, " \t");
				operand = strtok(NULL, "");
				
			}
	//		printf("line : %s\n", line);
	//		printf("label, Operator, operand : %s %s %s\n", label, Operator, operand);
			if(strcmp(Operator, "START")==0){
				start_addr = strtol(operand, &temp,16);
				addr = start_addr;
	//			printf("start address : %04X, operadn : %s\n", start_addr, operand);
	//			printf("start : %s %s %s \n", label, Operator, operand);
				fprintf(fp2, "%04X %-7s %-7s %-10s\n", addr, label, Operator, operand);
			}
			else{
				printf("%s error : don't have START\n", line2);
				assemble_error_flag = 1;
				return assemble_error_flag;
			}

			while(strstr(Operator, "END")==0){
				fgets(line, sizeof(line), fp1);
				if(feof(fp1))
						break;
					
					
				
				line[strlen(line)-1] = '\0';
			
				
				
				if(line[0] != '.'){
					if(line[0] == ' '){
						label = "       ";
						Operator = strtok(line, " \t");
						operand = strtok(NULL, " \t");
						operand2 = strtok(NULL, "");
						if(!operand){
							operand = "          ";
						}
						else{
							if(operand2)
								strcat(operand, operand2);
						}

	//					printf("line1 : %s, %s, %s\n", label, Operator, operand);
					}
					else{
						label = strtok(line, " \t");
						Operator = strtok(NULL, " \t");
						operand = strtok(NULL, " \t");
						operand2 = strtok(NULL, "");
				//		printf("line1 : %s, %s, %s \n", label, Operator, operand);
						if(!operand){
							operand = "          ";
						}
						else{
							if(operand2)
								strcat(operand, operand2);
						}
	//					printf("line1 : %s, %s, %s \n", label, Operator, operand);
					}


					if(label[0] != ' '){
						if(strcmp(Operator, "END")==0){
							assemble_error_flag = 1;
							printf("label front END\n");
							return assemble_error_flag;
						}
						else if(!search_symbol_table(label, symbol_header)){
							make_symbol_table(symbol_header, addr, label);
	//						printf("make sym table\n");
						}
						else{
							printf("duplicate label in SYMTAB!\n");
							assemble_error_flag = 1;
							return assemble_error_flag;
						}
					}
					
					if(strcmp(Operator, "END")==0){
						fprintf(fp2, "     %-7s %-7s %-10s\n", label, Operator, operand);
						end_flag = 1;
	//					printf("end _flag : %d\n", end_flag);
						break;
					}
					else{

						 if(strcmp(Operator, "BASE")==0){
							fprintf(fp2, "     %-7s %-7s %-10s\n", label, Operator, operand);
						 }
						 else{
							/* if(label[0] = ' '){
								 fprintf(fp2, "     %-7s %-7s %-10s\n", label, Operator, operand);
							 }*/
							 fprintf(fp2, "%04X %-7s %-7s %-10s\n", addr, label, Operator, operand);
						 }
					}
					/*
					else{
						//fgets(line2, sizeof(line2), fp1);
						printf("line : %s\n", line3);
						printf("line2: %s\n", line2);
						if(!line2){
							fprintf(fp2, "     %-7s %-7s %-10s\n", label, Operator, operand);
							break;
						}
						else{
							fprintf(fp2, "%04X %-7s %-7s %-10s\n", addr, label, Operator, operand);
						}
					}*/

					if(Operator[0] == '+'){
						k = strtok(Operator+1, "");
						if(return_opcode_node(hash_header, k)){
							addr = addr+4;
							if(object_code_len[oidx]+4>30 || enter_flag == 1){
								oidx++;
								enter_flag=0;
							}
							object_code_len[oidx] +=4;

						}
						else{
							assemble_error_flag = 1;
							return assemble_error_flag;
						}
					}
					else if(Operator[0] != '+'){
						if(return_opcode_node(hash_header, Operator)){
							if(strcmp(return_opcode_node(hash_header, Operator)->ss, "2")==0){
								addr = addr+2;
								if(object_code_len[oidx]+2>30||enter_flag==1){
									oidx++;
									enter_flag=0;
								}
								object_code_len[oidx] += 2;
							}
							else{
								addr = addr+3;
								if(object_code_len[oidx]+3>30 || enter_flag == 1){
									oidx++;
									enter_flag = 0;
								}
								object_code_len[oidx] +=3;
							}
						}
						else{
							if(strcmp(Operator, "WORD")==0){
								addr = addr+3;
								if(object_code_len[oidx]+3>30 || enter_flag==1){
									oidx++;
									enter_flag=0;
								}
								object_code_len[oidx] +=3;
							}

							else if(strcmp(Operator, "RESW")==0){
								addr = addr+3*char_dec(operand);
								enter_flag = 1;
							}
							else if(strcmp(Operator, "RESB")==0){
								addr = addr+char_dec(operand);
								enter_flag = 1;
							}
							else if(strcmp(Operator, "BYTE")==0){
								if(operand[0] == 'C'){
									k = strtok(operand+1, "'");
									addr = addr+strlen(k);
									if(object_code_len[oidx]+strlen(k)>30 || enter_flag == 1){
										oidx++;
										enter_flag = 0;
									}
									object_code_len[oidx] += strlen(k);
								}
								else if(operand[0] == 'X'){
									k = strtok(operand+1, "'");
									addr = addr+strlen(k)/2;
									if(object_code_len[oidx]+strlen(k)/2>30 || enter_flag == 1){
										oidx++;
										enter_flag = 0;
									}
									object_code_len[oidx] += strlen(k)/2; 
								}
								else{
									printf("invalid operand!\n");
									assemble_error_flag = 1;
									break;
								}
							}
							else if(strcmp(Operator, "BASE")==0){
								*base_address = 0;
								strcpy(base_operand, operand);
	//							printf("base_operand : %s\n", base_operand);
							}
						}
					}
				}
			}
			//strcpy(line3, line2);
		} 
		*length = addr-start_addr;
		*base_address = search_symbol_table(base_operand, symbol_header)->address;
	//	fprintf(fp2, "     %-7s %-7s %-10s\n", label, Operator, operand);
		if(end_flag ==0){
			printf("%s  don't have END\n", line);
			printf("assemble error!\n");
			assemble_error_flag = 1;
		}
	//	printf("base address : %04X\n", *base_address);

		fclose(fp1);
		fclose(fp2);
	//	return assemble_error_flag;
	//	printf("assemble flag : %d\n", assemble_error_flag);
	}

	return assemble_error_flag;
}
int pass2(char *file_name, int *length, int *base_address, symbol **symbol_header, hash **hash_header, int *object_code_len){
	//fp1 = intermediate.txt, fp2 = file_name.lst, fp3 = file_name.obj
	FILE *fp1, *fp2, *fp3;
	char *write_file_name, lst_file_name[20], obj_file_name[20];
	//line of intermediate file
	char line[128], line2[128];
	char buffer[128];//line을 저장하기 위해서
	char label[10], operator[10], operand[10], address[10];//intermediate 파일에서 읽은 line을 이와같이 나눈다.
	char *rev_label, *rev_operator, *rev_operand, *rev_address;//각각에 대해서 공백을 제거
	char *rev_operand2;//X'F1', C'EOF'에서 F1과 EOF를 분리하기 위해서
	int line_num;//몇번째 줄인지 나타내기 위해서
	int record_length;
	int object_code;//object code
	int object_code_byte;
	int error_flag;
	int i;//반복문을 위한 index
	int enter_flag;//object file에서 개행을 해야할 때를 알려주는 flag
	int pc;//program counter
	int modicode[100], midx;//modification을 처리하기 위해서

	int ta;//target address
	int nixbpe;
	int constant; // #뒤에 붙은 상수를 처리하기 위해
	int first_execution_addr;//프로그램에서 첫번 째로 수행되는 instruction의 주소
	symbol *sym_node;
	hash *hash_node;
	int oidx = 0;//object_code_len을 위한 index
	
	midx = 0;
	pc = 0;
	object_code_byte = 0;
	enter_flag = 1;
	object_code_byte=0;
	line_num = 5;
	record_length = 0;
	object_code = 0;
	error_flag = 0;

	fp1 = fopen("intermediate.txt", "r");

	write_file_name = strtok(file_name, ".");
	strcpy(lst_file_name, write_file_name);
	strcpy(obj_file_name, write_file_name);

	strcat(lst_file_name, ".lst");
	strcat(obj_file_name, ".obj");

	fp2 = fopen(lst_file_name, "w");
	fp3 = fopen(obj_file_name, "w");

	fgets(line, sizeof(line), fp1);
	line[strlen(line)-1] = '\0';
//	printf("%s\n", line);
	strncpy(address, line, 5);
	strncpy(label, line+5, 8);
	label[6] = '\0';
	strncpy(operator, line+13, 8);
	operator[6] ='\0';
	strncpy(operand, line+21, strlen(line)-21);
	operand[strlen(operand)-1] = '\0';
	
	rev_address = strtok(address, " \t");
//	printf("label : %s\n", label);
	rev_label = strtok(label, " \t");
//	printf("rev_label : %s\n", rev_label);
	if(!rev_label){
		rev_label = "      ";
//		printf("rev label : %s\n", rev_label);
	}
	rev_operator = strtok(operator, " \t");
	rev_operand = strtok(operand, " \t");
//	printf("%s\n",rev_address);
//	printf("%s\n", rev_label);
//	printf("%s\n", rev_operator);
//	printf("%s\n", rev_operand);
	

	if(strcmp(rev_operator, "START")==0){
		fprintf(fp2, "%3d %s\n", line_num, line);
		line_num = line_num+5;
		if(rev_label[0]==' '){
			fprintf(fp3, "H      %06X%06x", convert_dec(rev_address), *length);
		}
		else{
			fprintf(fp3, "H%-6s%06X%06X", rev_label, convert_dec(rev_address), *length);
		}
	}
/*	else{
		printf("line : %d don't exist START\n", line_num);
		error_flag = 1;
		return error_flag;
	}*/

	first_execution_addr = convert_dec(rev_address);

	while(strstr(rev_operator, "END")==0){
		fgets(line, sizeof(line), fp1);
		line[strlen(line)-1] = '\0';
	//	printf("line : %s\n", line);
		strcpy(buffer, line);
		strcpy(line2, line);

		if(line[0]!='.'){
			strncpy(address, line, 4);
			strncpy(label, line+5, 7);
			label[6] = '\0';
			strncpy(operator, line+13, 7);
			operator[6] = '\0';
			strncpy(operand, line+21, strlen(line)-21);
			operand[strlen(operand)-1] = '\0';
			
	
			if(!rev_address){
				rev_address = "    ";
			}
		
			rev_label = strtok(label, " \t");
			if(!rev_label){
				rev_label = "       ";
			}
		
			rev_operator = strtok(operator, " \t");
		
			rev_operand = strtok(operand, " \t");
	//		operand2 = strtok(NULL, "");
			if(!rev_operand){
				rev_operand = "          ";
			}

			if(strcmp(rev_operator, "RESW")==0){
				fprintf(fp2, "%3d %s\n", line_num, buffer);
				line_num = line_num+5;
				enter_flag = 1;
			}
			else if(strcmp(rev_operator, "RESB")==0){
				fprintf(fp2, "%3d %s\n", line_num, buffer);
				line_num = line_num+5;
				enter_flag = 1;
			}
			else if(strcmp(rev_operator, "END")==0){
				fprintf(fp2, "%3d %s\n", line_num, buffer);
	//			fprintf(fp3, "\nE%06X", first_execution_addr);
			}
			
			else if(strcmp(rev_operator, "WORD")==0){
				object_code = char_dec(rev_operand);
				if(object_code>=0&&object_code<=16777215){
					fprintf(fp2, "%3d %s %06X\n", line_num, buffer, object_code);
					if(object_code_byte+3>30 || enter_flag ==1){
						fprintf(fp3, "\nT%06X%02X", convert_dec(rev_address), object_code_len[oidx]);
						object_code_byte = 0;
						enter_flag = 0;
						oidx++;
					}
					fprintf(fp3, "%06X", object_code);
					object_code_byte = object_code_byte+3;
				}
				else{
					printf("%s error : range over!\n", line2);
					error_flag = 1;
					break;
				}
				line_num = line_num+5;
			}
			else if(strcmp(rev_operator, "BYTE")==0){
				rev_operand2 = strtok(rev_operand+1, "'");
				fprintf(fp2, "%3d %s ", line_num, buffer);
				if(rev_operand[0]=='C'){
					for(i = 0; i<strlen(rev_operand2); i++){
						fprintf(fp2, "%2X", rev_operand2[i]);
					//	fprintf(fp3, "%2X", rev_operand2[i]);
					}
					fprintf(fp2, "\n");
					if(object_code_byte+strlen(rev_operand2)>30 || enter_flag ==1){
						fprintf(fp3, "\nT%06X%02X", convert_dec(rev_address), object_code_len[oidx]);
					
						object_code_byte = 0;
						enter_flag = 0;
						oidx++;
					}
					for(i = 0; i<strlen(rev_operand2); i++){
						fprintf(fp3, "%2X", rev_operand2[i]);
					}
					object_code_byte = object_code_byte+strlen(rev_operand2);
					

				}
				else if(rev_operand[0] == 'X'){
					for(i = 0; i<strlen(rev_operand2); i++){
						fprintf(fp2, "%c", rev_operand2[i]);
				//		fprintf(fp3, "%c", rev_operand2[i]);
					}
					if(object_code_byte+strlen(rev_operand2)/2>30 || enter_flag == 1){
						fprintf(fp3, "\nT%06X%02X", convert_dec(rev_address), object_code_len[oidx]);
						fprintf(fp3, "%02X", 0);
						object_code_byte = 0;
						enter_flag = 0;
						oidx++;
					}
					for(i = 0; i<strlen(rev_operand2); i++){							
						fprintf(fp3, "%c", rev_operand2[i]);
					}
					object_code_byte = object_code_byte+strlen(rev_operand2)/2;
	

					fprintf(fp2, "\n");
				}
				else{
					printf("%s error : invalid operand!\n", line2);
					error_flag = 1;
					break;
				}
				line_num = line_num+5;
			}
			else if(strcmp(rev_operator, "BASE")==0){
				fprintf(fp2, "%3d %s\n", line_num, buffer);
				line_num = line_num+5;
			}
			else if(strcmp(rev_operator, "RSUB")==0){
				fprintf(fp2, "%3d %s %06X\n", line_num, buffer, 0x4F0000);
				if(object_code_byte+3>30 || enter_flag ==1){
					fprintf(fp3, "\nT%06X%02X", convert_dec(rev_address), object_code_len[oidx]);
					object_code_byte = 0;
					enter_flag = 0;
					oidx++;
				}
				fprintf(fp3, "%06X", 0x4F0000);
				object_code_byte +=3;
				line_num = line_num+5;
			//	fprintf(fp3, "%06X", 0x4F0000);
			}

			else if(rev_operator[0] != '+'){
				hash_node = return_opcode_node(hash_header, rev_operator);
				if(hash_node){
					if(strcmp(hash_node->ss, "2")==0){
	//					printf("opcode type : %s %s\n", hash_node->instructions,hash_node->ss);
						object_code = format2(hash_node->opcode, rev_operand);
					//	printf("object_code : %d\n", object_code);
						if(object_code>=0)
							fprintf(fp2, "%3d %s %4X\n", line_num, buffer, object_code);
						else{
							printf("%s error : invalid register!\n", line2);
							error_flag = 1;
							return error_flag;
						}

						if(object_code_byte+2>30||enter_flag == 1){
							fprintf(fp3, "\nT%06X%02X", convert_dec(rev_address), object_code_len[oidx]);
							object_code_byte = 0;
							enter_flag = 0;
							oidx++;
						}
						fprintf(fp3, "%04X", object_code);
						object_code_byte = object_code_byte+2;
					}
					else if(strcmp(hash_node->ss, "1")==0){
							object_code = convert_dec(hash_node->opcode);
							fprintf(fp2, "%3d %s %2X\n", line_num, buffer, object_code);
							if(object_code_byte+1>30 || enter_flag==1){
								fprintf(fp3, "\nT%06X%01X", convert_dec(rev_address), object_code_len[oidx]);
								object_code_byte = 0;
								enter_flag = 0;
								oidx++;
							}
							fprintf(fp3, "%04X", object_code);
							object_code_byte+=1;
					
					}
					else if(strcmp(hash_node->ss, "3/4")==0){
						if(rev_operand[0] == '#'){
							sym_node = search_symbol_table(rev_operand+1, symbol_header);
						//	printf("# symbol  : %s\n", rev_operand+1);
							if(sym_node){
						//		printf("exist symbol\n");
								pc = convert_dec(rev_address)+3;
								ta = sym_node->address;
								if(ta-pc>=-2048 && ta-pc<=2047){
									nixbpe = 18;
									object_code = format3(hash_node->opcode, nixbpe, ta-pc);
									fprintf(fp2, "%3d %s %06X\n", line_num, buffer, object_code);
									if(object_code_byte+3>30 || enter_flag == 1){
										fprintf(fp3, "\nT%06X%02X", convert_dec(rev_address), object_code_len[oidx]);
										object_code_byte = 0;
										enter_flag = 0;
										oidx++;
									}
									fprintf(fp3, "%06X", object_code);
									object_code_byte = object_code_byte+3;
			//						line_num = line_num+5;
								}
								//base
								
								else if(ta-*base_address>=0 && ta-*base_address<=4095){
								//	disp = ta-*base_address;
									nixbpe = 20;
									object_code = format3(hash_node->opcode, nixbpe, ta-*base_address);
									fprintf(fp2, "%3d %s %06X\n", line_num, buffer, object_code);
									if(object_code_byte+3>30 || enter_flag == 1){
										fprintf(fp3, "\nT%06X%02X", convert_dec(rev_address), object_code_len[oidx]);
										object_code_byte = 0;
										enter_flag = 0;
										oidx++;
									}
									fprintf(fp3, "%06X", object_code);
									object_code_byte = object_code_byte+3;

								}
								else{
									printf("%s error : range over!\n", line2);
									error_flag = 1;
									break;
								}

								//range over
							}
							else{
								constant = char_dec(rev_operand+1);
								if(constant>=-2048 && constant<=4095){
									nixbpe = 16;
									object_code = format3(hash_node->opcode, nixbpe, constant);
									fprintf(fp2, "%3d %s %06X\n", line_num, buffer, object_code);
									if(object_code_byte+3>30 || enter_flag == 1){
										fprintf(fp3, "\nT%06X%02X", convert_dec(rev_address), object_code_len[oidx]);
										object_code_byte = 0;
										enter_flag = 0;
										oidx++;
									}
									fprintf(fp3, "%06X", object_code);
									object_code_byte +=3;
								}//range over
							}
						}//if(operant[0] == '#')

						else if(rev_operand[0] == '@'){
							sym_node = search_symbol_table(rev_operand+1, symbol_header);
							if(sym_node){
								pc = convert_dec(rev_address)+3;
								ta = sym_node->address;
								
								if(ta-pc>=-2048 && ta-pc<=2047){
									nixbpe = 34;
									object_code = format3(hash_node->opcode, nixbpe, ta-pc);
									fprintf(fp2, "%3d %s %06X\n", line_num, buffer, object_code);
									if(object_code_byte+3>30 || enter_flag == 1){
										fprintf(fp3, "\nT%06X%02X", convert_dec(rev_address), object_code_len[oidx]);
										object_code_byte = 0;
										enter_flag = 0;
										oidx++;
									}
									fprintf(fp3, "%06X", object_code);
									object_code_byte +=3;
								}
								
								else if(ta-*base_address>=0 && ta-*base_address<=4096){
									nixbpe = 36;
							//		disp = ta-*base_address;
									object_code = format3(hash_node->opcode, nixbpe, ta-*base_address);
									fprintf(fp2, "%3d %s %06X\n", line_num, buffer, object_code);
									if(object_code_byte+3>30 || enter_flag == 1){
										fprintf(fp3, "\nT%06X%02X", convert_dec(rev_address), object_code_len[oidx]);
										object_code_byte = 0;
										enter_flag = 0;
										oidx++;
									}
									fprintf(fp3, "%06X", object_code);
									object_code_byte+=3;
								}
								else{
									printf("%s error : range over\n", line2);
									error_flag = 1;
									break;
								
								}
							}
							else{
								printf("%s error : symbol doesn't exist in SYMTAB\n", line2);
								error_flag = 1;
								return error_flag;
							}
						}
						else if(strstr(rev_operand, ",")){
							rev_operand2 = strtok(rev_operand, ",");
							sym_node = search_symbol_table(rev_operand2, symbol_header);
							if(sym_node){
								pc = convert_dec(rev_address)+3;
								ta = sym_node->address;
						//		printf("rev_operand2 : %s\n", rev_operand2);
								if(ta-pc>=-2048 && ta-pc<=2047){
									nixbpe = 58;
									object_code = format3(hash_node->opcode, nixbpe, ta-pc);
									fprintf(fp2, "%3d %s %06X\n", line_num, buffer, object_code);
									if(object_code_byte+3>30 || enter_flag==1){
										fprintf(fp3, "\nT%06X%02X", convert_dec(rev_address), object_code_len[oidx]);
										object_code_byte = 0;
										enter_flag = 0;
										oidx++;
									}
									fprintf(fp3, "%06X", object_code);
									object_code_byte +=3;
								}
								else if(ta - *base_address>=0 && ta- *base_address<=4096){
									nixbpe = 60;
									object_code = format3(hash_node->opcode, nixbpe, ta-*base_address);
									fprintf(fp2, "%3d %s %06X\n", line_num, buffer, object_code);
									if(object_code_byte+3>30 || enter_flag==1){
										fprintf(fp3, "\nT%06X%02X", convert_dec(rev_address), object_code_len[oidx]);
										object_code_byte = 0;
										enter_flag = 0;
										oidx++;
									}
									fprintf(fp3, "%06X", object_code);
									object_code_byte+=3;
								}
								else{
									printf("%s error : range over!\n", line2);
									error_flag = 1;
									break;
								}
							}
							else{
								printf("%s error : symbol doesn't exist in SYMTAB\n", line2);
								error_flag = 1;
								return error_flag;
							}
						}

						else{
							sym_node = search_symbol_table(rev_operand, symbol_header);
					//		printf("simple addressing, symbol %s!\n", rev_operand+1);
							if(sym_node){
								pc = convert_dec(rev_address)+3;
								ta = sym_node->address;
								
								if(ta-pc>=-2048 && ta-pc<=2047){
									nixbpe = 50;
									object_code = format3(hash_node->opcode, nixbpe, ta-pc);
								//	printf("pc address : %04X object_code : %06X\n", convert_dec(rev_address), object_code);
									fprintf(fp2, "%3d %s %06X\n", line_num, buffer, object_code);
									if(object_code_byte+3>30 || enter_flag==1){
										fprintf(fp3, "\nT%06X%02X", convert_dec(rev_address), object_code_len[oidx]);
										object_code_byte = 0;
										enter_flag = 0;
										oidx++;
									}
									fprintf(fp3, "%06X", object_code);
									object_code_byte +=3;
								}
								
								else if(ta-*base_address>=0 && ta-*base_address<=4096){
								//	disp = ta-*base_address;
									nixbpe = 52;
									object_code = format3(hash_node->opcode, nixbpe, ta-*base_address);
									fprintf(fp2, "%3d %s %06X\n", line_num, buffer, object_code);
									if(object_code_byte+3>30 || enter_flag==1){
										fprintf(fp3, "\nT%06X%02X", convert_dec(rev_address), object_code_len[oidx]);
										object_code_byte = 0;
										enter_flag = 0;
										oidx++;
									}
									fprintf(fp3, "%06X", object_code);
									object_code_byte +=3;
								}
								else{
								//	printf("%s  disp : %d  target address : %d error!\n", buffer, disp, ta);
									error_flag = 1;
									break;
								}
							}
							else{
								printf("%s error : symbol doesn't exist in SYMTAB\n", line2);
								error_flag = 1;
								break;
							}

						}
					}

					line_num = line_num+5;
				}

			}//else if(rev_operator[0]!='+')
			else if(rev_operator[0] == '+'){
				hash_node = return_opcode_node(hash_header, rev_operator+1);
				if(hash_node){
					if(strcmp(hash_node->ss, "3/4")==0){
						if(rev_operand[0]=='#'){
							sym_node = search_symbol_table(rev_operand+1, symbol_header);
							if(sym_node){
								
								ta = sym_node->address;
								nixbpe = 17;
								object_code = format4(hash_node->opcode, nixbpe, ta);
								fprintf(fp2, "%3d %s %08X\n", line_num, buffer, object_code);
								if(object_code_byte+4>30 || enter_flag ==1){
									fprintf(fp3, "\nT%06X%02X", convert_dec(rev_address), object_code_len[oidx]);
									object_code_byte = 0;
									enter_flag = 0;
									oidx++;
								}
								modicode[midx] = convert_dec(rev_address)+1;
								midx++;
								fprintf(fp3, "%08X", object_code);
								object_code_byte += 4;

							}//if(sym_node)
							else{
								constant = char_dec(rev_operand+1);
								nixbpe = 17;
								object_code = format4(hash_node->opcode, nixbpe, constant);
								fprintf(fp2, "%3d %s %08X\n", line_num, buffer, object_code);
								if(object_code_byte+4>30 || enter_flag==1){
									fprintf(fp3, "\nT%06X%02X", convert_dec(rev_address), object_code_len[oidx]);
									object_code_byte = 0;
									enter_flag = 0;
									oidx++;
								}
								fprintf(fp3, "%08X", object_code);
								object_code_byte +=4;
							}
						}//if(rev_operand[0]=='#')
						else if(rev_operand[0]=='@'){
							sym_node = search_symbol_table(rev_operand+1, symbol_header);
							if(sym_node){
								ta = sym_node->address;
								nixbpe = 33;
								object_code = format4(hash_node->opcode, nixbpe, ta);
								fprintf(fp2, "%3d %s %08X\n", line_num, buffer, object_code);
								if(object_code_byte+4>30 || enter_flag==1){
									fprintf(fp3, "\nT%06X%02X", convert_dec(rev_address), object_code_len[oidx]);
									object_code_byte = 0;
									enter_flag = 0;
									oidx++;
								}
								modicode[midx] = convert_dec(rev_address)+1;
								midx++;
								fprintf(fp3, "%08X", object_code);
								object_code_byte+=4;
							}
							else{
								printf("%s error : symbol doesn't exist in SYMTAB\n", line2);
								error_flag = 1;
								break;
							}
						}//else if(rev_operand[0]=='@')
						else{
							sym_node = search_symbol_table(rev_operand, symbol_header);
							if(sym_node){
								ta = sym_node->address;
								nixbpe = 49;
								object_code = format4(hash_node->opcode, nixbpe, ta);
								fprintf(fp2, "%3d %s %08X\n", line_num, buffer, object_code);
								if(object_code_byte+4>30 || enter_flag == 1){
									fprintf(fp3, "\nT%06X%02X", convert_dec(rev_address), object_code_len[oidx]);
									object_code_byte = 0;
									enter_flag = 0;
									oidx++;
								}
								modicode[midx] = convert_dec(rev_address)+1;
								midx++;
								fprintf(fp3, "%08X", object_code);
								object_code_byte+=4;
							
							}
							else{
								printf("%s error : symbol doesn't exist in SYMTAB\n", line2);
								error_flag = 1;
								break;
							}
						}//else


					}//if(strcmp(hash_node->ss, "3/4")
				}//if(hash_node)
				line_num = line_num+5;
			}//else if(rev_operator[0]=='+')
						


		//	printf("%s %s %s %s\n", rev_address, rev_label, rev_operator, rev_operand);
		}//if(line[0]!='.')
	//	printf("\n");
	}
	for(i = 0; i<midx; i++){
		fprintf(fp3, "\nM%06X05", modicode[i]);
	}
	fprintf(fp3, "\nE%06X\n", first_execution_addr);

	printf("output file : [%s], [%s]\n", obj_file_name, lst_file_name);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);


	return error_flag;
}


//user input->standard input
//standard input : command_startaddress,endaddress,value 
void revise_input(char *input1, char *input2){
	int i, len1, len2, j;
	int space, comma;
	space = comma = 0;
	len2 = 0;
	len1 = strlen(input1);
	input1[len1-1] = '\0';


	for(i = 0; i<len1; i++){
		if(input1[i] != ' ' && input1[i] != '	'){
			input2[len2] = input1[i];
			len2++;
			
		}
		else if(input1[i] == ' '||input1[i]=='	'){
			if(input1[i-1] != ' ' && input1[i+1] != ',' && input1[i-1] != ',' && i-1>=0 && i+1<len1 && input1[i-1] != '	')
				input2[len2++] = '_';
		}
	
		
	}
	
	if(input2[len2-2] == '_')
		input2[len2-2] = '\0';

	for(i = 0; i<len2; i++){
		if(input2[i] == '_' && i+1 < len2 && input2[i+1] == ','){
			for(j = i; j<len2; j++){
				input2[j] = input2[j+1];
			}
		}
	}
}

//determine mode for user input
int mode(char *input){
	int result, comma, underbar, character;
	int i, len;
	int comma1, character1;
	char *token, *token2;
	comma = result = 0;
	comma1 = 0;
	underbar = character = character1 = 0;



	len = strlen(input);
	if(input[0] == '\0')
		result = 0;
	else{
	
		for(i = 0; i<len; i++){
			if(input[i] == ','){
				comma++;
				comma1 = i;
				if(input[i+1] != '\0')
					character++;
			}

			else if(input[i] == '_')
				underbar++;
		}	
	
		if(input[comma1+1]!='\0')
			character1++;

		token = strtok(input, "_");


		if(strcmp(token, "help")==0 || strcmp(token, "h")==0)
			result = 1;
		else if(strcmp(token, "dir")==0 || strcmp(token, "d")==0)
			result = 2;
		else if(strcmp(token, "quit")==0 || strcmp(token, "q")==0)
			result = 3;
		else if(strcmp(token, "history")==0 || strcmp(token, "hi")==0)
			result = 4;
		else if(strcmp(token, "dump")==0 || strcmp(token, "du")==0){
			if(comma==0 && underbar ==0)
				result = 5;
			else if(comma==0 && underbar > 0)
				result = 6;
			else if(comma == 1 && underbar ==1&&character > 0)
				result = 7;
		}
		else if(strcmp(token, "edit")==0 || strcmp(token, "e")==0){
			if(comma==1 && underbar==1&&character>0)
				result = 8;
		}
		else if(strcmp(token, "fill")==0 || strcmp(token, "f")==0){
			if(comma==2&&character1>0) 
				result = 9;
		}
		else if(strcmp(token, "reset")==0)
			result = 10;
		else if(strcmp(token, "opcode")==0)
			result = 11;
		else if(strcmp(token, "opcodelist")==0)
			result = 12;
		else if(strcmp(token, "type")==0)
			result = 13;
		else if(strcmp(token, "symbol")==0)
			result = 14;
		else if(strcmp(token, "assemble")==0)
			result = 15;
		else if(strcmp(token, "progaddr")==0)
			result = 16;
		else if(strcmp(token, "loader")==0)
			result = 17;
		else if(strcmp(token, "run")==0)
			result = 18;
		else if(strcmp(token, "bp")==0)
			result = 19;
		
	}
	return result;
}
void save_progaddr(char *input, int *progaddr){
	char *token1, *token2;
	token1 = strtok(input, "_");
	token2 = strtok(NULL, "");
	*progaddr = convert_dec(token2);
	printf("Program starting address set to %#x\n", *progaddr);
}
ext_symbol *create_ext_symbol_node(char *symbol, int address, int Length){
	ext_symbol *tmp;
	tmp = (ext_symbol*)malloc(sizeof(ext_symbol));
	strcpy(tmp->name, symbol);
	tmp->addr = address;
	tmp->length = Length;
	tmp->link = NULL;
//	printf("%s %x %x\n", tmp->name, tmp->addr, tmp->length);
	return tmp;
}
void make_estab(ext_symbol **header, char *symbol, int address, int Length){
	int index = 0;

	ext_symbol *newnode;
	ext_symbol *pointer;
	char *ssymbol;
	ssymbol = strtok(symbol, " \n");
	index = hash_function(ssymbol);
	newnode = create_ext_symbol_node(ssymbol, address, Length);
//	printf("%s %x %x\n", newnode->name, newnode->addr, newnode->length);
	
	
	if(header[index] == NULL){
		header[index] = newnode;
	//	printf("%s %x %X\n", header[index]->name, header[index]->addr, header[index]->length);
	}

	else{
		pointer = header[index];
		while(pointer->link!=NULL){
			pointer = pointer->link;
		}
		pointer->link = newnode;
	}
}
ext_symbol *search_estab(ext_symbol **header, char *symbol){
	int hash_key;
	ext_symbol *ptr;
	ext_symbol *tmp = NULL;
	hash_key = hash_function(symbol);
	
	ptr = header[hash_key];

	while(ptr != NULL){
		if(strcmp(ptr->name, symbol)==0){
			tmp = ptr;
			break;
		}
		ptr = ptr->link;
	}
	return tmp;
}
void free_sorted_estab_node(ext_symbol **list){
	ext_symbol *tmp;
	while(*list){
		tmp = *list;
		*list = (*list)->link;
		free(tmp);
	}
}
void print_estab(ext_symbol **header){
	int i;
	int total_length = 0;
	ext_symbol *pointer=NULL;//hash table 에서 움직이는 포인터
	ext_symbol *new_list=NULL;
	ext_symbol *newnode;
	ext_symbol *cur_ptr;//new_list에서 움직이는 포인터
	ext_symbol *prev=NULL;
	for(i = 0; i<20; i++){
		pointer = header[i];
		while(pointer!=NULL){
			newnode = create_ext_symbol_node(pointer->name, pointer->addr, pointer->length);

			if(new_list==NULL){
				new_list = newnode;
	//			printf("%s %x %x\n", new_list->name, new_list->addr, new_list->length);
			}
			else{
				cur_ptr = new_list;
				if(newnode->addr<new_list->addr){
					newnode->link = new_list;
					new_list = newnode;
	//				printf("%s %x %x\n", new_list->name, new_list->addr, new_list->length);
				}
							
				else{
					while(1){
						if(newnode->addr>cur_ptr->addr){
							if(cur_ptr->link == NULL){
								cur_ptr->link = newnode;
								break;
							}
							prev = cur_ptr;
							cur_ptr = cur_ptr->link;
						}
						else if(newnode->addr<=cur_ptr->addr){
							prev->link = newnode;
							newnode->link = cur_ptr;
							break;
						}
					}
		//			prev->link = newnode;
		//			newnode->link = cur_ptr;
		//			printf("%s %x %x\n", prev->name, prev->addr, prev->length);
				}
			}
			pointer = pointer->link;
		}		
		
	}


	printf("control\t\tsymbol\t\taddress\t\tlength\n");
	printf("section\t\tname\n");		
	printf("--------------------------------------------------------\n");
	while(new_list){
		if(new_list->length!=0){
			printf("%s\t\t\t\t%04X\t\t%04X\n", new_list->name, new_list->addr, new_list->length);
			total_length = total_length+new_list->length;
		}
		else if(new_list->length==0){
			printf("\t\t\%s\t\t%04X\t\t\t\n", new_list->name, new_list->addr);
			total_length = total_length+new_list->length;
		}
		new_list = new_list->link;
	}
	printf("--------------------------------------------------------\n");
	printf("\t\t\t\ttotal length\t%X\n", total_length);
	free_sorted_estab_node(&new_list);
	
}

int linking_loader_pass1(char *filename, ext_symbol **header, int *csaddr){
	char line[256];
	FILE *fp = fopen(filename, "r");
	int flag = 0;
	int cs_length;
	int sym_addr;
	//반복문을 위한 index
	int i;
	if(fp == NULL){
		printf("file open error\n");
		return 1;
	}

	while(1){

		if(fgets(line, sizeof(line), fp)==NULL)
			break;
		char symname[6];
		char llength[6];
		char aaddr[6];
		if(line[0]=='H'){
			strncpy(llength, line+13, 6);
			sscanf(llength, "%X", &cs_length);
			strncpy(symname, line+1, 6); 
			make_estab(header, symname, *csaddr, cs_length);
		}
		while(line[0] != 'E'){
			if(fgets(line, sizeof(line), fp) == NULL)
				break;

			else if(line[0]=='D'){
				for(i = 1; i<strlen(line)-1; i = i+12){
					strncpy(symname, line+i, 6);
					strncpy(aaddr, line+i+6, 6);
					sscanf(aaddr, "%X", &sym_addr);
	//			printf("%s %x\n", symname, sym_addr);
					if(search_estab(header, symname)==NULL){
	//					printf("%s %x %x\n", symname, sym_addr, 0);
						sym_addr = *csaddr+sym_addr;
						make_estab(header, symname, sym_addr, 0);
					}
					else if(search_estab(header, symname)){
						printf("pass1 error : external symbol duplicate!\n");
						flag = 1;
						break;
					}
				}
			}
		}
	}
//	printf("cslth : %04X\n", cs_length);
	*csaddr = *csaddr+cs_length;
	fclose(fp);
	return flag;
}

int linking_loader_pass2(unsigned char **memory, char *filename, ext_symbol **header, int *csaddr){
	char line[256];//object file에서 한 줄씩 읽을 때 
	int cslth;
	char symbol[6], iindex[2], *ssymbol;
	char Addr[6], Length[2], objcode[2];//T record에서 시작 위치와 길이, object code를 받기 위해서 선언한 변수
	FILE *fp;
	int flag;
	int addr, len, index, i;
	int x, y;//memory의 index
	int j, value;//t record에서 object code를 2개씩 읽기 위해서 선언한 변수
	int length;//t record에서 object code들의 길이를 저장하기 위해서 선언한 변수
	int sum, shift;//m record에서 memory에 있는 object code들의 합을 구하기 위해서 선언한 변수
	//shift는 m record에서 값들을 shift해주기 위해서 선언한 변수
	ext_symbol *node;
	int ext_reference[10]={-1};
	char token[8] = {0};
	char Cslth[6] = {0};
	addr = 0;
	ext_reference[1] = *csaddr;
	flag = 0;
	shift = 16;


	fp = fopen(filename, "r");
	if(fp==NULL){
		printf("file open error!\n");
	}
//	printf("ext reference address : %X\n", ext_reference[1]);
	while(fgets(line, sizeof(line), fp)!= NULL){
		if(line[0]=='H'){
			strncpy(Cslth, line+13, 6);
			sscanf(Cslth, "%X", &cslth);
	//		printf("cslth : %04X\n", cslth);
		}
//		printf("line1 : %s\n", line);
		while(line[0]!='E'){
			if(fgets(line, sizeof(line), fp)==NULL)
				break;
//			printf("line2 : %s\n", line);

			if(line[0] == 'R'){
				len = strlen(line);
				line[len-1] = '\0';
				for(i = 1; i<len-1; i = i+8){
					strncpy(token, line+i, 8);
					strncpy(iindex, token, 2);
					strncpy(symbol, token+2, 6);
					sscanf(iindex, "%X", &index);
	//				printf("token : %s\n",token); 
					ssymbol = strtok(symbol, " ");
				//	printf("symbol : %s, index : %X\n", symbol, index);
					node = search_estab(header, ssymbol);
	//				printf("symbol : %s,index : %x\n", node->name, node->addr);
					
					if(node==NULL){
						printf("external symbol not in estab\n");
						flag = 1;
						break;
					}
					ext_reference[index] = node->addr;
	//				printf("ext reference address : %X\n", ext_reference[index]);
				}
			}
			
			else if(line[0] == 'T'){
				j = 0;
				len = strlen(line);
				line[len-1] = '\0';
				strncpy(Addr, line+1, 6);
				strncpy(Length, line+7, 2);
				sscanf(Addr, "%X", &addr);
				sscanf(Length, "%X", &length);
		//		printf("Addr : %X, Length : %d\n", addr, length);
				addr = addr+*csaddr;
				for(i = 0; i<length; i++){
					strncpy(objcode, line+9+j, 2);
		//			printf("%s", objcode);
					value = convert_dec(objcode);
		//			printf("%02X\n", value);
					x = addr/16;
					y = addr%16;
					memory[x][y] = value;
					j = j+2;
					addr = addr+1;
				}
		//		printf("\n");
			}
			else if(line[0] == 'M'){
				sum = 0;
				strncpy(Addr, line+1, 6);
				strncpy(Length, line+7, 2);
				strncpy(iindex, line+10, 2);
				sscanf(Addr, "%X", &addr);
				sscanf(Length, "%X", &length);
				sscanf(iindex, "%X", &index);
				addr = addr+ *csaddr;
				if((ext_reference[index] != -1)||(ext_reference[index]==-1&&line[9]=='\n')){
	//				printf("ext_reference[%d] = %X\n", index, ext_reference[index]);
					if(length%2==0){
						for(i = addr; i<addr+length/2; i++){
							sum = sum<<8;
							x = i/16;
							y = i%16;
							sum = sum+memory[x][y];	
						}
						if(sum>>23==1){
							sum =sum+0xFF000000;
						}
					
					//	printf("addr : %X sum = %06X\n", addr, sum);
					}
					
					else if(length%2==1){
						for(i = addr; i<addr+length/2+1; i++){
							sum = sum<<8;
							x = i/16;
							y = i%16;
							sum = sum+memory[x][y];
						}
						if(sum>>23==1){
							sum = sum+0xFF000000;
						}

					//	printf("addr : %X sum = %06X\n", addr, sum);
					}
					
	//				printf("addr : %X sum : %06X, %d\n", addr, sum, sum);
					if(line[9]=='+')
						sum = sum+ext_reference[index];
					else if(line[9] == '-')
						sum = sum-ext_reference[index];
					else if(line[9] == '\n')
						sum = sum+ext_reference[1];
					
					sum = sum&0xFFFFFF;

			//		printf("addr : %X sum = %06X\n", addr, sum);	
					if(length%2==0){
						shift = 16;
						for(i = addr; i<addr+length/2; i++){
							x = i/16; 
							y = i%16;
							memory[x][y] = (sum>>shift)&0xFF;
					//		printf("%02X", memory[x][y]);
							shift = shift-8;
						}
					}
					else if(length%2==1){
						shift = 16;
						for(i = addr; i<addr+length/2+1; i++){
							x = i/16;
							y = i%16;
							memory[x][y] = (sum>>shift)&0xFF;
					//		printf("%02X", memory[x][y]);
							shift = shift-8;
						}
					}
				//	printf("addr : %X sum = %06X\n", addr, sum);

				}
				else if(ext_reference[index]==-1 && line[9] != '\n'){
						printf("linking loader pass2 error\n");
						flag = 1;
						break;
				}

			}


		}
	}
	*csaddr = *csaddr+cslth;
	fclose(fp);
	return flag;
}


void store_operation(unsigned char **memory, int ta, int value){
	memory[ta/16][ta%16] = value/(16*16*16*16);
	memory[(ta+1)/16][(ta+1)%16] = (value%(16*16*16*16))/(16*16);
	memory[(ta+2)/16][(ta+2)%16] = (value%(16*16*16*16))%(16*16);
}
int decision_xbp(unsigned char **memory, int current_loc){
	int k = current_loc;
	int x = (k+1)/16;
	int y = (k+1)%16;
	int xbp = -1;
	int content = memory[x][y]/16;
	
	if(content==0)
		xbp = 0;
	else if(content==1)
		xbp = 1;
	else if(content==2)
		xbp = 2;
	else if(content==4)
		xbp = 4;
	else if(content==8)
		xbp = 8;
	else if(content==10)
		xbp = 10;
	else if(content==12)
		xbp = 12;
	return xbp;
}
int get_target_addr(unsigned char **memory, int format, int pc, int reg[10]){
	int disp, ta, sign_flag;
	int xbp = decision_xbp(memory, pc);
	sign_flag = 0;
	if(format==4){
		disp = memory[(pc+3)/16][(pc+3)%16]+memory[(pc+2)/16][(pc+2)%16]*16*16+(memory[(pc+1)/16][(pc+1)%16]%16)*16*16*16*16;
	}
	else if(format==3)
		disp = memory[(pc+2)/16][(pc+2)%16]+(memory[(pc+1)/16][(pc+1)%16]%16)*16*16;
		

	if(((memory[(pc+1)/16][(pc+1)%16]%16)>>3)==0x0001)
		sign_flag=1;

	if(xbp == 0)
		ta = disp;
	else if(xbp==1)
		ta = disp;
	else if(xbp==2)
		ta = disp+reg[PC]+format;
	else if(xbp==4)
		ta = disp+reg[B];
	else if(xbp==8)
		ta = disp+reg[X];
	else if(xbp==10)
		ta = disp+reg[PC]+reg[X];
	else if(xbp==12)
		ta = disp+reg[B]+reg[X];

	if(sign_flag==1){
		ta = ta+0xF000;
		ta = ta&0x0FFFF;
	}
//	printf("format : %d, sign : %d\n", format, sign_flag);
//	printf("xbp : %d\n", xbp);
//	printf("ta in function : %06X\n", ta);
	return ta;

}
int bp_clear_or_set(char *input){
	char *token1, *token2;
	int flag = 0;

	token1 = strtok(input, "_");
	token2 = strtok(NULL, "_");


	if(token2){
		if(strcmp(token2, "clear")==0)
			flag = 0;
		else
			flag = 1;
	}
	else if(token2==NULL)
		flag = 2;

//	printf("flag : %d\n", flag);
	return flag;
}
void bp_set(int *bp, char *input, int *bp_count){
	char *token1, *token2;
	int addr;
	

	token1 = strtok(input, "_");
	token2 = strtok(NULL, "_");
//	printf("token2 : %s\n", token2);	
	sscanf(token2, "%X", &addr);
//	printf("addr : %04X\n", addr);
	if(*bp_count==100){
		printf("full bp array\n");
	}
	else{
		bp[*bp_count]=addr;
		(*bp_count)++;
	}
	printf("[ok] create breakpoint %04X\n", addr);
}
void bp_print(int *bp, int *bp_count){
	int i;
	if(*bp_count>0){
		printf("breakpoints\n");
		printf("-----------\n");
		for(i = 0; i<*bp_count; i++){
			printf("%04X\n", bp[i]);
		}
	}
	else if(*bp_count==0)
		printf("no breakpoints set\n");
}
void bp_clear(int *bp, int *bp_count){
	int i;
	for(i = 0; i<*bp_count; i++){
		bp[i] = 0;
	}
	*bp_count=0;
	printf("[ok] clear all breakpoints\n");
}


int run(unsigned char **memory, int progaddr, int endaddr, int reg[10], int *bp, int *bp_count, int *first_run_flag){
	int opcode, ni, xbp, format;
	int pc;
	int r1, r2;
	int error_flag = 0;
	int ta, value;
	int jump_flag, bp_flag, pc_in_bp_flag;
	int k;
	int break_point;
	int i;


	
	
	if((*first_run_flag)==0){
		reg[PC] = progaddr;
		reg[L] = endaddr;
		(*first_run_flag)=1;
	}
//	printf("reg[PC] : %04X, reg[L] = %04X\n", reg[PC], reg[L]);
	while(reg[PC]<endaddr){
		pc = reg[PC];
	//	printf("program counter : %04X\n", pc);
		ni = decision_ni(memory, pc);
		opcode = decision_opcode(memory, pc, ni);
		
	/*	for(i = 0; i<(*bp_count); i++){
			if(bp[i]==pc){
				pc_in_bp_flag=1;
				break;
			}
		}
		if(pc_in_bp_flag==1){
			bp_flag = 1;
			break_point = pc;
	
		}*/

		if(opcode==0xA0 || opcode==0xB4 || opcode==0xB8){
			format = 2;
			r1 = memory[(pc+1)/16][(pc+1)%16]/16;
			r2 = memory[(pc+1)/16][(pc+1)%16]%16;
			if(r1<0 || r1>9 || r1==7){
				printf("error : first register is invalid register\n");
				error_flag = 1;
				break;
			}
			else if(r2<0 || r2>9 || r2==7){
				printf("error : second register is invalid register\n");
				error_flag = 1;
				break;
			}
			
		}
		else{
			if(decision_format(memory, pc)==4)
				format = 4;
			else if(decision_format(memory, pc)==3)
				format = 3;
			ta = get_target_addr(memory, format, pc, reg);
			k = ta;
			//immediate addressing
			if(ni==1)
				value = ta;
			else{
				if(ta<0||ta>endaddr){
					printf("error : target address range over\n");
					break;
				}
				//indirect addressing
				value = memory[(ta+2)/16][(ta+2)%16]+memory[(ta+1)/16][(ta+1)%16]*16*16+memory[ta/16][ta%16]*16*16*16*16;
				if(ni==2)
					ta = value;
			}
			
		}
		switch(opcode){
			//LDA
			case 0x00 : 
				reg[A] = value;
				break;
			//LDB
			case 0x68 : 
				reg[B] = value;
				break;
			//LDT
	
			case 0x74 : 
				reg[T] = value;
				break;
			//LDCH
			case 0x50 : 
				reg[A] = value/(16*16*16*16);
				break;
			//STA
			case 0x0C : 
				store_operation(memory, ta, reg[A]);
				break;
			//STX
			case 0x10 : 
				store_operation(memory, ta, reg[X]);
				break;
			//STL
			case 0x14 :
				store_operation(memory, ta, reg[L]);
				break;
			//STCH
			case 0x54 :
				memory[ta/16][ta%16] = reg[0]%256;
				break;
			//J
			case 0x3C :
			//	printf("%02X%02X%02X\n", memory[k/16][k%16], memory[(k+1)/16][(k+1)%16], memory[(k+2)/16][(k+2)%16]);
				reg[PC] = ta;
				jump_flag = 1;
				break;
			//JSUB
			case 0x48 : 
				reg[L] = reg[PC] + format;
				reg[PC] = ta;
				jump_flag = 1;
				break;
			//JLT
			case 0x38 : 
				if(reg[SW]==2){
					printf("error : condition doesn't set\n");
					error_flag = 1;
				}
				else if(reg[SW]==-1){
					reg[PC] = ta;
					jump_flag = 1;
				}
				break;
			//JEQ
			case 0x30 : 
				if(reg[SW]==2){
					printf("error : condition doesn't set\n");
					error_flag = 1;
				}
				else if(reg[SW]==0){
					reg[PC] = ta;
					jump_flag = 1;
				}
				break;
			//RSUB
			case 0x4C : 
				reg[PC] = reg[L];
				jump_flag = 1;
				break;
			//COMP
			case 0x28 : 
				if(reg[A]>value)
					reg[SW] = 1;
				else if(reg[A] == value)
					reg[SW] = 0;
				else
					reg[SW] = -1;
//				printf("reg[A] = %04X\n", reg[A]);
//				printf("%04X\n", value);
//				printf("%04X\n", ta);
				break;
			//COMPR
			case 0xA0 : 
				if(reg[r1]>reg[r2])
					reg[SW] = 1;
				else if(reg[r1]==reg[r2])
					reg[SW] = 0;
				else
					reg[SW] = -1;
				break;
			//CLEAR
			case 0xB4 : 
				reg[r1] = 0;
				break;
			//TIXR
			case 0xB8 : 
				reg[X] = reg[X]+1;
				if(reg[X]>reg[r1])
					reg[SW] = 1;
				else if(reg[X]==reg[r1])
					reg[SW] = 0;
				else
					reg[SW] = -1;
				break;
			//TD
			
			case 0xE0 : 
				reg[SW] = -1;
				break;
				
			//RD
			case 0xD8 : 
				reg[A] = 0;
				break;
			//WD
	/*		case 0xDC : 
				reg[X] = reg[T];
				break;*/

		}
		if(jump_flag==0)
			reg[PC] = reg[PC]+format;
		jump_flag = 0;
		value = 0;

		for(i = 0; i<(*bp_count); i++){
			if(reg[PC]==bp[i]){
				pc_in_bp_flag=1;
				break;
			}
		}
		if(pc_in_bp_flag==1){
			bp_flag=1;
			break_point = reg[PC];
		}


		if(bp_flag==1)
			break;
	
//		printf("pc : %04X\n", pc);
//		printf("reg pc : %04X\n", reg[PC]);
//		printf("opcode : %02X\n", opcode);
//		printf("reg L : %04X\n", reg[L]);
//		printf("reg SW : %04X\n", reg[SW]);
/*		printf("target address : %04X\n", ta);
		printf("A : %06X X : %06X\n", reg[A], reg[X]);
		printf("L : %06X PC: %06X\n", reg[L], reg[PC]);
		printf("B : %06X S : %06X\n", reg[B], reg[S]);
		printf("T : %06X\n", reg[T]);
		printf("SW : %06X\n\n", reg[SW]);*/

	//	printf("end program\n");
//		if(pc==0x5036)
//			break;
	}
	printf("A : %06X X : %06X\n", reg[A], reg[X]);
	printf("L : %06X PC: %06X\n", reg[L], reg[PC]);
	printf("B : %06X S : %06X\n", reg[B], reg[S]);
	printf("T : %06X\n", reg[T]);

	if(bp_flag==1){
		printf("Stop at checkpoint[%04X]\n", break_point);
		bp_flag = 0;
	}
	else if(bp_flag==0){
		printf("End program\n");
		(*first_run_flag)=0;
	}
	
	return error_flag;
}


int decision_opcode(unsigned char **memory, int current_loc, int ni){
	int result;
	result = memory[current_loc/16][current_loc%16]-ni;
	return result;
}
int decision_format(unsigned char **memory, int current_loc){
	if((memory[(current_loc+1)/16][(current_loc+1)%16]/16)%2==1)
		return 4;
	else
		return 3;
}

int decision_ni(unsigned char **memory, int current_loc){
	int k = current_loc;
	int ni = -1;

	//n = 0, i = 0, sic machine
	if(memory[k/16][k%16]%4==0){
		ni = 0;
	}
	//n = 0, i = 1, immediate addressing
	else if(memory[k/16][k%16]%4==1){
		ni = 1;
	}
	//n = 1, i = 0, idirect addressing
	else if(memory[k/16][k%16]%4==2){
		ni = 2;
	}
	//n = 1, i = 1, simple addressing
	else if(memory[k/16][k%16]%4==3){
		ni = 3;
	}


	return ni;


}

//free memory array
void free_memory_array(unsigned char **memory){
	int i;
	for(i = 0; i<65536; i++)
		free(memory[i]);
	free(memory);
}
//free history linked list 
void free_history_node(history **head){
	history *tmp;
	
	while(*head){
		tmp = *head;
		*head = (*head)->link;
		free(tmp);
	}
}
//free hash table 
void free_hash_node(hash **head){
	int i;
	hash *tmp;
	for(i = 0; i<20; i++){
		while(*head){
			tmp = head[i];
			head[i] = head[i]->link;
			free(tmp);
		}
	}
}
void free_symbol_node(symbol **head){
	int i;
	symbol *tmp;
	for(i = 0; i<26; i++){
		while(*head){
			tmp = head[i];
			head[i] = head[i]->link;
			free(tmp);
		}
	}
}
void free_ext_symbol_node(ext_symbol **head){
	int i;
	ext_symbol *tmp;
	for(i = 0; i<20; i++){
		while(head[i]){
			tmp = head[i];
			head[i] = head[i]->link;
			free(tmp);
		}
	}
}


//main for program 
int main(void){
	char *input;
	char *std_input, *std_input2, *std_input3, *std_input4, *std_input5;
	char *aa, *bb;
	//load를 해줄 obj file들의 이름
	char *objname[3], *ttemp;
	int len, result, i, dump_start;
	//std_input2's length
	int len2;
	int kkk;//linking loader pass1이 잘 되었는지 확인하기 위해 선언한 flag
	history *head;
	history *tmp;
	unsigned char **memory;
	FILE *fp1;
	int bp[100] = {0};//break point	
	symbol *symbol_head[26];
	hash *hash_head[20];
	hash *temp;

	//estab의 head
	ext_symbol *ext_symbol_header[20];
	
	int symbol_flag = 0;
	int length=0;
	int base_address = -1;
	int object_code_len[100]={0};
	int reg[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 2};

	//program의 시작 주소
	int progaddr = 0;
	//control section의 시작주소
	int csaddr;
	int endaddr;
	int bp_clear_flag, first_run_flag;
	int bp_count;


	fp1 = fopen("opcode.txt", "r");
	head = (history*)malloc(sizeof(history));
	head->link = NULL;
	head->index = 0;
	bp_count=0;
	dump_start = 0;
	first_run_flag = 0;
		
	for(i = 0; i<20; i++){
		hash_head[i] = NULL;
		ext_symbol_header[i] = NULL;
	}
	for(i = 0; i<26; i++){
		symbol_head[i] = NULL;
	}
	
	hashtable_made(hash_head, fp1);
	
	memory = (unsigned char**)calloc(65536, sizeof(unsigned char*));

	for(i = 0; i<65536; i++)
		memory[i] = (unsigned char*)calloc(16, sizeof(unsigned char));
	
	while(1){
		printf("sicsim>");
		input = (char*)malloc(sizeof(char)*100);
		fgets(input, sizeof(char)*100, stdin);
		len = strlen(input);
	
		csaddr = progaddr;
		std_input = (char*)malloc(sizeof(char)*101);
		revise_input(input, std_input);
		
		len2 = strlen(std_input);
		std_input2 = (char*)malloc(sizeof(char)*len2);
		std_input3 = (char*)malloc(sizeof(char)*len2);
		std_input4 = (char*)malloc(sizeof(char)*len2);
		std_input5 = (char*)malloc(sizeof(char)*len2);
		strcpy(std_input2, std_input);
//		printf("std_input : %s\n", std_input2);
		strcpy(std_input3, std_input);
		strcpy(std_input4, std_input);
		strcpy(std_input5, std_input);
//		printf("input : %s\n", std_input4);
		result = mode(std_input);
		aa = strtok(std_input3, "_");
		bb = strtok(NULL, "");//file name


//		printf("%s %s\n", aa, bb);
		//print help

	//	ttemp = strtok(std_input4, "_");
	//	objname1 = strtok(NULL, "_");
	//	objname2 = strtok(NULL, "_");
	//	objname3 = strtok(NULL, "");
		
		
		if (result == 1) {
			tmp = create_history_node(input);
			history_made(&head, tmp);
			print_help();
		}

		//print directory
		else if (result == 2) {
			tmp = create_history_node(input);
			history_made(&head, tmp);
			print_directory();
		}

		//quit
		else if (result == 3) {
			free(input);
			free(std_input);
			free(std_input2);
			free_hash_node(hash_head);
			free_symbol_node(symbol_head);
			free_history_node(&head);
			free_memory_array(memory);
	/*		if(remove("intermediate.txt")==-1)
				printf("file remove error!\n");*/
			break;
		}

		//print history
		else if (result == 4) {
			tmp = create_history_node(input);
			history_made(&head, tmp);
			print_history(head);
		}

		//print dump 1
		else if (result == 5) {
			tmp = create_history_node(input);
			history_made(&head, tmp);
			print_dump1(memory, &dump_start);
		}

		//print dump 2
		else if (result == 6 && !print_dump2(memory, std_input2, &dump_start)) {
			tmp = create_history_node(input);
			history_made(&head, tmp);
		
		}

		//print dump3
		else if (result == 7 && !print_dump3(memory, std_input2, &dump_start)) {
			tmp = create_history_node(input);
			history_made(&head, tmp);
		
		}

		//edit
		else if (result == 8 && !edit(memory, std_input2)) {
			tmp = create_history_node(input);
			history_made(&head, tmp);
		}

		//fill
		else if (result == 9 && !fill(memory, std_input2)) {
			tmp = create_history_node(input);
			history_made(&head, tmp);
		}
		
		//reset
		else if (result == 10) {
			tmp = create_history_node(input);
			history_made(&head, tmp);
			reset(memory);
		}

		//opcode mnemonic
		else if (result == 11&&search_opcode_mnemonic(hash_head, std_input2)<0) {
			tmp = create_history_node(input);
			history_made(&head, tmp);
		}
		//opcodelist
		else if (result == 12) {
			tmp = create_history_node(input);
			history_made(&head, tmp);			
			opcodelist_print(hash_head);
		
		}
		else if(result == 13){
			tmp = create_history_node(input);
			history_made(&head, tmp);
			type_filename(bb);
		}
		else if(result==14){
			tmp = create_history_node(input);
			history_made(&head, tmp);
			if(symbol_flag==1)
				print_symbol_table(symbol_head);
			else
				printf("because of assemble error, we can't make symbol_table\n");
		}
		
		else if(result==15 && !pass1(bb, &length, &base_address, symbol_head, hash_head, object_code_len)){
			if(!pass2(bb, &length, &base_address, symbol_head, hash_head, object_code_len)){
				tmp = create_history_node(input);
				history_made(&head, tmp);
				symbol_flag = 1;

			}
		}//	aa = strtok(std_input2, "_");
		//	bb = strtok(NULL, "");
		//	printf("%s %s\n", aa, bb);
	//		pass1(bb,&length, &base_flag, symbol_head, hash_head); 
		
		else if(result == 16){
			save_progaddr(std_input2, &progaddr);
		//	csaddr = progaddr;
		}
		else if(result == 17){
		//	if(objname1 && !objname2 && !objname3 && !linking_loader_pass1(objname1, ext_symbol_header, &csaddr)){
			ttemp = strtok(std_input4, "_");
			objname[0] = strtok(NULL, "_");
			objname[1] = strtok(NULL, "_");
			objname[2] = strtok(NULL, "_");
			kkk = 1;
			for(i = 0; i<3; i++){
			//	printf("object name : %s\n", objname[i]);
				if(objname[i]){
					if(!linking_loader_pass1(objname[i], ext_symbol_header, &csaddr)){ 
							kkk = 0;
					}
					else
						break;
				}
				else
					break;
			}
			csaddr = progaddr;
//			printf("csaddr : %04X\n", csaddr);
			if(kkk == 0){
				for(i = 0; i<3; i++){
					if(objname[i]){
						if(!linking_loader_pass2(memory, objname[i], ext_symbol_header, &csaddr)){
							kkk = 0;
						}
						else
							break;
					}
					else
						break;
				}
			}	
		//	else if(objname1 && objname2 && !objname3 && !linking_loader_pass1(objname1, ext_symbol_header, &csaddr)&& !linking_loader_pass1(objname1, )
			if(kkk == 0){
				print_estab(ext_symbol_header);
				tmp = create_history_node(input);
				history_made(&head, tmp);
			}

		//	printf("loading good\n");
			endaddr = csaddr;
//			printf("endaddr : %04X\n", endaddr);
			free_ext_symbol_node(ext_symbol_header);
		}

		else if(result==18&&!run(memory, progaddr, endaddr, reg, bp, &bp_count, &first_run_flag)){
			//	printf("good\n");
			tmp = create_history_node(input);
			history_made(&head, tmp);
		}


		else if(result==19){
			bp_clear_flag = bp_clear_or_set(std_input2);
			if(bp_clear_flag==0){
			//	printf("bp clear\n");
				bp_clear(bp, &bp_count);
			}
			else if(bp_clear_flag==1){
			//	printf("bp set\n");
				bp_set(bp, std_input5, &bp_count);
			}
			else if(bp_clear_flag==2){
				bp_print(bp, &bp_count);
			//	printf("bp print\n");
			}
			tmp = create_history_node(input);
			history_made(&head, tmp);
		}


		//wrong command
		else if(result ==0)
			printf("wrong command!\n");
		
	

	}
}






















