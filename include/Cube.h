/**
 * \file Cube.h
 * \brief contains the Cube type and functions related to it
 * \author Jean-Manuel ERIALC - Hadjer DJERROUMI
 * \version 0.1
 * \date 11 juin 2020
 *
 * represents a cube in 3D space and functions related to it
 */
#ifndef __CUBE__
#define __CUBE__

#include "Color.h"
#include "Point.h"
#include "Vecteur.h"

/**
 * \struct Cube
 * \brief a cube
 *
 * Cube is a type representing a cube by its center and its raduis.
 * Its facets are supposed to be parallel to those of the canonical cube.
 * The reason of this limitation is to facilitate the creation of instances.
 * 
 */
typedef struct{
	double rayon; /*!< radius of the cube */
	Color color;  /*!< the color of the cube */
	Point center; /*!< the center of the cube */
}Cube;

/**
 * \fn int setCube(Cube *cube, const Point *center, const Color *color, double rayon)
 * \brief sets a cube by the specified parameters
 *
 * \param cube the cube to set
 * \param center ther new center
 * \param color the new color
 * \param rayon the new radius
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int setCube(Cube *cube, const Point *center, const Color *color, double rayon);

/**
 * \fn int rayon_inter_Cube(const Point *A, const Vecteur *u, Point *I, Vecteur *N)
 * \brief check the intersection between a line (A, u) and the canonical cube
 *
 * \param A a point of the line
 * \param u the normalized director vector of the line
 * \param I the intersection point if it exists
 * \param N the normal vector in I
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int rayon_inter_Cube(const Point *A, const Vecteur *u, Point *I, Vecteur *N);

/**
 * \fn int CubeConsoleDisplay(const Cube *cube, int return_line)
 * \brief print a cube in the console
 *
 * \param cube the cube to print
 * \param return_line != 0 if we want to add a '\n' after the print
 * \return 0 if a error occurs(cube == NULL)<br>
 * 		   1 otherwise
 */
int CubeConsoleDisplay(const Cube *cube, int return_line);

#endif
