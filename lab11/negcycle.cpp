#include <bits/stdc++.h>
#include <fstream>

using namespace std;

ifstream in("negcycle.in");
ofstream out("negcycle.out");

void checkForCycle(vector<pair<int, pair<int, int>>> &dg, vector<int> &path, vector<long long> &distances, int quantityOfVertices)
{
    in.tie(0)->sync_with_stdio(false);

    int startOfCycle;
    for (int i = 0; i < quantityOfVertices; ++i)
    {
        startOfCycle = -1;
        for (auto &e : dg)
        {
            if (distances[e.first] + e.second.second < distances[e.second.first])
            {
                distances[e.second.first] = distances[e.first] + e.second.second;
                path[e.second.first] = e.first;
                startOfCycle = e.second.first;
            }
        }
    }

    if (startOfCycle == -1)
    {
        out << "NO\n";
        return;
    }

    vector<int> answer;

    for (int i = 0; i < quantityOfVertices; ++i)
    {
        startOfCycle = path[startOfCycle];
    }

    for (int i = startOfCycle;; i = path[i])
    {
        answer.push_back(i);

        if (i == startOfCycle && answer.size() > 1)
            break;
    }

    reverse(answer.begin(), answer.end());

    out << "YES\n"
        << answer.size() << '\n';

    for (auto &i : answer)
    {
        out << i + 1 << ' ';
    }
}

int main()
{
    int n;
    in >> n;

    vector<pair<int, pair<int, int>>> dg;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int w;
            in >> w;

            if (w != 1e9)
                dg.push_back({i, {j, w}});
        }
    }

    vector<int> path(n, -1);
    vector<long long> distances(n, 1e9);
    distances[0] = 0;

    checkForCycle(dg, path, distances, n);

    return 0;
}