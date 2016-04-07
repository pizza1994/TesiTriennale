#ifndef CHECK_INTERSECTION_H
#define CHECK_INTERSECTION_H

#include <math.h>
#include "lib/common/point.h"

#define kEpsilon 0.000001

class CheckIntersection
{
    public:
        CheckIntersection();

        //DA COMPLETARE E DA TESTARE
        static bool isInside(Pointd &pointToCheck, std::vector<Pointd> &triangle);

    private:
        static bool rayTriangleIntersect(const Pointd &orig, const Pointd &dir, const Pointd &v0, const Pointd &v1, const Pointd &v2, float &t);
};

#endif // CHECK_INTERSECTION_H
