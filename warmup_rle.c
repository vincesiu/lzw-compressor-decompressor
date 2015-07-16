#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {

	if (argc != 3 || (*argv[1] != 'd' && *argv[1] != 'c'))
		printf("Error: this program requires two arguments.\nThe first argument is 'd' for decompressing or 'c' for compressing, and the second argument is the name of the file.\n");
	
	printf("%d", strlen(argv[2]));
	FILE *fp_input = fopen (argv[2], "r");
	FILE *fp_output = fopen("newfile", "w");
	int i;
	//for (i = 0; i < 10; i++) {
	//printf("%c", fgetc(fp));
	//}
	char c;
	char active_char = fgetc(fp_input);
	char active_char_count = 1;

	while ((c = fgetc(fp_input)) != EOF){
		if (c != active_char){
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




}
