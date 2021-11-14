#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <chrono>

#include "graph.h"
#include "gol.h"


bool if_isomorphic_hash(Graph g, Graph h, size_t a, size_t d, size_t r, size_t max_iter) {
    if (g.adjm.size() != h.adjm.size()) {
        return false;
    }
    size_t n = g.adjm.size();

    // prepare games
    std::vector<GOL> g_games, h_games;
    g_games.reserve(n);
    h_games.reserve(n);
    for (size_t i=0; i<n; ++i) {
        std::set<size_t> i_alive{ i };
        g_games.emplace_back(a, d, r, &g, i_alive);
        h_games.emplace_back(a, d, r, &h, i_alive);
    }

    // prepare labels and hasher
    std::hash<size_t> hasher;
    std::vector<size_t> g_labels, h_labels, g_labels_new, h_labels_new, g_labels_sorted, h_labels_sorted;
    for (size_t i=0; i<n; ++i) {
        g_labels.push_back(1);
        h_labels.push_back(1);
        g_labels_new.push_back(1);
        h_labels_new.push_back(1);
        g_labels_sorted.push_back(1);
        h_labels_sorted.push_back(1);
    }

    for (size_t k=0; k<max_iter; ++k) {
        for (size_t game_index=0; game_index<n; ++game_index) {
            g_games[game_index].Evolve();
            h_games[game_index].Evolve();
        }

        for (size_t i=0; i<n; ++i) {
            g_labels_new[i] = g_labels[i];
            h_labels_new[i] = h_labels[i];

            g_labels_sorted.clear();
            h_labels_sorted.clear();
            for (size_t j=0; j<n; ++j) {
                if (i != j) {

                    auto it = g_games[i].alive.find(j);
                    if (it != g_games[i].alive.end()) {
                        g_labels_sorted.emplace_back(hasher(g_labels[j]));
                    }

                    it = h_games[i].alive.find(j);
                    if (it != h_games[i].alive.end()) {
                        h_labels_sorted.emplace_back(hasher(h_labels[j]));
                    }
                }
            }
            std::sort(g_labels_sorted.begin(), g_labels_sorted.end());
            std::sort(h_labels_sorted.begin(), h_labels_sorted.end());

            for (size_t ghash : g_labels_sorted) {g_labels_new[i] = hasher(g_labels_new[i] + ghash);}
            for (size_t hhash : h_labels_sorted) {h_labels_new[i] = hasher(h_labels_new[i] + hhash);}
        }

        g_labels_sorted.clear();
        h_labels_sorted.clear();
        for (size_t i=0; i<n; ++i) {
            g_labels[i] = g_labels_new[i];
            h_labels[i] = h_labels_new[i];

            g_labels_sorted.push_back(g_labels_new[i]);
            h_labels_sorted.push_back(h_labels_new[i]);
        }

        std::sort(g_labels_sorted.begin(), g_labels_sorted.end());
        std::sort(h_labels_sorted.begin(), h_labels_sorted.end());

        for (size_t i=0; i<n; ++i) {
            if (g_labels_sorted[i] != h_labels_sorted[i]) {
                return false;
            }
        }

    }

    return true;
}



void test_collection(std::string filename, size_t max_iter) {
    auto Glst = read_file(filename);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int i=0; i<Glst.size(); ++i) {
        for (int j=i+1; j<Glst.size(); ++j) {
            if (if_isomorphic_hash(Glst[i], Glst[j], 1, 1, 1, max_iter)) {
                if (if_isomorphic_hash(Glst[i], Glst[j], 0, 1, 1, max_iter)) {
                    if (if_isomorphic_hash(Glst[i], Glst[j], 0, 2, 1, max_iter)) {
                        std::cout << "Graphs " << i << " and " << j;
                        std::cout << " coincide under GOL-test" << std::endl;
                    }
                }
            }
        }
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Tested " << Glst.size() << " non-isomorphic graphs in ";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

}

void collect_stats(size_t n, size_t max_m, size_t samples) {

    std::vector<size_t> dies;
    dies.reserve(max_m);
    std::vector<size_t> max_complexity;
    max_complexity.reserve(max_m);
    for (size_t m=n; m<max_m; ++m) {dies.push_back(0); max_complexity.push_back(1);}

    for (size_t m=n; m<max_m; ++m) {
        for (size_t s=0; s<samples; ++ s) {
            Graph g(n, m);
            for (size_t v=0; v<n; ++v) {
                std::set<size_t> v_alive{ v };
                GOL Game(1, 1, 1, &g, v_alive);
                size_t complexity = Game.Complexity();

                if (complexity > max_complexity[m]) {
                    max_complexity[m] = complexity;
                }

                if (Game.alive.empty()) {
                    dies[m] += 1;
                }
            }
        }
    }

    std::cout << "% Dies: [";
    for (size_t m=n; m<max_m; ++m) {
        std:: cout << float(dies[m])/(float(samples)*float(n)) << ", ";
    }
    std:: cout << "]" << std::endl;

    std::cout << "Complexity: [";
    for (size_t m=n; m<max_m; ++m) {
        std:: cout << max_complexity[m] << ", ";
    }
    std:: cout << "]" << std::endl;


}

int main() {
//    test_collection("/home/mk/CLionProjects/GameOfLifeOnGraphsCPP/collections/graph8c.g6", 5);
    collect_stats(15, 60, 1000);
    return 0;
}
