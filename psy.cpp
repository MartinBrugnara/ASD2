#include <fstream>
#include <vector>

using namespace std;

struct node_t {
    vector<int> neighbors;
};

typedef vector<node_t> graph_t;

vector<int> solve(const graph_t &graph){
    vector<int> res;
    for(int i = 0; i < graph.size(); i++){
        if(graph[i].neighbors.size() == 1){
            res.push_back(i);
            break;
        }
    }
    return res;
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
    return 0;
}
