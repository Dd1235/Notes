#include <iostream>
#include <vector>
#include <stack>

#include "DrawGraph.hpp"

using namespace std;

void dfs(int node, vector<vector<int>> &adj, vector<bool> &visited, stack<int> &st)
{
    visited[node] = true;
    for (int neighbour : adj[node])
    {
        if (!visited[neighbour])
        {
            dfs(neighbour, adj, visited, st);
        }
    }
    st.push(node); // add it once all nodes reachable from it are processed, so we get reverse topological order
}

bool dfs(int node, vector<vector<int>> &adj, vector<bool> &visited, vector<bool> &recStack, stack<int> &st)
{
    visited[node] = true;  // Mark the node as visited
    recStack[node] = true; // Add the node to the recursion stack

    // Explore all neighbors
    for (int neighbor : adj[node])
    {
        if (!visited[neighbor])
        {
            // If the neighbor is unvisited, recursively visit it
            if (dfs(neighbor, adj, visited, recStack, st))
            {
                return true; // Cycle detected in the subtree
            }
        }
        else if (recStack[neighbor])
        {
            // If the neighbor is already in the recursion stack, a cycle is detected
            return true;
        }
    }

    recStack[node] = false; // Remove the node from the recursion stack
    st.push(node);          // Add the node to the stack for topological sort
    return false;           // No cycle detected
}
// vector<int> topologicalSort(vector<vector<int>> &graph)
// {
//     // O(V+E) time complexity

//     int n = graph.size();
//     vector<bool> visited(n, false);
//     stack<int> st;

//     for (int i = 0; i < n; i++)
//     {
//         if (!visited[i])
//             dfs(i, graph, visited, st);
//     }
//     vector<int> sorted;
//     while (st.size())
//     {
//         sorted.push_back(st.top());
//         st.pop();
//     }

//     return sorted;
// }

vector<int> topologicalSort(vector<vector<int>> &graph)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<bool> recStack(n, false); // Tracks the recursion stack
    stack<int> st;

    // Perform DFS for all unvisited nodes
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            if (dfs(i, graph, visited, recStack, st))
            {
                return {}; // Return an empty vector if a cycle is detected
            }
        }
    }

    // Extract nodes from the stack to get the topological order
    vector<int> sorted;
    while (!st.empty())
    {
        sorted.push_back(st.top());
        st.pop();
    }

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
    vector<int> topologicallySorted = topologicalSort(graph);
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
// g++ -I/opt/homebrew/include -L/opt/homebrew/lib TopologicalSortDFS.cpp -lsfml-graphics -lsfml-window -lsfml-system -std=c++17