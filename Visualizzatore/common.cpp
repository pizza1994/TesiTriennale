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
