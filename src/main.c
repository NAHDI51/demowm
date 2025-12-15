#include <X11/Xlib.h>
#include <stdio.h>
#include <err.h>

// estallish connection with display serer 
static Display* dpy;

// Number of screen
static int screen_number;

// Root from which the windows start
static Window root;

/*
MACROS
*/

#define POSX    500
#define POSY    500
#define WIDTH   500
#define HEIGHT  500
#define BORDER  15

int main(int argc, char** argv) {

    Window window1;
    XEvent ev;

    // Establish connection with X11
    dpy = XOpenDisplay(NULL);

    // Cherck if opened properly 
    if(dpy == NULL) {
        errx(1, "Can't open display.\n");
    }

    // Get default screen and root widow
    screen_number = DefaultScreen(dpy);
    root = RootWindow(dpy, screen_number); 

    /*
    Last two variables: Border and Background
    */
    window1 = XCreateSimpleWindow(dpy, root, POSX, POSY, 
              WIDTH, HEIGHT, BORDER, 
              BlackPixel(dpy, screen_number),
              WhitePixel(dpy, screen_number)
            );
    
    // Map our widow to display Server
    XMapWindow(dpy, window1);

    // XEventGroup, writes o XEvent as long as there are next event
    while(XNextEvent(dpy, &ev) == 0) {
         
    }
    /*
    Free the resources
    */
    // Unmap widow
    XUnmapWindow(dpy, window1);

    // Destroy Window 
    XDestroyWindow(dpy, window1);

    // XClose the connection with X11.
    XCloseDisplay(dpy);
}