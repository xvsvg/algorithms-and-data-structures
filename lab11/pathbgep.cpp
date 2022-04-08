#include <bits/stdc++.h>
#include <fstream>

using namespace std;

void evaluateDistances(vector<vector<pair<int, long long>>> &udg, vector<long long> &distances)
{
    priority_queue<pair<int, long long>, deque<pair<int, long long>>, greater<pair<int, long long>>> edgesToBeChecked;
    edgesToBeChecked.push(make_pair(0, 0)); // pair: {distance to this vertex,vertex} <=> pair: {distances[0], 0}

    while (!edgesToBeChecked.empty())
    {
        int v = edgesToBeChecked.top().second;
        long long w = edgesToBeChecked.top().first;
        edgesToBeChecked.pop();

        if (w > distances[v])
            continue;

        for (int i = 0; i < udg[v].size(); ++i)
        {
            int to = udg[v][i].second;
            long long consideringWeight = udg[v][i].first;

            if (distances[v] + consideringWeight < distances[to])
            {
                distances[to] = distances[v] + consideringWeight;
                edgesToBeChecked.push(make_pair(distances[to], to));
            }
        }
    }
}

int main()
{
    ifstream in("pathbgep.in");
    ofstream out("pathbgep.out");
    in.tie(0)->sync_with_stdio(false);

    int n, m;
    in >> n >> m;

    vector<vector<pair<int, long long>>> udg(n);
    for (int i = 0; i < m; ++i)
    {
        int from, to;
        long long w;
        in >> from >> to >> w;

        udg[--from].push_back({w, --to});
        udg[to].push_back({w, from});
    }

    vector<long long> distances(n, LONG_LONG_MAX);
    distances[0] = 0;

    evaluateDistances(udg, distances);

    for (auto &i : distances)
    {
        out << i << ' ';
    }

    return 0;
}