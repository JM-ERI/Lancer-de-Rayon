#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "../include/Cube.h"


int setCube(Cube *cube, const Point *center, const Color *color, double rayon){
	if (cube == NULL){
		return 0;
	}
	
	cube->rayon = rayon;
	cube->center = (*center);
	cube->color = (*color);
	
	return 1;
}

int rayon_inter_Cube(const Point *A, const Vecteur *u, Point *I, Vecteur *N){
	int i;
	
	double t;
	double l2;
	double ps1;
	double ps2;
	
	Point ci;
	
	Vecteur AC;
	Vecteur facettes[6] = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};
	
	if (A == NULL || u == NULL || I == NULL || N == NULL){
		return 0;
	}
	
	for (i = 0; i < 6; i++){
		VecteurProd_scal(u, &facettes[i], &ps1);
		if (ps1 > 0.){
			continue;
		}
		
		setPoint(&ci, facettes[i].x , facettes[i].y , facettes[i].z ); /*center of facette[i] */
		setVecteur(&AC, ci.x - A->x, ci.y - A->y, ci.z - A->z);
		
		VecteurProd_scal(&AC, &facettes[i], &ps2);
		if (ps2 > 0.){
			continue;
		}
		
		t = ps2 / ps1;
		
		setPoint(I, A->x + t * u->x, A->y + t * u->y, A->z + t * u->z);
		setVecteur(N, ci.x, ci.y, ci.z);
		PointNormeL2(&ci, I, &l2);
		if (l2 <= 1.){
			return 1;
		}
	}
	return 0;
}

int CubeConsoleDisplay(const Cube *cube, int return_line){
	if(cube == NULL){
		return 0;
	}
	
	printf("Center: ");
	PointConsoleDisplay(&(cube)->center, 0);
	printf("rayon: %f ", cube->rayon);
	printf("color: ");
	ColorConsoleDisplay(&(cube)->color, return_line);
	return 1;
}
