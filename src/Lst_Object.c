#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Lst_Object.h"

/* DEBUG */
/*
int lst_Object_size(lst_Object lst){
	int i;
	lst_Object tmp;
	
	if (lst == NULL){
		return -1;
	}
	for (i = 1, tmp = lst; tmp->suivant != NULL; i++){
			tmp = tmp->suivant;
	}
	
	return i;
}
*/

/*
int lst_Object_add_object(lst_Object *lst, const Object *obj){
	lst_Object tmp;
	
	if (lst == NULL || obj == NULL){
		return 0;
	}
	
	if ((*lst) == NULL){
		(*lst) = (Object_Node *)malloc(sizeof(Object_Node));
		if((*lst) == NULL){
			return 0;
		}
		(*lst)->suivant = NULL;
		(*lst)->obj = (Object *)malloc(sizeof(Object));
		if ((*lst)->obj == NULL){
			free(*lst);
			return 0;
		}
		ObjectCopy((*lst)->obj, obj);
		return 1;
	}
	
	
	for (tmp = (*lst); tmp->suivant != NULL ; tmp = tmp->suivant){
								;
	}
	tmp->suivant = (Object_Node *)malloc(sizeof(Object_Node));
	
	if (tmp->suivant == NULL){
		return 0;
	}
	tmp = tmp->suivant;
	tmp->suivant = NULL;
	tmp->obj = (Object *)malloc(sizeof(Object));
	if (tmp->obj == NULL){
		free(tmp);
		return 0;
	}

	ObjectCopy(tmp->obj, obj);
	return 2;
}

void lst_Object_free(lst_Object *lst){
	lst_Object tmp;
	lst_Object prec;
	if (lst == NULL || (*lst) == NULL){
		return;
	}
	
	for (tmp = (*lst); tmp != NULL;){
		prec = tmp;
		tmp = tmp->suivant;
		free(prec->obj);
		free(prec);
	}
	(*lst) = NULL;
}
*/

int lst_Object_add_object(lst_Object *lst, const Object *obj){
	lst_Object tmp;
	
	if (lst == NULL || obj == NULL){
		return 0;
	}
	
	if ((*lst) == NULL){
		(*lst) = (Object_Node *)malloc(sizeof(Object_Node));
		if((*lst) == NULL){
			return 0;
		}
		(*lst)->suivant = NULL;
		ObjectCopy(&(*lst)->obj, obj);
		return 1;
	}
	
	
	for (tmp = (*lst); tmp->suivant != NULL ; tmp = tmp->suivant){
								;
	}
	tmp->suivant = (Object_Node *)malloc(sizeof(Object_Node));
	
	if (tmp->suivant == NULL){
		return 0;
	}
	tmp = tmp->suivant;
	tmp->suivant = NULL;
	ObjectCopy(&tmp->obj, obj);
	return 2;
}

void lst_Object_free(lst_Object *lst){
	lst_Object tmp;
	lst_Object suiv;
	if (lst == NULL || (*lst) == NULL){
		return;
	}
	tmp = (*lst)->suivant;
	free(*lst);
	for (;tmp != NULL;){
		suiv = tmp;
		tmp = tmp->suivant;
		free(suiv);
	}
	(*lst) = NULL;
}
