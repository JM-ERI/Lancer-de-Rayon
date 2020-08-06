#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "../include/Hmat.h"

int HmatIdentity(Hmat mat){
	if (mat == NULL){
		return 0;
	}
	memset(mat, 0, sizeof(Hmat));
	mat[A00] = mat[A11] = mat[A22] = mat[A33] = 1;
	return 1;
}

int Hmat_fill_with_value(Hmat mat, double value){
	int i;
	if (mat == NULL){
		return 0;
	}
	for (i = 0; i < Hmat_SIZE; i++){
		mat[i] = value;
	}
	return 1;
}

int Hmat_translation_Vecteur(Hmat mat, const Vecteur *v){
	if (mat == NULL){
		return 0;
	}
	HmatIdentity(mat);
    mat[A03] = v->x;
    mat[A13] = v->y;
    mat[A23] = v->z;
    return 1;
}

int Hmat_translation_Hmatxyz(Hmat mat, double x, double y, double z){ /*translation equivalente a la precedente*/
	if(mat == NULL){
		return 0;
	}
	HmatIdentity(mat);
    mat[A03] = x;
    mat[A13] = y;
    mat[A23] = z;
    return 1;
}

int static valid_coordonate(int i, int j){
	return (i >= 0 && i < Hmat_ELEMENT_PER_LINE) && (j >= 0 && j < Hmat_ELEMENT_PER_LINE);
}

int Hmat_get_value(const Hmat mat, int i, int j, double *res){
	if (res == NULL || mat == NULL || !valid_coordonate(i, j)){
		return 0;
	}
	(*res) = mat[i * Hmat_ELEMENT_PER_LINE + j];
	return 1;
}

int Hmat_set_value(Hmat mat, int i, int j, double value){
	if (!valid_coordonate(i, j)){
		return 0;
	}
	mat[i * Hmat_ELEMENT_PER_LINE + j] = value;
	return 1;
}

int Hmat_x_Point(const Hmat mat, const Point *p, Point *res){
    if(mat == NULL || p == NULL|| res == NULL || res == p){
    	return 0;
    }
    setPoint(res, mat[A00] * p->x + mat[A01] * p->y + mat[A02] * p->z + mat[A03],
                  mat[A10] * p->x + mat[A11] * p->y + mat[A12] * p->z + mat[A13],
                  mat[A20] * p->x + mat[A21] * p->y + mat[A22] * p->z + mat[A23]);
    return 1;
}

int Hmat_x_Vecteur(const Hmat mat, const Vecteur *vec, Vecteur *res){
	if(mat == NULL || vec == NULL || res == NULL || res == vec){
    	return 0;
    }
    setVecteur(res,  mat[A00] * vec->x + mat[A01] * vec->y + mat[A02] * vec->z,
                     mat[A10] * vec->x + mat[A11] * vec->y + mat[A12] * vec->z,
                     mat[A20] * vec->x + mat[A21] * vec->y + mat[A22] * vec->z);
    return 1;
}

int Hmat_x_Vec(const Hmat mat, Vecteur *vec){
	if(mat == NULL || vec == NULL){
    	return 0;
    }
    setVecteur(vec,  mat[A00] * vec->x + mat[A01] * vec->y + mat[A02] * vec->z,
                     mat[A10] * vec->x + mat[A11] * vec->y + mat[A12] * vec->z,
                     mat[A20] * vec->x + mat[A21] * vec->y + mat[A22] * vec->z);
    return 1;
}

int Hmat_x_Hmat(const Hmat A, const Hmat B, Hmat res){
	if(A == NULL || B == NULL || res == NULL || res == A || res == B){
    	return 0;
    }
	memset(res, 0, sizeof(Hmat));
    int i, j, k;
	for(i = 0; i < 4; i++)
	{
    	for(j = 0; j < 4; j++)
    	{
      		double mul = 0.;
      		for(k = 0; k < 4; k++)
            { 
            	double val1;
            	double val2;
            	Hmat_get_value(A, i, k, &val1);
            	Hmat_get_value(B, k, j, &val2);
       	 		mul += val1 * val2;
      		}
     		Hmat_set_value(res, i, j, mul);
    	}
  	}
    return 1;
}

int Homothetie(Hmat res, double a, double b, double c){
	if(res == NULL){
		return 0;
	}
	HmatIdentity(res);
	res[A00] = a;
	res[A11] = b;
	res[A22] = c;
	return 1;
}

void HmatDisplay(Hmat mat){
	int i;
	int j;
	
	if (mat == NULL){
		return;
	}
	
	for (i = 0; i < Hmat_ELEMENT_PER_LINE; i++){
		for (j = 0; j < Hmat_ELEMENT_PER_LINE; j++){
			printf("%11.4lf ", mat[i * Hmat_ELEMENT_PER_LINE + j]);
		}
		printf("\n");
	}
}
