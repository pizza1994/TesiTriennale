/**
 @author    Marco Livesu (marco.livesu@gmail.com)
 @copyright Marco Livesu 2014.
*/

#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

#include <float.h>

#include "vec3.h"

typedef enum
{
    ABSTRACT  ,
    TRIMESH   ,
    QUADMESH  ,
    TETMESH   ,
    HEXMESH   ,
    SKELETON  ,
    LINE      ,
    ARROW     ,
    LABEL     ,
    OTHER
}
ObjectType;

class DrawableObject
{
    public :

        ObjectType type;

        DrawableObject() { type = ABSTRACT; }

        virtual void  draw()         const = 0;  // do rendering
        virtual vec3d scene_center() const = 0;  // get position in space
        virtual float scene_radius() const = 0;  // get size (approx. radius of the bounding sphere)
};

#endif // DRAWABLE_OBJECT_H
