/**
 * \file Cylindre.h
 * \brief represents a cylinder
 * \author Jean-Manuel ERIALC - Hadjer DJERROUMI
 * \version 0.1
 * \date 11 juin 2020
 *
 * contains the type representing a cylinder in a 3D space and functions related to it
 */
#ifndef __CYLINDRE__
#define __CYLINDRE__

#include "Color.h"
#include "Point.h"
#include "Vecteur.h"

/**
 * \struct Cylindre
 * \brief a cylinder
 *
 * a cylinder is defined by two points and the raduis,
 * the axis of the cylinder is the line (PQ)
 * the hight of the cylinder is the distance PQ
 * 
 */
typedef struct{
	Color color;   /*!< the color of the cylinder */
	double rayon;  /*!< the radius of the cylinder */
	Point P;	   /*!< the center of the 1st face of the cylinder */
	Point Q;	   /*!< the center of the 2nd face of the cylinder */
}Cylindre;

/**
 * \fn int setCylindre(Cylindre *cylindre, const Point *P, const Point *Q, const Color *color, double rayon)
 * \brief sets a cylinder with the specified parameters
 *
 * \param cylindre the cylinder to set
 * \param P the new first point
 * \param Q the new second point
 * \param color the new color
 * \param rayon the new radius
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int setCylindre(Cylindre *cylindre, const Point *P, const Point *Q, const Color *color, double rayon);

/**
 * \fn int rayon_inter_Cylindre(const Point *A, const Vecteur *u, Point *I, Vecteur *N)
 * \brief check the intersection between a line (A, u) and the canonical cylinder
 *
 * \param A a point of the line
 * \param u the normalized director vector of the line
 * \param I the intersection point if it exists
 * \param N the normal vector in I
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int rayon_inter_Cylindre(const Point *A, const Vecteur *u, Point *I, Vecteur *N);

/**
 * \fn int rayon_inter_Disque(const Point *A, const Vecteur *u, Point *I, Vecteur *N, double d)
 * \brief check the intersection between a line (A, u) and the canonical disk in the plane z = d
 *
 * \param A a point of the line
 * \param u the normalized director vector of the line
 * \param I the intersection point if it exists
 * \param N the normal vector in I
 * \param d the d in the plane equation z = d
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int rayon_inter_Disque(const Point *A, const Vecteur *u, Point *I, Vecteur *N, double d);

/**
 * \fn int CylindreConsoleDisplay(const Cylindre *cylindre, int return_line)
 * \brief print a cylinder in the console
 *
 * \param cylindre the cylinder to print
 * \param return_line != 0 if we want to add a '\n' after the print
 * \return 0 if a error occurs(cylinder == NULL)<br>
 * 		   1 otherwise
 */
int CylindreConsoleDisplay(const Cylindre *cylindre, int return_line);
#endif
