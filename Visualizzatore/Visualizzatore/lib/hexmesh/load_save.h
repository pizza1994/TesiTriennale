#ifndef LOAD_SAVE_H
#define LOAD_SAVE_H

#include<vector>

void build_surface( std::vector<double> &coords, std::vector<int> &tris, std::vector<int> &quads, std::vector<int> &tets, std::vector<int> &hexes );

bool load_mesh( const char *filename, std::vector<double> &coords, std::vector<int> &tris, std::vector<int> &quads, std::vector<int> &tets, std::vector<int> &hexes );
bool load_tetgen( const char *filename, std::vector<double> &coords, std::vector<int> &tris, std::vector<int> &quads, std::vector<int> &tets, std::vector<int> &hexes );

bool save_mesh( const char *filename, std::vector<double> &coords, std::vector<int> &tris, std::vector<int> &quads, std::vector<int> &tets, std::vector<int> &hexes, int off );
bool save_mesh( const char *filename, std::vector<double> &coords, std::vector<int> &hexes, int off );
bool save_tetgen( const char *filename, std::vector<double> &coords, std::vector<int> &tris, std::vector<int> &quads, std::vector<int> &tets, std::vector<int> &hexes, int off );
bool save_quadmesh(const char *filename, std::vector<double> &coords, std::vector<int> &quads, std::vector<int> &tris, int off );


#endif
