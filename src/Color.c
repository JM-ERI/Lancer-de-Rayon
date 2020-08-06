#include <stdio.h>
#include <string.h>
#include <math.h>

#include "../include/Color.h"
#define CLIP(min,a,max) (((a)<(min)?(min):((a)>(max)?(max):(a))))

int moyennageColor(int n, const Color *color_comming, const Color *color_old, Color *res){

	if(color_comming == NULL || color_old == NULL || res == NULL){
		return 0;
	}
	
	double double_n = (double)n;

	res->r = ((1 / double_n) * color_comming->r) + ((n - 1) / double_n) * color_old->r;
	res->g = ((1 / double_n) * color_comming->g) + ((n - 1) / double_n) * color_old->g;
	res->b = ((1 / double_n) * color_comming->b) + ((n - 1) / double_n) * color_old->b;
	return 1;
}

int setColor(Color *color, unsigned char r, unsigned char g, unsigned char b){
	
	if (color == NULL){
		return 0;
	}
	
	color->r = r;
	color->g = g;
	color->b = b;
	return 1;
}

int Color_to_uint32_t(const Color *color, uint32_t *value){
	if (color == NULL || value == NULL){
		return 0;
	}
	(*value) = (color->r) + (color->g << 8) + (color->b << 16);
	return 1;
}

int ColorCopy(Color *dest, const Color *src){
	if (src == NULL || dest == NULL){
		return 0;
	}

	(*dest) = (*src);
	return 1;
}

int Color_from_double(Color *color, double r, double g, double b){
	if(color == NULL){
		return 0;
	}

	return setColor(color, (unsigned char)CLIP(0, r, 255), (unsigned char)CLIP(0, g, 255), (unsigned char)CLIP(0, b, 255));
}

int ColorConsoleDisplay(const Color *c, int return_line){
	if (c == NULL){
		return 0;
	}
	printf("r:%d, g:%d, b:%d%c", c->r, c->g, c->b, return_line == 0 ? ' ':'\n');
	return 1;
}
