#ifndef OCTREE_H
#define OCTREE_H

#include <vector>
#include <float.h>
#include "point.h"


template<typename item_type> class Octree
{
    private:
        Pointd                  bb_min;
        Pointd                  bb_max;
        std::vector<Octree>    children;
        std::vector<item_type> item_list;

    public:

        Octree() {}

        Octree(const Pointd & minim, const Pointd & maxim)
        {
            set_extents(minim, maxim);
        }

        void set_extents(const Pointd & minim, const Pointd & maxim )
        {
            bb_min = minim;
            bb_max = maxim;
        }

        void subdivide()
        {
            assert (children.empty());

            Pointd bb_avg = (bb_min + bb_max)/2.0;

            children.resize(8);
            children[0].set_extents(Pointd(bb_min.x(), bb_min.y(), bb_min.z()),
                                    Pointd(bb_avg.x(), bb_avg.y(), bb_avg.z()));
            children[1].set_extents(Pointd(bb_avg.x(), bb_min.y(), bb_min.z()),
                                    Pointd(bb_max.x(), bb_avg.y(), bb_avg.z()));
            children[2].set_extents(Pointd(bb_avg.x(), bb_avg.y(), bb_min.z()),
                                    Pointd(bb_max.x(), bb_max.y(), bb_avg.z()));
            children[3].set_extents(Pointd(bb_min.x(), bb_avg.y(), bb_min.z()),
                                    Pointd(bb_avg.x(), bb_max.y(), bb_avg.z()));
            children[4].set_extents(Pointd(bb_min.x(), bb_min.y(), bb_avg.z()),
                                    Pointd(bb_avg.x(), bb_avg.y(), bb_max.z()));
            children[5].set_extents(Pointd(bb_avg.x(), bb_min.y(), bb_avg.z()),
                                    Pointd(bb_max.x(), bb_avg.y(), bb_max.z()));
            children[6].set_extents(Pointd(bb_avg.x(), bb_avg.y(), bb_avg.z()),
                                    Pointd(bb_max.x(), bb_max.y(), bb_max.z()));
            children[7].set_extents(Pointd(bb_min.x(), bb_avg.y(), bb_avg.z()),
                                    Pointd(bb_avg.x(), bb_max.y(), bb_max.z()));
        }

        void subdivide_n_levels(const int n)
        {
            assert(children.empty());

            subdivide();

            if (n > 1)
            {
                for(auto & child : children) child.subdivide_n_levels(n-1);
            }
        }

        void get_items(const Pointd & query, std::set<item_type> & items) const
        {
            double eps = 1e-3;

            if (query.x() >= bb_min.x() - eps && query.y() >= bb_min.y() - eps && query.z() >= bb_min.z() - eps &&
                query.x() <= bb_max.x() + eps && query.y() <= bb_max.y() + eps && query.z() <= bb_max.z() + eps)
            {
                if (children.empty())
                {
                    for(auto it : item_list) items.insert(it);
                }
                else
                {
                    assert(children.size() == 8);
                    for(const auto & child : children) child.get_items(query, items);
                }
            }
        }

        void add_item(const item_type & item, const Pointd & minim, const Pointd & maxim)
        {
            if (minim.x() <= bb_max.x() && minim.y() <= bb_max.y() && minim.z() <= bb_max.z() &&
                maxim.x() >= bb_min.x() && maxim.y() >= bb_min.y() && maxim.z() >= bb_min.z() )
            {
                item_list.push_back(item);

                if (!children.empty())
                {
                    assert(children.size() == 8);
                    for(auto & child : children) child.add_item(item, minim, maxim);
                }
            }
        }
};

#endif
