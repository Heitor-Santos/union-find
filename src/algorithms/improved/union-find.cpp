#include "union-find.h"
#include <iostream>

using namespace std;


ImprovedUnionFind::ImprovedUnionFind(){
    uf = unordered_map<int,Node*>();
}

Node* ImprovedUnionFind::findAux(Node* node){
    if(node->isRoot()) return node;
    return findAux(node->getParent());
}

int ImprovedUnionFind::find(int element){
    return findAux(uf[element])->getElement();
}

Node* ImprovedUnionFind::findNode(int element){
    return findAux(uf[element]);
}


void ImprovedUnionFind::makeset(int element){
    Node* node = new Node(true, element);
    uf[element] = node;
}

void ImprovedUnionFind::unionAux(Node* parent, Node* node){
    Node* tempParent = node->getParent();
    node->removeFromParentChildren();
    node->setParent(parent);
    node->addToParentChildren();
}

void ImprovedUnionFind::unionElements(int indexA, int indexB){
    Node* rootA = findNode(indexA);
    Node* rootB = findNode(indexB);
    
    if (rootA == rootB) return; // Já estão no mesmo conjunto

    if (rootA->getRank() < rootB->getRank()) {
        std::swap(rootA, rootB); // Garante que rootA tenha a maior altura
    }

    unionAux(rootA, rootB);

    if (rootA->getRank() == rootB->getRank()) {
        rootA->setRank(rootA->getRank() + 1); // Incrementa a altura de rootA
    }
}

void ImprovedUnionFind::deleteElement(int index){
    Node* node = uf[index];
    node->setOccupied(false);
    uf[index]=nullptr;
    uf.erase(index);
    if(!node->isLeaf()){
        // cout<<"1"<<endl;
        if(node->hasOnlyOneChild()){
            // cout<<"11"<<endl;
            node->onlyChild()->setParent(node->getParent());
            node->removeFromParentChildren();
            node->addOnlyChildToParentChildren();
        }
    }

    else{
        // cout<<"111"<<endl;
        node->removeFromParentChildren();
        Node* parent = node->getParent();
        if(!node->isRoot() && parent->isLeaf()) {
            parent->setRank(0);
            // cout<<"1111"<<endl;
        }
        if(!node->isRoot() && !parent->isOccupied()){
            // cout<<"11111 "<<parent->getElement()<<endl;
            if(parent->hasOnlyOneChild()){
                // cout<<"11111111111111 "<<parent->onlyChild()->getElement()<<endl;
                // cout<<"22 "<<parent->onlyChild()->getParent()->getElement()<<endl;
                parent->onlyChild()->setParent(parent->getParent());
                parent->removeFromParentChildren();
                parent->addOnlyChildToParentChildren();
                // if(parent->onlyChild()->getParent()==nullptr)cout<<"nul pa"<<endl;
                // else cout<<parent->onlyChild()->getParent()<<" <<<-----"<<endl;
            }
        }
        delete node;
    }
}

unordered_map<int, set<int>> ImprovedUnionFind::getComponents(){
    unordered_map<int, set<int>> components = unordered_map<int, set<int>>();
    for (const auto& pair : uf) {
        if(pair.second != nullptr){
            Node* nodeRoot = findNode(pair.first); 
            int root = nodeRoot->getElement();
            int parent = pair.second->getParent() == nullptr ? -1 : pair.second->getParent()->getElement();
            // cout<<pair.first<<" "<<root<<endl;
            // cout<<pair.first<<" ->parent: "<<parent<<endl;
            if (components.find(root) == components.end()) {
                components[root] = set<int>(); // Inicializa o conjunto se a chave não existir
            }
            components[root].insert(pair.first);
        }
    }
    return components;
}