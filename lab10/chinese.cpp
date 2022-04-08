#include <bits/stdc++.h>
#include <fstream>

using namespace std;

void dfs(vector<vector<pair<int, int>>> &dg, vector<bool> &visited, int v)
{
    visited[v] = true;

    for (int i = 0; i < dg[v].size(); i++)
    {
        if (!visited[dg[v][i].first])
            dfs(dg, visited, dg[v][i].first);
    }
}

void getOrder(vector<vector<pair<int, int>>> &dg, vector<int> &order, vector<bool> &visited, int v)
{
    visited[v] = true;
    for (auto &i : dg[v])
    {
        if (!visited[i.first])
        {
            getOrder(dg, order, visited, i.first);
        }
    }
    order.push_back(v);
}

void getComponent(vector<vector<pair<int, int>>> &tdg, vector<bool> &visited, vector<int> &components, int v)
{
    visited[v] = true;
    components.push_back(v);

    for (auto &i : tdg[v])
    {
        if (!visited[i.first])
        {
            getComponent(tdg, visited, components, i.first);
        }
    }
}

void condense(vector<vector<pair<int, int>>> &dg, vector<int> &components, int &numberOfComponents)
{
    vector<vector<pair<int, int>>> tdg(dg.size());

    for (int i = 0; i < dg.size(); i++)
    {
        for (auto &x : dg[i])
        {
            tdg[x.first].push_back({i, x.second});
        }
    }

    vector<int> order;
    vector<bool> visited(dg.size(), false);

    for (int i = 0; i < dg.size(); i++)
        if (!visited[i])
            getOrder(dg, order, visited, i);

    visited.assign(dg.size(), false);
    vector<int> component;

    for (int i = tdg.size() - 1; i >= 0; i--)
    {
        if (!visited[order[i]])
        {
            getComponent(tdg, visited, component, order[i]);

            for (auto &x : component)
            {
                components[x] = numberOfComponents;
            }
            numberOfComponents++;
            component.clear();
        }
    }
}

//                                           {to, weight}
long long getWeightOfMST(vector<vector<pair<int, int>>> &dg, int quantityOfVertices, int v)
{
    long long treeWeight = 0;
    vector<int> minimalWeightsIncomingInEachComponent(quantityOfVertices, INT_MAX);

    for (auto &x : dg)
    {
        for (auto &i : x)
        {
            minimalWeightsIncomingInEachComponent[i.first] = min(i.second, minimalWeightsIncomingInEachComponent[i.first]);
        }
    }

    for (int i = 0; i < quantityOfVertices; i++)
    {
        if (i != v)
            treeWeight += minimalWeightsIncomingInEachComponent[i];
    }

    vector<vector<pair<int, int>>> zeroEdges(quantityOfVertices);
    for (int i = 0; i < dg.size(); i++)
    {
        for (auto &e : dg[i])
        {
            if (e.second == minimalWeightsIncomingInEachComponent[e.first])
            {
                zeroEdges[i].push_back(e);
            }
        }
    }

    vector<bool> visited(quantityOfVertices, false);
    dfs(zeroEdges, visited, v);

    if (all_of(visited.begin(), visited.end(), [](const bool &x)
               { return x; }))
        return treeWeight;

    int numberOfComponents = 0;
    vector<int> components(quantityOfVertices);
    condense(zeroEdges, components, numberOfComponents);

    vector<vector<pair<int, int>>> newEdges(numberOfComponents);
    for (int i = 0; i < dg.size(); i++)
    {
        for (auto &x : dg[i])
        {
            if (components[i] != components[x.first])
            {
                newEdges[components[i]].push_back({components[x.first], (x.second - minimalWeightsIncomingInEachComponent[x.first])});
            }
        }
    }

    treeWeight += getWeightOfMST(newEdges, numberOfComponents, components[v]);
    return treeWeight;
}

int main()
{
    ifstream in("chinese.in");
    ofstream out("chinese.out");
    in.tie(0)->sync_with_stdio(false);

    unsigned n, m;
    in >> n >> m;
    vector<vector<pair<int, int>>> dg(n);

    for (int i = 0; i < m; i++)
    {
        int from, to, w;
        in >> from >> to >> w;

        dg[--from].push_back({--to, w});
    }

    vector<bool> visited(n);
    dfs(dg, visited, 0);

    if (!all_of(visited.begin(), visited.end(), [](const bool &x)
                { return x; }))
    {
        out << "NO";
        return 0;
    }

    out << "YES" << endl;
    out << getWeightOfMST(dg, n, 0) << endl;

    return 0;
}