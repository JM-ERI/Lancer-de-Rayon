/**
 * \file Png_Output.h
 * \brief export a Image in png
 * \author Jean-Manuel ERIALC - Hadjer DJERROUMI
 * \version 0.1
 * \date 11 juin 2020
 *
 * export a Image in png
 */
#ifndef _PNG_OUTPUT_
#define _PNG_OUTPUT_

#include "Image.h"

/**
 * \fn int PNG_output_file(const Image *I, const char *output_path)
 * \brief exports a image in a file specified by a path in png format
 *
 * \param I the image to export
 * \param output_path the path of the file
 * \return 0 if a error occurs(I == NULL || output_path == NULL || error when creating the file)<br>
 * 		   1 otherwise
 */
int PNG_output_file(const Image *I, const char *output_path);

#endif

