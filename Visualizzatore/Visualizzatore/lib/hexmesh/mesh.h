#ifndef MESH_H
#define MESH_H

 
//#include"vec3.h"
#include"load_save.h"
#include "lib/common/point.h"
#include <map>


//using namespace geom;


template< typename real >
class mesh {
private:
    std::vector<real>               m_coords;
    std::vector<int>                m_tris;
    std::vector<int>                m_quads;
    std::vector<int>                m_tets;
    std::vector<int>                m_hexes;

	std::vector<int>				m_anchors;
    
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
        /*if(print_debug_info)
            std::cout << "adjacency: hexes..." << std::endl;*/
		for (int i = 0; i < num_vertices(); i++)
		{
			m_vtx2hex[i].reserve(4);
		}
        /*if(print_debug_info)
            std::cout << "adjacency: hexes... (2)" << std::endl;*/
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
        std::vector<int> empty;
        std::vector<int> hexes;
        std::vector<double> coords = subdivide(polyhedra, length, hexes);
        set(coords, empty, empty, empty, hexes);
    }

    std::vector<double> subdivide(std::vector<std::vector<Pointd>> polyhedra, double length, std::vector<int> &hexes){
        std::vector<double> coords;

        int i=1;
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
        return mesh<real>( m_coords, tris, quads, tets, hexes );
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
