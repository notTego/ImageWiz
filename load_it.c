//Marin Vladimir 312CAa

/*-------NOTES-FOR-SELF-------
- fix check for comments
----------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "miscellaneous.h"
#include "color_values.h"
#include "select_all.h"

#define LENMAX 10 //max length for command name
#define FILENAME 100 //max length for a file's name
#define TYPELEN 2

//returns 1 for ascii type and 0 for binary type
int type_of_file(char *magic_word)
{
	char ascii_type[TYPELEN * 3 + 1] = "P1P2P3";
	char binary_type[TYPELEN * 3 + 1] = "P4P5P6";

	int type;
	if (strstr(ascii_type, magic_word))
		type = 1;
	if (strstr(binary_type, magic_word))
		type = 0;
	return type;
}

//returns 0 for GS, 1 for B&W and 2 for RGB
int type_of_image(char *magic_word)
{
	int color = 0;

	if (!strcmp(magic_word, "P1") || !strcmp(magic_word, "P4"))
		color = 1;

	if (!strcmp(magic_word, "P3") || !strcmp(magic_word, "P4"))
		color = 2;

	return color;
}

void check_for_comments(FILE *file_name)
{
	char character, trash;
	fscanf(file_name, "%c", &character);
	if (character != '#') {
		fseek(file_name, -1, SEEK_CUR);
	} else {
		//if a comment is detected, we disregard characters until 
		//a "new line" character appears
		do {
			fscanf(file_name, "%c", &trash);
		} while (trash != '\n');
	}
}

values **load_it(char *file_name, int *height, int *width, int *x1, int *y1,
				 int *x2, int *y2, int *filetype, int *maximum, int *imagetype
				 , int *loaded)
{
	values **image = NULL;
	char magic_word[TYPELEN + 1];
	long position; //stores end of file position

	FILE *input = fopen(file_name, "rt");

	//defensive programming
	if (input == NULL) {
		printf("Failed to load %s\n", file_name);
		*loaded = 0; //not loaded
		return NULL;
	}

	//check for comments before and after magic word
	check_for_comments(input);
	fscanf(input, "%s", magic_word);
	check_for_comments(input);

	//maximum value is specified for everything except for B&W
	if (strstr("P1P4", magic_word)) {
		fscanf(input, "%d%d", width, height);
	} else {
		fscanf(input, "%d%d", width, height);
		check_for_comments(input);
		fscanf(input, "%d", maximum);
	}

	check_for_comments(input);
	position = ftell(input); //EOF

	*filetype = type_of_file(magic_word);
	*imagetype = type_of_image(magic_word);

	switch (*filetype) {
	case 1:
		printf("Loaded %s\n", file_name);
		image = read_ascii_matrix(width, height, imagetype, input);

		//SELECT ALL
		select_all(height, width, x1, y1, x2, y2, loaded);
		fclose(input);
		break;

	case 0:
		fclose(input);
		//open file as binary
		FILE *input = fopen(file_name, "rb");
		if (input == NULL) {
			printf("Failed to load %s\n", file_name);
			*loaded = 0;
			return NULL;
		}
		printf("Loaded %s\n", file_name);

		fseek(input, position + 1, SEEK_SET);
		image = read_binary_matrix(width, height, imagetype, input);

		//SELECT ALL
		select_all(height, width, x1, y1, x2, y2, loaded);
		fclose(input);
		break;

	default:
		printf("Cannot load %s", file_name);
	}

	//printf("WIDTH: %d\nHEIGHT: %d\nMagic Word: %s\n", *width, *height, magic_word);

	// for (int i = 0; i < *height; i++) {
	// 	for (int j = 0; j < *width; j++) {
	// 		for (int k = 0; k < 1; k++)
	// 			fprintf(stdout, "%d ", image[i][j].pixel[k]);
	// 	}
	// 	fprintf(stdout, "\n");
	// }

	return image;
}