#include <bits/stdc++.h>
#include <fstream>

using namespace std;

void bfs(vector<vector<int>> &adjacency_list, vector<int> &distances, queue<int> &queue_for_check, int start_point)
{
    if (distances.size() == 0)
        return;

    distances[start_point] = 0;

    queue_for_check.push(start_point);

    while (!queue_for_check.empty())
    {
        int vertex = queue_for_check.front();
        queue_for_check.pop();

        for (auto v : adjacency_list[vertex])
        {
            if (distances[v] == -1)
            {
                distances[v] = distances[vertex] + 1;
                queue_for_check.push(v);
            }
        }
    }
}

int main()
{
    ifstream in("pathbge1.in");
    ofstream out("pathbge1.out");
    in.tie(0)->sync_with_stdio(false);

    int vertices, edges;
    in >> vertices >> edges;

    vector<vector<int>> adjacency_list(vertices);
    int vertex1, vertex2;

    for (int i = 0; i < edges; i++)
    {
        in >> vertex1 >> vertex2;
        adjacency_list[vertex1 - 1].push_back(vertex2 - 1);
        adjacency_list[vertex2 - 1].push_back(vertex1 - 1);
    }

    vector<int> distances(vertices, -1);
    queue<int> queue_for_check;

    bfs(adjacency_list, distances, queue_for_check, 0);

    for (int i = 0; i < distances.size(); i++)
        out << distances[i] << ' ';

    return 0;
}