/**
 * \file Sphere.h
 * \brief represents a sphere
 * \author Jean-Manuel ERIALC - Hadjer DJERROUMI
 * \version 0.1
 * \date 11 juin 2020
 *
 * contains the type representing a sphere in a 3D space and functions related to it 
 */
#ifndef __SPHERE__
#define __SPHERE__

#include "Color.h"
#include "Point.h"
#include "Vecteur.h"

/**
 * \struct Sphere
 * \brief a sphere
 *
 * Sphere is a type representing a sphere by its center and its raduis
 * 
 */
typedef struct{
	Color color;
	double rayon;
	Point center;
}Sphere;

/**
 * \fn int setSphere(Sphere *sphere, const Point *center, const Color *color,  double rayon)
 * \brief sets a sphere with the specified parameters
 *
 * \param sphere the sphere to set
 * \param center ther new center
 * \param color the new color
 * \param rayon the new radius
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int setSphere(Sphere *sphere, const Point *center, const Color *color,  double rayon);

/**
 * \fn int rayon_inter_Sphere(const Point *A, const Vecteur *u, Point *I, Vecteur *N)
 * \brief check the intersection between a line (A, u) and the canonical sphere
 *
 * \param A a point of the line
 * \param u the normalized director vector of the line
 * \param I the intersection point if it exists
 * \param N the normal vector in I
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int rayon_inter_Sphere(const Point *A, const Vecteur *u, Point *I, Vecteur *N);

/**
 * \fn int SphereConsoleDisplay(const Sphere *sphere, int return_line)
 * \brief print a sphere in the console
 *
 * \param sphere the sphere to print
 * \param return_line != 0 if we want to add a '\n' after the print
 * \return 0 if a error occurs(sphere == NULL)<br>
 * 		   1 otherwise
 */
int SphereConsoleDisplay(const Sphere *sphere, int return_line);

#endif
