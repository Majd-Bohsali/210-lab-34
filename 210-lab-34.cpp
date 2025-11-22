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

    void BFS(int start) { 
        vector<bool> visited(SIZE, false); 
        queue<int> q;
        
        visited[start] = true; 
        q.push(start); 

        while(!q.empty()) { 
            int currNode = q.front(); 
            q.pop(); 

            cout << currNode << " "; 

            for(auto &edge : adjList[currNode]) { 
                if(!visited[edge.first]) { 
                    visited[edge.first] = true;
                    q.push(edge.first);
                }
            }
        }
    }

    void DFS(int start) { 
        vector<bool> visited(SIZE, false); 
        stack<int> s; 

        visited[start] = true; 
        s.push(start); 
        
        while(!s.empty()) { 
            int currNode = s.top(); 
            s.pop(); 

            cout << currNode << " "; 

            for(auto &edge : adjList[currNode]) { 
                if(!visited[edge.first]) { 
                    visited[edge.first] = true;
                    s.push(edge.first);
                }
            }
        }
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

    cout << "------------------------------------------------------\n";
    cout << "Emergency Route Trace using DFS from Intersection 0 (Central Square):\n";
    cout << "Purpose: Simulate a fire truck leaving Central Square and exploring\n";
    cout << "connected streets as far as possible before backtracking.\n";
    cout << "Visit order (intersection IDs):\n";
    graph.DFS(0);

    cout << "\nLayer-by-Layer Street Check using BFS from Intersection 0 (Central Square):\n";
    cout << "Purpose: City planners inspect which intersections are 1 turn away,\n";
    cout << "2 turns away, and so on from Central Square.\n";
    cout << "Visit order (intersection IDs):\n";
    graph.BFS(0);

    return 0;
}

