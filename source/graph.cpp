#include <graph.h>
#include <iostream>
#include <fstream> // reading from file
#include <sstream> // reading from file line by line
#include <stdlib.h>

std::string DecToBinary(int n)
{
    std::string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    while(r.size()<6) {r.insert(0, "0");}
    return r;
}

void Graph::print_adjm() {
    int n = this->adjm.size();

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            std::cout << this->adjm[i][j];
        }
        std::cout << std::endl;
    }
}

Graph::Graph(std::string g6) {
    int n = (int)g6[0]-63;

    // fill adj matrix with zeros
    this->adjm.reserve(n);
    std::vector<size_t> row;
    row.reserve(n);
    for(int col=0; col<n; ++col) {row.emplace_back(0);}
    for(int i=0; i<n; ++i) {
        this->adjm.emplace_back(row);
    }

    std::string graphstring;
    for(int i=1; i<g6.size(); ++i) {
        graphstring += DecToBinary((int)g6[i]-63);
    }

    int position = 0;
    for(int j=1; j<n; ++j) {
        for(int i=0; i<j; ++i) {
            if (graphstring[position] == '1') {
                this->adjm[i][j] = 1;
                this->adjm[j][i] = 1;

            }
            position += 1;
        }
    }

}

Graph::Graph(size_t n, size_t m) {
    // fill adj matrix with zeros
    this->adjm.reserve(n);
    std::vector<size_t> row;
    row.reserve(n);
    for(size_t col=0; col<n; ++col) {row.emplace_back(0);}
    for(size_t i=0; i<n; ++i) {
        this->adjm.emplace_back(row);
    }

    size_t edge_count = 0;
    while (edge_count < m) {
        size_t u = rand() % n;
        size_t v = rand() % n;
        if ((u != v) and (this->adjm[u][v] == 0)) {
            this->adjm[u][v] = 1;
            edge_count += 1;
        }
    }
}

std::vector<Graph> read_file(std::string filename) {
    std::ifstream infile(filename);
    std::stringstream iss;
    std::string line;

    std::vector<Graph> Glst;
    std::string s;
    while (true) {
        std::getline(infile, line);
        iss.str(line);
        if (!(iss >> s)){
            break;
        }
        Glst.emplace_back(Graph(s));
        iss.clear();
    }

    return Glst;
}

