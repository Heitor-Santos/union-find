#pragma once
#include <fstream>
#include <string>
#include <string.h>
#include <list>
#include <set> 
#include <vector>
#include <unordered_map>
#include <algorithm>

class FileReader {
private:
    bool closed;
    std::ifstream file;

public:
    FileReader(std::string filename, bool binary);

    bool next_line(std::string &line);
    void close();
};

class FileWriter {
private:
    std::ofstream file;

public:
    FileWriter();
    FileWriter(std::string &filename);

    void close();
    void append_text(std::string &text);
};

class UnionFind{
    
public:
    UnionFind();
    virtual int find(int index)=0;
    virtual void makeset(int element)=0;
    virtual void unionElements(int indexA, int indexB)=0;
    virtual void deleteElement(int index)=0;
    virtual std::unordered_map<int, std::set<int>> getComponents()=0;
};

class Utils{
public:
    Utils();
    void printOrderedMap(const std::unordered_map<int, std::set<int>>& map);
    std::string orderedMapText(const std::unordered_map<int, std::set<int>>& map);
};