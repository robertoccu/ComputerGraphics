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
    bool isEmpty = true;

    BVHNode(const AABB &box, bool leaf, unsigned int index, bool empty);
    BVHNode(){};
};

class BVH {
    std::vector<BVHNode> node_list;
private:
    AABB make_aabb(const std::vector<AABB>& aabb, int left_index, int right_index);
    float calculate_split_edge(const std::vector<AABB>& aabb, int left_index, int right_index, int edge);
    int get_split_index(std::vector<AABB>& aabb, int left_index, int right_index, float split_edge, int edge);
    void build_recursive(int left_index, int right_index, std::vector<AABB>& aabb, int parent);
public:
    BVH(){};
    void construct(std::vector<AABB> &aabbs);
    void show_nodes();

    bool intersect(const Ray& ray, float &t);

};


#endif //COMPUTERGRAPHICS_BVH_H
