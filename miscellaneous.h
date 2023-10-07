//Marin Vladimir 312CAa
#ifndef MISC
#define MISC

#include <stdio.h>
#include "color_values.h"

void swap(int *a, int *b);

void pointer_swap(unsigned char **a, unsigned char **b);

void free_matrix(int *height, int *width, values **image);

values **read_ascii_matrix(int *width, int *height, int *color,
						   FILE *file_name);

values **read_binary_matrix(int *width, int *height, int *color,
						   FILE *file_name);

double limiter(double value, int maxvalue);

void print_in_ascii(int *height, int *width, values **image, int *color,
					FILE *file_name);

void print_in_binary(int *height, int *width,values **image,  int *color,
					FILE *file_name);

#endif