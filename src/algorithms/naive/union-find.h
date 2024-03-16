#pragma once
#include "../../utils.h"
#include <unordered_map>
#include <set>

class NaiveUnionFind : public UnionFind{
    std::unordered_map<int,std::set<int>>component_members;
    std::unordered_map<int,int>mapping_components;

public:
    NaiveUnionFind();
    int find(int index);
    void makeset(int element);
    void unionElements(int indexA, int indexB);
    void deleteElement(int index);
    std::unordered_map<int, std::set<int>> getComponents();
};
