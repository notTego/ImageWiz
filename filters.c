//Marin Vladimir 312CAa

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "miscellaneous.h"
#include "hash.h"
#include "color_values.h"

#define KERLEN 3
#define LENMAX 15 //max length for command name

enum hashes {
	EDGE = 999170732,
	SHARPEN = 236722860,
	BLUR = 999571714,
	GAUSSIAN_BLUR = 309466651
};

// typedef struct{
// 	int sharpen[KERLEN][KERLEN] = {
// 								   {0, -1, 0},
// 								   {-1, 5, -1},
// 								   {0, -1, 0}
// 								  };

// 	int edge_det[KERLEN][KERLEN] = {
// 									 {-1, -1, -1},
// 									 {-1, 8, -1},
// 									 {-1, -1, -1}
// 								   };

// 	float box_blur[KERLEN][KERLEN] = {
// 									  {1 / 9, 1 / 9, 1 / 9},
// 									  {1 / 9, 1 / 9, 1 / 9},
// 									  {1 / 9, 1 / 9, 1 / 9}
// 									 };

// 	float gaussian_blur[KERLEN][KERLEN] = {
// 										   {1 / 16, 2 / 16, 1 / 16},
// 										   {2 / 16, 4 / 16, 2 / 16},
// 										   {1 / 16, 2 / 16, 1 / 16}
// 										  };
// }kernel;

//image convolution using a kernel
void move_filter(values **image, int *height, int *width, int *nr_values,
				 int kernel[KERLEN][KERLEN], values **copy)
{
	double sum;

	for (int i = 0; i < KERLEN; i++) {
		for (int j = 0; j < KERLEN; j++)
			printf("%d ", kernel[i][j]);
		printf("\n");
	}

	for (int i = 0; i < KERLEN; i++) {
		for (int j = 0; j < KERLEN; j++)
			for (int k = 0; k < *nr_values; k++)
				printf("%d ", image[i][j].pixel[k]);
		printf("\n");
	}

	for (int i = 0; i < KERLEN; i++) {
		for (int j = 0; j < KERLEN; j++)
			for (int k = 0; k < *nr_values; k++)
				printf("%d ", copy[i][j].pixel[k]);
		printf("\n");
	}

	//go through image matrix
	for (int i = 0; i < *height; i++) {
		for (int j = 0; j < *width; j++)
			for (int k = 0; k < *nr_values; k++) {
				//edge values remain unchanged
				if (i == 0 || i == *height - 1)
					copy[i][j].pixel[k] = image[i][j].pixel[k];
				else if (j == 0 || j == *width - 1)
					copy[i][j].pixel[k] = image[i][j].pixel[k];
				else {
					//fill in filtered pixel value
					sum = 0;
					for (int conv_i = i - 1; conv_i < i + 2; conv_i++)
						for (int conv_j = j - 1; conv_j < j + 2; conv_j++) {
							sum = sum + image[i][j].pixel[k] * kernel[i][j];
							printf("%f ", sum);
						}
					copy[i][j].pixel[k] = sum / (KERLEN * KERLEN);
					printf("%d ", copy[i][j].pixel[k]);
				}
				
			}
		printf("\n");
	}
}

values **filter_sharpen(values **image, int *height, int *width,
						int *imagetype)
{
	int sharpen[KERLEN][KERLEN] = {
								   {0, -1, 0},
								   {-1, 5, -1},
								   {0, -1, 0}
								   };

	int nr_values;
	double sum;

	values **copy = (values **)calloc(*height, sizeof(values *));
	//defensive programming
	if(copy == NULL) {
		fprintf(stderr, "malloc() failed\n");
		return NULL;
	}

	for (int i = 0; i < *height; i++) {
		copy[i] = (values *)calloc(*width, sizeof(values *));
		//defensive programming
		if (copy[i] == NULL) {
			fprintf(stderr, "malloc() failed\n");
			//free previously alloc'd memory
			for (int j = 0; j < i; j++)
				free(copy[j]);
			free(copy);
			return NULL;
		}

		switch (*imagetype) {
		case 2: //RGB
			nr_values = 3;
			break;
		default: //GS, B&W
			nr_values = 1;
			break;
		}

		sum = 0;
		for (int j = 0; j < *width; j++) {
			copy[i][j].pixel = (unsigned char *)calloc(nr_values,
							 sizeof(unsigned char));
			
			for (int k = 0; k < nr_values; k++) {
				//edge values remain unchanged
				if (i == 0 || i == *height - 1)
					copy[i][j].pixel[k] = image[i][j].pixel[k];
				else if (j == 0 || j == *width - 1)
					copy[i][j].pixel[k] = image[i][j].pixel[k];
				else {
					//fill in filtered pixel value
					for (int conv_i = i - 1; conv_i < i + 2; conv_i++)
						for (int conv_j = j - 1; conv_j < j + 2; conv_j++) {
							sum = sum + image[conv_i][conv_j].pixel[k] * sharpen[conv_i][conv_j];
							printf("%f = sum + %d * %d\n", sum, image[conv_i][conv_j].pixel[k], sharpen[conv_i][conv_j]);
						}
					copy[i][j].pixel[k] = round(sum / (KERLEN * KERLEN)) ;
					sum = 0;
				}
				printf("%d ", copy[i][j].pixel[k]);
			}
		}
		printf("\n");
	}

	//move_filter(image, height, width, &nr_values, sharpen, copy);
	printf("filtered\n");
	// return copy;
	//free_matrix(height, width, image);
	return copy;
}

void filter_it(values ***image, int *height, int *width, int *imagetype)
{
	char param[LENMAX];
	int code;
	scanf("%s", param);
	code = string_hash(param);

	switch (code)
	{
	case SHARPEN:
		*image = filter_sharpen(*image, height, width, imagetype);
		printf("APPLY %s done\n", param);
		break;
	
	default:
		printf("APPLY parameter invalid\n");
		break;
	}


}
