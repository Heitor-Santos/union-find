#include "union-find.h"
#include "iostream"

using namespace std;

NaiveUnionFind::NaiveUnionFind() {
  mapping_components = unordered_map<int, int>();
  component_members = unordered_map<int, set<int>>();
}

void NaiveUnionFind::makeset(int element){
  mapping_components[element] = element; 
  component_members[element] = std::set<int>(); 
  component_members[element].insert(element);
}

int NaiveUnionFind::find(int index){
  return mapping_components[index];
}

void NaiveUnionFind::unionElements(int indexA, int indexB){
  int root_a = find(indexA);
  int root_b = find(indexB);
  int min_root = min(root_a, root_b);
  int max_root = max(root_a, root_b);
  if(min_root==max_root)return;
  for(int element: component_members[max_root]){
    mapping_components[element] = min_root;
    component_members[min_root].insert(element);
  }
  component_members.erase(max_root);
}

void NaiveUnionFind::deleteElement(int index){
  int root_of_removed_node = mapping_components[index]; 
  if (component_members.find(root_of_removed_node) != component_members.end()) {
    component_members[root_of_removed_node].erase(index);
  }

  if (component_members.find(index) != component_members.end() && !component_members[index].empty()) {
    int first_element = *component_members[index].begin();
    component_members[first_element] = std::set<int>();
    for (auto removed_node_member : component_members[index]) {
      component_members[first_element].insert(removed_node_member);
      mapping_components[removed_node_member] = first_element;
    }
    component_members.erase(index);
  }

  mapping_components.erase(index); 
}

unordered_map<int, set<int>> NaiveUnionFind::getComponents(){
  return component_members;
}
