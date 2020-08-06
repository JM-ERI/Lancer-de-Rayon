#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../include/Vecteur.h"
#include "../include/Hmat.h"

int VecteurCopy(Vecteur *dest, const Vecteur *src){
	if (src == NULL || dest == NULL){
		return 0;
	}
	
	memcpy(dest, src, sizeof(Vecteur));
	return 1;
}


int setVecteur(Vecteur *u, double x, double y, double z){
	if(u == NULL){
		return 0;
	}
	u->x = x;
	u->y = y;
	u->z = z;
	
	return 1;
}

int VecteurNormalize(Vecteur *u){
	double norme;

	if (u == NULL){
		return 0;
	}
	
	if(!VecteurSquareNorme(u, &norme)){
		return 0;
	}
	
	norme = sqrt(norme);
	
	u->x /= norme;
	u->y /= norme;
	u->z /= norme;
	
	return 1;
}

int VecteurSquareNorme(const Vecteur *u, double *res){	
	if (u == NULL || res == NULL){
		return 0;
	}
	(*res) = (u->x * u->x + u->y * u->y + u->z * u->z);
	return 1;
}

int VecteurProd_scal(const Vecteur *u, const Vecteur *v, double *res){
	if (u == NULL || v == NULL || res == NULL){
		return 0;
	}
	(*res) = u->x * v->x + u->y * v->y + u->z * v->z;
	return 1;
}

int VecteurProd_vec(const Vecteur *u, const Vecteur *v, Vecteur *newVecteur){
	if (u == NULL || v == NULL || newVecteur == NULL){
		return 0;
	}
	
	newVecteur->x =  (u->y * v->z) - (u->z * v->y);
	newVecteur->y =  (u->z * v->x) - (u->x * v->z);
	newVecteur->z =  (u->x * v->y) - (u->y * v->x);
	
	return 1;
}

int Sinus(const Vecteur *u, const Vecteur *v, double *res){
	double norme;
	Vecteur normalize_u;
	Vecteur normalize_v;
	Vecteur produit_vectoriel;
    
    if(u == NULL || v == NULL || res == NULL){
		return 0;
	}
	
	VecteurCopy(&normalize_u, u);
	VecteurCopy(&normalize_v, v);
    if(!VecteurNormalize(&normalize_u) || !VecteurNormalize(&normalize_v) || !VecteurProd_vec(&normalize_u, &normalize_v, &produit_vectoriel)){
		return 0;
	}
	
	VecteurSquareNorme(&produit_vectoriel, &norme);
	(*res) = sqrt(norme);
    return 1;
}	

int Cosinus(const Vecteur *u, const Vecteur *v, double *res){
	Vecteur normalize_u;
	Vecteur normalize_v;
    
    if(u == NULL || v == NULL || res == NULL){
		return 0;
	}
    
    VecteurCopy(&normalize_u, u);
	VecteurCopy(&normalize_v, v);
	
    if(!VecteurNormalize(&normalize_u) || !VecteurNormalize(&normalize_v)){
		return 0;
	}
	if(!VecteurProd_scal(&normalize_u, &normalize_v, res)){
		return 0;
	}
	return 1;
}

int VecteurOfPoints(Vecteur *vecteur, const Point *A, const Point *B){
	if (vecteur == NULL || A == NULL || B == NULL){
		return 0;
	}
    return setVecteur(vecteur, B->x - A->x, B->y - A->y, B->z - A->z);
}

int VecteurEquals(const Vecteur *u, const Vecteur *v){
	if (u == NULL || v == NULL){
		return -1;
	}
	return u->x == v->x && u->y == v->y && u->z == v->z;	
}

int VecteurIsZero(const Vecteur *u){
	if(u == NULL){
		return 0;
	}
	double norme;
	VecteurSquareNorme(u, &norme);
	return norme == 0.;
}

int VecteurAnglesEquals(Vecteur *u1, Vecteur *u2, Vecteur *v1, Vecteur *v2){
	if(u1 == NULL || u2 == NULL || v1 == NULL || v2 == NULL){
		return 0;
	}
	double cos_u;
	double cos_v;
	Cosinus(u1, u2, &cos_u);
	Cosinus(v1, v2, &cos_v);
	return (cos_u == cos_v);
}

int VecteurHalf(const Vecteur *u, const Vecteur *v, Vecteur *res){
	if(u == NULL || v == NULL || res == NULL){
		return 0;
	}
	setVecteur(res, (u->x - v->x)/2., (u->y - v->y)/2., (u->z - v->z)/2.);
	return VecteurNormalize(res);
}

int VecteurReflected(const Vecteur *u, const Vecteur *N, Vecteur *res){
	if(u == NULL || N == NULL || res == NULL){
		return 0;
	}
	double ps;
	Vecteur tmp;
	VecteurProd_scal(u, N, &ps);
	setVecteur(&tmp, -2 * ps * N->x, -2 * ps * N->y, -2 * ps * N->z);
	setVecteur(res, tmp.x + u->x, tmp.y + u->y, tmp.z + u->z);
	return 1;
}


int VecteurConsoleDisplay(const Vecteur *vecteur, int return_line){
	if (vecteur == NULL){
		return 0;
	}
	
	return printf("Vecteur x:%lf y:%lf z:%lf %c", vecteur->x, vecteur->y, vecteur->z, return_line == 0 ? ' ' : '\n');
	
}
