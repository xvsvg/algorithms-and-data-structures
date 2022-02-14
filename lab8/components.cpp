#include <bits/stdc++.h>
#include <fstream>

using namespace std;

void dfs(vector<vector<int>> &adjacency_matrix, vector<int> &visited, int current_position, int component_number)
{
    visited[current_position] = component_number;

    for (auto vertex : adjacency_matrix[current_position])
        if (!visited[vertex])
        {
            dfs(adjacency_matrix, visited, vertex, component_number);
        }
}

int main()
{
    ifstream in("components.in");
    ofstream out("components.out");
    in.tie(0)->sync_with_stdio(false);

    int vertices, edges;
    in >> vertices >> edges;

    vector<int> visited(vertices, 0);
    vector<vector<int>> adjacency_matrix(vertices);

    int vertex1, vertex2;
    for (int i = 0; i < edges; i++)
    {
        in >> vertex1 >> vertex2;
        adjacency_matrix[vertex1 - 1].push_back(vertex2 - 1);
        adjacency_matrix[vertex2 - 1].push_back(vertex1 - 1);
    }

    int component_number = 0;

    for (int i = 0; i < vertices; i++)
        if (visited[i] == 0)
        {
            ++component_number;
            dfs(adjacency_matrix, visited, i, component_number);
        }

    out << component_number << '\n';
    for (int i = 0; i < visited.size(); i++)
        out << visited[i] << ' ';

    return 0;
}