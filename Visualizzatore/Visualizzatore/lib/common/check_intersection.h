#ifndef CHECK_INTERSECTION_H
#define CHECK_INTERSECTION_H

#include <math.h>
#include "lib/common/point.h"
#include "GUI/objects/grid_cell.h"

#define kEpsilon 0.000001

class CheckIntersection
{
    public:
        CheckIntersection();
        static bool rayTriangleIntersect(const Pointd &orig, const Pointd &dir, const Pointd &v0, const Pointd &v1, const Pointd &v2);
};

#endif // CHECK_INTERSECTION_H
