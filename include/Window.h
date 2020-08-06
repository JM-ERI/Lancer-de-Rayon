/**
 * \file Window.h
 * \brief represents a window to display a scene
 * \author Jean-Manuel ERIALC - Hadjer DJERROUMI
 * \version 0.1
 * \date 11 juin 2020
 *
 * represents a window to display a scene
 *
 */
#ifndef __SYNTHESE_WINDOW__
#define __SYNTHESE_WINDOW__

#include "Scene.h"
#include "Option.h"

/**
 * \fn void openWindow(Scene* scene, Option *options)
 * \brief create a window to display a scene
 *
 * \param scene the scene to display
 * \param options the parameters specified by the user
 * 
 * create a window to display a scene
 */
void openWindow(Scene* scene, Option *options);
#endif
