//Marin Vladimir 312CAa

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
#define COORD_NR 4

void select_it(int *height, int *width, int *x1, int *y1, int *x2, int *y2,
			   int *loaded)
{
	int is_int, coordinates[COORD_NR] = {};
	char rest[TYPELEN + 1], trash;

	if (*loaded == 0) {
		printf("No image loaded\n");
		do {
			scanf("%c", &trash);
		} while (trash != '\n');
		return;
	}

	//verify if the first input after SELECT is an int or not
	//if it is, we store each value in an array as follows:
	if (scanf("%d", &is_int) == 1) {
		coordinates[0] = is_int;

		for (int i = 1; i < COORD_NR; i++) {
			scanf("%d", &coordinates[i]);

			//x axis coordinates on odd positions in array
			if (i % 2 == 1)
				if (coordinates[i] < 0 || coordinates[i] >= *width) {
					printf("X coordinates outside picture: %d, WIDTH: %d\n", coordinates[i], *width); // !DEBUGGING
					return;
				}

			//y axis coordinates on even positions in array
			if (i % 2 == 0)
				if (coordinates[i] < 0 || coordinates[i] >= *height) {
					printf("Y coordinates outside picture\n");
					return;
				}
		}

		//x1 - x2 == 0 || y1 - y2 == 0 : these points do not exist
		if ((coordinates[0] - coordinates[2] == 0) ||
			(coordinates[1] - coordinates[3] == 0)) {
				printf("Invalid set of coordinates\n");
				return;
			}

		*x1 = coordinates[0];
		*y1 = coordinates[1];
		*x2 = coordinates[2];
		*y2 = coordinates[3];

		//x1 or y1 must always be less than x2 or y2
		if (*x1 > *x2)
			swap(x1, x2);
		if (*y1 > *y2)
			swap(y1, y2);
		printf("SELECTED %d %d %d %d\n", *x1, *y1, *x2, *y2);

	} else {
		scanf("%s", rest);
		if (strstr("ALL", rest))
			select_all(height, width, x1, y1, x2, y2, loaded);
	}


}
