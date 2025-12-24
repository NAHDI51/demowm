/*
    * color.h
    *
    * Created on: 2011-5-19
    * 
    * color.h contains the essential definitions and macros needed 
    * across the files of the project, bundled together. It contains
    * color definitions primarily, structs and other stuffs needed 
    * for the color management of the project.
*/

#ifndef __COLOR_H
#define __COLOR_H 1

/*
    inclusions
*/

#include <X11/Xft/Xft.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/X.h>
#include "def.h"
#include "window.h"

/*
    Visual colors
    !!! WARNING: They are not hexadecimal values, they are
    string representations of hexadecimal values !!!
*/

typedef const char* ColorCode;

/*
    The program will not yet support adding custom colors. 
    The 8 default colors will make up everything for the time
    being. However, I may need some other colors in the future for
    inner functionality, for which reserve colors will be used.
*/
typedef enum {
    COLOR_BLACK = 0,
    COLOR_WHITE,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_RED,
    COLOR_YELLOW,
    COLOR_CYAN,
    COLOR_MAGENTA,
    COLOR_COUNT
} ColorIndex;

/*
    Some additional color to handle other things.
*/

// 50% opacity black color.
extern const unsigned long COLOR_SEMIBLACK; 
// 50% opacity sky-blue
extern const unsigned long COLOR_SEMISKYBLUE;



extern ColorCode colorCodes[COLOR_COUNT];
// They need to be initialized by createColor function before use
extern XftColor* colorResources[COLOR_COUNT];

/*
    @brief: Creates color based on the hex provided.
*/
void createColor(
    XftColor* colorResource, 
    ColorCode colorCode
);
// @brief: Initializes and destroys all the color resources
void constructColorResources();
void destroyColorResources();

/*
    @brief: Color box dimensions
*/
typedef enum {
    COLORBOX_SIZE   = 32,
    COLORBOX_PAD    = 12,
    COLORBOX_BORDER = 4,

    /*
        Mappings used in order to copy the toolbar pixmap to the
        main window.

        These coordinates are calculated using oddly specific ways
        and they will be used in order to make the buttonpress 
        functionality better.
    */

    COLORBOX_X_OFFSET = WIDTH/2 - 
                        ((COLOR_COUNT * COLORBOX_SIZE) + 
                        ((COLOR_COUNT + 1) * COLORBOX_PAD )) / 2,
    
    COLORBOX_Y_OFFSET = HEIGHT - ((COLORBOX_SIZE + (2*COLORBOX_PAD)) * 2)

} ColorBoxProperties;

/*
    @brief: For the menubar color option buttons.
*/
typedef struct {
    int posx, posy;
    int width, height;
    unsigned long code;
} ColorButton;

// Initially support for only few colors defined.
extern ColorButton colorButtons[COLOR_COUNT];

// Constructs with proper xpox ypos and width heigth
void constructColorButtons();
void destroyColorButtons();

/* 
    @brief: Simply creates the toolbar with appropriate dimensions.
    however, nothing is drawn on it yet.
*/
Toolbar createColorboxToolbar(Window win);

/* 
    @brief: now, it draws the colors onto the toolbar. 
    It sets up everything properly.
*/
void drawColorboxToolbar(
    Toolbar toolbar, 
    GC graphicContent,
    Window win
);

#endif // __COLOR_H