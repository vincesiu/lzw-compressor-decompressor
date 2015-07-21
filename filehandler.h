#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <stdio.h>

//Note: this filehandler will be dealing with
//converting between 8 and 12 bit codes. Not portable
//at all lol

struct Filehandler
{
	FILE *fd;
	char read_or_write;
	char buffer;
	int flag_bufferactive;
};

void init_Filehandler(Filehandler handler, char *fileName, char read_or_write) {
	Filehandler.read_or_write = read_or_write;

}

void filehandler_write(Filehandler handler, int code) {
	if (handler.read_or_write != 'w')
		printf("error: attempting to write to readonly");
	if (code < 0 || 4096 <= code)	
		printf("error: invalid code passed to filehandler_write");
	
	char writebuffer[2];
	int writebufferSize;
	if (flag_bufferactive == 1) {
		writebuffer[0] = (code << 4) | handler.buffer;
		writebuffer[1] = code >> 4;
		writebufferSize = 2;
	}
	else {
		writebuffer[0] = code;
		writebufferSize = 1;
	}
	fwrite(writebuffer, sizeof(char), writebufferSize, handler.fd);		
}	
#endif /* FILEHANDER_H */
