#include <X11/X.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/Xatom.h>
#include <X11/Xft/Xft.h>
#include <stdbool.h>

/*
    Window properties
*/

#define POSX    500
#define POSY    500
#define WIDTH   500
#define HEIGHT  500
#define BORDER  10
#define LINE    5

/*
    Visual colors
    !!! WARNING: They are not hexadecimal values, they are
    string representations of hexadecimal values !!!
*/

#define BLUECOLOR   "#0000FF"
#define REDCOLOR    "#FF0000"
#define GREENCOLOR  "#00FF00"
#define YELLOWCOLOR "#FFFF00"
#define CYANCOLOR   "#00FFFF"
#define MAGENTACOLOR "#FF00FF"
#define BLACKCOLOR  "#000000"
#define WHITECOLOR  "#FFFFFF"

/*
    Global display attributes
*/

static Display* disp;
static int screenNum;
static Window rootWindow;
static Visual* mainVisual;

static Window createWindow(
    int x, int y, int w, int h, int b,
    XftColor *bgColor,
    XftColor *borderColor
    ) {

    unsigned long long eventMask = Button1MotionMask | ButtonPressMask |
                                   ButtonReleaseMask | KeyPressMask;
    XSetWindowAttributes xattr = {
        .background_pixel = bgColor->pixel,
        // .border_pixel     = borderColor->pixel,
        .border_pixel     = WhitePixel(disp, screenNum),
        .event_mask       = eventMask
    };

    unsigned long long createWindowMask = CWBackPixel | CWBorderPixel | CWEventMask;

    Window win = XCreateWindow(disp, rootWindow, x, y, w, h, b,
                 DefaultDepth(disp, screenNum), InputOutput,
                 DefaultVisual(disp, screenNum), 
                 createWindowMask,
                 &xattr
                );
            
    // Colormap colormap = DefaultColormap(disp, screenNum);
    
    return win;
}

static GC createGraphicContent(
    unsigned int lineWidth, 
    Window win,
    XftColor* fgColor, 
    XftColor* bgColor
    ) {

    // So far, win doesn't do anything
    XGCValues xgcValues = {

        // Drawing attributes
        .line_style = LineSolid,
        .line_width = lineWidth,
        .cap_style  = CapRound,
        .join_style = JoinMiter,
        .fill_style = FillSolid,

        // Colors
        .foreground = fgColor->pixel,
        .background = bgColor->pixel
    };

    unsigned long long valueMask = GCForeground | GCBackground | GCFillStyle | 
                    GCLineStyle  | GCLineWidth  | GCCapStyle   | GCJoinStyle;

    GC graphicContent = XCreateGC(disp, rootWindow, valueMask, &xgcValues);

    return graphicContent;
}

/*
    @brief: Creates color based on colorName.
*/

static void createColor(XftColor* color, char* colorName) {

    int okay = XftColorAllocName(
        disp,
        mainVisual,
        DefaultColormap(disp, screenNum),
        colorName,
        color
    );

    if(!okay) {
        errx(1, "Failed to allocate color: %s\n", colorName);
        exit(1);
    }

    // Not sure why this is needed, but some examples have it.
    // Need to check later.

    color->pixel |= 0xff << 24;

    printf("Successfully created color: %s\n", colorName);

    return;
}

// Just using raw for now.

XftColor* createColorBlue() {
    XftColor* blue = (XftColor*) malloc(sizeof(XftColor));
    createColor(blue, BLUECOLOR);
    return blue;
}

XftColor* createColorRed() {
    XftColor* red = (XftColor*) malloc(sizeof(XftColor));
    createColor(red, REDCOLOR);
    return red;
}

XftColor* createColorBlack() {
    XftColor* black = (XftColor*) malloc(sizeof(XftColor));
    createColor(black, BLACKCOLOR);
    return black;
}

XftColor* createColorWhite() {
    XftColor* white = (XftColor*) malloc(sizeof(XftColor));
    createColor(white, WHITECOLOR);
    return white;
}

/*
    @brief: Sets the sizes within which the 
    window can be resized. 

    @details: 
        minWidth: Minimum width of the window
        minHeight: Minimum height of the window
        maxWidth: Maximum width of the window
        maxHeight: Maximum height of the window
    
        @ If maxWidth or maxHeight is set to 0,
        then there is no maximum limit on resizing

        @ If maxWidth < minWidth or maxHeight < minHeight,
        then the function will not set any maximum limits.

        @ If maxWidth == minWidth and maxHeight == minHeight,
        then the window will not be resizable.
*/

static void setWindowSizeHints(
    Window win, 
    int minWidth, 
    int minHeight,
    int maxWidth,
    int maxHeight) 
{
    XSizeHints sizeHints = {
        .flags = PMinSize | PMaxSize,
        .min_width  = minWidth,
        .min_height = minHeight,
        .max_width  = maxWidth,
        .max_height = maxHeight
    };
    XSetSizeHints(disp, win, &sizeHints, XA_WM_NORMAL_HINTS);
}

/*
    @brief: Sets a fixed size for the window
*/
static void setFixedWindowSize(Window win, int width, int height) {
    setWindowSizeHints(win, width, height, width, height);
}

/*
    @brief: Takes input of x,y,width,height, border, and 
    uses them to create a window
*/
Window takeWindowInput() {
    /*
    Last two variables: Border and Background
    */
    printf("Enter the dimensions (x,y,width,height,border): ");
    int x, y;
    unsigned int width, height, border;
    scanf("%d %d %u %u %u", &x, &y, &width, &height, &border);

    char windowName[128];
    printf("Enter the name of the Window: ");
    scanf("%[^\n]s", windowName);

    Window win = createWindow(x, y, width, height, border,
                              createColorWhite(),
                              createColorWhite()
    );
    XStoreName(disp, win, windowName);
    XMapWindow(disp, win);

    // For the time being, setting fixed window size.
    setFixedWindowSize(win, width, height);



    printf("Window created at (%d,%d) with dimensions %ux%u and border %u\n",
           x, y, width, height, border
    );

    return win;
}

/*
    @brief: Creates a default window with predefined
    attributes.
*/
Window openDefaultWindow() {
    Window mainWindow = createWindow(POSX, POSY, WIDTH, HEIGHT, BORDER,
                                     createColorWhite(),
                                     createColorWhite()        
    );
    XStoreName(disp, mainWindow, "Default Paint Window");
    XMapWindow(disp, mainWindow);

    // For the time being, setting fixed window size.
    setFixedWindowSize(mainWindow, WIDTH, HEIGHT);
    return mainWindow;
}
//
/*
    @brief Takes input of lineWidth from the user
*/
GC takeGraphicContentInput(Window win) {
    unsigned int lineWidth;
    printf("Enter the width of the line: ");
    scanf("%u", &lineWidth);

    // Default color: Red foreground, Blue background
    GC graphicContent = createGraphicContent(lineWidth, win, createColorRed(), createColorBlue() );

    printf("Graphic Content created with line width: %u\n", lineWidth);

    return graphicContent;
}

/*
    @brief: Creates a default graphic content
    with predefined attributes.
*/
GC openDefaultGraphicContent(Window win) {
    return createGraphicContent(LINE, win, createColorRed(), createColorBlue() );
}

/*
    @brief Sets the necessary globat attributes with
    proper value.
*/

void constructDisplay() {

    if(!(disp = XOpenDisplay(NULL))) {
        errx(1, "Can't open display!\n");
        exit(1);
    }
    screenNum = DefaultScreen(disp);
    mainVisual = DefaultVisual(disp, screenNum);
    rootWindow = RootWindow(disp, screenNum);

    return;
}

/*
    @brief: Frees the resources
*/
void destroyDisplay(Window* win, GC* gc) {
    XUnmapWindow(disp, *win);
    XDestroyWindow(disp, *win);
    XFreeGC(disp, *gc);

    //Close connection with X11
    XCloseDisplay(disp);
}


void runGraphicContent(GC graphicContent) {
    XEvent event;
    int prevX = 0, prevY = 0;
    bool pointInit = false;

    printf("reached runGraphicContent\n");

    while(!(XNextEvent(disp, &event))) {
        // printf("Reached inside event loop\n");

        switch(event.type) {

            case ButtonPress:
                if(event.xbutton.x == Button1) {
                    XDrawPoint(disp, event.xbutton.window, graphicContent,
                               event.xbutton.x, event.xbutton.y
                    );
                } 
                break;
            
            case MotionNotify:
                if(pointInit) {
                    XDrawLine(disp, event.xbutton.window, graphicContent,
                              prevX          , prevY,           /* From */
                              event.xbutton.x, event.xbutton.y  /* To */
                    );
                } else {
                    XDrawPoint(disp, event.xbutton.window, graphicContent,
                               event.xbutton.x, event.xbutton.y
                    );
                    pointInit = true;
                } 

                prevX = event.xbutton.x;
                prevY = event.xbutton.y;

                break;
            
            case ButtonRelease:
                pointInit = false;
                break;
            
            case KeyPress:
                if(XkbKeycodeToKeysym(disp, event.xkey.keycode, 0, 0) == XK_q) {
                    return; 
                }
                break;

        }

    }

}

int main() {

    constructDisplay();
    // Window mainWindow = takeWindowInput();
    Window mainWindow = openDefaultWindow();
    
    // GC graphicContent = takeGraphicContentInput(mainWindow);
    GC graphicContent = openDefaultGraphicContent(mainWindow);
    runGraphicContent(graphicContent);
    destroyDisplay(&mainWindow, &graphicContent);

    return 0;
}