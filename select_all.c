//Marin Vladimir 312CAa
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "miscellaneous.h"
#include "color_values.h"

#define LENMAX 10 //max length for command name
#define FILENAME 100 //max length for a file's name
#define TYPELEN 2

void select_all(int *height, int *width, int *x1, int *y1,
				int *x2, int *y2, int *loaded)
{
	int trash;

	if (*loaded == 0) {
		printf("No image loaded\n");
		do {
			scanf("%d", &trash);
		} while (trash != '\n');
		return;
	}

	*x1 = 0;
	*x2 = *width;
	*y1 = 0;
	*y2 = *height;

	printf("Selected ALL\n");
}