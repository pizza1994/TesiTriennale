#include "vfl.h"

VFL::vertex_iterator VFL::vertex_begin()
{
    return vertex_iterator(vertex_list.begin());
}

VFL::vertex_iterator VFL::vertex_end()
{
    return vertex_iterator(vertex_list.end());
}

VFL::face_iterator VFL::face_begin()
{
    return face_iterator(face_list.begin());
}

VFL::face_iterator VFL::face_end()
{
    return face_iterator(face_list.end());
}

VFL::VFL()
{
}

VFL::~VFL()
{
    for (unsigned int i = 0; i < vertex_list.size(); ++i) delete vertex_list[i];
    for (unsigned int i = 0; i < face_list.size(); ++i) delete face_list[i];
    vertex_list.clear();
    face_list.clear();
}

VFL::vertex_pointer VFL::add_vertex()
{
    VFL::Vertex v;
    v.set_id(vid++);
    vertex_pointer last = new VFL::Vertex(v);
    vertex_list.push_back(last);
    return last;
}

VFL::vertex_pointer VFL::add_vertex(VFL::Vertex v)
{
    v.set_id(vid++);
    vertex_pointer last = new Vertex(v);
    vertex_list.push_back(last);
    return last;
}

VFL::face_pointer VFL::add_face()
{
    VFL::Face f;
    f.set_id(fid++);
    face_pointer last = new VFL::Face(f);
    face_list.push_back(last);
    return last;
}

VFL::face_pointer VFL::add_face(VFL::Face f)
{
    f.set_id(fid++);
    face_pointer last = new VFL::Face(f);
    face_list.push_back(last);
    return last;
}

VFL::vertex_pointer VFL::get_vertex(int id)
{
    int i = find_vertex(id);
    if (i >= 0) return vertex_list[i];
    else return NULL;
}

VFL::face_pointer VFL::get_face(int id)
{
    int i = find_face(id);
    if (i >= 0) return face_list[i];
    else return NULL;
}

int VFL::get_number_vertices()
{
    return vertex_list.size();
}

int VFL::get_number_faces()
{
    return face_list.size();
}

bool VFL::delete_vertex(VFL::vertex_pointer v)
{
    int i = find_vertex(v);
    if (i != -1){
        vertex_list.erase(vertex_list.begin() + i);
        delete v;
        return true;
    }
    return false;
}

bool VFL::delete_face(VFL::face_pointer f)
{
    int i = find_face(f);
    if (i != -1){
        face_list.erase(face_list.begin() + i);
        delete f;
        return true;
    }
    return false;
}

bool VFL::delete_vertex(VFL::vertex_iterator vit)
{
    delete vit.get_vertex_pointer();
    vertex_list.erase(vit.get_iterator());
    return true;
}

bool VFL::delete_face(VFL::face_iterator fit)
{
    delete fit.get_face_pointer();
    face_list.erase(fit.get_iterator());
    return true;
}

std::pair<Pointf, Pointf> VFL::get_bounding_box()
{
    float minx=10000, miny=10000, minz=10000, maxx=-10000, maxy=-10000, maxz=-10000;
    vertex_iterator vit = vertex_begin();
    for (; vit!=vertex_end(); ++vit){
        Pointf p = vit->get_coordinate();
        if (p.x_coord < minx) minx = p.x_coord;
        if (p.y_coord < miny) miny = p.y_coord;
        if (p.z_coord < minz) minz = p.z_coord;
        if (p.x_coord > maxx) maxx = p.x_coord;
        if (p.y_coord > maxy) maxy = p.y_coord;
        if (p.z_coord > maxz) maxz = p.z_coord;
    }
    Pointf min(minx, miny, minz);
    Pointf max(maxx, maxy, maxz);
    return std::pair<Pointf, Pointf>(min, max);
}

bool VFL::is_triangle_mesh()
{
    VFL::face_iterator fit;
    for (fit = face_begin(); fit != face_end(); ++fit)
        if (! fit->is_triangle()) return false;
    return true;
}

void VFL::update_face_normals()
{
    VFL::face_iterator fit;
    for (fit = face_begin(); fit != face_end(); ++fit)
        fit->update_normal();
}

void VFL::recalculate_ids()
{
    int i = 0;
    for (vertex_iterator vit = vertex_begin(); vit != vertex_end(); ++vit) vit->set_id(i++);
    i = 0;
    for (face_iterator fit = face_begin(); fit != face_end(); ++fit) fit->set_id(i++);
}

void VFL::reset_face_colors()
{
    for (face_iterator fit = face_begin(); fit != face_end(); ++fit) fit->set_color(Color());
}

void VFL::reset()
{
    for (unsigned int i=0; i<vertex_list.size(); i++) delete vertex_list[i];
    for (unsigned int i=0; i<face_list.size(); i++) delete face_list[i];
    vertex_list.clear();
    face_list.clear();
    vid = 0;
    fid = 0;
}

void VFL::erase()
{
    for (unsigned int i=0; i<vertex_list.size(); i++) delete vertex_list[i];
    for (unsigned int i=0; i<face_list.size(); i++) delete face_list[i];
    vertex_list.clear();
    face_list.clear();
    vid = 0;
    fid = 0;
}

std::string VFL::load_from_obj_file(std::string filename)
{
    reset();
    typedef boost::char_separator<char>     CharSeparator;
    typedef boost::tokenizer<CharSeparator> Tokenizer;
    typedef Tokenizer::iterator             TokenizerIterator;

    CharSeparator space_separator(" ");
    CharSeparator slash_separator("/");

    static std::string vertex = "v";
    static std::string face   = "f";

    std::ifstream file(filename);
    std::string   line;

    if(!file.is_open())
    {
        qDebug() << "ERROR : read() : could not open input file " << filename.c_str() << "\n";
        assert(0);
    }

    while(std::getline(file,line))
    {
        Tokenizer space_tokenizer(line, space_separator);

        if (space_tokenizer.begin() == space_tokenizer.end()) continue;

        TokenizerIterator token = space_tokenizer.begin();
        std::string header = *token;

        // Handle
        //
        // v 0.123 0.234 0.345
        // v 0.123 0.234 0.345 1.0

        if (strcmp(header.c_str(), vertex.c_str()) == 0)
        {
            std::string x = *(++token);
            std::string y = *(++token);
            std::string z = *(++token);

            Pointf coord(atof(x.c_str()), atof(y.c_str()), atof(z.c_str()));

            Vertex v(coord);
            add_vertex(v);
        }

        // Handle
        //
        // f 1 2 3
        // f 3/1 4/2 5/3
        // f 6/4/1 3/5/3 7/6/5
        //
        // NOTE: 6/4/1 => only 6 (vertex id) will be stored in the mesh

        else if (strcmp(header.c_str(), face.c_str()) == 0)
        {
            QVector<std::string> dummy;
            int i=-1;
            token++;
            while (token != space_tokenizer.end()) {
                dummy.push_back(*(token));
                token++;
                i++;
            }

            std::vector<Tokenizer> slash_tokenizer;
            for (int i=0; i<dummy.size(); i++){
                Tokenizer t(dummy[i], slash_separator);
                slash_tokenizer.push_back(t);
            }

            std::vector<int> nid;
            for (unsigned int i=0; i<slash_tokenizer.size(); i++){
                nid.push_back(atoi((*slash_tokenizer[i].begin()).c_str()));
            }
            Face f;
            face_pointer fid = add_face(f);
            for (unsigned int i = 0; i < nid.size(); i++)
                fid->add_vertex(get_vertex(nid[i] - 1));

            fid->update_normal();
            fid->update_area();
        }

        // Ignore
        //
        // vt 0.500 1 [0]
        // vn 0.707 0.000 0.707
        // vp 0.310000 3.210000 2.100000
        // ...

    }
    file.close();
    std::stringstream ss;
    ss << "Vertices: " << vertex_list.size() << "; Faces: " << face_list.size() << ".";
    return ss.str();
}

std::string VFL::load_from_ply_file(std::string filename)
{
    reset();
    typedef boost::char_separator<char>     CharSeparator;
    typedef boost::tokenizer<CharSeparator> Tokenizer;
    typedef Tokenizer::iterator             TokenizerIterator;

    CharSeparator space_separator(" ");

    std::ifstream file(filename);
    std::string   line;

    int n_vertices = -1, n_faces = -1;
    int nv=0, nf=0;

    if(!file.is_open())
    {
        qDebug() << "ERROR : read() : could not open input file " << filename.c_str() << "\n";
        assert(0);
    }

    bool header = true, vertex=false, face=false, edge=false, vertex_color_int = false, face_color_int = false;
    std::pair<std::string, std::string> vertex_order("", ""), face_order("", "");
    while(std::getline(file,line))
    {
        Tokenizer space_tokenizer(line, space_separator);

        if (space_tokenizer.begin() == space_tokenizer.end()) continue;

        TokenizerIterator token = space_tokenizer.begin();
        std::string header_line = *token;
        if (header){
            if (header_line == "end_header"){
                header = false;
            }
            if (header_line == "element"){
                std::string s = *(++token);
                if (s == "vertex"){
                    n_vertices = atof((*(++token)).c_str());
                    vertex = true;
                    face = edge = false;
                }
                if (s == "face"){
                    n_faces = atof((*(++token)).c_str());
                    face = true;
                    vertex = edge = false;
                }
            }
            if (header_line == "property"){
                std::string type;
                if (vertex){
                    type = *(++token);
                    ++token;
                    if (*token == "red"){
                        if (vertex_order.first == "") vertex_order.first = "color";
                        else vertex_order.second = "color";
                        if (type == "uchar" || type == "int") vertex_color_int = true;
                    }
                    if (*token == "nx") {
                        if (vertex_order.first == "") vertex_order.first = "normal";
                        else vertex_order.second = "normal";
                    }
                }
                if (face){
                    type = *(++token);
                    ++token;
                    if (*token == "red"){
                        if (face_order.first == "") face_order.first = "color";
                        else face_order.second = "color";
                        if (type == "uchar" || type == "int") face_color_int = true;
                    }
                    if (*token == "nx") {
                        if (face_order.first == "") face_order.first = "normal";
                        else face_order.second = "normal";
                    }

                }
            }
        }
        else {
            if (nv < n_vertices){
                std::string x = *(token);
                std::string y = *(++token);
                std::string z = *(++token);

                Pointf coord(atof(x.c_str()), atof(y.c_str()), atof(z.c_str()));

                Vertex v(coord);
                add_vertex(v);
                nv++;
            }
            else {
                if (nf < n_faces){
                    std::vector<std::string> dummy;
                    int nvf = atoi((*(token++)).c_str());
                    while (token != space_tokenizer.end()) {
                        dummy.push_back(*(token++));
                    }

                    Face f;
                    face_pointer fid = add_face(f);
                    QVector<int> nid;
                    for (int i=0; i<nvf; i++){
                        nid.push_back(atoi((dummy[i]).c_str()));
                        fid->add_vertex(get_vertex(nid[i]));
                    }


                    fid->update_normal();
                    fid->update_area();
                    nf++;
                    if (face_order.first == "normal"){
                        std::string x = dummy[nvf];
                        std::string y = dummy[nvf+1];
                        std::string z = dummy[nvf+2];

                        Vec3 norm(atof(x.c_str()), atof(y.c_str()), atof(z.c_str()));
                        fid->set_normal(norm);
                    }
                    if (face_order.first == "color"){
                        std::string x = dummy[nvf];
                        std::string y = dummy[nvf+1];
                        std::string z = dummy[nvf+2];

                        if (face_color_int){
                            Color color((float)(atof(x.c_str()) / 255.0), (float)(atof(y.c_str()) / 255.0), (float)(atof(z.c_str()) / 255.0));
                            fid->set_color(color);
                        }
                        else {
                            Color color((float)atof(x.c_str()), (float)atof(y.c_str()), (float)atof(z.c_str()));
                            fid->set_color(color);
                        }
                    }
                    if (face_order.second == "normal"){
                        std::string x = dummy[nvf+3];
                        std::string y = dummy[nvf+4];
                        std::string z = dummy[nvf+5];

                        Vec3 norm(atof(x.c_str()), atof(y.c_str()), atof(z.c_str()));
                        fid->set_normal(norm);
                    }
                    if (face_order.second == "color"){
                        std::string x = dummy[nvf+3];
                        std::string y = dummy[nvf+4];
                        std::string z = dummy[nvf+5];

                        if (vertex_color_int){
                            Color color((float)(atof(x.c_str()) / 255.0), (float)(atof(y.c_str()) / 255.0), (float)(atof(z.c_str()) / 255.0));
                            fid->set_color(color);
                        }
                        else {
                            Color color((float)atof(x.c_str()), (float)atof(y.c_str()), (float)atof(z.c_str()));
                            fid->set_color(color);
                        }
                    }

                }
            }
        }
    }
    file.close();
    std::stringstream ss;
    ss << "Vertices: " << vertex_list.size() << "; Faces: " << face_list.size() << ".";
    return ss.str();
}

void VFL::save_on_obj_file(std::string filename)
{
    int i = 0;
    for (vertex_iterator vit = vertex_begin(); vit != vertex_end(); ++vit) vit->private_flag = i++;
    std::map<Color, std::string> colors;
    std::string filename_obj, filename_mtu;
    std::string string_color = "COLOR";
    int num_color = 0;
    Color actual_color;
    filename_obj = filename + ".obj";
    filename_mtu = filename + ".mtu";
    std::ofstream filestream_obj, filestream_mtu;
    filestream_obj.open(filename_obj.c_str());
    filestream_mtu.open(filename_mtu.c_str());

    if (filestream_obj && filestream_mtu)
    {
        filestream_obj << "mtllib " << filename_mtu << "\n";
        for (vertex_iterator vid = vertex_begin(); vid != vertex_end(); vid++)
        {
            filestream_obj << "v " << vid->get_coordinate().x_coord << " "<< vid->get_coordinate().y_coord << " " <<  vid->get_coordinate().z_coord << "\n";

        }

        for (face_iterator fit = face_begin(); fit != face_end(); fit++)
        {
            if (fit->get_color() != actual_color){
                std::map<Color, std::string>::iterator it = colors.find(fit->get_color());
                if (it == colors.end()){
                    std::stringstream stm;
                    stm << string_color << num_color;
                    std::string mtl_color = stm.str();
                    num_color++;
                    filestream_mtu << "newmtl " << mtl_color << "\nKd " << fit->get_color().get_red() << " " << fit->get_color().get_green() << " " << fit->get_color().get_blue() << "\n";
                    colors[fit->get_color()] = mtl_color;
                    filestream_obj << "usemtl " << mtl_color << "\n";
                    actual_color = fit->get_color();
                }
                else {
                    filestream_obj << "usemtl " << colors[fit->get_color()] << "\n";
                    actual_color = fit->get_color();
                }
            }

            filestream_obj << "f ";
            for (VFL::Face::vertex_iterator vit = fit->vertex_begin(); vit != fit->vertex_end(); ++vit){
                filestream_obj << (vit->private_flag + 1) << " ";
            }
            filestream_obj << "\n";
        }

        filestream_obj.close();
        filestream_mtu.close();
    }
}

void VFL::save_on_ply_file(std::string filename)
{
    int i = 0;
    for (vertex_iterator vit = vertex_begin(); vit != vertex_end(); ++vit) vit->private_flag = i++;
    std::string filename_ply;
    filename_ply = filename + ".ply";
    std::ofstream filestream_ply;
    filestream_ply.open(filename_ply.c_str());
    filestream_ply << "ply\nformat ascii 1.0\n";
    filestream_ply << "element vertex " << vertex_list.size()<< "\n";
    filestream_ply << "property float x\nproperty float y\nproperty float z\n";
    filestream_ply << "element face " << face_list.size()<< "\n";
    filestream_ply << "property list uchar int vertex_indices\n";
    filestream_ply << "property uchar red\nproperty uchar green\nproperty uchar blue\n";
    filestream_ply << "end_header\n";
    for (vertex_iterator vid = vertex_begin(); vid != vertex_end(); ++vid)
    {
        filestream_ply << vid->get_coordinate().x_coord << " "<< vid->get_coordinate().y_coord << " " <<  vid->get_coordinate().z_coord << "\n";
    }

    for (face_iterator fit = face_begin(); fit != face_end(); ++fit)
    {
        filestream_ply << fit->get_number_vertices() << " ";
        for (Face::vertex_iterator vit = fit->vertex_begin(); vit != fit->vertex_end(); ++vit){
            filestream_ply << vit->private_flag << " ";
        }
        if (fit->get_color() == Color()) filestream_ply << "128 128 128\n";
        else {
            int r, g, b;
            r = fit->get_color().get_red_int();
            g = fit->get_color().get_green_int();
            b = fit->get_color().get_blue_int();
            filestream_ply << r << " " << g << " " << b << "\n";
        }
    }
    filestream_ply.close();
}

int VFL::find_vertex(int vid)
{
    int first = 0, last = vertex_list.size()-1, mid;
    while (first <= last){
        mid = (first + last) / 2;
        if (vertex_list[mid]->get_id() < vid) first = mid + 1;
        else if (vertex_list[mid]->get_id() == vid) return mid;
        else last = mid - 1;
    }
    return -1;
}

int VFL::find_face(int fid)
{
    int first = 0, last = face_list.size()-1, mid;
    while (first <= last){
        mid = (first + last) / 2;
        if (face_list[mid]->get_id() < fid) first = mid + 1;
        else if (face_list[mid]->get_id() == fid) return mid;
        else last = mid - 1;
    }
    return -1;
}

int VFL::find_vertex(VFL::vertex_pointer v)
{
    int first = 0, last = vertex_list.size()-1, mid;
    while (first <= last){
        mid = (first + last) / 2;
        if (vertex_list[mid]->get_id() < v->get_id()) first = mid + 1;
        else if (vertex_list[mid]->get_id() == v->get_id()) return mid;
        else last = mid - 1;
    }
    return -1;
}

int VFL::find_face(face_pointer f)
{
    int first = 0, last = face_list.size()-1, mid;
    while (first <= last){
        mid = (first + last) / 2;
        if (face_list[mid]->get_id() < f->get_id()) first = mid + 1;
        else if (face_list[mid]->get_id() == f->get_id()) return mid;
        else last = mid - 1;
    }
    return -1;
}

VFL::Vertex::Vertex()
{
    this->id = 0;
}

VFL::Vertex::Vertex(Pointf p)
{
    this->id = 0;
    this->p = p;
}

VFL::Vertex::~Vertex()
{
}

int VFL::Vertex::get_id()
{
    return id;
}

int VFL::Vertex::get_flag()
{
    return flag;
}

void VFL::Vertex::set_flag()
{
    flag = 1;
}

void VFL::Vertex::reset_flag()
{
    flag = 0;
}

void VFL::Vertex::set_flag(int f)
{
    flag = f;
}

Pointf VFL::Vertex::get_coordinate()
{
    return p;
}

void VFL::Vertex::set_coordinate(Pointf p)
{
    this->p = p;
}

double VFL::Vertex::dist(VFL::Vertex *v)
{
    return this->p.dist(v->get_coordinate());
}

bool VFL::Vertex::operator ==(const VFL::Vertex &v1)
{
    return (p == v1.p);
}

bool VFL::Vertex::operator !=(const VFL::Vertex &v1)
{
    return (p != v1.p);
}

void VFL::Vertex::set_id(int id)
{
    this->id = id;
}


VFL::Face::Face()
{
}

int VFL::Face::get_id()
{
    return id;
}

int VFL::Face::get_flag()
{
    return flag;
}

void VFL::Face::set_flag()
{
    flag = 1;
}

void VFL::Face::reset_flag()
{
    flag = 0;
}

void VFL::Face::set_flag(int f)
{
    flag = f;
}

std::vector<VFL::Vertex *> VFL::Face::get_vertices()
{
    return vertex_list;
}

int VFL::Face::get_number_vertices()
{
    return vertex_list.size();
}

void VFL::Face::add_vertex(VFL::Vertex *v)
{
    vertex_list.push_back(v);
}

VFL::Vertex *VFL::Face::get_vertex(int i)
{
    return vertex_list[i];
}

bool VFL::Face::is_triangle()
{
    if (vertex_list.size() == 3) return true;
    return false;
}

Vec3 VFL::Face::get_normal()
{
    return normal;
}

Vec3 VFL::Face::update_normal()
{
    if (is_triangle()){
        Vertex* a = vertex_list[0], *b = vertex_list[1], *c = vertex_list[2];
        normal = (b->get_coordinate() - a->get_coordinate()).cross(c->get_coordinate() - a->get_coordinate());
    }
    normal.normalize();
    return normal;
}

float VFL::Face::get_area()
{
    return area;
}

void VFL::Face::set_area(float area)
{
    this->area = area;
}

void VFL::Face::set_normal(Vec3 norm)
{
    this->normal = norm;
}

Color VFL::Face::get_color()
{
    return color;
}

void VFL::Face::set_color(Color color)
{
    this->color = color;
}

float VFL::Face::update_area()
{
    if (!is_triangle()) return -1;
    else {
        Vertex* a = vertex_list[0], *b = vertex_list[1], *c = vertex_list[2];
        Pointf v1 = a->get_coordinate();
        Pointf v2 = b->get_coordinate();
        Pointf v3 = c->get_coordinate();
        this->area = (((v3 - v1).cross(v2 - v1)).get_length() / 2);
        return area;
    }
}

VFL::Face::vertex_iterator VFL::Face::vertex_begin()
{
    return vertex_list.begin();
}

VFL::Face::vertex_iterator VFL::Face::vertex_end()
{
    return vertex_list.end();
}

void VFL::Face::set_id(int id)
{
    this->id = id;
}

std::vector<VFL::Vertex*>::iterator VFL::Face::vertex_iterator::get_iterator()
{
    return it;
}

VFL::Face::vertex_iterator::vertex_iterator()
{
}

VFL::Face::vertex_iterator::vertex_iterator(std::vector<VFL::Vertex*>::iterator it)
{
    this->it = it;
}

VFL::Vertex &VFL::Face::vertex_iterator::operator *() const
{
    return **it;
}

VFL::Vertex *VFL::Face::vertex_iterator::operator ->() const
{
    return *it;
}

VFL::Face::vertex_iterator VFL::Face::vertex_iterator::operator ++()
{
    ++it;
    return *this;
}

VFL::Face::vertex_iterator VFL::Face::vertex_iterator::operator ++(int)
{
    vertex_iterator old_value = *this;
    ++it;
    return old_value;
}

VFL::Face::vertex_iterator VFL::Face::vertex_iterator::operator --()
{
    --it;
    return *this;
}

VFL::Face::vertex_iterator VFL::Face::vertex_iterator::operator --(int)
{
    vertex_iterator old_value = *this;
    --it;
    return old_value;
}

bool VFL::Face::vertex_iterator::operator ==(VFL::Face::vertex_iterator right)
{
    return this->it == right.it;
}

bool VFL::Face::vertex_iterator::operator !=(VFL::Face::vertex_iterator right)
{
    return !(*this == right);
}

VFL::Vertex *VFL::Face::vertex_iterator::get_vertex_id()
{
    return *it;
}


std::vector<VFL::Vertex*>::iterator VFL::vertex_iterator::get_iterator()
{
    return it;
}

VFL::vertex_iterator::vertex_iterator()
{
}

VFL::vertex_iterator::vertex_iterator(std::vector<VFL::Vertex*>::iterator it)
{
    this->it = it;
}

VFL::Vertex &VFL::vertex_iterator::operator *() const
{
    return **it;
}

VFL::vertex_pointer VFL::vertex_iterator::operator ->() const
{
    return *it;
}

VFL::vertex_iterator VFL::vertex_iterator::operator ++()
{
    ++it;
    return *this;
}

VFL::vertex_iterator VFL::vertex_iterator::operator ++(int)
{
    vertex_iterator old_value = *this;
    ++it;
    return old_value;
}

VFL::vertex_iterator VFL::vertex_iterator::operator --()
{
    --it;
    return *this;
}

VFL::vertex_iterator VFL::vertex_iterator::operator --(int)
{
    vertex_iterator old_value = *this;
    --it;
    return old_value;
}

bool VFL::vertex_iterator::operator ==(VFL::vertex_iterator right)
{
    return this->it == right.it;
}

bool VFL::vertex_iterator::operator !=(VFL::vertex_iterator right)
{
    return !(*this == right);
}

VFL::vertex_pointer VFL::vertex_iterator::get_vertex_pointer()
{
    return *it;
}


std::vector<VFL::Face*>::iterator VFL::face_iterator::get_iterator()
{
    return it;
}

VFL::face_iterator::face_iterator()
{
}

VFL::face_iterator::face_iterator(std::vector<VFL::Face*>::iterator it)
{
    this->it = it;
}

VFL::Face &VFL::face_iterator::operator *() const
{
    return **it;
}

VFL::face_pointer VFL::face_iterator::operator ->() const
{
    return *it;
}

VFL::face_iterator VFL::face_iterator::operator ++()
{
    ++it;
    return *this;
}

VFL::face_iterator VFL::face_iterator::operator ++(int)
{
    face_iterator old_value = *this;
    ++it;
    return old_value;
}

VFL::face_iterator VFL::face_iterator::operator --()
{
    --it;
    return *this;
}

VFL::face_iterator VFL::face_iterator::operator --(int)
{
    face_iterator old_value = *this;
    --it;
    return old_value;
}

bool VFL::face_iterator::operator ==(VFL::face_iterator right)
{
    return this->it == right.it;
}

bool VFL::face_iterator::operator !=(VFL::face_iterator right)
{
    return !(*this == right);
}

VFL::face_pointer VFL::face_iterator::get_face_pointer()
{
    return *it;
}
