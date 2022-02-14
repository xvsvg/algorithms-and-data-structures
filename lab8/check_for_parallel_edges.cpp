#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    in.tie(0)->sync_with_stdio(false);

    bool failure = false;
    int vertices, edges;
    in >> vertices >> edges;

    vector<vector<int>> adjacency_matrix(vertices, vector<int>(vertices, 0));

    int vertex1, vertex2;
    for (int i = 0; i < edges; i++)
    {
        in >> vertex1 >> vertex2;

        adjacency_matrix[vertex1 - 1][vertex2 - 1]++;
        adjacency_matrix[vertex2 - 1][vertex1 - 1]++;

        if (adjacency_matrix[vertex1 - 1][vertex2 - 1] + adjacency_matrix[vertex2 - 1][vertex1 - 1] > 2)
        {
            failure = true;
            break;
        }
    }

    if (failure)
        out << "YES";
    else
        out << "NO";

    return 0;
}