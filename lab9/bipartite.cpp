#include <bits/stdc++.h>
#include <fstream>

using namespace std;

inline int invert(int x)
{
    return (x == 1 ? 2 : 1);
}

void dfs(vector<vector<int>> &udg, vector<int> &marks, int v, int mark)
{
    marks[v] = mark;

    for (int u : udg[v])
    {
        if (marks[u] == 0)
        {
            dfs(udg, marks, u, invert(mark));
        }
        else
        {
            if (marks[u] == mark)
            {
                cout << "NO\n";
                exit(0);
            }
        }
    }
}

int main()
{
    ifstream in("bipartite.in");
    in.tie(0)->sync_with_stdio(false);

    int n, m;
    in >> n >> m;

    vector<vector<int>> udg(n);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        in >> a >> b;
        a--;
        b--;

        udg[a].push_back(b);
        udg[b].push_back(a);
    }

    vector<int> marks(udg.size(), 0);

    for (int i = 0; i < n; i++)
    {
        if (marks[i] == 0)
            dfs(udg, marks, i, 1);
    }

    cout << "YES\n";

    return 0;
}