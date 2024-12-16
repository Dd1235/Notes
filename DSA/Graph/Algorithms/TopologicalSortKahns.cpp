#include <iostream>
#include <vector>
#include <queue>

#include "DrawGraph.hpp"

using namespace std;

vector<int> topologicalSort(vector<vector<int>> &graph, vector<int> &inDegree)
{
    // O(V+E) time complexity

    int n = graph.size();
    vector<int> sorted;
    queue<int> q;

    for (int i = 0; i < n; i++)
    {
        if (inDegree[i] == 0)
        {
            q.push(i);
        }
    }
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        sorted.push_back(node);

        for (int neighbour : graph[node])
        {
            inDegree[neighbour]--;
            if (inDegree[neighbour] == 0)
            {
                q.push(neighbour);
            }
        }
    }
    if (sorted.size() != n)
        sorted.clear();
    return sorted;
}

int main()
{
    int n, m;
    cout << "Number of vertices: ";
    cin >> n;
    cout << "Number of edges: ";
    cin >> m;

    vector<vector<int>> graph(n);
    vector<int> inDegree(n, 0);

    cout << "Start entering the edges... " << endl;
    for (int i = 0; i < m; i++)
    {
        int from, to;
        cout << "from: ";
        cin >> from;
        cout << "to: ";
        cin >> to;
        graph[from].push_back(to);
        inDegree[to]++;
        cout << "\n";
    }
    vector<int> topologicallySorted = topologicalSort(graph, inDegree);
    if (topologicallySorted.empty() and n != 0)
        cout << "Graph contains a cycle, topological order cannot be found";
    else
    {
        cout << "Topological order: " << "\n";
        for (auto v : topologicallySorted)
            cout << v << " ";
        cout << endl;
    }
    drawGraph(graph);
    return 0;
}
// g++ -I/opt/homebrew/include -L/opt/homebrew/lib TopologicalSortKahns.cpp -lsfml-graphics -lsfml-window -lsfml-system -std=c++17
