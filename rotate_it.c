//Marin Vladimir 312CAa

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "miscellaneous.h"
#include "color_values.h"
#include "select_all.h"

#define NOT_RGB 1 //for debugging square_plus90() 

//+90 degrees rotated copy of matrix
//demonstration as follows:
/*
HOW TO ACHIEVE THIS:
g d a
h e b
i f c

FROM THIS:
a b c
d e f
g h i
-----------STEPS-----------
transpose:
a d g
b e h
c f i

flip around vertical axis:
g d a
h e b
i f c
*/
values **copy_matrix(values **image, int *height, int *width, int *color)
{
	int nr_values, last = 0, first = *height - 1;

	//column array allocation for copy matrix
	values **copy = (values **)malloc(*width * sizeof(values *));

	//defensive programming
	if (!copy) {
		fprintf(stderr, "malloc() failed\n");
		return NULL;
	}

	//column allocation
	for (int i = 0; i < *width; i++) {
		copy[i] = (values *)malloc(*height * sizeof(values *));
		//defensive programming
		if (!copy) {
			fprintf(stderr, "malloc() failed\n");
			//free previously alloc'd memory
			for (int j = i - 1; j >= 0; j--)
				free(copy[j]);
			free(copy);
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

		for (int j = 0; j < *height; j++) {
			copy[i][j].pixel = (unsigned char *)malloc(nr_values *
													   sizeof(char));
			//defensive programming
			if (!copy[i][j].pixel) {
				fprintf(stderr, "malloc() failed\n");
				free(copy[i][j].pixel);
			}

			//transpose matrix
			for (int k = 0; k < nr_values; k++)
				copy[i][j].pixel[k] = image[i][j].pixel[k];	
		}

		//flip around vertical axis
			while (last > first) {
			pointer_swap(&copy[i][last].pixel, &copy[i][first].pixel);
			last--;
			first++;
		}
	}

	return copy;
}

void all_plus90(values ***image, int *height, int *width, int *x1, int *y1,
				int *x2, int *y2, int *color)
{
	int loaded = 1, last = 0, first = *height - 1;;
	//90 degree rotated copy
	values **copy = copy_matrix(*image, height, width, color);

	free_matrix(height, width, *image); //frees old matrix
	swap(width, height);
	select_all(height, width, x1, y1, x2, y2, &loaded);


	for (int i = 0; i < *height; i++) {
			//flip around vertical axis
		while (last > first-1) {
			//pointer_swap(&copy[i][last].pixel, &copy[i][first].pixel);

			unsigned char *aux = copy[i][last].pixel;
			copy[i][last].pixel = copy[i][first].pixel;
			copy[i][first].pixel = aux;

			last--;
			first++;
		}
	}



	*image = copy;
	
	
		
}

void square_plus90(values **image, int *x1, int *y1, int *x2, int *y2)
{
	int len = (*x2 - *x1) + (*y2 - *y1), nr_values = NOT_RGB;
	for (int i = 0; i < len / 2; i++) {
        	for (int j = i; j < len - i - 1; j++) {
				for (int k = 0; k < nr_values; k++) {
					int aux = image[i][j].pixel[k];
					image[i][j].pixel[k] = image[len- 1 - j][i].pixel[k];
					image[len - 1 - j][i].pixel[k] = image[len - i - 1][len - 1 - j].pixel[k];
					image[len - i - 1][len - 1 - j].pixel[k] = image[j][len - i - 1].pixel[k];
					image[j][len - i - 1].pixel[k] = aux;
				}
					
			}
		}
}

// void square_plus90(values **image, int *x1, int *y1, int *x2, int *y2)
// {
// 	int i, j, first, last;
// 	//transpose
// 	for (i = *y1; i < *y2; i++)
// 		for(j = *x1; j < *x2; j++)
// 			pointer_swap(&image[i][j].pixel, &image[j][i].pixel);

// 	//flip around vertical axix
// 	for (i = *y1; i < *y2; i++) {
// 		first = *x1;
// 		last = *x2 - 1;
// 		while (last > first) {
// 			pointer_swap(&image[i][first].pixel, &image[i][last].pixel);
// 			last--;
// 			first++;
// 		}
// 	}
// }

void rotate_it(values ***image, int *height, int *width, int *color, int *x1,
			   int *y1, int *x2, int *y2, int *loaded)
{
	int angle, status = 0;
	scanf("%d", &angle);

	if (*loaded == 0) {
		printf("No image loaded\n");
		return;
	}

	//selection is square
	if (*x2 - *x1 == *y2 - *y1) {
		switch (angle) {
		case 90:
			square_plus90(*image, x1, y1, x2, y2);
			status = 1;
			break;
		case 180:
			square_plus90(*image, x1, y1, x2, y2);
			square_plus90(*image, x1, y1, x2, y2);
			status = 1;
			break;
		case 270:
			square_plus90(*image, x1, y1, x2, y2);
			square_plus90(*image, x1, y1, x2, y2);
			square_plus90(*image, x1, y1, x2, y2);
			status = 1;
			break;
		case 360:
			status = 1;
			break;
		case -90:
			square_plus90(*image, x1, y1, x2, y2);
			square_plus90(*image, x1, y1, x2, y2);
			square_plus90(*image, x1, y1, x2, y2);
			status = 1;
			break;
		case -180:
			square_plus90(*image, x1, y1, x2, y2);
			square_plus90(*image, x1, y1, x2, y2);
			status = 1;
			break;
		case -270:
			square_plus90(*image, x1, y1, x2, y2);
			status = 1;
			break;
		case -360:
			status = 1;
			break;
		default:
			printf("Unsupported rotation angle\n");
		}

		if (status)
			printf("Rotated %d\n", angle);
		return;
	}

	//selection is ALL
	if (*x1 == 0 && *y1 == 0 && *x2 == *width && *y2 == *height) {
		switch (angle)
		{
		case 90:
			all_plus90(image, height, width, x1, y1, x2, y2, color);
			status = 1;
			break;
		case 180:
			all_plus90(image, height, width, x1, y1, x2, y2, color);
			all_plus90(image, height, width, x1, y1, x2, y2, color);
			status = 1;
			break;
		case 270:
			all_plus90(image, height, width, x1, y1, x2, y2, color);
			all_plus90(image, height, width, x1, y1, x2, y2, color);
			all_plus90(image, height, width, x1, y1, x2, y2, color);
			status = 1;
			break;
		case 360:
			status = 1;
			break;
		case -90:
			all_plus90(image, height, width, x1, y1, x2, y2, color);
			all_plus90(image, height, width, x1, y1, x2, y2, color);
			all_plus90(image, height, width, x1, y1, x2, y2, color);
			status = 1;
			break;
		case -180:
			all_plus90(image, height, width, x1, y1, x2, y2, color);
			all_plus90(image, height, width, x1, y1, x2, y2, color);
			status = 1;
			break;
		case -360:
			status = 1;
			break;
		default:
			printf("Unsupported rotation angle\n");
			break;
		}

		if (status)
			printf("Rotated %d\n", angle);
		return;
	}
	//selection does not meet requirements
	printf("The selection must be square\n");

	//DBG
	// for(int i = 0; i < *width; i++) {
	// 	for (int j = 0; j < *height; j++)
	// 		printf("%hhn ", image[i][j].pixel);
	// 	printf("\n");
	// }

}