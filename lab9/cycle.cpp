#include <bits/stdc++.h>
#include <fstream>

using namespace std;

void analyzeVertex(vector<vector<int>> &dg, vector<bool> &visited, int index, vector<bool> &analyzed, bool &hasCycle, int &cycleStart, int &cycleFinish, vector<int> &path)
{
    visited[index] = true;

    for (int i = 0; i < dg[index].size(); i++)
    {

        if (hasCycle)
            return;

        int next = dg[index][i];

        if (!visited[next] && !analyzed[next])
        {
            path[next] = index;
            analyzeVertex(dg, visited, next, analyzed, hasCycle, cycleStart, cycleFinish, path);
        }
        else if (visited[next] && !analyzed[next])
        {
            cycleStart = next;
            cycleFinish = index;
            hasCycle = true;

            vector<int> ans;
            ans.push_back(cycleStart);

            for (int i = cycleFinish; i != cycleStart; i = path[i])
                ans.push_back(i);

            reverse(ans.begin(), ans.end());

            cout << "YES\n";
            for (int j = 0; j < ans.size(); j++)
                cout << ans[j] + 1 << ' ';

            break;
        }
    }

    analyzed[index] = true;
}

void topsort(vector<vector<int>> &dg, bool &hasCycle, int &cycleStart, int &cycleFinish)
{
    vector<bool> visited(dg.size(), false);
    vector<bool> analyzed(dg.size(), false);
    vector<int> path(dg.size(), -1);

    for (int i = 0; i < dg.size(); i++)
    {
        if (hasCycle)
            return;

        if (!visited[i])
            analyzeVertex(dg, visited, i, analyzed, hasCycle, cycleStart, cycleFinish, path);
    }
}

int main()
{
    ifstream in("cycle.in");

    int n, m;
    in >> n >> m;

    vector<vector<int>> dg(n);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        in >> a >> b;
        a--;
        b--;
        dg[a].push_back(b);
    }

    bool hasCycle = false;
    int cycleStart = -1, cycleFinish = -1;
    topsort(dg, hasCycle, cycleStart, cycleFinish);

    if (!hasCycle)
        cout << "NO\n";

    return 0;
}