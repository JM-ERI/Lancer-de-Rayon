#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../include/Image.h"
#include "../include/Point.h"
#include "../include/Png_Output.h"

#define ENTETE_JPG_SIZE 8
#define WIDTH_SIZE 4
#define HEIGHT_SIZE 4
#define BIT_DEPTH 8
#define PNG_RGB 2
#define CHUNK_NAME_SIZE 4

Image* newImage(int w, int h){
	
	Image *tmp;
	Color *data;

	if (w <= 0 || h <= 0){
		return NULL;
	}
	
	tmp = (Image *)malloc(sizeof(Image));
	
	if (tmp == NULL){
		return NULL;
	}
	data = (Color *)malloc(w * h * sizeof(Color));
	
	if (data == NULL){
		free(tmp);
		return NULL;
	}
	
	tmp->w = w;
	tmp->h = h;
	tmp->data = data;
	
	return tmp;
}

void freeImage(Image *image){
	
	if (image == NULL){
		return;
	}
	
	free(image->data);
	image->data = NULL;
	free(image);
}

Image* cloneImage(Image* src){
	Image* res;
	
	if (src == NULL){
		return NULL;
	}

	res = newImage(src->w, src->h);
	memcpy(res->data, src->data, src->w * src->h * sizeof(Color));
	return res;
}

int cpyImage(Image *dest, Image *src){
	if (dest->w != src->w || dest->h != src->h){
		return 0;
	}
	memcpy(dest->data, src->data, src->w * src->h * sizeof(Color));
	return 1;
}

int writeImagePPM(Image* I, const char* export_file_name){
	int row;
	int column;
	
	Color tmp;
	setColor(&tmp, 0, 0, 0);
	/*int nb_pixel;*/
	FILE *exportFile;
	char exportPath[512] = {"output/"};
	
	if (I == NULL || export_file_name == NULL){
		return 0;
	}
	strcat(exportPath, export_file_name);
	strcat(exportPath, ".ppm");
	exportFile = fopen(exportPath, "wb");
	if (exportFile == NULL){
		return 0;
	}
	
	fprintf(exportFile, "P3\n%d %d\n255\n", I->w, I->h);
	for(row = 0; row < I->h; row++){
		for (column = 0; column < I->w; column++){
			ImageGetPixel(I, &tmp, row, column);
			fprintf(exportFile, "%hhu %hhu %hhu ", tmp.r, tmp.g, tmp.b);
		}
		fprintf(exportFile, "\n");
	}

	fclose(exportFile);
	return 1;
}

int writeImagePNG(Image* I, const char* export_file_name){
	if (I == NULL){
		return 0;
	}
	PNG_output_file(I, export_file_name);
	return 1;
}

int ImageSetPixel(Image *image, const Color *p, int row, int column){
	if (image == NULL || row < 0 || column < 0 || row >= image->h || column >= image->w){
		printf("ImageSetPixel bad row, column\n");
		return 0;
	}

	image->data[(image->w * row) + column] = (*p);
	return 1;
}

int ImageGetPixel(const Image* img, Color *res, int row, int column){
	if (img == NULL || row < 0 || column < 0 || row >= img->h || column >= img->w){
		return 0;
	}
	
	(*res) = img->data[(row * img->w) + column];
	return 1;
}

void progressiveRay(int render, Image *dest, Image *comming, Image *old){
	int row;
	int col;
	Color tmp_comming;
	Color tmp_old;
	Color tmp;

	if (dest == NULL || comming == NULL || old == NULL){
		fprintf(stderr, "error NULL\n");
		return;
	}

	for (row = 0; row < dest->h; row++){
		for (col = 0; col < dest->w; col++){
			ImageGetPixel(comming, &tmp_comming, row, col);
			ImageGetPixel(old, &tmp_old, row, col);
			moyennageColor(render, &tmp_comming, &tmp_old, &tmp);
			ImageSetPixel(dest, &tmp, row, col);
		}
	}
}
