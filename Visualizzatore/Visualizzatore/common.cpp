#include "common.h"

int WINDOW_MANAGER_ID;
int MESH_STACK_MANAGER_ID;
int DCEL_MANAGER_ID;
int GRID_MANAGER_ID;
int TRIMESH_MANAGER_ID;
int OCTREE_MANAGER_ID;

float absolute(float x)
{
    if (x < 0) return x*-1;
    return x;
}

bool epsilonEqual(float x, float v){
    if ((v-EPSILON) <= x && (v+EPSILON) >= x) return true;
    return false;
}


bool epsilonEqual(const Vec3 &x, const Vec3 &v)
{
    if ((epsilonEqual(x.x(), v.x())) && (epsilonEqual(x.y(), v.y())) && (epsilonEqual(x.z(), v.z()))) return true;
    else return false;

}

Pointd max3Point(Pointd a, Pointd b, Pointd c)
{
    return Pointd( max3Double(a.x(), b.x(), c.x()), max3Double(a.y(), b.y(), c.y()), max3Double(a.z(), b.z(), c.z()) );
}

double max3Double(double a, double b, double c){

    if ( a > b )
    {
        if (a > c)
            return a;
        else
            return c;
    }
    else
    {
        if ( b > c )
            return b;
        else
            return c;
    }
}

Pointd min3Point(Pointd a, Pointd b, Pointd c)
{
    return Pointd( min3Double(a.x(), b.x(), c.x()), min3Double(a.y(), b.y(), c.y()), min3Double(a.z(), b.z(), c.z()) );
}

double min3Double(double a, double b, double c){

    if ( a < b )
    {
        if (a < c)
            return a;
        else
            return c;
    }
    else
    {
        if ( b < c )
            return b;
        else
            return c;
    }
}

bool checkPointInVector(Pointd p, std::vector<Pointd> vct)
{
    for(int i = 0; i< (int) vct.size(); i++){


        if(p.x() == vct[i].x() && p.y() == vct[i].y() && p.z() == vct[i].z()){

            return true;
        }

    }
    return false;
}

K::Point_3 point_to_point3(Pointd a)
{
    return K::Point_3 (a.x(), a.y(), a.z());
}

bool pointInside(Tree &tree, K::Point_3 query) {
    // Construct AABB tree with a KdTree
    // Initialize the point-in-polyhedron tester
    Point_inside inside_tester(tree);

    // Determine the side and return true if inside!
    return inside_tester(query) == CGAL::ON_BOUNDED_SIDE;
}
