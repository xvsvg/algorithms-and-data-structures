#include <bits/stdc++.h>
#include <fstream>

using namespace std;

const long long INF = 8e18;

void dfs(vector<vector<pair<long long, int>>> &dg, vector<bool> &marks, int v)
{
    marks[v] = true;

    for (int i = 0; i < dg[v].size(); ++i)
    {
        if (!marks[dg[v][i].second])
        {
            dfs(dg, marks, dg[v][i].second);
        }
    }
}

void evaluateDistances(vector<vector<pair<long long, int>>> &dg, vector<bool> &visited, vector<bool> &negativeCycle, vector<long long> &distances)
{
    for (int i = 0; i < dg.size(); ++i)
    {
        for (int j = 0; j < dg.size(); ++j)
        {
            for (auto &x : dg[j])
            {
                if (distances[j] + x.first < distances[x.second])
                {
                    distances[x.second] = max(-INF, distances[j] + x.first);

                    if (i == dg.size() - 1 && visited[x.second])
                    {
                        dfs(dg, negativeCycle, x.second);
                    }
                }
            }
        }
    }
}

int main()
{
    ifstream in("path.in");
    ofstream out("path.out");
    in.tie(0)->sync_with_stdio(false);

    int n, m, s;
    in >> n >> m >> s;

    vector<vector<pair<long long, int>>> dg(n);

    for (int i = 0; i < m; ++i)
    {
        int a, b;
        long long w;
        in >> a >> b >> w;
        a--;
        b--;

        dg[a].push_back({w, b});
    }

    s--;
    vector<bool> visited(n, false);
    dfs(dg, visited, s);

    vector<long long> distances(n, INF);
    distances[s] = 0;
    vector<bool> negativeCycle(n, false);
    evaluateDistances(dg, visited, negativeCycle, distances);

    for (int i = 0; i < n; ++i)
    {
        if (negativeCycle[i] || distances[i] < -INF)
            out << "-\n";
        else if (!visited[i])
            out << "*\n";
        else
            out << distances[i] << '\n';
    }

    return 0;
}