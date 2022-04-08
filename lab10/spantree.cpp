#include <bits/stdc++.h>
#include <fstream>

using namespace std;

struct point
{
    int x, y;

    inline long double getDist(point b)
    {
        return sqrt(pow(this->x - b.x, 2) + pow(this->y - b.y, 2));
    }
};

struct edge
{
    int from = 0, to = 0;
    long double weight = 0;
};

int main()
{
    ifstream in("spantree.in");
    ofstream out("spantree.out");
    in.tie(0)->sync_with_stdio(false);

    unsigned n;
    in >> n;

    vector<point> points(n);

    for (int i = 0; i < n; i++)
    {
        int x, y;
        in >> x >> y;

        points[i] = {x, y};
    }

    vector<edge> edges;
    edges.reserve(n * n);

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
            edges.push_back({i, j, points[i].getDist(points[j])});
    }

    sort(edges.begin(), edges.end(), [](const edge &a, const edge &b)
         { return a.weight < b.weight; });

    long double minCost = 0;

    vector<int> dsf(n);
    iota(dsf.begin(), dsf.end(), 0);

    for (int i = 0; i < edges.size(); i++)
    {
        int a = edges[i].from;
        int b = edges[i].to;
        long double w = edges[i].weight;

        if (dsf[a] != dsf[b])
        {
            minCost += w;
            int group = dsf[b];

            for (int j = 0; j < n; j++)
                if (dsf[j] == group)
                    dsf[j] = dsf[a];
        }
    }

    out << setprecision(10) << minCost << endl;

    return 0;
}