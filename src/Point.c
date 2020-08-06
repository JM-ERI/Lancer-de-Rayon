#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "../include/Point.h"
#include "../include/Vecteur.h"

int PointCopy(Point *dest, const Point *src){
	if (src == NULL || dest == NULL){
		return 0;
	}
	memcpy(dest, src, sizeof(Point));
	return 1;
}

int setPoint(Point *p, double x, double y, double z){
	if (p == NULL){
		return 0;
	}
    p->x = x;
	p->y = y;
	p->z = z;
	
	return 1;
}

int PointDistance(const Point *A, const Point *B, double *res){
	if (A == NULL ||  B == NULL){
		return 0;
	}
	 (*res) = sqrt(pow(B->x - A->x, 2) + pow(B->y - A->y, 2) + pow(B->z - A->z, 2));
	 return 1;
}

int PointCenter(Point *res, const Point *A, const Point *B){
	if(A == NULL || B == NULL || res == NULL){
		return 0;
	}
	double x = (A->x + B->x) / 2.;
	double y = (A->y + B->y) / 2.;
	double z = (A->z + B->z) / 2.;
	setPoint(res, x, y, z);
	return 1;
}

int PointNormeL2(const Point *A, const Point *B, double *res){
	Vecteur u;
	double max;
	
	if (A == NULL || B == NULL){
		return 0;
	}
	
	VecteurOfPoints(&u, A, B);
	max = fabs(u.x);
	
	if(fabs(u.y) > max){
		max = fabs(u.y);
	}
	if(fabs(u.z) > max){
		max = fabs(u.z);
	}
	(*res) =  max;
	
	return 1;
}

int PointBarycentre(const Point *A, const Point *B, const Point *C, Point *BaryCentre){
	if(A == NULL || B == NULL || C == NULL || BaryCentre == NULL){
		return 0;
	}
	return setPoint(BaryCentre, (A->x + B->x + C->x)/3., (A->y + B->y + C->y)/3., (A->z + B->z + C->z)/3.);
}

int PointConsoleDisplay(const Point *p, int return_line){
	if (p == NULL){
		return 0;
	}
	return printf("x:%lf y:%lf z:%lf %c", p->x, p->y, p->z, return_line == 0 ? ' ' : '\n');
}

