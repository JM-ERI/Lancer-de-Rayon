/**
 * \file Rectangle.h
 * \brief represents an object (shape)
 * \author Jean-Manuel ERIALC - Hadjer DJERROUMI
 * \version 0.1
 * \date 11 juin 2020
 *
 * contains the type representing an object (shape) in a 3D space and functions related to it
 */
#ifndef __OBJECT__
#define __OBJECT__

#include "Hmat.h"
#include "Cube.h"
#include "Sphere.h"
#include "Cylindre.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Color.h"

#define TYPE_OBJECT_SIZE 6

/**
 * \enum TYPE_OBJECT
 * \brief enumerate all types of objects
 *
 * Object can be Cube, Cylinder, Rectangle, Sphere or Triangle
 * 
 */
typedef enum TYPE_OBJECT{UNKNOW, CUBE, CYLINDRE, RECTANGLE, SPHERE, TRIANGLE} TYPE_OBJECT;

/**
 * \struct Object
 * \brief an object
 *
 * Object is a type representing a shape
 * 
 */
typedef struct{
    TYPE_OBJECT canonique;		         /*!< reference to the canonical object */
    int shininess;                       /*!< value between 2 and 256 */
    Color color;                         /*!< RGB color */
    double specular_reflection_coeff[3]; /*!< RGB coefficient between 0 and 1 */
    double diffuse_reflection_coeff[3];  /*!< RGB coefficient between 0 and 1 */
    int (*rayon_inter)(const Point *A, const Vecteur *u, Point *I, Vecteur *N);  /*!< 1 if the object is seen from point A, 0 otherwise*/
    Hmat Md, Mi, Mn;			        /*!< direct, inverse and normal homogeneous matrices */
}Object;

/**
 * \fn TYPE_OBJECT string_to_TYPE_OBJECT(char *object_name)
 * \brief transforms the name of a object e.g Sphere to his TYPE_OBJECT enum
 *
 * \param object_name the object name
 * \return a TYPE_OBJECT representing the object<br>
 *           UNKNOW if an error occurs
 */
TYPE_OBJECT string_to_TYPE_OBJECT(char *object_name);

/**
 * \fn int translate(Object *obj, const Vecteur *v)
 * \brief translates an object with the vector v
 *
 * \param obj the object to translate
 * \param v the translation vector
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int translate(Object *obj, const Vecteur *v);

/**
 * \fn int rescale(Object *obj, double a, double b, double c)
 * \brief recale an object with specified parameters
 *
 * \param obj the object to translate
 * \param a the ox parameter
 * \param b the oy parameter
 * \param c the oz parameter
 * \return 0 if a error occurs(obj == NULL)<br>
 * 		   1 otherwise
 */
int rescale(Object *obj, double a, double b, double c);

/**
 * \fn int rotate_x(Object *obj, const Vecteur *u, const Vecteur *v)
 * \brief rotate an object with angle (u, v) around the ox axis
 *
 * \param obj the object to rotate
 * \param u the first vector of the angle
 * \param v the second vector of the angle
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int rotate_x(Object *obj, const Vecteur *u, const Vecteur *v);

/**
 * \fn int rotate_y(Object *obj, const Vecteur *u, const Vecteur *v)
 * \brief rotate an object with angle (u, v) around the oy axis
 *
 * \param obj the object to rotate
 * \param u the first vector of the angle
 * \param v the second vector of the angle
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int rotate_y(Object *obj, const Vecteur *u, const Vecteur *v);

/**
 * \fn int rotate_z(Object *obj, const Vecteur *u, const Vecteur *v)
 * \brief rotate an object with angle (u, v) around the oz axis
 *
 * \param obj the object to rotate
 * \param u the first vector of the angle
 * \param v the second vector of the angle
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int rotate_z(Object *obj, const Vecteur *u, const Vecteur *v);

/**
 * \fn int ObjectFromCube(Object *object, const Cube *cube)
 * \brief create an Object from a given Cube
 *
 * \param object the object to create
 * \param cube the given cube
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int ObjectFromCube(Object *object, const Cube *cube);

/**
 * \fn int ObjectFromCylindre(Object *object, const Cylindre *cylindre)
 * \brief create an Object from a given Cylinder
 *
 * \param object the object to create
 * \param cylindre the given cylinder
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int ObjectFromCylindre(Object *object, const Cylindre *cylindre);

/**
 * \fn int ObjectFromRectangle(Object *object, const Rectangle *rectangle)
 * \brief create an Object from a given Rectangle
 *
 * \param object the object to create
 * \param rectangle the given rectangle
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int ObjectFromRectangle(Object *object, const Rectangle *rectangle);

/**
 * \fn int ObjectFromSphere(Object *object, const Sphere *sphere)
 * \brief create an Object from a given Sphere
 *
 * \param object the object to create
 * \param sphere the given sphere
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int ObjectFromSphere(Object *object, const Sphere *sphere);

/**
 * \fn int ObjectFromTriangle(Object *object, const Triangle *triangle)
 * \brief create an Object from a given Triangle
 *
 * \param object the object to create
 * \param triangle the given triangle
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int ObjectFromTriangle(Object *object, const Triangle *triangle);
void ObjectCopy(Object *dest, const Object *src);

#endif
