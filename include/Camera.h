/**
 * \file Camera.h
 * \brief represents a camera filming the scene
 * \author Jean-Manuel ERIALC - Hadjer DJERROUMI
 * \version 0.1
 * \date 11 juin 2020
 *
 * represents a camera filming the scene
 *
 */
#ifndef __CAMERA__
#define __CAMERA__

#include "Point.h"
#include "Hmat.h"

/**
 * \struct Camera
 * \brief represents a camera observing the scene
 *
 * represents a camera observing the scene
 *
 */
typedef struct{
    Point eye;		   /*!< the eye of the camera observing the scene */
    int resolution[2]; /*!< width x height */
    double screen[2];  /*!< width x height */
    Hmat M;
}Camera;

/**
 * \fn int setCamera(Camera *camera, const Point *eye, int resolution[2], int screen[2])
 * \brief sets the camera with the specified values
 *
 * \param camera the camera to change
 * \param eye the new point of vue of the camera
 * \param resolution the new resolution
 * \param screen the dimensions of the new screen
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise
 */
int setCamera(Camera *camera, const Point *eye, int resolution[2], int screen[2]);

/**
 * \fn int CameraConsoleDisplay(const Camera *camera, int return_line)
 * \brief print a camera in the console
 *
 * \param camera the camera to print
 * \param return_line != 0 if we want to add a '\n' after the print
 * \return 0 if a error occurs(camera == NULL)<br>
 * 		   1 otherwise
 */
int CameraConsoleDisplay(const Camera *camera, int return_line);

#endif
