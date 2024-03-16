#include "node.h"

using namespace std;

Node::Node(bool _occupied, int _element) {
    occupied = _occupied;
    rank = 0;
    parent = nullptr;
    element = _element;
    prev_sibling = nullptr;
    next_sibling = nullptr;
    children_count = 0;
    children_tail = nullptr;
}

bool Node::isLeaf(){
    return children_count == 0;
}

bool Node::isRoot(){
    return parent == nullptr;
}

bool Node::hasPrevChildren(){
    return prev_sibling != nullptr;
}

bool Node::hasOnlyOneChild(){
    return children_count == 1;
}

bool Node::isTailofTheChildrenList(){
    return next_sibling == nullptr;
}

void Node::removeFromParentChildren(){
    if(!isRoot()){
        if(hasPrevChildren()) prev_sibling->next_sibling = next_sibling;
        if(isTailofTheChildrenList()) parent->children_tail = prev_sibling;
        else next_sibling->prev_sibling = prev_sibling;
        parent->children_count--;
    }
}

void Node::addNodeToParentChildren(Node* node){
    if(!isRoot()){
        Node* parent_last_child = parent->children_tail;
        if(parent_last_child != nullptr){
           parent_last_child->next_sibling = node;
           node->prev_sibling = parent_last_child;
        }
        parent->children_tail = node;
        parent->children_count++;   
    }
    else{
        node->prev_sibling = nullptr;
        node->next_sibling = nullptr;
    }
}

void Node::addToParentChildren(){
    addNodeToParentChildren(this);
}

void Node::addOnlyChildToParentChildren(){
    addNodeToParentChildren(children_tail);
}

Node* Node::getParent(){
    return parent;
}

Node* Node::setParent(Node* _parent){
    parent = _parent;
    return this;
}

int Node::getRank(){
    return rank;
}

Node* Node::setRank(int _rank){
    rank = _rank;
    return this;
}

bool Node::isOccupied(){
    return occupied;
}

Node* Node::setOccupied(bool _occupied){
    occupied = _occupied;
    return this;
}

Node* Node::onlyChild(){
    return children_tail;
}

int Node::getElement(){
    return element;
}