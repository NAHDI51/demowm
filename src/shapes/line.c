#include "line.h"

Line createLine(Point st, Point ed) {
    return (Line){ st, ed };
}

bool isHorizontalLine(Line l) {
    return l.st.posY == l.ed.posY;
}

bool isVerticalLine(Line l) {
    return l.st.posX == l.ed.posX;
}

/*
    Bunch of computational geometry
*/
int pointLineDistSq(Point p, Line l) {
    Point v = pointSubtract(l.ed, l.st);
    Point w = pointSubtract(p, l.st);

    int c1 = dotProduct(w, v);
    if (c1 <= 0) return pointDistSq(p, l.st);

    int c2 = dot(v, v);
    if (c2 <= c1) return pointDistSq(p, l.ed);

    double t = (double)c1 / c2;

    Point projection = {
        l.st.posX + (int)(t * v.posX),
        l.st.posY + (int)(t * v.posY)
    };

    return pointDistSq(p, projection);
}

bool pointNearLine(Point p, Line l, int tolerance) {
    return pointLineDistSq(p, l) <= tolerance * tolerance;
}