#include <bits/stdc++.h>

using namespace std;

void getOrder(vector<vector<int>> &dg, vector<bool> &visited, vector<int> &order, int v)
{
    visited[v] = true;

    for (int i = 0; i < dg[v].size(); i++)
    {
        if (!visited[dg[v][i]])
            getOrder(dg, visited, order, dg[v][i]);
    }

    order.push_back(v);
}

void getComponent(vector<vector<int>> &tdg, vector<bool> &visited, vector<int> &components, int number, int v)
{
    visited[v] = true;
    components[v] = number;

    for (int i = 0; i < tdg[v].size(); i++)
    {
        if (!visited[tdg[v][i]])
            getComponent(tdg, visited, components, number, tdg[v][i]);
    }
}

int main()
{
    ifstream in("cond.in");
    int n, m;
    in >> n >> m;
    vector<vector<int>> dg(n);
    vector<vector<int>> tdg(n);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        in >> a >> b;

        dg[a - 1].push_back(b - 1);
        tdg[b - 1].push_back(a - 1);
    }

    vector<int> order;
    vector<bool> visited(n, false);

    for (int i = 0; i < dg.size(); i++)
    {
        if (!visited[i])
            getOrder(dg, visited, order, i);
    }

    visited.assign(n, false);
    vector<int> components(n, 0);
    int quantity = 0;

    for (int i = 0; i < tdg.size(); i++)
    {
        int v = order[n - 1 - i];
        if (!visited[v])
        {
            ++quantity;
            getComponent(tdg, visited, components, quantity, v);
        }
    }

    cout << quantity << '\n';
    for (auto &it : components)
    {
        cout << it << ' ';
    }

    return 0;
}