/**
 * \file Option.h
 * \brief represents the options specified by the user when launching the program
 * \author Jean-Manuel ERIALC - Hadjer DJERROUMI
 * \version 0.1
 * \date 11 juin 2020
 *
 * represents the options specified by the user when launching the program
 *
 */
#ifndef __USER_ARGS__
#define __USER_ARGS__

/**
 * \struct Option
 * \brief options specified by the user
 *
 * options specified by the user
 * 
 */
typedef struct{
	int level;  		 			/*!< the level of scene wanted by the user */
	int timer_on_compute_scene;		/*!< if the user wants to time the compute scene */
	int pixel_sampling;  			/*!< the number of pixel sampling */
	char *input_path;	 			/*!< the path to the scene to import  */
	char *output_path;	 			/*!< the path of the exported image */
}Option;

/**
 * \fn int want_fast_output_scene(const Option *options)
 * \brief tells if the user want the image of the scene without passing by a graphic window
 *
 * \param options options specified by the user
 * \return 1 if the user want the image of the scene without passing by a graphic window
 *		   0 otherwise
 * 
 * tells if the user want the image of the scene without passing by a graphic window
 */
int want_fast_output_scene(const Option *options);
#endif
