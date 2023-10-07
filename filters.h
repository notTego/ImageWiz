//Marin Vladimir 312CAa
#ifndef FILTER
#define FILTER
#define KERLEN 3
#include <stdio.h>
#include <math.h>

#include "color_values.h"
#include "hash.h"

void move_filter(values **image, int *height, int *width, int *nr_values,
				 const double kernel[KERLEN][KERLEN], values **copy);

values **filter_sharpen(values **image, int *height, int *width,
						int *imagetype);

void filter_it(values **image, int *height, int *width, int *imagetype);

#endif