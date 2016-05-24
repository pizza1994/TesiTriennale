#ifndef COMMON_H
#define COMMON_H
#define SCALE 100
#include <set>
#include <vector>
#include "lib/common/point.h"
#include <CGAL/Simple_cartesian.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/boost/graph/graph_traits_Polyhedron_3.h>
#include "CGAL/Polyhedron_items_3.h"
#include "CGAL/HalfedgeDS_list.h"
#include <CGAL/AABB_face_graph_triangle_primitive.h>
#include <CGAL/algorithm.h>
#include <CGAL/Side_of_triangle_mesh.h>




typedef CGAL::Simple_cartesian<double> K;
typedef CGAL::Polyhedron_3<K> Polyhedron;
typedef CGAL::AABB_face_graph_triangle_primitive<Polyhedron> Primitive;
typedef CGAL::AABB_traits<K, Primitive> Traits;
typedef CGAL::AABB_tree<Traits> Tree;
typedef CGAL::Side_of_triangle_mesh<Polyhedron, K> Point_inside;

#define EPSILON 0.00000001

#define ONE_ON_SQRT2 0.7071067811865475f
#define ONE_ON_SQRT3 0.5773502691896258f

typedef K::Ray_3 Ray;
typedef K::Triangle_3 Triangle;
typedef std::list<Triangle>::iterator Iterator;


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
K::Point_3 point_to_point3(Pointd a);
double max3Double(double a, double b, double c);
Pointd max3Point(Pointd  a, Pointd b, Pointd c);
bool checkPointInVector(Pointd p, std::vector<Pointd> vct);

float absolute(float x);

bool epsilonEqual(float x, float v);

bool epsilonEqual(const Vec3 &x, const Vec3 &v);

bool pointInside(Tree &tree, K::Point_3 query);

#endif // COMMON_H
