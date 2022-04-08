#include <bits/stdc++.h>
#include <fstream>

using namespace std;

struct edge
{
    int from = 0, to = 0, weight = 0;
};

int find(int x, vector<int> &dsf)
{
    return (x == dsf[x]) ? (x) : dsf[x] = find(dsf[x], dsf);
}

void unite(int x, int y, vector<int> &dsf)
{
    x = find(x, dsf);
    y = find(y, dsf);

    if (x == y)
        return;

    if (x < y)
    {
        swap(x, y);
    }

    dsf[x] = y;
}

int main()
{
    ifstream in("spantree3.in");
    ofstream out("spantree3.out");
    in.tie(0)->sync_with_stdio(false);

    unsigned n, m;
    in >> n >> m;

    vector<edge> edges;
    for (int i = 0; i < m; i++)
    {
        int x, y, w;
        in >> x >> y >> w;

        edges.push_back({x - 1, y - 1, w});
    }

    sort(edges.begin(), edges.end(), [](const edge &a, const edge &b)
         { return a.weight < b.weight; });

    long double minCost = 0;

    vector<int> dsf(n);
    iota(dsf.begin(), dsf.end(), 0);

    int vertexCounter = 0;
    for (int i = 0; i < edges.size() && vertexCounter < n - 1; i++)
    {
        int a = edges[i].from;
        int b = edges[i].to;
        long double w = edges[i].weight;

        if (find(a, dsf) != find(b, dsf))
        {
            minCost += w;
            unite(a, b, dsf);
        }
    }

    out << setprecision(10) << minCost << endl;

    return 0;
}