/**
 * \file Scene.h
 * \brief represents a scene
 * \author Jean-Manuel ERIALC - Hadjer DJERROUMI
 * \version 0.1
 * \date 11 juin 2020
 *
 * Contains a type Scene representing a 3D scene and functions related to it.
 * The scene can be seen via a graphic window or exported as an image.
 * The scene contains shapes and light sources.
 */
#ifndef __SCENE__
#define __SCENE__

#include "Point.h"
#include "Camera.h"
#include "Image.h"
#include "Light.h"
#include "Lst_Object.h"
#include "Option.h"

/**
 * \struct Scene
 * \brief the 3D scene seen by the camera
 *
 * Scene is a type representing a scene and all his components (shapes, lights, camera...)
 * 
 */
typedef struct{
	int level;            			/*!< the level can be 1, 2 or 3 */
	int reflection_level;			/*!< the level of reflection of objects */
	int timer_on_compute_scene;		/*!< if we have to time the scene calculation */
	int pixel_sampling;   			/*!< number of rays per pixel (level 3)*/
	int count_rayon;      			/*!< index (between 0 and 8) of the current ray launched in the given pixel (level 2)*/
	lst_Source sources;		    	/*!< list of all light sources */
	Camera camera;		  			/*!< the camera observing the scene */
	lst_Object lst_object;			/*!< list of all objects */
	Image *output_image;		    /*!< the computed image */
}Scene;

/**
 * \fn void Scene_init(Scene *scene)
 * \brief initialize an empty scene
 *
 * \param scene the scene to initializ
 */
void Scene_init(Scene *scene);


/**
 * \fn int createScene(Scene *scene, const Option *options)
 * \brief create a scene with the specified options
 *
 * \param scene pointer to a scene which will contains the scene
 * \param options options that the scene should respect
 * \return 0 if a error occurs(scene == NULL || options == NULL)<br>
 * 		   1 otherwise
 */
int createScene(Scene *scene, const Option *options);

/**
 * \fn void freeScene(Scene *scene)
 * \brief free all memory allocated by a scene
 *
 * \param scene the scene we want to free
 */
void freeScene(Scene *scene);

/**
 * \fn int computeScene(Scene *scene)
 * \brief calculate the scene and create the resulting image
 *
 * \param scene the scene
 * \return 0 if a error occurs(scene == NULL)<br>
 * 		   1 otherwise
 */
int computeScene(Scene *scene);

/**
 * \fn int outputScene(const Scene *scene, const char *output_file)
 * \brief output the computed image in a file
 *
 * \param scene the scene
 * \param output_file the file where we want to export the image
 * \return 0 if a error occurs(scene == NULL || output_file == NULL or a error when writing in the file)<br>
 * 		   1 otherwise
 */
int outputScene(const Scene *scene, const char *output_file);
#endif
