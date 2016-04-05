#include "segmentation.h"

Segmentation::Segmentation()
{
}

Segmentation::Segmentation(DCEL &d)
{
    DCEL::face_iterator fit;
    id = 0;


    for (fit = d.face_begin(); fit != d.face_end(); ++fit){
        if (s.find(fit.get_face_id()) == s.end()){
            patch_id p = new Patch(id++, fit.get_face_id(), s);
            patches.insert(p);
        }
    }
}

Segmentation::~Segmentation()
{
    std::set<patch_id>::iterator it;
    for (it = patches.begin(); it != patches.end(); ++it){
        patch_id p = *it;
        delete p;
    }
}

int Segmentation::get_num_patches()
{
    return patches.size();
}

patch_id Segmentation::get_patch(face_id f)
{
    if (s.find(f) != s.end()) return s[f];
    else return NULL;
}

void Segmentation::delete_patch(patch_id p)
{
    for (Patch::face_iterator fit = p->face_begin(); fit != p->face_end(); ++fit){
        s.erase(fit.get_face_id());
    }
    patches.erase(p);
}

patch_id Segmentation::add_patch(face_id seed)
{
    patch_id p = new Patch(id++, seed, s);
    patches.insert(p);
    return p;
}

bool Segmentation::face_exists(face_id f)
{
    if (s.find(f) == s.end()) return false;
    else return true;
}

Segmentation::patch_iterator Segmentation::patch_begin()
{
    return patch_iterator(patches.begin());
}

Segmentation::patch_iterator Segmentation::patch_end()
{
    return patch_iterator(patches.end());
}

Segmentation::face_iterator Segmentation::face_begin()
{
    return face_iterator(s.begin());
}

Segmentation::face_iterator Segmentation::face_end()
{
    return face_iterator(s.end());
}

Segmentation::patch_iterator::patch_iterator(){
}

Segmentation::patch_iterator::patch_iterator(std::set<patch_id>::iterator it)
{
    this->it = it;
}

Patch &Segmentation::patch_iterator::operator *() const
{
    return **it;
}

patch_id Segmentation::patch_iterator::operator ->() const
{
    return *it;
}

Segmentation::patch_iterator Segmentation::patch_iterator::operator ++()
{
    ++it;
    return *this;
}

Segmentation::patch_iterator Segmentation::patch_iterator::operator ++(int)
{
    patch_iterator old_value = *this;
    ++it;
    return old_value;
}

Segmentation::patch_iterator Segmentation::patch_iterator::operator --()
{
    --it;
    return *this;
}

Segmentation::patch_iterator Segmentation::patch_iterator::operator --(int)
{
    patch_iterator old_value = *this;
    --it;
    return old_value;
}

bool Segmentation::patch_iterator::operator ==(Segmentation::patch_iterator right)
{
    return this->it == right.it;
}

bool Segmentation::patch_iterator::operator !=(Segmentation::patch_iterator right)
{
    return !(*this == right);
}

patch_id Segmentation::patch_iterator::get_patch_id()
{
    return *it;
}

std::set<patch_id>::iterator Segmentation::patch_iterator::get_iterator()
{
    return it;
}


Segmentation::face_iterator::face_iterator()
{

}

Segmentation::face_iterator::face_iterator(std::map<face_id, patch_id>::iterator it)
{
    this->it = it;
}

Face &Segmentation::face_iterator::operator *() const
{
    return *(it->first);
}

face_id Segmentation::face_iterator::operator ->() const
{
    return it->first;
}

Segmentation::face_iterator Segmentation::face_iterator::operator ++()
{
    ++it;
    return *this;
}

Segmentation::face_iterator Segmentation::face_iterator::operator ++(int)
{
    face_iterator old_value = *this;
    ++it;
    return old_value;
}

Segmentation::face_iterator Segmentation::face_iterator::operator --()
{
    --it;
    return *this;
}

Segmentation::face_iterator Segmentation::face_iterator::operator --(int)
{
    face_iterator old_value = *this;
    --it;
    return old_value;
}

bool Segmentation::face_iterator::operator ==(Segmentation::face_iterator right)
{
    return this->it == right.it;
}

bool Segmentation::face_iterator::operator !=(Segmentation::face_iterator right)
{
    return !(*this == right);
}

face_id Segmentation::face_iterator::get_face_id()
{
    return it->first;
}

patch_id Segmentation::face_iterator::get_patch_id()
{
    return it->second;
}
