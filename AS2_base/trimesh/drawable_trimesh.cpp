/**
 @author    Marco Livesu (marco.livesu@gmail.com)
 @copyright Marco Livesu 2014.
*/

#include "drawable_trimesh.h"

#ifdef __APPLE__
#include <gl.h>
#else
#include <GL/gl.h>
#endif

DrawableTrimesh::DrawableTrimesh() : Trimesh<double>()
{
    init();
}

DrawableTrimesh::DrawableTrimesh(const char *filename) : Trimesh<double>(filename)
{
    init();
}

void DrawableTrimesh::init()
{
    type               = TRIMESH;
    draw_mode          = DRAW_MESH | DRAW_SMOOTH | DRAW_VERTEXCOLOR;
    wireframe_width    = 1;
    wireframe_color[0] = 0.1;
    wireframe_color[1] = 0.1;
    wireframe_color[2] = 0.1;

    set_t_color(0.1, 0.8, 0.1);
    set_v_color(0.1, 0.8, 0.1);
}

void DrawableTrimesh::clear()
{
    Trimesh<double>::clear();
    v_colors.clear();
    t_colors.clear();
}

vec3d DrawableTrimesh::scene_center() const
{
    return bbox.center();
}

float DrawableTrimesh::scene_radius() const
{
    return bbox.diag();
}

void DrawableTrimesh::render_pass() const
{
    if (draw_mode & DRAW_POINTS)
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, coords.data());

        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer (3, GL_FLOAT, 0, v_colors.data());

        glDrawArrays(GL_POINTS, 0, num_vertices());

        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
    else if (draw_mode & DRAW_SMOOTH || draw_mode & DRAW_FLAT)
    {
        // Old fashioned, verbose and slow rendering.
        //
        if (draw_mode & DRAW_FACECOLOR)
        {
            int n_tris = tris.size()/3;
            for(int tid=0; tid<n_tris; ++tid)
            {
                int tid_ptr  = 3 * tid;
                int vid0     = tris[tid_ptr + 0];
                int vid1     = tris[tid_ptr + 1];
                int vid2     = tris[tid_ptr + 2];
                int vid0_ptr = 3 * vid0;
                int vid1_ptr = 3 * vid1;
                int vid2_ptr = 3 * vid2;

                glBegin(GL_TRIANGLES);
                glColor3fv(&(t_colors[tid_ptr]));
                glNormal3dv(&(v_norm[vid0_ptr]));
                glVertex3dv(&(coords[vid0_ptr]));
                glNormal3dv(&(v_norm[vid1_ptr]));
                glVertex3dv(&(coords[vid1_ptr]));
                glNormal3dv(&(v_norm[vid2_ptr]));
                glVertex3dv(&(coords[vid2_ptr]));
                glEnd();
            }
        }
        else
        {
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_DOUBLE, 0, coords.data());

            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(GL_DOUBLE, 0, v_norm.data());

            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(3, GL_FLOAT, 0, v_colors.data());

            glDrawElements(GL_TRIANGLES, tris.size(), GL_UNSIGNED_INT, tris.data());

            glDisableClientState(GL_COLOR_ARRAY);
            glDisableClientState(GL_NORMAL_ARRAY);
            glDisableClientState(GL_VERTEX_ARRAY);
        }
    }

    if (draw_mode & DRAW_WIREFRAME)
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, coords.data());

        glLineWidth(wireframe_width);
        glColor4fv(wireframe_color);

        glDrawElements(GL_TRIANGLES, tris.size(), GL_UNSIGNED_INT, tris.data());

        glDisableClientState(GL_VERTEX_ARRAY);
    }
}


void DrawableTrimesh::draw() const
{
    if (draw_mode & DRAW_MESH)
    {
        if (draw_mode & DRAW_WIREFRAME)
        {
            if (draw_mode & DRAW_POINTS)
            {
                glDisable(GL_LIGHTING);
                glShadeModel(GL_FLAT);
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glDepthRange(0.0, 1.0);
                render_pass();
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }

            else

            if (draw_mode & DRAW_FLAT)
            {
                glEnable(GL_LIGHTING);
                glShadeModel(GL_FLAT);
                glDepthRange(0.01, 1.0);
                render_pass();

                glDisable(GL_LIGHTING);
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glDepthRange(0.0, 1.0);
                glDepthFunc(GL_LEQUAL);
                render_pass();
                glDepthFunc(GL_LESS);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }

            else

            if (draw_mode & DRAW_SMOOTH)
            {
                glEnable(GL_LIGHTING);
                glShadeModel(GL_SMOOTH);
                glDepthRange(0.01, 1.0);
                render_pass();

                glDisable(GL_LIGHTING);
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glDepthRange(0.0, 1.0);
                glDepthFunc(GL_LEQUAL);
                render_pass();
                glDepthFunc(GL_LESS);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }

        else

        {
            if (draw_mode & DRAW_POINTS)
            {
                glDisable(GL_LIGHTING);
                render_pass();
            }

            else

            if (draw_mode & DRAW_FLAT)
            {
                glEnable(GL_LIGHTING);
                glShadeModel(GL_FLAT);
                render_pass();
            }

            else

            if (draw_mode & DRAW_SMOOTH)
            {
                glEnable(GL_LIGHTING);
                glShadeModel(GL_SMOOTH);
                render_pass();
            }
        }
    }
}

void DrawableTrimesh::set_draw_mesh(bool b)
{
    if (b) draw_mode |=  DRAW_MESH;
    else   draw_mode &= ~DRAW_MESH;
}

void DrawableTrimesh::set_wireframe(bool b)
{
    if (b) draw_mode |=  DRAW_WIREFRAME;
    else   draw_mode &= ~DRAW_WIREFRAME;
}

void DrawableTrimesh::set_flat_shading()
{
    draw_mode |=  DRAW_FLAT;
    draw_mode &= ~DRAW_SMOOTH;
    draw_mode &= ~DRAW_POINTS;
}

void DrawableTrimesh::set_smooth_shading()
{
    draw_mode |=  DRAW_SMOOTH;
    draw_mode &= ~DRAW_FLAT;
    draw_mode &= ~DRAW_POINTS;
}

void DrawableTrimesh::set_points_shading()
{
    draw_mode |=  DRAW_POINTS;
    draw_mode &= ~DRAW_FLAT;
    draw_mode &= ~DRAW_SMOOTH;
}

void DrawableTrimesh::set_enable_vertex_color()
{
    draw_mode |=  DRAW_VERTEXCOLOR;
    draw_mode &= ~DRAW_FACECOLOR;
}

void DrawableTrimesh::set_enable_triangle_color()
{
    draw_mode |=  DRAW_FACECOLOR;
    draw_mode &= ~DRAW_VERTEXCOLOR;
}

void DrawableTrimesh::set_wireframe_color(float r, float g, float b)
{
    wireframe_color[0] = r;
    wireframe_color[1] = g;
    wireframe_color[2] = b;
}

void DrawableTrimesh::set_wireframe_width(float width)
{
    wireframe_width = width;
}

void DrawableTrimesh::set_v_color(float r, float g, float b)
{
    v_colors.resize(num_vertices()*3);
    for(int i=0; i<(int)v_colors.size(); i+=3)
    {
        v_colors[i + 0] = r;
        v_colors[i + 1] = g;
        v_colors[i + 2] = b;
    }
}

void DrawableTrimesh::set_t_color(float r, float g, float b)
{
    t_colors.resize(num_triangles()*3);
    for(int i=0; i<(int)t_colors.size(); i+=3)
    {
        t_colors[i + 0] = r;
        t_colors[i + 1] = g;
        t_colors[i + 2] = b;
    }
}
