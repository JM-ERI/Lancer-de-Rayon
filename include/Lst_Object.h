/**
 * \file Lst_Object.h
 * \brief represents a list of Objects (shapes)
 * \author Jean-Manuel ERIALC - Hadjer DJERROUMI
 * \version 0.1
 * \date 11 juin 2020
 *
 * represents a list of Objects (shapes)
 *
 */
#ifndef __LST_OBJECT__
#define __LST_OBJECT__

#include "Object.h"

/**
 * \struct lst_Object
 * \brief a list of objects
 *
 * a list of objects
 * 
 */
typedef struct _lst_obj{	
	Object obj; 				/*!< the object of the current node */
	struct _lst_obj *suivant;	/*!< pointer to a next node */
}Object_Node, *lst_Object;

/**
 * \fn int lst_Object_add_object(lst_Object *lst, const Object *obj)
 * \brief add an object to the list
 *
 * \param lst the list
 * \param obj the object to add
 * \return 0 if a error occurs(lst == NULL || obj == NULL or memory allocation error)
 * 		   1 otherwise
 */
int lst_Object_add_object(lst_Object *lst, const Object *obj);


/**
 * \fn void lst_Object_free(lst_Object *lst)
 * \brief free all the memory alocated by a lst_Object
 *
 * \param lst the list to free
 */
void lst_Object_free(lst_Object *lst);
#endif
