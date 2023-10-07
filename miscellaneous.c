//Marin Vladimir 312CAa

/*
	NOTE TO SELF

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "color_values.h"

void swap(int *a, int *b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

//swaps 2 unsigned int pointers
void pointer_swap(unsigned char **a, unsigned char **b)
{
	unsigned char *aux = *a;
	*a = *b;
	*b = aux;
}

void free_matrix(int *height, int *width, values **image)
{
	for (int i = 0; i < *height; i++) {
		for (int j = 0; j < *width; j++)
			free(image[i][j].pixel);
		free(image[i]);
	}
	free(image);
}

//read matrix from an ASCII file
values **read_ascii_matrix(int *width, int *height, int *color,
						   FILE *file_name)
{
	int nr_values; // for each pixel: 1 for GS and B&W, 3 for RGB

	//dynamically allocate matrix
	values **a = (values **)malloc(*height * sizeof(values *));

	//defensive programming
	if(a == NULL) {
		fprintf(stderr, "malloc() failed\n");
		return NULL;
	}

	//alloc lines
	for (int i = 0; i < *height; i++) {
		a[i] = malloc(*width * sizeof(values *));

		//defensive programming
		if (a[i] == NULL) {
			fprintf(stderr, "malloc() failed\n");
			//free previously alloc'd memory
			for (int j = 0; j < i; j++)
				free(a[j]);
			free(a);
			return NULL;
		}

		switch (*color) {
		case 2: //RGB
			nr_values = 3;
			break;
		default: //GS, B&W
			nr_values = 1;
			break;
		}

		for (int j = 0; j < *width; j++) {
			a[i][j].pixel = (unsigned char *)calloc(nr_values,
							 sizeof(unsigned char));
			for (int k = 0; k < nr_values; k++)
				//%hhu - numeric value of unsigned char
				fscanf(file_name, "%hhu", &a[i][j].pixel[k]);
		}
	}

	return a;
}

//read matrix from a binary file
values **read_binary_matrix(int *width, int *height, int *color,
						   FILE *file_name)
{
	int nr_values; // for each pixel: 1 for GS and B&W, 3 for RGB

	//dynamically allocate matrix
	values **a = (values **)malloc(*height * sizeof(values *));

	//defensive programming
	if(a == NULL) {
		fprintf(stderr, "malloc() failed\n");
		return NULL;
	}

	//alloc lines
	for (int i = 0; i < *height; i++) {
		a[i] = malloc(*width * sizeof(values *));

		//defensive programming
		if (a[i] == NULL) {
			fprintf(stderr, "malloc() failed\n");
			//free previously alloc'd memory
			for (int j = 0; j < i; j++)
				free(a[j]);
			free(a);
			return NULL;
		}

		switch (*color) {
		case 2: //RGB
			nr_values = 3;
			break;
		default: //GS, B&W
			nr_values = 1;
			break;
		}

		for (int j = 0; j < *width; j++) {
			a[i][j].pixel = (unsigned char *)calloc(nr_values,
							 sizeof(unsigned char));
			fread(a[i][j].pixel, sizeof(unsigned char), nr_values, file_name);
		}
	}
	return a;
}

//limits any number greater than a max value to that value
double clamp(double value, int minvalue, int maxvalue)
{
	if (value > maxvalue)
		return maxvalue;
	else if (value < minvalue)
		return minvalue;
	return value;
}

//prints matrix in ASCII file
void print_in_ascii(int *height, int *width, values **image, int *color,
					FILE *file_name)
{
	int nr_values, temp;
	switch (*color) {
		case 2: //RGB
			nr_values = 3;
			for (int i = 0; i < *height; i++) {
				for (int j = 0; j < *width; j++) {
					for (int k = 0; k < nr_values; k++) {
						temp = image[i][j].pixel[k];
						fprintf(file_name, "%d ", temp);
					}
				}
				fprintf(file_name, "\n");
			}
			break;
		default: //GS, B&W
			nr_values = 1;
			for (int i = 0; i < *height; i++) {
				for (int j = 0; j < *width; j++) {
					temp = image[i][j].pixel[0];
					fprintf(file_name, "%d ", temp);
				}
				fprintf(file_name, "\n");
			}


			break;
		}

	

}


// void print_in_ascii(int *height, int *width, values **image, int *color,
// 					char *filename)
// {
// 	FILE *file_name = fopen(filename, "a");

// 	int nr_values, temp;
// 	switch (*color) {
// 		case 1: //RGB
// 			nr_values = 3;
// 			break;
// 		default: //GS, B&W
// 			nr_values = 1;
// 			break;
// 		}

// 	for (int i = 0; i < *height; i++) {
// 		for (int j = 0; j < *width; j++) {
// 			for (int k = 0; k < nr_values; k++) {
// 				temp = image[i][j].pixel[k];
// 				fprintf(file_name, "%d ", temp);
// 				printf("INCARCAT\n");
// 			}
// 		}
// 		fprintf(file_name, "\n");
// 	}

// }

//prints matrix in binary file
void print_in_binary(int *height, int *width, values **image, int *color,
					FILE *file_name)
{
	int nr_values;
	switch (*color) {
		case 1: //RGB
			nr_values = 3;
			break;
		default: //GS, B&W
			nr_values = 1;
			break;
		}

	for (int i = 0; i < *height; i++)
		for (int j = 0; j < *width; j++)
			for (int k = 0; k < nr_values; k++)
				fwrite(&image[i][j].pixel[k], sizeof(unsigned char),
					   1, file_name);
}