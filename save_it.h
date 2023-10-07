//Marin Vladimir 312CAa
#ifndef SAVE_IT
#define SAVE_IT

#include <stdio.h>
#include "color_values.h"

void get_params(int *filetype, char *filename);

void fill_magicword(FILE *filename, int *imagetype, int *filetype);

void save_it(values **image, int *height, int *width, int *maximum,
			 int *imagetype, int *filetype, char *filename);

#endif