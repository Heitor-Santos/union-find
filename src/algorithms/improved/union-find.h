#pragma once
#include "../../utils.h"
#include "node.h"

#include <unordered_map>
#include <set>

class ImprovedUnionFind: public UnionFind{

private:
    std::unordered_map<int,Node*> uf;

private:
    Node* findAux(Node*);
    Node* findNode(int index);
    void unionAux(Node* parent, Node* node);
    
public:
    ImprovedUnionFind();
    int find(int index);
    void makeset(int element);
    void unionElements(int indexA, int indexB);
    void deleteElement(int index);
    std::unordered_map<int, std::set<int>> getComponents();
};