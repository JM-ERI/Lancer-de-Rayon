/**
 * \file Point.h
 * \brief contains the Point type in a 3D space and all functions related to this type
 * \author Jean-Manuel ERIALC - Hadjer DJERROUMI
 * \version 0.1
 * \date 11 juin 2020
 *
 * contains the vector type in a 3D space and all functions related to this type
 *
 */
#ifndef __POINT__
#define __POINT__

/**
 * \struct Point
 * \brief a point in 3D space
 *
 * Point is a type representing a point by its three real coordinates
 * 
 */
typedef struct{
    double x, y, z;
}Point;

/**
 * \fn int PointCopy(Point *dest, const Point *src)
 * \brief copy a point to another
 *
 * \param dest the destination point
 * \param src the point to copy
 * \return 0 if a error occurs(dest == NULL || A == src)<br>
 * 		   1 otherwise
 */
int PointCopy(Point *dest, const Point *src);

/**
 * \fn int setPoint(Point *p, double x, double y, double z)
 * \brief sets the point with the specified values
 *
 * \param p the point to change
 * \param x the x coordinate
 * \param y the y coordinate
 * \param z the z coordinate
 * \return 0 if a error occurs(p == NULL)<br>
 * 		   1 otherwise
 */
int setPoint(Point *p, double x, double y, double z);

/**
 * \fn int PointCenter(Point *res, const Point *A, const Point *B)
 * \brief computes the center of the segment [AB]
 *
 * \param res the result
 * \param A the first point
 * \param B the second point
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int PointCenter(Point *res, const Point *A, const Point *B);

/**
 * \fn int PointDistance(const Point *A, const Point *B, double *res);
 * \brief computes the distance between two points
 *
 * \param A the first point
 * \param B the second point
 * \param res the result
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int PointDistance(const Point *A, const Point *B, double *res);

/**
 * \fn int PointNormeL2(const Point *A, const Point *B, double *res)
 * \brief computes the maximum norm of two points
 *
 * \param A the first point
 * \param B the second point
 * \param res the result 
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int PointNormeL2(const Point *A, const Point *B, double *res);

/**
 * \fn int PointBarycentre(const Point *A, const Point *B, const Point *C, Point *BaryCentre)
 * \brief computes the barycenter of three points
 *
 * \param A the first point
 * \param B the second point
 * \param C the third point
 * \param BaryCentre the computed barycenter 
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int PointBarycentre(const Point *A, const Point *B, const Point *C, Point *BaryCentre);

/**
 * \fn int PointConsoleDisplay(const Point *p, int return_line)
 * \brief print a point in the console
 *
 * \param p the point to print
 * \param return_line != 0 if we want to add a '\n' after the print
 * \return 0 if a error occurs(p == NULL)<br>
 * 		   1 otherwise
 */
int PointConsoleDisplay(const Point *p, int return_line);

#endif
