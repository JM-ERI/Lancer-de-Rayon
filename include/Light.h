/**
 * \file Rectangle.h
 * \brief represents the Light type
 * \author Jean-Manuel ERIALC - Hadjer DJERROUMI
 * \version 0.1
 * \date 11 juin 2020
 *
 * represents the Light type in 3D space and contains functions related it
 */
#ifndef __SOURCE_LUX__
#define __SOURCE_LUX__

#include "Point.h"
#include "Vecteur.h"
#include "Lst_Object.h"

/**
 * \struct Source
 * \brief a light source
 *
 * Source is a type representing a light source by its position in space and its intensity
 * 
 */
typedef struct {
	double intensity;  /*!< the intensity is a big value (millions) */
	Point p;           /*!< the position of the light source */
}Source;

/**
 * \struct lst_Source
 * \brief a liste of light sources
 *
 */
typedef struct _lst_point{
	Source src;                  /*!< the source of the current node */
	struct _lst_point *suivant;  /*!< pointer to a next node */
}node_Source, *lst_Source;

/**
 * \fn int setSource(Source *src, const Point *p, double intensity)
 * \brief sets a source with the specified parameters
 *
 * \param src the light source to set
 * \param p the position of the source
 * \param intensity the intensity of the source
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int setSource(Source *src, const Point *p, double intensity);

/**
 * \fn int add_source(lst_Source *lst, const Source *src)
 * \brief add a source to the list
 *
 * \param lst the list
 * \param src the the lignt source to add
 * \return 0 if a error occurs(lst == NULL || src == NULL or memory allocation error)
 * 		   1 otherwise
 */
int add_source(lst_Source *lst, const Source *src);

/**
 * \fn void free_lst_Source(lst_Source *lst)
 * \brief free all the memory alocated by a lst_Source
 *
 * \param lst the list to free
 */
void free_lst_Source(lst_Source *lst);

/**
 * \fn int delta(const Source *src, const Point *point, const lst_Object lst)
 * \brief check wether a point is illuminated by a source
 *
 * \param src a light source
 * \param point a point
 * \param lst the list of all objects of the scene
 * \return -1 if a error occurs(src == NULL || point == NULL || lst == NULL)<br>
 *          0 if the point is not illuminated<br>
 * 		    1 otherwise
 */
int delta(const Source *src, const Point *point, const lst_Object lst);

/**
 * \fn int SourceConsoleDisplay(const Source *s)
 * \brief print a source in the console
 *
 * \param s the light source to print
 * \return 0 if a error occurs(s == NULL)<br>
 * 		   1 otherwise
 */
int SourceConsoleDisplay(const Source *s);

#endif
