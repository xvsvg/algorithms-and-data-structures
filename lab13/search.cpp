#include <bits/stdc++.h>
#include <fstream>

using namespace std;

vector<int> z_function(const string &x)
{
    vector<int> z(x.size(), 0);

    int last = 0, bound = 0;
    for (int i = 1; i < x.size(); ++i)
    {
        if (i < bound)
            z[i] = max(0, min(z[i - last], bound - i));

        while (i + z[i] < x.size() && x[z[i]] == x[i + z[i]])
        {
            z[i]++;
        }

        if (i + z[i] > bound)
        {
            last = i;
            bound = i + z[i];
        }
    }

    z[0] = x.size();
    return z;
}

int main()
{
    ifstream in("search2.in");
    ofstream out("search2.out");
    in.tie(0)->sync_with_stdio(false);

    string p, t;
    in >> p >> t;

    if (p.size() > t.size())
    {
        out << 0 << '\n';
        return 0;
    }

    string support = p + t;

    auto z = z_function(support);
    vector<int> ans;

    for (int i = p.size(); i < z.size(); ++i)
    {
        if (z[i] >= p.size())
            ans.push_back(i);
    }

    out << ans.size() << '\n';
    for (auto &i : ans)
    {
        out << i - p.size() + 1 << ' ';
    }

    return 0;
}