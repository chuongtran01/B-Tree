#include <iostream>
#include "btree.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include <unordered_map> 
#include "ArgumentManager.h"
using namespace std;

int main(int argc, char* argv[]) {
    ArgumentManager am(argc , argv);
    ifstream input(am.get("input"));
    ifstream command(am.get("command"));
    ofstream output(am.get("output"));

    string degree;
    string level;
    string line;
    btree myTree(0);
    
    if (input.peek() == std::ifstream::traits_type::eof()) {
        output << "";
    }
    else {
        while (getline(command, line)) {
            line.erase(remove(line.begin(), line.end(), '\n'), line.end());
            line.erase(remove(line.begin(), line.end(), '\r'), line.end());
            if (line.find("Degree") != -1) {
                degree = line.substr((int)line.find('=') + 1, line.size() - (int)line.find('=')+1);
                myTree.setDegree(stoi(degree));

                int val;
                unordered_map<int,int>mpp;
                while (input >> val) {
                    if (mpp[val] != 1) {
                        mpp[val] = 1;
                        myTree.insert(val);
                    }
                    else if (mpp[val] == 1) {
                        continue;
                    }
                }
            }
            else if (line.find("Level") != -1) {
                level = line.substr((int)line.find(' ') + 1, line.size() - (int)line.find(' ') + 1);
                myTree.printLevel(myTree.getRoot(), stoi(level), output);
                output << endl;
            }
            else if (line.find("Inorder Traversal") != -1) {
                myTree.InOrderTraversal(myTree.getRoot(), output);
                output << endl;
            }
            else if (line.size() == 0) {
                continue;
            }
        }   
    }
    return 0;
}