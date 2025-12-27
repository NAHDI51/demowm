#ifndef __SIZEBOX_H
#define __SIZEBOX_H

#include <stdbool.h>

#include "../def.h"

// GC
#include "../GC/GC.h"
#include "../GC/GC_snapshot.h"

// Shapes
#include "../shapes/shapes.h"

// Geometry
#include "../geometry/axis1d.h"

// Builds on axis and circle.
typedef struct {
    Axis1D axis;      // geometric axis
    Circle knob;      // draggable knob
    int value;        // current value (axis.minValue .. axis.maxValue)
} Slider;

Slider sliderCreate(
    Axis1D axis,
    int knobRadius,
    int initialValue
);



#endif // __SIZEBOX_H