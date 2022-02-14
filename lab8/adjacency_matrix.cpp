#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    in.tie(0)->sync_with_stdio(false);

    int vertices, arcs;
    in >> vertices >> arcs;

    vector<vector<int>> adjacency_matrix(vertices, vector<int>(vertices, 0));

    int vertex1, vertex2;
    for (int i = 0; i < arcs; i++)
    {
        in >> vertex1 >> vertex2;

        adjacency_matrix[vertex1-1][vertex2-1] = 1;
    }

    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
        {
            if (j == vertices - 1)
                out << adjacency_matrix[i][j] << '\n';
            else
                out << adjacency_matrix[i][j] << ' ';
        }

    return 0;
}