/**
 * \file Image.h
 * \brief represents RGB image
 * \author Jean-Manuel ERIALC - Hadjer DJERROUMI
 * \version 0.1
 * \date 11 juin 2020
 *
 * contains RGB type image and fonctions related to it
 *
 */
#ifndef __IMAGE__
#define __IMAGE__

#include <stdio.h>
#include "Color.h"

/**
 * \struct Image
 * \brief represents an Image
 *
 * Image is a type representing RGB Image
 * 
 */
typedef struct Image{
	int w;			/*!< the width of the image */
	int h;			/*!< the height of the image */
	Color* data;	/*!< data of the image (pixel colors) */
}Image;

/**
 * \fn Image* newImage(int w, int h)
 * \brief create a image of size w x h
 *
 * \param w the width of the image to create
 * \param h the height of the image to create
 * \return the address of the created image<br>
 * 		   NULL if a image occurs(w <= 0 || h <= 0 or memory allocation error)
 */
Image* newImage(int w, int h);

/**
 * \fn void freeImage(Image *image)
 * \brief free all the memory alocated by the image
 *
 * \param image the image to free
 */
void freeImage(Image *image);

/**
 * \fn int writeImagePPM(Image* I, const char* export_file_name)
 * \brief export image to PPM
 *
 * \param I the image to export
 * \param export_file_name the path where the image should be exported
 * \return 1 if the image was successfully exported<br>
 * 		   0 if a error occurs (I == NULL || export_file_name == NULL or the open of export_file_name fails)
 */
int writeImagePPM(Image* I, const char* export_file_name);

/**
 * \fn int writeImagePNG(Image* I, const char* export_file_name);
 * \brief export image to PNG
 *
 * \param I the image to export
 * \param export_file_name the path where the image should be exported
 * \return 1 if the image was successfully exported<br>
 * 		   0 if a error occurs (I == NULL || export_file_name == NULL or the open of export_file_name fails)
 */
int writeImagePNG(Image* I, const char* export_file_name);


/**
 * \fn Image* cloneImage(Image*)
 * \brief clone a image (this function make memory allocation)
 *
 * \param src the image to clone
 * \return the address of the cloned image<br>
 * 		   NULL if a memory allocation occurs or src == NULL
 */
Image* cloneImage(Image* src);


/**
 * \fn int cpyImage(Image *dest, Image *src)
 * \brief copy an image to another
 *
 * \param dest the destination image
 * \param src the source image
 * \return 1 if the image was successfully copied<br>
 * 		   0 if a error occurs
 */
int cpyImage(Image *dest, Image *src);


/**
 * \fn int ImageSetPixel(Image *image, const Color *p, int row, int column)
 * \brief sets the color of the given pixel
 *
 * \param image the image to set
 * \param p the new color of the pixel
 * \param row the row of the pixel
 * \param column the colomn of the pixel
 * \return 0 if a error occurs<br>
 *         1 otherwise
 * 		  
 */
int ImageSetPixel(Image *image, const Color *p, int row, int column);


/**
 * \fn int ImageGetPixel(const Image* img, Color *res, int row, int column)
 * \brief gets the color of a given pixel
 *
 * \param img the image
 * \param res the color of the pixel
 * \param row the row of the pixel
 * \param column the colomn of the pixel
 * \return 0 if a error occurs<br>
 *         1 otherwise
 */
int ImageGetPixel(const Image* img, Color *res, int row, int column);

/**
 * \fn void progressiveRay(int render, Image *dest, Image *comming, Image *old)
 * \brief make a progressiveRay on two image
 *
 * \param render the render of the progressiveRay (between 1 and 9)
 * \param dest the computed image
 * \param comming the next image computed
 * \param old the old image computed
 */
void progressiveRay(int render, Image *dest, Image *comming, Image *old);
#endif
