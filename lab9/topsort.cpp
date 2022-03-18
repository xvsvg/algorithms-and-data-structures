#include <bits/stdc++.h>
#include <fstream>

using namespace std;

void analyzeVertex(vector<vector<int>> &dg, stack<int> &ans, vector<bool> &visited, int index)
{
    visited[index] = true;

    for (auto &i : dg[index])
    {
        if (!visited[i])
            analyzeVertex(dg, ans, visited, i);
    }

    ans.push(index);
}

void topsort(vector<vector<int>> &dg, stack<int> &ans)
{
    vector<bool> visited(dg.size(), false);

    for (int i = 0; i < dg.size(); i++)
    {
        if (!visited[i])
            analyzeVertex(dg, ans, visited, i);
    }
}

bool hasCycle(vector<vector<int>> &dg, stack<int> ans)
{
    unordered_map<int, int> indices;
    int index = 0;

    while (!ans.empty())
    {
        indices[ans.top()] = index;
        index++;
        ans.pop();
    }

    for (int i = 0; i < dg.size(); i++)
        for (auto &it : dg[i])
            if (indices[i] > indices[it])
                return true;

    return false;
}

int main()
{
    ifstream in("topsort.in");

    int n, m;
    in >> n >> m;

    vector<vector<int>> dg(n);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        in >> a >> b;

        if (a == b)
        {
            cout << -1;
            return 0;
        }

        a--;
        b--;
        dg[a].push_back(b);
    }

    stack<int> ans;
    topsort(dg, ans);

    if (hasCycle(dg, ans))
    {
        cout << -1;
        return 0;
    }
    else
        while (!ans.empty())
        {
            cout << ans.top() + 1 << ' ';
            ans.pop();
        }

    return 0;
}