
#include <stdlib.h>
#include <stdio.h>
#include "filehandler.h"
#include "lzw.h"

int main (int argc, char *argv[]) {


lzw_compress("precompressedfile");
lzw_decompress("compressedfile");

/*


	struct Filehandler *outputFile = filehandler_init("testcompressedfile", 'w');

	filehandler_write(outputFile, 'b');
	filehandler_write(outputFile, 'a');
	filehandler_write(outputFile, 'n');
	filehandler_write(outputFile, 129);
	filehandler_write(outputFile, 'a');
	filehandler_write(outputFile, ' ');
	filehandler_write(outputFile, 128);
	filehandler_write(outputFile, 'n');
	filehandler_write(outputFile, 'd');
	filehandler_write(outputFile, 131);


	filehandler_write(outputFile, 'a');
	filehandler_write(outputFile, 'b');
	filehandler_write(outputFile, 'c');
	filehandler_write(outputFile, 128);
	filehandler_write(outputFile, 130);
	filehandler_write(outputFile, 129);
	filehandler_write(outputFile, 131);
	filehandler_write(outputFile, 134);
	filehandler_write(outputFile, 133);
	filehandler_write(outputFile, 136);
	filehandler_write(outputFile, 132);
	filehandler_write(outputFile, 138);
	filehandler_write(outputFile, 135);
	filehandler_write(outputFile, 'c');


	filehandler_close(outputFile);


	lzw_decompress("testcompressedfile");
*/
	return EXIT_SUCCESS;

}
