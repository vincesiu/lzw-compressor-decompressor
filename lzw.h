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
	for (idx = 0; idx < 128; idx++) {
		temp = malloc(sizeof(char));
		*temp = idx;
		printf("%c", *temp);
		foo->dict[idx] = temp;	
	}
	foo->dict_length = 128;
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
			return 1; 

	int len = strlen(string);	
	dict->dict[dict_length] = malloc(sizeof(char) * (len + 1));
	strcpy(dict->dict[dict_length], string);
	dict->dict_length++;
	
	//printf("dictionary length: %i\n", dict->dict_length);
	return 0;
}



void lzw_decompress(struct Filehandler *handler_input) {
	struct Dictionary *dict = dictionary_init();
	FILE *fd = fopen("decompressedfile", "w");	
		
	char *string_code = calloc(65537, sizeof(char));	

	int code = filehandler_read(handler_input);
	int length = 1;	
	int idx;
	char *string_write;

	if (handler_input->read_or_write == 'w')
		printf("error: trying to decompress a writeonly");
	if (code == -1) 
		printf("error: cannot decompress empty file");
	
	string_write[0] = code;
	fwrite(string_write, sizeof(char), strlen(string_write), fd);
	string_code[0] = code;	
	
	while((code = filehandler_read(handler_input)) != -1) {
		if (code != dict->dict_length) {
			string_write = dict->dict[code];	
			fwrite(string_write, sizeof(char), strlen(string_write), fd);
			//strcpy((string_code + length), string_write);
			string_code[length] = string_write[0];
			dictionary_query(dict, string_code);
				strcpy(string_code, string_write);
				length = strlen(string_write);
				string_code[length] = 0;
		}		
		else {
			string_code[length] = string_code[0];
			dictionary_query(dict, string_code);
			string_write = dict->dict[code];
			fwrite(string_write, sizeof(char), strlen(string_write), fd);
			length++;
			string_code[length] = 0;

		}
	}	
			

	free(string_code);
	dictionary_close(dict);
	close(fd);
}



#endif /* LZW_H */
