/**
 * \file Parser.h
 * \brief contains the parser of user command line and a scene parser
 * \author Jean-Manuel ERIALC - Hadjer DJERROUMI
 * \version 0.1
 * \date 11 juin 2020
 *
 * contains the parser of user command line and a scene parser
 */
#ifndef __PARSER__
#define __PARSER__

#include "Point.h"
#include "Cube.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Cylindre.h"
#include "Camera.h"
#include "Object.h"
#include "Lst_Object.h"
#include "Scene.h"
#include "Option.h"

/**
 * \fn void lray_help()
 * \brief help message of lray program
 *
 */
void lray_help();

/**
 * \fn void lray_usage()
 * \brief usage message of lray program
 *
 */
void lray_usage();

/**
 * \fn int parse_args(int argc, char *argv[], Option *options)
 * \brief parse user arguments from the command line
 *
 * \param argc number of arguments
 * \param argv all arguments
 * \param options all options specified by user in a type
 * \return 0 if the parsing fails<br>
 * 		   1 otherwise
 */
int parse_args(int argc, char *argv[], Option *options);

/**
 * \fn int parse_XML_scene(const char *input_path, Scene *scene)
 * \brief parse a XML scene
 *
 * \param input_path path of the scene file
 * \param scene the scene to build
 * \return 0 if a err occurs ( file not found or parsing error)<br>
 * 		   1 successful parsing
 */
int parse_XML_scene(const char *input_path, Scene *scene);
#endif
