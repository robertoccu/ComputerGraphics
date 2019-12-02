//
// Created by Sergio on 23/11/2019.
//

#include <cmath>
#include <algorithm>
#include "BVH.h"





/**
 * Crea un AABB grande a partir de los objetos de aabb[left_index, right_index] incluidos
 * @param aabb
 * @param left_index
 * @param right_index
 * @return
 */
AABB BVH::make_aabb(const std::vector<AABB> &aabb, int left_index, int right_index) {
    float minimum[3] = {INFINITY, INFINITY, INFINITY};
    float maximum[3] = {-INFINITY, -INFINITY, -INFINITY};

    for(int dim = 0; dim < 3; dim++){
        for(int i = left_index; i <= right_index; i++){
            if(aabb[i].getMinPoint().get(dim) < minimum[dim]){
                minimum[dim] = aabb[i].getMinPoint().get(dim);
            }
            if(aabb[i].getMaxPoint().get(dim) > maximum[dim]){
                maximum[dim] = aabb[i].getMaxPoint().get(dim);
            }
        }
    }

    return AABB(Vector(minimum[0], minimum[1], minimum[2], 1),
                Vector(maximum[0], maximum[1], maximum[2], 1));
}

void BVH::construct(std::vector<AABB> &aabb) {
    // Creamos nodo raiz
    node_list.resize(2 * aabb.size() - 1);
    auto it = node_list.begin();
    node_list.insert(it, BVHNode(make_aabb(aabb, 0, aabb.size()-1), false, 0));
    n_nodes = 1;
    build_recursive(0, aabb.size()-1, aabb, 0);

}

void BVH::build_recursive(int left_index, int right_index, std::vector<AABB>& aabb, int parent) {
    if((right_index - left_index) >= 2){
        // It's more than two AABBs.
        static int axis = 0;    // X:0, Y:1, Z:2
        // Calculate which is the line that divides the objects if we project them on the axis
        float split_axis = calculate_split_edge(aabb, left_index, right_index, axis);
        // With the dividing line, we get the index of the first element that is to the right of the line.
        int split_index = get_split_index(aabb, left_index, right_index, split_axis, axis);
        // In [left_index, split_index-1] are the objects that have to be in the left leaf.
        // In [split_index, right_index] are the objects that have to be in the right leaf
        AABB bb_left  = make_aabb(aabb, left_index, split_index - 1);;
        AABB bb_right = make_aabb(aabb, split_index, right_index);
        // Create the new nodes
        BVHNode node_left = BVHNode(bb_left, false, 2 * parent + 1);
        BVHNode node_right = BVHNode(bb_right, false, 2 * parent + 2);
        // Insert the two nodes in the node_list
        auto it = node_list.begin();
        node_list.insert(it + (2 * parent + 1), node_left);
        node_list.insert(it + (2 * parent + 2), node_right);
        // Change the new axis to compare
        axis = (axis + 2) % 3;
        // Call the recursive function with the two ranges
        build_recursive(left_index, split_index - 1, aabb, 2 * parent + 1);
        build_recursive(split_index, right_index , aabb, 2 * parent + 2);

    }else if((right_index - left_index) == 1){
        // It's only two AABB, so it's two leafs.
        // Create the left leaf with the left aabb and the right leaf with the right aabb.
        BVHNode left_leaf = BVHNode(aabb[left_index], true, 2 * parent + 1);
        BVHNode right_leaf = BVHNode(aabb[right_index], true, 2 * parent + 2);
        // Insert in the list of nodes the two new leafs.
        auto it = node_list.begin();
        node_list.insert(it + (2 * parent + 1), left_leaf);
        node_list.insert(it + (2 * parent + 2), right_leaf);
    }else{
        //One AABB, set to leaf
        node_list[right_index].leaf = true;
    }

}

void BVH::show_nodes() {
    cout<<"Recorrido en anchura"<<endl;
    for(auto & i : node_list){
        if(i.leaf){
            cout<<"HOJA "<<i.box.getMinPoint()<<", "<<i.box.getMaxPoint()<<endl;
        }else{
            cout<<i.box.getMinPoint()<<", "<<i.box.getMaxPoint()<<endl;
        }

    }
}

/**
 *
 * @param aabb
 * @param left_index
 * @param right_index
 * @param edge
 * @return
 */
float BVH::calculate_split_edge(const std::vector<AABB>& aabb, int left_index, int right_index, int edge) {
    float minEdge = INFINITY, maxEdge = -INFINITY;
    // Recorremos la lista de AABB en busca del minimo y del maximo del eje pedido
    for(int i = left_index; i < right_index; i++){
        if(aabb[i].getMinPoint().get(edge) < minEdge){
            minEdge = aabb[i].getMinPoint().get(edge);
        }
        if(aabb[i].getMaxPoint().get(edge) > maxEdge){
            maxEdge = aabb[i].getMaxPoint().get(edge);
        }
    }

    return minEdge + ( (abs(maxEdge) + abs(minEdge)) / 2);
}

/**
 *
 * @param aabb
 * @param left_index
 * @param right_index
 * @param split_edge
 * @return
 */
int BVH::get_split_index(std::vector<AABB> &aabb, int left_index, int right_index, float split_edge, int edge) {
    // Hay que ordenar el vector en funcion del eje que estemos usando
    auto initial = aabb.begin() + left_index;
    auto right = aabb.begin() + right_index;
    auto final = aabb.end();
    if(edge == 0){
        partial_sort(initial, right, final, AABB::comparatorX);
    }else if(edge == 1){
        partial_sort(initial, right, final, AABB::comparatorY);
    }else if(edge == 2){
        partial_sort(initial, right, final, AABB::comparatorZ);
    }

    // Recorremos la lista para ver que objetos estan a un lado u a otro
    int split_index = left_index;
    for(int i = left_index; i < right_index; i++){
        if(aabb[i].getCentroid().get(edge) < split_edge)
            split_index++;
    }

    return split_index;
}


BVHNode::BVHNode(const AABB &box, bool leaf, unsigned int index) {
    this->box = box;
    this->leaf = leaf;
    this->index = index;
}
