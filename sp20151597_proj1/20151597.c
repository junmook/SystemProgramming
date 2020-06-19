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
	

	printf("opcodelist\n");
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
	char k[100];
	char *start_point;
	char *buffer;
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
//	opcode = strtok(input, "_");
//	mnemonic = strtok(NULL, "");

	hash_key = hash_function(input);
	ptr = header[hash_key];

	while(ptr!=NULL){
		if(strcmp(ptr->instructions, input)==0){
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

		char *token, *token2;
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
		
	}

	return result;
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
//main for program 
int main(void){
	char *input;
	char *std_input, *std_input2;
	char *aa, *bb;
	int len, result, i, dump_start;
	//std_input2's length
	int len2;
	history *head;
	history *tmp;
	unsigned char **memory;
	FILE *fp1;
	hash *hash_head[20];
	hash *temp;
	fp1 = fopen("opcode.txt", "r");
	head = (history*)malloc(sizeof(history));
	head->link = NULL;
	head->index = 0;

	dump_start = 0;
		
	for(i = 0; i<20; i++){
		hash_head[i] = NULL;
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
	

		std_input = (char*)malloc(sizeof(char)*101);
		revise_input(input, std_input);


		len2 = strlen(std_input);
		std_input2 = (char*)malloc(sizeof(char)*len2);
		strcpy(std_input2, std_input);

		result = mode(std_input);
//		aa = strtok(std_input2, "_");
//		bb = strtok(NULL, "");
//		printf("%s %s\n", aa, bb);
		//print help
		
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
			free_history_node(&head);
			free_memory_array(memory);
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
		else if (result == 11&&!search_opcode_mnemonic(hash_head, std_input2)) {
			tmp = create_history_node(input);
			history_made(&head, tmp);
		}
		//opcodelist
		else if (result == 12) {
			tmp = create_history_node(input);
			history_made(&head, tmp);			
			opcodelist_print(hash_head);
		
		}

		//wrong command
		else if(result ==0)
			printf("wrong command!\n");
		
	

	}
}






















