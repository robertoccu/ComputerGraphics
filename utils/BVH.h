//
// Created by Sergio on 23/11/2019.
//

#ifndef COMPUTERGRAPHICS_BVH_H
#define COMPUTERGRAPHICS_BVH_H

#include <vector>
#include "../geometry/AABB.h"

class BVHNode{
public:
    AABB box;
    bool leaf;
    unsigned int index;

    BVHNode(const AABB &box, bool leaf, unsigned int index);
    BVHNode(){};
};

class BVH {
    std::vector<BVHNode> node_list;
    int n_nodes;
private:
    AABB make_aabb(const std::vector<AABB>& aabb, int left_index, int right_index);
    float calculate_split_edge(const std::vector<AABB>& aabb, int left_index, int right_index, int edge);
    int get_split_index(const std::vector<AABB>& aabb, int left_index, int right_index, float split_edge, int edge);
public:
    BVH(){};
    void construct(const std::vector<AABB> &aabbs);
    void build_recursive(int left_index, int right_index, const std::vector<AABB>& aabb, int depth);
    void show_nodes();

};


#endif //COMPUTERGRAPHICS_BVH_H
