#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <functional>

using namespace std;

// Graph class
class Graph {
public:
    int V;  // number of vertices
    vector<vector<int>> adj; // adjacency list

    Graph(int V) : V(V), adj(V) {}

    // add edge (undirected)
    void addEdge(int u, int v) {
        // avoid duplicate insertion if needed
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // DFS based function to mark connected vertices
    void dfsUtil(int v, vector<bool>& visited, vector<int>& component) {
        visited[v] = true;
        component.push_back(v);
        for (int u : adj[v]) {
            if (!visited[u])
                dfsUtil(u, visited, component);
        }
    }

    // Find connected components of the graph
    vector<vector<int>> connectedComponents() {
        vector<bool> visited(V, false);
        vector<vector<int>> components;
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                vector<int> comp;
                dfsUtil(i, visited, comp);
                components.push_back(comp);
            }
        }
        return components;
    }

    // BFS shortest path between source and target
    vector<int> shortestPath(int source, int target) {
        vector<bool> visited(V, false);
        vector<int> parent(V, -1);
        queue<int> q;
        visited[source] = true;
        q.push(source);
        bool found = false;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == target) {
                found = true;
                break;
            }
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    q.push(v);
                }
            }
        }

        vector<int> path;
        if (!found)
            return path; // empty if no path exists.

        // Backtrack from target to source.
        for (int v = target; v != -1; v = parent[v])
            path.push_back(v);
        reverse(path.begin(), path.end());
        return path;
    }

    // Structure to represent an edge for MST
    struct Edge {
        int u, v, weight;
        bool operator<(const Edge& other) const {
            return weight < other.weight;
        }
    };

    // Find minimal spanning forest (one spanning tree per connected component) using Kruskal's algorithm.
    // All edges are assigned weight = 1.
    vector<Edge> minimalSpanningForest() {
        vector<Edge> edges;
        // Since our graph is undirected, take each edge once.
        set<pair<int, int>> added;
        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) {
                if (added.find({ v,u }) == added.end()) {
                    edges.push_back({ u, v, 1 });
                    added.insert({ u, v });
                }
            }
        }
        sort(edges.begin(), edges.end());

        vector<int> parent(V);
        iota(parent.begin(), parent.end(), 0);

        function<int(int)> findp = [&](int x) -> int {
            if (parent[x] != x)
                parent[x] = findp(parent[x]);
            return parent[x];
            };

        auto unionp = [&](int x, int y) {
            parent[findp(x)] = findp(y);
            };

        vector<Edge> mst;
        for (const auto& e : edges) {
            int pu = findp(e.u), pv = findp(e.v);
            if (pu != pv) {
                mst.push_back(e);
                unionp(pu, pv);
            }
        }
        return mst;
    }

    // A simple greedy matching algorithm. Note, this does NOT guarantee a maximum matching.
    vector<pair<int, int>> greedyMatching() {
        vector<bool> matched(V, false);
        vector<pair<int, int>> matching;
        for (int u = 0; u < V; u++) {
            if (!matched[u]) {
                for (int v : adj[u]) {
                    if (!matched[v]) {
                        matching.push_back({ u, v });
                        matched[u] = matched[v] = true;
                        break;
                    }
                }
            }
        }
        return matching;
    }
};

// Helper functions declared static for internal linkage.
static void printVector(const vector<int>& vec) {
    for (int v : vec)
        cout << v << " ";
    cout << "\n";
}

static void printEdgeList(const vector<Graph::Edge>& edges) {
    for (const auto& e : edges) {
        cout << e.u << " - " << e.v << " (weight " << e.weight << ")\n";
    }
}

static void printMatching(const vector<pair<int, int>>& matching) {
    for (const auto& m : matching) {
        cout << m.first << " -- " << m.second << "\n";
    }
}

int main() {
    string filename = "graph.txt";
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error opening file: " << filename << "\n";
        return 1;
    }

    // First, determine how many vertices we have.
    int maxVertex = -1;
    vector<string> lines;
    string line;
    while (getline(infile, line)) {
        if (line.empty())
            continue;
        lines.push_back(line);
        stringstream ss(line);
        int vertex;
        char colon;
        ss >> vertex >> colon;
        maxVertex = max(maxVertex, vertex);
    }
    infile.close();

    // Create graph with vertices count being maxVertex + 1.
    int numVertices = maxVertex + 1;
    Graph g(numVertices);

    // Re-read the lines from our vector "lines" and parse neighbors.
    for (const string& line : lines) {
        // Expected line format: "<vertex>: (n1), (n2), ..."
        stringstream ss(line);
        int vertex;
        char colon;
        ss >> vertex >> colon; // read vertex and colon

        string token;
        while (getline(ss, token, '(')) {
            // token now starts after '('; extract number until ')'
            if (token.empty()) continue;
            string numStr;
            for (char c : token) {
                if (isdigit(c))
                    numStr.push_back(c);
                else
                    break;
            }
            if (!numStr.empty()) {
                int neigh = stoi(numStr);
                g.addEdge(vertex, neigh);
            }
        }
    }

    // Provide a menu to run different algorithms:
    cout << "Graph Algorithms Demo\n";
    cout << "1. Connected Components\n";
    cout << "2. Shortest Path (BFS)\n";
    cout << "3. Minimal Spanning Forest (Kruskal)\n";
    cout << "4. Greedy Matching\n";
    cout << "Choose an option (1-4): ";

    int option;
    cin >> option;

    switch (option) {
    case 1: {
        auto comps = g.connectedComponents();
        cout << "Connected Components:\n";
        for (size_t i = 0; i < comps.size(); i++) {
            cout << "Component " << i + 1 << ": ";
            printVector(comps[i]);
        }
        break;
    }
    case 2: {
        int source, target;
        cout << "Enter source vertex: ";
        cin >> source;
        cout << "Enter target vertex: ";
        cin >> target;
        auto path = g.shortestPath(source, target);
        if (path.empty())
            cout << "No path found between " << source << " and " << target << "\n";
        else {
            cout << "Shortest path from " << source << " to " << target << ":\n";
            printVector(path);
        }
        break;
    }
    case 3: {
        auto mst = g.minimalSpanningForest();
        cout << "Edges in the minimal spanning forest:\n";
        printEdgeList(mst);
        break;
    }
    case 4: {
        auto matching = g.greedyMatching();
        cout << "Greedy Matching:\n";
        printMatching(matching);
        break;
    }
    default:
        cout << "Invalid option.\n";
        break;
    }

    return 0;
}