//Marin Vladimir 312 CAa

//IMAGE EDITOR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "color_values.h"
#include "hash.h"
#include "miscellaneous.h"
#include "load_it.h"
#include "select_it.h"
#include "select_all.h"
#include "rotate_it.h"
#include "save_it.h"
#include "filters.h"

#define LENMAX 10 //max length for command name
#define FILENAME 100 //max length for a file's name



//assign tags for each hash for easier comprehension
enum hashes {
	//string_hash("<command>")
	LOAD = 999135523,
	SELECT = 628843661,
	//SELECTALL = 678529236,
	ROTATE = 214995086,
	SAVE = 999185068,
	APPLY = 992923639,
	EXIT = 999620139
};

int main()
{
	char command[LENMAX + 1], file_name[FILENAME], trash;
	char source[FILENAME];
	int height, width, maximum;
	int loaded = 0; //verifies if a file has been loaded or not
	int x1, x2, y1, y2, filetype, imagetype;
	values **image = NULL; //no image loaded
	int code = 0; //hash of input string
	int loop = 1;
	//int loop = 0;

	while (loop) {
		scanf("%s", command);
		// fgets(command, sizeof(command), stdin);
		code = string_hash(command);

		//two strings have the same hash only if they are identical
		switch (code) {
		case LOAD:
			//free a previously loaded image
			if (image)
				free_matrix(&height, &width, image);

			//specify source file
			scanf("%s", source);
			getchar();
			loaded = 1;

			image = load_it(source, &height, &width, &x1, &y1, &x2, &y2,
							&filetype, &maximum, &imagetype, &loaded);

			break;

		case SELECT:
			select_it(&height, &width, &x1, &y1, &x2, &y2, &loaded);
			break;

		case ROTATE:
			rotate_it(&image, &height, &width, &imagetype, &x1, &y1, &x2, &y2,
					  &loaded);
			break;

		case SAVE:
			if (loaded) {
				get_params(&filetype, file_name);
				
				save_it(image, &height, &width, &maximum, &imagetype,
						&filetype, file_name);

			} else {
				printf("No image loaded\n");
				do {
					scanf("%c", &trash);
				} while (trash != '\n');
			}
			break;

		case APPLY:
			if (loaded) {
				filter_it(image, &height, &width, &imagetype);
			} else {
				printf("No image loaded\n");
				do {
					scanf("%c", &trash);
				} while (trash != '\n');
			}
			break;

		case EXIT:
			if (loaded) {
				free_matrix(&height, &width, image);
			} else {
				printf("No image loaded\n");
			}
			loop = 0;
			break;

		default:
			do {
				scanf("%c", &trash);
			} while (trash != '\n');
			fprintf(stderr, "Unrecognised command\n");
			break;
		}
	}
	//printf("%d\n", string_hash("APPLY"));
	
	return 0;
}
