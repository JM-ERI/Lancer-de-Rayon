#include <stdio.h>
#include <stdlib.h>
#include "../include/Rectangle.h"


int setRectangle(Rectangle *rectangle, const Point *center, const Vecteur *u, const Vecteur *v, double rayon, const Color *color){
	if (rectangle == NULL || center == NULL || u == NULL || v == NULL || color == NULL){
		return 0;
	}
	
	rectangle->center = (*center);
	rectangle->u = (*u);
	rectangle->v = (*v);
	rectangle->rayon = rayon;
	ColorCopy(&rectangle->color, color);
	return 1;
}

int rayon_inter_Square(const Point *A, const Vecteur *u, Point *I, Vecteur *N){
	if (A == NULL || u == NULL || I == NULL || N == NULL){
		return 0;
	}
	
	double t;
	double l2;
	Point O;
	setPoint(&O, 0., 0., 0.);
	t = (- A->z) / (u->z);
	
	setPoint(I, A->x + t * u->x, A->y + t * u->y, 0.);
	PointNormeL2(&O, I, &l2);
	if (l2 > 1.){
		return 0;
	}
	setVecteur(N, 0., 0., 1.);
	return 1;
}

int RectangleConsoleDisplay(const Rectangle *rectangle, int return_line){
	if(rectangle == NULL){
		return 0;
	}
	
	printf("Center: ");
	PointConsoleDisplay(&(rectangle)->center, 0);
	printf("vecteur 1: %lf  %lf  %lf ", rectangle->u.x, rectangle->u.y, rectangle->u.z);
	printf("vecteur 2: %lf  %lf  %lf ", rectangle->v.x, rectangle->v.y, rectangle->v.z);
	printf("color: ");
	ColorConsoleDisplay(&rectangle->color, return_line);
	return 1;
}
