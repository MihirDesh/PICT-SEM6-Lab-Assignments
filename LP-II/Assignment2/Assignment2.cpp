#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <functional>
#include <climits>
#include <list>

using namespace std;

typedef pair<int, string> iPair;

class Graph {
    int V;
    map<string, list<iPair>> adj;
    map<string, int> heuristic;
    map<string, string> cameFrom;

public:
    Graph(int V);

    void addEdge(string u, string v, int w);

    void aStar(string start, string goal);

    void setHeuristic(string city, int value);

    void printPath(string start, string goal);
};

Graph::Graph(int V) {
    this->V = V;
}

void Graph::addEdge(string u, string v, int w) {
    adj[u].push_back(make_pair(w, v));
    adj[v].push_back(make_pair(w, u));
}

void Graph::aStar(string start, string goal) {
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
    map<string, int> dist;
    for (auto j = adj.begin(); j != adj.end(); ++j)
        dist[j->first] = INT_MAX;

    pq.push(make_pair(0, start));
    dist[start] = 0;

    while (!pq.empty()) {
        string u = pq.top().second;
        pq.pop();

        list<iPair>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
            string v = (*i).second;
            int weight = (*i).first;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v] + heuristic[v], v));
                cameFrom[v] = u;
            }
        }
    }

    cout << "Shortest distance from " << start << " to " << goal << " is " << dist[goal] << endl;
}

void Graph::setHeuristic(string city, int value) {
    heuristic[city] = value;
}

void Graph::printPath(string start, string goal) {
    if (start == goal) {
        cout << start;
    } else if (cameFrom.find(goal) == cameFrom.end()) {
        cout << "No path";
    } else {
        printPath(start, cameFrom[goal]);
        cout << " -> " << goal;
    }
}

int main() {
    int V = 14;
    Graph g(V);

    // Add edges
    g.addEdge("Arad", "Zerind", 75);
    g.addEdge("Zerind", "Oradea", 71);
    g.addEdge("Oradea", "Sibiu", 151);
    g.addEdge("Arad", "Sibiu", 140);
    g.addEdge("Arad", "Timisoara", 118);
    g.addEdge("Timisoara", "Lugoj", 111);
    g.addEdge("Lugoj", "Mehadia", 70);
    g.addEdge("Mehadia", "Drobeta", 75);
    g.addEdge("Drobeta", "Craiova", 120);
    g.addEdge("Craiova", "Rimnicu Vilcea", 146);
    g.addEdge("Sibiu", "Rimnicu Vilcea", 80);
    g.addEdge("Rimnicu Vilcea", "Pitesti", 97);
    g.addEdge("Sibiu", "Fagaras", 99);
    g.addEdge("Fagaras", "Bucharest", 211);
    g.addEdge("Pitesti", "Bucharest", 101);
    g.addEdge("Bucharest", "Giurgiu", 90);
    g.addEdge("Bucharest", "Urziceni", 85);
    g.addEdge("Urziceni", "Hirsova", 98);
    g.addEdge("Hirsova", "Eforie", 86);
    g.addEdge("Urziceni", "Vaslui", 142);
    g.addEdge("Vaslui", "Iasi", 92);
    g.addEdge("Iasi", "Neamt", 87);

    // Add heuristic values
    g.setHeuristic("Arad", 366);
    g.setHeuristic("Zerind", 374);
    g.setHeuristic("Oradea", 380);
    g.setHeuristic("Sibiu", 253);
    g.setHeuristic("Timisoara", 329);
    g.setHeuristic("Lugoj", 244);
    g.setHeuristic("Mehadia", 241);
    g.setHeuristic("Drobeta", 242);
    g.setHeuristic("Craiova", 160);
    g.setHeuristic("Rimnicu Vilcea", 193);
    g.setHeuristic("Pitesti", 98);
    g.setHeuristic("Fagaras", 176);
    g.setHeuristic("Bucharest", 0);
    g.setHeuristic("Giurgiu", 77);
    g.setHeuristic("Urziceni", 80);
    g.setHeuristic("Hirsova", 151);
    g.setHeuristic("Eforie", 161);
    g.setHeuristic("Vaslui", 199);
    g.setHeuristic("Iasi", 226);
    g.setHeuristic("Neamt", 234);

    string start, goal;
    cout << "Enter the starting city: ";
    cin >> start;
    cout << "Enter the destination city: ";
    cin >> goal;

    g.aStar(start, goal);
    cout << "Shortest path from " << start << " to " << goal << ": ";
    g.printPath(start, goal);
    cout << endl;

    return 0;
}
