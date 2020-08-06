#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/Triangle.h"
#define min(a,b) (a<=b?a:b)

int setTriangle(Triangle *triangle, const Point *A, const Point *B, const Point *C, const Color *color){
	if (triangle == NULL || A == NULL || B == NULL || C == NULL || color == NULL){
		return 0;
	}
	
	triangle->A = (*A);
	triangle->B = (*B);
	triangle->C = (*C);
	ColorCopy(&triangle->color, color);
	return 1;
}

int rayon_inter_Triangle(const Point *A, const Vecteur *u, Point *I, Vecteur *N){
	Point P1;
	Point P2;
	Point P3;
	double t;

	if (A == NULL || u == NULL || I == NULL || N == NULL){
		return 0;
	}

	setPoint(&P1, 0., 1., 0.);
	setPoint(&P2, 0.87, -0.5, 0.);
	setPoint(&P3, -0.87, -0.5, 0.);

	t = (- A->z) / (u->z);
	
	setPoint(I, A->x + t * u->x, A->y + t * u->y, 0.);
	if(!TrianglePointInTriangle(&P1, &P2, &P3, I)){
		return 0;
	}
	setVecteur(N, 0., 0., 1.);
	return 1;
}

int TrianglePointInTriangle(const Point *A, const Point *B, const Point *C, const Point *I){
	if(A == NULL || B == NULL || C == NULL || I == NULL){
		return -1;
	}
	Vecteur AB;
	Vecteur BA;
	Vecteur AC;
	Vecteur CA;
	Vecteur CB;
	Vecteur BC;
	Vecteur AI;
	Vecteur BI;
	Vecteur CI;
	VecteurOfPoints(&AB, A, B);
	VecteurOfPoints(&BA, B, A);
	VecteurOfPoints(&AC, A, C);
	VecteurOfPoints(&CA, C, A);
	VecteurOfPoints(&CB, C, B);
	VecteurOfPoints(&BC, B, C);
	VecteurOfPoints(&AI, A, I);
	VecteurOfPoints(&BI, B, I);
	VecteurOfPoints(&CI, C, I);

	Vecteur prod_vec1;
	Vecteur prod_vec2;

	double ps;

	VecteurProd_vec(&AB, &AI, &prod_vec1);
	VecteurProd_vec(&AI, &AC, &prod_vec2);
	VecteurProd_scal(&prod_vec1, &prod_vec2, &ps);
	if(ps < 0.){
		return 0;
	}

	VecteurProd_vec(&BA, &BI, &prod_vec1);
	VecteurProd_vec(&BI, &BC, &prod_vec2);
    VecteurProd_scal(&prod_vec1, &prod_vec2, &ps);
    if(ps < 0.){
		return 0;
	}
	
	VecteurProd_vec(&CA, &CI, &prod_vec1);
	VecteurProd_vec(&CI, &CB, &prod_vec2);
	VecteurProd_scal(&prod_vec1, &prod_vec2, &ps);
	if(ps < 0.){
		return 0;
	}
	return 1;
}

int TriangleConsoleDisplay(const Triangle *triangle, int return_line){
	if(triangle == NULL){
		return 0;
	}
	
	printf("A: ");
	PointConsoleDisplay(&(triangle)->A, 0);
	printf("B: ");
	PointConsoleDisplay(&(triangle)->B, 0);
	printf("C: ");
	PointConsoleDisplay(&(triangle)->C, 0);
	printf("color: ");
	ColorConsoleDisplay(&triangle->color, return_line);
	return 1;
}
