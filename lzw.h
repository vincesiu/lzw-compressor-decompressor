#ifndef LZW_H
#define LZW_H

#include <stdio.h>
#include <string.h>
#include "filehandler.h"

struct Dictionary {
	char *dict[65536];
	int dict_length;
};


struct Dictionary *dictionary_init() {
	struct Dictionary *foo = malloc(sizeof(struct Dictionary));
	int idx;
	char *temp;
	for (idx = 0; idx < 256; idx++) {
		temp = malloc(sizeof(char));
		*temp = idx;
		foo->dict[idx] = temp;	
	}
	foo->dict_length = 256;
	return foo;
}


void dictionary_close(struct Dictionary *dict) {
	int dict_length = dict->dict_length;
	int idx;
	
	for (idx = 0; idx < dict_length; idx++) 
		free(dict->dict[idx]);

	free(dict);
}
	

int dictionary_query(struct Dictionary *dict, char *string) {
	int dict_length = dict->dict_length, idx = 0;
	
	for (idx = 0; idx < dict_length; idx++) 
		if (strcmp(string, dict->dict[idx]) == 0)
			return idx; 

	int len = strlen(string);	
	dict->dict[dict_length] = malloc(sizeof(char) * (len + 1));
	strcpy(dict->dict[dict_length], string);
	dict->dict_length++;
	
	return -1;
}

void lzw_compress(char *inputFile) {
	FILE *fd_input = fopen(inputFile, "r");
	struct Filehandler *handler_output = filehandler_init("compressedfile", 'w');
	struct Dictionary *dict = dictionary_init();
	
	int code = fgetc(fd_input);
	char *string_code = calloc(65538, sizeof(char));
	int idx = 1;
	int dictidx_cur;
	int dictidx_prev = code;
	string_code[0] = code;
	
	while ((code = fgetc(fd_input)) != EOF) {
		string_code[idx] = code;
		string_code[idx + 1] = 0;
		if ((dictidx_cur = dictionary_query(dict, string_code)) != -1) {
			idx++;
			dictidx_prev = dictidx_cur;
		}
		else {
			filehandler_write(handler_output, dictidx_prev);
			string_code[0] = code;
			string_code[1] = 0;
			idx = 1;	
			dictidx_prev = code;
		}	
	}

	filehandler_write(handler_output, dictidx_prev);

	free(string_code);
	dictionary_close(dict);
	close(fd_input);
	filehandler_close(handler_output);
}

void lzw_decompress(char *inputFile) {
	struct Filehandler *handler_input = filehandler_init(inputFile, 'r');
	struct Dictionary *dict = dictionary_init();
	FILE *fd_output = fopen("decompressedfile", "w");	
		
	int code = filehandler_read(handler_input);
	int length = 1;	
	int idx;
	char *string_write;
	char *string_code = calloc(65537, sizeof(char));	

	if (handler_input->read_or_write == 'w')
		printf("error: trying to decompress a writeonly\n");
	if (code == -1) 
		printf("error: cannot decompress empty file\n");
	
	string_code[0] = code;	
	fwrite(string_code, sizeof(char), 1, fd_output);
	
	while((code = filehandler_read(handler_input)) != -1) {
		printf("%c, %i\n", code, code);
		if (code != dict->dict_length) {
			string_write = dict->dict[code];	
			fwrite(string_write, sizeof(char), strlen(string_write), fd_output);
			string_code[length] = string_write[0];
			string_code[length+1] = 0;
			dictionary_query(dict, string_code);
			strcpy(string_code, string_write);
			length = strlen(string_write);
			string_code[length] = 0;
		}		
		else {
			string_code[length] = string_code[0];
			string_code[length + 1] = 0;
			dictionary_query(dict, string_code);
			string_write = dict->dict[code];
			fwrite(string_write, sizeof(char), strlen(string_write), fd_output);
			length++;
			string_code[length] = 0;
		}
	}	

	free(string_code);
	dictionary_close(dict);
	close(fd_output);
}



#endif /* LZW_H */
