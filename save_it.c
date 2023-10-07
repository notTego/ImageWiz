//Marin Vladimir 312 CAa
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "color_values.h"
#include "miscellaneous.h"

#define LENMAX 10 //max length for command name
#define FILENAME 100 //max length for a file's name
#define ASCIILEN 4

// void get_params(int *filetype, char *filename)
// {
// 	char params[FILENAME];
// 	//filetype = 0 for binary, 1 for ASCII
// 	*filetype = 0;

// 	fgets(params, FILENAME, stdin);
	
// 	if (strstr(params, "ascii"))
// 		*filetype = 1;
// 	for (int i = 0; i < strlen(params) - 1; i++)
// 		if (params[i] == ' ' || params[i] == '\n') {
// 			params[i] = '\0';
// 			break;
// 		}
// 	strcpy(filename, params);
// }

void get_params(int *ascii_type, char *filename)
{
	char arguments[FILENAME];
	fgets(arguments, FILENAME, stdin);
	int len = strlen(arguments);
	arguments[len - 1] = '\0';

	// if the string contains the string "ascii", the image will be
	// saved in ascii file
	*ascii_type = 0;
	if (strstr(arguments, "ascii"))
		*ascii_type = 1;

	char *delim = "\n ";
	char *token = strtok(arguments, delim);

	// get the path of the file where to save image
	strcpy(filename, token);
}

void fill_magicword(FILE *filename, int *imagetype, int *filetype)
{
	switch (*filetype) {
	case 1: // ascii
		switch (*imagetype) {
		case 0: // GS
			fprintf(filename, "P2");
			break;
		case 1: // B&W
			fprintf(filename, "P1");
			break;
		case 2: // RGB
			fprintf(filename, "P3");
		}
		break;
	case 0: // binary
		switch (*imagetype) {
		case 0: // GS
			fprintf(filename, "P5");
			break;
		case 1: // B&W
			fprintf(filename, "P4");
			break;
		case 2: // RGB
			fprintf(filename, "P6");
		}
		break;
	}
}

void save_it(values **image, int *height, int *width, int *maximum,
			 int *imagetype, int *filetype, char *filename)
{
	FILE *output = fopen(filename, "wt");

	//defensive programming
	if (!output) {
		fprintf(stderr, "Cannot open %s\n", filename);
		return;
	}

	fill_magicword(output, imagetype, filetype);

	fprintf(output, "\n");
	// B&W does not have maximum value
	if (*imagetype == 1)
		fprintf(output, "%d %d\n", *width, *height);
	else
		fprintf(output, "%d %d\n%d\n", *width, *height, *maximum);
	
	//check for "ascii" parameter
	if (*filetype) {
		//save image as ascii file
		print_in_ascii(height, width, image, imagetype, output);
		printf("Saved %s\n", filename);
		fclose(output);

	} else {
		//close file in ascii and open it in binary
		fclose(output);
		FILE *output = fopen(filename, "ab");

		//defensive programming
		if (!output) {
			fprintf(stderr, "Cannot open %s\n", filename);
			return;
		}

		//save image as binary file
		print_in_binary(height, width, image, imagetype, output);
		printf("Saved %s\n", filename);
		fclose(output);
	}


	// ////////////////DEBUGGING///////////////
	// output = fopen(filename, "r");
	// char c = fgetc(output);
	// while (c != EOF) {
	// 	printf("%c", c);
	// 	c = fgetc(output);
	// }
}



// int main()
// {
// 	int filetype;
// 	char filename[LENMAX];
// 	get_params(&filetype, filename);
// 	printf("%s: %d", filename, filetype);
// 	return 0;
// }