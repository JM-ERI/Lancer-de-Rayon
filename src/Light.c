#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/Vecteur.h"
#include "../include/Light.h"

#define EPSILON 1.E-6

int setSource(Source *src, const Point *p, double intensity){
	if (src == NULL || p == NULL){
		return 0;
	}
	src->p = (*p);
	src->intensity = intensity;
	return 1;
}

int static add_node(lst_Source *lst, const Source *src){
	(*lst) = (lst_Source)malloc(sizeof(node_Source));
	if((*lst) == NULL){
		return 0;
	}
	(*lst)->src = (*src);
	(*lst)->suivant = NULL;
	return 1;	
}

int add_source(lst_Source *lst, const Source *src){
	lst_Source tmp;
	if (lst == NULL){
		return 0;
	}
	if ((*lst) == NULL){
		return add_node(lst, src);
	}
	
	for (tmp = (*lst); tmp->suivant != NULL; tmp = tmp->suivant){
						;
	}
	return add_node(&tmp->suivant, src);
}

void free_lst_Source(lst_Source *lst){
	lst_Source tmp;
	
	if (lst == NULL || (*lst) == NULL){
		return;
	}
	tmp = (*lst);
	
	for (; (*lst) != NULL; tmp = (*lst)){
		(*lst) = (*lst)->suivant;
		free(tmp);
	}
	(*lst) = NULL;
}

int SourceConsoleDisplay(const Source *s){
	if (s == NULL){
		return 0;
	}
	PointConsoleDisplay(&s->p, 1);
	printf("intensity:%lf\n", s->intensity);
	return 1;
}

int delta(const Source *src, const Point *point, const lst_Object lst){
	if(src == NULL || point == NULL || lst == NULL){
		return -1;
	}
	lst_Object tmp;
	Vecteur light;
	Vecteur N;
	Point I; /* intersection point of current canonique object*/
	Point point_t; /* transformed source point */
	Point X; /* intersection point of current object */
	Vecteur light_t; /* transformed light vector */
	double distance;
	double dist;

	PointDistance(&src->p, point, &distance);
	VecteurOfPoints(&light, &src->p, point);
	for (tmp = lst; tmp != NULL; tmp = tmp->suivant){
		Hmat_x_Point(tmp->obj.Mi, &src->p, &point_t);
		Hmat_x_Vecteur(tmp->obj.Mi, &light, &light_t);
		VecteurNormalize(&light_t);
		if (tmp->obj.rayon_inter(&point_t, &light_t, &I, &N)){
			Hmat_x_Point(tmp->obj.Md, &I, &X);
			PointDistance(&src->p, &X, &dist);
			if(dist < distance - EPSILON){
				return 0;
			}
		}
	}
	return 1;
}
