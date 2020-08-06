/**
 * \file Rectangle.h
 * \brief represents a rectangle
 * \author Jean-Manuel ERIALC - Hadjer DJERROUMI
 * \version 0.1
 * \date 11 juin 2020
 *
 * contains the type representing a rectangle in a 3D space and functions related to it
 */
#ifndef __RECTANGLE__
#define __RECTANGLE__

#include "Color.h"
#include "Point.h"
#include "Vecteur.h"

/**
 * \struct Rectangle
 * \brief a rectangle
 *
 * Rectangle is a type representing a rectangle by its center, its raduis and an angle (u, v)
 * which defines the plane of the rectangle and the other angles
 * 
 */
typedef struct{
	Color color;
    double rayon;  /*!< the distance from the center to an end point*/
	Point center;
	Vecteur u;
	Vecteur v;
}Rectangle;

/**
 * \fn int setRectangle(Rectangle *rectangle, const Point *center, const Vecteur *u, const Vecteur *v, double rayon, const Color *color)
 * \brief sets a rectangle with the specified parameters
 *
 * \param rectangle the rectangle to set
 * \param center the center point
 * \param u the first vector of the angle
 * \param v the second vector of the angle
 * \param rayon the radius
 * \param color the color
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int setRectangle(Rectangle *rectangle, const Point *center, const Vecteur *u, const Vecteur *v, double rayon, const Color *color);

/**
 * \fn int rayon_inter_Square(const Point *A, const Vecteur *u, Point *I, Vecteur *N)
 * \brief check the intersection between a line (A, u) and the canonical square
 *
 * \param A a point of the line
 * \param u the normalized director vector of the line
 * \param I the intersection point if it exists
 * \param N the normal vector in I
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int rayon_inter_Square(const Point *A, const Vecteur *u, Point *I, Vecteur *N);

/**
 * \fn int RectangleConsoleDisplay(const Rectangle *rectangle, int return_line)
 * \brief print a rectangle in the console
 *
 * \param rectangle the rectangle to print
 * \param return_line != 0 if we want to add a '\n' after the print
 * \return 0 if a error occurs(rectangle == NULL)<br>
 * 		   1 otherwise
 */
int RectangleConsoleDisplay(const Rectangle *rectangle, int return_line);

#endif
