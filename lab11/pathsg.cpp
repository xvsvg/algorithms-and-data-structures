#include <bits/stdc++.h>
#include <fstream>

using namespace std;

void evaluateDistance(vector<vector<pair<int, long long>>> &dg, vector<bool> &visited, vector<long long> &distances)
{
    for (int i = 0; i < dg.size(); i++)
    {
        int mark = -1;

        for (int j = 0; j < dg.size(); j++)
        {
            if (!visited[j] && (mark == -1 || distances[j] < distances[mark]))
            {
                mark = j;
            }
        }

        if (distances[mark] == LONG_LONG_MAX)
            break;

        visited[mark] = true;

        for (int j = 0; j < dg[mark].size(); ++j)
        {
            distances[dg[mark][j].first] = min(distances[dg[mark][j].first], distances[mark] + dg[mark][j].second);
        }
    }
}

int main()
{
    ifstream in("pathsg.in");
    ofstream out("pathsg.out");
    in.tie(0)->sync_with_stdio(false);

    int n, m;
    in >> n >> m;

    vector<vector<pair<int, long long>>> dg(n);

    for (int i = 0; i < m; ++i)
    {
        int a, b;
        long long w;
        in >> a >> b >> w;
        a--;
        b--;

        dg[a].push_back({b, w});
    }

    for (int i = 0; i < n; i++)
    {
        vector<long long> distances(n, LONG_LONG_MAX);
        vector<bool> visited(n, false);
        distances[i] = 0;

        evaluateDistance(dg, visited, distances);
        for (auto &x : distances)
        {
            out << x << ' ';
        }
        out << endl;
    }

    return 0;
}