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
        static bool isInside(Vec3 &pointToCheck, Vec3 &triangle){

            float t = 1.1;
            return rayTriangleIntersect(pointToCheck, NULL, NULL, NULL, NULL, t);

        }

    private:
        static bool rayTriangleIntersect(const Vec3 &orig, const Vec3 &dir, const Vec3 &v0, const Vec3 &v1, const Vec3 &v2, float &t);
};

#endif // CHECK_INTERSECTION_H
