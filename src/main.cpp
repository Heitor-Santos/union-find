#include "utils.h"
#include "algorithms/naive/union-find.h"
#include "algorithms/improved/union-find.h"

#include <iostream>
#include <string>
#include <iostream>
#include <queue>  
#include <vector> 
#include <unordered_map>
#include <stack> 
#include <set> 
#include <algorithm>
#include <list>
#include <boost/program_options.hpp>
using namespace std;
namespace po = boost::program_options;

void add(NaiveUnionFind* naiveUf, 
        ImprovedUnionFind* improvedUf, 
        UnionFind* union_find, 
        bool isDebug,
        int index){
    if(isDebug){
        naiveUf->makeset(index);
        improvedUf->makeset(index);
    }
    else union_find->makeset(index);
}

void find(NaiveUnionFind* naiveUf, 
        ImprovedUnionFind* improvedUf, 
        UnionFind* union_find, 
        bool isDebug,
        int index){
    if(isDebug){
        naiveUf->find(index);
        improvedUf->find(index);
    }
    else union_find->find(index);
}

void deleteEl(NaiveUnionFind* naiveUf, 
        ImprovedUnionFind* improvedUf, 
        UnionFind* union_find, 
        bool isDebug,
        int index){
    if(isDebug){
        naiveUf->deleteElement(index);
        improvedUf->deleteElement(index);
    }
    else union_find->deleteElement(index);
}

void unionEls(NaiveUnionFind* naiveUf, 
        ImprovedUnionFind* improvedUf, 
        UnionFind* union_find, 
        bool isDebug,
        int index_a,
        int index_b){
    if(isDebug){
        naiveUf->unionElements(index_a, index_b);
        improvedUf->unionElements(index_a, index_b);
    }
    else union_find->unionElements(index_a, index_b);
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string algorithm(argv[1]);
    string input_file(argv[2]);
    string output_file(argc > 3 ? argv[3]:"output");
    FileReader reader(input_file, false);
    string output_file_original = output_file+"_original";
    string output_file_improved = output_file+"_improved";
    string line, final_output, command;
    unordered_map<string, int>single_commands;
    single_commands.insert({"add", 0});
    single_commands.insert({"find", 1});
    single_commands.insert({"delete", 2});
    NaiveUnionFind* naiveUf = new NaiveUnionFind();
    ImprovedUnionFind* improvedUf = new ImprovedUnionFind();
    UnionFind* union_find;
    bool fullReport = algorithm[0]=='f';
    bool isDebug = algorithm=="debug";
    if (algorithm == "original" || algorithm == "foriginal") {
        union_find = naiveUf;
        final_output = output_file_original;
    } else {
        union_find = improvedUf;
        final_output = output_file_improved;
    }
    //FileWriter writer(final_output);
    while (reader.next_line(command)) {
        // cout<<command<<endl;
        if(single_commands.find(command)!=single_commands.end()){
            reader.next_line(line);
            int node = stoi(line);
            int command_num = single_commands[command];
            // cout<<line<<endl;
            switch (command_num){
                case 0: 
                    add(naiveUf, improvedUf, union_find, isDebug, node);
                    break;
                
                case 1: 
                    find(naiveUf, improvedUf, union_find, isDebug, node);
                    break;
                
                case 2: 
                    deleteEl(naiveUf, improvedUf, union_find, isDebug, node);
                    break;
            
                default:
                    break;
            }
        }
        else {
            reader.next_line(line);
            // cout<<line<<endl;
            int index_a, index_b;
            istringstream iss(line);    
            iss >> index_a >> index_b;
            unionEls(naiveUf, improvedUf, union_find, isDebug, index_a, index_b);
        }
        if(isDebug){
            string original_result = Utils().orderedMapText(naiveUf->getComponents());
            string imp_result = Utils().orderedMapText(improvedUf->getComponents());
            cout<<command<<endl;
                cout<<line<<endl;
                cout<<"======================="<<endl;
                cout<<original_result<<endl;
                cout<<"----------------------"<<endl;
                cout<<imp_result<<endl;
            if(original_result!=imp_result){
                break;
            }
        }
    }
    // string final_components = Utils().orderedMapText(union_find->getComponents());
    // writer.append_text(final_components);
    // writer.close();
    reader.close();
}