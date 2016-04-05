#include "dcel.h"

DCEL::DCEL()
{
}

DCEL::~DCEL()
{
    for (unsigned int i=0; i<V.size(); i++) delete V[i];
    for (unsigned int i=0; i<HE.size(); i++) delete HE[i];
    for (unsigned int i=0; i<F.size(); i++) delete F[i];
    V.clear();
    HE.clear();
    F.clear();
}

/**
 * \param v Il vertice da aggiungere alla DCEL.
 * \return l'indice del vertice aggiunto.
 */
vertex_id DCEL::add_vertex(Vertex v )	{
    v.set_id(vid++);
    vertex_id last= new Vertex(v);
    V.push_back( last );
    return last;
}

/**
 * \param he L'half-edge da aggiungere alla DCEL.
 * \return l'indice dell'half-edge aggiunto.
 */
half_edge_id DCEL::add_half_edge(HalfEdge he )	{
    he.set_id(heid++);
    half_edge_id last = new HalfEdge(he);
    HE.push_back( last );
    return last;
}

/**
 * \param f La faccia da aggiungere alla DCEL.
 * \return l'indice della faccia aggiunta.
 */
face_id DCEL::add_face(Face f )	{
    f.set_id(fid++);
    face_id last = new Face(f);
    F.push_back( last );
    return last;
}

vertex_id DCEL::add_vertex()
{
    Vertex v;
    v.set_id(vid++);
    vertex_id last= new Vertex(v);
    V.push_back( last );
    return last;
}

half_edge_id DCEL::add_half_edge()
{
    HalfEdge he;
    he.set_id(heid++);
    half_edge_id last = new HalfEdge(he);
    HE.push_back( last );
    return last;
}

face_id DCEL::add_face()
{
    Face f;
    f.set_id(fid++);
    face_id last = new Face(f);
    F.push_back( last );
    return last;
}

vertex_id DCEL::get_vertex(int id)
{
    int i = find_vertex(id);
    if (i >= 0) return V[i];
    else return NULL;
}

half_edge_id DCEL::get_half_edge(int id)
{
    int i = find_half_edge(id);
    if (i >= 0) return HE[i];
    else return NULL;
}

face_id DCEL::get_face(int id)
{
    int i = find_face(id);
    if (i >= 0) return F[i];
    else return NULL;
}

/** \return Il numero di vertici della DCEL. */
int DCEL::get_number_vertices ( void )	{
    return V.size();
}

/** \return Il numero di half-edge della DCEL. */
int DCEL::get_number_half_edges ( void )	{
    return HE.size();
}

/** \return Il numero di facce della DCEL. */
int DCEL::get_number_faces ( void )	{
    return F.size();
}

/**
 * @brief DCEL::load_from_file
 * @param filename
 *
 */
std::string DCEL::load_from_obj_file(std::string filename)
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

    std::vector<vertex_id> vertices;

    std::map< std::pair<int,int>, half_edge_id > edge;
    std::map< std::pair<int,int>, half_edge_id >::iterator eiter;

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
            vertex_id vid = add_vertex(v);

            vertices.push_back(vid);
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
            nid.push_back(nid[0]);
            std::pair<int, int> p;
            HalfEdge e;
            half_edge_id eid = NULL;
            Face f;
            face_id fid = add_face(f);
            half_edge_id prev = NULL;
            half_edge_id first = NULL;

            for (unsigned int i=0; i<nid.size()-1; i++){
                eid = add_half_edge(e);
                if (i==0) {
                    first = eid;
                    fid->set_outer_half_edge(eid);
                }
                else {
                    eid->set_prev(prev);
                    prev->set_next(eid);
                }
                vertices[nid[i] - 1]->set_incident_half_edge(eid);
                eid->set_from_vertex(vertices[nid[i] - 1]);
                vertices[nid[i] - 1]->increment_cardinality();
                eid->set_to_vertex(vertices[nid[i+1] - 1]);
                eid->set_face(fid);
                p.first = nid[i+1] - 1;
                p.second = nid[i] - 1;
                eiter = edge.find(p);
                if (eiter != edge.end()){
                    half_edge_id twin = edge[p];
                    eid->set_twin(twin);
                    twin->set_twin(eid);
                    edge.erase(eiter);
                }
                else {
                    p.first = nid[i] - 1;
                    p.second = nid[i+1] - 1;
                    edge[p] = eid;
                }
                prev = eid;
            }
            eid->set_next(first);
            first->set_prev(eid);

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
    if (is_triangle_mesh()) update_vertex_normals();
    std::stringstream ss;
    ss << "Vertices: " << V.size() << "; Half Edges: " << HE.size() << "; Faces: " << F.size() << ".";
    return ss.str();
}

std::string DCEL::load_from_ply_file(std::string filename)
{
    reset();
    typedef boost::char_separator<char>     CharSeparator;
    typedef boost::tokenizer<CharSeparator> Tokenizer;
    typedef Tokenizer::iterator             TokenizerIterator;

    CharSeparator space_separator(" ");

    std::ifstream file(filename);
    std::string   line;

    QVector<vertex_id> vertices;

    int n_vertices = -1, n_faces = -1;
    int nv=0, nf=0;

    std::map< std::pair<int,int>, half_edge_id > edge_map;
    std::map< std::pair<int,int>, half_edge_id >::iterator eiter;

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
                vertex_id vid = add_vertex(v);
                nv++;

                vertices.push_back(vid);
                if (vertex_order.first == "normal"){
                    std::string x = *(++token);
                    std::string y = *(++token);
                    std::string z = *(++token);

                    Vec3 norm(atof(x.c_str()), atof(y.c_str()), atof(z.c_str()));
                    vid->set_normal(norm);
                }
                if (vertex_order.first == "color"){
                    std::string x = *(++token);
                    std::string y = *(++token);
                    std::string z = *(++token);

                    if (vertex_color_int){
                        Color color(atoi(x.c_str()), atoi(y.c_str()), atoi(z.c_str()));
                        //vid->set_color(color);
                    }
                    else {
                        Color color(atof(x.c_str()), atof(y.c_str()), atof(z.c_str()));
                        //vid->set_color(color);
                    }
                }
                if (vertex_order.second == "normal"){
                    std::string x = *(++token);
                    std::string y = *(++token);
                    std::string z = *(++token);

                    Vec3 norm(atof(x.c_str()), atof(y.c_str()), atof(z.c_str()));
                    vid->set_normal(norm);
                }
                if (vertex_order.second == "color"){
                    std::string x = *(++token);
                    std::string y = *(++token);
                    std::string z = *(++token);

                    if (vertex_color_int){
                        Color color(atoi(x.c_str()), atoi(y.c_str()), atoi(z.c_str()));
                        //vid->set_color(color);
                    }
                    else {
                        Color color(atof(x.c_str()), atof(y.c_str()), atof(z.c_str()));
                        //vid->set_color(color);
                    }
                }

            }
            else {
                if (nf < n_faces){
                    std::vector<std::string> dummy;
                    int nvf = atoi((*(token++)).c_str());
                    while (token != space_tokenizer.end()) {
                        dummy.push_back(*(token++));
                    }

                    std::vector<int> nid;
                    for (int i=0; i<nvf; i++){
                        nid.push_back(atoi((dummy[i]).c_str()));
                    }
                    nid.push_back(nid[0]);
                    std::pair<int, int> p;
                    HalfEdge e;
                    half_edge_id eid = NULL;
                    Face f;
                    face_id fid = add_face(f);
                    half_edge_id prev = NULL;
                    half_edge_id first = NULL;

                    for (unsigned int i=0; i<nid.size()-1; i++){
                        eid = add_half_edge(e);
                        if (i==0) {
                            first = eid;
                            fid->set_outer_half_edge(eid);
                        }
                        else {
                            eid->set_prev(prev);
                            prev->set_next(eid);
                        }
                        vertices[nid[i]]->set_incident_half_edge(eid);
                        eid->set_from_vertex(vertices[nid[i]]);
                        vertices[nid[i]]->increment_cardinality();
                        eid->set_to_vertex(vertices[nid[i+1]]);
                        eid->set_face(fid);
                        p.first = nid[i+1];
                        p.second = nid[i];
                        eiter = edge_map.find(p);
                        if (eiter != edge_map.end()){
                            half_edge_id twin = edge_map[p];
                            eid->set_twin(twin);
                            twin->set_twin(eid);
                            edge_map.erase(eiter);
                        }
                        else {
                            p.first = nid[i];
                            p.second = nid[i+1];
                            edge_map[p] = eid;
                        }
                        prev = eid;
                    }
                    eid->set_next(first);
                    first->set_prev(eid);

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
    if (is_triangle_mesh()) update_vertex_normals();
    std::stringstream ss;
    ss << "Vertices: " << V.size() << "; Half Edges: " << HE.size() << "; Faces: " << F.size() << ".";
    return ss.str();
}

void DCEL::save_on_obj_file(std::string filename)
{
    std::map<vertex_id, int> vertices;
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
        int i = 1;
        for (vertex_iterator vid = vertex_begin(); vid != vertex_end(); vid++)
        {
            filestream_obj << "v " << vid->get_coordinate().x_coord << " "<< vid->get_coordinate().y_coord << " " <<  vid->get_coordinate().z_coord << "\n";
            vertices[vid.get_vertex_id()] = i;
            i++;
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
            if (fit->get_number_inner_half_edges() == 0) {
                for (Face::incident_half_edge_iterator heit = fit->incident_half_edge_begin(); heit != fit->incident_half_edge_end(); ++heit){
                    heit->check_from_vertex();
                    filestream_obj << vertices[heit->get_from_vertex()] << " ";
                }
            }
            else {
                /// Gestione Buchi
                std::vector<vertex_id> v = make_single_border(fit.get_face_id());
                for (unsigned int i = 0; i<v.size(); ++i) filestream_obj << vertices[v[i]] << " ";
            }
            filestream_obj << "\n";
        }

        filestream_obj.close();
        filestream_mtu.close();
    }
}

void DCEL::save_on_ply_file(std::string filename)
{
    int i = 0;
    for (vertex_iterator vit = vertex_begin(); vit != vertex_end(); ++vit) vit->private_flag = i++;
    std::string filename_ply;
    filename_ply = filename + ".ply";
    std::ofstream filestream_ply;
    filestream_ply.open(filename_ply.c_str());
    filestream_ply << "ply\nformat ascii 1.0\n";
    filestream_ply << "element vertex " << V.size()<< "\n";
    filestream_ply << "property float x\nproperty float y\nproperty float z\n";
    filestream_ply << "element face " << F.size()<< "\n";
    filestream_ply << "property list uchar int vertex_indices\n";
    filestream_ply << "property uchar red\nproperty uchar green\nproperty uchar blue\n";
    filestream_ply << "end_header\n";
    for (vertex_iterator vid = vertex_begin(); vid != vertex_end(); ++vid)
    {
        filestream_ply << vid->get_coordinate().x_coord << " "<< vid->get_coordinate().y_coord << " " <<  vid->get_coordinate().z_coord << "\n";
    }

    for (face_iterator fit = face_begin(); fit != face_end(); ++fit)
    {
        std::vector<int> vint;
        if (fit->get_number_inner_half_edges() == 0) {
            for (Face::incident_half_edge_iterator heit = fit->incident_half_edge_begin(); heit != fit->incident_half_edge_end(); ++heit){
                heit->check_from_vertex();
                vint.push_back(heit->get_from_vertex()->private_flag);
            }
        }
        else { /// Gestione Buchi
            std::vector<vertex_id> v = make_single_border(fit.get_face_id());
            for (unsigned int i = 0; i<v.size(); ++i) vint.push_back((v[i])->private_flag);

        }
        filestream_ply << vint.size() << " ";
        for (unsigned int i =0; i<vint.size(); i++) filestream_ply << vint[i] << " ";
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

int DCEL::find_vertex(vertex_id v)
{
    int first = 0, last =V.size()-1, mid;
    while (first <= last){
        mid = (first + last) / 2;
        if (V[mid]->get_id() < v->get_id()) first = mid + 1;
        else if (V[mid]->get_id() == v->get_id()) return mid;
        else last = mid - 1;
    }
    return -1;
}

int DCEL::find_half_edge(half_edge_id he)
{
    int first = 0, last =HE.size()-1, mid;
    while (first <= last){
        mid = (first + last) / 2;
        if (HE[mid]->get_id() < he->get_id()) first = mid + 1;
        else if (HE[mid]->get_id() == he->get_id()) return mid;
        else last = mid - 1;
    }
    return -1;
}

int DCEL::find_face(face_id f)
{
    int first = 0, last =F.size()-1, mid;
    while (first <= last){
        mid = (first + last) / 2;
        if (F[mid]->get_id() < f->get_id()) first = mid + 1;
        else if (F[mid]->get_id() == f->get_id()) return mid;
        else last = mid - 1;
    }
    return -1;
}

int DCEL::find_vertex(int v)
{
    int first = 0, last =V.size()-1, mid;
    while (first <= last){
        mid = (first + last) / 2;
        if (V[mid]->get_id() < v) first = mid + 1;
        else if (V[mid]->get_id() == v) return mid;
        else last = mid - 1;
    }
    return -1;
}

int DCEL::find_half_edge(int he)
{
    int first = 0, last =HE.size()-1, mid;
    while (first <= last){
        mid = (first + last) / 2;
        if (HE[mid]->get_id() < he) first = mid + 1;
        else if (HE[mid]->get_id() == he) return mid;
        else last = mid - 1;
    }
    return -1;
}

int DCEL::find_face(int f)
{
    int first = 0, last =F.size()-1, mid;
    while (first <= last){
        mid = (first + last) / 2;
        if (F[mid]->get_id() < f) first = mid + 1;
        else if (F[mid]->get_id() == f) return mid;
        else last = mid - 1;
    }
    return -1;
}

std::vector<vertex_id> DCEL::make_single_border(face_id f)
{
    std::vector< std::vector<vertex_id> > visited;
    std::vector< std::vector<vertex_id> > not_visited;
    std::map< std::pair<int, int>, std::pair<int, int> > links;
    std::vector<vertex_id> tmp;
    for (Face::incident_half_edge_iterator heit = f->incident_half_edge_begin(); heit != f->incident_half_edge_end(); ++heit){
        heit->check_from_vertex();
        tmp.push_back(heit->get_from_vertex());
    }
    visited.push_back(tmp);
    for (Face::inner_half_edge_iterator iheit = f->inner_half_edge_begin(); iheit != f->inner_half_edge_end(); ++iheit){
        tmp.clear();
        for (Face::incident_half_edge_iterator heit = f->incident_half_edge_begin(iheit.get_half_edge_id()); heit != f->incident_half_edge_end(); ++heit){
            heit->check_from_vertex();
            tmp.push_back(heit->get_from_vertex());
        }
        not_visited.push_back(tmp);
    }
    while (not_visited.size() > 0) {
        // trova la coppia di punti tra visited e not_visited più vicina
        double dist = 10000000;
        int vis_index = -1;
        int notvis_index = -1;
        int vis_i = -1;
        int vis_j = -1;
        for (unsigned int i=0; i<visited.size(); ++i){
            std::vector<vertex_id> tmp_visited = visited[i];
            for (unsigned int j=0; j<not_visited.size(); ++j){
                std::vector<vertex_id> tmp_not_visited = not_visited[j];
                for (unsigned int vi = 0; vi<tmp_visited.size(); ++vi){
                    for (unsigned int vj = 0; vj<tmp_not_visited.size(); ++vj){
                        if (((tmp_visited[vi])->dist(tmp_not_visited[vj])) < dist){
                            vis_index = vi;
                            notvis_index = vj;
                            vis_i = i;
                            vis_j = j;
                            dist = (tmp_visited[vi])->dist(tmp_not_visited[vj]);
                        }
                    }
                }
            }
        }
        std::pair<int, int> p1;
        p1.first = vis_i;
        p1.second = vis_index;
        std::pair<int, int> p2;
        p2.first = visited.size();
        p2.second = notvis_index;
        visited.push_back(not_visited[vis_j]);
        not_visited.erase(not_visited.begin() + vis_j);
        links[p1] = p2;
        links[p2] = p1;
    }
    std::vector<vertex_id> border;
    vertex_id start = visited[0][0];
    border.push_back(start);
    vertex_id v = NULL;
    int i = 0;
    int j = 0;
    while (v != start){
        std::pair<int, int> p;
        p.first = i;
        p.second = j;
        if (links.find(p) != links.end()){
            p = links[p];
            i = p.first;
            j = p.second;
            border.push_back(visited[i][j]);
        }
        j = (j + 1) % (visited[i]).size();
        border.push_back(visited[i][j]);
        v = visited[i][j];
    }
    return border;
}

DCEL::half_edge_iterator DCEL::half_edge_begin()
{
    return half_edge_iterator(HE.begin());
}

DCEL::half_edge_iterator DCEL::half_edge_end()
{
    return half_edge_iterator(HE.end());
}

DCEL::vertex_iterator DCEL::vertex_begin()
{
    return vertex_iterator(V.begin());
}

DCEL::vertex_iterator DCEL::vertex_end()
{
    return vertex_iterator(V.end());
}

DCEL::face_iterator DCEL::face_begin()
{
    return face_iterator(F.begin());
}

DCEL::face_iterator DCEL::face_end()
{
    return face_iterator(F.end());
}

bool DCEL::delete_vertex(vertex_id v)
{
    int i = find_vertex(v);
    if (i != -1){
        V.erase(V.begin() + i);
        delete v;
        return true;
    }
    return false;
}

bool DCEL::delete_half_edge(half_edge_id he)
{
    int i = find_half_edge(he);
    //std::vector<half_edge_id>::iterator i = std::find(HE.begin(), HE.end(), he);
    if (i != -1){
        HE.erase(HE.begin() + i);
        delete he;
        return true;
    }
    return false;
}

bool DCEL::delete_face(face_id f)
{
    int i = find_face(f);
    //std::vector<face_id>::iterator i = std::find(F.begin(), F.end(), f);
    if (i != -1){
        F.erase(F.begin() + i);
        delete f;
        return true;
    }
    return false;
}

bool DCEL::delete_vertex(DCEL::vertex_iterator vit)
{
    delete vit.get_vertex_id();
    V.erase(vit.get_iterator());
    return true;
}

bool DCEL::delete_half_edge(DCEL::half_edge_iterator heit)
{
    delete heit.get_half_edge_id();
    HE.erase(heit.get_iterator());
    return true;
}

DCEL::face_iterator DCEL::delete_face(DCEL::face_iterator fit)
{
    delete fit.get_face_id();
    fit.it = F.erase(fit.get_iterator());
    return fit;
}

std::pair<Pointf, Pointf> DCEL::get_bounding_box()
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

bool DCEL::is_triangle_mesh()
{
    face_iterator fit;
    for (fit = face_begin(); fit != face_end(); ++fit)
        if (! fit->is_triangle()) return false;
    return true;
}

void DCEL::update_face_normals()
{
    face_iterator fit;
    for (fit = face_begin(); fit != face_end(); ++fit)
        fit->update_normal();
}

void DCEL::update_vertex_normals()
{
    vertex_iterator vit;
    for (vit = vertex_begin(); vit != vertex_end(); ++vit){
        Vertex::incident_face_iterator fit;
        Vec3 average;
        int num = 0;
        for (fit = vit->incident_face_begin(); fit != vit->incident_face_end(); ++fit){
            average += fit->get_normal();
            num++;
        }
        average /= (float)num;
        average.normalize();
        vit->set_normal(average);
        vit->set_cardinality(num);
    }
}

void DCEL::recalculate_ids()
{
    int i = 0;
    for (vertex_iterator vit = vertex_begin(); vit != vertex_end(); ++vit) vit->set_id(i++);
    i = 0;
    for (half_edge_iterator heit = half_edge_begin(); heit != half_edge_end(); ++heit) heit->set_id(i++);
    i = 0;
    for (face_iterator fit = face_begin(); fit != face_end(); ++fit) fit->set_id(i++);
}

void DCEL::reset_face_colors()
{
    for (face_iterator fit = face_begin(); fit != face_end(); ++fit) fit->set_color(Color());
}

/**
 * Per cancellazione si intende la rimozione di tutti i vertici,
 * gli half-edge e le facce precedentemente create, con relativa
 * perdita di tutte le informazioni in esse contenute.
 */
void DCEL::reset()	{
    for (unsigned int i=0; i<V.size(); i++) delete V[i];
    for (unsigned int i=0; i<HE.size(); i++) delete HE[i];
    for (unsigned int i=0; i<F.size(); i++) delete F[i];
    V.clear();
    HE.clear();
    F.clear();
    vid = 0;
    fid = 0;
    heid = 0;
}

void DCEL::erase()
{
    for (unsigned int i=0; i<V.size(); i++) delete V[i];
    for (unsigned int i=0; i<HE.size(); i++) delete HE[i];
    for (unsigned int i=0; i<F.size(); i++) delete F[i];
    V.clear();
    HE.clear();
    F.clear();
    vid = 0;
    fid = 0;
    heid = 0;
}


DCEL::half_edge_iterator::half_edge_iterator(){
}

DCEL::half_edge_iterator::half_edge_iterator(std::vector<HalfEdge*>::iterator it)
{
    this->it = it;
}

HalfEdge &DCEL::half_edge_iterator::operator *() const
{
    return **it;
}

half_edge_id DCEL::half_edge_iterator::operator ->() const
{
    return *it;
}

DCEL::half_edge_iterator DCEL::half_edge_iterator::operator ++()
{
    ++it;
    return *this;
}

DCEL::half_edge_iterator DCEL::half_edge_iterator::operator ++(int)
{
    half_edge_iterator old_value = *this;
    ++it;
    return old_value;
}

DCEL::half_edge_iterator DCEL::half_edge_iterator::operator --()
{
    --it;
    return *this;
}

DCEL::half_edge_iterator DCEL::half_edge_iterator::operator --(int)
{
    half_edge_iterator old_value = *this;
    --it;
    return old_value;
}

bool DCEL::half_edge_iterator::operator ==(DCEL::half_edge_iterator right)
{
    return this->it == right.it;
}

bool DCEL::half_edge_iterator::operator !=(DCEL::half_edge_iterator right)
{
    return !(*this == right);
}

half_edge_id DCEL::half_edge_iterator::get_half_edge_id()
{
    return *it;
}

std::vector<HalfEdge*>::iterator DCEL::half_edge_iterator::get_iterator()
{
    return it;
}

DCEL::vertex_iterator::vertex_iterator(){
}

DCEL::vertex_iterator::vertex_iterator(std::vector<Vertex*>::iterator it)
{
    this->it = it;
}

Vertex &DCEL::vertex_iterator::operator *() const
{
    return **it;
}

vertex_id DCEL::vertex_iterator::operator ->() const
{
    return *it;
}

DCEL::vertex_iterator DCEL::vertex_iterator::operator ++()
{
    ++it;
    return *this;
}

DCEL::vertex_iterator DCEL::vertex_iterator::operator ++(int)
{
    vertex_iterator old_value = *this;
    ++it;
    return old_value;
}

DCEL::vertex_iterator DCEL::vertex_iterator::operator --()
{
    --it;
    return *this;
}

DCEL::vertex_iterator DCEL::vertex_iterator::operator --(int)
{
    vertex_iterator old_value = *this;
    --it;
    return old_value;
}

bool DCEL::vertex_iterator::operator ==(DCEL::vertex_iterator right)
{
    return this->it == right.it;
}

bool DCEL::vertex_iterator::operator !=(DCEL::vertex_iterator right)
{
    return !(*this == right);
}

vertex_id DCEL::vertex_iterator::get_vertex_id()
{
    return *it;
}

std::vector<Vertex*>::iterator DCEL::vertex_iterator::get_iterator()
{
    return it;
}

DCEL::face_iterator::face_iterator(){
}

DCEL::face_iterator::face_iterator(std::vector<Face*>::iterator it)
{
    this->it = it;
}

Face &DCEL::face_iterator::operator *() const
{
    return **it;
}

face_id DCEL::face_iterator::operator ->() const
{
    return *it;
}

DCEL::face_iterator DCEL::face_iterator::operator ++()
{
    ++it;
    return *this;
}

DCEL::face_iterator DCEL::face_iterator::operator ++(int)
{
    face_iterator old_value = *this;
    ++it;
    return old_value;
}

DCEL::face_iterator DCEL::face_iterator::operator --()
{
    --it;
    return *this;
}

DCEL::face_iterator DCEL::face_iterator::operator --(int)
{
    face_iterator old_value = *this;
    --it;
    return old_value;
}

bool DCEL::face_iterator::operator ==(DCEL::face_iterator right)
{
    return this->it == right.it;
}

bool DCEL::face_iterator::operator !=(DCEL::face_iterator right)
{
    return !(*this == right);
}

face_id DCEL::face_iterator::get_face_id()
{
    return *it;
}

std::vector<Face*>::iterator DCEL::face_iterator::get_iterator()
{
    return it;
}
