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

#include "def.h"
#include "GC.h"
#include "window.h"
#include "color.h"

Pixmap createDefaultPixmap(Window win) {
    Pixmap pixmap = XCreatePixmap(
        disp,
        win,
        WIDTH,
        HEIGHT,
        DefaultDepth(disp, screenNum)
    );

    if(pixmap == None) {
        errx(1, "Failed to create pixmap");
        exit(1); 
    }
    return pixmap;
}

void run(GC graphicContent) {
    XEvent event;
    while(!XNextEvent(disp, &event)) {
        // Event loop can be implemented here
    }
}


int main() {
    constructDisplay();
    // Window mainWindow = takeWindowInput();
    Window mainWindow = openDefaultWindow();
    
    // GC graphicContent = takeGraphicContentInput(mainWindow);
    GC graphicContent = openDefaultGraphicContent(mainWindow);
    run(graphicContent);
    destroyDisplay(&mainWindow, &graphicContent);

    return 0;
}