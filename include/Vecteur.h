/**
 * \file Vecteur.h
 * \brief contains the vector type in a 3D space and all functions related to this type
 * \author Jean-Manuel ERIALC - Hadjer DJERROUMI
 * \version 0.1
 * \date 11 juin 2020
 *
 * contains the vector type in a 3D space and all functions related to vectors and angels
 *
 */
#ifndef __VECTEUR__
#define __VECTEUR__

#include "Point.h"

/**
 * \struct Vecteur
 * \brief represents a vector in 3D space.
 *
 * Vecteur is a type representing a vector in 3D space
 * 
 */
typedef struct{
    double x; /*!< the x coordinate */
    double y; /*!< the y coordinate */
    double z; /*!< the z coordinate */
}Vecteur;

/**
 * \fn int VecteurOfPoints(Vecteur *vecteur, const Point *A, const Point *B)
 * \brief compute the vector passing through points A and B
 *
 * \param vecteur the computed vector
 * \param A Point A the point A
 * \param B Point B the point B
 * \return 0 if a error occurs(vecteur == NULL || A == NULL || B == NULL)<br>
 * 		   1 otherwise
 */
int VecteurOfPoints(Vecteur *vecteur, const Point *A, const Point *B);

/**
 * \fn int VecteurCopy(Vecteur *dest, const Vecteur *src)
 * \brief copy a vector to another
 *
 * \param dest the vector receiving this vector
 * \param src the vector to copy
 * \return 0 if a error occurs(dest == NULL || A == src)<br>
 * 		   1 otherwise
 */
int VecteurCopy(Vecteur *dest, const Vecteur *src);

/**
 * \fn int setVecteur(Vecteur *u, double x, double y, double z)
 * \brief sets the vector with the specified values
 *
 * \param u the vector to change
 * \param x the x coordinate
 * \param y the y coordinate
 * \param z the z coordinate
 * \return 0 if a error occurs(u == NULL)<br>
 * 		   1 otherwise
 */
int setVecteur(Vecteur *u, double x, double y, double z);

/**
 * \fn int VecteurNormalize(Vecteur *u)
 * \brief normalizes a vector
 *
 * \param u the vector to normalize
 * \return 0 if a error occurs(u == NULL)<br>
 * 		   1 otherwise
 */
int VecteurNormalize(Vecteur *u);

/**
 * \fn int VecteurSquareNorme(const Vecteur *u, double *res)
 * \brief get the square of the norm of a vector
 *
 * \param u the vector to change
 * \param res the result
 * \return 0 if a error occurs(u == NULL || res == NULL)<br>
 * 		   1 otherwise
 */
int VecteurSquareNorme(const Vecteur *u, double *res);

/**
 * \fn int VecteurProd_scal(const Vecteur *u, const Vecteur *v, double *res)
 * \brief computes the dot product of two vectors
 *
 * \param u the first vector
 * \param v the second vector
 * \param res the computed value (the dot product of u v)
 * \return 0 if a error occurs(u == NULL || v == NULL || res == NULL)<br>
 * 		   1 otherwise
 */
int VecteurProd_scal(const Vecteur *u, const Vecteur *v, double *res);

/**
 * \fn int VecteurProd_vec(const Vecteur *u, const Vecteur *v, Vecteur *newVecteur)
 * \brief computes the vector product of two vectors
 *
 * \param u the first vector
 * \param v the second vector
 * \param newVecteur the computed vector (the vector product of u v)
 * \return 0 if a error occurs(u == NULL || v == NULL || newVecteur == NULL)<br>
 * 		   1 otherwise
 */
int VecteurProd_vec(const Vecteur *u, const Vecteur *v, Vecteur *newVecteur);

/**
 * \fn int Sinus(const Vecteur *u, const Vecteur *v, double *res)
 * \brief compute the sine of an angle(u, v)
 *
 * \param u the first vector
 * \param v the second vector
 * \param res the computed result
 * 
 * \return 0 if an error occurs<br>
 * 		   1 otherwise
 */
int Sinus(const Vecteur *u, const Vecteur *v, double *res);

/**
 * \fn int Cosinus(const Vecteur *u, const Vecteur *v, double *res)
 * \brief compute the cosine of an angle(u, v)
 *
 * \param u the first vector
 * \param v the second vector
 * \param res the computed result
 * \return 0 if an error occurs<br>
 * 		   1 otherwise
 */
int Cosinus(const Vecteur *u, const Vecteur *v, double *res);

/**
 * \fn int VecteurEquals(const Vecteur *u, const Vecteur *v)
 * \brief tells if a vector is equal to another
 *
 * \param u the first vector
 * \param v the second vector
 * 
 * \return -1 if one of the vector is NULL<br>
 * 		   0 if the two vectors was not equals<br>
 * 		   1 if the two vectors was equals
 */
int VecteurEquals(const Vecteur *u, const Vecteur *v);

/**
 * \fn int VecteurIsZero(const Vecteur *u)
 * \brief check if the norme of a vector is zero
 *
 * \param u a vector
 * \return 0 if a error occurs(u == NULL)<br>
 * 		   1 otherwise
 */
int VecteurIsZero(const Vecteur *u);

/**
 * \fn int VecteurAnglesEquals(Vecteur *u1, Vecteur *u2, Vecteur *v1, Vecteur *v2)
 * \brief check if tow angles are equals
 *
 * \param u1 the first vector of the first angle
 * \param u2 the second vector of the first angle
 * \param v1 the first vector of the second angle
 * \param v2 the second vector of the second angle
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int VecteurAnglesEquals(Vecteur *u1, Vecteur *u2, Vecteur *v1, Vecteur *v2);

/**
 * \fn int VecteurHalf(const Vecteur *u, const Vecteur *v, Vecteur *res)
 * \brief calculates the half vector of two vectors
 *
 * \param u the first vector
 * \param v the second vector
 * \param res the result
 * \return 0 if a error occurs(u == NULL || v == NULL || res == NULL)<br>
 * 		   1 otherwise
 */
int VecteurHalf(const Vecteur *u, const Vecteur *v, Vecteur *res);

/**
 * \fn int VecteurReflected(const Vecteur *u, const Vecteur *N, Vecteur *res)
 * \brief sets the vector with the specified values
 *
 * \param u the incident vector 
 * \param N the normal vector 
 * \param res the normalized reflected vector
 * \return 0 if a error occurs(u == NULL || N == NULL || res == NULL)<br>
 * 		   1 otherwise
 */
int VecteurReflected(const Vecteur *u, const Vecteur *N, Vecteur *res);

/**
 * \fn int VecteurConsoleDisplay(const Vecteur *vecteur, int return_line)
 * \brief print a vector in the console
 *
 * \param vecteur the vector to print
 * \param return_line != 0 if we want to add a '\n' after the print
 * \return 0 if a error occurs(u == NULL)<br>
 * 		   1 otherwise
 */
int VecteurConsoleDisplay(const Vecteur *vecteur, int return_line);
#endif
