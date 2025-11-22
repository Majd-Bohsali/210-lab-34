// COMSC210 | Lab 34 | Majd Bohsali
// IDE used: Visual Studio Code
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>  
using namespace std;

const int SIZE = 10;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

class Graph {
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);

        // add edges to the directed graph
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // insert at the end
            adjList[src].push_back(make_pair(dest, weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    void BFS(int start, const vector<string>& names) { 
        vector<bool> visited(SIZE, false); 
        queue<int> q;

        cout << "Layer-by-Layer Street Inspection (BFS) from Intersection " << start
            << " (" << names[start] << "):\n";
        cout << "Purpose: Analyzing which intersections are 1 turn, 2 turns, etc., away\n";
        cout << "=================================================\n";

        visited[start] = true; 
        q.push(start); 

        while(!q.empty()) { 
            int curr = q.front(); 
            q.pop(); 

            cout << "Checking Intersection " << curr 
                << " (" << names[curr] << ")\n";

            for (auto &edge : adjList[curr]) { 
                int nxt = edge.first;
                int time = edge.second;

                if (!visited[nxt]) {
                    cout << "  -> Next reachable intersection: " << nxt 
                        << " (" << names[nxt] 
                        << ") - Travel time: " << time << " minutes\n";

                    visited[nxt] = true;
                    q.push(nxt);
                }
            }
        }
        cout << endl;
    }

    void DFS(int start, const vector<string>& names) { 
        vector<bool> visited(SIZE, false); 
        stack<int> s; 

        cout << "Driving Route Trace (DFS) from Intersection " << start 
            << " (" << names[start] << "):\n";
        cout << "Purpose: Tracing how a car might travel deep into the street network\n";
        cout << "=======================================\n";

        visited[start] = true; 
        s.push(start); 
        
        while(!s.empty()) { 
            int curr = s.top(); 
            s.pop(); 

            cout << "Inspecting Intersection " << curr << " (" 
                << names[curr] << ")\n";

            // list neighbors with arrows BEFORE pushing
            for (auto &edge : adjList[curr]) { 
                int nxt = edge.first;
                int time = edge.second;

                if (!visited[nxt]) {
                    cout << "  -> Possible route to Intersection " << nxt 
                        << " (" << names[nxt] 
                        << ") - Travel time: " << time << " minutes\n";
                }
            }

            // Now push neighbors
            for (auto &edge : adjList[curr]) { 
                int nxt = edge.first;
                if (!visited[nxt]) {
                    visited[nxt] = true;
                    s.push(nxt);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,8}, {0,4,17}, {0,7,5}, {1,2,6}, {1,5,12}, {2,3,9}, {2,8,4},
        {3,6,11}, {4,5,7}, {4,9,13}, {5,7,10}, {6,8,15}, {7,9,3}, {8,9,6}
    };

    // Creates graph
    Graph graph(edges);

     vector<string> intersectionNames = {
        "Central Square", "Maple & 1st", "Oak & 2nd", "Pine & 3rd", "River Bridge",
        "Hill Market", "Stadium Entrance", "Library Plaza", "City Park Gate", "Train Station Plaza"
    };


    cout << "City Street Network Topology (Intersections and Roads)" << endl << endl; 

    for (int i = 0; i < SIZE; ++i) {
        cout << "Intersection " << i << " (" << intersectionNames[i] << ") connects to:\n";
        for (const auto &edge : graph.adjList[i]) {
            int neighbor = edge.first;
            int minutes  = edge.second;
            cout << "   -> Intersection " << neighbor << " ("
                 << intersectionNames[neighbor]
                 << ") - Travel time: " << minutes << " minutes\n";
        }
        cout << endl;
    }

    graph.DFS(0, intersectionNames);
    graph.BFS(0, intersectionNames);
    return 0;
}

