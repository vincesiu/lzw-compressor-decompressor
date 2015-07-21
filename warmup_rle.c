#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void compression(char *file) {

	FILE *fp_input = fopen (file, "r");
	FILE *fp_output = fopen("compressed_file", "w");


	char c;
	char active_char = fgetc(fp_input);
	char active_char_count = 1;

	while ((c = fgetc(fp_input)) != EOF){
		if (c != active_char || active_char_count == 9){
			if (active_char_count == 1)
				fprintf(fp_output, "%c", (active_char+128));
			else
				fprintf(fp_output, "%d%c", active_char_count, active_char);
				active_char = c;
				active_char_count = 1;
		}
		else {
			active_char_count++;
		}	
	}

	fprintf(fp_output, "%d%c", active_char_count, active_char);

	fclose(fp_input);	
	fclose(fp_output);


}



void decompression (char *file) {

	FILE *fp_input = fopen (file, "r");
	FILE *fp_output = fopen("decompressed_file", "w");
	
	char c;
	while ((c = fgetc(fp_input)) != EOF) {
		if (c < 0) 
			fprintf(fp_output, "%c", c+=128);		
		else {
			int count = c - '0';
			char active_char = fgetc(fp_input);
			int idx;
			for (idx = 0; idx < count; idx++)
				fprintf(fp_output, "%c", active_char);		
		}
	}
}


int main (int argc, char *argv[]) {

	if (argc != 3 || (*argv[1] != 'd' && *argv[1] != 'c'))
		printf("Error: this program requires two arguments.\nThe first argument is 'd' for decompressing or 'c' for compressing, and the second argument is the name of the file.\n");
	
	
	switch(argv[1][0]) {
                case('c'):	
			compression(argv[2]);
			break;
		case('d'):
			decompression(argv[2]);
			break;
		default:
			printf("Invalid argument. Please provide the first argument as 'c' for compressing or 'd' for decompressing");

}

}
