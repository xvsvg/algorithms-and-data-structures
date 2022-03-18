#include <bits/stdc++.h>

using namespace std;

void dfs(vector<vector<int>> &dg, vector<bool> &visited, vector<int> &winningPositions, int v)
{
    visited[v] = true;

    for (int i = 0; i < dg[v].size(); i++)
    {
        if (!visited[dg[v][i]])
            dfs(dg, visited, winningPositions, dg[v][i]);

        if (winningPositions[dg[v][i]] == 2)
            winningPositions[v] = 1;
    }
}
int main()
{
    ifstream in("game.in");

    int n, m, start;
    in >> n >> m >> start;
    start--;

    vector<vector<int>> dg(n);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        in >> a >> b;

        dg[a - 1].push_back(b - 1);
    }

    vector<bool> visited(n, false);
    vector<int> winningPositions(n, 2);

    for (int i = 0; i < dg.size(); i++)
    {
        if (!visited[i])
            dfs(dg, visited, winningPositions, i);
    }

    if (winningPositions[start] == 1)
        cout << "First player wins\n";
    else
        cout << "Second player wins\n";

    return 0;
}