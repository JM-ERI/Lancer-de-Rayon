/**
 * \file Triangle.h
 * \brief represents a triangle
 * \author Jean-Manuel ERIALC - Hadjer DJERROUMI
 * \version 0.1
 * \date 11 juin 2020
 *
 * contains the type representing a triangle in a 3D space and functions related to it
 */
#ifndef __TRIANGLE__
#define __TRIANGLE__

#include "Color.h"
#include "Point.h"
#include "Vecteur.h"

/**
 * \struct Triangle
 * \brief a triangle
 *
 * a triangle is defined by its three points
 * 
 */
typedef struct{
	Color color;
	Point A;
	Point B;
	Point C;
}Triangle;

/**
 * \fn int setTriangle(Triangle *triangle, const Point *A, const Point *B, const Point *C, const Color *color)
 * \brief sets a triangle with new parameters
 *
 * \param triangle the triangle to set
 * \param A the first point
 * \param B the second point
 * \param C the third point
 * \param color the color
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int setTriangle(Triangle *triangle, const Point *A, const Point *B, const Point *C, const Color *color);

/**
 * \fn int rayon_inter_Triangle(const Point *A, const Vecteur *u, Point *I, Vecteur *N)
 * \brief check the intersection between a line (A, u) and the canonical triangle
 *
 * \param A a point of the line
 * \param u the normalized director vector of the line
 * \param I the intersection point if it exists
 * \param N the normal vector in I
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int rayon_inter_Triangle(const Point *A, const Vecteur *u, Point *I, Vecteur *N);

/**
 * \fn int TrianglePointInTriangle(const Point *A, const Point *B, const Point *C, const Point *I)
 * \brief check if the triangle (ABC) contains the point I
 *
 * \param A the first point of the triangle
 * \param B the second point of the triangle
 * \param C the third point of the triangle
 * \param I a point
 * \return -1 if a error occurs(one parameter is NULL)<br>
 *			0 if the triangle contains I<br>
 * 		    1 otherwise
 */
int TrianglePointInTriangle(const Point *A, const Point *B, const Point *C, const Point *I);

/**
 * \fn int int TriangleConsoleDisplay(const Triangle *triangle, int return_line)
 * \brief print a triangle in the console
 *
 * \param triangle the triangle to print
 * \param return_line != 0 if we want to add a '\n' after the print
 * \return 0 if a error occurs(triangle == NULL)<br>
 * 		   1 otherwise
 */
int TriangleConsoleDisplay(const Triangle *triangle, int return_line);

#endif
