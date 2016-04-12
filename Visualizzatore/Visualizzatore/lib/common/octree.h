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
            children[0].set_extents(Pointd(bb_min[0], bb_min[1], bb_min[2]),
                                    Pointd(bb_avg[0], bb_avg[1], bb_avg[2]));
            children[1].set_extents(Pointd(bb_avg[0], bb_min[1], bb_min[2]),
                                    Pointd(bb_max[0], bb_avg[1], bb_avg[2]));
            children[2].set_extents(Pointd(bb_avg[0], bb_avg[1], bb_min[2]),
                                    Pointd(bb_max[0], bb_max[1], bb_avg[2]));
            children[3].set_extents(Pointd(bb_min[0], bb_avg[1], bb_min[2]),
                                    Pointd(bb_avg[0], bb_max[1], bb_avg[2]));
            children[4].set_extents(Pointd(bb_min[0], bb_min[1], bb_avg[2]),
                                    Pointd(bb_avg[0], bb_avg[1], bb_max[2]));
            children[5].set_extents(Pointd(bb_avg[0], bb_min[1], bb_avg[2]),
                                    Pointd(bb_max[0], bb_avg[1], bb_max[2]));
            children[6].set_extents(Pointd(bb_avg[0], bb_avg[1], bb_avg[2]),
                                    Pointd(bb_max[0], bb_max[1], bb_max[2]));
            children[7].set_extents(Pointd(bb_min[0], bb_avg[1], bb_avg[2]),
                                    Pointd(bb_avg[0], bb_max[1], bb_max[2]));
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

            if (query[0] >= bb_min[0] - eps && query[1] >= bb_min[1] - eps && query[2] >= bb_min[2] - eps &&
                query[0] <= bb_max[0] + eps && query[1] <= bb_max[1] + eps && query[2] <= bb_max[2] + eps)
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
            if (minim[0] <= bb_max[0] && minim[1] <= bb_max[1] && minim[2] <= bb_max[2] &&
                maxim[0] >= bb_min[0] && maxim[1] >= bb_min[1] && maxim[2] >= bb_min[2] )
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
