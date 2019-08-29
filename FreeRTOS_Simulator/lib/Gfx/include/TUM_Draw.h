/**
 * @file TUM_Draw.h
 * @author Alex Hoffman
 * @date 27 Auguest 2019
 * @brief A SDL2 based library to implement work queue based drawing of graphical
 * elements. Allows for drawing using SDL2 from multiple threads.
 *
 * @mainpage FreeRTOS Simulator Graphical Library
 *
 * @verbatim
   ----------------------------------------------------------------------
    Copyright (C) Alexander Hoffman, 2019
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------
@endverbatim
 */

#ifndef __TUM_DRAW_H__
#define __TUM_DRAW_H__

#include "FreeRTOS.h"
#include "semphr.h"

/**
 * Defines the default font size used by the SDL TTF library
 */
#define DEFAULT_FONT_SIZE  15 

/**
 * Default font to be used by the SDL TTF library
 */
#define DEFAULT_FONT        "IBMPlexSans-Medium.ttf"
/**
 * Location of font TTF files
 */
#define FONTS_LOCATION       "/../resources/fonts/"
#define FONT_LOCATION       FONTS_LOCATION DEFAULT_FONT

/**
 * Sets the width (in pixels) of the screen
 */
#define SCREEN_WIDTH 640
/**
 * Sets the height (in pixels) of the screen
 */
#define SCREEN_HEIGHT 480

/**
 * Defines a generic priority for tasks to use
 */
#define mainGENERIC_PRIORITY	( tskIDLE_PRIORITY )
/**
 * Defines a generic stack size for tasks to use
 */
#define mainGENERIC_STACK_SIZE  ( ( unsigned short ) 2560 )

/**
 * @defgroup rgb_colours RGB hex colours
 *
 * RRGGBB colours used by TUM Draw backend, colour standard is the same as the
 * common html standard
 */
/**
 * @ingroup rgb_colours
 */
#define Red     0xFF0000
/**
 * @ingroup rgb_colours
 */
#define Green   0x00FF00
/**
 * @ingroup rgb_colours
 */
#define Blue    0x0000FF
/**
 * @ingroup rgb_colours
 */
#define Yellow  0xFFFF00
/**
 * @ingroup rgb_colours
 */
#define Aqua    0x00FFFF
/**
 * @ingroup rgb_colours
 */
#define Fuchsia 0xFF00FF
/**
 * @ingroup rgb_colours
 */
#define White   0xFFFFFF
/**
 * @ingroup rgb_colours
 */
#define Black   0x000000

/**
 * @brief Semaphore that signals when the TUM Draw backend is finished drawing
 * its current work packets
 */
extern SemaphoreHandle_t DisplayReady;

/**
 * @typedef coord_t
 * @brief Typedef for @ref struct coord_t
 */

/**
 * @struct coord
 * @brief Holds a pixel co-ordinate
 */
typedef struct coord {
	unsigned short x; /*!< X axis coord */
	unsigned short y; /*!< Y axis coord */
} coord_t;

/**
 * @brief Returns a string error message from the TUM Draw back end
 *
 * @return String holding the most recent TUM Draw error message
 */
char *tumGetErrorMessage(void);

/**
 * @brief Initializes the TUM Draw backend
 *
 * @param path Path to the folder's location where the program's binary is
 * located
 * @return NULL always returns NULL
 */
void vInitDrawing(char *path);

/**
 * @brief Exits the TUM Draw backend
 *
 * @return NULL always returns NULL
 */
void vExitDrawing(void);

/**
 * @brief Executes the queued draw jobs
 *
 * The tumDraw functions are designed to be callable from any thread, as such
 * each function queues a draw job into a queue. Once vDrawUpdateScreen is called,
 * the queued draw jobs are executed by the background SDL thread.
 *
 * @returns NULL always return NULL
 */
void vDrawUpdateScreen(void);

/**
 * @defgroup tum_draw TUM Draw API
 *
 * Functions to draw various shapes and lines on the screen
 */

/**
 * @ingroup tum_draw
 * @brief Sets the screen to a solid colour
 *
 * @param colour RGB colour to fill the screen with
 * @return signed char 0 on success
 */
signed char tumDrawClear(unsigned int colour);

/**
 * @ingroup tum_draw
 * @brief Draws an ellipse on the screen
 *
 * @param x X coordinate of the center of the ellipse
 * @param y Y coordinate of the cente of the ellipse
 * @param rx Horizontal radius in pixels
 * @param ry Vertical radius in pixels
 * @param colour RGB colour of the ellipse
 * @return signed char 0 on success
 */
signed char tumDrawEllipse(signed short x, signed short y, signed short rx,
		signed short ry, unsigned int colour);

/**
 * @ingroup tum_draw
 * @brief Draws an arc on the screen
 *
 * Draws an arc on the screen, the arc is determined from the starting and 
 * ending angles. 
 *
 * @param x X coordinate of the center of the arc 
 * @param y Y coordinate of the cente of the arc
 * @param radius Radius of the arc in pixels 
 * @param start Starting radius of the arc, 0 degrees is down
 * @param end Ending radius of the arc, 0 degrees is down
 * @param colour RGB colour of the arc
 * @return signed char 0 on success
 */
signed char tumDrawArc(signed short x, signed short y, signed short radius,
		signed short start, signed short end, unsigned int colour);

/**
 * @ingroup tum_draw
 * @brief Prints a string to the screen
 *
 * The given string is printed in the given colour at the location x,y. The
 * location is referenced from the top left corner of the strings bounding box.
 *
 * @param str String to print
 * @param x X coordinate of the top left point of the text's bounding box 
 * @param y Y coordinate of the top left point of the text's bounding box 
 * @param colour RGB colour of the text
 * @return signed char 0 on success
 */
signed char tumDrawText(char *str, signed short x, signed short y,
		unsigned int colour);

/**
 * @ingroup tum_draw
 * @brief Finds the width and height of a strings bounding box
 *
 * @param String who's bounding box size is required
 * @param width Variable where the width shall be stored
 * @param height Variable where the height shall be stored
 * @return signed char 0 on success
 */
void tumGetTextSize(char *str, unsigned int *width, unsigned int *height);

/**
 * @ingroup tum_draw
 * @brief Draws a filled box on the screen
 *
 * @param x X coordinate of the top left point of the box 
 * @param y Y coordinate of the top left point of the box 
 * @param w Width of the box
 * @param h Height of the box
 * @param colour RGB colour of the box
 * @return signed char 0 on success
 */
signed char tumDrawBox(signed short x, signed short y, signed short w,
		signed short h, unsigned int colour);

/**
 * @ingroup tum_draw
 * @brief Draws an unfilled box on the screen
 *
 * @param x X coordinate of the top left point of the box 
 * @param y Y coordinate of the top left point of the box 
 * @param w Width of the box
 * @param h Height of the box
 * @param colour RGB colour of the filled box
 * @return signed char 0 on success
 */
signed char tumDrawFilledBox(signed short x, signed short y, signed short w,
		signed short h, unsigned int colour);

/**
 * @ingroup tum_draw
 * @brief
 *
 * @param
 * @param colour RGB colour of the ellipse
 * @return signed char 0 on success
 */
signed char tumDrawCircle(signed short x, signed short y, signed short radius,
		unsigned int colour);

/**
 * @ingroup tum_draw
 * @brief
 *
 * @param
 * @param colour RGB colour of the ellipse
 * @return signed char 0 on success
 */
signed char tumDrawLine(signed short x1, signed short y1, signed short x2,
		signed short y2, unsigned char thickness, unsigned int colour);

/**
 * @ingroup tum_draw
 * @brief
 *
 * @param
 * @param colour RGB colour of the ellipse
 * @return signed char 0 on success
 */
signed char tumDrawPoly(coord_t *points, int n, unsigned int colour);

/**
 * @ingroup tum_draw
 * @brief
 *
 * @param
 * @param colour RGB colour of the ellipse
 * @return signed char 0 on success
 */
signed char tumDrawTriangle(coord_t *points, unsigned int colour);

/**
 * @ingroup tum_draw
 * @brief
 *
 * @param
 * @param colour RGB colour of the ellipse
 * @return signed char 0 on success
 */
signed char tumDrawImage(char *filename, signed short x, signed short y);

/**
 * @ingroup tum_draw
 * @brief
 *
 * @param
 * @param colour RGB colour of the ellipse
 * @return signed char 0 on success
 */
signed char tumDrawArrow(unsigned short x1, unsigned short y1,
		unsigned short x2, unsigned short y2, unsigned short head_length,
		unsigned char thickness, unsigned int colour);

#endif
