#ifndef COMMON_H
#define COMMON_H

#include <set>
#include <vector>
#include "lib/common/point.h"

#define EPSILON 0.0000001

#define ONE_ON_SQRT2 0.7071067811865475f
#define ONE_ON_SQRT3 0.5773502691896258f

extern int WINDOW_MANAGER_ID;
extern int MESH_STACK_MANAGER_ID;
extern int DCEL_MANAGER_ID;
extern int GRID_MANAGER_ID;
extern int TRIMESH_MANAGER_ID;
extern int OCTREE_MANAGER_ID;

template <typename T>
int binarySearch(const T &n, const std::vector<T> &v){
    int first = 0, last =v.size()-1, mid;
    while (first <= last){
        mid = (first + last) / 2;
        if (v[mid] < n) first = mid + 1;
        else if (v[mid] == n) return mid;
        else last = mid - 1;
    }
    return -1;
}

template <typename T>
int searchInsertIndex(const T &n, const std::vector<T> &v){
    int first = 0, last =v.size()-1, mid;
    while (first <= last){
        mid = (first + last) / 2;
        if (v[mid] < n) first = mid + 1;
        else if (v[mid] == n) return mid;
        else last = mid - 1;
    }
    return first;
}

double min3Double(double a, double b, double c);
Pointd min3Point(Pointd  a, Pointd b, Pointd c);

double max3Double(double a, double b, double c);
Pointd max3Point(Pointd  a, Pointd b, Pointd c);
bool checkPointInVector(Pointd p, std::vector<Pointd> vct);

float absolute(float x);

bool epsilonEqual(float x, float v);

bool epsilonEqual(const Vec3 &x, const Vec3 &v);

#endif // COMMON_H
