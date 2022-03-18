#include <bits/stdc++.h>

using namespace std;

void dfs(vector<set<int>> &dg, stack<int> &vertices, vector<int> &visited, int v)
{
    visited[v] = true;

    for (auto i = dg[v].begin(); i != dg[v].end(); ++i)
    {
        if (!visited[(*i)])
            dfs(dg, vertices, visited, (*i));
    }

    vertices.push(v);
}

void check(vector<set<int>> &dg, stack<int> &vertices)
{
    int prevV = 0, curV = 0;
    bool err = true;

    if (!vertices.empty())
    {
        prevV = vertices.top();
        vertices.pop();
        err = false;
    }
    while (!vertices.empty())
    {
        curV = vertices.top();
        vertices.pop();

        if (dg[prevV].find(curV) == dg[prevV].end())
        {
            err = true;
            break;
        }

        prevV = curV;
    }

    if (!err)
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main()
{
    ifstream in("hamiltonian.in");

    int n, m;
    in >> n >> m;

    vector<set<int>> dg(n);
    stack<int> vertices;

    for (int i = 0; i < m; i++)
    {
        int a, b;
        in >> a >> b;

        dg[a - 1].insert(b - 1);
    }
    vector<int> visited(n, false);

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
            dfs(dg, vertices, visited, i);
    }

    check(dg, vertices);

    return 0;
}