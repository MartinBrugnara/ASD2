#include <fstream>
#include <vector>
#include <utility>

using namespace std;

struct node_t {
    vector<int> neighbors;
};

typedef vector<node_t> graph_t;

pair<vector<int>, bool> solve_rec(const graph_t &graph, const int star_root, const int parent) {
    vector<int> tmp_wo_root; // not passed via star
    pair<vector<int>, bool> res;
    pair<vector<int>, bool> tmp;


    switch (graph[star_root].neighbors.size()) {
        case 1: // leaf
            res.first.push_back(star_root);
            res.second = false;
            break;
        case 2: // transition node
            res =  solve_rec(graph, 
                    (graph[star_root].neighbors[0] != parent ? 
                     graph[star_root].neighbors[0] : 
                     graph[star_root].neighbors[1]), 
                    star_root);
            break;
        default: // > 2 -> star
            for (int i: graph[star_root].neighbors) {
                if (parent != -1 && i == parent) continue;
                // TODO: add star margin algorithm
                
                tmp = solve_rec(graph, i, star_root);
                if (tmp.second) {
                    res.first.insert(res.first.end(), tmp.first.begin(), tmp.first.end());
                } else {
                    tmp_wo_root.insert(tmp_wo_root.begin(), tmp.first.begin(), tmp.first.end());
                }
            }
            if (tmp_wo_root.size() > 1) {
                tmp_wo_root.pop_back();
                res.first.insert(res.first.begin(), tmp_wo_root.begin(), tmp_wo_root.end());
            }
            res.second = true;
            break;
    }

    // TODO: think
    return res;
}

vector<int> solve(const graph_t & graph) {

    int last_leaf = -1, root = -1;
    // identify valid root [>3 children]
    for (int i=0; i<graph.size(); i++) {
        switch(graph[i].neighbors.size()) {
            case 1:
                last_leaf = i;
                break;
            case 2:
                break;
            default:
                root = i;
                goto out;
        }
    }
out:
    if (root == -1)
        return vector<int>{last_leaf};
    return solve_rec(graph, root, -1).first;
}

int main(int argc, char ** argv){
    ifstream in("input.txt");
    graph_t graph;
    int size,M;
    in>>size>>M;
    graph.resize(size);
    for(int i=0;i<M;i++){
        int from, to;
        in >> from >> to;
        graph[from].neighbors.push_back(to);
        graph[to].neighbors.push_back(from);
    }

    vector<int> sol = solve(graph);

    ofstream out("output.txt");
    out << sol.size() << endl;
    for(int i: sol){
        out << i << endl;
    }

    out.close();
    return 0;
}
