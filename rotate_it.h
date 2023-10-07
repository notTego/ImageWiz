//Marin Vladimir 312CAa
#ifndef ROTATE_IT
#define ROTATE_IT

#include <stdio.h>
#include "color_values.h"

values **copy_matrix(values **image, int *height, int *width, int *color);

void all_plus90(values ***image, int *height, int *width, int *x1, int *y1,
				int *x2, int *y2, int *color);

void square_plus90(values **image, int *x1, int *y1, int *x2, int *y2);

void rotate_it(values ***image, int *height, int *width, int *color, int *x1,
			   int *y1, int *x2, int *y2, int *loaded);

#endif