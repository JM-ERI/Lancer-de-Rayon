/**
 * \file Color.h
 * \brief contains RGB color type and all functions related to it
 * \author Jean-Manuel ERIALC - Hadjer DJERROUMI
 * \version 0.1
 * \date 11 juin 2020
 *
 * contains RGB color type and all functions related to it
 *
 */
#ifndef __COULEUR__
#define __COULEUR__

#include <stdint.h>

/**
 * \struct Color
 * \brief represents RGB color
 * 
 */
typedef struct{
	unsigned char r; /*!< red value */
	unsigned char g; /*!< green value */
	unsigned char b; /*!< blue value */
} Color;

/**
 * \fn int moyennageColor(int n, const Color *color_comming, const Color *color_old, Color *res)
 * \brief computes a weighted average of two colors
 *
 * \param n the render
 * \param color_comming the first color
 * \param color_old the second color
 * \param res the result
 * \return 0 if a error occurs(one parameter is NULL)<br>
 * 		   1 otherwise 
 */
int moyennageColor(int n, const Color *color_comming, const Color *color_old, Color *res);

/**
 * \fn int setColor(Color *color, unsigned char r, unsigned char g, unsigned char b)
 * \brief sets a color with the specified valuers
 *
 * \param color the color to set
 * \param r the red value
 * \param g the green value
 * \param b the blue value
 * \return 0 if a error occurs(color == NULL)<br>
 * 		   1 otherwise 
 */
int setColor(Color *color, unsigned char r, unsigned char g, unsigned char b);

/**
 * \fn int ColorCopy(Color *dest, const Color *src)
 * \brief copy a color to another
 *
 * \param dest the color to change
 * \param src the copy to copy
 * \return 0 if a error occurs(dest == NULL || src == NULL)<br>
 * 		   1 otherwise 
 */
int ColorCopy(Color *dest, const Color *src);

/**
 * \fn int Color_to_uint32_t(const Color *color, uint32_t *value)
 * \brief transform a color to a uint32_t value
 *
 * \param color the color to transform
 * \param value the result
 * \return 0 if a error occurs(dest == NULL || src == NULL)<br>
 * 		   1 otherwise 
 */
int Color_to_uint32_t(const Color *color, uint32_t *value);

/**
 * \fn int Color_from_double(Color *color, double r, double g, double b)
 * \brief computes RGB color from real values
 *
 * \param color the result color
 * \param r the red value
 * \param g the green value
 * \param b the blue value
 * \return 0 if a error occurs(color == NULL)<br>
 * 		   1 otherwise 
 */
int Color_from_double(Color *color, double r, double g, double b);

/**
 * \fn int ColorConsoleDisplay(const Color *c, int return_line)
 * \brief print a color and all his fiels in console
 *
 * \param c the color to print
 * \param return_line if we want to add a '\n' after the print
 */
int ColorConsoleDisplay(const Color *c, int return_line);
#endif
