#include<set>
#include<algorithm>
#include<vector>
#include <iostream>

#include"load_save.h"

class face {
public:
    int vtx[4];
    int sort_vtx[4];
    
    face( const int a, const int b, const int c, const int d=-1 ){
        vtx[0]=sort_vtx[0]=a;
        vtx[1]=sort_vtx[1]=b;
        vtx[2]=sort_vtx[2]=c;
        vtx[3]=sort_vtx[3]=d;
        std::sort( sort_vtx, sort_vtx+4 );
    }
    
    inline bool operator<( const face &in ) const {
        for( int i=0; i<4; i++ ){
            if( sort_vtx[i] < in.sort_vtx[i] ) return true;
            if( sort_vtx[i] > in.sort_vtx[i] ) return false;
        }
        return false;
    }
};

void build_surface( std::vector<double> &coords, std::vector<int> &tris, std::vector<int> &quads, std::vector<int> &tets, std::vector<int> &hexes ){
    std::set< face > faces;
    const int tet_faces[][3] = {
        { 0, 2, 1 },
        { 0, 1, 3 },
        { 0, 3, 2 },
        { 1, 2, 3 },
    };
    const int hex_faces[][4] = {
        { 0, 3, 2, 1 },
        { 4, 5, 6, 7 },
        { 0, 4, 7, 3 },
        { 1, 2, 6, 5 },
        { 0, 1, 5, 4 },
        { 2, 3, 7, 6 },
    };
    for( int i=0; i<tets.size(); i+=4 ){
        for( int j=0; j<4; j++ ){
            face tmp( tets[i+tet_faces[j][0]], tets[i+tet_faces[j][1]], tets[i+tet_faces[j][2]] );
            if( faces.find( tmp ) != faces.end() ){
                faces.erase( tmp );
            } else {
                faces.insert( tmp );
            }
        }
    }
    for( int i=0; i<hexes.size(); i+=8 ){
        for( int j=0; j<6; j++ ){
            face tmp( hexes[i+hex_faces[j][0]], hexes[i+hex_faces[j][1]], hexes[i+hex_faces[j][2]], hexes[i+hex_faces[j][3]] );
            if( faces.find( tmp ) != faces.end() ){
                faces.erase( tmp );
            } else {
                faces.insert( tmp );
            }
        }
    }
    for( std::set<face>::iterator iter=faces.begin(); iter!=faces.end(); iter++ ){
        face tmp = *iter;
        int pid[] = { tmp.vtx[0], tmp.vtx[1], tmp.vtx[2], tmp.vtx[3] };
        if( pid[3] < 0 ){
            tris.push_back( pid[0] );
            tris.push_back( pid[1] );
            tris.push_back( pid[2] );
        } else {
            quads.push_back( pid[0] );
            quads.push_back( pid[1] );
            quads.push_back( pid[2] );
            quads.push_back( pid[3] );

			
        }
    }
}


bool load_mesh( const char *filename, std::vector<double> &coords, std::vector<int> &tris, std::vector<int> &quads, std::vector<int> &tets, std::vector<int> &hexes ){
    FILE *fp = fopen( filename, "r" );
    if( !fp ){
        std::cout << "failed to open input file: " << filename << " exiting!" << std::endl;
        return false;
    }
    int nverts, ntris, nquads, ntets, nhexes;
    double x,y,z;
    int v0, v1, v2, v3, v4, v5, v6, v7;
    char line[1024];
    fgets(line,1024,fp);
    fgets(line,1024,fp);
    while( fgets( line, 1024, fp ) ){
        // read vertices
        if( line[0] == 'V' ){
            fgets(line,1024,fp);
            sscanf( line, "%d", &nverts );
            for( int i=0; i<nverts; i++ ){
                fgets(line,1024,fp);
                sscanf( line, "%lf%lf%lf", &x, &y, &z );
                coords.push_back( x );
                coords.push_back( y );
                coords.push_back( z );
            }
        }
        // read triangles
        if( line[0] == 'T' && line[1] == 'r' ){
            fgets( line, 1024, fp );
            sscanf( line, "%d", &ntris );
            for( int i=0; i<ntris; i++ ){
                fgets(line,1024,fp);
                sscanf( line, "%d%d%d", &v0, &v1, &v2 );
                tris.push_back( v0 );
                tris.push_back( v1 );
                tris.push_back( v2 );
            }
        }
        // read quadrilaterals
        if( line[0] == 'Q' ){
            fgets( line, 1024, fp );
            sscanf( line, "%d", &nquads );
            for( int i=0; i<nquads; i++ ){
                fgets(line,1024,fp);
                sscanf( line, "%d%d%d%d", &v0, &v1, &v2, &v3 );
                quads.push_back( v0 );
                quads.push_back( v1 );
                quads.push_back( v2 );
                quads.push_back( v3 );
            }
        }
        // read tetrahedra
        if( line[0] == 'T' && line[1] == 'e' ){
            fgets( line, 1024, fp );
            sscanf( line, "%d", &ntets );
            for( int i=0; i<ntets; i++ ){
                fgets(line,1024,fp);
                sscanf( line, "%d%d%d%d", &v0, &v1, &v2, &v3 );
                tets.push_back( v0 );
                tets.push_back( v1 );
                tets.push_back( v2 );
                tets.push_back( v3 );
            }
        }
        // read hexahedra
        if( line[0] == 'H' ){
            fgets( line, 1024, fp );
            sscanf( line, "%d", &nhexes );
            for( int i=0; i<nhexes; i++ ){
                fgets(line,1024,fp);
                sscanf( line, "%d%d%d%d%d%d%d%d", &v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7 );
                hexes.push_back( v0 );
                hexes.push_back( v1 );
                hexes.push_back( v2 );
                hexes.push_back( v3 );
                hexes.push_back( v4 );
                hexes.push_back( v5 );
                hexes.push_back( v6 );
                hexes.push_back( v7 );
            }
        }
        if( line[0] == 'E' ){
            break;
        }
    }
    fclose(fp);
    return true;
}

bool save_mesh( const char *filename, std::vector<double> &coords, std::vector<int> &tris, std::vector<int> &quads, std::vector<int> &tets, std::vector<int> &hexes, int off ){
    FILE *fp = fopen( filename, "w" );
    if( !fp ){
        std::cout << "failed to open output file: " << filename << ", exiting!" << std::endl;
        return false;
    }
    // write header
    fprintf( fp, "MeshVersionFormatted 1\n" );
    fprintf( fp, "Dimension 3\n" );

    // write vertices
    fprintf( fp, "Vertices\n" );
    fprintf( fp, "%d\n", (int)coords.size()/3 );
    for( int i=0; i<coords.size(); i+=3 ){
        fprintf( fp, "%lf %lf %lf -1\n", coords[i+0], coords[i+1], coords[i+2] );
    }
    
    // write triangles
    if( tris.size() > 0 ){
        fprintf( fp, "Triangles\n" );
        fprintf( fp, "%d\n", (int)tris.size()/3 );
        for( int i=0; i<tris.size(); i+=3 ){
            fprintf( fp, "%d %d %d 1\n", tris[i+0]+off, tris[i+1]+off, tris[i+2]+off );
        }
    }
    
    // write quads
    if( quads.size() > 0 ){
        fprintf( fp, "Quadrilaterals\n" );
        fprintf( fp, "%d\n", (int)quads.size()/4 );
        for( int i=0; i<quads.size(); i+=4 ){
            fprintf( fp, "%d %d %d %d 1\n", quads[i+0]+off, quads[i+1]+off, quads[i+2]+off, quads[i+3]+off );
        }
    }
    
    // write quads
    if( tets.size() > 0 ){
        fprintf( fp, "Tetrahedra\n" );
        fprintf( fp, "%d\n", (int)tets.size()/4 );
        for( int i=0; i<tets.size(); i+=4 ){
            fprintf( fp, "%d %d %d %d 1\n", tets[i+0]+off, tets[i+1]+off, tets[i+2]+off, tets[i+3]+off );
        }
    }
    
    // write hexes
    if( hexes.size() > 0 ){
        fprintf( fp, "Hexahedra\n" );
        fprintf( fp, "%d\n", (int)hexes.size()/8 );
        for( int i=0; i<hexes.size(); i+=8 ){
            fprintf( fp, "%d %d %d %d %d %d %d %d 1\n", hexes[i+0]+off, hexes[i+1]+off, hexes[i+2]+off, hexes[i+3]+off, hexes[i+4]+off, hexes[i+5]+off, hexes[i+6]+off, hexes[i+7]+off );
        }
    }
    
    // write footer and close the file
    fprintf( fp, "End\n\n" );
    fclose(fp);
    
    return true;
}


bool save_mesh( const char *filename, std::vector<double> &coords, std::vector<int> &hexes, int off )
{
    FILE *fp = fopen( filename, "w" );

    if( !fp )
    {
        std::cout << "failed to open output file: " << filename << ", exiting!" << std::endl;
        return false;
    }

    // write header
    fprintf( fp, "MeshVersionFormatted 1\n" );
    fprintf( fp, "Dimension 3\n" );

    // write vertices
    fprintf( fp, "Vertices\n" );
    fprintf( fp, "%d\n", (int)coords.size()/3 );
    for( int i=0; i<coords.size(); i+=3 ){
        fprintf( fp, "%lf %lf %lf -1\n", coords[i+0], coords[i+1], coords[i+2] );
    }

    // write hexes
    if( hexes.size() > 0 )
    {
        fprintf( fp, "Hexahedra\n" );
        fprintf( fp, "%d\n", (int)hexes.size()/8 );
        for( int i=0; i<hexes.size(); i+=8 ){
            fprintf( fp, "%d %d %d %d %d %d %d %d 1\n", hexes[i+0]+off, hexes[i+1]+off, hexes[i+2]+off, hexes[i+3]+off, hexes[i+4]+off, hexes[i+5]+off, hexes[i+6]+off, hexes[i+7]+off );
        }
    }

    // write footer and close the file
    fprintf( fp, "End\n\n" );
    fclose(fp);

    return true;
}

bool save_quadmesh( const char *filename, std::vector<double> &coords, std::vector<int> &quads, std::vector<int> &tris, int off ){
    FILE *fp = fopen( filename, "w" );

    if( !fp )
    {
        std::cout << "failed to open output file: " << filename << ", exiting!" << std::endl;
        return false;
    }

    // write vertices
    for( int i=0; i<coords.size(); i+=3 ){
        fprintf( fp, "v %lf %lf %lf\n", coords[i+0], coords[i+1], coords[i+2] );
    }

    if( quads.size() > 0 ){
        for( int i=0; i<quads.size(); i+=4 ){
            fprintf( fp, "f %d %d %d %d\n", quads[i+3]+off, quads[i+2]+off, quads[i+1]+off, quads[i+0]+off );
        }
    }

    if( tris.size() > 0 ){
        for( int i=0; i<tris.size(); i+=3 ){
            fprintf( fp, "f %d %d %d\n", tris[i+2]+off, tris[i+1]+off, tris[i+0]+off );
        }
    }
    fclose(fp);

    return true;
}

