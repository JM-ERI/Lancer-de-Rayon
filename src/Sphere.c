#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/Sphere.h"

int setSphere(Sphere *sphere, const Point *center, const Color *color, double rayon){
	if (sphere == NULL || center == NULL || color == NULL){
		return 0;
	}
	
	sphere->rayon = rayon;
	sphere->center = (*center);
	ColorCopy(&sphere->color, color);
	return 1;
}


int rayon_inter_Sphere(const Point *A, const Vecteur *u, Point *I, Vecteur *N){
	double t;
	double l;
	double d2;
	
	Vecteur OA;
	
	if (A == NULL || u == NULL || I == NULL || N == NULL){
		fprintf(stderr, "rayon_inter_Sphere NULL\n");
		return 0;
	}
	
	setVecteur(&OA, A->x, A->y, A->z);

	VecteurProd_scal(&OA, u, &t);
	
	t *= -1.;
	
    if(t < 0.){
		return 0;
	}

    VecteurSquareNorme(&OA, &d2);
    d2 = d2 - t * t;
    
    if(d2 > 1.){
		return 0;
	}
    
    l = t - sqrt(1. - d2);
    setPoint(I, A->x + l * u->x, A->y + l * u->y, A->z + l * u->z);
    setVecteur(N, I->x, I->y, I->z);
	return 1;
}

int SphereConsoleDisplay(const Sphere *sphere, int return_line){
	if(sphere == NULL){
		return 0;
	}
	
	printf("Center: ");
	PointConsoleDisplay(&sphere->center, 0);
	printf("color: ");
	printf("rayon: %f", sphere->rayon);
	ColorConsoleDisplay(&sphere->color, return_line);
	return 1;
}
