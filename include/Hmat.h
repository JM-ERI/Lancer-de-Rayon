/**
 * \file Hmat.h
 * \brief contains the type Hmat representing homogeneous matrices and functions related to if
 * \author Jean-Manuel ERIALC - Hadjer DJERROUMI
 * \version 0.1
 * \date 11 juin 2020
 *
 * contains the type Hmat representing homogeneous matrices and functions 
 * related to this type witch are used to transform objects in the 3D space
 */
#ifndef __HMAT__
#define __HMAT__

#include "Vecteur.h"

#define A00 0
#define A01 1
#define A02 2
#define A03 3
#define A10 4
#define A11 5
#define A12 6
#define A13 7
#define A20 8
#define A21 9
#define A22 10
#define A23 11
#define A30 12
#define A31 13
#define A32 14
#define A33 15
#define Hmat_SIZE 16
#define Hmat_ELEMENT_PER_LINE 4

/**
 * the Hmat type is an array of size Hmat_SIZE witch represents a 4 x 4 matrix
 */
typedef double Hmat[Hmat_SIZE];

/**
 * \fn int HmatIdentity(Hmat mat)
 * \brief create and initialize a matrix with identity
 *
 * \param mat matrix to initialized 
 * \return 0 if a error occurs(mat == NULL)<br>
 * 		   1 otherwise
 */
int HmatIdentity(Hmat mat);

/**
 * \fn int Hmat_fill_with_value(Hmat mat, double value)
 * \brief assign the given value to all elements of the given matrix
 *
 * \param mat the given matrix
 * \param value the given value
 * \return 0 if a error occurs(mat == NULL)<br>
 * 		   1 otherwise
 */
int Hmat_fill_with_value(Hmat mat, double value);

/**
 * \fn int Hmat_get_value(const Hmat mat, int i, int j, double *res)
 * \brief get the value in the specified position of a given matrix
 *
 * \param mat the given matrix
 * \param i the row of the value
 * \param j the column of the value
 * \param res the result
 * \return 0 if a error occurs(mat == NULL)<br>
 * 		   1 otherwise
 */
int Hmat_get_value(const Hmat mat, int i, int j, double *res);

/**
 * \fn int Hmat_set_value(Hmat mat, int i, int j, double value)
 * \brief set the value in the specified position of a given matrix
 *
 * \param mat the given matrix
 * \param i the row of the value
 * \param j the column of the value
 * \param value the new value of the position
 * \return 0 if a error occurs(mat == NULL)<br>
 * 		   1 otherwise
 */
int Hmat_set_value(Hmat mat, int i, int j, double value);


/**
 * \fn int Hmat_translation_Vecteur(Hmat mat, const Vecteur *v)
 * \brief create the translation matrix corresponding to a vector v
 *
 * \param mat the hmat of the translated vector
 * \param v the translation vector 
 * \return 0 if a error occurs(mat == NULL || v == NULL)<br>
 * 		   1 otherwise
 */
int Hmat_translation_Vecteur(Hmat mat, const Vecteur *v);

/**
 * \fn int Hmat_translation_Hmatxyz(Hmat mat, double x, double y, double z)
 * \brief create the translation matrix corresponding to the given values
 *
 * \param mat the computed hmat
 * \param x the first value
 * \param y the second value
 * \param z the third value
 * \return 0 if a error occurs(mat == NULL)<br>
 * 		   1 otherwise
 */
int Hmat_translation_Hmatxyz(Hmat mat, double x, double y, double z);

/**
 * \fn int Hmat_x_Point(const Hmat mat, const Point *p, Point *res)
 * \brief transform the given point with the given homogeneous matrix
 *
 * \param mat the homogeneous matrix
 * \param p the given point
 * \param res the transformed point
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int Hmat_x_Point(const Hmat mat, const Point *p, Point *res);

/**
 * \fn int Hmat_x_Vecteur(const Hmat mat, const Vecteur *vec, Vecteur *res)
 * \brief transform the given vector with the given homogeneous matrix
 *
 * \param mat the homogeneous matrix
 * \param vec the given vector
 * \param res the transformed vector
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int Hmat_x_Vecteur(const Hmat mat, const Vecteur *vec, Vecteur *res);

/**
 * \fn int Hmat_x_Vec(const Hmat mat, Vecteur *vec)
 * \brief transform the given vector with the given homogeneous matrix
 *
 * \param mat the homogeneous matrix
 * \param vec the vector to set
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int Hmat_x_Vec(const Hmat mat, Vecteur *vec);

/**
 * \fn int Hmat_x_Hmat(const Hmat A, const Hmat B, Hmat res)
 * \brief matrix product
 *
 * \param A the first homogeneous matrix
 * \param B the second homogeneous matrix
 * \param res the first homogeneous matrix
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int Hmat_x_Hmat(const Hmat A, const Hmat B, Hmat res);

/**
 * \fn int Homothetie(Hmat res, double a, double b, double c)
 * \brief create the homothety matrix corresponding to the given parameters
 *
 * \param res the homothety matrix
 * \param a the first homothety parameter
 * \param b the second homothety parameter
 * \param c the third homothety parameter
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int Homothetie(Hmat res, double a, double b, double c);

/**
 * \fn void HmatDisplay(Hmat mat)
 * \brief print a matrix in the console
 *
 * \param mat the homogeneous matrix to print
 */
void HmatDisplay(Hmat mat);

#endif
