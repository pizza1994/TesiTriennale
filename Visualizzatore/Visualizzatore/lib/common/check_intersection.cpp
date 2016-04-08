#include "check_intersection.h"


    bool CheckIntersection::rayTriangleIntersect(
        const Pointd &orig, const Pointd &dir,
        const Pointd &v0, const Pointd &v1, const Pointd &v2)
    {
        //Calculate Triangle Normal
        Pointd v0v1 = v1 - v0;
        Pointd v0v2 = v2 - v0;
        Pointd N = v0v1.cross(v0v2); // Normal
        float t;

        // Step 1: finding the interseption point

        float NdotRayDirection = N.dot(dir);
        if (fabs(NdotRayDirection) < kEpsilon)
            return false; //if they are parallels there is not intersection

        // compute d parameter using equation 2
        float d = N.dot(v0);

        // compute t (equation 3)
        t = (N.dot(orig) + d) / NdotRayDirection;
        // check if the triangle is in behind the ray
        if (t < 0) return false; // the triangle is behind

        // compute the intersection point using equation 1
        Pointd P = orig +  dir.operator *(t);

        // Step 2: inside-outside test
        Pointd C; // vector perpendicular to triangle's plane

        // edge 0
        Pointd edge0 = v1 - v0;
        Pointd vp0 = P - v0;
        C = edge0.cross(vp0);
        if (N.dot(C) < 0) return false; // P is on the right side

        // edge 1
        Pointd edge1 = v2 - v1;
        Pointd vp1 = P - v1;
        C = edge1.cross(vp1);
        if (N.dot(C) < 0)  return false; // P is on the right side

        // edge 2
        Pointd edge2 = v0 - v2;
        Pointd vp2 = P - v2;
        C = edge2.cross(vp2);
        if (N.dot(C) < 0) return false; // P is on the right side;

        return true; // this ray hits the triangle
    }




