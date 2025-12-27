#include "axis1d.h"

// Pure geometry shits, I hate them

Axis1D axis1dCreate(
    Line l,
    AxisOrientation ori,
    int minValue,
    int maxValue
) {
    Axis1D axis = {
        .line = l,
        .ori = ori,
        .minValue = minValue,
        .maxValue = maxValue
    };
    return axis;
}

Point axis1dClampPoint(Point p, Axis1D axis) {
    int a0 = AXIS_COORD(axis.line.st, axis.ori);
    int a1 = AXIS_COORD(axis.line.ed, axis.ori);

    int minA = a0 < a1 ? a0 : a1;
    int maxA = a0 > a1 ? a0 : a1;

    int a = AXIS_COORD(p, axis.ori);
    if (a < minA) a = minA;
    if (a > maxA) a = maxA;

    Point res = p;
    SET_AXIS(res, axis.ori, a);
    SET_ORTH(res, axis.ori, 
             ORTH_COORD(axis.line.st, axis.ori));

    return res;
}

double axis1dNormalizedFromPoint(Point p, Axis1D axis) {
    int a0 = AXIS_COORD(axis.line.st, axis.ori);
    int a1 = AXIS_COORD(axis.line.ed, axis.ori);

    if (a0 == a1)
        return 0.0;

    double t = (double)(AXIS_COORD(p, axis.ori) - a0) /
               (double)(a1 - a0);

    if (t < 0.0) t = 0.0;
    if (t > 1.0) t = 1.0;

    return t;
}

int axis1dValueFromPoint(Point p, Axis1D axis) {
    Point c = axis1dClampPoint(p, axis);
    double t = axis1dNormalizedFromPoint(c, axis);

    return axis.minValue +
           (int)(t * (axis.maxValue - axis.minValue));
}

Point axis1dPointFromValue(int value, Axis1D axis) {
    if (value < axis.minValue) value = axis.minValue;
    if (value > axis.maxValue) value = axis.maxValue;

    double t = (double)(value - axis.minValue) /
               (double)(axis.maxValue - axis.minValue);

    int a0 = AXIS_COORD(axis.line.st, axis.ori);
    int a1 = AXIS_COORD(axis.line.ed, axis.ori);

    Point p = axis.line.st;
    SET_AXIS(p, axis.ori, a0 + (int)(t * (a1 - a0)));

    return p;
}