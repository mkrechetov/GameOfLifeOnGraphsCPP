#include <iostream>
#include <graph.h>

std::string DecToBinary(int n)
{
    std::string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    while(r.size()<6) {r.insert(0, "0");}
    return r;
}

void Graph::PrintAdjM() {
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

Graph::Graph(int n, int m, int seed) {

}

