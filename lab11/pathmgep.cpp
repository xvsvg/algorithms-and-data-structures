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
    ifstream in("pathmgep.in");
    ofstream out("pathmgep.out");
    in.tie(0)->sync_with_stdio(false);

    int n, s, f;
    in >> n >> s >> f;
    s--;
    f--;

    vector<vector<pair<int, long long>>> dg(n);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            long long w;
            in >> w;

            if (i != j && w >= 0)
            {
                dg[i].push_back({j, w});
            }
        }
    }

    vector<long long> distances(n, LONG_LONG_MAX);
    vector<bool> visited(n, false);
    distances[s] = 0;

    evaluateDistance(dg, visited, distances);

    if (distances[f] == LONG_LONG_MAX)
        out << -1;
    else
        out << distances[f];

    return 0;
}