#ifndef MESH_H
#define MESH_H

 
//#include"vec3.h"
#include"load_save.h"
#include "lib/common/point.h"
#include <map>
#include "common.h"


//using namespace geom;


template< typename real >
class mesh {
private:
    std::vector<real>               m_coords;
    std::vector<int>                m_tris;
    std::vector<int>                m_quads;
    std::vector<int>                m_tets;
    std::vector<int>                m_hexes;
    std::vector<std::vector<Pointd>> quads_used;
	std::vector<int>				m_anchors;
    std::vector<int>                m_quads_to_delete;
    std::vector<int>                m_tris_to_delete;

    std::vector< bool >             m_vtx_on_surface;
    std::vector< std::vector<int> > m_vtx2tri;
    std::vector< std::vector<int> > m_vtx2quad;
    std::vector< std::vector<int> > m_vtx2tet;
    std::vector< std::vector<int> > m_vtx2hex;

    std::vector<real> to_real_array( const std::vector<double> &in ) const {
        std::vector<real> res(in.size());
        for(int i=0; i<in.size(); i++ ){
            res[i] = in[i];
        }
        return res;
    }
    
    std::vector<double> from_real_array( const std::vector<real> &in ) const {
        std::vector<double> res(in.size());
        for( int i=0; i<in.size(); i++ ){
            res[i] = in[i];
        }
        return res;
    }
    
    void build_adjacency(){

        m_vtx_on_surface = std::vector<bool>(num_vertices(),false);

        m_vtx2tri.clear();
        m_vtx2tri.resize( num_vertices() );

        for( int i=0; i<num_tris(); i++ ){
            for( int j=0; j<3; j++ ){

                m_vtx2tri[m_tris[i*3+j]].push_back( i );
                m_vtx_on_surface[m_tris[i*3+j]] = true;
              }
        }

        m_vtx2quad.clear();
        m_vtx2quad.resize( num_vertices() );


        for( int i=0; i<num_quads(); i++ ){
            for( int j=0; j<4; j++ ){
                m_vtx2quad[m_quads[i*4+j]].push_back( i );
                m_vtx_on_surface[m_quads[i*4+j]] = true;

            }
        }

        m_vtx2tet.clear();
        m_vtx2tet.resize( num_vertices() );
        for( int i=0; i<num_tets(); i++ ){
            for( int j=0; j<4; j++ ){
                m_vtx2tet[m_tets[i*4+j]].push_back( i );
            }
        }

        m_vtx2hex.clear();
        m_vtx2hex.resize( num_vertices() );
        for( int i=0; i<num_hexes(); i++ ){
            for( int j=0; j<8; j++ ){
                m_vtx2hex[m_hexes[i*8+j]].push_back( i );

            }
        }
    }
    
public:
    mesh(){
        
    }
    
    mesh( const char *filename ){
        load( filename );
    }
    
    mesh( const std::vector<real> &coords, const std::vector<int> &tris, const std::vector<int> &quads, const std::vector<int> &tets, const std::vector<int> &hexes ){
        set( coords, tris, quads, tets, hexes );
    }

    mesh(std::vector<std::vector<Pointd>> polyhedra, double length){
        std::vector<int> empty1;
        std::vector<int> empty2;
        std::vector<int> empty3;
        std::vector<int> hexes;
        std::vector<double> coords = subdivide(polyhedra, length, hexes);
        //deleteNotManifoldHexes(hexes);
        set(coords, empty1, empty2, empty3, hexes);
    }

    /*void deleteNotManifoldHexes(std::vector<int> &hexes){

        std::vector<int> hexesToDelete;

        for(int i = 0, p = 0; i < (int) hexes.size()/8; i++, p+=8){
            for(int j = 0, p1=0; j < (int) hexes.size()/8; j++, p1+=8){
                int counter = 0;
                if(i!=j){

                    if(hexes[p] == hexes[p1] || hexes[p] == hexes[p1+1] || hexes[p] == hexes[p1+2] || hexes[p] == hexes[p1+3] || hexes[p] == hexes[p1+4] || hexes[p] == hexes[p1+5] || hexes[p] == hexes[p1+6] || hexes[p] == hexes[p1+7])
                        counter++;
                    if(hexes[p+1] == hexes[p1] || hexes[p+1] == hexes[p1+1] || hexes[p+1] == hexes[p1+2] || hexes[p+1] == hexes[p1+3] || hexes[p+1] == hexes[p1+4] || hexes[p+1] == hexes[p1+5] || hexes[p+1] == hexes[p1+6] || hexes[p+1] == hexes[p1+7])
                        counter++;
                    if(hexes[p+2] == hexes[p1] || hexes[p+2] == hexes[p1+1] || hexes[p+2] == hexes[p1+2] || hexes[p+2] == hexes[p1+3] || hexes[p+2] == hexes[p1+4] || hexes[p+2] == hexes[p1+5] || hexes[p+2] == hexes[p1+6] || hexes[p+2] == hexes[p1+7])
                        counter++;
                    if(hexes[p+3] == hexes[p1] || hexes[p+3] == hexes[p1+1] || hexes[p+3] == hexes[p1+2] || hexes[p+3] == hexes[p1+3] || hexes[p+3] == hexes[p1+4] || hexes[p+3] == hexes[p1+5] || hexes[p+3] == hexes[p1+6] || hexes[p+3] == hexes[p1+7])
                        counter++;
                    if(hexes[p+4] == hexes[p1] || hexes[p+4] == hexes[p1+1] || hexes[p+4] == hexes[p1+2] || hexes[p+4] == hexes[p1+3] || hexes[p+4] == hexes[p1+4] || hexes[p+4] == hexes[p1+5] || hexes[p+4] == hexes[p1+6] || hexes[p+4] == hexes[p1+7])
                        counter++;
                    if(hexes[p+5] == hexes[p1] || hexes[p+5] == hexes[p1+1] || hexes[p+5] == hexes[p1+2] || hexes[p+5] == hexes[p1+3] || hexes[p+5] == hexes[p1+4] || hexes[p+5] == hexes[p1+5] || hexes[p+5] == hexes[p1+6] || hexes[p+5] == hexes[p1+7])
                        counter++;
                    if(hexes[p+6] == hexes[p1] || hexes[p+6] == hexes[p1+1] || hexes[p+6] == hexes[p1+2] || hexes[p+6] == hexes[p1+3] || hexes[p+6] == hexes[p1+4] || hexes[p+6] == hexes[p1+5] || hexes[p+6] == hexes[p1+6] || hexes[p+6] == hexes[p1+7])
                        counter++;
                    if(hexes[p+7] == hexes[p1] || hexes[p+7] == hexes[p1+1] || hexes[p+7] == hexes[p1+2] || hexes[p+7] == hexes[p1+3] || hexes[p+7] == hexes[p1+4] || hexes[p+7] == hexes[p1+5] || hexes[p+7] == hexes[p1+6] || hexes[p+7] == hexes[p1+7])
                        counter++;

                    if(counter==2)
                    {
                        bool flag = false;
                        for(int k : hexesToDelete){
                            if (p == k) flag=true;
                        }
                        if(!flag) hexesToDelete.push_back(p);

                    }
                }
            }
        }

       std::sort(hexesToDelete.begin(), hexesToDelete.end(), std::greater<int>());

       for(int i : hexesToDelete){
           qDebug()<<i;
           hexes.erase(hexes.begin()+i, hexes.begin()+i+8);
       }

    }*/

    void smoothNinetyDegreesAngles(double length, Polyhedron &poly){

        smoothAxis1(length, poly);
        smoothAxis2(length, poly);
        smoothAxis3(length, poly);
        smoothAxis4(length, poly);
        smoothAxis5(length, poly);
        smoothAxis6(length, poly);
        cleanQuads();
        cleanTris();
        cleanTrisOnQuads();
    }

    void smoothAxis1(double length, Polyhedron &poly){
        std::map<Pointd, int> vertexMap;
        int j, p=0, p1=0;
        std::vector<Pointd> quad;
        std::vector<std::vector<Pointd>> quads_used_here;
        bool flag1=false, flag2=false, flag3=false, flag4=false, flagNormal1=false, flagNormal2=false;
        std::list<Triangle> triangles;


        Tree tree(faces(poly).first, faces(poly).second, poly);
        tree.accelerate_distance_queries();

        quad.push_back(Pointd(0, 0, 0));
        quad.push_back(Pointd(0, 0, 0));
        quad.push_back(Pointd(0, 0, 0));
        quad.push_back(Pointd(0, 0, 0));

        for(int i = 0; i < (int) coords().size()/3; i++, p+=3)
        {
            vertexMap.insert(std::pair<Pointd, int>(Pointd(coords()[p], coords()[p+1], coords()[p+2]), i));
            /*if (Pointd(coords()[p], coords()[p+1], coords()[p+2]) < min)
                min = Pointd(coords()[p], coords()[p+1], coords()[p+2]);*/
        }

        p=0;

        for(int i = 0; i < (int) coords().size()/3; i++, p+=3)
        {
            quad[0] = Pointd(coords()[p], coords()[p+1]-length, coords()[p+2]+length);
            quad[1] = Pointd(coords()[p]+length, coords()[p+1]-length, coords()[p+2]+length);
            quad[2] = Pointd(coords()[p]+length, coords()[p+1], coords()[p+2]);
            quad[3] = Pointd(coords()[p], coords()[p+1], coords()[p+2]);

            for (j=0, p1=0; j< (int) coords().size()/3; j++, p1+=3)
            {
                if (quad[0] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag1 = true;
                if (quad[1] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag2 = true;
                if (quad[2] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag3 = true;
                if (quad[3] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag4 = true;
            }


            if (flag1 && flag2 && flag3 && flag4)
            {
                if (!(tree.do_intersect(K::Triangle_3(point_to_point3(quad[0]), point_to_point3(quad[1]), point_to_point3(quad[3])))) &&
                    !(tree.do_intersect(K::Triangle_3(point_to_point3(quad[1]), point_to_point3(quad[2]), point_to_point3(quad[3])))))
                {
                    for (j=0, p1=0; j< (int) coords().size()/3; j++, p1+=3)
                    {
                        int p2, k;


                        if (Pointd(quad[0].x(), quad[0].y()+length, quad[0].z()) == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                            for (k=0, p2=0; k< (int) coords().size()/3; k++, p2+=3)
                            {
                                if(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z()) == Pointd(coords()[p2], coords()[p2+1], coords()[p2+2]))
                                {
                                    std::vector<int> quads1 = adjacent_quads(vertexMap.at(Pointd(quad[0].x(), quad[0].y()+length, quad[0].z())));
                                    std::vector<int> quads2 = adjacent_quads(vertexMap.at(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z())));
                                    std::vector<int> shared_quads;
                                    for(int qd : quads1){
                                        for(int qd2 : quads2){
                                            if(qd==qd2)
                                                shared_quads.push_back(qd);
                                        }
                                    }

                                    cleanSharedQuads(quad, shared_quads);

                                    for (int x=0; x < (int) shared_quads.size(); x++)
                                    {
                                        for (int y=0; y < (int) shared_quads.size(); y++)
                                        {
                                            if (shared_quads[x] != shared_quads[y] && checkOrthoNormals(shared_quads[x], shared_quads[y]) && checkSameVerseNormals(shared_quads[x], shared_quads[y])
                                                    && checkQuadExists(vertexMap.at(quad[0]), vertexMap.at(Pointd(quad[0].x(), quad[0].y()+length, quad[0].z())), vertexMap.at(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z())), vertexMap.at(quad[1])) &&
                                                    checkQuadExists(vertexMap.at(quad[2]), vertexMap.at(Pointd(quad[0].x(), quad[0].y()+length, quad[0].z())), vertexMap.at(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z())), vertexMap.at(quad[3])))
                                            {
                                                flagNormal1 = true;
                                                int indexToDelete;
                                                if (!checkIfTriangleExists(vertexMap.at(Pointd(quad[0].x(), quad[0].y()+length, quad[0].z())), vertexMap.at(quad[0]), vertexMap.at(quad[3]), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[0].x(), quad[0].y()+length, quad[0].z())));
                                                    m_tris.push_back(vertexMap.at(quad[0]));
                                                    m_tris.push_back(vertexMap.at(quad[3]));
                                                }
                                                else
                                                {
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }

                                                if (!checkIfTriangleExists(vertexMap.at(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z())), vertexMap.at(quad[2]), vertexMap.at(quad[1]), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z())));
                                                    m_tris.push_back(vertexMap.at(quad[2]));
                                                    m_tris.push_back(vertexMap.at(quad[1]));
                                                }
                                                else
                                                {
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }

                                                m_quads_to_delete.push_back(shared_quads[x]);
                                                m_quads_to_delete.push_back(shared_quads[y]);

                                                break;
                                            }
                                        }
                                    if (flagNormal1) break;
                                    }
                                }
                            }


                        if(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z()) == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                            for (k=0, p2=0; k< (int) coords().size()/3; k++, p2+=3)
                            {
                                if(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z()) == Pointd(coords()[p2], coords()[p2+1], coords()[p2+2]))
                                {
                                    std::vector<int> quads1 = adjacent_quads(vertexMap.at(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z())));
                                    std::vector<int> quads2 = adjacent_quads(vertexMap.at(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z())));
                                    std::vector<int> shared_quads;
                                    for(int qd : quads1){
                                        for(int qd2 : quads2){
                                            if(qd==qd2)
                                                shared_quads.push_back(qd);
                                        }
                                    }

                                    cleanSharedQuads(quad, shared_quads);

                                    for (int x=0; x < (int) shared_quads.size(); x++)
                                    {
                                        for (int y=0; y < (int) shared_quads.size(); y++)
                                            if (shared_quads[x] != shared_quads[y] && checkOrthoNormals(shared_quads[x], shared_quads[y])&& checkSameVerseNormals(shared_quads[x], shared_quads[y])
                                                    && checkQuadExists(vertexMap.at(quad[3]), vertexMap.at(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z())), vertexMap.at(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z())), vertexMap.at(quad[2])) &&
                                                    checkQuadExists(vertexMap.at(quad[0]), vertexMap.at(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z())), vertexMap.at(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z())), vertexMap.at(quad[1])))
                                            {
                                                int indexToDelete;
                                                flagNormal2 = true;

                                                if(!checkIfTriangleExists( vertexMap.at(quad[3]), vertexMap.at(quad[0]), vertexMap.at(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z())), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(quad[3]));
                                                    m_tris.push_back(vertexMap.at(quad[0]));
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z())));
                                                }
                                                else{
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }
                                                if(!checkIfTriangleExists(vertexMap.at(quad[2]), vertexMap.at(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z())) , vertexMap.at(quad[1]), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(quad[2]));
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z())));
                                                    m_tris.push_back(vertexMap.at(quad[1]));
                                                }
                                                else{
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }
                                                m_quads_to_delete.push_back(shared_quads[x]);
                                                m_quads_to_delete.push_back(shared_quads[y]);

                                                break;
                                            }

                                        if (flagNormal2) break;
                                    }
                                }
                            }
                    }

                    if (flagNormal1)
                    {
                        m_quads.push_back(vertexMap.at(quad[2]));
                        m_quads.push_back(vertexMap.at(quad[3]));
                        m_quads.push_back(vertexMap.at(quad[0]));
                        m_quads.push_back(vertexMap.at(quad[1]));

                        std::vector<Pointd> temp;
                        temp.push_back(quad[2]);
                        temp.push_back(quad[3]);
                        temp.push_back(quad[0]);
                        temp.push_back(quad[1]);
                        quads_used_here.push_back(temp);
                    }
                    else if (flagNormal2)
                    {
                        m_quads.push_back(vertexMap.at(quad[3]));
                        m_quads.push_back(vertexMap.at(quad[2]));
                        m_quads.push_back(vertexMap.at(quad[1]));
                        m_quads.push_back(vertexMap.at(quad[0]));

                        std::vector<Pointd> temp;
                        temp.push_back(quad[3]);
                        temp.push_back(quad[2]);
                        temp.push_back(quad[1]);
                        temp.push_back(quad[0]);
                        quads_used_here.push_back(temp);

                    }

                    flagNormal1 = false;
                    flagNormal2 = false;

                }


            }

            flag1 = false;
            flag2 = false;
            flag3 = false;
            flag4 = false;

        }
        for (std::vector<Pointd> quad_used : quads_used_here)
            quads_used.push_back(quad_used);

    }

    void smoothAxis2(double length, Polyhedron &poly){
        std::map<Pointd, int> vertexMap;
        int j, p=0, p1=0;
        std::vector<Pointd> quad;
        std::vector<std::vector<Pointd>> quads_used_here;
        bool flag1=false, flag2=false, flag3=false, flag4=false, flagNormal1=false, flagNormal2=false;
        std::list<Triangle> triangles;


        Tree tree(faces(poly).first, faces(poly).second, poly);
        tree.accelerate_distance_queries();

        quad.push_back(Pointd(0, 0, 0));
        quad.push_back(Pointd(0, 0, 0));
        quad.push_back(Pointd(0, 0, 0));
        quad.push_back(Pointd(0, 0, 0));

        for(int i = 0; i < (int) coords().size()/3; i++, p+=3)
        {
            vertexMap.insert(std::pair<Pointd, int>(Pointd(coords()[p], coords()[p+1], coords()[p+2]), i));
            /*if (Pointd(coords()[p], coords()[p+1], coords()[p+2]) < min)
                min = Pointd(coords()[p], coords()[p+1], coords()[p+2]);*/
        }

        p=0;

        for(int i = 0; i < (int) coords().size()/3; i++, p+=3)
        {
            bool flag_quad_intersection = false;
            quad[0] = Pointd(coords()[p], coords()[p+1]-length, coords()[p+2]-length);
            quad[1] = Pointd(coords()[p]-length, coords()[p+1]-length, coords()[p+2]-length);
            quad[2] = Pointd(coords()[p]-length, coords()[p+1], coords()[p+2]);
            quad[3] = Pointd(coords()[p], coords()[p+1], coords()[p+2]);

            for (std::vector<Pointd> quad_already_used : quads_used){
                int intersections = 0;
                if (quad[0] == quad_already_used[0] || quad[0] == quad_already_used[1] || quad[0] == quad_already_used[2] || quad[0] == quad_already_used[3])
                    intersections++;
                if (quad[1] == quad_already_used[0] || quad[1] == quad_already_used[1] || quad[1] == quad_already_used[2] || quad[1] == quad_already_used[3])
                    intersections++;
                if (quad[2] == quad_already_used[0] || quad[2] == quad_already_used[1] || quad[2] == quad_already_used[2] || quad[2] == quad_already_used[3])
                    intersections++;
                if (quad[3] == quad_already_used[0] || quad[3] == quad_already_used[1] || quad[3] == quad_already_used[2] || quad[3] == quad_already_used[3])
                    intersections++;
                if (intersections > 1)
                {
                    flag_quad_intersection = true;
                    break;
                }
            }

            for (j=0, p1=0; j< (int) coords().size()/3; j++, p1+=3)
            {
                if (quad[0] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag1 = true;
                if (quad[1] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag2 = true;
                if (quad[2] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag3 = true;
                if (quad[3] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag4 = true;
            }


            if (flag1 && flag2 && flag3 && flag4 && !flag_quad_intersection)
            {
                if (!(tree.do_intersect(K::Triangle_3(point_to_point3(quad[0]), point_to_point3(quad[1]), point_to_point3(quad[3])))) &&
                    !(tree.do_intersect(K::Triangle_3(point_to_point3(quad[1]), point_to_point3(quad[2]), point_to_point3(quad[3])))))
                {
                    for (j=0, p1=0; j< (int) coords().size()/3; j++, p1+=3)
                    {
                        int p2, k;


                        if (Pointd(quad[0].x(), quad[0].y()+length, quad[0].z()) == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                            for (k=0, p2=0; k< (int) coords().size()/3; k++, p2+=3)
                            {
                                if(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z()) == Pointd(coords()[p2], coords()[p2+1], coords()[p2+2]))
                                {
                                    std::vector<int> quads1 = adjacent_quads(vertexMap.at(Pointd(quad[0].x(), quad[0].y()+length, quad[0].z())));
                                    std::vector<int> quads2 = adjacent_quads(vertexMap.at(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z())));
                                    std::vector<int> shared_quads;
                                    for(int qd : quads1){
                                        for(int qd2 : quads2){
                                            if(qd==qd2)
                                                shared_quads.push_back(qd);
                                        }
                                    }

                                    cleanSharedQuads(quad, shared_quads);

                                    for (int x=0; x < (int) shared_quads.size(); x++)
                                    {
                                        for (int y=0; y < (int) shared_quads.size(); y++)
                                            if (shared_quads[x] != shared_quads[y] && checkOrthoNormals(shared_quads[x], shared_quads[y]) && checkSameVerseNormals(shared_quads[x], shared_quads[y])
                                                    && checkQuadExists(vertexMap.at(quad[0]), vertexMap.at(Pointd(quad[0].x(), quad[0].y()+length, quad[0].z())), vertexMap.at(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z())), vertexMap.at(quad[1])) &&
                                                    checkQuadExists(vertexMap.at(quad[2]), vertexMap.at(Pointd(quad[0].x(), quad[0].y()+length, quad[0].z())), vertexMap.at(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z())), vertexMap.at(quad[3])))
                                            {
                                                flagNormal1 = true;

                                                int indexToDelete;
                                                if (!checkIfTriangleExists(vertexMap.at(Pointd(quad[0].x(), quad[0].y()+length, quad[0].z())), vertexMap.at(quad[3]), vertexMap.at(quad[0]), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[0].x(), quad[0].y()+length, quad[0].z())));
                                                    m_tris.push_back(vertexMap.at(quad[0]));
                                                    m_tris.push_back(vertexMap.at(quad[3]));

                                                }
                                                else
                                                {
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }

                                                if (!checkIfTriangleExists(vertexMap.at(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z())), vertexMap.at(quad[1]), vertexMap.at(quad[2]), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z())));
                                                    m_tris.push_back(vertexMap.at(quad[2]));
                                                    m_tris.push_back(vertexMap.at(quad[1]));
                                                }
                                                else
                                                {
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }



                                                m_quads_to_delete.push_back(shared_quads[x]);
                                                m_quads_to_delete.push_back(shared_quads[y]);

                                                break;
                                            }
                                        if(flagNormal1) break;
                                    }
                                }
                            }


                        if(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z()) == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                            for (k=0, p2=0; k< (int) coords().size()/3; k++, p2+=3)
                            {
                                if(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z()) == Pointd(coords()[p2], coords()[p2+1], coords()[p2+2]))
                                {
                                    std::vector<int> quads1 = adjacent_quads(vertexMap.at(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z())));
                                    std::vector<int> quads2 = adjacent_quads(vertexMap.at(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z())));
                                    std::vector<int> shared_quads;
                                    for(int qd : quads1){
                                        for(int qd2 : quads2){
                                            if(qd==qd2)
                                                shared_quads.push_back(qd);
                                        }
                                    }

                                    cleanSharedQuads(quad, shared_quads);

                                    for (int x=0; x < (int) shared_quads.size(); x++)
                                    {
                                        for (int y=0; y < (int) shared_quads.size(); y++)
                                            if (shared_quads[x] != shared_quads[y] && checkOrthoNormals(shared_quads[x], shared_quads[y]) && checkSameVerseNormals(shared_quads[x], shared_quads[y])
                                                    && checkQuadExists(vertexMap.at(quad[3]), vertexMap.at(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z())), vertexMap.at(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z())), vertexMap.at(quad[2])) &&
                                                    checkQuadExists(vertexMap.at(quad[0]), vertexMap.at(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z())), vertexMap.at(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z())), vertexMap.at(quad[1])))
                                            {
                                                flagNormal2 = true;

                                                int indexToDelete;
                                                if (!checkIfTriangleExists(vertexMap.at(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z())), vertexMap.at(quad[3]), vertexMap.at(quad[0]), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(quad[3]));
                                                    m_tris.push_back(vertexMap.at(quad[0]));
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z())));

                                                }
                                                else
                                                {
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }

                                                if (!checkIfTriangleExists(vertexMap.at(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z())), vertexMap.at(quad[1]), vertexMap.at(quad[2]), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(quad[2]));
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z())));
                                                    m_tris.push_back(vertexMap.at(quad[1]));
                                                }
                                                else
                                                {
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }


                                                m_quads_to_delete.push_back(shared_quads[x]);
                                                m_quads_to_delete.push_back(shared_quads[y]);

                                                break;
                                            }
                                        if(flagNormal2) break;
                                    }
                                }
                            }
                        }

                    if (flagNormal1)
                    {
                        m_quads.push_back(vertexMap.at(quad[0]));
                        m_quads.push_back(vertexMap.at(quad[1]));
                        m_quads.push_back(vertexMap.at(quad[2]));
                        m_quads.push_back(vertexMap.at(quad[3]));

                        std::vector<Pointd> temp;
                        temp.push_back(quad[0]);
                        temp.push_back(quad[1]);
                        temp.push_back(quad[2]);
                        temp.push_back(quad[3]);
                        quads_used_here.push_back(temp);

                    }
                    else if (flagNormal2)
                    {
                        m_quads.push_back(vertexMap.at(quad[1]));
                        m_quads.push_back(vertexMap.at(quad[0]));
                        m_quads.push_back(vertexMap.at(quad[3]));
                        m_quads.push_back(vertexMap.at(quad[2]));
                        std::vector<Pointd> temp;
                        temp.push_back(quad[0]);
                        temp.push_back(quad[1]);
                        temp.push_back(quad[2]);
                        temp.push_back(quad[3]);
                        quads_used_here.push_back(temp);

                    }

                    flagNormal1 = false;
                    flagNormal2 = false;

                }


            }

            flag1 = false;
            flag2 = false;
            flag3 = false;
            flag4 = false;

        }

        for (std::vector<Pointd> quad_used : quads_used_here)
            quads_used.push_back(quad_used);

    }

    void smoothAxis3(double length, Polyhedron &poly){
        std::map<Pointd, int> vertexMap;
        int j, p=0, p1=0;
        std::vector<Pointd> quad;
        std::vector<std::vector<Pointd>> quads_used_here;
        bool flag1=false, flag2=false, flag3=false, flag4=false, flagNormal1=false, flagNormal2=false;
        std::list<Triangle> triangles;


        Tree tree(faces(poly).first, faces(poly).second, poly);
        tree.accelerate_distance_queries();

        quad.push_back(Pointd(0, 0, 0));
        quad.push_back(Pointd(0, 0, 0));
        quad.push_back(Pointd(0, 0, 0));
        quad.push_back(Pointd(0, 0, 0));

        for(int i = 0; i < (int) coords().size()/3; i++, p+=3)
        {
            vertexMap.insert(std::pair<Pointd, int>(Pointd(coords()[p], coords()[p+1], coords()[p+2]), i));
            /*if (Pointd(coords()[p], coords()[p+1], coords()[p+2]) < min)
                min = Pointd(coords()[p], coords()[p+1], coords()[p+2]);*/
        }

        p=0;

        for(int i = 0; i < (int) coords().size()/3; i++, p+=3)
        {
            bool flag_quad_intersection = false;
            quad[0] = Pointd(coords()[p], coords()[p+1]-length, coords()[p+2]);
            quad[1] = Pointd(coords()[p]+length, coords()[p+1]-length, coords()[p+2]+length);
            quad[2] = Pointd(coords()[p]+length, coords()[p+1], coords()[p+2]+length);
            quad[3] = Pointd(coords()[p], coords()[p+1], coords()[p+2]);


            for (std::vector<Pointd> quad_already_used : quads_used){
                int intersections = 0;
                if (quad[0] == quad_already_used[0] || quad[0] == quad_already_used[1] || quad[0] == quad_already_used[2] || quad[0] == quad_already_used[3])
                    intersections++;
                if (quad[1] == quad_already_used[0] || quad[1] == quad_already_used[1] || quad[1] == quad_already_used[2] || quad[1] == quad_already_used[3])
                    intersections++;
                if (quad[2] == quad_already_used[0] || quad[2] == quad_already_used[1] || quad[2] == quad_already_used[2] || quad[2] == quad_already_used[3])
                    intersections++;
                if (quad[3] == quad_already_used[0] || quad[3] == quad_already_used[1] || quad[3] == quad_already_used[2] || quad[3] == quad_already_used[3])
                    intersections++;
                if (intersections > 1)
                {
                    flag_quad_intersection = true;
                    break;
                }
            }


            for (j=0, p1=0; j< (int) coords().size()/3; j++, p1+=3)
            {
                if (quad[0] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag1 = true;
                if (quad[1] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag2 = true;
                if (quad[2] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag3 = true;
                if (quad[3] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag4 = true;
            }



            if (flag1 && flag2 && flag3 && flag4 && !flag_quad_intersection)
            {
                if (!(tree.do_intersect(K::Triangle_3(point_to_point3(quad[0]), point_to_point3(quad[1]), point_to_point3(quad[3])))) &&
                    !(tree.do_intersect(K::Triangle_3(point_to_point3(quad[1]), point_to_point3(quad[2]), point_to_point3(quad[3])))))
                {
                    for (j=0, p1=0; j< (int) coords().size()/3; j++, p1+=3)
                    {
                        int p2, k;


                        if (Pointd(quad[0].x(), quad[0].y(), quad[0].z()+length) == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                            for (k=0, p2=0; k < (int) coords().size()/3; k++, p2+=3)
                            {
                                if(Pointd(quad[3].x(), quad[3].y(), quad[3].z()+length) == Pointd(coords()[p2], coords()[p2+1], coords()[p2+2]))
                                {
                                    std::vector<int> quads1 = adjacent_quads(vertexMap.at(Pointd(quad[0].x(), quad[0].y(), quad[0].z()+length)));
                                    std::vector<int> quads2 = adjacent_quads(vertexMap.at(Pointd(quad[3].x(), quad[3].y(), quad[3].z()+length)));
                                    std::vector<int> shared_quads;
                                    for(int qd : quads1){
                                        for(int qd2 : quads2){
                                            if(qd==qd2)
                                                shared_quads.push_back(qd);
                                        }
                                    }

                                    cleanSharedQuads(quad, shared_quads);

                                    for (int x=0; x < (int) shared_quads.size(); x++)
                                    {
                                        for (int y=0; y < (int) shared_quads.size(); y++)
                                            if (shared_quads[x] != shared_quads[y] && checkOrthoNormals(shared_quads[x], shared_quads[y])&& checkSameVerseNormals(shared_quads[x], shared_quads[y])
                                                    && checkQuadExists(vertexMap.at(quad[3]), vertexMap.at(Pointd(quad[3].x(), quad[3].y(), quad[3].z()+length)), vertexMap.at(Pointd(quad[0].x(), quad[0].y(), quad[0].z()+length)), vertexMap.at(quad[0])) &&
                                                    checkQuadExists(vertexMap.at(quad[1]), vertexMap.at(Pointd(quad[3].x(), quad[3].y(), quad[3].z()+length)), vertexMap.at(Pointd(quad[0].x(), quad[0].y(), quad[0].z()+length)), vertexMap.at(quad[2])))
                                            {
                                                flagNormal1 = true;

                                                int indexToDelete;
                                                if (!checkIfTriangleExists(vertexMap.at(Pointd(quad[3].x(), quad[3].y(), quad[3].z()+length)), vertexMap.at(quad[3]), vertexMap.at(quad[2]), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[3].x(), quad[3].y(), quad[3].z()+length)));
                                                    m_tris.push_back(vertexMap.at(quad[3]));
                                                    m_tris.push_back(vertexMap.at(quad[2]));
                                                }
                                                else
                                                {
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }

                                                if (!checkIfTriangleExists(vertexMap.at(Pointd(quad[0].x(), quad[0].y(), quad[0].z()+length)), vertexMap.at(quad[1]), vertexMap.at(quad[0]), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(quad[1]));
                                                    m_tris.push_back(vertexMap.at(quad[0]));
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[0].x(), quad[0].y(), quad[0].z()+length)));
                                                }
                                                else
                                                {
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }


                                                m_quads_to_delete.push_back(shared_quads[x]);
                                                m_quads_to_delete.push_back(shared_quads[y]);

                                                break;
                                            }
                                        if(flagNormal1) break;
                                    }
                                }
                            }


                        if(Pointd(quad[3].x()+length, quad[3].y(), quad[3].z()) == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                            for (k=0, p2=0; k< (int) coords().size()/3; k++, p2+=3)
                            {
                                if(Pointd(quad[0].x()+length, quad[0].y(), quad[0].z()) == Pointd(coords()[p2], coords()[p2+1], coords()[p2+2])
                                        )
                                {
                                    std::vector<int> quads1 = adjacent_quads(vertexMap.at(Pointd(quad[3].x()+length, quad[3].y(), quad[3].z())));
                                    std::vector<int> quads2 = adjacent_quads(vertexMap.at(Pointd(quad[0].x()+length, quad[0].y(), quad[0].z())));
                                    std::vector<int> shared_quads;
                                    for(int qd : quads1){
                                        for(int qd2 : quads2){
                                            if(qd==qd2)
                                                shared_quads.push_back(qd);
                                        }
                                    }

                                    cleanSharedQuads(quad, shared_quads);

                                    for (int x=0; x < (int) shared_quads.size(); x++)
                                    {
                                        for (int y=0; y < (int) shared_quads.size(); y++)
                                            if (shared_quads[x] != shared_quads[y] && checkOrthoNormals(shared_quads[x], shared_quads[y])&& checkSameVerseNormals(shared_quads[x], shared_quads[y])
                                                    && checkQuadExists(vertexMap.at(quad[3]), vertexMap.at(Pointd(quad[3].x()+length, quad[3].y(), quad[3].z())), vertexMap.at(Pointd(quad[0].x()+length, quad[0].y(), quad[0].z())), vertexMap.at(quad[0])) &&
                                                    checkQuadExists(vertexMap.at(quad[1]), vertexMap.at(Pointd(quad[3].x()+length, quad[3].y(), quad[3].z())), vertexMap.at(Pointd(quad[0].x()+length, quad[0].y(), quad[0].z())), vertexMap.at(quad[2])))
                                            {
                                                flagNormal2 = true;

                                                int indexToDelete;
                                                if (!checkIfTriangleExists(vertexMap.at(Pointd(quad[3].x()+length, quad[3].y(), quad[3].z())), vertexMap.at(quad[3]), vertexMap.at(quad[2]), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[3].x()+length, quad[3].y(), quad[3].z())));
                                                    m_tris.push_back(vertexMap.at(quad[2]));
                                                    m_tris.push_back(vertexMap.at(quad[3]));
                                                }
                                                else
                                                {
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }

                                                if (!checkIfTriangleExists(vertexMap.at(Pointd(quad[0].x()+length, quad[0].y(), quad[0].z())), vertexMap.at(quad[1]), vertexMap.at(quad[0]), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(quad[1]));
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[0].x()+length, quad[0].y(), quad[0].z())));
                                                    m_tris.push_back(vertexMap.at(quad[0]));
                                                }
                                                else
                                                {
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }

                                                m_quads_to_delete.push_back(shared_quads[x]);
                                                m_quads_to_delete.push_back(shared_quads[y]);

                                                break;
                                            }
                                        if(flagNormal2) break;
                                    }
                                }
                            }
                    }


                    if (flagNormal1)
                    {
                        m_quads.push_back(vertexMap.at(quad[0]));
                        m_quads.push_back(vertexMap.at(quad[1]));
                        m_quads.push_back(vertexMap.at(quad[2]));
                        m_quads.push_back(vertexMap.at(quad[3]));
                        std::vector<Pointd> temp;
                        temp.push_back(quad[0]);
                        temp.push_back(quad[1]);
                        temp.push_back(quad[2]);
                        temp.push_back(quad[3]);
                        quads_used_here.push_back(temp);

                    }
                    else if (flagNormal2)
                    {


                        m_quads.push_back(vertexMap.at(quad[1]));
                        m_quads.push_back(vertexMap.at(quad[0]));
                        m_quads.push_back(vertexMap.at(quad[3]));
                        m_quads.push_back(vertexMap.at(quad[2]));
                        std::vector<Pointd> temp;
                        temp.push_back(quad[0]);
                        temp.push_back(quad[1]);
                        temp.push_back(quad[2]);
                        temp.push_back(quad[3]);
                        quads_used_here.push_back(temp);


                    }

                    flagNormal1 = false;
                    flagNormal2 = false;

                }


            }

            flag1 = false;
            flag2 = false;
            flag3 = false;
            flag4 = false;

        }

        for (std::vector<Pointd> quad_used : quads_used_here)
            quads_used.push_back(quad_used);

    }

    void smoothAxis4(double length, Polyhedron &poly){
        std::map<Pointd, int> vertexMap;
        int j, p=0, p1=0;
        std::vector<Pointd> quad;
        std::vector<std::vector<Pointd>> quads_used_here;
        bool flag1=false, flag2=false, flag3=false, flag4=false, flagNormal1=false, flagNormal2=false;
        std::list<Triangle> triangles;


        Tree tree(faces(poly).first, faces(poly).second, poly);
        tree.accelerate_distance_queries();

        quad.push_back(Pointd(0, 0, 0));
        quad.push_back(Pointd(0, 0, 0));
        quad.push_back(Pointd(0, 0, 0));
        quad.push_back(Pointd(0, 0, 0));

        for(int i = 0; i < (int) coords().size()/3; i++, p+=3)
        {
            vertexMap.insert(std::pair<Pointd, int>(Pointd(coords()[p], coords()[p+1], coords()[p+2]), i));
            /*if (Pointd(coords()[p], coords()[p+1], coords()[p+2]) < min)
                min = Pointd(coords()[p], coords()[p+1], coords()[p+2]);*/
        }

        p=0;

        for(int i = 0; i < (int) coords().size()/3; i++, p+=3)
        {
            bool flag_quad_intersection = false;
            quad[0] = Pointd(coords()[p], coords()[p+1]-length, coords()[p+2]);
            quad[1] = Pointd(coords()[p]+length, coords()[p+1]-length, coords()[p+2]-length);
            quad[2] = Pointd(coords()[p]+length, coords()[p+1], coords()[p+2]-length);
            quad[3] = Pointd(coords()[p], coords()[p+1], coords()[p+2]);


            for (std::vector<Pointd> quad_already_used : quads_used){
                int intersections = 0;
                if (quad[0] == quad_already_used[0] || quad[0] == quad_already_used[1] || quad[0] == quad_already_used[2] || quad[0] == quad_already_used[3])
                    intersections++;
                if (quad[1] == quad_already_used[0] || quad[1] == quad_already_used[1] || quad[1] == quad_already_used[2] || quad[1] == quad_already_used[3])
                    intersections++;
                if (quad[2] == quad_already_used[0] || quad[2] == quad_already_used[1] || quad[2] == quad_already_used[2] || quad[2] == quad_already_used[3])
                    intersections++;
                if (quad[3] == quad_already_used[0] || quad[3] == quad_already_used[1] || quad[3] == quad_already_used[2] || quad[3] == quad_already_used[3])
                    intersections++;
                if (intersections > 1)
                {
                    flag_quad_intersection = true;
                    break;
                }
            }


            for (j=0, p1=0; j< (int) coords().size()/3; j++, p1+=3)
            {
                if (quad[0] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag1 = true;
                if (quad[1] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag2 = true;
                if (quad[2] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag3 = true;
                if (quad[3] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag4 = true;
            }


            if (flag1 && flag2 && flag3 && flag4 && !flag_quad_intersection)
            {
                if (!(tree.do_intersect(K::Triangle_3(point_to_point3(quad[0]), point_to_point3(quad[1]), point_to_point3(quad[3])))) &&
                    !(tree.do_intersect(K::Triangle_3(point_to_point3(quad[1]), point_to_point3(quad[2]), point_to_point3(quad[3])))))
                {
                    for (j=0, p1=0; j< (int) coords().size()/3; j++, p1+=3)
                    {
                        int p2, k;


                        if (Pointd(quad[0].x(), quad[0].y(), quad[0].z()-length) == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                            for (k=0, p2=0; k< (int) coords().size()/3; k++, p2+=3)
                            {
                                if(Pointd(quad[3].x(), quad[3].y(), quad[3].z()-length) == Pointd(coords()[p2], coords()[p2+1], coords()[p2+2]))
                                {
                                    std::vector<int> quads1 = adjacent_quads(vertexMap.at(Pointd(quad[0].x(), quad[0].y(), quad[0].z()-length)));
                                    std::vector<int> quads2 = adjacent_quads(vertexMap.at(Pointd(quad[3].x(), quad[3].y(), quad[3].z()-length)));
                                    std::vector<int> shared_quads;
                                    for(int qd : quads1){
                                        for(int qd2 : quads2){
                                            if(qd==qd2)
                                                shared_quads.push_back(qd);
                                        }
                                    }

                                    cleanSharedQuads(quad, shared_quads);

                                    for (int x=0; x < (int) shared_quads.size(); x++)
                                    {
                                        for (int y=0; y < (int) shared_quads.size(); y++)
                                            if (shared_quads[x] != shared_quads[y] && checkOrthoNormals(shared_quads[x], shared_quads[y]) && checkSameVerseNormals(shared_quads[x], shared_quads[y])
                                                    && checkQuadExists(vertexMap.at(quad[3]), vertexMap.at(Pointd(quad[3].x(), quad[3].y(), quad[3].z()-length)), vertexMap.at(Pointd(quad[0].x(), quad[0].y(), quad[0].z()-length)), vertexMap.at(quad[0])) &&
                                                    checkQuadExists(vertexMap.at(quad[1]), vertexMap.at(Pointd(quad[3].x(), quad[3].y(), quad[3].z()-length)), vertexMap.at(Pointd(quad[0].x(), quad[0].y(), quad[0].z()-length)), vertexMap.at(quad[2])))
                                            {
                                                flagNormal1 = true;

                                                int indexToDelete;
                                                if (!checkIfTriangleExists(vertexMap.at(Pointd(quad[3].x(), quad[3].y(), quad[3].z()-length)), vertexMap.at(quad[3]), vertexMap.at(quad[2]), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(quad[2]));
                                                    m_tris.push_back(vertexMap.at(quad[3]));
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[3].x(), quad[3].y(), quad[3].z()-length)));
                                                }
                                                else
                                                {
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }

                                                if (!checkIfTriangleExists(vertexMap.at(Pointd(quad[0].x(), quad[0].y(), quad[0].z()-length)), vertexMap.at(quad[1]), vertexMap.at(quad[0]), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[0].x(), quad[0].y(), quad[0].z()-length)));
                                                    m_tris.push_back(vertexMap.at(quad[0]));
                                                    m_tris.push_back(vertexMap.at(quad[1]));
                                                }
                                                else
                                                {
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }


                                                m_quads_to_delete.push_back(shared_quads[x]);
                                                m_quads_to_delete.push_back(shared_quads[y]);

                                                break;
                                            }
                                        if(flagNormal1) break;
                                    }
                                }
                            }

                        if(Pointd(quad[3].x()+length, quad[3].y(), quad[3].z()) == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                            for (k=0, p2=0; k< (int) coords().size()/3; k++, p2+=3)
                            {
                                if(Pointd(quad[0].x()+length, quad[0].y(), quad[0].z()) == Pointd(coords()[p2], coords()[p2+1], coords()[p2+2]))
                                {
                                    std::vector<int> quads1 = adjacent_quads(vertexMap.at(Pointd(quad[3].x()+length, quad[3].y(), quad[3].z())));
                                    std::vector<int> quads2 = adjacent_quads(vertexMap.at(Pointd(quad[0].x()+length, quad[0].y(), quad[0].z())));
                                    std::vector<int> shared_quads;
                                    for(int qd : quads1){
                                        for(int qd2 : quads2){
                                            if(qd==qd2)
                                                shared_quads.push_back(qd);
                                        }
                                    }

                                    cleanSharedQuads(quad, shared_quads);

                                    for (int x=0; x < (int) shared_quads.size(); x++)
                                    {
                                        for (int y=0; y < (int) shared_quads.size(); y++)
                                            if (shared_quads[x] != shared_quads[y] && checkOrthoNormals(shared_quads[x], shared_quads[y]) && checkSameVerseNormals(shared_quads[x], shared_quads[y]) &&
                                                    checkQuadExists(vertexMap.at(quad[3]), vertexMap.at(Pointd(quad[3].x()+length, quad[3].y(), quad[3].z())), vertexMap.at(Pointd(quad[0].x()+length, quad[0].y(), quad[0].z())), vertexMap.at(quad[0])) &&
                                                    checkQuadExists(vertexMap.at(quad[1]), vertexMap.at(Pointd(quad[3].x()+length, quad[3].y(), quad[3].z())), vertexMap.at(Pointd(quad[0].x()+length, quad[0].y(), quad[0].z())), vertexMap.at(quad[2])))
                                            {
                                                flagNormal2 = true;

                                                int indexToDelete;
                                                if (!checkIfTriangleExists(vertexMap.at(Pointd(quad[3].x()+length, quad[3].y(), quad[3].z())), vertexMap.at(quad[3]), vertexMap.at(quad[2]), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[3].x()+length, quad[3].y(), quad[3].z())));
                                                    m_tris.push_back(vertexMap.at(quad[3]));
                                                    m_tris.push_back(vertexMap.at(quad[2]));
                                                }
                                                else
                                                {
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }

                                                if (!checkIfTriangleExists(vertexMap.at(Pointd(quad[0].x()+length, quad[0].y(), quad[0].z())), vertexMap.at(quad[1]), vertexMap.at(quad[0]), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(quad[1]));
                                                    m_tris.push_back(vertexMap.at(quad[0]));
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[0].x()+length, quad[0].y(), quad[0].z())));
                                                }
                                                else
                                                {
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }

                                                m_quads_to_delete.push_back(shared_quads[x]);
                                                m_quads_to_delete.push_back(shared_quads[y]);

                                                break;
                                            }
                                        if(flagNormal2) break;
                                    }
                                }
                            }
                    }


                    if (flagNormal1)
                    {
                        m_quads.push_back(vertexMap.at(quad[1]));
                        m_quads.push_back(vertexMap.at(quad[0]));
                        m_quads.push_back(vertexMap.at(quad[3]));
                        m_quads.push_back(vertexMap.at(quad[2]));
                        std::vector<Pointd> temp;
                        temp.push_back(quad[0]);
                        temp.push_back(quad[1]);
                        temp.push_back(quad[2]);
                        temp.push_back(quad[3]);
                        quads_used_here.push_back(temp);

                    }
                    else if (flagNormal2)
                    {


                        m_quads.push_back(vertexMap.at(quad[0]));
                        m_quads.push_back(vertexMap.at(quad[1]));
                        m_quads.push_back(vertexMap.at(quad[2]));
                        m_quads.push_back(vertexMap.at(quad[3]));
                        std::vector<Pointd> temp;
                        temp.push_back(quad[0]);
                        temp.push_back(quad[1]);
                        temp.push_back(quad[2]);
                        temp.push_back(quad[3]);
                        quads_used_here.push_back(temp);



                    }

                    flagNormal1 = false;
                    flagNormal2 = false;

                }


            }

            flag1 = false;
            flag2 = false;
            flag3 = false;
            flag4 = false;

        }
        for (std::vector<Pointd> quad_used : quads_used_here)
            quads_used.push_back(quad_used);

    }

    void smoothAxis5(double length, Polyhedron &poly){
        std::map<Pointd, int> vertexMap;
        int j, p=0, p1=0;
        std::vector<Pointd> quad;
        std::vector<std::vector<Pointd>> quads_used_here;
        bool flag1=false, flag2=false, flag3=false, flag4=false, flagNormal1=false, flagNormal2=false;
        std::list<Triangle> triangles;


        Tree tree(faces(poly).first, faces(poly).second, poly);
        tree.accelerate_distance_queries();

        quad.push_back(Pointd(0, 0, 0));
        quad.push_back(Pointd(0, 0, 0));
        quad.push_back(Pointd(0, 0, 0));
        quad.push_back(Pointd(0, 0, 0));

        for(int i = 0; i < (int) coords().size()/3; i++, p+=3)
        {
            vertexMap.insert(std::pair<Pointd, int>(Pointd(coords()[p], coords()[p+1], coords()[p+2]), i));
            /*if (Pointd(coords()[p], coords()[p+1], coords()[p+2]) < min)
                min = Pointd(coords()[p], coords()[p+1], coords()[p+2]);*/
        }

        p=0;

        for(int i = 0; i < (int) coords().size()/3; i++, p+=3)
        {
            bool flag_quad_intersection = false;
            quad[0] = Pointd(coords()[p]-length, coords()[p+1]-length, coords()[p+2]);
            quad[1] = Pointd(coords()[p]-length, coords()[p+1]-length, coords()[p+2]+length);
            quad[2] = Pointd(coords()[p], coords()[p+1], coords()[p+2]+length);
            quad[3] = Pointd(coords()[p], coords()[p+1], coords()[p+2]);


            for (std::vector<Pointd> quad_already_used : quads_used){
                int intersections = 0;
                if (quad[0] == quad_already_used[0] || quad[0] == quad_already_used[1] || quad[0] == quad_already_used[2] || quad[0] == quad_already_used[3])
                    intersections++;
                if (quad[1] == quad_already_used[0] || quad[1] == quad_already_used[1] || quad[1] == quad_already_used[2] || quad[1] == quad_already_used[3])
                    intersections++;
                if (quad[2] == quad_already_used[0] || quad[2] == quad_already_used[1] || quad[2] == quad_already_used[2] || quad[2] == quad_already_used[3])
                    intersections++;
                if (quad[3] == quad_already_used[0] || quad[3] == quad_already_used[1] || quad[3] == quad_already_used[2] || quad[3] == quad_already_used[3])
                    intersections++;
                if (intersections > 1)
                {
                    flag_quad_intersection = true;
                    break;
                }
            }


            for (j=0, p1=0; j< (int) coords().size()/3; j++, p1+=3)
            {
                if (quad[0] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag1 = true;
                if (quad[1] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag2 = true;
                if (quad[2] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag3 = true;
                if (quad[3] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag4 = true;
            }


            if (flag1 && flag2 && flag3 && flag4  && !flag_quad_intersection)
            {
                if (!(tree.do_intersect(K::Triangle_3(point_to_point3(quad[0]), point_to_point3(quad[1]), point_to_point3(quad[3])))) &&
                    !(tree.do_intersect(K::Triangle_3(point_to_point3(quad[1]), point_to_point3(quad[2]), point_to_point3(quad[3])))))
                {
                    for (j=0, p1=0; j< (int) coords().size()/3; j++, p1+=3)
                    {
                        int p2, k;


                        if (Pointd(quad[0].x(), quad[0].y()+length, quad[0].z()) == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                            for (k=0, p2=0; k< (int) coords().size()/3; k++, p2+=3)
                            {
                                if(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z()) == Pointd(coords()[p2], coords()[p2+1], coords()[p2+2]))
                                {
                                    std::vector<int> quads1 = adjacent_quads(vertexMap.at(Pointd(quad[0].x(), quad[0].y()+length, quad[0].z())));
                                    std::vector<int> quads2 = adjacent_quads(vertexMap.at(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z())));
                                    std::vector<int> shared_quads;
                                    for(int qd : quads1){
                                        for(int qd2 : quads2){
                                            if(qd==qd2)
                                                shared_quads.push_back(qd);
                                        }
                                    }

                                    cleanSharedQuads(quad, shared_quads);

                                    for (int x=0; x < (int) shared_quads.size(); x++)
                                    {
                                        for (int y=0; y < (int) shared_quads.size(); y++)
                                            if (shared_quads[x] != shared_quads[y] && checkOrthoNormals(shared_quads[x], shared_quads[y]) && checkSameVerseNormals(shared_quads[x], shared_quads[y])
                                                    && checkQuadExists(vertexMap.at(quad[0]), vertexMap.at(Pointd(quad[0].x(), quad[0].y()+length, quad[0].z())), vertexMap.at(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z())), vertexMap.at(quad[1])) &&
                                                    checkQuadExists(vertexMap.at(quad[2]), vertexMap.at(Pointd(quad[0].x(), quad[0].y()+length, quad[0].z())), vertexMap.at(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z())), vertexMap.at(quad[3])))
                                            {

                                                flagNormal1 = true;
                                                int indexToDelete;
                                                if (!checkIfTriangleExists(vertexMap.at(Pointd(quad[0].x(), quad[0].y()+length, quad[0].z())), vertexMap.at(quad[0]), vertexMap.at(quad[3]), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[0].x(), quad[0].y()+length, quad[0].z())));
                                                    m_tris.push_back(vertexMap.at(quad[0]));
                                                    m_tris.push_back(vertexMap.at(quad[3]));
                                                }
                                                else
                                                {
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }

                                                if (!checkIfTriangleExists(vertexMap.at(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z())), vertexMap.at(quad[2]), vertexMap.at(quad[1]), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z())));
                                                    m_tris.push_back(vertexMap.at(quad[2]));
                                                    m_tris.push_back(vertexMap.at(quad[1]));
                                                }
                                                else
                                                {
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }


                                                m_quads_to_delete.push_back(shared_quads[x]);
                                                m_quads_to_delete.push_back(shared_quads[y]);

                                                break;
                                            }
                                        if(flagNormal1) break;
                                    }
                                }
                            }


                        if(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z()) == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                            for (k=0, p2=0; k< (int) coords().size()/3; k++, p2+=3)
                            {
                                if(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z()) == Pointd(coords()[p2], coords()[p2+1], coords()[p2+2]))
                                {
                                    std::vector<int> quads1 = adjacent_quads(vertexMap.at(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z())));
                                    std::vector<int> quads2 = adjacent_quads(vertexMap.at(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z())));
                                    std::vector<int> shared_quads;
                                    for(int qd : quads1){
                                        for(int qd2 : quads2){
                                            if(qd==qd2)
                                                shared_quads.push_back(qd);
                                        }
                                    }


                                    cleanSharedQuads(quad, shared_quads);



                                    for (int x=0; x < (int) shared_quads.size(); x++)
                                    {
                                        for (int y=0; y < (int) shared_quads.size(); y++)
                                            if (shared_quads[x] != shared_quads[y] && checkOrthoNormals(shared_quads[x], shared_quads[y]) && checkSameVerseNormals(shared_quads[x], shared_quads[y])
                                                    && checkQuadExists(vertexMap.at(quad[3]), vertexMap.at(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z())), vertexMap.at(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z())), vertexMap.at(quad[2])) &&
                                                    checkQuadExists(vertexMap.at(quad[0]), vertexMap.at(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z())), vertexMap.at(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z())), vertexMap.at(quad[1])))
                                            {
                                                int indexToDelete;
                                                flagNormal2 = true;

                                                if(!checkIfTriangleExists( vertexMap.at(quad[3]), vertexMap.at(quad[0]), vertexMap.at(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z())), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(quad[3]));
                                                    m_tris.push_back(vertexMap.at(quad[0]));
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z())));
                                                }
                                                else{
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }
                                                if(!checkIfTriangleExists(vertexMap.at(quad[2]), vertexMap.at(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z())) , vertexMap.at(quad[1]), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(quad[2]));
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z())));
                                                    m_tris.push_back(vertexMap.at(quad[1]));
                                                }
                                                else{
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }
                                                m_quads_to_delete.push_back(shared_quads[x]);
                                                m_quads_to_delete.push_back(shared_quads[y]);

                                                break;
                                            }
                                        if(flagNormal2) break;
                                    }
                                }
                            }
                    }

                    if (flagNormal1)
                    {
                        m_quads.push_back(vertexMap.at(quad[2]));
                        m_quads.push_back(vertexMap.at(quad[3]));
                        m_quads.push_back(vertexMap.at(quad[0]));
                        m_quads.push_back(vertexMap.at(quad[1]));

                        std::vector<Pointd> temp;
                        temp.push_back(quad[2]);
                        temp.push_back(quad[3]);
                        temp.push_back(quad[0]);
                        temp.push_back(quad[1]);
                        quads_used_here.push_back(temp);
                    }
                    else if (flagNormal2)
                    {
                        m_quads.push_back(vertexMap.at(quad[3]));
                        m_quads.push_back(vertexMap.at(quad[2]));
                        m_quads.push_back(vertexMap.at(quad[1]));
                        m_quads.push_back(vertexMap.at(quad[0]));

                        std::vector<Pointd> temp;
                        temp.push_back(quad[3]);
                        temp.push_back(quad[2]);
                        temp.push_back(quad[1]);
                        temp.push_back(quad[0]);
                        quads_used_here.push_back(temp);

                    }

                    flagNormal1 = false;
                    flagNormal2 = false;

                }


            }

            flag1 = false;
            flag2 = false;
            flag3 = false;
            flag4 = false;

        }
        for (std::vector<Pointd> quad_used : quads_used_here)
            quads_used.push_back(quad_used);

    }

    void smoothAxis6(double length, Polyhedron &poly){
        std::map<Pointd, int> vertexMap;
        int j, p=0, p1=0;
        std::vector<Pointd> quad;
        std::vector<std::vector<Pointd>> quads_used_here;
        bool flag1=false, flag2=false, flag3=false, flag4=false, flagNormal1=false, flagNormal2=false;
        std::list<Triangle> triangles;


        Tree tree(faces(poly).first, faces(poly).second, poly);
        tree.accelerate_distance_queries();

        quad.push_back(Pointd(0, 0, 0));
        quad.push_back(Pointd(0, 0, 0));
        quad.push_back(Pointd(0, 0, 0));
        quad.push_back(Pointd(0, 0, 0));

        for(int i = 0; i < (int) coords().size()/3; i++, p+=3)
        {
            vertexMap.insert(std::pair<Pointd, int>(Pointd(coords()[p], coords()[p+1], coords()[p+2]), i));
            /*if (Pointd(coords()[p], coords()[p+1], coords()[p+2]) < min)
                min = Pointd(coords()[p], coords()[p+1], coords()[p+2]);*/
        }

        p=0;

        for(int i = 0; i < (int) coords().size()/3; i++, p+=3)
        {
            bool flag_quad_intersection = false;
            quad[0] = Pointd(coords()[p]+length, coords()[p+1]-length, coords()[p+2]);
            quad[1] = Pointd(coords()[p]+length, coords()[p+1]-length, coords()[p+2]-length);
            quad[2] = Pointd(coords()[p], coords()[p+1], coords()[p+2]-length);
            quad[3] = Pointd(coords()[p], coords()[p+1], coords()[p+2]);

            for (std::vector<Pointd> quad_already_used : quads_used){
                int intersections = 0;
                if (quad[0] == quad_already_used[0] || quad[0] == quad_already_used[1] || quad[0] == quad_already_used[2] || quad[0] == quad_already_used[3])
                    intersections++;
                if (quad[1] == quad_already_used[0] || quad[1] == quad_already_used[1] || quad[1] == quad_already_used[2] || quad[1] == quad_already_used[3])
                    intersections++;
                if (quad[2] == quad_already_used[0] || quad[2] == quad_already_used[1] || quad[2] == quad_already_used[2] || quad[2] == quad_already_used[3])
                    intersections++;
                if (quad[3] == quad_already_used[0] || quad[3] == quad_already_used[1] || quad[3] == quad_already_used[2] || quad[3] == quad_already_used[3])
                    intersections++;
                if (intersections > 1)
                {
                    flag_quad_intersection = true;
                    break;
                }
            }

            for (j=0, p1=0; j< (int) coords().size()/3; j++, p1+=3)
            {
                if (quad[0] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag1 = true;
                if (quad[1] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag2 = true;
                if (quad[2] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag3 = true;
                if (quad[3] == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                    flag4 = true;
            }


            if (flag1 && flag2 && flag3 && flag4 && !flag_quad_intersection)
            {
                if (!(tree.do_intersect(K::Triangle_3(point_to_point3(quad[0]), point_to_point3(quad[1]), point_to_point3(quad[3])))) &&
                    !(tree.do_intersect(K::Triangle_3(point_to_point3(quad[1]), point_to_point3(quad[2]), point_to_point3(quad[3])))))
                {
                    for (j=0, p1=0; j< (int) coords().size()/3; j++, p1+=3)
                    {
                        int p2, k;


                        if (Pointd(quad[0].x(), quad[0].y()+length, quad[0].z()) == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                            for (k=0, p2=0; k< (int) coords().size()/3; k++, p2+=3)
                            {
                                if(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z()) == Pointd(coords()[p2], coords()[p2+1], coords()[p2+2]))
                                {
                                    std::vector<int> quads1 = adjacent_quads(vertexMap.at(Pointd(quad[0].x(), quad[0].y()+length, quad[0].z())));
                                    std::vector<int> quads2 = adjacent_quads(vertexMap.at(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z())));
                                    std::vector<int> shared_quads;
                                    for(int qd : quads1){
                                        for(int qd2 : quads2){
                                            if(qd==qd2)
                                                shared_quads.push_back(qd);
                                        }
                                    }

                                    cleanSharedQuads(quad, shared_quads);

                                    for (int x=0; x < (int) shared_quads.size(); x++)
                                    {
                                        for (int y=0; y < (int) shared_quads.size(); y++)
                                            if (shared_quads[x] != shared_quads[y] && checkOrthoNormals(shared_quads[x], shared_quads[y]) && checkSameVerseNormals(shared_quads[x], shared_quads[y])
                                                    && checkQuadExists(vertexMap.at(quad[0]), vertexMap.at(Pointd(quad[0].x(), quad[0].y()+length, quad[0].z())), vertexMap.at(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z())), vertexMap.at(quad[1])) &&
                                                    checkQuadExists(vertexMap.at(quad[2]), vertexMap.at(Pointd(quad[0].x(), quad[0].y()+length, quad[0].z())), vertexMap.at(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z())), vertexMap.at(quad[3])))
                                            {
                                                flagNormal1 = true;

                                                int indexToDelete;
                                                if (!checkIfTriangleExists(vertexMap.at(Pointd(quad[0].x(), quad[0].y()+length, quad[0].z())), vertexMap.at(quad[3]), vertexMap.at(quad[0]), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[0].x(), quad[0].y()+length, quad[0].z())));
                                                    m_tris.push_back(vertexMap.at(quad[0]));
                                                    m_tris.push_back(vertexMap.at(quad[3]));

                                                }
                                                else
                                                {
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }

                                                if (!checkIfTriangleExists(vertexMap.at(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z())), vertexMap.at(quad[1]), vertexMap.at(quad[2]), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[1].x(), quad[1].y()+length, quad[1].z())));
                                                    m_tris.push_back(vertexMap.at(quad[2]));
                                                    m_tris.push_back(vertexMap.at(quad[1]));
                                                }
                                                else
                                                {
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }


                                                m_quads_to_delete.push_back(shared_quads[x]);
                                                m_quads_to_delete.push_back(shared_quads[y]);

                                                break;
                                            }
                                        if(flagNormal1) break;
                                    }
                                }
                            }


                        if(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z()) == Pointd(coords()[p1], coords()[p1+1], coords()[p1+2]))
                            for (k=0, p2=0; k< (int) coords().size()/3; k++, p2+=3)
                            {
                                if(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z()) == Pointd(coords()[p2], coords()[p2+1], coords()[p2+2]))
                                {
                                    std::vector<int> quads1 = adjacent_quads(vertexMap.at(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z())));
                                    std::vector<int> quads2 = adjacent_quads(vertexMap.at(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z())));
                                    std::vector<int> shared_quads;
                                    for(int qd : quads1){
                                        for(int qd2 : quads2){
                                            if(qd==qd2)
                                                shared_quads.push_back(qd);
                                        }
                                    }

                                    cleanSharedQuads(quad, shared_quads);

                                    for (int x=0; x < (int) shared_quads.size(); x++)
                                    {
                                        for (int y=0; y < (int) shared_quads.size(); y++)
                                            if (shared_quads[x] != shared_quads[y] && checkOrthoNormals(shared_quads[x], shared_quads[y]) && checkSameVerseNormals(shared_quads[x], shared_quads[y])
                                                    && checkQuadExists(vertexMap.at(quad[3]), vertexMap.at(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z())), vertexMap.at(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z())), vertexMap.at(quad[2])) &&
                                                    checkQuadExists(vertexMap.at(quad[0]), vertexMap.at(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z())), vertexMap.at(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z())), vertexMap.at(quad[1])))
                                            {
                                                flagNormal2 = true;

                                                int indexToDelete;
                                                if (!checkIfTriangleExists(vertexMap.at(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z())), vertexMap.at(quad[3]), vertexMap.at(quad[0]), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(quad[3]));
                                                    m_tris.push_back(vertexMap.at(quad[0]));
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[3].x(), quad[3].y()-length, quad[3].z())));
                                                }
                                                else
                                                {
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }

                                                if (!checkIfTriangleExists(vertexMap.at(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z())), vertexMap.at(quad[1]), vertexMap.at(quad[2]), indexToDelete))
                                                {
                                                    m_tris.push_back(vertexMap.at(quad[2]));
                                                    m_tris.push_back(vertexMap.at(Pointd(quad[2].x(), quad[2].y()-length, quad[2].z())));
                                                    m_tris.push_back(vertexMap.at(quad[1]));
                                                }
                                                else
                                                {
                                                    m_tris_to_delete.push_back(indexToDelete);
                                                }



                                                m_quads_to_delete.push_back(shared_quads[x]);
                                                m_quads_to_delete.push_back(shared_quads[y]);

                                                break;
                                            }
                                        if(flagNormal2) break;
                                    }
                                }
                            }
                    }


                    if (flagNormal1)
                    {
                        m_quads.push_back(vertexMap.at(quad[0]));
                        m_quads.push_back(vertexMap.at(quad[1]));
                        m_quads.push_back(vertexMap.at(quad[2]));
                        m_quads.push_back(vertexMap.at(quad[3]));

                        std::vector<Pointd> temp;
                        temp.push_back(quad[0]);
                        temp.push_back(quad[1]);
                        temp.push_back(quad[2]);
                        temp.push_back(quad[3]);
                        quads_used_here.push_back(temp);

                    }
                    else if (flagNormal2)
                    {
                        m_quads.push_back(vertexMap.at(quad[1]));
                        m_quads.push_back(vertexMap.at(quad[0]));
                        m_quads.push_back(vertexMap.at(quad[3]));
                        m_quads.push_back(vertexMap.at(quad[2]));
                        std::vector<Pointd> temp;
                        temp.push_back(quad[0]);
                        temp.push_back(quad[1]);
                        temp.push_back(quad[2]);
                        temp.push_back(quad[3]);
                        quads_used_here.push_back(temp);

                    }

                    flagNormal1 = false;
                    flagNormal2 = false;

                }


            }

            flag1 = false;
            flag2 = false;
            flag3 = false;
            flag4 = false;

        }

        for (std::vector<Pointd> quad_used : quads_used_here)
            quads_used.push_back(quad_used);

    }



    bool checkIfTriangleExists(int a, int b, int c, int &index)
    {

        for (int i=0, p=0; i< (int) tris().size()/3; i++, p+=3)
        {
            if (tris()[p] == a || tris()[p] == b || tris()[p] == c)
                if (tris()[p+1] == a || tris()[p+1] == b || tris()[p+1] == c)
                    if (tris()[p+2] == a || tris()[p+2] == b || tris()[p+2] == c)
                    {
                        index = i;
                        return true;
                    }
        }

        return false;
    }

    bool checkQuadExists (int a, int b, int c, int d)
    {

        for (int i=0, p=0; i< (int) quads().size()/4; i++, p+=4)
        {
            if (quads()[p] == a || quads()[p] == b || quads()[p] == c || quads()[p] == d)
                if (quads()[p+1] == a || quads()[p+1] == b || quads()[p+1] == c || quads()[p+1] == d)
                    if (quads()[p+2] == a || quads()[p+2] == b || quads()[p+2] == c || quads()[p+2] == d)
                        if (quads()[p+3] == a || quads()[p+3] == b || quads()[p+3] == c || quads()[p+3] == d)
                            return true;

        }

        return false;
    }

    bool checkOrthoNormals(int quad1, int quad2){

        std::vector<Pointd> first;
        first.push_back(Pointd(m_coords[m_quads[quad1*4]*3], m_coords[m_quads[quad1*4]*3+1], m_coords[m_quads[quad1*4]*3+2]));
        first.push_back(Pointd(m_coords[m_quads[quad1*4+1]*3], m_coords[m_quads[quad1*4+1]*3+1], m_coords[m_quads[quad1*4+1]*3+2]));
        first.push_back(Pointd(m_coords[m_quads[quad1*4+2]*3], m_coords[m_quads[quad1*4+2]*3+1], m_coords[m_quads[quad1*4+2]*3+2]));
        first.push_back(Pointd(m_coords[m_quads[quad1*4+3]*3], m_coords[m_quads[quad1*4+3]*3+1], m_coords[m_quads[quad1*4+3]*3+2]));



        std::vector<Pointd> second;
        second.push_back(Pointd(m_coords[m_quads[quad2*4]*3], m_coords[m_quads[quad2*4]*3+1], m_coords[m_quads[quad2*4]*3+2]));
        second.push_back(Pointd(m_coords[m_quads[quad2*4+1]*3], m_coords[m_quads[quad2*4+1]*3+1], m_coords[m_quads[quad2*4+1]*3+2]));
        second.push_back(Pointd(m_coords[m_quads[quad2*4+2]*3], m_coords[m_quads[quad2*4+2]*3+1], m_coords[m_quads[quad2*4+2]*3+2]));
        second.push_back(Pointd(m_coords[m_quads[quad2*4+3]*3], m_coords[m_quads[quad2*4+3]*3+1], m_coords[m_quads[quad2*4+3]*3+2]));

        Pointd normal1 = (first[1] - first[0]).cross((first[3]-first[0]));
        Pointd normal2 = (second[1] - second[0]).cross((second[3]-second[0]));
        normal1.normalize();
        normal2.normalize();
        //qDebug()<<normal1.dot(normal2);
        return normal1.dot(normal2) == 0;
        //return true;

    }

    bool checkSameVerseNormals(int quad1, int quad2){

        std::vector<Pointd> first;
        first.push_back(Pointd(m_coords[m_quads[quad1*4]*3], m_coords[m_quads[quad1*4]*3+1], m_coords[m_quads[quad1*4]*3+2]));
        first.push_back(Pointd(m_coords[m_quads[quad1*4+1]*3], m_coords[m_quads[quad1*4+1]*3+1], m_coords[m_quads[quad1*4+1]*3+2]));
        first.push_back(Pointd(m_coords[m_quads[quad1*4+2]*3], m_coords[m_quads[quad1*4+2]*3+1], m_coords[m_quads[quad1*4+2]*3+2]));
        first.push_back(Pointd(m_coords[m_quads[quad1*4+3]*3], m_coords[m_quads[quad1*4+3]*3+1], m_coords[m_quads[quad1*4+3]*3+2]));

        std::vector<Pointd> second;
        second.push_back(Pointd(m_coords[m_quads[quad2*4]*3], m_coords[m_quads[quad2*4]*3+1], m_coords[m_quads[quad2*4]*3+2]));
        second.push_back(Pointd(m_coords[m_quads[quad2*4+1]*3], m_coords[m_quads[quad2*4+1]*3+1], m_coords[m_quads[quad2*4+1]*3+2]));
        second.push_back(Pointd(m_coords[m_quads[quad2*4+2]*3], m_coords[m_quads[quad2*4+2]*3+1], m_coords[m_quads[quad2*4+2]*3+2]));
        second.push_back(Pointd(m_coords[m_quads[quad2*4+3]*3], m_coords[m_quads[quad2*4+3]*3+1], m_coords[m_quads[quad2*4+3]*3+2]));

        Pointd normal1 = (first[1] - first[0]).cross((first[3]-first[0]));
        Pointd normal2 = (second[1] - second[0]).cross((second[3]-second[0]));


        std::vector<Pointd> sharedVertices;

        std::vector<int> indicesFound;

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                if (first[i] == second[j])
                {
                    sharedVertices.push_back(first[i]);
                    indicesFound.push_back(i);
                }
            }

        if (indicesFound[0] == 0 && indicesFound[1] == 3)
        {
            Pointd temp;
            temp = sharedVertices[0];
            sharedVertices[0] = sharedVertices[1];
            sharedVertices[1] = temp;
        }

        // sharedVertices[0] poi sharedVertices[1] nel primo quad
        // viceversa

        Pointd crossNormal = normal1.cross(normal2);

        Pointd diffVertices = sharedVertices[0] - sharedVertices[1];

        return crossNormal.dot(diffVertices) < 0;
    }

    void cleanSharedQuads(std::vector<Pointd> quadWedge, std::vector<int> &sharedQuads){

        std::vector<int> indicesToDelete;

        for (int i=0 ; i< (int) sharedQuads.size(); i++)
        {
            int counter = 0;
            for (int j=0; j<4; j++) if (quadWedge[j] == (Pointd(m_coords[m_quads[sharedQuads[i]*4]*3], m_coords[m_quads[sharedQuads[i]*4]*3+1], m_coords[m_quads[sharedQuads[i]*4]*3+2]))) counter++;
            for (int j=0; j<4; j++) if (quadWedge[j] == (Pointd(m_coords[m_quads[sharedQuads[i]*4+1]*3], m_coords[m_quads[sharedQuads[i]*4+1]*3+1], m_coords[m_quads[sharedQuads[i]*4+1]*3+2]))) counter++;
            for (int j=0; j<4; j++) if (quadWedge[j] == (Pointd(m_coords[m_quads[sharedQuads[i]*4+2]*3], m_coords[m_quads[sharedQuads[i]*4+2]*3+1], m_coords[m_quads[sharedQuads[i]*4+2]*3+2]))) counter++;
            for (int j=0; j<4; j++) if (quadWedge[j] == (Pointd(m_coords[m_quads[sharedQuads[i]*4+3]*3], m_coords[m_quads[sharedQuads[i]*4+3]*3+1], m_coords[m_quads[sharedQuads[i]*4+3]*3+2]))) counter++;

            if (counter==0) indicesToDelete.push_back(i);
        }

        std::sort(indicesToDelete.begin(), indicesToDelete.end(), std::greater<int>());

        for (int i : indicesToDelete)
            sharedQuads.erase(sharedQuads.begin()+(i));

    }

    void cleanTris(){

        std::sort(m_tris_to_delete.begin(), m_tris_to_delete.end(), std::greater<int>());

        for (int i : m_tris_to_delete)
        {
            m_tris.erase(m_tris.begin()+(i*3), m_tris.begin()+(i*3)+3);
        }

    }

    void cleanQuads(){

        std::sort(m_quads_to_delete.begin(), m_quads_to_delete.end(), std::greater<int>());

        for (int i : m_quads_to_delete)
        {
            m_quads.erase(m_quads.begin()+(i*4), m_quads.begin()+(i*4)+4);
        }
    }

    static bool comp(const std::pair<int, int>&i, const std::pair<int, int>&j)
    {
        return i.second > j.second;
    }


    void cleanTrisOnQuads(){

        std::vector<std::pair<int, int>> indicesTrisQuads;

        for (int i = 0, p = 0; i< (int) m_tris.size()/3; i++, p+=3)
        {
            for (int iq = 0, pq = 0; iq< (int) m_quads.size()/4; iq++, pq+=4)
            {
                int counter = 0;
                if (m_tris[p] == m_quads[pq] || m_tris[p] == m_quads[pq+1] || m_tris[p] == m_quads[pq+2] || m_tris[p] == m_quads[pq+3])
                    counter++;
                if (m_tris[p+1] == m_quads[pq] || m_tris[p+1] == m_quads[pq+1] || m_tris[p+1] == m_quads[pq+2] || m_tris[p+1] == m_quads[pq+3])
                    counter++;
                if (m_tris[p+2] == m_quads[pq] || m_tris[p+2] == m_quads[pq+1] || m_tris[p+2] == m_quads[pq+2] || m_tris[p+2] == m_quads[pq+3])
                    counter++;
                if (counter==3)
                    indicesTrisQuads.push_back(std::pair<int, int>(p,pq));
            }
        }

        std::sort(indicesTrisQuads.begin(), indicesTrisQuads.end(), comp);

        for (std::pair<int, int> index : indicesTrisQuads)
        {
            int indexVertexToKeep, indexVertexToDelete;
            for (int i=0; i<4; i++)
            {
                if (!(m_quads[index.second+i] == m_tris[index.first] || m_quads[index.second+i] == m_tris[index.first+1] || m_quads[index.second+i] == m_tris[index.first+2] ))
                    indexVertexToKeep = i;
            }


            if (indexVertexToKeep >= 2)
                indexVertexToDelete = indexVertexToKeep - 2;
            else
                indexVertexToDelete = indexVertexToKeep + 2;

            for (int i=0, p=0; i<4; i++)
            {
                if (i != indexVertexToDelete)
                {
                    m_tris[index.first+p] = m_quads[index.second+i];
                    p++;
                }
            }

            m_quads.erase(m_quads.begin()+index.second, m_quads.begin()+index.second+4);

        }



    }


    std::vector<double> subdivide(std::vector<std::vector<Pointd>> polyhedra, double length, std::vector<int> &hexes){
        std::vector<double> coords;

        int i=0;
        std::map<Pointd, int> mymap;

        for(std::vector<Pointd> polyhedron : polyhedra){

            for(int x = 0; x<=(polyhedron[1].x() - polyhedron[0].x()) / length; x++){
                for(int y = 0; y<=(polyhedron[4].y() - polyhedron[0].y()) / length; y++){
                    for(int z = 0; z<=(polyhedron[3].z() - polyhedron[0].z()) / length; z++){


                        if(mymap.find(Pointd(polyhedron[0].x() + length * x, polyhedron[0].y() + length * y, polyhedron[0].z() + length * z )) == mymap.end()){
                            mymap.insert(std::pair<Pointd, int>(Pointd(polyhedron[0].x() + length * x, polyhedron[0].y() + length * y, polyhedron[0].z() + length * z ), i++));
                            coords.push_back(polyhedron[0].x() + length * x);
                            coords.push_back(polyhedron[0].y() + length * y);
                            coords.push_back(polyhedron[0].z() + length * z);
                        }
                    }
                }
            }
        }


        for(auto mapElement : mymap){
            if(mymap.find(mapElement.first + Pointd(length, 0 ,0)) != mymap.end() && mymap.find(mapElement.first + Pointd(length, 0 ,length) ) != mymap.end() && mymap.find(mapElement.first + Pointd(0, 0 ,length)) != mymap.end() && mymap.find(mapElement.first + Pointd(0, length ,0)) != mymap.end() && mymap.find(mapElement.first + Pointd(length, length ,0)) != mymap.end() && mymap.find(mapElement.first + Pointd(length, length ,0)) != mymap.end() && mymap.find(mapElement.first + Pointd(length, length ,length)) != mymap.end() && mymap.find(mapElement.first + Pointd(0, length ,length)) != mymap.end()){
                hexes.push_back(mapElement.second);
                hexes.push_back(mymap.at(mapElement.first + Pointd(length, 0 ,0)));
                hexes.push_back(mymap.at(mapElement.first + Pointd(length, 0 ,length)));
                hexes.push_back(mymap.at(mapElement.first + Pointd(0, 0 ,length)));
                hexes.push_back(mymap.at(mapElement.first + Pointd(0, length ,0)));
                hexes.push_back(mymap.at(mapElement.first + Pointd(length, length ,0)));
                hexes.push_back(mymap.at(mapElement.first + Pointd(length, length ,length)));
                hexes.push_back(mymap.at(mapElement.first + Pointd(0, length ,length)));
            }
        }


        return coords;
    }
    
    void clear(){
        m_coords.clear();
        m_tris.clear();
        m_quads.clear();
        m_tets.clear();
        m_hexes.clear();
        m_vtx2tri.clear();
        m_vtx2quad.clear();
        m_vtx2tet.clear();
        m_vtx2hex.clear();
        m_vtx_on_surface.clear();
    }

    void set( const std::vector<real> &coords, const std::vector<int> &tris, const std::vector<int> &quads, const std::vector<int> &tets, const std::vector<int> &hexes ){
        clear();
        m_coords = coords;
        m_tris = tris;
        m_quads = quads;
        m_tets = tets;
        m_hexes = hexes;
        build_adjacency();
    }
    
    void construct_surface(){
        std::vector<double> coords = m_coords;
        m_tris.clear();
        m_quads.clear();
        build_surface( coords, m_tris, m_quads, m_tets, m_hexes );
        build_adjacency();

    }
    
    bool load( const char *filename ){
        bool val;
        clear();
        std::vector<double> coords;
        val = load_mesh( filename, coords, m_tris, m_quads, m_tets, m_hexes );
        m_coords = coords;
        build_adjacency();
        return val;
    }
    
    bool save( const char *filename ){
        std::vector<double> coords = m_coords;
        return save_mesh( filename, coords, m_tris, m_quads, m_tets, m_hexes );
    }

    inline int num_vertices() const {
        return m_coords.size()/3;
    }
    
    inline int num_tris() const {
        return m_tris.size()/3;
    }
    
    inline int num_quads() const {
        return m_quads.size()/4;
    }
    
    inline int num_tets() const {
        return m_tets.size()/4;
    }
    
    inline int num_hexes() const {
        return m_hexes.size()/8;
    }
    
    std::vector<real> minimum() const {
        std::vector<real> minim =vertex(0);
        for( int i=1; i<m_coords.size()/3; i++ ){
            minim = minim.minimum( vertex(i) );
        }
        return minim;
    }
    
    std::vector<real> maximum() const {
        std::vector<real> maxim = vertex(0);
        for( int i=1; i<m_coords.size()/3; i++ ){
            maxim = maxim.maximum( vertex(i) );
        }
        return maxim;
    }

    
    std::vector<real> &coords(){
        return m_coords;
    }
    
    std::vector<int> &tris(){
        return m_tris;
    }
    
    std::vector<int> &quads(){
        return m_quads;
    }
    
    std::vector<int> &tets(){
        return m_tets;
    }
    
    std::vector<int> &hexes(){
        return m_hexes;
    }
    
    inline void set_vertex( int id, const real x, const real y, const real z ){
        m_coords[id*3+0] = x;
        m_coords[id*3+1] = y;
        m_coords[id*3+2] = z;
    }
    
    inline void set_vertex( int id, const std::vector<real> &pos ){
        m_coords[id*3+0] = pos.x();
        m_coords[id*3+1] = pos.y();
        m_coords[id*3+2] = pos.z();
    }
    
    inline std::vector<real> vertex( int id ) const {
        return std::vector<real>( m_coords[id*3+0], m_coords[id*3+1], m_coords[id*3+2] );
    }
    
    inline int tri_vertex_id( int tri_id, int vid ) const {
        return m_tris[tri_id*3+vid];
    }
    
    inline std::vector<real> tri_vertex( int tri_id, int vid ) const {
        return vertex( tri_vertex_id(tri_id,vid) );
    }
    
    inline std::vector<real> tri_centroid( int tri_id ) const {
        return (tri_vertex(tri_id,0) + tri_vertex(tri_id,1) + tri_vertex(tri_id,2))/real(3.0);
    }
    
    inline std::vector<real> tri_normal( int tri_id ) const {
        std::vector<real> a=tri_vertex(tri_id,0), b=tri_vertex(tri_id,1), c=tri_vertex(tri_id,2);
        return (b-a).cross(c-a)*0.5;
    }
    
    inline int quad_vertex_id( int quad_id, int vid ) const {
        return m_quads[quad_id*4+vid];
    }
    
    inline std::vector<real> quad_vertex( int quad_id, int vid ) const {
        return vertex( quad_vertex_id(quad_id,vid) );
    }
    
    inline std::vector<real> quad_centroid( int quad_id ) const {
        return (quad_vertex(quad_id,0) + quad_vertex(quad_id,1) + quad_vertex(quad_id,2) + quad_vertex(quad_id,3))/real(4.0);
    }
    
    inline std::vector<real> quad_normal( int quad_id ) const {
        std::vector<real> a=quad_vertex(quad_id,0), b=quad_vertex(quad_id,1), c=quad_vertex(quad_id,2), d=quad_vertex(quad_id,3);
        std::vector<real> n = ((b-a).cross(c-a) + (c-a).cross(d-a))/real(4.0);
        n.normalize();
        return n;
    }
    
    inline int tet_vertex_id( int tet_id, int vid ) const {
        return m_tets[tet_id*4+vid];
    }
    
    inline std::vector<real> tet_vertex( int tet_id, int vid ) const {
        return vertex( tet_vertex_id(tet_id,vid) );
    }
    
    inline std::vector<real> tet_centroid( int tet_id ) const {
        return (tet_vertex(tet_id,0) + tet_vertex(tet_id,1) + tet_vertex(tet_id,2) + tet_vertex(tet_id,3))/real(4.0);
    }
    
    inline int hex_vertex_id( int hex_id, int vid ) const {
        return m_hexes[hex_id*8+vid];
    }
    
    inline std::vector<real> hex_vertex( int hex_id, int vid ) const {
        return vertex( hex_vertex_id(hex_id,vid) );
    }
    
    inline std::vector<real> hex_centroid( int hex_id ) const {
        return (hex_vertex(hex_id,0) + hex_vertex(hex_id,1) + hex_vertex(hex_id,2) + hex_vertex(hex_id,3) + hex_vertex(hex_id,4) + hex_vertex(hex_id,5) + hex_vertex(hex_id,6) + hex_vertex(hex_id,7 ) )*0.125;
    }
    
    inline std::vector<int> adjacent_tris( int vid ) const {
        return m_vtx2tri[vid];
    }
    
    inline std::vector<int> adjacent_quads( int vid ) const {
        return m_vtx2quad[vid];
    }
    
    inline std::vector<int> adjacent_tets( int vid ) const {
        return m_vtx2tet[vid];
    }
    
    inline std::vector<int> adjacent_hexes( int vid ) const {
        return m_vtx2hex[vid];
    }
    
    inline bool is_surface_vertex( int vid ) const {
        return m_vtx_on_surface[vid];
    }
    
    mesh<real> get_volume(){
        std::vector<int> tris, quads;
        return mesh<real>( m_coords, tris, quads, m_tets, m_hexes );
    }
    
    mesh<real> get_surface(){
        std::vector<int> tris, quads, tets, hexes;
        std::vector<double> coords = m_coords;
        //if (print_debug_info) std::cout << "building surface..." << std::endl;
        build_surface( coords, tris, quads, m_tets, m_hexes );
        return mesh<real>( coords, tris, quads, tets, hexes );
    }

    void cleanCoords(){

        int num_deleted = 0;

        for (int i=0, p=0; i < (int) m_coords.size()/3; i++, p+=3)
        {
            if (!m_vtx_on_surface[i+num_deleted])
            {

                m_coords.erase(m_coords.begin() + p);
                m_coords.erase(m_coords.begin() + p);
                m_coords.erase(m_coords.begin() + p);
                p-=3;
                i--;

                num_deleted++;

                for (int k = 0; k < (int) m_quads.size(); k++)
                {
                    if (m_quads[k] > i) m_quads[k]--;
                }


            }


        }
        m_vtx2quad.clear();
        build_adjacency();

    }



    /*
    inline real hex_quality( const int hid ) const {
        int vid;
        double p[8][3];
        for( int i=0; i<8; i++ ){
            vid = hex_vertex_id( hid, i );
            std::vector<double> pos = vertex( vid );
            p[i][0] = pos[0];
            p[i][1] = pos[1];
            p[i][2] = pos[2];
        }
        return v_hex_scaled_jacobian( 8, p );
    }*/
    /*
    inline real vertex_quality( const int vid ) const {
        std::vector<int> adjacent_hexes(vid);
        if( adjacent_hexes.size() == 0 )
            throw "shitfit!";
        
        real minq = hex_quality( adjacent_hexes[0] );
        for( int i=1; i<adjacent_hexes.size(); i++ ){
            minq = std::min( minq, hex_quality( adjacent_hexes[i] ) );
        }

        std::cout << minq << std::endl;
        return minq;
    }*/

};


#endif
