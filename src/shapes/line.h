#ifndef __LINE_H
#define __LINE_H

#include <stdbool.h>
#include "point.h"

/*
    Working with lines is very important for multitude of reasons 

    1. For making ui that uses line shapes, such as setting font/
        brush size.
    2. For implementing normal straight line drawing feature. 

    This header file contains GEOMETRIC functions only.
*/

typedef struct {
    Point st, ed;
} Line;

// Constructor
Line createLine(Point start, Point end);

/*
    Special function for creating horizontal and vertical lines.
    Very useful for toolbar and other ui features.
*/
bool isHorizontalLine(Line l);
bool isVerticalLine(Line l);

/*
    @brief: Checks whether point p lies ON or NEAR the line.
    tolerance = allowed distance (pixels)
*/
bool pointNearLine(Point p, Line l, int tolerance);

/*
    @brief: Returns squared distance from point to line segment
*/
int pointLineDistSq(Point p, Line l);


#endif // __LINE_H