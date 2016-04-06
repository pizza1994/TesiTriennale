#include "check_intersection.h"


    bool CheckIntersection::rayTriangleIntersect(
        const Vec3 &orig, const Vec3 &dir,
        const Vec3 &v0, const Vec3 &v1, const Vec3 &v2,
        float &t)
    {
        // compute plane's normal
        Vec3 v0v1 = v1 - v0;
        Vec3 v0v2 = v2 - v0;
        // no need to normalize
        Vec3 N = v0v1.cross(v0v2); // N

        // Step 1: finding P

        // check if ray and plane are parallel ?
        float NdotRayDirection = N.dot(dir);
        if (fabs(NdotRayDirection) < kEpsilon) // almost 0
            return false; // they are parallel so they don't intersect !

        // compute d parameter using equation 2
        float d = N.dot(v0);

        // compute t (equation 3)
        t = (N.dot(orig) + d) / NdotRayDirection;
        // check if the triangle is in behind the ray
        if (t < 0) return false; // the triangle is behind

        // compute the intersection point using equation 1
        Vec3 P = orig +  dir.operator *(t);

        // Step 2: inside-outside test
        Vec3 C; // vector perpendicular to triangle's plane

        // edge 0
        Vec3 edge0 = v1 - v0;
        Vec3 vp0 = P - v0;
        C = edge0.cross(vp0);
        if (N.dot(C) < 0) return false; // P is on the right side

        // edge 1
        Vec3 edge1 = v2 - v1;
        Vec3 vp1 = P - v1;
        C = edge1.cross(vp1);
        if (N.dot(C) < 0)  return false; // P is on the right side

        // edge 2
        Vec3 edge2 = v0 - v2;
        Vec3 vp2 = P - v2;
        C = edge2.cross(vp2);
        if (N.dot(C) < 0) return false; // P is on the right side;

        return true; // this ray hits the triangle
    }




