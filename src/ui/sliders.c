#include "sliders.h"

bool clickedOnSizebox(Point mouse, Sizebox *box) {
    return pointInsideCircle(mouse, box->knob);
}