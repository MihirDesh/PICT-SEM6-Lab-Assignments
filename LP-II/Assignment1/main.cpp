#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    map<int, bool> visited;
    map<int, list<int>> adj;

    void addEdge(int, int);

    void DFS(int);
    void BFS(int v, queue<int> &q);
};

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::DFS(int start)
{
    stack<int> s;
    s.push(start);

    while (!s.empty())
    {
        int v = s.top();
        s.pop();

        if (!visited[v])
        {
            visited[v] = true;
            cout << v << ' ';

            for (int i : adj[v])
            {
                if (!visited[i])
                {
                    s.push(i);
                }
            }
        }
    }
}

void Graph::BFS(int v, queue<int> &q)
{
    if (q.empty())
        return;

    v = q.front();
    q.pop();

    if (!visited[v])
    {
        visited[v] = true;
        cout << v << ' ';

        for (int i : adj[v])
        {
            if (!visited[i])
            {
                q.push(i);
            }
        }
    }

    BFS(v, q);
}

int main()
{
    char f = 10;
    Graph g;
    g.addEdge(0, 1);
    g.addEdge(1, 3);
    g.addEdge(1, 2);
    g.addEdge(2, 4);
    cout << "Enter 1 for DFS and 2 for BFS: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        cout << "Following is Depth First Traversal: \n";
        g.DFS(2);
        break;
    }
    case 2:
    {
        cout << "Following is Breadth First Traversal: \n";
        queue<int> q;
        q.push(2);
        g.BFS(2, q);
        break;
    }
    default:
        cout << "Invalid choice";
    }
    cout << f;
    return 0;
}
