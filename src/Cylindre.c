#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/Cylindre.h"

int setCylindre(Cylindre *cylindre, const Point *P, const Point *Q, const Color *color, double rayon){
	if (cylindre == NULL || P == NULL || Q == NULL || color == NULL){
		return 0;
	}
	
	cylindre->P = (*P);
	cylindre->Q = (*Q);
	cylindre->rayon = rayon;
	cylindre->color = (*color);
	
	return 1;
}

int rayon_inter_Cylindre(const Point *A, const Vecteur *u, Point *I, Vecteur *N){
	double t;
	/* a*t² + b*t + c = 0 est l equation de l intersection a resoudre */
	double a = u->x*u->x + u->y*u->y;
	double b = 2 * (u->x * A->x + u->y * A->y);
	double c = A->x * A->x + A->y * A->y - 1;
	double delta = b*b - 4*a*c;

	if(delta < 0.){
		return 0;
	}
	double t1 = (-b -sqrt(delta))/(2*a);
	double t2 = (-b +sqrt(delta))/(2*a);
	t= t1;
	setPoint(I, A->x+t*u->x, A->y+t*u->y, A->z+t*u->z);
	setVecteur(N, I->x, I->y, I->z);
	if(I->z <= 1. && I->z >= -1.){
		return 1;
	}

	if((I->z > 1. && rayon_inter_Disque(A, u, I, N, 1)) || (I->z < -1. && rayon_inter_Disque(A, u, I, N, -1))){
		return 1;
	}

	t = t2;
	setPoint(I, A->x+t*u->x, A->y+t*u->y, A->z+t*u->z);
	setVecteur(N, A->x+t*u->x, A->y+t*u->y, A->z+t*u->z);
	if(I->z <= 1. && I->z >= -1.){
		return 1;
	}
	if((I->z > 1. && rayon_inter_Disque(A, u, I, N, 1)) || (I->z < -1. && rayon_inter_Disque(A, u, I, N, -1)) ){
		return 1;
	}

	return 0;
}

int rayon_inter_Disque(const Point *A, const Vecteur *u, Point *I, Vecteur *N, double d){
	/* the plane is z = d */
	double t;
	double OI;
	Point O;
	setPoint(&O, 0., 0., d);
	t = (d - A->z) / (u->z);
	
	setPoint(I, A->x + t * u->x, A->y + t * u->y, d);
	PointDistance(&O, I, &OI);
	if (OI > 1.){
		return 0;
	}
	setVecteur(N, 0., 0., d);
	return 1;
}	

int CylindreConsoleDisplay(const Cylindre *cylindre, int return_line){
	if(cylindre == NULL){
		return 0;
	}
	
	printf("P: ");
	PointConsoleDisplay(&cylindre->P, 0);
	printf("Q: ");
	PointConsoleDisplay(&cylindre->Q, 0);
	printf("rayon: %f", cylindre->rayon);
	printf("color: ");
	ColorConsoleDisplay(&cylindre->color, return_line);
	return 1;
}
