//Marin Vladimir 312CAa
#ifndef LOAD_IT
#define LOAD_IT

#include <stdio.h>
#include "color_values.h"

int type_of_file(char *magic_word);

int type_of_image(char *magic_word);

void check_for_comments(FILE *file_name);

values **load_it(char *file_name, int *height, int *width, int *x1, int *y1,
				 int *x2, int *y2, int *filetype, int *maximum, int *imagetype
				 , int *loaded);

#endif