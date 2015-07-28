#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <stdio.h>

//Note: this filehandler will be dealing with
//converting between 8 and 16 bit codes. Not portable
//at all lol

struct Filehandler
{
	FILE *fd;
	char read_or_write;
};

struct Filehandler *filehandler_init(char *fileName, char read_or_write) {
	struct Filehandler *handler = malloc(sizeof(struct Filehandler));	

	handler->read_or_write = read_or_write;

	if (read_or_write == 'r')
		handler->fd = fopen(fileName, "r");
	else if (read_or_write == 'w')
		handler->fd = fopen(fileName, "w");
	else
		printf("error: invalid file access mode passed in");

	return handler;
}

void filehandler_write(struct Filehandler *handler, int code) {
	if (handler->read_or_write != 'w')
		printf("error: attempting to write to readonly");
	if (code < 0 || 4096 <= code)	
		printf("error: invalid code passed to filehandler_write");

	unsigned char *buffer = malloc(sizeof(unsigned char) * 2);

	buffer[0] = code & 255;
	buffer[1] = (code >> 8) & 255;
	fwrite(buffer, sizeof(unsigned char), 2, handler->fd);		

	free(buffer);
}	

int filehandler_read(struct Filehandler *handler) {
	if (handler->read_or_write != 'r')
		printf("error: attempting to read a writeonly");
	unsigned char *buffer = malloc(sizeof(unsigned char) * 2);
	if(fread(buffer, sizeof(unsigned char), 2, handler->fd) == 0) {
		free(buffer);
		return -1;
	}
	int code = buffer[0];
	code = code | (buffer[1] << 8);
	free(buffer);
		 
	return code;
}
	
void filehandler_close(struct Filehandler *handler) {
	fclose(handler->fd);
	free(handler);
}
#endif /* FILEHANDER_H */
