#ifndef __AXIS1D_H
#define __AXIS1D_H

#include <stdbool.h>

#include "../shapes/line.h"
#include "../shapes/point.h"

/*
    Purpose: creates a horizontal/vertical line segment using 
    shapes/line.h. It uses computational geometry to calculate
    things, and especially useful for further implementing ui 
    and WM objects.

    Axis1D represents a 1D coordinate system embedded in 2D space.
    It may be horizontal or vertical.
*/

typedef enum {
    AXIS_HORIZONTAL,
    AXIS_VERTICAL
} AxisOrientation;

typedef struct {
    Line line;                
    AxisOrientation ori;      
    int minValue, maxValue;
} Axis1D;

// constructor
Axis1D axis1dCreate(
    Line l, 
    AxisOrientation ori, 
    int minValue, int maxValue
);

/*
    Projects a point onto the axis and clamps it 
    to the axis extents.
*/
Point axis1dClampPoint(
    Point p, 
    Axis1D axis
);

/*
    Returns normalized position along axis.
    within [0.0, 1.0]: Kinda works with ratio.
*/
double axis1dNormalizedFromPoint(
    Point p, 
    Axis1D axis
);

/*
    Conversion: Described in terms of scale and value.
    point -> value
    value -> point
*/
int axis1dValueFromPoint(Point p, Axis1D axis);
Point axis1dPointFromValue(int value, Axis1D axis);

/*
    SOME helper macros in order to handle horizontality 
    and verticality better. Pure geometric stuffs
*/
#define AXIS_COORD(p, ori) \
    ((ori) == AXIS_HORIZONTAL ? (p).posX : (p).posY)

#define ORTH_COORD(p, ori) \
    ((ori) == AXIS_HORIZONTAL ? (p).posY : (p).posX)

#define SET_AXIS(p, ori, v)           \
    do {                              \
        if ((ori) == AXIS_HORIZONTAL) \
            (p).posX = (v);           \
        else (p).posY = (v);          \
    } while (0)     

#define SET_ORTH(p, ori, v)           \
    do {                              \
        if ((ori) == AXIS_HORIZONTAL) \
            (p).posY = (v);           \
        else (p).posX = (v);          \
    } while (0)


#endif //__AXIS1D_H